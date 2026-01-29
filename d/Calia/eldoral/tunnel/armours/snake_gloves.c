/*   snake_gloves.c
 *
 * This pair of snake-skin gloves is not only an armour,
 * it also shadows the player with a function that makes
 * the player fight slightly better when hitting with the
 * hands, unarmed. It also gives the player 5 extra levels
 * of unarmed combat.
 *
 * Baldacin@Genesis, Sep 2003
 *
 * Updates:
 *   - fixed usage of this_player so that message is passed correctly
       when someone wearing the gloves kills the banshee.
       (Petros, July 2008)
 */

inherit "/std/armour";
inherit "/lib/keep";
#include "snake_gloves.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
object glove_shadow = 0;

void
create_armour()
{
    set_name("gloves");
    set_adj("snake-skin");
    add_adj("green");
    set_short("pair of snake-skin gloves"); 
    set_pshort("pairs of snake-skin gloves"); 
    set_long("This is a pair of green snake-skin gloves, crafted "+
      "with great expertise by an expert armourer. They seem to "+
      "fit your hands very well.\n");
    set_ac(10);
    set_at(A_HANDS);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({15,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"These gloves are enchanted.", 20,
        "These gloves give you prowess when attacking with them and "+
        "you are unarmed.", 40, "These gloves will magically enhance "+
        "your unarmed skill.", 60 }));
    add_prop(OBJ_S_WIZINFO,"This pair of snake-skin gloves is not "+
        "only an armour, it also shadows the player with a function "+
        "that makes the player fight slightly better when hitting with "+
        "the hands, unarmed. It also gives the player 5 extra levels "+
        "of unarmed combat.\n");
    set_wf(this_object());
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15 + random(5)));
    set_keep(1);
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    object wearer;
       
    setuid(); seteuid(getuid());
    wearer = environment(obj);
    if (living(wearer))
    {
        glove_shadow = clone_object(GLOVE_SHAD);
        glove_shadow->start_gloves(wearer);
        wearer->set_skill_extra(SS_UNARM_COMBAT, wearer->query_skill_extra(SS_UNARM_COMBAT) + 5);
        return 1;
    }

    // Should never happen.    
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
public mixed
remove(object obj)
{
    object wearer;
    
    wearer = query_worn();
    if (objectp(wearer))
    {
        wearer->stop_gloves();
        wearer->set_skill_extra(SS_UNARM_COMBAT, wearer->query_skill_extra(SS_UNARM_COMBAT) - 5);
        return 1;
    }
    
    return 0;
}

