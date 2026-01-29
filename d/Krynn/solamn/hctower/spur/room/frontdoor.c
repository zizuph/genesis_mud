/* created by Aridor 06/21/93 (for H. C. Tower)
 * modified by Grace 05/31/94 (for Knight Spur)
 *   Knight Spur Front Door   */

#include "../local.h"

inherit SPURRM;

create_spur_room()
{
    set_short("Inside the gates of the Knight Spur");
    set_long("You are standing in a wide hallway inside the "
      +   "walls of the Knights' Spur. It is very dim in here. "
      +   "A faint light can be seen in the northwest end of "
      +   "the tunnel.\n");

    add_prop("_room_i_allow_steed", 1);

    add_exit(ROOM + "east_gap","northwest",0); 
    clone_object(SOBJ + "steeldoor")->move(TO);  

    add_item("hallway", "The hallway extends to the northwest into "
      +   "a patch of light and ends to the southeast at a massive "
      +   "steel door.\n");
}

