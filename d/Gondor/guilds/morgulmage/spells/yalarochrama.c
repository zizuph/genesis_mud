#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "../morgulmage.h"
#include <terrain.h>
#include "/d/Avenir/include/steed.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"
#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public string *query_yalarochrama_ingredients(object caster);
int is_yalarochrama_restricted(object caster);
object find_steed_for_caster(object caster);

public void config_spell()
{
    ::config_spell();

    set_spell_name("yalarochrama");
    set_spell_desc("Summon a winged steed");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);
    set_spell_time(2); // Time till landing is 20s, way more than the official
                       // casting time of 12s

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(0);
    set_spell_ingredients(query_yalarochrama_ingredients);

    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_CONJURATION, 50);

    set_morgul_rank(24);
}

public string *query_yalarochrama_ingredients(object caster)
{
    return ({ "_ramal_charge" });
}

public void summon_sequence(object caster, object steed, int sequence, float alarmtime) {
    if (is_yalarochrama_restricted(caster)) {
        tell_object(caster, "Your winged steed tries to follow your "
            + "summons but is unable to reach you!\n");
        steed->remove_object();
    }

    switch(sequence) {
        case 2: {
            tell_room(environment(caster), "A dark shape, like a cloud and "
                + "yet not like a cloud, for it moves far too quickly, is "
                + "coming out of the sky, speeding towards you, blocking out "
                + "all light as it approaches.\n");
            environment(caster)->notify_winged_steed_approach(2);
            break;
        }
        case 1: {
            tell_room(environment(caster), "Blind fear mixed with terror and "
                + "deadly cold embrace you as the dark shape draws nearer.\n");
            environment(caster)->notify_winged_steed_approach(1);
            break;
        }
        default: {
            steed->set_last_location(environment(caster));
            steed->move_living("M", environment(caster));
            tell_room(environment(caster), "With a terrible screech a "
                + "huge winged leathery beast descends from the sky and "
                + "lands here!\n", ({ steed, caster }));
            tell_object(caster, "Your winged steed descends from the sky "
                + "and lands here.\n");
            environment(caster)->notify_winged_steed_landing();
            break;
        }
    }

    if (sequence > 0) {
        sequence--;
        set_alarm(alarmtime, 0.0, &summon_sequence(caster, steed, sequence, alarmtime));
    }
}

public void resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    int is_restricted = is_yalarochrama_restricted(caster);
    if (is_restricted) {
        switch (is_restricted) {
        case 1:
            caster->catch_tell("You are unable to summon your steed from "
                + "this location.\n");
            return;
        case 2:
            caster->catch_tell("A power greater than the Dark Lord "
                + "prevents you from summoning your winged steed.\n");
            return;
        case 3:
            caster->catch_tell("You are unable to summon your steed "
                + "while underwater.\n");
            return;
        case 4:
            caster->catch_tell("But your steed is standing right next "
                + "to you.\n");
            return;
        }
    }

    tell_room(environment(caster), QCTNAME(caster) + " begins to "
        + "chant in a horrible, rasping speech and gazes far into the "
        + "distant sky.\n" + capitalize(caster->query_pronoun()) + " lifts "
        + caster->query_possessive() + " arms to the sky and begins a "
        + "keening wail, as if calling to something.\nFar off, storm clouds "
        + "break, and a distant figure appears in the sky.\n", caster);
    caster->catch_tell("Using the power the Dark Lord has bestowed upon "
        + "you, you summon your winged steed with a horrible chant, wailing "
        + "the words \"Yala roch rama\" over and over again. Far off, storm "
        + "clouds break, and a distant figure appears in the sky.\n");

    object steed = find_steed_for_caster(caster);
    if (objectp(steed)) {
        steed->take_off();
    } else {
        setuid();
        seteuid(getuid());
        steed = clone_object(MORGUL_SPELL_OBJ_DIR + "winged_steed");
        steed->set_owner(caster);
        MORGUL_WINGED_STEED_ROOM->register_steed_for_mage(caster, steed);
        steed->move_living("M", MORGUL_WINGED_STEED_ROOM);
    }

    float flight_time = steed->determine_flight_time(environment(steed),
        environment(this_player()));
    float notification_time = flight_time / 3.0;

    set_alarm(notification_time, 0.0, &summon_sequence(caster, steed, 2, notification_time));

    MORGUL_MASTER->increase_activity(caster, ACTIVITY_RARE_SPELL);
}

object find_steed_for_caster(object caster) {
    return MORGUL_WINGED_STEED_ROOM->find_steed_for_mage(caster);
}

int is_yalarochrama_restricted(object caster)
{
    object room = environment(caster);

    if (!room->query_prop(ROOM_I_IS) ||
        (room->query_prop(ROOM_I_INSIDE) &&
        (file_name(room) != AVENIR_PORT_PATH))) {
        return 1;
    }

    if (room->query_prop(ROOM_M_NO_TELEPORT) ||
        room->query_prop(MORGUL_I_NO_SUMMON_STEED)) {
        return 2;
    }

    if ((room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
        (room->terrain_includes_any(TERRAIN_UNDERWATER))) {
        return 3;
    }

    object steed = find_steed_for_caster(caster);
    if (!objectp(steed)) {
        return 0;
    }

    if (room == environment(steed)) {
        return 4;
    }

    return 0;
}
