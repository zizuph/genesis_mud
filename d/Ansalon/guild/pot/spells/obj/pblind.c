/* 
 * pblind object - simple blindness
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#define BLIND_SUBLOC "pot_blind_subloc"

int changeAmount;
int alarm;

void
create_object()
{
    add_name(BLIND_ID);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "PoT magical object blinding the affected.\n");
    set_no_show();
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object *obs;

    spell_target->catch_tell("The black fire leaves your eyes, and you can "+
			"see again.\n");
    obs = all_inventory(environment(spell_target));
    obs -= FILTER_IS_SEEN(spell_target, obs);
    obs += ({ spell_target });
    tell_room(environment(spell_target), "The black fire leaves "+
		QTNAME(spell_target)+" eyes.\n",
		obs, spell_target);

    spell_target->add_prop(LIVE_I_BLIND, 
			   spell_target->query_prop(LIVE_I_BLIND) + 1);
    spell_target->remove_subloc(BLIND_SUBLOC);

    if (!interactive(query_spell_effect_target()) &&
        !query_spell_effect_target()->query_attack() &&
        !query_spell_effect_target()->query_prop(OBJ_M_NO_ATTACK) &&
        F_DARE_ATTACK(query_spell_effect_target(), query_spell_effect_caster()))
        spell_target->command("$kill "+OB_NAME(spell_caster));

    set_alarm(10.0 + itof(random(10)), 0.0, &remove_spell_effect_object());
    return 1;
}

public void
set_pblind_time(int t)
{
    remove_alarm(alarm);
    alarm = set_alarm(itof(t), 0.0, dispel_spell_effect);
}

public int
start()
{
    set_spell_effect_desc("blindness");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    if (move(spell_target,1))
    {
        remove_spell_effect_object();
        return 0;
    }

    changeAmount = 200;

    spell_target->add_prop(LIVE_I_BLIND,
			   spell_target->query_prop(LIVE_I_BLIND) - 1);
    spell_target->add_subloc(BLIND_SUBLOC, TO);

    alarm = set_alarm(30.0 + itof(random(10) + random(5)), 0.0, dispel_spell_effect);

    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "Your eyes are blinded by a blanket of black fire.\n";

    return C(HIS(me)) + " eyes are covered by a blanket of black fire.\n";
}

