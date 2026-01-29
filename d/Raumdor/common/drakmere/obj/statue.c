inherit "/std/object";
#include <stdproperties.h>

/* Sarr */

void
create_object()
{
    set_name("statue");
    set_adj("large");
    add_adj("stone");
    set_short("large stone statue");
    set_long("Upon a large, black stone base stands a tall statue of man, "+
    "dressed in ceremonial armour. The man holds a large "+
    "and powerful-looking claymore in his hands. His grim face "+
    "stares to the south.\n"+
    "There is a plaque on the base.\n");
    add_item("plaque","A beautiful, silver and gold plaque. It has "+
    "readable words on it.\n");
    add_cmd_item(({"plaque","the plaque"}),"read","King Raumdor I.\n"+
    "Hail unto our great King, the Demon Slayer, first to wield the "+
    "Holy Avenger, and first bringer of light to the lands of Death.\n");
    add_prop(OBJ_M_NO_GET,"Are you MAD?\n");
}

