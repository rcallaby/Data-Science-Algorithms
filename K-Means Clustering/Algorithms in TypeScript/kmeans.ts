interface DataPoint {
    x: number;
    y: number;
  }
  
  class KMeans {
    private k: number;
    private data: DataPoint[];
    private centroids: DataPoint[];
  
    constructor(k: number, data: DataPoint[]) {
      this.k = k;
      this.data = data;
      this.centroids = [];
    }
  
    private initializeCentroids(): void {
      // Randomly select k data points as initial centroids
      const randomIndices = new Set<number>();
      while (randomIndices.size < this.k) {
        const randomIndex = Math.floor(Math.random() * this.data.length);
        randomIndices.add(randomIndex);
      }
  
      randomIndices.forEach((index) => {
        this.centroids.push(this.data[index]);
      });
    }
  
    private assignPointsToClusters(): number[] {
      const clusterLabels: number[] = [];
  
      for (const point of this.data) {
        let minDistance = Infinity;
        let label = 0;
  
        for (let i = 0; i < this.k; i++) {
          const centroid = this.centroids[i];
          const distance = this.calculateDistance(point, centroid);
  
          if (distance < minDistance) {
            minDistance = distance;
            label = i;
          }
        }
  
        clusterLabels.push(label);
      }
  
      return clusterLabels;
    }
  
    private calculateDistance(pointA: DataPoint, pointB: DataPoint): number {
      const dx = pointA.x - pointB.x;
      const dy = pointA.y - pointB.y;
      return Math.sqrt(dx * dx + dy * dy);
    }
  
    private updateCentroids(clusterLabels: number[]): void {
      const clusterSums: DataPoint[] = new Array(this.k).fill({ x: 0, y: 0 });
      const clusterCounts = new Array(this.k).fill(0);
  
      for (let i = 0; i < this.data.length; i++) {
        const point = this.data[i];
        const label = clusterLabels[i];
  
        clusterSums[label].x += point.x;
        clusterSums[label].y += point.y;
        clusterCounts[label]++;
      }
  
      this.centroids = clusterSums.map((sum, i) => ({
        x: sum.x / clusterCounts[i],
        y: sum.y / clusterCounts[i],
      }));
    }
  
    public run(): number[] {
      this.initializeCentroids();
  
      let prevClusterLabels: number[] = [];
      let clusterLabels = this.assignPointsToClusters();
  
      while (!this.arraysEqual(prevClusterLabels, clusterLabels)) {
        prevClusterLabels = clusterLabels;
        this.updateCentroids(clusterLabels);
        clusterLabels = this.assignPointsToClusters();
      }
  
      return clusterLabels;
    }
  
    private arraysEqual(a: any[], b: any[]): boolean {
      if (a.length !== b.length) {
        return false;
      }
  
      for (let i = 0; i < a.length; i++) {
        if (a[i] !== b[i]) {
          return false;
        }
      }
  
      return true;
    }
  }
  
  // Usage example:
  const data: DataPoint[] = [
    { x: 1, y: 1 },
    { x: 1, y: 2 },
    { x: 2, y: 1 },
    { x: 5, y: 4 },
    { x: 5, y: 5 },
    { x: 6, y: 4 },
  ];
  
  const kmeans = new KMeans(2, data);
  const clusterLabels = kmeans.run();
  console.log(clusterLabels);
  