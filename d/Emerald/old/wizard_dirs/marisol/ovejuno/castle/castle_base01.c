/* Castle_base_room
  * To be used as a base for the castle first floor in Ovejuno, Emerald.
  * Contain general information
  * Coded by Marisol (09/03/98)
  * Copyright (c) Marisol Ramos 1998
  */

#pragma strict_types;

inherit "/d/Emerald/std/room";
#include "/d/Emerald/sys/macros.h"
#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>


void
create_castle_room()
{
}

nomask void
create_emerald_room()
{

    set_short("The Lord's residence first floor.");

    add_item(({"residence", "castle"}),
        "The inside of the castle is a radical contrast to the "+
        "outside, like night from day. The rooms here are clean "+
        "and sumptuous. The white walls are covered with artful "+
        "paintings and tapestries. Compare with the unkept outside, "+
        "the inside of this residence is extremely beautiful.\n");

    add_item("walls",
        "The white walls gleam prettily with the firelight of the "+
        "the torches that light the rooms. Wondeful hanging "+
        "tapestries decorate the walls together with beautiful "+
        "paintings.\n");

    add_item(({"hanging tapestries", "tapestries", "paintings"}),
        "The hanging tapestries depict elves nobleman and "+
        "elfmaidens dancing and playing together in the glorious "+
        "city of Telbarin. Some paintings are of serious-looking "+
        "male elves, possible previous lords that lived here. "+
        "Others are outwordly beautiful elven ladies, maybe the "+
        "wifes of the lords?\n");

    add_item(({"torches", "torch-lights"}),
        "The torches are set in iron holders. Maybe they are magical "+
        "elven torch-lights. They are too tall to taken away from "+
        "their place.\n");

    

    reset_room();
    create_castle_room();


}                                 
