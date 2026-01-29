/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

object door;
int door_alarm = 0;

create_xak_room()
{
    set_short("The South Crypt");
    set_long(BS(
		"You are at the end of the south corridor of the crypt beneath"
		+ " the temple of Mishakal. There are no coffins along the walls"
		+ " here but there is an exit to a small room to the north and"
		+ " to the south you can hear more activity.", 70));

    add_exit(CDIR + "southcrypt3.c", "west", 0);
    add_exit(CDIR + "middlecrypt2.c", "north", 0);
    add_exit(CDIR + "lifttop.c", "south", 0);

    INSIDE
      DARK
}



init()
{
    ::init();
    ADA("listen");
    ADA("search");
}

search(string str)
{
    if (str != "here" && str != "east wall" && strlen(str)!= 0)
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

    door = clone_object(OBJ + "bupudoora.c");
    door->move(TO);
    door->set_key(K_TEMPLE);
    tell_room(TO, "A secret door opens in the east wall!\n");
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
    call_other(CDIR + "southtmpl.c", "get_door2");
}

remove_door()
{
    remove_door2();
    call_other(CDIR + "southtmpl.c", "remove_door2");
    tell_room(TO, "The secret door slams shut and becomes unnoticable again.\n");
}



listen(string str)
{
    write("You hear what sounds like many creatures to the south.\n");
    return 1;
}
