/* 2017-09-03 Malus: Creating replacement for rot/foul effect */ 
#include "defs.h"
inherit "/std/food";

void
create_food()
{
    set_name(({"_raumdor_corrupt_food", "lump"}));
    set_adj(({"rotten"}));
    set_short("lump of rotten food");
    set_pshort("lumps of rotten food");
    add_prop(OBJ_I_VALUE, 0);
}

public mixed
command_eat()
{
    return "That is rotten an inedible.\n";
}
