inherit "/d/Genesis/ship/cabin";
#include "/d/Shire/common/defs.h"

void
create_cabin()
{
  set_short("A dark passage inside the ship");
  set_long("Wooden ribbing, planks, and beams dominate this "+
    "musty passage in the bowels of the ship.  No light penetrates "+
    "this region of the ship from the upper decks, and "+
    "certainly no light penetrates the hull!  The air here "+
    "is damp and musty, smelling of salt, wood, and pitch.\n");
  add_item("pitch","Pitch coats all the wood here, making the "+
    "wood dark and sticky, but also waterproofed.\n");
  add_item("wood","Surely strong, supple pieces of timber, "+
   "all the wood here is soaked in pitch, making it black and "+
   "sticky to the touch.\n");
  add_item(({"beam","beams","plank","planks","planking","ribbing",
  "ribs","rib"}), 
    "Shaped from strong, durable wood soaked in pitch, "+
    "this area of the ship contains the backbone "+
    "of the ship, and is surrounded by the sturdy shell that "+
    "keeps the sea from rushing inwards.\n");
  add_item("hull","The hull is formed of sturdy planks that are "+
    "held together by their tongue and groove construction, pins, "+
    "and pitch.\n");

  add_exit(SHIP_DIR + "cabin", "up",0,3);
  add_exit(SHIP_DIR + "quest/u2", "fore",0,3);
  add_prop(ROOM_I_LIGHT, 0);

}
