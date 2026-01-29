inherit "/std/key";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_key()
{
    set_name("key");
    set_adj("black");
    add_name("_kalad_free_goblin_door_");
    set_short("black key");
    set_long("It is a small key made of darkened metal.\n");
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,8);
}

