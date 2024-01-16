# EvanstonCampusNavigator
EvanstonCampusNavigator is a C++ application designed to navigate Open Street Maps, specifically focused on Northwestern's Evanston campus. It efficiently finds the shortest paths between buildings, leveraging detailed map data.

## Features
- **Map Parsing**: Extracts and processes data from Open Street Map XML files.
- **Pathfinding**: Implements algorithms to find the shortest paths between campus buildings.
- **Data Handling**: Manages Nodes (map positions) and Ways (paths defining buildings and footways).

## Technologies Used
- **C++**: Core programming language.
- **XML Parsing**: Utilizes [TinyXML](http://www.grinninglizard.com/tinyxml/) for handling map data.
- Additional libraries and tools can be listed here.

## Getting Started
To start using the EvanstonCampusNavigator:

1. **Setup**:
    - Install a C++ development environment (like GCC).
    - Ensure you have a C++17 compliant compiler.
    - Download and install [TinyXML](http://www.grinninglizard.com/tinyxml/) for XML parsing.

2. **Compilation**:
    - Compile the project using a command like:
      ```
      g++ -o EvanstonCampusNavigator main.cpp
      ```
      Replace `main.cpp` with the names of your source files.

3. **Execution**:
    - Run the program with:
      ```
      ./EvanstonCampusNavigator
      ```
      Add any necessary command line arguments.

## Implementation Details
The EvanstonCampusNavigator project is structured around several key components:

- **Classes**:
  - `MapParser`: Responsible for reading and processing XML map data.
  - `PathFinder`: Implements pathfinding algorithms.
  - `Node`: Represents map positions.
  - `Way`: Represents a series of nodes defining buildings and footways.

- **Algorithms**:
  - Pathfinding is achieved using algorithms like Dijkstra's or A* for efficient shortest path calculations.
  - XML data is parsed and organized to facilitate quick and accurate map rendering and pathfinding.

