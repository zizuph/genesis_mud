/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh() 
{
    add_exit(TDIR + "marshend.c", "west", "@@cross", 5);
    add_exit(TDIR + "marsh4.c", "east", "@@cross", 5);
}
