inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <macros.h>
#include <ss_types.h>
int eye_taken_flag;
 
reset_room()
{
 
 
}
 
create_room()
{
	object door;

    set_short("Shrine");
    set_long(BSS("You are in a large room with lots of broken benches spread around "+
              "everywhere and there is also a broken statuette lying on the floor here. "+
	      " \n"));

    add_prop(ROOM_I_INSIDE, 1);


    add_item(({"figure", "statuette"}), BSS("The statuet has been crushed by some creature going mad, you just cannot "+
			      "find any reason for it. The statuette is missing both eyes.\n"));
    add_item(({"benches", "bench"}), "The benches are all broken, maybe someone has gone mad in here.\n");

    call_out("reset_room", 1);


	door = clone_object(DOOR_D+"wood_door_b");
    door->move(this_object());

    call_out("reset_room", 1);

    add_prop(OBJ_S_SEARCH_FUN, "search_it");
}

string
search_it(object player, string what)
{
    if (what != "bench" && what != "benches")
	return 0;
	if (eye_taken_flag)
	return "You find nothing of interest.\n";
    if (player->query_skill(SS_AWARENESS)>25);
	clone_object(A_OBJ_D+"eye")->move(this_object());
	eye_taken_flag = 1;
	return "Your search reveals an citrine eye!\n";
}
