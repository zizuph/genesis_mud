
#include "../../guild.h"

inherit "/std/object";
inherit SPELLOBJ_DIR+"spell_obj";

#include <stdproperties.h>

object last_env;

public void create_object()
{
    set_name("_flicker_obj");
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Object causing lamps/torches to go out");

    set_spell_effect_desc("control the winds");
    set_no_show();

}

varargs public int
dispel_spell_effect(object dispeller)
{

    tell_room(environment(this_object()),"As suddenly as they began, the "+
    "chill wind dies down.\n", ({ }));

    remove_spell_effect_object();
    return 1;
}

public void warn_fading()
{
    effect_target->catch_tell("You notice a lull in the blowing "+
    "winds for a moment.\n");
}

public void wind_blows()
{
    if (last_env && ENV(effect_target)!=last_env)
    {
        last_env=ENV(effect_target);
        return;
    }

    object * lamps = filter(deep_inventory(environment(effect_target)),
    &->query_lit(0));

    string message="";
    switch (random(7))
    {
        case 0: 
            message="A cold wind whips around the room, lifting dust "+
            "and debris into the air.\n";
            break;
        case 1:
            message="A howling chill echos about the room as the wind "+
            "dances across your skin.\n";
            break;
        case 2:
            message="An unnatural breeze fills the air.\n";
            break;
        case 3:
            message="Gusts of wind dance across your skin, their "+
            "touch quite unnatural.\n";
    }

    tell_room(environment(this_object()),message);

    foreach (object lamp: lamps)
    {
        if (random(100)>40)
        {
            continue;
        }
        
        if (lamp->extinguish_me())
        {
            tell_room(environment(lamp),"The "+lamp->short()+
            " is suddenly blown out.\n", ({ }));
            environment(lamp)->hook_torch_burned_out(lamp);
            clone_object(SPELLOBJ_DIR+"torch_sh")->shadow_me(lamp);
            lamp->set_flicker_object(TO);
        }
    }
        
}


public int
start()
{

    if (!::start() || move(effect_target,1))
    {
        remove_spell_effect_object();
        return 0;
    }

    /*
     * Timing of Flicker changed by Balance Team February 2009
     * Ranges from 5-20 seconds depending on guild stat, with a
     * 1 minute cooldown afterwards.
     * Rationale:
     *  The duration of the flicker spell will be reduced to around 20
     *  seconds or so. Its a great ability, and lovely for the theme, so
     *  we want to keep it. However, in that it reduces parry, defence,
     *  and tohit against the opponents, it renders them practically
     *  helpless against the Vampire, so long as the Vampire has enough
     *  darkness items in their possession to overcome the 1 torch per
     *  10 second relight allowance (which they always seem to.) We
     *  do not want such a powerful game-changer to last the entire
     *  duration of battle (5 minutes, currently.)
     */
    
    // A vampire at 100 guild stat will have the maximum of 20 seconds
    // and someone with a minimum guild stat will always get at least
    // 5 seconds.
    int delay = max(5, effect_target->query_vamp_stat() / 5);    
    delay = min(20, delay);

    effect_target->catch_tell("You focus your mind intently, summoning "+
    "the cloud gift. In response, a strong wind gusts through the room, "+
    "its invisible tentacles grasping to do your bidding.\n");
    
    tell_room(environment(effect_target),"An unnatural gust of wind picks "+
    "up in the room. The chill breeze indicates a dark omen.\n");

    last_env=ENV(effect_target);

    set_dispel_time(delay);

    // Wind now blows every other second.
    set_alarm(0.1, 2.0, wind_blows);

    return 1;
}

public void init()
{
    ::init();
    add_action(stop,"stop");
}
