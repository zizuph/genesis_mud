/* 
 * peyes - dragon eyes.
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#define EYES_SUBLOC "eyes"

object gSublocObj;
int gDark;
int alarm;

void
create_object()
{
    add_name(EYES_ID);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "PoT magical object bestowing darkness sight.\n");
    set_no_show();
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object *obs;

    spell_target->catch_tell("You close your eyes in pain for a moment. " +
	"When you open them your vision returns to normal.\n");

    obs = all_inventory(environment(spell_target));
    obs -= FILTER_IS_SEEN(spell_target, obs);
    obs += ({ spell_target });
    tell_room(environment(spell_target), QCTNAME(spell_target)+ " closes "+
		HIS(spell_target)+" eyes for a moment.\n",
		obs, spell_target);

    spell_target->change_prop(LIVE_I_SEE_DARK,
        spell_target->query_prop(LIVE_I_SEE_DARK) - gDark);
    if (gDark > 1)
        spell_target->change_prop(LIVE_I_SEE_INVIS,
            spell_target->query_prop(LIVE_I_SEE_INVIS) - (gDark - 1));

    spell_target->remove_subloc(EYES_SUBLOC);

    if (objectp(gSublocObj))
        spell_target->add_subloc(EYES_SUBLOC, gSublocObj);
    
    remove_spell_effect_object();
    return 1;
}

public void
set_pslow_time(int t)
{
    remove_alarm(alarm);
    alarm = set_alarm(itof(t), 0.0, dispel_spell_effect);
}

public int
start()
{
    set_spell_effect_desc("darkvision");

    if (!::start() || move(spell_target,1))
    {
        remove_spell_effect_object();
        return 0;
    }

    switch (spell_caster->query_priest_level())
    {
        case 2:        // ancient dragon
    	    gDark  = (spell_caster == spell_target ? 5 : 2);
    	    break;
    	case 1:         // aged dragon
    	    gDark  = (spell_caster == spell_target ? 3 : 1);
    	    break;
    	default:         // adult dragon
    	    gDark  = 1;
    }

    spell_target->change_prop(LIVE_I_SEE_DARK,
        spell_target->query_prop(LIVE_I_SEE_DARK) + gDark);
    if (gDark > 1)
        spell_target->change_prop(LIVE_I_SEE_INVIS,
            spell_target->query_prop(LIVE_I_SEE_INVIS) + gDark);

    gSublocObj = spell_target->query_subloc_obj(EYES_SUBLOC);

    spell_target->add_subloc(EYES_SUBLOC, TO);

    alarm = set_alarm(900.0, 0.0, dispel_spell_effect);

    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You have the eyes of a dragon.\n";

    return C(HIS(me)) + " eyes look like the eyes of a dragon.\n";
}

