/* 
 * pslow object - slow the target down
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#define SLOW_SUBLOC "pot_slow_subloc"

int changeAmount;
int alarm;

void
create_object()
{
    add_name(SLOW_ID);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "PoT magical object slowing the affected.\n");
    set_no_show();
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object *obs;

    spell_target->catch_tell("The air around you changes back to normal.\n");
    obs = all_inventory(environment(spell_target));
    obs -= FILTER_IS_SEEN(spell_target, obs);
    obs += ({ spell_target });
    tell_room(environment(spell_target), "The air around "+
        QTNAME(spell_target)+" changes back to normal.\n",
        obs, spell_target);

    spell_target->change_prop(LIVE_I_QUICKNESS,
	spell_target->query_prop(LIVE_I_QUICKNESS) + changeAmount);

    (spell_target->query_combat_object())->cb_update_speed();

    spell_target->remove_subloc(SLOW_SUBLOC);

    remove_spell_effect_object();
    return 1;
}

public void
set_pslow_time(int t)
{
    t = MIN(300, t);
    remove_alarm(alarm);
    alarm = set_alarm(itof(t), 0.0, dispel_spell_effect);
}

public int
start()
{
    set_spell_effect_desc("slowness");

    if (!::start() || move(spell_target,1))
    {
        remove_spell_effect_object();
        return 0;
    }

    changeAmount = min(150, max(75, query_spell_effect_caster()->query_stat(SS_OCCUP))) +
        random(50) - spell_target->query_stat(SS_STR)/3;
    if (spell_caster->query_priest_level() == 0)
        changeAmount /= 2;
    if (spell_caster->query_priest_level() == 1)
        changeAmount = (changeAmount * 3) / 4;
    if (changeAmount < 1)
        changeAmount = 1;

    spell_target->change_prop(LIVE_I_QUICKNESS,
        spell_target->query_prop(LIVE_I_QUICKNESS) - changeAmount);

    (spell_target->query_combat_object())->cb_update_speed();

    spell_target->add_subloc(SLOW_SUBLOC, TO);

    alarm = set_alarm(300.0, 0.0, dispel_spell_effect);

    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are trapped in thick air of red color, and can only " +
            "move very slowly.\n";

    return "The air around "+HIM(me)+" has red color and "+HE(me)+
        " moves sluggishly.\n";
}
