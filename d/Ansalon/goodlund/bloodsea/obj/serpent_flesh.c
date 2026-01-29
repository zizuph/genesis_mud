/*
 *  Serpent leftover, and good bait for fishing!
 *
 *  Arman, May 2021
 */

inherit "/d/Krynn/common/fishing/fishing_bait";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_bait()
{
   set_name("flesh");
   set_pname("flesh");
   add_name("_luminous_serpent_flesh");
   set_adj("luminous");
   add_adj("serpent");
   set_short("luminous serpent flesh");
   set_pshort("pieces of luminous serpent flesh");
   set_long("This is a piece of luminous flesh cut from the corpse " +
       "of a great sea serpent. It is reputed to be greatly " +
       "sought after by anglers, where the glow of the flesh " +
       "is effective at attracting the bigger fish!\n");

    // Food amount in grams. Bait is a food item!
    set_amount(50);

   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VALUE, 144);

    // Bait value helps determine the quality of the fish caught.
    // This is good bait!
    set_bait_value(14);
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
        worms = "luminous serpent flesh";
    else
        worms = "luminous serpent flesh";

    switch(race_name)
    {
        case "elf":
        case "half-elf":
        case "drow":
        case "human":
            str1 = "You gag as you swallow the " +
                 worms +".\n";
            str2 = " gags as " +HE(this_player())+ " swallows " +
                 "the " +worms+ ".\n";
        break;
        case "goblin":
        case "orc":
        case "ogre":
            str1 = "You wolf down the " +worms+ " with delight.\n";
            str2 = " wolfs down the " +worms+ " with delight.\n";
        break;
        default:
            str1 = "You slowly chew on the " +worms+ ".\n";
            str2 = " slowly chews on the " +worms+ ".\n";
    }

    write(str1);
    say(QCTNAME(this_player()) + str2);
}

