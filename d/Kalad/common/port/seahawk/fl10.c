#include "../default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    set_short("Captain's Cabin");
    set_long("You are within the captain's cabin of the Seahawk. This "+
      "richly attired room seems more fitting for a prince than for a "+
      "captain. The floor is blanketed by a magnificent ruby-red carpet "+
      "that pleases the eye. The wooden walls have also been painted a "+
      "red color, though darker, like burgundy. A large painting "+
      "dominates the room's ceiling. Across the room is a large redwood "+
      "desk aside a comfortable bed. A lamp set into each corner of the "+
      "room provides a steady illumination.\n");
    add_item(({"floor"}),"The floor cannot be seen because of the "+
      "carpet that covers it.\n");
    add_item(({"magnificent ruby-red carpet","magnificent carpet","ruby-red carpet","carpet"}),
      "Excellently woven, it is littered with symbols of dark suns, "+
      "lending it an air of unmistakable danger.\n");
    add_item(({"wooden walls","walls","wall"}),"The sides of the cabin "+
      "have all been painted a deep red color, reminding you of the inside "+
      "of a butchery.\n");
    add_item(({"large painting","painting","ceiling"}),"Craning your "+
      "neck backwords you gaze upon an image of an entire fleet of "+
      "galleons making war upon a city, brutally slaying anything that so "+
      "much as moves. Examing it further, you make out individual sailors "+
      "as they viciously impale and slash women and their infant children "+
      "and gut the men as if they were pigs. You note that the flags beared "+
      "by the ships is that of a dark sun upon a blood red field.\n");
    add_item(({"large redwood desk","redwood desk","large desk","desk"}),
      "A finely crafted desk of antique design. It is in an amazingly good "+
      "condition, with little to no scratches marring its polished "+
      "surface. A few papers lie scattered on top of it.\n");
    add_item(({"papers"}),"You can't look at all of them at once!\n");
    add_item(({"paper"}),"Nearly all of the papers have been written "+
      "in some secret code, appearing as garbish to your untrained eyes. "+
      "Only one paper is readable.\n");
    add_cmd_item("paper","read","@@paper");
    add_item(({"comfortable bed","bed"}),"The wooden bed only looks "+
      "capable of holding one person, though comfortably.\n");
    add_item(({"lamp"}),"Iron lamps that are currently lit and providing "+
      "a bright yellow light.\n");
    add_item(({"corner"}),"It is free of dust and cobwebs.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl9", "north");

    reset_room();
}

paper()
{
    return "The paper mentions several things...\n"+
    "...destroy those filthy subhuman scum...\n"+
    "...the port open to the outside world we must...\n"+
    "...surely Shadowgloom will help us...\n"+
    "...Master Knight will lead...\n"+
    "...invade Atuan, it will be a simple...\n"+
    "...will personally lead the Order against the...\n"+
    "...miserable traitor will rot in the prison cells for...\n";
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/captain");
	ob1 -> move_living("xxx",TO);
    }
}

