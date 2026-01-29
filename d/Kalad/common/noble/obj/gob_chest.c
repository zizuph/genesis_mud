inherit "/std/receptacle.c";
#include "/d/Kalad/defs.h"
/* SARR */

int trap = 1;

void
create_receptacle()
{
    set_name("chest");
    set_adj("steel");
    add_adj("black");
    set_short("black steel chest");
    add_prop(CONT_I_MAX_WEIGHT,1000);
    add_prop(CONT_I_MAX_VOLUME,1000);
    add_prop(CONT_I_WEIGHT,200);
    add_prop(CONT_I_VOLUME,200);    
    add_prop(CONT_I_CLOSED,1);
    add_prop(CONT_I_LOCK,1);
    set_long("A small chest made of black steel. There is a lock on it "+
    "which is surrounded by small, dull red jewels. It looks kinda "+
    "valuable.\n");
    set_key("free_goblin_quest_kalad");
}
