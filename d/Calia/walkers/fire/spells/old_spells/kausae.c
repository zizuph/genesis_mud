
 /*
  *
  * Kausae (Combustion) spell for the Firewalkers of Thalassia
  * by Jaacar - November, 1997
  * Converted to the new spell system May 20th, 1998
  *
  */

#pragma strict_types

inherit "/d/Genesis/magic/spells/bolt";

#include <ss_types.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "defs.h"
#include FIRE_HEADER

public int create_spell_kausae(object caster, object *targets, 
    string argument);
private void desc_kausae_casting(object caster, object *targets);
private void desc_kausae_damage(object caster, object target, 
    mixed *results);
private void desc_kausae_miss(object caster, object target);

public object *
kausae_target_present_enemies(object caster, string str)
{
    object *enemies = (object *)caster->query_enemy(-1) &
        all_inventory(environment(caster));

    if (!present("_kausae_potion_object_",caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "kausae potion!\n");
        return ({});
    }

    if (environment(caster)->query_prop(ROOM_UNDER_WATER))
    {
        caster->catch_tell("You cannot use the powers of Kausae "+
            "while underwater!\n");
        return ({});
    }

    if (!present(STOIECHEIO_OBJ,caster))
    {
        caster->catch_tell("You can only use the powers of Kausae "+
            "in elemental form.\n");
        return ({});
    }

    if (!sizeof(enemies))
    {
        caster->catch_msg("There aren't any enemies present!\n");
        return ({});
    }

    return enemies;
}

public int
create_spell_kausae(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_time(4);
    set_spell_mana(216);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_PRAYER, 60);
    set_spell_offensive(1);
    set_bolt_pen(900);
    set_spell_resist(spell_resist);
    set_spell_ingredients(({})); // Uses a potion
    set_spell_task(TASK_ROUTINE+100);
    set_bolt_casting_msg(desc_kausae_casting);
    set_bolt_damage_msg(desc_kausae_damage);
    set_bolt_miss_msg(desc_kausae_miss);
    return 0;
}

private int
try_to_hit(object caster, object target)
{
    return (target->resolve_task(TASK_ROUTINE+100, ({ TS_DEX, SS_DEFENCE })) > 0);
}

private void
desc_kausae_casting(object caster, object *targets)
{
    caster->catch_tell("Concentrating on the image of your attackers "+
            "in your mind, you summon forth the powers granted to "+
            "you by Lord Pyros.\nYou feel the intense energies of the Lord "+
            "of Flames pulsing throughout you, growing in the "+
            "centre of your flaming body.\n");
    
    targets->catch_msg(QCTNAME(caster)+" seems to diminish in "+
            "ferocity.  The flames do not lick as high as before and "+
            C_HE+" seems faded.\nAs "+C_HE+" becomes more and more "+
            "transparent, you become aware of an incredibly dense energy "+
            "growing and pulsing in "+C_HIS+" centre.\n");

    caster->tell_watcher(QCTNAME(caster)+" seems to diminish in "+
            "ferocity.  The flames do not lick as high as before and "+
            C_HE+" seems faded.\nAs "+C_HE+" becomes more and more "+
            "transparent, you become aware of an incredibly dense energy "+
            "growing and pulsing in "+C_HIS+" centre.\n",targets);
}

private void
desc_kausae_damage(object caster, object target, mixed *result)
{
    string how;

    switch(result[0])
    {
        case 0..10:
            how = "slightly burning";
            break;
        case 11..20:
            how = "scorching"; 
            break;
        case 21..30:
            how = "badly burning"; 
            break;
        case 31..40:
            how = "whithering"; 
            break;
        case 41..70:
            how = "shrivelling"; 
            break;
        case 71..99:
            how = "consuming"; 
            break;
        default:
            break;
    }

    if (!how)
    {
        caster->catch_tell("Upon you giving a final thought "+
            "the entire mass of energy erupts from your body with a terrible "+
            "roar, streaking towards "+target->query_the_name(caster)+
            ".\n"+capitalize(T_HE)+
            " appears to try to avoid the mass but to no avail.  It brutally "+
            "slams into "+T_HIM+" quickly burning away "+T_HIS+" flesh, then "+
            "finally "+T_HIS+" bones leaving nothing behind.\nDrained "+
            "by your efforts you find it impossible to hold your elemental "+
            "form any longer.\n");
        target->catch_tell("With a terrible "+
            "roar, the entire mass of energy streaks towards you.  You "+
            "duck to try to avoid it, but it grows in mass as it streaks "+
            "towards you.  It strikes you, painfully burning your flesh "+
            "away from your bones.  It quickly burns away all of your "+
            "nerves then finally your bones, leaving nothing behind.\n");
        tell_room(environment(caster),"With a terrible "+
            "roar, the entire mass of energy streaks towards "+
            target->query_the_name(caster)+
            ".  "+capitalize(T_HE)+" tries to duck to avoid it, but it seems "+
            "to grow in mass as it streaks towards "+T_HIM+".  It strikes "+
            T_HIM+" with devastating force, burning "+T_HIS+" flesh away from "+
            T_HIS+" body then finally "+T_HIS+" bones, leaving nothing "+
                "behind.\n",({caster, target}));
        seteuid(getuid());
        present(STOIECHEIO_OBJ,caster)->do_revert();
        target->add_prop(LIVE_I_NO_CORPSE,1);
    }
    else
    {
        caster->catch_tell("Upon giving a final thought, a fiery-red "+
            "globe of plasma tears loose and jets erupts from your "+
            "body with a terrible roar, streaking "+
            "towards "+target->query_the_name(caster)+", " +
            how + " " + T_HIM + ".\n");
        target->catch_tell("With a terrible roar, a fiery-red globe "+
            "of plasma tears loose and jets towards "+
            "you.  It strikes you forcefully, "+how+" you.\n");
        tell_room(environment(caster),"With a terrible "+
            "roar, a fiery-red globe of plasma tears loose and jets "+
            "towards "+target->query_the_name(caster)+", "+how+" "+T_HIM+
            ".\n",({caster, target}));
    }
}

private void
desc_kausae_miss(object caster, object target)
{
    target->catch_tell("A fiery-red globe of plasma tears loose "+
        "and streaks in your direction.  You skillfully "+
        "dodge it and it disipates just beyond you.\n");
    caster->catch_tell("Upon giving a final thought, a fiery-red globe "+
        "of plasma tears loose and streaks towards "+
        target->query_the_name(caster)+", but it misses.\n");
    caster->tell_watcher("A fiery-red globe of plasma tears loose "+
        "and streaks in the direction of "+target->query_the_name(caster)+
        ", but it misses.\n",target);
}
