/* 
 * psummon - summon dragons
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

int gResult;

int gAlarm, gSkill;

void
create_object()
{
    set_name(DRAGON_ID);
    set_no_show();
    add_prop(OBJ_M_NO_GET, 1);
}

varargs public int
dispell_spell_effect(object dispeller)
{
    set_alarm(0.0, 0.0, &remove_spell_effect_object());

    return 1;
}

void
set_result(int r)
{
    gResult = r;
}

int
query_result()
{
    return gResult;
}

void
summon_dragon()
{
    object dragon;

    if (environment(query_spell_effect_caster()) !=
        query_spell_effect_target())
    {
        tell_room(query_spell_effect_target(), "The dragon about to " +
            "swoop down upon you decides to take to the skies again " +
            "and flies off to the distance.\n");
        remove_spell_effect_object();
        return;
    }
    
    setuid();
    seteuid(getuid());
    dragon = clone_object(GUILDDIROBJ + "living/dragon");
    dragon->set_summoner(query_spell_effect_caster());
    dragon->set_gender(!query_spell_effect_caster()->query_gender());

    tell_room(query_spell_effect_target(), "With a final beat of " +
        "its leathery wings, " + LANG_ADDART(dragon->short()) +
        " lands here.\n");
    dragon->move_living("M", query_spell_effect_target());
    remove_spell_effect_object();
}

void
summon_message_cont()
{
    if (environment(query_spell_effect_caster()) !=
        query_spell_effect_target())
    {
        tell_room(query_spell_effect_target(), "In the near distance, " +
            "a winged-shaped creature just a moment ago on its way " +
            "towards you decides to alter course.\n");
        remove_spell_effect_object();
        return;
    }

    tell_room(query_spell_effect_target(), "A cruel shriek from the " +
        "skies alterts you to the wing-form of a dragon bearing down " +
        "upon you with great speed!\n");

    set_alarm(3.0 + itof(random(2)), 0.0, &summon_dragon());
}

void
summon_message()
{
    if (query_result() < 5)
    {
        query_spell_effect_caster()->catch_tell("You watch the skies " +
            "expectadely but see no response to your summons.\n");
        remove_spell_effect_object();
    }
    else if (environment(query_spell_effect_caster()) ==
        query_spell_effect_target())
    {
        tell_room(query_spell_effect_target(), "In the distance, like a " +
            "dark star on the horizon, a winged-shaped creature makes its " +
            "way towards you.\n");
    }
    
    set_alarm(8.0 + itof(random(4)), 0.0, &summon_message_cont());
}

public int
start()
{
    set_spell_effect_desc("dragon summoning");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    set_alarm(6.0 + itof(random(4)), 0.0, &summon_message());
    
    return 1;
}
