#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Highland Gate, intersection of High and Gateway");
    set_long("This is the intersection of the heavily-travelled High "+
      "Street, which divides the Upper Class district from the Caravan "+
      "district, and the equally busy Gateway Lane. From this point High "+
      "Street leads north through the Highland Gate towards the expansive "+
      "estates of the nobles, as well as heading south, deep into the heart "+
      "of Kabal. Gateway Lane travels west-east along the northern city "+
      "walls. Several buildings line the intersection to the southwest while "+
      "in the southeast lies a high stone wall surrounding a massive "+
      "edifice.\n");

    add_item(({ "intersection", "high street", "gateway lane" }),
      "Both roadways are paved in slate-grey cobblestones that despite "+
      "being heavily used are in good condition. The only apparent "+
      "difference between the two streets is the tidier look of High Street, "+
      "while Gateway Lane looks in need of some cleaning.\n");

    add_item(({ "highland gate", "gate" }),
      "Two massive steel doors, nearly as high as the city walls, block the "+
      "gap made in the wall by High Street, which continues north out of "+
      "the city.\n");

    add_item(({ "city walls", "walls" }),
      "Examining the walls closer you note the finely crafted stone from which "+
      "it was made from. Clearly the stone used in its construction came "+
      "from the Hespyre mountains, which lie east of Kabal. The walls themself "+
      "rise to a height of thirty feet, presenting a formidable barrier to "+
      "any invading forces.\n");

    add_item(({ "buildings" }),
      "Comely-looking buildings that are most likely shops for the guards "+
      "and nobles that frequent this area. The buildings all seem to be made "+
      "from the mighty redwoods found on the slopes of the hespyre mountains, "+
      "indicating that these structures were built to last.\n");

    add_item(({ "high stone wall", "stone wall", "wall" }),
      "It stretches to the east and south completely encircling a large "+
      "stone edifice. Since the wall is fifteen feet in height, only the "+
      "very top of the edifice is visible.\n");

    add_item(({ "edifice" }),
      "Little detail can be made out since the majority of the building is "+
      "blocked from view by the stone wall surrounding it. The only thing "+
      "you can see are the extremely dark stones from which the edifice was "+
      "built from.\n");

    add_item(({ "large winch", "winch" }), "A large metal rod used to open "+
      "up the Highland Gate.\n");

    add_exit(NOBLE + "gateway/s11", "west", 0);
    add_exit(CVAN + "gateway/s1", "east");
    add_exit(CVAN + "high/s1", "south");

    clone_object(CVAN + "door/hgdoor")->move(TO);

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "cmilitia_hg");
	ob1->arm_me();
	ob1->move_living("M", TO);
    }
}

int
block()
{
    write("The way is blocked by a barricade.\n");
    return 1;
}

int
crank(string str)
{
    if(!str || str != "winch")
    {
	notify_fail("Crank what? The winch?\n");
	return 0;
    }
    write("You try vainly to crank the winch but lack the knowledge "+
      "to operate the mechanism.\n");
    say(QCTNAME(TP) + " vainly tries to crank the winch but lacks the "+
      "knowledge to do so.\n");
    return 1;
}

void
init()
{
    ::init();
    AA(crank,crank);
}
