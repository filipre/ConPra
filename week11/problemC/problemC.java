import java.util.Scanner;
import java.math.BigInteger;
import java.util.*;

public class problemC {
	public static void main(String[] args) {
		// create scanner object
		Scanner s = new Scanner(System.in);

		long t = s.nextInt();

		for (long testCase=1; testCase<=t; ++testCase)
		{
			System.out.print("Case #" + testCase + ": ");
			// System.out.print("\n");

            int n = s.nextInt();
            BigInteger y = BigInteger.valueOf(s.nextLong());

            BigInteger mod = BigInteger.valueOf(10).pow(n);
            BigInteger x = y.modInverse(mod);

            System.out.println(x);
		}
	}
}
