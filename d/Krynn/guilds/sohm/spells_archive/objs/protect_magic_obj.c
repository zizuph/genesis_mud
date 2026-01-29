/*
 * Standard Spell Resistance Object
 *
 * This is the spell object for the standard Genesis Magic System Resistance
 * spell. 
 *
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Krynn/common/defs.h"

#include "../defs.h"

inherit "/d/Genesis/specials/std/spells/obj/resistance_obj";

#define PROT_MAGIC_PROP     "_wohs_prot_element_type"
#define PROT_MAGIC_CASTER   "_wohs_prot_element_caster"

string prot;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
   setuid();
   seteuid(getuid());

    set_name("_protect_magic_object_");
    set_short("ward against magic object");    
    set_long("This is the standard resistance spell's object. It protects "
        + "one against certain elements.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created to protect against magic.\n");
    set_spell_effect_desc("element protection");    
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    object caster = query_effect_caster();
    prot = target->query_prop(PROT_MAGIC_PROP);

    if(!prot)
        prot = "the arcane";

    if (objectp(target))
    {
        target->catch_tell("You are now protected by a magical ward of " +prot+ 
            " resistance.\n");
        tell_room(environment(target), QCTNAME(target) + " is now protected "
            + "by a magical ward of " +prot+ " resistance.\n", ({ target }));
    }
    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("You feel your ward against " +prot+ " disappear.\n");
        tell_room(environment(target), QCTNAME(target) + " is no longer " +
           "protected by a magical ward.\n", ({ target }));
        target->remove_prop(PROT_MAGIC_PROP);
        target->remove_prop(PROT_MAGIC_CASTER);
    }

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the ward against " +prot+ " begin to "
            + "fade.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the ward against " +prot+ ".\n");
    }    
}