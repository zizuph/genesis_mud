/*
 *  An example bait based off earthworm by Greneth
 *  /w/greneth/fishing/bait/earthworm.c
 *
 *  Can be searched for on the Mithas Isles forest areas.
 *
 *  Arman, March 2021
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/common/fishing/fishing_bait";

void 
create_bait()
{
    set_name("grub");
    add_adj("bardee");
    set_short("bardee grub");
    set_long("This large fleshy grub is the larvae of the " +
        "Rain Moths common to the forests of the Bloodsea " +
        "Isles and the Goodlund Peninsula. It is a great " +
        "favourite of fisherman, and makes a very effective " +
        "saltwater and freshwater bait.\n" +
        "@@query_bait_quality_description");

    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VALUE, 50);

    // Food amount in grams. Bait is a food item!
    set_amount(10);

    // Bait value helps determine the quality of the fish caught.
    set_bait_value(6);	
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
        worms = "bardee grubs";
    else
        worms = "bardee grub";

    switch(race_name)
    {
        case "elf":
        case "half-elf":
        case "drow":
        case "human":
            str1 = "You gag slightly as you swallow the fleshy " +
                 worms +".\n";
            str2 = " gags slightly as " +HE(this_player())+ " swallows " +
                 "the fleshy " +worms+ ".\n";
        break;
        case "goblin":
        case "orc":
        case "ogre":
            str1 = "You wolf down the fleshy " +worms+ " with delight.\n";
            str2 = " wolfs down the fleshy " +worms+ " with delight.\n";
        break;
        default:
            str1 = "You munch thoughtfully on the fleshy " +worms+ ".\n";
            str2 = " munches thoughtfully on a fleshy " +worms+ ".\n";
    }

    write(str1);
    say(QCTNAME(this_player()) + str2);
}

