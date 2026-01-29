
/*
 * synithis_obj.c
 *
 * This is the spell object for the synithis (Summon Familiar) spell for 
 * the Spirit Circle of Psuchae
 * This familiar will allow the Circle member to say, ask or whisper
 * through it for the purpose of quest completion. It will cost the
 * member health and mana each and every time they use any commands
 * through the familiar.
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 *
 * Special thanks to Raven for help with the catch_say, catch_ask, and 
 * catch_whisper commands.
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <options.h>
#include <filter_funs.h>

#include "defs.h"
#include SPIRIT_HEADER

int    st_timer;
string adj, f_type, familiar_desc;
string *adjective = ({"small","tiny","black","white","brown"});
string *type = ({"imp","owl","bat","cat","rat","bird","hawk","eagle"});

void 
create_object()
{
    set_name("_synithis_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_S_WIZINFO,"This is a spell object created by the "+
        "synithis spell of the Spirit Circle of Psuchae.\n");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

public string
show_subloc(string subloc, object me, object observer)
{
    if((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
        (subloc != "_synithis_object"))
            return "";

    return "A "+familiar_desc+" sits on " + ( observer == me ? "your" :
        me->query_possessive() ) + " shoulder.\n";
}

int
do_check_mana()
{
    object ob;

    ob = environment(TO);
    if (ob->query_mana() < 25)
    {
        write("You do not have enough mental power to retain your familiar.\n");
        seteuid(getuid());
        TO->do_dispel(ob);
        return 1;
    }
    ob->add_mana(-25);
    return 1;
}

int
do_dispel()
{
    object ob;
    ob = environment(TO);
    dispel_spell_effect(ob);
    return 1;
}

int
catch_say(int saysto, mixed oblist, string argval)
{
    if (interactive(oblist[0]))
    {
        spell_caster->catch_tell("You psychically send the message to "+ 
            "the " +familiar_desc+" on your shoulder to say to "+
            oblist[0]->query_The_name(spell_caster) + " on your behalf.\n");
        if (spell_caster->query_option(OPT_ECHO))
        {
            spell_caster->catch_tell("The message you sent was: " + 
                argval + "\n");
        }
        oblist[0]->catch_msg(QCTNAME(spell_caster)+" has "+
            spell_caster->query_possessive()+" "+familiar_desc+" on "+
            spell_caster->query_possessive()+" shoulder say to you: "+
            argval+"\n");
        say("The "+familiar_desc+" on "+QTNAME(spell_caster)+"'s shoulder "+
            "says something to "+QTNAME(oblist[0])+".\n",({spell_caster,
            oblist[0]}));
        return 1;
    }

    else
    {
        spell_caster->catch_tell("You psychically send the message to "+
            "the " +familiar_desc+" on your shoulder to say to "+
            oblist[0]->query_The_name(spell_caster) + " on your behalf.\n");
        if (spell_caster->query_option(OPT_ECHO))
        {
            spell_caster->catch_tell("The message you sent was: " + 
                argval + "\n");
        }
        oblist[0]->catch_tell(spell_caster->query_The_name(oblist[0])+
            " says to you: " + argval + "\n");
        say("The "+familiar_desc+" on "+QTNAME(spell_caster)+"'s shoulder "+
            "says something to "+QTNAME(oblist[0])+".\n",({spell_caster,
            oblist[0]}));
        return 1;
    }
}

int
catch_shout(string argval)
{
    spell_caster->catch_tell("You psychically send the message to "+ 
        "the " +familiar_desc+" on your shoulder to shout to "+
        "the room on your behalf.\n");
    if (spell_caster->query_option(OPT_ECHO))
    {
        spell_caster->catch_tell("The message you sent was: " + 
            argval + "\n");
    }
    say("The "+familiar_desc+" on "+QTNAME(spell_caster)+"'s shoulder "+
        "says: "+argval+".\n",({spell_caster}));
    return 1;
}

int
catch_ask(int saysto, mixed oblist, string argval)
{
    if (interactive(oblist[0]))
    {
        spell_caster->catch_tell("You psychically send the message to "+
            "the " +familiar_desc+" on your shoulder to ask from "+
            oblist[0]->query_The_name(spell_caster) + " on your behalf.\n");
        if (spell_caster->query_option(OPT_ECHO))
        {
            spell_caster->catch_tell("The message you sent was: " + 
                argval + "\n");
        }
        oblist[0]->catch_msg(QCTNAME(spell_caster)+" has "+
            spell_caster->query_possessive()+" "+familiar_desc+" on "+
            spell_caster->query_possessive()+" shoulder ask you: "+argval+"\n");
        say("The "+familiar_desc+" on "+QTNAME(spell_caster)+"'s shoulder "+
            "asks something from "+QTNAME(oblist[0])+".\n",({spell_caster,
            oblist[0]}));
        return 1;
    }

    else
    {
        oblist[0]->catch_question(argval);
        spell_caster->catch_tell("You psychically send the message to "+
            "the " +familiar_desc+" on your shoulder to ask from "+
            oblist[0]->query_The_name(spell_caster) + " on your behalf.\n");
        if (spell_caster->query_option(OPT_ECHO))
        {
            spell_caster->catch_tell("The message you sent was: " + 
                argval + "\n");
        }
        say("The "+familiar_desc+" on "+QTNAME(spell_caster)+"'s shoulder "+
            "asks something from "+QTNAME(oblist[0])+".\n",({spell_caster,
            oblist[0]}));
        return 1;
    }


}

int
catch_whisper(int saysto, mixed oblist, string argval)
{
    if (interactive(oblist[0]))
    {
        spell_caster->catch_tell("You psychically send the message to "+
            "the " +familiar_desc+" on your shoulder to whisper to "+
            oblist[0]->query_The_name(spell_caster) + " on your behalf.\n");
        if (spell_caster->query_option(OPT_ECHO))
        {
            spell_caster->catch_tell("The message you sent was: " + 
                argval + "\n");
        }
        oblist[0]->catch_msg(QCTNAME(spell_caster)+" has "+
            spell_caster->query_possessive()+" "+familiar_desc+" on "+
            spell_caster->query_possessive()+" shoulder whisper to you: "+
            argval+"\n");
        say("The "+familiar_desc+" on "+QTNAME(spell_caster)+"'s shoulder "+
            "whispers something to "+QTNAME(oblist[0])+".\n",({spell_caster,
            oblist[0]}));
        return 1;
    }

    else
    {
        spell_caster->catch_tell("You psychically send the message to "+
            "the " +familiar_desc+" on your shoulder to whisper to "+
            oblist[0]->query_The_name(spell_caster) + " on your behalf.\n");
        if (spell_caster->query_option(OPT_ECHO))
        {
            spell_caster->catch_tell("The message you sent was: " + 
                argval + "\n");
        }
        oblist[0]->catch_tell(spell_caster->query_The_name(oblist[0])+
            " whispers to you: " + argval + "\n");
        say("The "+familiar_desc+" on "+QTNAME(spell_caster)+"'s shoulder "+
            "whispers something to "+QTNAME(oblist[0])+".\n",({spell_caster,
            oblist[0]}));
        return 1;
    }
}

public int
start()
{
    int gstat, spirit, spellcraft, conjuration, time;
    int j,k;

    j = random(sizeof(adjective));
    k = random(sizeof(type));
    adj = adjective[j];
    f_type = type[k];

    familiar_desc = adj + " " + f_type;

    gstat = spell_target->query_stat(SS_OCCUP);
    spirit = spell_target->query_skill(SS_ELEMENT_SPIRIT);
    spellcraft = spell_target->query_skill(SS_SPELLCRAFT);
    conjuration = spell_target->query_skill(SS_FORM_DIVINATION);

    time = MAX(600,(gstat + spirit + spellcraft + conjuration + random(200)));
    
    set_spell_effect_desc("familiar");
    spell_target->catch_tell("A "+familiar_desc+" suddenly appears "+
        "on your shoulder.\n");
    say("A "+familiar_desc+" suddenly appears on "+QTNAME(spell_target)+
        "'s shoulder.\n");
    spell_target->catch_tell("You can use the command 'dispel' when you "+
        "wish to send your familiar away.\n");
    spell_target->add_subloc("_synithis_object", TO);
    spell_target->add_prop(SPIRIT_FAMILIAR_SUMMONED,1);
    st_timer = set_alarm(itof(time), itof(time), &do_check_mana());
        
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("The "+familiar_desc+" on your shoulder "+
        "suddenly vanishes.\n");
    say("The "+familiar_desc+" on "+QTNAME(spell_target)+"'s shoulder "+
        "suddenly vanishes.\n");
    spell_target->remove_prop(SPIRIT_FAMILIAR_SUMMONED);
    remove_spell_effect_object();

    return 1;
}

void
init()
{
    ::init();
    add_action("do_dispel","dispel");
}