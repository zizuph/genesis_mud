/* Circle road */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();
    hear_bell = 3;
    set_short("Circle road");
    set_long("You walk along the circle road, a road paved with large "+
      "bricks of stone. There are not many buildings around you except "+
      "the backside of one on the eastern side. You notice some pigeons "+
      "flying up from it. It must be a post-office there. To your "+
      "surprise you see a run-down ramshackle hut situated on the western "+
      "side of the road. The circle "+
      "streets continue northwards and to the southeast.\n");

    add_item(({"pigeon","pigeons"}),"They look like...pigeons. Except "+
      "that you notice a small cylinder attached to one of their legs.\n");

    add_item(({"brick","bricks"}),"Most of the bricks are hole, but some "+
      "are craced up, leaving smaller pieces that you might be able to "+
      "pry loose.\n");

    add_item(({"hut","ramshackle hut"}),"The hut is built of "+
      "cracked planks probably found floating in the ocean. You "+
      "wonder if it will stand through bad weather. Doubtful...\n");

    add_exit(CENTRAL(circle/beggar_hut),"in",0,1);
    add_exit(CENTRAL(circle/s11),"north",0,1);
    add_exit(CENTRAL(circle/s9),"southeast",0,1);
}
void
init()
{
    ::init();
    add_action("pry_loose","pry");
}


int
pry_loose(string str)
{
    notify_fail("Pry what loose?\n");

    if (!str)
	return 0;
    if (str != "stones" && str!= "stone")
	return 0;
    write ("You try to pry one of the stones loose, but its too stuck.\n");
    say(QCTNAME(TP)+" tried to pry one of the stones loose, but failed.\n");
    return 1;
}

