# Parallel-Search-OpenMP
Searching for an element in a huge csv file can take quite a long time. Using parallel programming (with help of openmp library) we can divide the csv files in parts and search an eleemnt relatively quickly.
This project highlights how efficient parallel programming can be when compared to it's sequential counterparts.

Step 1: Install Qt
    Go to the Qt Downloads page and download the Qt installer for your operating system.
    Run the installer and choose a version of Qt (preferably the latest stable version).
    Make sure to select Qt Creator (IDE) and the necessary components for your platform (e.g., Desktop development for your OS).
    Complete the installation.
Step 2: Install OpenMP Support (if needed)
    Linux: OpenMP is usually included with GCC. You can confirm by running gcc -fopenmp in the terminal. If it’s not installed, you can install it via:
    bash
        Copy code
            sudo apt install gcc
    Windows: OpenMP is supported with MSVC. Ensure you have the latest Visual Studio installed or a version of GCC that supports OpenMP.
    macOS: OpenMP is not enabled by default with Apple’s Clang. It’s recommended to install GCC through Homebrew:
    bash
        Copy code
            brew install gcc
Step 3: Download and Open the Project in Qt Creator
    Clone the project repository from GitHub or download it as a ZIP file.
    bash
        Copy code
            git clone <your-repository-url>
    Open Qt Creator.
    Select File > Open File or Project....
    Navigate to the downloaded project folder and open the searchusingopenmp.pro file.
    Qt Creator will parse the project and load all files.
Step 4: Configure the Project
    Qt Creator may prompt you to select a Kit for building the project. Choose a kit that includes OpenMP support (such as Desktop GCC, Desktop MSVC).
    Confirm the configuration.
Step 5: Build the Project
    In Qt Creator, go to the Build menu and select Build Project "searchusingopenmp".
    The project should compile without errors if all dependencies are set up correctly.
Step 6: Run the Project
    After building, go to the Run menu and select Run.
    The application window should open. You’ll see the main UI where you can select a CSV file and perform a search.
Step 7: Using the Application
    Load a CSV File: Click on the button to select and load a CSV file.
    Enter Search Term: Enter the search term you’re looking for in the CSV file.
    Search: Click the search button to initiate the search. The program will display the search results, including sequential and parallel search times and the total number of occurrences.
    
