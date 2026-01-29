/* File         : /d/Khalakhor/guilds/tuatha/obj/spellobj.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : August 12, 1998
 * Purpose      : This is the Tuatha De Danaan spell object.
 * Related Files: /d/Khalakhor/guilds/tuatha/spells/
 * Comments     : TODO: add all the spells ;-)
 *                      security issues with entering/leaving inv, cloning
 *                      redefine hold() and release() messages
 *                      add in the variable long descs
 *                      ensure that none/some spells can be cast w/o hold?
 *                      add wizinfo and magic props
 * Modifications: Teth - March 19, 1999 - added comments
 *                                      - added in lore appraisal
 *                                      - changed long to use vbfc
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/magic/spellcasting";
inherit "/d/Khalakhor/std/object";
inherit "/lib/holdable_item";

// inherit "/d/Khalakhor/guilds/tuatha/spells/bho";

#include <stdproperties.h>
#include <wa_types.h>

#include "../guild.h"
#include "/d/Khalakhor/sys/skills.h"

/*
 * Function name: create_khalakhor_object (MASK)
 * Description  : The constructor function.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_object()
{
    set_name("twig");
    add_name("_Khalakhor_tuatha_twig_");
    set_adj(({"gnarled","oaken"}));
    add_adj(({"living","brown"}));
    set_short("gnarled oaken twig");

    set_long("@@my_long");

    set_slots(W_ANYH);

/*
    add_spell("bho", "find origin", create_bho_spell, 
      spell_target_one_present_object);
*/
    add_prop(OBJ_I_WEIGHT, 750); /* 750 grams */
    add_prop(OBJ_I_VOLUME, 775); /* 775 mL */
    add_prop(OBJ_I_VALUE, 1035); /* Give it a value, as too large
                                  or no value may break code. */
    add_prop(OBJ_M_NO_DROP, "That which has been given to you in trust " +
                            "by the Crann Bethadh can not be carelessly " +
                            "dropped or given away.\n");   
    add_prop(OBJ_M_NO_GIVE, "That which has been given to you in trust " +
                            "by the Crann Bethadh can not be carelessly " +
                            "dropped or given away.\n");
    add_prop(OBJ_M_NO_SELL, "No shopkeeper would truly fathom the " +
                            "value of this branch.\n");
    add_prop(OBJ_M_NO_STEAL, "The twig slips from your grasp as you " +
                             "attempt to wrap your fingers around it.\n");
}

/*
 * Function name: leave_env (MASK)
 * Description  : This function is called when the item leaves an environment.
 * Arguments    : object from - the environment it is leaving.
 *              : object to   - the environment it is entering.
 * Returns      : n/a
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    holdable_item_leave_env(from, to);
    remove_spell_object(from);
}

/*
 * Function name: appraise_object
 * Description  : This is called when the object is appraised.
 * Arguments    : int num - A seed number to randomize variables when appraised.
 * Returns      : n/a
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_holdable_item();
}

/*
 * Function name: enter_env
 * Description  : This function is called when the object is entering a new env.
 * Arguments    : object env  - the destination it is entering.
 *              : object from - the location it is leaving.
 * Returns      : n/a
 */
/*
public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (IS_MEMBER(env) || env->query_wiz_level())
        add_spell_object(env);
}

*/

/*
 * Function name: lore_skill_desc (MASK)
 * Description  : Provides a variable appraisal message based on lore skill.
 * Arguments    : n/a
 * Returns      : The string of the lore description.
 */
public string
lore_skill_desc()
{
    int loreskill = this_player()->query_skill(SS_KHALAKHOR_LORE);

    switch(loreskill)
    {
    case 0..10:
    return "";
    break;

    case 11..35:
    return "You recognize the branch.";
    break;

    case 36..100:
    return "You recognize the branch as special to the Meidh region of " +
           "Khalakhor.";
    break;

    default:
    return "";
    break;
    }
}

/*
 * Function name: my_long
 * Description  : VBFC for the set_long function.
 * Arguments    : n/a
 * Returns      : The long description of the object.
 */
public string
my_long()
{
    
    return "This is a segment of the Crann Bethadh. Green lobed leaves " +
        "growing with vigour on the gnarled twig suggest that it is " +
        "imbued with the magic of nature, much like the sacred tree " +
        "which is its parent. Each of the Tuatha bears one of these " +
        "branches, a bond between the possessor and the Crann " +
        "Bethadh, and thus with each other.\n";
}