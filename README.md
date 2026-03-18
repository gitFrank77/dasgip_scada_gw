# DASGIP SCADA Gateway

A C-based gateway that bridges DASGIP bioreactor vessel data with a SQL database, supporting up to 8 vessels access to and from SCADA.


## How It Works
Dasware PC (VBA writes state files) → Dasware PC (.bat shares files) → Pi (C/MariaDB syncs state into DB) → SCADA (reads states, pushes control tags back to DB) → Pi (C reads control table, writes action files) → Dasware PC (.bat shares back) → Dasware PC (VBA reads actions)


## Architecture
![PCDasware Architecture](docs/PCDasware_architecture.png)


| File / Folder | Description |
|---|---|
| `supervisor.c` | Main process — manages vessel threads |
| `dasgip_utils/` | DASGIP communication utilities |
| `mysql_utils/` | Database read/write utilities |
| `includes/` | Shared headers |



## Build

```bash
make
```

## Changelog

| Date | Notes |
|---|---|
| 2026-02-09 | Initial version — `main_loop_2.c` reads state files, writes to DB; `vessel_control.c` reads DB and writes commands to vessels |
| 2026-02-18 | `supervisor_v1.c` introduced as new main function |
| 2026-02-24 | `supervisor_v1.c` cleaned and tested; `supervisor_v2.c` created as single-thread reference implementation |
| 2026-02-24 | `supervisor_v3.c` started — multi-vessel/multi-thread support via pthreads |
