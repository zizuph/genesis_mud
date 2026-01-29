inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
    ::create_room();
    add_prop(ROOM_NO_TIME_DESC,1);
    set_short("In the mountains");
    set_long("An abundance of slate-grey rocks surrounds you on all sides, "+
      "making the world seem composed solely of mountainous terrain. "+
      "You are travelling on a rocky path that reaches the base of the "+
      "mountains to the "+
      "northeast and downhill to the southwest, where it wanders through "+
      "yet more of this rugged landscape. To the southeast, lower in "+
      "elevation, is a large plain littered with numerous rocks and "+
      "boulders. The punishing rays of the Kaladian "+
      "sun beat down on you from above, burning your flesh.\n");
    add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
    add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
    add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
    add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
    add_item(({"large plain","plain"}),"A desolate area encompassed by "+
      "the enfolding arms of the mountains.\n");
    add_item(({"numerous rocks","numerous boulders","boulders","boulder"}),
      "You are too far off to see any details from here.\n");
    add_exit(CPASS(desert/mount/m1),"southwest",0,4);
    add_exit(CPASS(desert/rock/p1),"southeast",0,4);
    add_exit(CPASS(desert/mount/m3),"up","@@check_climb",5);
    set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(CPASS(npc/mo_scout));
	ob1 -> my_stuff();
	ob1 -> move_living("M",TO);
	tell_room(TO,"An ogre arrives and rushes directly at you!\n");
    }
    if(!ob2)
    {
	ob2 = clone_object(CPASS(npc/mo_dog));
	ob2 -> move_living("M",TO);
	ob1 -> team_join(ob2);
	tell_room(TO,"A wild dog arrives seemingly from nowhere.\n");
    }
}
check_climb()
{
    if(TP->query_skill(SS_CLIMB) < 30)
    {
	write("You try to climb the steep cliff but slip and fall!\n");
	write("You land with a bonecrushing sound!!!\n");
	say(QCTNAME(TP) + " tries to climb the steep cliff but slips and falls!\n");
	say(QCTNAME(TP) + " lands with a bonecrushing sound!!!\n");
	TP->heal_hp(-500);
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }
    write("You safely climb up the cliff.\n");
    say(QCTNAME(TP) + " safely climbs up the cliff.\n");
    return 0;
}
