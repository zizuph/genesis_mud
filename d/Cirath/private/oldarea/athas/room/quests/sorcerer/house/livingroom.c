inherit "/std/room";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
 
create_room() {
	object door, key;
	set_noshow_obvious(1);

    set_short("Livingroom");
	set_long(BSS("As you enter this livingroom, you find it strange to be "+
		"in such a private part of the templar's house, without even being "+
		"invited in. There is also a large fireplace here, but it is "+
		"currently not in use.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(HOUS_D+"library","east",0);
	add_exit(HOUS_D+"stair1","up",0);
	add_exit(HOUS_D+"sittroom","north",0);
	add_exit(HOUS_D+"fireplace", "enter", "@@enter_check");
 

	add_item(({"hole","hole"}), "The hole looks like a small keyhole.\n");

	add_item(({"stairs"}), BSS(
		"These stairs are made of stone. In fact, you would guess "+
		"that the whole stairway was made out of one stone block.\n"));
	add_item(({"fireplace","fireplace"}),BSS(
		"The fireplace is large, almost so large that you could enter "+
		"it, but still not that large. It seems to have been used"+
		" recently, and you dont find that difficult to believe when "+
		"you think of the cold desert nights. There is a small "+
		"hole on one side of the fireplace that looks pretty "+
		"strange indeed.\n"));

	door = clone_object(DOOR_D+"secr_door_a");
    door->move(this_object());

	key = clone_object(DOOR_D+"secret_key");
    door->set_key(123321);

    call_out("reset_room", 1);
}
 
enter_check(){

     string str;
     str = query_dircmd();
	if (str == "fireplace")
	 return 0;
	write("Enter what did you say?\n");
     return 1;
 }
