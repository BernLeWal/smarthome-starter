# CrateDB

- CrateDB is a **distributed SQL database** system designed for handling **large volumes** of machine data and **real-time analytics**. 
- It combines the familiarity and simplicity of SQL with the scalability and flexibility of NoSQL.

## Features

- **Distributed Architecture**: CrateDB is built on a **shared-nothing architecture**, ensuring horizontal scalability and fault tolerance. This allows it to handle large datasets by distributing the load across multiple nodes.
- **SQL Interface**: Despite being *designed for handling unstructured data*, CrateDB supports a full SQL interface, making it accessible to those familiar with traditional relational databases.
- **Real-Time Performance**: With its *in-memory columnar indexes* and *distributed query execution*, CrateDB delivers high-speed data ingestion and query performance, even for complex analytical queries.
- **Dynamic Schema**: CrateDB supports dynamic schema changes, allowing for the addition of new fields without downtime, which is crucial for agile development and evolving data models.
- **Integration with Machine Learning**: CrateDB can integrate with machine learning tools and libraries, providing built-in functions for data transformation and statistical analysis.
- **Full-Text Search**: Built on top of Apache Lucene, CrateDB offers powerful full-text search capabilities, making it suitable for applications requiring text indexing and search functionality.
- **High Availability and Fault Tolerance**: Automated data replication and sharding ensure high availability and fault tolerance, with self-healing mechanisms to recover from node failures seamlessly.

## Links

- Official Site of CrateDB: https://cratedb.com/
- GitHub Repo: https://github.com/crate/crate, https://github.com/crate
- Official Docker Hub Image: https://hub.docker.com/_/crate

## HOWTO

1. Deploy and run CrateDB, e.g. as Docker container
```docker
  crate-db:
    image: crate:latest
    ports:
      - "4200:4200"
      - "4300:4300"
```

2. Install Python Client
```shell
pip install crate
```
Remarks: In this project (SHS) CrateDB is integrated with QuantumLeap and Grafana queries that database directly, so no Python Script was used here.

3. Connect to CrateDB:
```python
from crate import client
connection = client.connect("http://localhost:4200")
cursor = connection.cursor()
```

4. Execute SQL Queries:
```python
cursor.execute("CREATE TABLE sensor_data (id INT, temperature FLOAT, timestamp TIMESTAMP)")
cursor.execute("INSERT INTO sensor_data (id, temperature, timestamp) VALUES (1, 23.5, '2024-05-23T12:34:56')")
cursor.execute("SELECT * FROM sensor_data")
results = cursor.fetchall()
print(results)
```

5. Optional: Handling schema changes (as needed, without downtime):
```python
cursor.execute("ALTER TABLE sensor_data ADD COLUMN humidity FLOAT")
```

## CrateDB vs. PostgreSQL

The choice between CrateDB and PostgreSQL  depends on the specific requirements and future plans of the application:

* **CrateDB**: is well-suited for scenarios where real-time data processing, scalability, and flexibility in handling evolving data models are critical. It is particularly beneficial if the application is expected to grow or require advanced search and analytical capabilities.

* **PostgreSQL**: is ideal for applications prioritizing stability, rich SQL features, and strong transactional integrity, especially in small-scale deployments where the overhead of a distributed system may not be justified.
