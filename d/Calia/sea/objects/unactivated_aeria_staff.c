/*******************************************************
*
* /d/Calia/sea/objects/unactivated_aeria_staff.c
*
* Creator:    Quintas    03/10/2002
* Updated:    Jaacar      5/08/2003 - modified slightly
                                      moved to sea dir.
*
* This staff needs to be taken to Aeria to be activated. 
* 
********************************************************/

#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h> 
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "defs.h"

void
create_weapon()
{
    /*
     * Set weapon names, adjectives, descriptions. 
     */

    set_name("runed staff");
    add_name("staff");
    add_name("_unactivated_aeria_staff_");
    set_pname("staves"); 
    set_short("runed staff");
    set_pshort("runed staves");
    set_long("This is a long, runed staff with a large gem set in "+
        "the top of it. It appears that a golden claw of some sort "+
        "is holding a diamond in place. Spidery runes trace up and down " +
	    "the shaft of the staff.\n");
    set_adj(({"long","runed"}));

    /* Add_item for Runes, claw, diamond, shaft */ 

    add_item(({"runes"}), "@@runes_desc");
    add_item(({"claw","golden claw"}), "This claw has small scales and "+
        "long talons which form a perfect cradle for the diamond to nestle "+
        "into. It obviously came from a lizard of sometype, or maybe even "+
        "a gold dragon.\n");
    add_item(({"gem","diamond","large gem"}), "This diamond is of very pure "+
        "quality. It's clarity and brillance momentarily blind you as you "+
        "look at it.\n");
    add_item(({"shaft"}), "The shaft of the staff is made of rare ironwood. "+ 
        "You see runes carved into it.\n"); 

    /*
     * Set weapon combat properties.
     */

    set_wt(W_CLUB);
    set_hit(30);
    set_pen(10);
    set_dt(W_BLUDGEON); 
    set_hands(W_BOTH);
    add_prop(OBJ_I_NO_SELL,1);   // Can't sell it
    add_prop(OBJ_I_NO_DROP,1);   // Can't drop it
    add_prop(OBJ_I_NO_GIVE,1);   // Can't give it away
    add_prop(OBJ_M_NO_STEAL,1);  // Nobody can steal it
    
    /* 
     * Call set_wf to customize wield/unwield functions.
     */

    set_wf(TO);

    /*
     * Set weapon standard properties. Ie. weight, size, value, etc
     */
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(10, W_CLUB));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_WEAPON(10, W_CLUB) / 5);
  
    /*
    * Make the weapon magical.
    */

    /* Designate this as a magic weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    /* The 'form' of the magic and the degree of its expression. */
    add_prop(MAGIC_AM_MAGIC, (({ 60, "enchantment" })));

}

/*
 * Function:     runes_desc
 * Description:  A function used in VBFC to give the description
 *               of the staff, depending on skill and stat checks.
 * Returns:      The runes' description.
 */

string
runes_desc(string str)
{
    str = "The runes are a flowing cursive script made up "+ 
           "of curliques and dots. "; 
    
    /* Does the wielder have enough INT and SS_LANG to read the runes? */
    
    /* The wielder cannot read any of the command words */
    
    if ((TP->query_skill(SS_LANGUAGE) < 25) ||
       (TP->query_stat(SS_INT) < 15))
       str = (str + "They seem to shift and squiggle before your eyes. "+ 
           "You cannot make any understanding out of them.\n");
      
    /* The wielder can read the first command word */

    if ((TP->query_skill(SS_LANGUAGE) >= 25) &&
       (TP->query_stat(SS_INT) >= 15))
           str = (str + "You find that you can understand the first command "+
           "word from the runes. It is called 'Lignium'.\n");

    /* The wielder can read both command words. */ 
 
    if ((TP->query_skill(SS_LANGUAGE) >= 40) && 
       (TP->query_stat(SS_INT) >= 50))
           str = (str + "You find that you can understand both the command "+
           "words from the runes.  They are 'Lignium' and 'Nosterim'.\n");

return str;
}

/* 
 * Function name: wield
 * Description  : This function might be called when someone tries to wield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 * Arguments    : object obj - the weapon someone tried to wield.
 * Returns      : int  0 - wield this weapon normally.
 *                     1 - wield the weapon, but print no messages.
 *                    -1 - do not wield the weapon, use default messages.
 *                string - do not wield the weapon, use this fail message.
 */

public mixed
wield(object obj)
{
    return 0;
}

/*
 * Function name: unwield
 * Description  : This function might be called when someone tries to unwield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 * Arguments    : object obj - the weapon to stop wielding.
 * Returns      : int  0 - the weapon can be unwielded normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - do not unwield the weapon, print default messages.
 *                string - do not unwield the weapon, use this fail message.
 */

public mixed
unwield(object obj)
{
    return 0;
}

string
query_auto_load()
{
    return MASTER + ":";
}


