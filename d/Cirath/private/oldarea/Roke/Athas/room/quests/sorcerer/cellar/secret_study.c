inherit "/std/room";
#include "/d/Roke/common/defs.h"
 

reset_room()
{

}

create_room()
{
    object door, key;

    set_short("Study");
    set_long(BSS("This is a dark, scary study where Pandora reads her forbidden scrolls. "+
		"You sure dont want to be here when she comes to do so, even "+
		"though you would love to get your hands on those.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 
    add_item(({"%", "%"}), BSS("%\n"));

	door = clone_object(DOOR_D+"iron_door_b");
    door->move(this_object());
    door->set_key(570157);

	clone_object(DOOR_D+"stone_key")->move(this_object());

    call_out("reset_room", 1);
 
}
