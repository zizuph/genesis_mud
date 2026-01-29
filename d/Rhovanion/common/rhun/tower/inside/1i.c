#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";
#include <stdproperties.h>

void create_room()
{
    set_short("Dark passage");
    set_long("You are in a dark passageway in this"
        +" tall, mysterious tower.  There is little light here-- just enough"
        +" for you to see by.  The stones here are of the same dark red"
        +" material-- perhaps a kind of brick-- as the rest of the structure."
        +"  The passage turns here from north to east.\n");

    add_exit(RHUN_DIR+"tower/inside/1j", "north", 0);
    add_exit(RHUN_DIR+"tower/inside/1h", "east", 0);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
