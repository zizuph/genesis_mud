/* 
 * hortale object - channelling the speed of the Mearas
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>
#include "/d/Shire/common/defs.h"
#include "../../herald.h"

inherit "/d/Genesis/specials/new/magic/spells/objs/haste_obj";

#include "/d/Genesis/specials/calculations.c"

#define HERALD_HASTE_EFFECT "_herald_mounted_haste_effect"
#define CHECK_INTERVAL 5.0

// Global Variables
public void query_hortale_still_mounted();
object mount;
int mounted = 1;  // 0 is not mounted, 1 is mounted

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();

    if (!result)
    {
        return result;
    }

    mounted = 1;
    // HERALD_DEBUG("Quickness at setup: " +Quickness+ ", mounted: " + mounted);

    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    if(!mounted)
        Quickness = 0;

    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }

    return 1;
}


/*
 * Function:    query_spell_effect_still_valid()
 * Description: For a maintained spell effect, this allows the spell
 *              effect to determine whether it is still valid or not.
 *              In the maintain_spell_effects function, it will dispel
 *              the effect object if it determines that it is no longer
 *              valid.
 */
public int
query_spell_effect_still_valid()
{
    object target = query_effect_target();

    // Need to be mounted on or leading a steed for this blessing to work.
    if(target->is_rider_shadow() || target->is_leading_steed())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void
query_hortale_still_mounted()
{
    object target = query_effect_target();
    string mount_str;

    if(mount->steed_short())
        mount_str = mount->steed_short();
    else
        mount_str = mount->short();

    if(!(target->is_rider_shadow()) && (mounted == 1))
    {
        // HERALD_DEBUG("Dismount reduction called.");
        target->dec_prop(LIVE_I_QUICKNESS, Quickness); 
        target->query_combat_object()->cb_update_speed();

        if(mount_str)
            target->catch_tell("Your " + mount_str + " slows after you " +
                "dismount " +HIM_HER(mount)+ ".\n");

        mounted = 0;
    }
    else if (target->is_rider_shadow() && (mounted == 0))
    {
        // HERALD_DEBUG("Mount increase called.");
        mounted = 1;

        target->inc_prop(LIVE_I_QUICKNESS, Quickness);
        target->query_combat_object()->cb_update_speed();
        // HERALD_DEBUG("Quickness bonus at post-mount: " +Quickness+ ".");
        target->catch_tell("Your " + mount_str + " is ready to ride like " +
            "the wind again!\n");
    } 

    // HERALD_DEBUG("Default check called.");
    set_alarm(CHECK_INTERVAL, 0.0, &query_hortale_still_mounted());

}

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_herald_haste_object_");
    set_short("haste spell object");    
    set_long("This is the standard haste spell's object. It makes "
        + "one faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the hortale spell.\n");
    set_spell_effect_desc("Blessing of the Mearas");  
    set_dispel_time(1200);  

    set_alarm(CHECK_INTERVAL, 0.0, &query_hortale_still_mounted());
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
    mount = target->query_steed();
    string mount_str;

    if(!objectp(mount))
    {
        // HERALD_DEBUG("No mount detected in hook_spell_effect_started.");
        return;
    }

    if(mount->steed_short())
        mount_str = mount->steed_short();
    else
        mount_str = mount->short();

    if (objectp(target))
    {
        target->catch_tell("Your " + mount_str + " is now blessed with " +
            "the swiftness of Nahar, making " +HIM_HER(mount)+ " as " +
            "fast as the Mearas!\n");
        tell_room(environment(target), QCTPNAME(target) + " " + mount_str +
            " now moves with the enhanced speed of the Mearas!\n", 
            ({ target }));
    }      

    target->add_prop(HERALD_HASTE_EFFECT, 1); 
 
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
    string mount_str;

    if(mount->steed_short())
        mount_str = mount->steed_short();
    else
        mount_str = mount->short();

    target->remove_prop(HERALD_HASTE_EFFECT);

    if(target->query_ghost())
        return;

    if(!objectp(mount) && objectp(target))
    {
        // HERALD_DEBUG("No mount detected in hook_spell_effect_ended.");
        target->catch_tell("You cease channelling the blessings of " +
            "Orome the Rider.\n");
        return;
    }

    if (objectp(target))
    {
        target->catch_tell("Your " + mount_str + " suddenly slows, " +
            "no longer blessed with the swiftness of the Mearas.\n");
        tell_room(environment(target), QCTPNAME(target) + " " + mount_str
            + " moves less swiftly than before.\n", ({ target }));
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
        target->catch_tell("You feel you will be unable to maintain " +
            "channelling the hortale blessing.\n");
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
        caster->catch_tell("Mentally drained, you are unable to maintain " +
            "the hortale blessing.\n");
    }    
}

