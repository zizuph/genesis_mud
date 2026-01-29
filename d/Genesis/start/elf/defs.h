/*
 * Generic elf inherit file.
 */

/*
 * Standard defines for paths, etc.
 */


#include <macros.h>
#include <stdproperties.h>

#define STAND_DIR     "/d/Genesis/start/elf/"
#define ROOM          "std/room"

#define TP this_player()
#define TR this_room()
#define TO this_object()
#define SAY(str) say(({METNAME + str,TART_NONMETNAME + str}))

