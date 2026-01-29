/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh() 
{
    add_exit(TDIR + "marsh12.c", "north", "@@cross", 5);
    add_exit(TDIR + "marsh3.c", "east", "@@cross", 5);
}
