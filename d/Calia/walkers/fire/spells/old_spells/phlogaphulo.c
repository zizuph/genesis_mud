
 /*
   * Phlogaphulo (Flame Blade) Spell for the Firewalkers
   * by Jaacar
   * November, 1997
   * Converted to the new spell system May 20th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public void phlogaphulo(object caster, object *targets, int *resist,
    int result);
public int create_spell_phlogaphulo(object caster, object *targets,
    string argument);

public object *
phlogaphulo_target_one_present_object(object caster, string str)
{
    mixed *oblist;
    
    if (!present("_phlogaphulo_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "phlogaphulo potion.\n");
        return ({});
    }

    if (!str || str == "")
    {
        caster->catch_tell("What do you wish to target?\n");
        return ({});
    }

    if (!parse_command(str, all_inventory(caster) + 
        all_inventory(environment(caster)), "[at] / [on] [the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	caster->catch_tell("What do you wish to target?\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
	caster->catch_tell("You will have to be more specific!  You can only " +
	  "select one target.\n");
	return ({});
    }

    if (oblist[0]->query_prop(PHLOGAPHULO_PROP))
    {
        caster->catch_tell("That weapon is already flaming!\n");
        return ({});
    }

    if (oblist[0]->query_prop(PHLOGAPHULO_TIMES) >= 10)
    {
        caster->catch_tell("That weapon can no longer be enchanted.\n");
        return ({});
    }

    if (oblist[0]->query_pen() > 65 || oblist[0]->query_hit() > 70)
    {
        caster->catch_tell("That weapon is far too powerful for you to enchant.\n");
        return ({});
    }

    if (oblist[0]->query_pen() && present(oblist[0], caster))
        return oblist;
    else
        caster->catch_tell("You have no such weapon.\n");
        return ({});
}

public int 
create_spell_phlogaphulo(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(152);
    set_spell_task(TASK_ROUTINE+100);
    set_spell_element(SS_ELEMENT_FIRE,40);
    set_spell_form(SS_PRAYER,40);
    set_spell_ingredients(({})); // Uses a potion
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    return 0;
}

public void
remove_flames(object weapon, int extra_hit, int extra_pen)
{
    string foo;
    if (living(environment(weapon)))
    {
        tell_room(environment(environment(weapon)),"The "+weapon->short()+
            " held by "+QTNAME(environment(weapon))+
            " stops flaming.\n",environment(weapon));
        tell_object(environment(weapon),"Your "+weapon->short()+
            " stops flaming.\n");
    }
    weapon->remove_prop(PHLOGAPHULO_PROP);
    foo = weapon->query_prop(PHLOGAPHULO_OLD_SHORT);
    weapon->set_short(foo);
    weapon->remove_flaming_shadow();
    weapon->remove_prop(PHLOGAPHULO_OLD_SHORT);
    if (weapon->query_wielded())
        weapon->query_wielded()->update_weapon(weapon);
}

public void 
phlogaphulo(object caster, object *targets, int *resist, int result)
{
    object weapon = targets[0];
    int extra_pen, extra_hit;
    string wshort = weapon->short();
    float time = PHLOGAPHULO_DURATION;
    extra_pen = PHLOGAPHULO_PEN;
    extra_hit = PHLOGAPHULO_HIT;

    caster->catch_tell("You wave your hand over the "+wshort+
        " and it begins to flame.\n");
    tell_room(environment(caster),QCTNAME(caster)+" waves "+C_HIS+" hand "+
        "over "+C_HIS+" "+wshort+" and it begins to flame.\n",caster);
    seteuid(getuid());
    clone_object(PHLOGAPHULO_SH)->shadow_me(weapon);
    weapon->add_prop(PHLOGAPHULO_OLD_SHORT, weapon->query_short());
    weapon->set_short("flaming "+weapon->query_prop(PHLOGAPHULO_OLD_SHORT));
    weapon->add_prop(PHLOGAPHULO_PROP,1);
    weapon->add_prop(PHLOGAPHULO_TIMES, weapon->query_prop(PHLOGAPHULO_TIMES) + 1);
    if (weapon->query_wielded())
        weapon->query_wielded()->update_weapon(weapon);
    set_alarm(time, 0.0, "remove_flames", weapon, extra_hit, extra_pen);
}
