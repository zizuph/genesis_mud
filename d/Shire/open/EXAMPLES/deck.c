inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_deck()
{
  set_short("On the deck of the elegant ship");
  set_long("This ship, built of strong and supple timber, has "+
    "sleek, almost elegant lines to it as it seemingly flows like "+
    "water from its swan-head prow to its winged stern. The timber "+
    "forms alternately light and dark lines, with subtle shading "+
    "between them, forming an almost hypnotic pattern. The ship sports "+
    "three masts: a foremast; the main mast which is set just forward "+
    "of being midship; and a third set into the aft part of the ship, "+
    "just behind the doorway leading into the passenger's cabin. "+
    "Also to the fore of the ship is a dark doorway leading into "+
    "the forecastle, where the crews quarters are located. Above the "+
    "cabin in the rear of the ship is a small platform where "+
    "the helmsman usually stands, controlling the crew "+
    "and the movements of the ship.\n");

  add_item(({"door","doors","doorway","doorways"}),
    "The door looks like it is crafted of the same blend of woods "+
    "that composes the rest of the ship.\n");
  add_item("deck","The deck, built of the same timber as the "+
    "rest of the ship, is spotlessly clean. Probably it is kept "+ 
    "in such good condition by newbie passengers who are forced "+
    "to work for their passage by swabbing the deck.\n");

  add_item("hull","The hull possesses the same blend of timbers "+
    "apparent in the rest of the ship. Near the prow, the hull forms "+
    "a sharp, nearly straight V shaped point, then it gently "+
    "slopes towards the stern of the ship, gaining a bulge in the "+
    "center like many a retired warrior before squaring up, "+
    "aside from the wings, in the stern, presenting a flat "+
    "backside to the world, much like the previously mentioned "+
     "warriors.\n");
  add_item(({"wood","woods","timber","timbers"}),
    "All wooden components of the ship seem to be formed of at least "+
    "one of three types of woods: lebethron, cedar, or pine. While "+
    "the masts are carved from a single tree, most of the ship "+
    "was crafted from strips of differing timber joined together. The "+
    "strips are joined so well that the ship seems to have been "+
    "carved from a single, huge piece of many shaded-wood, "+
    "and the shades blend from light to dark and back to "+
    "light, producing an almost hypnotic effect when combined with "+
    "the swaying of the ship.\n");
  add_item(({"stern","winged stern","wings"}),
    "The wings sweep outward slightly from the ship, giving the "+
    "illusion of a gliding swan to the entire ship. The wings "+
    "also serve to expand the width of the stern at the deck level "+
    "by a few feet on each side, as they angle farther outwards "+
    "as they travel up the hull.\n");

  add_item("crew","The vast majority of the crew spends its time "+
    "bustling about the ship, taking care of all the duties that "+
    "are required to ensure smooth sailing. Only the captain and "+
    "helmsman spend any appreciable amount of time on deck, instead "+
    "of in the rigging or up a mast.\n");

  add_item(({"swan-head prow","prow","swan-head","swan head",
  "swan head prow"}),
    "Shaped much like a swan's head, from the narrow, black bill, "+
    "to the beady black eyes and long, powerful neck, this figure "+
    "head amply serves to personify the majesty of the ship.\n");

  add_item("ship","The ship, shaped much like a graceful, elegant "+
    "swan, easily cuts through water with a speed and ease that "+
    "makes any seasoned mariner, or warrior, envious.\n");

  add_item(({"crews quarters","cabin","passenger cabin",
  "passenger's cabin","quarters","crews' cabin"}),
    "A solid door blocks the view into the cabin.\n");

  add_item("rigging","Consisting of all the various ropes and chains "+
    "needed for positioning and controlling the sails and masts of "+
    "the ship, the rigging also creates a serviceble pathway for "+
    "those hands that are capable enough to move around above deck.\n");

  add_item(({"mast","masts","foremast","main mast","midmast","aft mast",
  "rear mast","forward mast","fore mast"}),
    "All three masts sport brilliantly white sails that billow "+
    "out fully with the slightest breeze. Crew members swarm about "+
    "the masts and rigging, making many fine adjustments to ensure "+
    "maximum efficency from the sails. "+
    "The masts, polished by years of handling by hordes of sailors, "+
    "glisten wetly from the sea spray, making the sailors' antics "+
    "seem praiseworthy, since they never seem to fall or even slip.\n");

  add_item(({"sail","sails","foresail","main sail","mainsail","fore sail",
  "rear sail","aft sail","mid sail","white sail","white sails"}),
    "The sails all carry the same design, that of feathers embroidered "+
    "onto the material. Each sail is shaped like a huge pyramid, "+
    "billowing out towards the front of the ship with even the "+
    "slightest breeze.\n");

  add_item("platform","The most significant feature is the ship's wheel "+
    "that controls the direction of the ship. A closer inspection "+
    "is required to observe things in greater detail.\n");
   add_item(({"platform","small platform","little bitty platform"}),"The most significant "+
   "feature is the ship's wheel that controls the direction "+
   "of the ship. A closer inspection is required to observe "+
   "things in greater detail.\n");

  add_exit(SHIP_DIR + "cabin", "down", 0);
  add_exit(SHIP_DIR + "crewroom","fore",0);
  add_exit(SHIP_DIR + "platform","up","@@move_up",4);

}


int move_up()
{
  WRITE("You climb up to the platform, dodging the clumsy first mate "+
    "and a falling bucket of wash water.\n");
  return 0;
}
