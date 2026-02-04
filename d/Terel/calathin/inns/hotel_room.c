/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * hotel_room.c
 *
 * A generic hotel room.  The other hotel rooms should inherit this one.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Prototypes
 */

public string sign_info();

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_start", "start", 0);
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Lodging room");
    set_long("It is a quite spartan lodging room. There is not much here " +
	     "except a bed. There is a sign on the wall.\n");
    add_item("bed", "The bed looks very soft.\n");
    add_item("sign", "@@sign_info");
    add_cmd_item("sign", "read", "@@sign_info");
    INSIDE;
}

/*
 * Function name: sign_info
 * Description:   returns what is written on the sign
 * Returns:       see above
 */
public string
sign_info()
{
    return "The sign reads:\n" + 
	"Type 'start here' and you will make this room your " +
	    "temporary starting location next time you login.\n";
}

/*
 * Function name: do_start
 * Description:   Handle the start action.  If successful, set a temporary
 *                start location for the player.
 * Returns:       1/0
 */
public int
do_start(string str)
{
    object key;
    int st;

    NF("Start where?\n");
    if (str != "here")
	return 0;
    
    key = present("_cal_room_key", TP);
    if(!key || (key->query_prop("_cal_room_renter") != TP->query_real_name())) {
	NF("Where is your key?\n");
	return 0;
    }
    st = TP->set_temp_start_location(file_name(TO));
    
    if (!st) {
	NF("You are unable to start here for some reason.\n");
	return 0;
    }
    
    write("You will now start here next time you wake up.\n");
    key->remove_prop("_cal_room_renter");
    return 1;
}
