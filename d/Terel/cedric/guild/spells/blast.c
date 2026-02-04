#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include <stdproperties.h>
#include "../guild_defs.h"

inherit "/w/cotillion/open/template/template";
inherit "/d/Genesis/specials/std/spells/harm";

public void
config_harm_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("vibrato");
    set_spell_desc("This Song of Power is designed to harm an opponent with a blast of discordant sound.");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(50.0);
    set_spell_task(TASK_HARD); 
    set_spell_time_factor(4.0);  

    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
}

public int
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) 
    {
        caster->catch_msg("You can't sing under water.\n");
        return 0;
    }
    return 1;
}

/*
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
//    caster->catch_tell(caster_message);
//    tell_room(environment(caster), watcher_message, ({ caster }), caster);
}

public void
desc_harm_cast(object caster, object *targets)
{
}
*/

string *harm_descs = ({
        "Your ears are left ringing by a blast of sound.",
        "You are hurt by a blast of discordant music.",
        "You are terribly shaken by a powerful blast of music.",
        "A powerful blast of music knocks you back a few steps.",
        "You are thrown to the ground by a tremendous blast of music."
        });

string *onlooker_descs = ({ 
        "{target} shakes {target:his} head, trying to clear {target:his} ears of their ringing.",
        "{target} is rattled by a blast of sound.",
        "A blast of discordant music hurts {target}.",
        "A powerful blast of music leaves {target} visibly shaken.",
        "{target} staggers back as {target:he} is crushed by a blast " 
        + "of music."
        });

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    t_set("target", target);

    if (result[0] < 0) 
    {
        t_tell(target, "You are unaffected by the blast of music.");
        t_watchers_miss("{target} appears unaffected by the blast of music.", caster, target);
        return;
    }

    t_tell(target, GET_NUM_DESC(result[0], 100, harm_descs));
    t_watchers(GET_NUM_DESC(result[0], 100, onlooker_descs), caster, target);
}

