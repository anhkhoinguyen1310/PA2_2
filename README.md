# Name
Madhu Seshadri

Netid: ms3249

Khoi Nguyen

netid: kan140


---



# **Our Implementation:**

Introduction:
The Comprehensive Spell-Checker Application in C provides a robust solution for identifying and correcting spelling errors within text files. Combining the functionality of a spell-checker with a user-friendly command-line interface, the application efficiently processes multiple text files, reporting errors and suggestions for improvement.

**Key Components:**

*Main Function (main.c)*: This component serves as the entry point for the spell-checker application. It parses command-line arguments, loads the dictionary, processes each text file provided as input, and unloads the dictionary upon completion.

*Dictionary Handling (dictionary.h, dictionary.c)*: Responsible for loading and unloading the dictionary containing correctly spelled words. This component ensures efficient lookup of words during the spell-checking process.

*File Handling (file_handler.h, file_handler.c)*: Implements functions for reading and processing text files. This component extracts words from the files, performs spell-checking, and reports any identified errors.

*Usage*:

Users interact with the spell-checker application via the command line. The following usage format is supported:


Usage: <executable_name> <dictionary_path> <text_file1> [text_file2] ...
<dictionary_path>: Path to the dictionary file containing correctly spelled words.
<text_file1> [text_file2] ...: Paths to the text files to be spell-checked.

Upon execution, the application loads the dictionary, checks the spelling of words in each text file provided, and outputs any detected errors to the standard error stream.

**File Handling Component (file_handler.h, file_handler.c):**

This component is responsible for processing text files, extracting words, and performing spell-checking. Key functionalities include:

checkSpelling Function: Accepts a file path as input and determines whether it is a directory or a single file. If it is a directory, the function traverses the directory recursively, processing all .txt files found within. If it is a file, the function processes the file directly.

processFile Function: Reads the contents of a text file, tokenizes the words, and performs spell-checking on each word. It then reports any identified spelling errors.

traverseDirectory Function: Recursively traverse directories to locate .txt files, calling the processFile function for each file found.

**Conclusion**:

The Comprehensive Spell-Checker Application in C offers a versatile solution for spell-checking text files, suitable for integration into various software projects. With its modular architecture, intuitive command-line interface, and robust file handling capabilities, the application addresses the critical need for accurate and error-free written communication in both personal and professional contexts.






