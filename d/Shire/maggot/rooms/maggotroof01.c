
/* 
	*A yard, just outside farmer Maggot's house
	*Altrus, 
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit BASE_YARD;
inherit AREA_ROOM;

public void
create_area_room()
{
	areadesc = "rooftop";
	area = "of a house";
	areaname = "in the Marish";
	land = "the East Farthing";
	areatype = 0;
	extraline = "At first glance the roof does not appear that sturdy, " +
	"but once you apply your full weight, it becomes apparent that " +
	"the roof will hold you. There is a chimney just to the west of " +
	"here.";
	
	add_item(({"roof"}), "Yes, you are sure the roof will hold your " +
	"weight. You can see the board you climbed just below your feet.\n");
	add_item(({"board"}), "It looks like the only way back to the ground " +
	"besides jumping down is to use the board again.\n");
	add_item(({"chimney"}), "It is a mud brick chimney. There is " +
	"smoke billowing out.\n");
	add_item(({"smoke"}), "The smoke pours slowly out of the " +
	"chimney and gently floats away.\n");
	
	set_no_herbs();
	
	set_add_rtells_yard();
		
	add_exit(ROOM_DIR + "maggotroof02", "west");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

void init()
{
	::init();
	 add_action("climb_board", "climb");
	add_action("jump_down", "jump");
}

int climb_board(string str)
{
	if (this_player()->query_prop(LIVE_O_STEED))
        {
            write("You must dismount your steed before climbing the tree.\n");
            return 1;
        }

        if(str == "board")
        {
		this_player()->catch_msg("You put your foot on the board and " +
		"scamper off the roof.\n");
		say(QCTNAME(this_player()) + " puts " + HIS_HER(this_player()) + " foot " +
		"on a loose board on the wall of the house and scampers down off the roof.\n");
		this_player()->move_living("M", ROOM_DIR + "maggotyard06", 1);
		tell_room(ENV(this_player()), QCTNAME(this_player()) + " arrives from above.\n",this_player());
		return 1;
        }
        else 
        {
            write("Climb what?\n");
            return 1;
        }
    
}

int jump_down(string str)
{
	if (this_player()->query_prop(LIVE_O_STEED))
        {
            write("You must dismount your steed before climbing the tree.\n");
            return 1;
        }

        if(str == "down")
        {
		this_player()->catch_msg("You take your life into your own hands " +
		"and prepare to jump off the roof. At the last second you stumble and fall " +
		"to the ground below!\n");
		say(QCTNAME(this_player()) + " starts running for the edge of the roof, but " +
		"trips and falls to the ground!\n");
		this_player()->move_living("M", ROOM_DIR + "maggotyard06", 1);
		tell_room(ENV(this_player()), QCTNAME(this_player()) + " falls unceremoniously " +
		"from above, lands in a head on the ground, then stands up, smiling sheepishly.\n",this_player());
		return 1;
        }
        else 
        {
            write("Jump where?\n");
            return 1;
        }
    
}