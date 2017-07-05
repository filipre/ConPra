import java.util.Scanner;
import java.math.BigInteger;
import java.util.*;
// import BigIntEuclidean;

public class problemC {

	public static void main(String[] args) {
		// create scanner object
		Scanner s = new Scanner(System.in);

		long t = s.nextInt();

		for (long testCase=1; testCase<=t; ++testCase)
		{
			System.out.print("Case #" + testCase + ": ");
			// System.out.print("\n");

			long n = s.nextLong();

			long kInput = s.nextLong();
			BigInteger k = BigInteger.valueOf(kInput);

			Vector<BigInteger> size = new Vector<>();
			Vector<BigInteger> rest = new Vector<>();
			Map<BigInteger, BigInteger> foundPrimes = new HashMap<>();
			boolean possible = true;
			BigInteger M = BigInteger.valueOf(1);

			for (int i=1; i<=n; ++i)
			{
				BigInteger size_i = BigInteger.valueOf(s.nextLong());
				BigInteger rest_i = BigInteger.valueOf(s.nextLong());

				BigInteger checkRest = foundPrimes.get(size_i);
				if (checkRest != null)
				{
					// we already have that under that key
					if (checkRest.equals(rest_i))
					{
						// ignore
					}
					else
					{
						possible = false;
					}
				}
				else
				{
					foundPrimes.put(size_i, rest_i);
					M = M.multiply(size_i);
					size.add(size_i);
					rest.add(rest_i);
				}

			}

			// if (n == 0)
			// {
			// 	System.out.println("0");
			// 	continue;
			// }

			if (!possible)
			{
				System.out.println("impossible");
				continue;
			}

			n = size.size();
			BigInteger result = BigInteger.valueOf(0);

			/*
			for (int i = 0; i < k; i++)
		    {
		        int pp = prod / num[i];
		        result += rem[i] * inv(pp, num[i]) * pp;
		    }
			*/

			for (int i=0; i<n; ++i)
			{
				BigInteger M_i = M.divide(size.get(i));
				BigInteger inv = M_i.modInverse(size.get(i));
				BigInteger prod = rest.get(i).multiply(M_i).multiply(inv);
				result = result.add(prod);
			}
			result = result.mod(M);

			// System.out.println(result);

			BigInteger scale = k.subtract(result).divide(M);
			result = result.add(scale.multiply(M));

			if (result.compareTo(k) == 1)
			{
				System.out.println("impossible");
			}
			else
			{
				System.out.println(result);
			}



			// result > k
			// if (result.compareTo(k) == 1)
			// {
			// 	System.out.println("impossible");
			// 	continue;
			// }



			// if (result.compareTo(k) == 0)
			// {
			// 	System.out.println(result);
			// }
			//
			// else
			// {
			// 	BigInteger scale = k.subtract(result).divide(M);
			// 	result = result.add(scale.multiply(M));
			// 	System.out.println(result);
			// }

		}
	}
}
