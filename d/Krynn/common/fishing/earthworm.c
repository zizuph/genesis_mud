/*
 *  An example bait based off earthworm by Greneth
 *  /w/greneth/fishing/bait/earthworm.c
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
    set_name("earthworm");
    add_name("worm");
    set_short("earthworm");
    set_long("A slimy and wriggling earthworm that could be " +
        "used for fishing bait.\n@@query_bait_quality_description");

    add_prop(OBJ_I_VOLUME, 4);
    add_prop(OBJ_I_WEIGHT, 4);
    add_prop(OBJ_I_VALUE, 0);

    // Food amount in grams. Bait is a food item!
    set_amount(4);

    // Bait value helps determine the quality of the fish caught.
    set_bait_value(1);	
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
        worms = "earthworms";
    else
        worms = "earthworm";

    switch(race_name)
    {
        case "elf":
        case "half-elf":
        case "drow":
        case "human":
            str1 = "You gag slightly as you swallow the slimy " +
                 worms +".\n";
            str2 = " gags slightly as " +HE(this_player())+ " swallows " +
                 "the slimy " +worms+ ".\n";
        break;
        case "goblin":
        case "orc":
        case "ogre":
            str1 = "You wolf down the slimy " +worms+ " with delight.\n";
            str2 = " wolfs down the slimy " +worms+ " with delight.\n";
        break;
        default:
            str1 = "You munch thoughtfully on the slimy " +worms+ ".\n";
            str2 = " munches thoughtfully on a slimy " +worms+ ".\n";
    }

    write(str1);
    say(QCTNAME(this_player()) + str2);
}

