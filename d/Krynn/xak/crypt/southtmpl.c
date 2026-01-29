/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

object door;
int doorhere;
int door_alarm;

create_xak_room()
{
        set_short("The South Temple");
        set_long(BS(
           "You are in the secret south temple of the dead. The room rises"
	 + " to a 20 foot high flat ceiling. The walls contain various"
	 + " carvings.", 70));

	add_exit(CDIR + "deadtmpl.c", "north", 0);
	add_item(({"carvings", "carving", "walls", "wall"}), "@@carving");

	INSIDE
        DARK
}

carving()
{
	write(BS("The walls are covered in detailed carvings depicting scenes"
	 + " of wars and death. Looking at them makes you feel somewhat morbid.", 70));
	return "";
}

init()
{
	::init();
	ADA("search");
}


search(string str)
{
	if (str != "here" && str != "west wall")
		return 0;
	if (door)
		return 0;
	get_door();
	return 1;
}


get_door2()
{
	if (door)
		door->remove_object();
	if (door_alarm)
	    remove_alarm(door_alarm);
	door_alarm = set_alarm(20.0,0.0,"remove_door");

	door = clone_object(OBJ + "bupudoorb.c");
        door->move(TO);
	door->set_key(K_TEMPLE);
	tell_room(TO, "A secret door opens in the west wall!\n");
}	

remove_door2()
{
	door->remove_object();
	if (door_alarm)
	  remove_alarm(door_alarm);
	door_alarm = 0;
}

get_door()
{
	get_door2();
	call_other(CDIR + "southcrypt4.c", "get_door2");
}

remove_door()
{
	remove_door2();
	tell_room(TO, "The secret door slams shut and becomes unnoticable again.\n");
	call_other(CDIR + "southcrypt4.c", "remove_door2");
}

