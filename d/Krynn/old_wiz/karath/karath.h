/*
 * /d/Krynn/karath/karath.h
 *
 * This file contains your personal definitions to be used in exec.
 * Check out <exec.h> before adding definitions to this file.
 */

#define TRANS(x,y) a = clone_object(x); a->move(find_player(y), 1);
