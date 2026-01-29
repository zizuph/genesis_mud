/*
 * Board needed for Telseron swing quest
 * By Finwe
 * February 1997
 */
 
#include "/d/Emerald/defs.h"
inherit "/std/object";
 
create_object()
{
    set_name("board");
    set_short("flat board");
    set_adj( ({"long,","firm"}));
    set_long("You examine the board carefully. It is long with " +
        "a couple knot holes at both end. It looks like it was " +
        "dropped when the lumberjacks passed through here.\n");
}
