/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh() 
{
    add_exit(TDIR + "marsh3.c", "south", "@@cross", 5);
    add_exit(TDIR + "marsh9.c", "east", "@@cross", 5);
}

