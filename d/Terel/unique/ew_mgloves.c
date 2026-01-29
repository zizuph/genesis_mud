
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_gloves.c
 *
 * Mergula's gloves.
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 *
 * Updated to correct the adding and removing of the extra SS_DEX.
 * Updated to make the description a little more interesting.
 * Lilith, Jun 05
 *
 * Changes made by Petros, May 2009
 * - Made it so that the armour's abilities can be used by all
 *   alignments, not just evils
 * - Fixed recovery so disenchant is applied correctly
 * - Fixed the messages sent when wearing and removing
 */

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;
inherit "/lib/keep";

#define MAX_TIMES     10

public int      no_times;
public int      pdex;

public void
create_terel_armour()
{
    set_name(({"gloves", "pair of gloves"}));
    set_pname("pairs of gloves");
    set_short("pair of black gloves with silver cuffs");
    set_pshort("pairs of black gloves with silver cuffs");
    set_long("A pair of gloves made from supple black leather. "+
       "The cuffs are embroidered in an intricate sword-"+
       "and-shield pattern picked out in silver thread.\n");
    set_adj(({"black", "leather", "embroidered", "silvery"}));
    add_item(({"embroidery", "silver embroidery", "intricate "+
        "embroidery", "pattern"}), 
        "The embroidery repeats an intricate "+
        "sword-and-shield pattern, picked out in thread "+
        "spun from silver.\n");
    add_item(({"uff", "cuffs"}), "The cuffs on these leather "+
        "gloves are heavily embroidered with silver thread.\n");

    set_default_armour(29, A_HANDS, 0, 0);
    set_af(this_object());
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({40, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"This is Mergula's pair of magical gloves. If worn they " +
	  "will increase your dexterity in combat.\n", 30,
	  "However, their magical strength will " +
	  "diminish everytime you remove them.\n", 60}));
    add_prop(OBJ_I_VALUE, 578);
}

public int
disenchant_object(object disenchanter)
{
    /* Disenchant the item */

    /* Reset magical properties */
    remove_prop(OBJ_I_IS_MAGIC_ARMOUR);
    remove_prop(MAGIC_AM_MAGIC);
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The gloves once possessed some magical power, but it is " +
        "now gone.\n", 50 }));

    /* It isn't worth as much without the magic */
    add_prop(OBJ_I_VALUE, 100); 

    /* No reason to restrict purchase of the item anymore */
    remove_prop(OBJ_M_NO_BUY);

    // When disenchanter is 0, it was called from init_recover
    if (objectp(disenchanter))
    {
        /* Give a message indicating that it was disenchanted */
        tell_room(environment(this_object()), "The black gloves "+
           "with silver cuffs glow darkly for a moment and "+
           "then go dull, as if they have lost something "+
           "vital!\n");
    }
    
    /* Make sure that the no_times > MAX_TIMES so no bonus */
    no_times = MAX_TIMES + 1;

    /* Return 1, indicating that it was disenchanted */
    return 1;
}


public mixed
wear_terel_armour(object obj)
{
    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
        return 0;

    if (no_times < MAX_TIMES) 
    {
        pdex = this_player()->query_base_stat(SS_DEX) / 10;

        this_player()->set_stat_extra(SS_DEX, 
            this_player()->query_stat_extra(SS_DEX) + pdex);
        write("You feel more dextrous as you wear the "
            + short() + ".\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
            + " wears the " + short() + ".\n", ({ this_player() }));
        return 1;
    }

    return 0;
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
public int
remove(object obj)
{
    if (pdex)
    {
        /* Use wearer instead of this player. /Mercade */
        wearer->set_stat_extra(SS_DEX,
            wearer->query_stat_extra(SS_DEX) - pdex);
        pdex = 0;
        write("You feel normal again as you remove the "
            + short() + ".\n");
        tell_room(environment(wearer), QCTNAME(wearer)
            + " removes " + this_player()->query_possessive()
            + " " + short() + ".\n", ({ wearer }));

        // Increment the number of times it has been used
        ++no_times;
        if (no_times >= MAX_TIMES)
        {
            disenchant_object(TP);
        }
                    
        return 1;
    }

    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "#nt#" + no_times + "##";
}

void
init_recover(string arg)
{
    string foobar;

    init_arm_recover(arg);
    if (sscanf(arg, "%s#nt#%d##", foobar, no_times) != 2
        || no_times >= MAX_TIMES) 
    {
        disenchant_object(0);
    }
}



