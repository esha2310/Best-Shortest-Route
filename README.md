# Best Shortest Route

Academic C++ project that models locations as a weighted graph and uses **Dijkstra's algorithm** to compute a shortest route and approximate travel distance between two listed locations.

## Course context

- Course: Data Structure
- Institution: Daffodil International University
- Team members: Rafi Shariar, Mahmudul Hasan, Nafisa Tasneem Esha, Asif

## Features

- Weighted undirected graph using an adjacency-list representation
- Dijkstra shortest-path computation
- Parent tracking for route reconstruction
- Alphabetically grouped location display
- Repeated route queries until the user exits
- Relative data-file paths for portability
- Input validation for unknown locations

## Repository structure

```text
Best-Shortest-Route/
├── src/
│   └── main.cpp
├── data/
│   ├── map_set.txt
│   └── data.txt
├── report/
│   ├── Best_Shortest_Route_Project_Report.docx
│   ├── Best_Shortest_Route_Project_Report.pdf
│   └── original/
│       └── DS_report.pdf
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Build and run

### g++

```bash
g++ -std=c++17 src/main.cpp -o best_shortest_route
./best_shortest_route
```

On Windows/MinGW:

```bash
g++ -std=c++17 src/main.cpp -o best_shortest_route.exe
best_shortest_route.exe
```

Run the executable from the repository root so it can locate `data/map_set.txt` and `data/data.txt`.

## Example queries reproduced from the academic report

- `Dhanmondi -> Shyamoly -> Mirpur -> DIU` (23 km in the report example)
- `Old_dhaka -> New_market -> Dhanmondi -> Shyamoly -> Mirpur` (12 km in the report example)

## Data note

The uploaded academic report contains the project code and example outputs but does **not** provide the original complete `data.txt` edge list. For a runnable GitHub portfolio repository, `data/data.txt` is therefore a **clearly labeled demo graph reconstructed for reproducibility**. It preserves the two example route totals shown in the report, but it should not be presented as the original full academic distance dataset.

## Portfolio description

**Best Shortest Route** [Code]  
Academic C++ project using graph data structures and Dijkstra's algorithm to compute shortest routes and approximate travel distance between locations.
