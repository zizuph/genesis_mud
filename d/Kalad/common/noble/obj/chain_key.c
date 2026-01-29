inherit "/std/key";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_key()
{
    set_name("key");
    set_adj("dirty");
    add_name("_kalad_free_goblin_quest_");
    set_short("dirty key");
    set_long("A small, steel key. It looks a bit rusted, and has some "+
    "dirt stains on it.\n");
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,8);
}

