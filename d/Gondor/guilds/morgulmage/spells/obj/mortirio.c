#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "darkvision_obj";

#include "../generic_functions.c"

public void 
create_spell_object()
{
    set_name("_mortirio_object_");
    set_short("mortirio spell object");    
    set_long("This is the standard darkvision spell's object. It turns "
        + "one's skin to stone.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the morgul mage mortirio spell.\n");
    set_spell_effect_desc("See in Darkness");    
}

public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your eyes glow like red coals, and you notice " +
            "your vision can now easily pierce the shadows around you.\n");
        tell_room(environment(target), QCTPNAME(target) + " eyes "
            + "glow like red coals.\n", ({ target }));
    }    
}

public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your eyes cease to glow like red coals, "
            + "your ability to see in darkness lessened.\n");
        tell_room(environment(target), QCTPNAME(target) + 
            " eyes no longer glow like red coals.\n", ({ target }));
    }
}

public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the effects of mortirio lessen.\n");
    }
}

public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you lose control of "
            + "mortirio.\n");
    }    
}
