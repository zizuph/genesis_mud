#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>



public void  create_gondor();
int climb_tree(string str);
public void  reset_room();

static object  Npc;

public void
create_gondor()
{
    set_short("the trail's end");
    set_long("This area marks the end of a trail.  The trees of the " +
      "forest close in, leaving no apparent escape but north.  " +
      "The trail stops suddenly at the base of a large tree, " +
      "for some unknown reason.  " +
      "\n");

    add_item("ground","It is hard and covered with grass.\n");
    add_item("grass","The grass here is green and lush.\n");
    add_item("sky","The sky rises into infinity above you.\n");
    add_item("trail","The trail is simply an area of trampled grass, " +
      "leading up to a tree.\n");
    add_item(({"bird","birds"}),"There are no birds in this area.\n");
    add_item("forest","The forest is thick with trees, surrounding " +
      "you.\n");
    add_item(({"tree","trees"}),"The trees in the area are " +
      "dominated by the large tree at the end of the trail.\n");
    add_item("large tree","This large tree marks the end of the trail.  " +
      "There are scuff marks upon its trunk.\n");
    add_item(({"marks","mark","trunk"}),"The marks on the trunk seem" +
      " to lead up.  They were probably created " +
      "by whatever animal made the trail.  " +
      "\n");

    add_exit(CAMP_ROOM_DIR + "trail2","north");

    add_prop(ROOM_I_INSIDE, 0);
    reset_room();
}

public void
init()
{
    ::init(); // remember this one.
    add_action(climb_tree, "climb");
}

int
climb_tree(string str)
{
    if (!strlen(str))
    {
	notify_fail("Climb what?\n");
	return 0;
    }

    if (str != "tree" && str != "up") 
    {
	notify_fail("Climb what?\n");
	return 0;
    }

    if (TP->resolve_task(TASK_ROUTINE, SS_CLIMB) > 0)
    { 
	write("You skillfully climb up the tree.\n");
	say(TPQN + " climbs up the tree.\n");
	tell_room(CAMP_ROOM_DIR + "tree", TPQN + " arrives climbing up.\n",
	  0,TP);
	TP->move_living("M",CAMP_ROOM_DIR + "tree",1,0);
    }
    else
    {
	write("You try to climb the tree but fail miserably.\n");
	say(TPQN + " tries to climb the tree.\n");
    }
    return 1;
}

public void
reset_room()
{

    if (!objectp(Npc))
    {
	Npc = clone_npc(Npc, (NPC_DIR + "rabbit"));
    }
}
