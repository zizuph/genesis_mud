/* created by Aridor 06/21/93 */

inherit "/std/room";

#include "../local.h"


create_room()
{
    set_short("Inside the gates of the Tower");
    set_long(BS("You are standing in a hallway below the High Clerist "
         +   "Tower.",SL));

    INSIDE;
    DARK;

    add_exit(ROOM + "hall2","northwest",0);
    clone_object(OBJ + "steeldoor")->move(TO);

    add_item("hallway",BS("The hallway extends to the northwest into "
         +   "darkness and ends to the southeast at a massive steel "
         +   "door.",SL));
}



