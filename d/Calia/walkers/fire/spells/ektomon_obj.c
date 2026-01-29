/*

Ektomon object, by Bishop of Calia, 23.6.99.

*/

#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <filter_funs.h>
#include <defs.h>

varargs public int dispel_spell_effect(object dispeller);
public void set_power();
public void do_ektomon_damage();

int times, power;
string room_long, new_room_long;
object target_room;


void 
create_object()
{
    set_name("_ektomon_obj_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
}

public int
start()
{
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    set_spell_effect_desc("Hellscape");

    target_room = environment(spell_caster);
    room_long = target_room->query_long();
    new_room_long = room_long;
    new_room_long += "A red haze lies over this area, emanating a suffocating"+
       " heat.\n";
 
    target_room->set_long(new_room_long);

    set_power();
    set_alarm(itof(12 + random(7)), 0.0, &do_ektomon_damage());

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    target_room->set_long(room_long);

    tell_room(target_room, "The red haze slowly dissipates, returning the" +
       " area to its natural temperature.\n");

    remove_spell_effect_object();

    return 1;
}

public void set_power()
{
    power = spell_caster->query_stat(SS_OCCUP) + 
        spell_caster->resolve_task(TASK_DIFFICULT, ({ SKILL_WEIGHT,
        75, TS_OCC, SKILL_END, SKILL_WEIGHT, 25, TS_WIS, SKILL_END, SKILL_AVG,
        SS_FORM_ENCHANTMENT, SS_ELEMENT_FIRE, SKILL_END}));
    power = min(max(power, 100), 200);
    times = min(power/10, 14 + random (3)); 

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_msg("Spell will deal up to " + power + " damage, "+
            (times + 1) + " times.\n");
    }
}

public void 
do_ektomon_damage()
{
    int i, thispower;
    object *targets;
    string *exits;

    targets = FILTER_LIVE(all_inventory(target_room));
    
    for (i = 0 ; i < sizeof(targets) ; i++)
    {
        if (targets[i]->query_wiz_level() || 
            targets[i]->query_magic_res(MAGIC_I_RES_FIRE) >= 40 ||
            targets[i]->query_magic_res(MAGIC_I_RES_FIRE) +
            targets[i]->query_magic_res(MAGIC_I_RES_MAGIC) >= 50 || 
            target_room->query_prop(ROOM_M_NO_ATTACK) ||
            targets[i]->query_prop(OBJ_M_NO_ATTACK) &&
            environment(targets[i]) == target_room)
        {
            targets[i]->catch_msg("The intense heat here makes you slightly" +
                " uncomfortable, but you shrug it off.\n");
        }
        else
        if (target_room == environment(targets[i]))
        {
            thispower = power;
            thispower -= targets[i]->query_magic_res(MAGIC_I_RES_FIRE) * 
                (thispower/100);
            thispower -= targets[i]->query_magic_res(MAGIC_I_RES_MAGIC) * 
                (thispower/100);

            targets[i]->heal_hp(-(thispower/2) - random(thispower/2));

            if (targets[i]->query_hp() <= 0)
            {
                targets[i]->catch_msg("The heat here brings you to your" +
                    " knees. You clutch your chest, feeling your heart" +
                    " slowing... and finally, stopping.\n");
                tell_room(environment(targets[i]), QCTNAME(targets[i]) +
                    " falls to " + targets[i]->query_possessive() +
                    " knees. " + capitalize(targets[i]->query_pronoun()) +
                    " clutches " + targets[i]->query_possessive() + 
                    " chest and falls lifeless to the ground a few moments" +
                    " later.\n", targets[i]);
                targets[i]->do_die();
            }
            else
            if (targets[i]->query_npc() && !random(3))
            {
                exits = environment(targets[i])->query_exit_cmds();
                
                tell_room(environment(targets[i]), QCTNAME(targets[i]) +
                    " looks like " + targets[i]->query_pronoun() + " wants" +
                    " to leave this place.\n");
                targets[i]->command(exits[random(sizeof(exits))]);
            }
            else
            {
                targets[i]->catch_msg("The intense heat here drains your" +
                    " health.\n");
            }
        }
    }

    times--;

    if (times >= 0)
    {
        set_alarm(itof(12 + random(7)), 0.0, &do_ektomon_damage());
    }
    else
    {
        dispel_spell_effect();
    }
}



