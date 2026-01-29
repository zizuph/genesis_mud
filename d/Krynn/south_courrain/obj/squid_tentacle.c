/*
 *  Squid leftover, and fantastic bait for fishing!
 *
 *  Arman, March 2021
 */

inherit "/d/Krynn/common/fishing/fishing_bait";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_bait()
{
   set_name("tentacle");
   add_name("segment");
   add_name("_giant_squid_tentacle");
   set_adj("giant");
   add_adj("squid");
   add_adj("sea");
   set_short("giant squid tentacle segment");
   set_long("This is a fleshy piece of giant squid tentacle. " +
       "Raw and very unappealing, this rare meat is renowned by " +
       "anglers as the best bait for fishing in the realms!\n");

    // Food amount in grams. Bait is a food item!
    set_amount(50);

   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VALUE, 200);

    // Bait value helps determine the quality of the fish caught.
    // This is excellent bait!
    set_bait_value(20);
}

/*      
 * Function name: special_effect
 * Description  : Define this routine if you want to do some special effect
 *                if a player consumes this food.
 * Arguments    : int amount - the number of foods consumed.
 */             
public void
special_effect(int amount)
{
    string race_name = this_player()->query_race_name();
    string str1, str2, worms;

    if(amount > 1)
        worms = "squid tentacle segments";
    else
        worms = "squid tentacle segment";

    switch(race_name)
    {
        case "elf":
        case "half-elf":
        case "drow":
        case "human":
            str1 = "You gag as you swallow the fleshy " +
                 worms +".\n";
            str2 = " gags as " +HE(this_player())+ " swallows " +
                 "the fleshy " +worms+ ".\n";
        break;
        case "goblin":
        case "orc":
        case "ogre":
            str1 = "You wolf down the fleshy " +worms+ " with delight.\n";
            str2 = " wolfs down the fleshy " +worms+ " with delight.\n";
        break;
        default:
            str1 = "You slowly chew on the fleshy " +worms+ ".\n";
            str2 = " slowly chews on the fleshy " +worms+ ".\n";
    }

    write(str1);
    say(QCTNAME(this_player()) + str2);
}

