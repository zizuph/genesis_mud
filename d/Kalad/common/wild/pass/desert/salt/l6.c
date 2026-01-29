inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    set_short("Stinking chamber");
    set_long("The myriad echoes of dripping water reaches your ears, "+
      "giving this stinking chamber an odd quality of infiniteness. Jet black "+
      "darkness surrounds you, or perhaps the walls themselves are just "+
      "colored midnight. In sharp contrast to the darkness, are the "+
      "bleach white bones of innumerable creatures, lying about on the "+
      "floor. However, that still doesn't explain the horrible stench that "+
      "pervades this area.\n");
    add_item(({"stinking chamber","chamber","area"}),"A large cavity "+
      "within the rock, filled with darkness and death...\n");
    add_item(({"jet black darkness","black darkness","darkness"}),
      "It can only be described as a void within the earth, for it is so "+
      "utterly lacking in the slightest of lightness.\n");
    add_item(({"walls","wall"}),"It is hard to distinguish from the "+
      "darkness, perhaps they are one and the same.\n");
    add_item(({"ceiling"}),"You cannot see the ceiling, for darkness "+
      "is the only thing there.\n");
    add_item(({"floor"}),"Barely visible is the rock and bone strewn "+
      "floor of this cave, itself a reflection of darkness.\n");
    add_item(({"bleach white bones","white bones","bones","bone","creatures","creature"}),
      "The skeletal remains of some animals, and yes, even humans that "+
      "have died here. Oddly enough, the bones themselves are as clean "+
      "as the silk kerchief of a nobleman, despite the filthy surroundings.\n");
    add_item(({"rocks","rock"}),"The stones appear to be the remnants "+
      "of large stalagmites, but for some odd reason, have been reduced "+
      "from jagged spikes into rounded mounds of rock.\n");
    add_exit(CPASS(desert/salt/l5),"up","@@pain",2,2);
    clone_object("/d/Kalad/common/wild/pass/obj/ldoor1")->move(TO);
    set_alarm(10.0,0.0,"reset_room");
    set_alarm(10.0,120.0,"stinky");
}
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object("/d/Kalad/common/wild/pass/npc/giant_blob");
	ob1 -> move_living("M",TO);
	tell_room(TO,"A blubbering sound emanates from the darkness.\n");
    }
}
pain()
{
    if(TP->query_skill(SS_CLIMB) < 25)
    {
	write("You try to climb up...\n");
	write("But instead you fall back down with a bonecrushing sound!!!\n");
	say(QCTNAME(TP) + " tried to climb up but fell down with a "+
	  "bonecrushing sound!!!\n");
	TP->heal_hp(-250);
	return 1;
    }
    write("You manage to climb up.\n");
    say(QCTNAME(TP) + " managed to climb up and out of this pit.\n");
    return 0;
}
stinky()
{
    tell_room(TO,"A horrible stench reaches your nostrils.\n");
    return 1;
}
