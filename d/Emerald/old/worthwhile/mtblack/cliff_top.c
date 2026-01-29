inherit "/std/room";

#include "/d/Emerald/defs.h";
#include <tasks.h>

#define FALLEN_ROOM MBLACK_DIR + "pass/mb21"
#define DOWN_ROOM MBLACK_DIR + "pass/mcliff7"

void fall_down(object target);

void
create_room()
{
	set_short("Top of the cliffs");
	set_long("   You are standing at the edge of a steep cliff that "+
		"drops for several hundred feet. Below you can see a "+
		"narrow pass that crosses over the mountains. Looking "+
		"north you can see smoke billowing out of the volcano. "+
		"from here you can go south to the summit of the "+
		"mountain, or you can attempt to climb down the side "+
		"of the cliff.\n\n");

	add_item(({"cliff", "cliffs", "edge"}), "You look down over the "+
		"the edge to see the cliff dissapear into the mists "+
		"below.\n");
	add_item(({"pass", "narrow pass"}), "Far below you can see the "+
		"thin line of the pass winding its way over the "+
		"mountains.\n");
	add_item(({"mountians"}), "The mountains are all below you from "+
		"here on the summit. They strech out west and east out "+
		"of sight.\n");
	add_item(({"volacno", "smoke"}), "Smoke billows out of the cone "+
		"of the volcano giving evidence of its activity.\n");
	add_item(({"summit"}), "The mist is very think in that direction. "+
		"You think you can make out a flat clearing.\n");

	add_exit(MBLACK_DIR + "top", "south");

}
void
init()
{
    ::init();
    add_action("climb_cliff", "climb");
}

int
climb_cliff(string str)
{

    if ( (member_array(str, ({"down", "cliff"})))==-1)
    {
	notify_fail("Climb what?\n");
	return 0;
    }
    
    if ( (str=="down") || (str=="cliff") ) 
    {
	if (this_player()->resolve_task(TASK_ROUTINE, ({SS_CLIMB,SS_DEX}))>0) 
	{
	    write("You manage to climb down the cliff ...\n\n");
	    this_player()->move_living("down the cliff",DOWN_ROOM,0,0);
	    return 1;
	}
	else 
	{
	    fall_down(this_player());
	    return 1;
	}
    }
} 

void
fall_down(object target)
{
    target->catch_msg("You struggle against the side of the cliff "+
		      "but lose your hold ....\n\nYou slip and fall!!\n\n");
    target->heal_hp( -(target->query_hp()/2) ); // take away 50% of hits! heh
        
    tell_room(FALLEN_ROOM, QCTNAME(target)+" comes crashing down the "+
	      "side of the cliff!!\n");
    
    target->move_living("falling down the cliff", FALLEN_ROOM, 0, 0);
}
