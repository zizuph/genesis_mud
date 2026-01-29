#include "default.h"
inherit PORT_ROOM;

object ob1;
object ob2;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("The Halfling Brewery");
    set_long("This room must be where the halflings make all their beer. "+
      "Filling the area are strange, moving belts of tanned hide. The "+
      "strange whirring, creaking noise from the belts combines with the "+
      "strong smell of beer to leave you thirsty and confused. Along the "+
      "walls are stacked many barrels. Archways lie to the west and east.\n");
    add_item(({"strange moving belts","strange belts","moving belts","belts","belt","tanned hide","hide"}),
      "Tasty, aromatic halfing-made beer is moving swiftly along the moving "+
      "belts. They seem to travel in any random direction, but most however "+
      "lead through the archway and east into another room.\n");
    add_item(({"beer"}),"It looks mighty good.\n");
    add_item(({"walls","wall"}),"The walls of the brewery are made out "+
      "of hardwood planks, durable for many years.\n");
    add_item(({"barrels","barrel"}),"Where the halflings store their "+
      "precious cargo of beer.\n");
    add_item(({"archways","archway"}),"Open entrances that lead out of "+
      "this section of the brewery.\n");
    add_exit(PORT + "s39", "west");
    add_exit(PORT + "s41", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/hbworker");
	ob1 -> move_living("xxx", TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(PORT + "npc/hbworker");
	ob2 -> move_living("xxx", TO);
	ob1 -> team_join(ob2);
    }

}

