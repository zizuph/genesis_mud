
#include "../local.h";

inherit SWIM_ROOM;

#include RND_MEET

object *npc = ({0,0,0,0,0});

void
create_swim_room()
{
    set_long("@@my_long");
    add_exit(ROOM + "lake2","southeast",0);
    add_exit(ROOM + "lake4","northwest",0);    
    add_item("mountains",
	     "The mountains on the other side of the lake look majestic and " +
	     "inspiring. You sigh deeply, hoping beyond hope to LIVE to " +
	     "visit them some day.\n");
    add_item("wilderness",
	     "Just kidding about the wilderness soothing your soul. This " +
	     "place gives you the creeps. It's dark and nasty. The woods " +
	     "to the east of you seem to have eyes, and you walk along the " +
	     "path with your guard up.\n");
    set_alarm(1.0,0.0,"reset_room");
}

void
reset_solace_room()
{
    if (npc && sizeof(npc) > 0 && !npc[0])
      set_alarm(1.0,0.0,"load_drac",0);
    if (npc && sizeof(npc) > 1 && !npc[1])
      set_alarm(2.0,0.0,"load_drac",1);
    if (npc && sizeof(npc) > 2 && !npc[2])
      set_alarm(3.0,0.0,"load_drac",2);
    if (npc && sizeof(npc) > 3 && !npc[3])
      set_alarm(9.0,0.0,"load_drac",3);
    if (npc && sizeof(npc) > 4 && !npc[4])
      set_alarm(10.0,0.0,"load_drac",4);
}

void
load_drac(int i)
{
  npc[i] = RANDOM_MEET(LAKETABLE);
  if (!npc[i])
    return;
  if (npc[i]->query_prop(OBJ_I_COLORABLE))
    npc[i]->set_color("red");
  npc[i]->set_aggressive(1);
  npc[i]->move_living("xxx", TO);
}

my_long()
{
    if (npc && sizeof(npc - ({0})))
      return ("You obviously aren't the kind of person to listen to his " +
	      "gut feelings. A number of warriors from the red dragon " +
	      "army jump out of the trees at you! Perhaps next time your " +
	      "conscience tries to tell you something, you'll listen. " +
	      "That is, if there is a next time.\n");
    else
      return ("It looks like there has been a great battle here. After " +
	      "looking around, you count yourself lucky, because you " +
	      "realize that there was an ambush set up here, and the only " +
	      "thing that saved your skin was another poor adventurer who " +
	      "stumbled through here before you.\n");
 }
