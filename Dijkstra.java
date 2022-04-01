package greedy;

public class Dijkstra {
    //아는 것
    private final int[][] graph;                        //문제
    private final boolean[] visited;                    //방문정보
    public static final int INF = Integer.MAX_VALUE/2;  //무한대

    //생성자 (초기화)
    public Dijkstra(int[][] graph) {
        this.graph = graph;
        this.visited = new boolean[graph.length];
    }

    //하는 것
    public int[] find(int x) {  //x는 시작정점
        int[] dist = graph[x];  //distance [0, 5, INF,
        visited[x] = true;      //

        for (int i = 0; i < graph.length; i++) {
            int vmin = closest(graph[x]);   //경유지 선택(distance vector)
            update(dist, vmin);             //min(직행, 경유지)
        }
        return dist;
    }

    private void update(int[] dist, int vmin) {
        for (int i = 0; i < graph.length; i++) {        //i 목적지
            int layover = dist[vmin] + graph[vmin][i];  //min(d15, d14 + d45)
            dist[i] = (layover < dist[i]) ? layover : dist[i];
        }
    }

    private int closest(int[] row) {
        int min = INF;
        int idx = 0;
        for (int i = 0; i < row.length; i++) {
            if (!visited[i] && row[i] < min) {
                idx = i;
                min = row[i];
            }
        }
        visited[idx] = true;
        return idx;
    }

    public static void main(String[] args) {
        int[][] graph = {
                {0, 7, INF, INF, 3, 10, INF},
                {7, 0, 4, 10, 2, 6, INF},
                {INF, 4, 0, 2, INF, INF, INF},
                {INF, 10, 2, 0, 11, 9, 4},
                {3, 2, INF, 11, 0, INF, 5},
                {10, 6, INF, 9, INF, 0, INF},
                {INF, INF, INF, 4, 5, INF, 0}
        };

        Dijkstra dijkstra = new Dijkstra(graph);
        int[] dist = dijkstra.find(0);
        for (int i : dist) {
            System.out.printf("%d, ", i);
        }
        System.out.println();
    }
}