/* by Antharanos */
/* Updated by Damaris 06/2003 */

#pragma strict_types
#pragma save_binary
#include "/d/Kalad/defs.h"
inherit "/d/Kalad/room_std";
inherit "/d/Genesis/lib/post";
public void
create_room()
{
    INSIDE;
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("The postal offices of Undraeth");
    set_long("This location is where drow, as well as non-drow may "+
      "communicate with others via mail. Please <examine mail reader>.\n");
    add_exit(CPASS(drow/d11),"north","@@msg",-1,-1);
    add_exit(CPASS(drow/shop/spider_room),"southeast");
 /*
    add_exit(CPASS(drow/shop/spider_room),"southeast","@@check",-1,-1);
 */
}

public void
msg()
{
    write("You head back towards the streets of Undraeth.\n");
    say(QCTNAME(TP) + " heads back towards the streets of Undraeth.\n");
    return 0;
}
/*
 * Function name:   leave_inv
 * Description:     remove mailreader from players exiting the room
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

public void
mail_message(string new)
{
    write("\nThere is"+ new +" mail for you.\n");
}

/*
 * Function name:   init
 * Description:     add a mailreader to players who enter the room
 */
public void
init()
{
    ::init();
    post_init();
}


/*
check()
{
    if (TP->query_guild_name_race() == "Drow race guild" ||
      TP->query_alignment() < 0)
    {
	write("You pass without incident.\n");
	return 0;
    }
    write("You cannot seem to pass!\n");
    say(QCTNAME(TP) + " cannot seem to head southeast.\n");
    return 1;
}
*/
