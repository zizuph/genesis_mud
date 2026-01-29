/*
 *  Khalakhor bait based off the bardee grub by Arman
 *  /d/Krynn/common/fishing/bardee_grub.c
 *
 *  Can be searched for in forests of Eil Galaith.
 *  One option for the angler quest in Cadu.
 *
 *  Treacher, September 2021
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Krynn/common/fishing/fishing_bait";

#define BAIT_VALUE  4
#define BAIT_EXTRA  2

string
long_desc_extra()
{
    if(query_bait_value() == BAIT_VALUE)
    {
        return "They are desired by fishermen as bait, " +
               "especially if you are lucky and skilled to find " +
               "a larger specimen.";
    }
    else
    {
        return "They are desired by fishermen as bait. " +
               "This is a large specimen, improving its lure on the fish.";
    }
}

void 
create_bait()
{
    set_name("maggot");
    add_name("_white_maggot");
    add_adj("white");
    set_short("white maggot");
    set_long("This white maggot is the larvae of a " +
        "common fly domestic to the forests of Khalakhor. " +
        "@@long_desc_extra@@\n" +
        "@@query_bait_quality_description@@");

    add_prop(OBJ_I_VOLUME, 8);
    add_prop(OBJ_I_WEIGHT, 8);
    add_prop(OBJ_I_VALUE, 50);

    // Food amount in grams. Bait is a food item!
    set_amount(8);

    // Bait value helps determine the quality of the fish caught.
    set_bait_value(BAIT_VALUE);	
}

/*
 * Function name: is_big
 * Description: Checks if this item is a big version
 */
 int
 is_big()
 {
     return (query_bait_value() == (BAIT_VALUE + BAIT_EXTRA));
 }

void
make_big()
{
    //Make the maggot fat - little bigger and little better bait
    add_prop(OBJ_I_VOLUME, 12);
    add_prop(OBJ_I_WEIGHT, 12);
    add_prop(OBJ_I_VALUE, 100);
    set_amount(10);
    add_adj("fat");
    set_short("fat white maggot");
    set_bait_value(BAIT_VALUE + BAIT_EXTRA);
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
        worms = "white maggot";
    else
        worms = "white maggots";

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

public void
init_recover(string str)
{
    ::init_recover(str);
    //Check if maggot was big
    if(query_bait_value() > BAIT_VALUE)
    {
        make_big();
    }
}
