#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("An empty wooden building");
    set_long("You're inside a good-sized wooden building that is now "+
      "totally vacant. Dust and cobwebs fill the room, while the walls and floor "+
      "have several holes in them.\n"+
      "A sign hangs before you.\n");

    add_item(({"dust"}),
      "It is thick and grey and covers everything, including the cobwebs.\n");
    add_item(({"cobwebs", "cobweb"}),
      "It lies scattered in the various corners of the room.\n");
    add_item(({"corners", "corner"}),
      "The corners are filled with cobwebs and dust.\n");
    add_item(({"walls", "floor"}),
      "Plain wooden walls with several small holes in them.\n");
    add_item(({"ceiling"}),
      "It has been built out of pine wood.\n");
    add_item(({"small holes", "holes", "hole"}),
      "Small fist-sized holes that appear to be the homes of rats.\n");
    add_item("sign", "@@sign");

    add_cmd_item("sign", "read", "@@sign");

    add_exit(CVAN + "wayfar/s2", "south");
}

string
sign()
{
    return "We have moved to the Central District aside the plaza square\n";
}
