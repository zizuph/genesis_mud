/* 	this is a room of the town Gelan

    coder(s):   Merlin & Maniac

    history:  
             26/7/95    Revision of old file            Maniac

    purpose:    room for guards guarding the entrance
    exits:      ne to armoury, north and ne to palace road, weat to gate

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      changing of guards at the appropriate times
    bug:        none known
*/

#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>

inherit GELAN_BASE_ROOM;

public void
create_gelan_room()
{
    /* descriptions */

    set_short("Standby guards");
    set_long("You find yourself in a small corner of the palace road. To the "
          + "south and east a stout wall reaches up far into the sky. To the "
          + "north you can see the palace road leading to the town square "
          + "with the statue. To the west you see the gate of Gelan. "
          + "Northeast you notice an entrance to one of the armouries "
          + "of Gelan.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);	/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "palace_road_se","north",0);
    add_exit(GELAN_ROOMS + "gate","west",0);
    add_exit(GELAN_ROOMS + "palace_road_sw","northwest",0);
    add_exit(GELAN_ROOMS + "guards_armoury_se","northeast","@@gse_block");

    /* items in the room */

    add_item(({"road","floor","ground"}), BS("The road consists of white "
          + "marble. It is shining white, but despite its look, its not "
          + "slippery at all. The road is very well kept here, not the "
          + "faintest sign of litter.\n"));
    add_item("gate", BS("The gate, as you see it from here, consists of a "
          + "long tunnel with huge columns on either side, all built out of "
          + "sandstone. You can't see the top of the tunnel though it "
          + "could be open to the sky as well.\n"));
    add_item("square", BS("This square is really big. To see more you have "
          + "to go closer.\n"));
    add_item(({"town","gelan","Gelan"}),BS("Well, your here, just look "
          + "around to see it. Isn't it great ?\n"));
    add_item("statue", BS("It's a huge statue of a woman and a dragon. You "
          + "can't see more from this distance.\n"));
    add_item("sky",BS("Well, your not sure if you can see it or not. "
          + "Perhaps the gate make some sort of roof here.\n"));
    add_item(({"armoury","armouries"}),BS("The guards armoury is a cube shaped house made "
          + "of sandstone. In order to do their duty and fight the ever "
          + "lurking evil the guardians renounced to have a door. The "
          + "building has quite a lot of windows so the guardians can "
          + "control the surroundings. Whenever there's trouble in town "
          + "you can be sure there's someone to handle it.\n"));
    add_item("entrance", BS("There is no door in the entrance, just a big "
          + "hole. On the wall left to the entrance is a sign.\n"));
    add_item("sign",BS("The sign is written in big golden letters.\n")
                     + "            GUARDS ENTRANCE, NO ENTRY\n"
                  + BS("Below the letters is the golden sign of Gelan.\n"));
    add_item(({"wall","walls"}),BS("The walls are shining in a bright "
          + "white. You wonder if there exists some sort of white lava rock.\n"));
    add_item(({"column","columns"}), BS("The columns are round and apparently about two "
          + "miles high (hobbit perspective ...). They are made, or at "
          + "least the part you can see, is made out of sandstone.\n"));


} /* create_room */


int
gse_block()
{
  write("The southeast guards armoury is currently off limits.\n"); 
  return 1;
}
