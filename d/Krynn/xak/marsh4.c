/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh()
{
    add_exit(TDIR + "marsh8.c", "south", "@@cross", 5);
    add_exit(TDIR + "marsh2.c", "east", "@@cross", 5);
    add_exit(TDIR + "marsh3.c", "north", "@@cross", 5);
    add_exit(TDIR + "marsh7.c", "west", "@@cross", 5);
}
