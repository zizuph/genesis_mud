/*
 *  Khalakhor bait based off the bardee grub by Arman
 *  /d/Krynn/common/fishing/bardee_grub.c
 *
 *  Used in npc/grugg.c
 *  Can be cut off from the grugg during battle, as well as occational leftovers.
 *  One option for the angler quest in Cadu.
 *
 *  Treacher, September 2021
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
 
inherit "/d/Krynn/common/fishing/fishing_bait";

#define BAIT_VALUE  3
#define BAIT_EXTRA  1
 
string
long_desc_extra()
{
    if(query_bait_value() == BAIT_VALUE)
    {
        return "They are used by Cariscan fishermen as bait, " +
            "especially if you are able to get a long limb.";
    }
    else
    {
        return "They are desired by Cariscan fishermen as bait. " +
            "This is a particular long limb, improving its lure on the fish.";
    }
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
     //Make the limb longer - little bigger and little better bait
     add_prop(OBJ_I_VOLUME, 15);
     add_prop(OBJ_I_WEIGHT, 15);
     add_prop(OBJ_I_VALUE, 100);
     set_amount(12);
     add_adj("long");
     set_short("long grugg limb");
     set_bait_value(BAIT_VALUE + BAIT_EXTRA);
 }

void 
create_bait()
{
    set_name("limb");
    add_name("_grugg_limb");
    add_adj("grugg");
    set_short("grugg limb");
    set_long("This is a severed limb from a grugg, twisted and " +
            "grotesque. At some angles it almost looks like glowing. " +
            "@@long_desc_extra@@\n" +
            "@@query_bait_quality_description@@");

    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VALUE, 50);

    // Food amount in grams. Bait is a food item!
    set_amount(10);
 
    // Bait value helps determine the quality of the fish caught.
    // 10% of created limbs will be bigger
    if(random(10) == 0) 
        make_big();
    else
        set_bait_value(BAIT_VALUE);	
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
        worms = "grugg limb";
    else
        worms = "grugg limbs";

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
    //Check if limb was big
    if(query_bait_value() > BAIT_VALUE)
    {
        make_big();
    }
}
