#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

#define THIS_DIR FIRST_DEEP_DIR
/* We must know what the standard directory is. */
#define CONSTRUCT_ROOM CreateMines()
#define RESET_ROOM reset_room()

inherit MINES_FILE;
/* I hate writing this all the time. :-) */
