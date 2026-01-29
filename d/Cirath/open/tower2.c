inherit"/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/sys/filter_funs.h"
int pres,i;
object *ob;
object ob1;
object ob2;
object rope;

void
create_room()
{
    set_short("Guard Tower");
    set_long("This is the second story of the guard tower. Here guards "
      +"stand looking out the windows at the city below. "
      +"There is a hole in the ceiling leading up, but you aren't sure "
      +"how to get up there.\n");
    add_exit(TRADE(wall/tower3),"up","@@rope_check");
    add_exit(TRADE(wall/tower1),"down");
    add_item(({"window","windows"}),"These windows look out over the "
      +"grand city of Kabal.\n");
    add_item(({"hole"}),"This is a hole in the ceiling that you can't quite reach. "
      +"It seems big enough for you to fit through, and you can see "
      +"open air through it.\n");
    add_item(({"ceiling"}),"It is a plain stone ceiling, that has a "
      +"nice sized hole in it. It probably leads up to the third "
      +"floor.\n");

    hear_bell = 2;
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_NO_TIME_DESC,1);
    set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
    if (!ob1 || !ob2)
    {
	ob1 = clone_object("/d/Kalad/common/caravan/npc/kguard.c");
	ob1 -> arm_me();
	ob1 ->move_living("xxx", this_object());
	ob2 = clone_object("/d/Kalad/common/trade/tguard.c");
	ob2 ->move_living("xxx", this_object());
	ob1->team_join(ob2);
    }
}
rope_check()
{
    object *ob;
    int i;
    if(TP->query_invis())
	return 0;
    ob = deep_inventory(TP);
    for(i = 0; i < sizeof(ob); i++)
	if(ob[i]->id("rope"))
	{
	    write("You toss the rope through the hole, and feel it tighten "+
	      "as it is tied around something.\n");
	    say(QCTNAME(TP) + " tosses a rope through the hole in the ceiling.\n");
	    ob[i]->remove_object();
	    return 0;
	}
    write("It's too high to go up.\n");
    say(QCTNAME(TP) + " tried to go up, but only succeeds in falling "
      +"down.\n");
    return 1;
}
