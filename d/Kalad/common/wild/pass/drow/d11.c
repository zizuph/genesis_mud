inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/*
 * Removing references to Avenir code.
 * The Drow guild is closed and Avenir
 * code being retired.
 *
 *	- Lucius, June 2017
 */
object ob1;
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("Within the drow city of Undraeth");
    set_long("Huge structures of rock known as stalagmites and "+
      "stalactites rise far above you, having been magically enchanted by "+
      "the resident populace into the graceful structures before you now. "+
      "The warmth of the air here is comforting, though it is stagnant and "+
      "stale-smelling. "+
      "Stalagmite compounds lie just to the north and south, off the street. "+
      "The street before you knifes its way to the west and east.\n");
    add_item(({"gigantic structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
    add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
    add_item(({"stalagmite compounds","compounds"}),
      "Which one? The northern or southern one?\n");
    add_item(({"northern stalagmite compound","northern compound"}),
      "A mass of stalagmites magically fused to form a building.\n"+
      "A plaque hangs before it.\n");
    add_item(({"southern stalagmite compound","southern compound"}),
      "A series of low stalagmite mounds that have been magically fused so "+
      "as to form a structure.\n"+
      "A sign hangs before it.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_item("sign","@@sign");
    add_cmd_item("sign","read","@@sign");
    add_exit(CPASS(drow/d5),"west");
    add_exit(CPASS(drow/d16),"east");
    add_exit(CPASS(drow/shop/guard_post), "north", "@@msg");
    add_exit(CPASS(drow/shop/post),"south","@@msg2",-1,-1);
    set_noshow_obvious(1);
    set_alarm(1.0,0.0,"reset_room");
}
msg()
{
    write("You depart for the stalagmite compound in the south.\n");
    say(QCTNAME(TP)+" departs for the stalagmite compounds in the "+
      "south.\n");
    return 0;
}
msg2()
{
    write("You depart for the stalagmite compound in the south.\n");
    say(QCTNAME(TP) + " departs for the stalagmite compound in the south.\n");
    return 0;
}
plaque()
{
    return "\n"+
    "It reads:Maps & Information\n";
}
sign()
{
    return "\n"+
    "It reads:Post Office\n";
}
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(CPASS(drow/npc/b_w_spider));
	ob1 -> move_living("M",TO);
	tell_room(TO,"A large arachnid arrives before you.\n");
    }
}
