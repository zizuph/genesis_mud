inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/caravan/thanar/default.h"
#include <stdproperties.h>
#define BOARD_DIR "/d/Kalad/common/guilds/thanar/log/ooc/board_data"

public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())

    {
	/* Is a member, pass through as normal */

	return 0;
    }

    write("A magical force prevents you from entering.\nYou are not a "+
      "Thanarian!\n");
    return 1;
}

public void
create_room()
{ 
    object bb;
    
    ::create_room();

    INSIDE;
   
    set_short("A shrine dedicated to the glory of Thanar");
    set_long("A shrine dedicated to the glory of Thanar, patron god of "+
      "all humanity. Here you may bask in the glorious power that is "+
      "Thanar's to wield, simply type 'start here' and you shall forever "+
      "after begin your journeys from this place of quiet solitude.\n");
    add_prop(ROOM_M_NO_ATTACK,"You would not dare to incur the wrath of "+
      "Thanar by such a foolish act!\n");
    add_exit("/d/Kalad/common/guilds/thanar/joinroom","south");
    
    setuid();
    seteuid(getuid());
    bb = clone_object("/std/board");
    bb->set_board_name(BOARD_DIR);
    bb->set_num_notes(30);
    bb->set_silent(0);
    bb->set_show_lvl(1);
    bb->move(this_object(), 1);
}
void
init()
{
    ::init();

    add_action("start","start");
}
int start(string s)
{
    if(s =="here" && (IS_MEMBER(TP)))
    {
	TP->set_default_start_location("/d/Kalad/common/caravan/thanar/shrine");
	write("From now on you shall start here, within the shrine to Thanar.\n");
	return 1;
    }

    write("Either you can't type or you are not a member. Please try again.\n");
    return 1;
}
