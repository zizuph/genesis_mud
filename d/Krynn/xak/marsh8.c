/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh() 
{
    add_exit(TDIR + "marsh11.c", "east", "@@cross", 5);
    add_exit(TDIR + "marsh4.c", "north", "@@cross", 5);
}
