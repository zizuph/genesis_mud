/* created by Aridor 06/21/93 */

inherit "/std/room";

#include "../local.h"


create_room()
{
    set_short("Hallway under the fortress.");
    set_long(BS("You are standing in a hallway below the High Clerist "
         +   "Tower.",SL));

    INSIDE;
    LIGHT;

    add_exit(ROOM + "hall2","southeast",0);
    clone_object(OBJ + "portcullis")->move(TO);

    add_item("hallway",BS("The hallway is just plain stonework, leading "
         +   "into darkness to the southeast.",SL));
}



