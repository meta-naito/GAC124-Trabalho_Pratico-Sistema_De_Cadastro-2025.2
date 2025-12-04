#include <iostream>
#include <string>
#include <map>

std::string removeAccents(const std::string& input) {
    std::map<char, char> accentMap;
    // Populate the map with accented characters and their unaccented equivalents
    accentMap['á'] = 'a';
    accentMap['é'] = 'e';
    accentMap['í'] = 'i';
    accentMap['ó'] = 'o';
    accentMap['ú'] = 'u';
    accentMap['Á'] = 'A';
    accentMap['É'] = 'E';
    accentMap['Í'] = 'I';
    accentMap['Ó'] = 'O';
    accentMap['Ú'] = 'U';
    accentMap['ñ'] = 'n'; // Example for 'ñ'
    accentMap['Ñ'] = 'N'; // Example for 'Ñ'
    // Add more mappings as needed for other accented characters

    std::string result = "";
    for (char c : input) {
        if (accentMap.count(c)) { // Check if the character is in our map
            result += accentMap[c];
        } else {
            result += c; // If not accented, keep it as is
        }
    }
    return result;
}

int main() {
    std::string text = "Hola, ¿cómo estás, señor? Ésta es una prueba.";
    std::string unaccentedText = removeAccents(text);
    std::cout << "Original: " << text << std::endl;
    std::cout << "Unaccented: " << unaccentedText << std::endl;
    return 0;
}