#!/bin/bash
pgcc -tp sandybridge-64 -acc -ta=nvidia -Minfo=accel BFS.c graph.c
