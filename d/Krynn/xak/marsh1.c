/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh() 
{
    add_exit(TDIR + "marsh2.c", "south", "@@cross", 5);
    add_exit(TDIR + "marsh3.c", "west", "@@cross", 5);
    add_exit(TDIR + "obelisk.c", "east", "@@cross", 5);
}
