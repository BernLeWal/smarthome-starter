# Grafana

- Grafana is a powerful **open-source** platform designed for **monitoring, visualization, and analytics of time-series data**. 
- Its primary goal is to provide users with a **visually rich and interactive interface** to **explore, query, and visualize large datasets** from **multiple sources**. 
- Grafana is widely used to create informative and customizable **dashboards**, enabling **real-time monitoring** and **alerting** for a variety of systems, applications, and infrastructure components.

## Features

* **Panels**: fast and flexible visualizations  
  Overview of all panels: https://grafana.com/grafana/plugins/panel-plugins/?pg=graf&plcmt=panels-txt
  - Timeseries
  - Gauge
  - Bar Chart
  - Clock
* **Plugins**: Data source plugins hook into existing data sources via APIs and render the data in real time  
  Plugin Browser: https://grafana.com/grafana/plugins/?pg=graf&plcmt=plugins
  - Data Sources: PostgreSQL, Elasticsearch (also OpenSearch), MQTT, CSV, JSON, JSON-Web API,..
  - Apps: Amazon AWS,...
* **Alerts**: generate alert-rules on your metrics and logs; create/manage and take action on your alerts  
  Overview of Grafana alerting: https://grafana.com/products/cloud/alerting/?pg=graf&plcmt=alerts
* **Transformations** to rename, summarize, combine, and perform calculations across different queries and data sources
* **Annotations**: annotate graphs with rich events from different data sources. Hover over events shows you the full event metadata and tags.

## Links

- Official Grafana Site: https://grafana.com/grafana/
- Grafana Docker Image Guide: https://grafana.com/docs/grafana/latest/setup-grafana/installation/docker/

## HOWTO

1. Docker-Compose file
define the Grafana service along with any other required services, such as a data source (e.g., CrateDB, which is accessable using PostgreSQL DataSource)

```docker
version: '3'
services:
  grafana:
    image: grafana/grafana:latest
    ports:
      - "3000:3000"
    volumes:
      - grafana-storage:/var/lib/grafana
    environment:
      - GF_SECURITY_ADMIN_PASSWORD=yourpassword

  crate-db:
    image: crate:latest
    ports:
      - "4200:4200"
      - "4300:4300"
    volumes:
      - cratedb-data:/var/lib/crate

volumes:
  grafana-storage:
  cratedb-data:
```

2. Configuring Data Sources in Grafana

* After deploying Grafana using Docker-Compose, access the Grafana UI at http://localhost:3000.

* Log in using the default credentials (admin/admin) and configure a data source (e.g., PostgreSQL) by navigating to Configuration -> Data Sources in the Grafana UI.

3. Add a new PostgreSQL data source for CrateDB:

- Name: CrateDB
- Host: crate-db:5432 (Important: Do not put localhost)
- Database: doc
- User: crate
- Password: leave it empty
- SSL mode: disable

Use the following SQL-query as a sample for a Gauge:
```sql
SELECT temperature, time_index, humidity FROM etsensorreading WHERE entity_id = 'A0:DD:6C:10:8A:4C' ORDER BY time_index DESC LIMIT 1
```
Remarks: Replace the entity_id with the MAC-Address of your own sensor.

4. Panels for the Dashboard

* Add Visualisation
* Enter your Query
* Select Panel-Type
* Define Panel Properties


