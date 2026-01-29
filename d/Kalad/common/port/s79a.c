#include "default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Shipwright's Office");
    set_long("This is the residence and office of Bassil Korahf, the "+
      "head shipwright of the Port District. The interior of the building "+
      "is furnished with many sea-related items. Most prominent among these "+
      "is the miniature model of a great sea-going galleon which hangs "+
      "from the ceiling rafters. A small window lies in the north wall. "+
      "The walls of this structure are covered with large shelves, upon "+
      "which many of the sea-related items are placed. "+
      "A small round table and wooden stool lie aside a tidy bed in one corner of "+
      "the room. In another section is a small iron stove and iron lamp.\n");
    add_item(({"items","item"}),"Among the objects lying on the shelves "+
      "are jars filled with tar, rolled-up parchments of paper, measuring "+
      "devices, wooden pegs and iron nails.\n");
    add_item(({"jars","jar","tar"}),"A dark black substance used in the "+
      "manufacture and upkeep of sea vessels.\n");
    add_item(({"parchments","parchment","paper"}),"They look like design "+
      "plans for new ships.\n");
    add_item(({"measuring devices","devices","device"}),"A numerous "+
      "variety of instruments useful to shipwrights, far too numerous to "+
      "adequately describe.n");
    add_item(({"wooden pegs","pegs","peg"}),"Small pieces of hardwood "+
      "that have been whittled down into thumb-sized fragments.\n");
    add_item(({"iron nails","nails","nail"}),"Newly forged nails, used "+
      "in the construction of many wooden objects, such as ships.\n");
    add_item(({"large shelves","shelves","shelf"}),"A great number of "+
      "them are all over the walls, holding many different items.\n");
    add_item(({"miniature model","model","great sea-going vessel","great vessel","sea-going vessel","vessel"}),
      "A magnificent galleon of outdated design. The words enscribed on "+
      "its hull are: 'The Seahawk'.\n");
    add_item(({"rafters","rafter"}),"Stout wooden beams that hold up "+
      "the ceiling.\n");
    add_item(({"ceiling"}),"Made out of hardwood and reinforced with "+
      "rafters, it looks quite sturdy.\n");
    add_item(({"small window","window"}),"Peering outside, you can see "+
      "the beautiful bay of Kabal.\n");
    add_item(({"beautiful bay of kabal","beautiful bay","bay of kabal","bay"}),
      "It sparkles with a clear blue light in the sun.\n");
    add_item(({"small round table","small table","round table","table"}),
      "An ordinary wooden table, it is as clean as a whistle.\n");
    add_item(({"walls","wall"}),"The hardwood walls look quite capable of "+
      "weathering the worst of sea storms.\n");
    add_item(({"wooden stool","stool"}),"A short, uncomfortable-looking "+
      "stool. It looks to have been made to specifically be uncomfortable.\n");
    add_item(({"tidy bed","bed"}),"A small, plain bed that completely "+
      "lacks any sheets or pillows.\n");
    add_item(({"iron stove","stove"}),"An ancient-looking device, used "+
      "for cooking and heating.\n");
    add_item(({"iron lamp","lamp"}),"The rusty old lamp looks to be "+
      "broken.\n");
    add_exit(PORT + "s79", "out");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/shipwright");
	ob1 -> move_living("xxx",TO);
    }

}

