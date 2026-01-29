/*
 * /d/Gondor/common/room.c
 *
 * A plain /std/room/c with time functions added
 *
 * Random, 6 Februari 1993
 *
 * Revision history:
 * /Mercade, 27 April 1994 time include altered.
 * Elessar, March 5th 1996. add_invis_exit(), 
 * exits_description(), remove_exit() and query_invis_exit() added,
 * copied from /d/Krynn/std/room.c  - OBSOLETE
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Updated after introduction of non-obvious 
 *                      arg to add_exit() in the mudlib.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include <language.h>
#include "/d/Gondor/common/lib/time.h"

