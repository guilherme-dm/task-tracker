# Task Tracker

A command-line task manager written in C. It stores tasks in a local JSON file and lets you create, update, delete, list, and change the status of tasks.

Source code is theoretically portable to Windows, Linux and MacOS, but currently there's only a release for Windows x86-64.

This is a solution to the [Task Tracker project on roadmap.sh](https://roadmap.sh/projects/task-tracker).

## Features

- Add tasks with a chosen title
- Update task titles
- Mark tasks as `to-do`, `doing`, or `done`
- List every task or filter tasks by status
- Delete tasks
- Persist data locally in `tasks.json`

## Requirements

- A C compiler such as GCC (in case you're not downloading binaries from releases page)
- No package installation is required; [cJSON](https://github.com/DaveGamble/cJSON) is included in the `libs` directory

## Build

Clone the repository and enter its directory:

```bash
git clone https://github.com/guilherme-dm/task-tracker.git
cd task-tracker
```

Compile the application:

```bash
gcc tasktracker.c libs/cJSON.c -o tasktracker
```

On Windows, the generated program is `tasktracker.exe`. On Linux and macOS, run it as `./tasktracker`. The examples below use `tasktracker`; replace it with the appropriate path for your system if the executable is not on your `PATH`.

## Usage

Running the program without a command displays its built-in help:

```bash
tasktracker
```

Task titles containing spaces must be enclosed in quotes.

### Add a task

New tasks start with the `to-do` status.

```bash
tasktracker add "Buy groceries"
```

### Update a task

Pass the task ID followed by its new title:

```bash
tasktracker update 1 "Buy groceries and cook dinner"
```

### Change a task's status

```bash
tasktracker mark-to-do 1
tasktracker mark-doing 1
tasktracker mark-done 1
```

### Delete a task

```bash
tasktracker remove 1
```

### List tasks

List all tasks:

```bash
tasktracker list
```

Filter the list by one of the supported statuses:

```bash
tasktracker list to-do
tasktracker list doing
tasktracker list done
```

## Command reference

| Command | Description |
| --- | --- |
| `tasktracker add "<title>"` | Add a task with the given title |
| `tasktracker update <id> "<title>"` | Replace a task's title |
| `tasktracker remove <id>` | Delete a task |
| `tasktracker mark-to-do <id>` | Set a task's status to `to-do` |
| `tasktracker mark-doing <id>` | Set a task's status to `doing` |
| `tasktracker mark-done <id>` | Set a task's status to `done` |
| `tasktracker list` | List all tasks |
| `tasktracker list <status>` | List tasks with the selected status |

## Data storage

The application creates `tasks.json` in the current working directory when the first task is added. Each task contains an ID, title, status, creation timestamp, and update timestamp.