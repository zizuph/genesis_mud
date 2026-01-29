/*
  This is the spell object for the light spell the Fire College
  uses. 

  Coded by Bishop of Calia, June 2003.

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/d/Calia/guilds/colleges/specials/common_functions";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "defs.h"

varargs public int dispel_spell_effect(object dispeller);

int potency, dispelalarm;

string
extra_desc()
{
    if (TP == spell_caster)
    {
        return " To see what you can do with the efreet," +
            " type <efreethelp>.";
    }
    else
    {
        return "";
    }
}

public int
start()
{
    int stat = find_controlling_stat("fire", spell_caster);
  
    potency = min(30 + (random(stat) + random(stat))/4, 80);

    set_spell_effect_desc("fire efreet");
    
    spell_caster->catch_tell("As you finish your summoning ritual," +
        " a flickering flame materalizes over your outstretched" +
        " palm. The flame grows and begins to look unstable, finally" +
        " exploding, leaving a tiny being of fire and smoke!\n");
    tell_room(environment(spell_caster), "As "+  QTNAME(spell_caster) +
        " finishes " + spell_caster->query_possessive() + " ritual" +
        ", a flickering flame materializes over " + 
        spell_caster->query_possessive() + " outstreched palm. The" +
        " flame grows and begins to look unstable, finally" +
        " exploding, leaving a tiny being of fire and smoke!\n", 
        spell_caster);
  
    dispelalarm = set_alarm(itof(potency*20), 0.0, dispel_spell_effect);

    return 1;
}


void
create_object()
{
    string adj1;

    set_name("efreet");
    add_name("_college_messenger_efreet_");

    adj1 = (({"roaring", "cruel", "vicious", "playful",
              "malevolent", "howling"})[random(6)]);
    add_adj("flaming");
    add_adj(adj1);
    
    set_short(adj1 + " " + "flaming efreet"); 

    set_long("It's a ferocious efreet, a small creature which appears" +
       " to be composed of only flames and smoke!@@extra_desc@@\n");

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, "The efreet isn't very cooperative with" +
        " your efforts to drop it.\n");
    add_prop(OBJ_M_NO_INS, "You'd have to catch it first.\n");
}

void
efreet_return_caster(int i)
{
    if (i)
    {
        spell_caster->catch_tell("The " + TO->query_short() + 
            " returns, having delivered your message.\n");
    }
    else
    {
        spell_caster->catch_tell("The " + TO->query_short() +
            " returns, unsuccessful in delivering the message.\n");
    }
        
    tell_room(environment(spell_caster), "A " + TO->query_short() +
        " arrives, streaking towards " + QTNAME(spell_caster) +
        ".\n", spell_caster);
    TO->move(spell_caster);
}

void
deliver_message(object target, string str)
{
    string name;

    if ((!(objectp(target) && interactive(target))) || 
        environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        set_alarm(10.0, 0.0, &efreet_return_caster(0));
        return;
    }

    if(target->query_met(spell_caster))
    {
        name = LANG_POSS(spell_caster->query_name()); // Met? -> 'Bishop's'
    }
    else
    {
        name = LANG_ADDART(spell_caster->query_gender_string()) + " " +
           spell_caster->query_race_name(); // Unmet? -> 'a male human'
    }
    
    
    target->catch_tell("A " + TO->query_short() + " streaks in," +
        " whispering the following message to you in a harsh and" +
        " jarring imitation of " + name + " voice: " + str + "\n" +
        "The efreet then streaks away, disappearing as quickly as" +
        " it came.\n");
        
    tell_room(environment(target), "A " + TO->query_short() + 
        " streaks in, moving up to " + QTNAME(target) + ". It" +
        " whispers something to " + target->query_objective() +
        ", then streaks off and disappears.\n", target);
    
    set_alarm(10.0, 0.0, &efreet_return_caster(1));
}


void
do_efreet_damage(object target, int i)
{
    string how;
    int thisdamage;
    
    if (!objectp(target) || target->query_ghost())
    {
       dispel_spell_effect();
       return;
    }    
    
    if (environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        target->catch_tell("The efreet screams loudly!\n");
        dispel_spell_effect();
        return;
    }         
    
    
    thisdamage = potency;
    thisdamage -= target->query_magic_res(MAGIC_I_RES_FIRE) * 
        thisdamage/100;
    thisdamage -= target->query_magic_res(MAGIC_I_RES_MAGIC) * 
        thisdamage/100;
        
    thisdamage = random(thisdamage) + random(thisdamage);
        
    
    switch(thisdamage)
    {
        case 0:
            how = "not doing any harm at all";
            break;
        case 1..20:
            how = "leaving a couple of minor burn marks";
            break;
        case 21..60:
            how = "leaving a few charred burn wounds";
            break;
        case 61..120:
            how = "leaving several ugly burn wounds";
            break;
        default:
            how = "leaving many ghastly burn wounds";
            break;
    }    
 
    target->heal_hp(-thisdamage);

    if (target->query_hp() <= 0)
    {
        target->catch_tell("The " + TO->query_short() + 
            " darts around you, striking from several directions." +
            " The combined pain and damage from all the wounds inflicted" +
            " cause you to topple to the ground and lose consciousness.\n");
        tell_room(environment(target), "The " + TO->query_short() +
            " darts around " + QTNAME(target) +
            ", striking at " + target->query_objective() + " from" +
            " several directions. The combined weight of all the wounds" +
            " inflicted causing " + target->query_objective() + " to" +
            " topple to the ground.\n", target);

        target->do_die(TO);
        dispel_spell_effect();

        return;

    }
    else
    {
        target->catch_tell("The " + TO->query_short() +
            " darts around you, striking at you from several" +
            " directions, " + how + ".\n");
        tell_room(environment(target), "The " + TO->query_short() +
            " darts around " + QTNAME(target) +
            ", striking at " + target->query_objective() + " from" +
            " several directions, " + how + ".\n", target);
    }

    if (i > potency/4)
    {
        dispel_spell_effect();
    }
    else
    {
        i++;
    }
    
    set_alarm(itof(12 + random(5)), 0.0, &do_efreet_damage(target, i));
}

int
efsic(string str)
{
    string *words;
    object *targets = PARSE_THIS(str, "[at] / [on] [the] %l");
    
    if (!sizeof(targets))
    {
        NF("Sic your efreet at who?\n");
        return 0;
    }
    if (sizeof(targets) > 1)
    {
        NF("You can only sic your efreet at one target!\n");
        return 0;
    }
    if (targets[0]->query_prop(OBJ_M_NO_ATTACK) || 
        targets[0]->query_prop(OBJ_M_NO_MAGIC_ATTACK))
    {
        NF("Your efreet refuses to attack that target!\n");
        return 0;
    }
    
    
    remove_alarm(dispelalarm);

  
    spell_caster->catch_tell("You sic the " + TO->query_short() +
        " at " + targets[0]->query_the_name(spell_caster) + 
        "! It speeds towards its target, attacking relentlessly!\n");
    targets[0]->catch_tell(spell_caster->query_The_name(targets[0]) +
        " sics " + spell_caster->query_possessive() + " " +
        TO->query_short() + " at you! It speeds toward you," +
        " attacking relentlessly!\n");
    tell_room(environment(targets[0]), QCTNAME(spell_caster) + 
        " sics " + spell_caster->query_possessive() + " " +
        TO->query_short() + " at " + QTNAME(targets[0]) + "!" +
        " It speeds towards its target, attacking relentlessly!\n",
        ({targets[0], spell_caster}));        

    TO->move(targets[0], 1);    

    if (objectp(TO))
    {  
        targets[0]->add_subloc("_college_attacking_efreet_", TO);
    
        set_alarm(1.0, 0.0, &do_efreet_damage(targets[0], 0));
    }
    
    return 1;
}


public string
show_subloc(string subloc, object me, object observer)
{
    object *spirits;

    spirits = filter(all_inventory(me), &operator(==)("efreet") @
        &->query_name()); 
        
    if (subloc != "_college_attacking_efreet_")
    {
        return me->show_subloc(subloc, me, observer);
    }        
    
    if (!sizeof(spirits))
    {
        return "";
    }

    if ((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)))
            return "";

    return capitalize( observer == me ? "you" : me->query_pronoun() ) + 
        " " + (observer == me ? "are" : "is") + " being harrassed and" +
        " tormented by " + COMPOSITE_ALL_DEAD(spirits) + ".\n";
}

int
efhelp(string str)
{
    write("These two actions are possible with the efreet:\n" +
        "efsend <target> <message> - the efreet finds someone who" +
        " is in the Realms, and delivers a message from you.\n" +
        "efsic <target> - you sic the efreet on a target in this" +
        " room, causing it to attack.\n");

    return 1;
}


int 
efsend(string str)
{
    string *words; 
    object target; 

    if (!str)
    {
        NF("Send the efreet where?\n");
        return 0;
    }
    
    words = explode(str, " ");
    target = find_living(lower_case(words[0]));

    if (objectp(target))
    {
        if (!(spell_caster->query_met(target)))
        {
            NF("You know no such person.\n");
            return 0;
        }
        if (target->query_wiz_level() && target->query_invis())
        {
            NF("Your cannot send to that target.\n");
            return 0;
        }
        if (sizeof(words) < 2)
        {
            NF("What message do you wish to send?\n");
            return 0;
        }
        if (present(target, environment(spell_caster)))
        {
            NF("The efreet refuses to deliver a message to someone" +
                " in the same room.\n");
            return 0;
        }
        
        spell_caster->catch_tell("You whisper the message to the " +
            TO->query_short() + ". It streaks away to" +
            " deliver your missive.\n");
        tell_room(environment(spell_caster), QCTNAME(spell_caster) +
            " whispers something to a " + TO->query_short() + ", and" +
            " it streaks off, trailing smoke.\n", spell_caster);
        TO->move(TEMP_ROOM, 1);
        
        set_alarm(20.0, 0.0, &deliver_message(target, 
            implode(words - ({words[0]}), " ")));
            
        return 1;
    }
    else
    {
        NF("You know no such person.\n");
        return 0;
    }
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object ob = environment(TO);

    if (ob == spell_caster)
    {
        spell_caster->catch_tell("The " + TO->query_short() + " returns" +
            " to the Plane of Fire, leaving behind only smoke behind.\n");      
    }
    else 
    if (!living(ob))
    {
        spell_caster->catch_tell("The " + TO->query_short() + " has" +
            " returned to the Plane of Fire\n");
    }
    else 
    if (ob->query_ghost())
    {
        tell_room(environment(ob), "The " + TO->query_short() + 
            ", having done its" +
            " job, disappears in a puff of smoke.\n");
    }
    else 
    {
        ob->catch_tell("The " + TO->query_short() + " that" +
            " has been tormenting you disappears in a puff of smoke.\n");
        tell_room(environment(ob), "The " + TO->query_short() +
            " tormenting " + QTNAME(ob) + " disappears" +
            " in a puff of smoke.\n", ob);
    }
    
    remove_spell_effect_object();

    return 1;
}

void
enter_env(object dest, object old)
{
    object *efreets;

    efreets = filter(all_inventory(dest), 
        &operator(==)("efreet") @ &->query_name());
        
    if (dest == spell_caster && sizeof(efreets) > 1)
    {
        spell_caster->catch_tell("The " + efreets[0]->query_short() +
            " and " + efreets[1]->query_short() + " immediately" +
            " begin to fight! The newcomer is defeated, and" +
            " returns to the Plane of Fire.\n");
        tell_room(environment(spell_caster), "The arriving efreet" +
            " immediately begins to fight with another efreet in " +
            LANG_POSS(QTNAME(spell_caster)) + " possession! The" +
            " newcomer is defeated, disappearing in a puff of smoke.\n", 
            spell_caster);
            
        TO->remove_object();
    }    
    else
    if (sizeof(efreets) > 1)
    {
        dest->catch_tell("The " + efreets[0]->query_short() +
            " and " + efreets[1]->query_short() + " immediately" +
            " begin to fight! The newcomer is defeated, and" +
            " disappears in a puff of smoke.");
        tell_room(environment(dest), "The arriving efreet" +
            " immediately begins to fight with the efreet that" +
            " is currently harassing " + QTNAME(dest) + "! The" +
            " newcomer is defeated, disappearing in a puff of smoke.\n", 
            dest);
            
        TO->remove_object();
    }
        
    ::enter_env(dest, old);
}
        

void
init()
{
    ::init();
    
    if (environment(TO) == spell_caster)
    {
        add_action(efsic, "efsic");
        add_action(efsend, "efsend");
        add_action(efhelp, "efreethelp");
    }
}