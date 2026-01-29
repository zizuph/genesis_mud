/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh() 
{
    add_exit(TDIR + "marsh4.c", "south", "@@cross", 5);
    add_exit(TDIR + "marsh1.c", "east", "@@cross", 5);
    add_exit(TDIR + "marsh5.c", "north", "@@cross", 5);
    add_exit(TDIR + "marsh6.c", "west", "@@cross", 5);
}
