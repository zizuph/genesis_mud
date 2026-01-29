/*
   Wayreth.

   leaveroom.c
   ------------

   Coded ........: 97/10/24
   By ...........: Karath

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;

#define WOHS_I_WANNA_LEAVE "_wohs_i_wanna_leave"

void
create_tower_room()
{
    set_short("The room of release");
    set_long("This room is otherworldly in appearance. The room is totally "+
	"barren except for a black crackling rift in the center of the "+
	"room. This place is one of great sadness yet has a sense of "+
	"release from torment. It is said that one may forsake magic "+
	"here and end their life. The rift here seems to be the "+
	"key.\n");

    add_item( ({"rift", "black crackling rift", "crackling rift",
		  "black rift" }), "The rift crackles with otherworldly "+
	"power. You may <enter the rift> to leave magic and the guild "+
	"forever.\n");

    set_wall_type(2);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(WTOWER + "stairwell09", "east", 0);
}

void
init()
{
    ::init();
    add_action("leave_guild", "enter");
}

int leave_guild(string str)
{
    notify_fail("Enter what?\n");
    if (str == "the rift" || "rift")
      {
	if( !call_other(ADMINDIR + "admin",
		 "query_wohs_member", TP->query_real_name() ) )
	  {
	    notify_fail("But you aren't even a guildmember!\n");
	    return 0;
	  }
	/* They get a second chance */
	if( !TP->query_prop(WOHS_I_WANNA_LEAVE) )
	  {
	    write("Are you _SURE_ ?? This is absolute, final, and you "+
		"can never return! Type again to verify.\n");
	    TP->add_prop(WOHS_I_WANNA_LEAVE, 1);
	    return 1;
	  }
	write("You step into the rift.\n");
	call_other(ADMINDIR + "admin", "remove_wohs_member", TP, 3);
	return 1;
      }
    return 0;
}
