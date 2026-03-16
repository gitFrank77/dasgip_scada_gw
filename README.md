# DASGIP SCADA Gateway

A C-based gateway that bridges DASGIP bioreactor vessel data with a MySQL database, supporting up to 8 vessels via multithreading.

## Architecture

| File / Folder | Description |
|---|---|
| `supervisor.c` | Main process — manages vessel threads |
| `vessel_control` | Reads DB and writes commands to vessels |
| `dasgip_utils/` | DASGIP communication utilities |
| `mysql_utils/` | Database read/write utilities |
| `includes/` | Shared headers |

## How It Works

1. Each vessel has a state file (`vessel_#_state.txt`) updated by the DASGIP system
2. The supervisor reads state files and writes data to the MySQL database
3. `vessel_control` reads the DB and sends commands back to vessels

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
