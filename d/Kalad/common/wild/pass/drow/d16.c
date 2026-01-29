inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/*
 * Removing references to Avenir code.
 * The Drow guild is closed and Avenir
 * code being retired.
 *
 * The books and lexicon in this library
 * have seen no activity in several years
 * so lets just remove it as there is a
 * new Drow guild in Faerun.
 *
 *    -Lucius, June 2017
 */
object ob1;
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("Within the drow city of Undraeth");
    set_long("A veritable kaleidoscope of stalagmites and stalactites "+
      "surround you, filling your field of view. These immense structures of "+
      "rock rise far above the ground, having been magically enhanced by the "+
      "native population into the astounding structures before you now. "+
      "The air around you is warm from the presence of numerous living beings in "+
      "the area. It is also quite stale and stagnant, due to its presence far "+
      "below the fresh air of the surface. "+
//    "Just to the south lies a stalagmite compound. "+
      "The street here bends gently, curving to the west and northeast.\n");
    add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
    add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
#if 0
    add_item(({"stalagmite compound","compound"}),
      "A conglomeration of stalagmites that have been melded into one "+
      "another to form a building of solid stone.\n"+
      "A plaque, glowing from faerie fire, floats before its entrance.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_item(({"faerie fire","fire"}),
      "It glows with an eerie purple light.\n");
    add_item(({"entrance"}),
      "A dark cavity within the compound's darker form.\n");
#endif
    add_exit(CPASS(drow/d11),"west");
    add_exit(CPASS(drow/bazaar/b1),"northeast");
//    add_exit("/d/Avenir/common/undraeth/library/entrance", "south", "@@msg");
    set_noshow_obvious(1);
    set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(CPASS(drow/npc/rand_drow));
	ob1 -> arm_me();
	ob1 -> move_living("M",TO);
	tell_room(TO,"A dark figure emerges from the greater darkness around "+
	  "you.\n");
    }
}
plaque()
{
    return "\n"+
    "In glowing purple letters the following has been written:\n"+
    "The Library of Undraeth.\n"+
    "\n";
}
msg()
{
    write("You head towards the stalagmite compound.\n");
    say(QCTNAME(TP) + " heads towards the stalagmite compound.\n");
    return 0;
}
