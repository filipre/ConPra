#include <iostream>
#include <string>

// http://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    // replace following stuff
    // entin    -> ierende
    // enten    -> ierende
    // ent      -> ierender
    // 
    // be greedy
    
    int t;
    std::cin >> t; // always 1
    std::cout << "Case #" << t << ":\n";

    int n;
    std::cin >> n; // 1 <= n <= 1000
    std::cin.ignore();

    std::string sentence;
    for (int i=0; i<n; ++i)
    {
        std::getline(std::cin, sentence);
        
        sentence = ReplaceAll(sentence, "entin", "ierende");
        sentence = ReplaceAll(sentence, "enten", "ierende");
        sentence = ReplaceAll(sentence, "ent", "ierender");
                
        std::cout << sentence << '\n';
    }
            
    return 0;
}


