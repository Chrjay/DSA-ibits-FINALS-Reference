function primMST(graph) {
    const V = graph.length;              
    const key = new Array(V).fill(Number.MAX_VALUE);
    const parent = new Array(V).fill(null);
    const mstSet = new Array(V).fill(false);

    // Start from vertex 0
    key[0] = 0;
    parent[0] = -1; // first node is root

    // Build MST
    for (let i = 0; i < V - 1; i++) {
        
        // Pick the minimum key vertex not yet in MST
        let u = -1, min = Number.MAX_VALUE;
        for (let v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        // Update key and parent for neighbors
        for (let v = 0; v < V; v++) {
            if (graph[u][v] > 0 && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the constructed MST
    console.log("Edge \tWeight");
    for (let i = 1; i < V; i++) {
        console.log(parent[i] + " - " + i + " \t" +
                               graph[parent[i]][i]);
    }
}

const graph = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
];

primMST(graph);
