/*
 * /d/Gondor/common/dwarf_guild/obj/rugsack.c
 *
 * A rucksack to carry stuff in. It has sell-protection.
 *
 * /Mercade, 24 January 1993
 *
 * Revision history:
 * Olorin, 4-Jan-1997: Modified to use /d/Genesis/std/wearable_pack.c
 * Toby, 26-Mar-2007 : Fixed so it keeps, but now the same bug remains
 *                     but for unkeep. Something with the VBFC is the cause.
 *                     I will leave it at this since it keeps at least.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/std/wearable_pack.c";
inherit "/lib/keep.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define NO_SELL_VBFC "@@no_sell_vbfc@@"

public void
create_wearable_pack()
{
    set_name("rucksack");
    add_name("sack");
    add_name("pack");
    add_name("backpack");
    add_name("knapsack");

    set_pname("sacks");
    add_pname("rucksacks");
    add_pname("packs");
    add_pname("backbacks");
    add_pname("knapsacks");

    add_adj("large");
    add_adj("camouflaged");

    set_short("large camouflaged rucksack");
    set_pshort("rucksacks");
    set_long("The rucksack is rather large and made of a very "
      + "light, yet strong material. Its colours are chosen so that it "
      +	"offers maximum camouflage in many surroundings.\n");

    set_mass_storage(1);
    set_keep(1);

    add_prop(OBJ_M_NO_SELL,  NO_SELL_VBFC);
    add_prop(CONT_I_REDUCE_VOLUME, 150);
    add_prop(CONT_I_REDUCE_WEIGHT, 150);
    add_prop(OBJ_I_VALUE,             288);
    add_prop(CONT_I_WEIGHT,          2000);
    add_prop(CONT_I_VOLUME,          2500);
    add_prop(CONT_I_MAX_WEIGHT,    150000);
    add_prop(CONT_I_MAX_VOLUME,    150000);
    remove_prop(CONT_I_RIGID);
}

/*
 * Function name: no_sell_vbfc
 * Description  : This function is the VBFC that is called when the keep
 *                protection is not active. We use it to test whether the
 *                wallet contains any money and if so, stop the rucksack
 *                from being sold.
 * Returns      : mixed - a string with a fail message if the rucksack may
 *                        not be sold (i.e. it is not empty).
 *                      - 0 if the rucksack may be sold.
 */
mixed
no_sell_vbfc()
{
    if (sizeof(all_inventory(TO)))
    {
        return ("The " + short() + " is not empty at the moment. Please " +
            "empty it before you sell it, to prevent loss of property.\n");
    }

    // Original is: return 0;
    //return (TO->query_prop_setting(OBJ_M_NO_SELL));
    return 0;
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg);
}


