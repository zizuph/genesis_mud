/*
 *  /d/Gondor/morgul/city/forge/leather.c
 *
 *  Custom leather to be used for the Morgul forge.
 *
 *  Created by Eowul, 11-12-2004
 */

inherit "/d/Shire/smiths/obj/sm_leath";

#include <stdproperties.h>

/*
 * Function name: create_object
 * Description  : Construct this custom leather.
 */
void create_heap()
{
    string race, *races;

    ::create_heap();

    // Determine the race of the parchment
    races = ({ "dwarven", "elven", "hobbit" });
    race = races[random(sizeof(races))];

    // Add the new names and description based on the race selected
    add_name("skin");
    add_pname("skins");
    add_adj(race);
    set_short(race + " skin");
    set_pshort(race + " skins");

    set_long("This piece of " + race + " skin is useful for wrapping the " +
        "hilts of weapons and in the making of armours.\n");

    add_prop(HEAP_S_UNIQUE_ID, "_smith_leather_" + race);
}
