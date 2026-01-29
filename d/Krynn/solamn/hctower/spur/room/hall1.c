/* created by Aridor 06/21/93 */
// modified by Grace
// hall1.c

#include "../local.h"

inherit SPURRM;

create_spur_room()
{
    set_short("Hallway under the fortress");
    set_long("You are standing in a hallway below the Knights' Spur.\n");

    add_exit(ROOM + "hall2","southeast",0);
    clone_object(SOBJ + "portcullis")->move(TO);

    add_prop("_room_i_allow_steed", 1);

    add_item("hallway",BS("The hallway is just plain stonework, leading "
	+   "into darkness to the southeast.",SL));
}
