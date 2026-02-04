
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h";
#include <macros.h>
#include <stdproperties.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

#define PORTRAIT MANSION + "second/portrait"
#define EAST_EXIT  MANSION + "second/gallery_c"

create_room()
{
    object ob;
    
    set_short("Portrait Room");
    set_long(BS("This is the west end of an incredibly long room, " +
		"full of portraits of various people.  However, " +
		"this area contains only the one very large portrait " +
		"that takes over the whole of the west wall.  There is " +
		"a thick, plush burgandy carpet running east, from the " +
		"west wall, into the further reaches of the room.  To " +
		"the southwest, there seems to be a sort of hallway.\n"));

    ob = clone_object(PORTRAIT);
    ob->move(this_object());

    add_item(({"carpet", "plush carpet"}), BS("The thick carpet covers " +
		"most of the carpet except along the north and south walls " +
		"where you can see the highly polished floorboards.\n"));

    add_item(({"boards", "floorboards", "polished floorboards"}),
		"These boards are in very good condition and look " +
		"quite slippery.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(EAST_EXIT, "east", 0);
    add_exit(MANSION + "second/front_stairs", "southwest", 0);
}
