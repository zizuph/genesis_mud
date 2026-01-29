#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_deck()
{
    set_short("aboard the large ship");

    set_long("The deck of the river boat is narrow. Near the bow, the deck " +
        "gives way to a large open cargo hold. The sails on the masts " +
        "are up and billow in the wind. The oars are  used to navigate " +
        "rivers and close quarters. A set of stairs leads down a hatch " +
        "to the captain's cabin.");
    add_item(({"mast", "masts"}),
        "There are three masts that support three great sails. The masts " +
        "are made of strong wood. The great mast rises above the other " +
        "two. You see people high up in the masts, climbing about.");
    add_item("people",
        "These people climb about in the rigging, tying ropes and securing " +
        "the sails. They look quite busy.\n");
    add_item(({"sail", "sails", "foresail", "main sail", "mainsail", 
            "fore sail", "rear sail", "aft sail", "mid sail", "white sail", 
            "white sails"}), 
        "The sails are made out of thick white canvas. They are fin-shaped " +
        "and billow in the wind. Each sail is shaped like a huge pyramid, "+
        "billowing out towards the front of the ship with even the "+
        "slightest breeze.");

    add_item("deck",
        "The deck, built of the same timber as the "+
        "rest of the ship, is spotlessly clean. Probably it is kept "+ 
        "in such good condition by newbie passengers who are forced "+
        "to work for their passage by swabbing the deck.\n");

    add_item("hull",
        "The hull possesses the same blend of timbers "+
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
    
    add_item("crew","The vast majority of the crew spends its time "+
        "bustling about the ship, taking care of all the duties that "+
        "are required to ensure smooth sailing. Only the captain and "+
        "helmsman spend any appreciable amount of time on deck, instead "+
        "of in the rigging or up a mast.\n");


    add_item("ship",
        "The ship is light and sleek and full of sails. It has three " +
        "masts which are full of sails. The ship is made of strong wood, " +
        "and looks able to outrun almost any ship it comes acrossed.\n");

    add_item(({"crews quarters", "cabin", "passenger cabin", 
            "passenger's cabin","quarters","crews' cabin"}),
        "A solid door blocks the view into the cabin.\n");

    add_item("rigging",
        "Consisting of all the various ropes and chains needed for " +
        "positioning and controlling the sails and masts of the ship, " +
        "the rigging also creates a serviceble pathway for those hands " +
        "that are capable enough to move around above deck.\n");

    add_item(({"mast", "masts", "foremast", "main mast", "midmast", "aft mast",
            "rear mast", "forward mast", "fore mast"}),
        "All three masts have brilliantly white sails that billow "+
        "out fully with the slightest breeze. Crew members swarm about "+
        "the masts and rigging, making many fine adjustments to ensure "+
        "maximum efficency from the sails. The masts, polished by years of " +
        "handling by countless sailors, glisten from the sea spray, making " +
        "the sailors' antics seem praiseworthy, since they never seem to " +
        "fall or even slip.\n");

    add_item("platform",
        "The most significant feature is the ship's wheel "+
        "that controls the direction of the ship. A closer inspection "+
        "is required to observe things in greater detail.\n");
   add_item(({"platform","small platform","little bitty platform"}),
        "The most significant "+
        "feature is the ship's wheel that controls the direction "+
        "of the ship. A closer inspection is required to observe "+
        "things in greater detail.\n");

  add_exit(SHIP_DIR + "har_cabin", "down", 0);
  add_exit(SHIP_DIR + "har_crewroom","fore",0);


}


int move_up()
{
  WRITE("You climb up to the platform, dodging the clumsy first mate "+
    "and a falling bucket of wash water.\n");
  return 0;
}