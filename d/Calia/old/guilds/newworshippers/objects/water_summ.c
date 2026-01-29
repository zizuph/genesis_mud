/*

   A water elemental, summoned by the Worshippers.

   Coded by Bishop of Calia, 04/07/03.

 */

#pragma strict_types

inherit "/std/monster";
inherit "/d/Calia/std/contents_desc"; 
inherit "/d/Genesis/newmagic/spell_effect_object";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"


object cont_ob;

void create_monster()
{
    string adj, *randadj;

    randadj = ({"flowing", "translucent", "shimmering", "watery", "churning"});
    adj = randadj[random(sizeof(randadj))];

    add_name("weird");
    set_race_name("water weird");
    set_gender(G_NEUTER);
    set_adj(adj);
    set_short(adj + " water weird");

    set_long("A vaguely humanoid shaped creature, comprised "+
        "completely of water, with the exception of the eyes "+
        "which are two large aquamarines.\n");

    set_m_in("sloshes in.");
    set_m_out("sloshes");

    set_mm_in("explodes in the room with the fury of a rainstorm.");
    set_mm_out("implodes upon itself and vanishes without a trace.");

    set_alignment(0);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "You're unable to attack the water weird.\n");
    add_prop(MAGIC_I_RES_WATER, 90);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_S_WIZINFO, "This is an elemental that is summoned by" +
        " a member of the Elemental Worshippers of Calia. It should not" +
        " enter into fights. Inquire with guildmaster if you need access" +
        " to the code.\n");       

    set_stats(({20, 80, 80, 10, 10, 20}));

    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_AWARENESS, 50);

    set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "watery arms");
    set_hitloc_unarmed(0, 5, 100, "watery body");
}

public int
start()
{
    set_spell_effect_desc("elemental summons");
    spell_caster->add_prop(WOR_CREATURE_SUMMONED, this_object());          
    cont_ob = clone_object(WOR_OBJECTS + "wor_elem_cont_ob.c");
    cont_ob->set_caster(spell_caster);
    cont_ob->move(spell_caster, 1);
    
    
    set_alarm(1200.0, 0.0, &dispel_spell_effect(spell_caster));
    
    return 1;
}

string race_sound()
{
  return "gargles";
}

void
do_look_exit(string what)
{
    string desc;
    object env, s;

    s = spell_caster;

    command(what); 

    env = environment(this_object()); 
    
    if (objectp(present(s, env))) 
    {   
        command("confused"); 
        return;
    } 

    move_living("X", environment(s)); 

    desc = ("\n" + room_desc(env,1)); 
    if (desc[strlen(desc)-1] == '\n')
    { 
        desc = desc[0..(strlen(desc)-2)]; 
    }

    tell_room(environment(this_object()),QCTNAME(this_object())+
        " whispers something to "+QTNAME(s)+".\n",({s}));
    tell_object(s,"The "+this_object()->short()+" whispers to you:\n"+
        desc+"\n");
}

void catch_question(string str)
{
    string nm = this_player()->query_real_name();
    string what;
    object env;
    
    if(nm != spell_caster->query_real_name())
    {
        return;
    }

    if(!strlen(str))
    {
        command("confused");
        return;
    }

    /* Turns 'ask elemental to say Hello.' -> 'ask elemental say Hello.' */
    sscanf(str, "to %s", str);

    /* Just say something */
    if (sscanf(str, "speak %s", what) || sscanf(str, "say %s", what))
    {
        set_alarm(1.0, 0.0, &command("say " + what));
        return;
    }
    
    sscanf(str, "for %s", str);

    if (str == "decanter")
    {
        if (!present("_worship_decanter_", spell_caster))
        {
            spell_caster->catch_msg(QCTNAME(this_object()) + 
               " hands a glowing decanter to you.\n");
            say(QCTNAME(this_object()) + " hands a glowing decanter"
                + " to " + QTNAME(spell_caster) + ".\n");
            clone_object(WOR_OBJECTS + "decanter.c")->move(spell_caster,1);
            return;
         }
         else
         {
             spell_caster->catch_tell("The water weird won't give you another"+
                 " decanter.\n");
             return;
         }
    }
    
    if (str == "flagon")
    {
        if (!present("_worship_flagon_", spell_caster))
        {
            spell_caster->catch_msg(QCTNAME(this_object()) + 
                " hands a glowing flagon to you.\n");
            say(QCTNAME(this_object()) + " hands a glowing flagon"
                + " to " + QTNAME(spell_caster) + ".\n");
            clone_object(WOR_OBJECTS + "flagon.c")->move(this_player(),1);
            return;
         }
         else
         {
             spell_caster->catch_tell("The water weird won't give you another"+
                 " flagon.\n");
             return;
         }
    }
   
    if (sscanf(str, "look %s", what)) 
    { 
        env = environment(this_object()); 
        if (member_array(what, env->query_exit_cmds()) > -1)
        {
            set_alarm(1.0, 0.0, &do_look_exit(what));
        }
        else
        {
            command("confused");
        }
        return;
    }

    command("confused"); 
}

/*
  This is obviously a variant of make_spell_effect_object. I don't like
  doing it this way, but since this object doesn't have that function, 
  I'm making my own variant in order to set up the elemental armor as 
  a proper spell effect.

 */
public object
make_elemental_armor()
{
    object spell;

    setuid();
    seteuid(getuid());

    spell = clone_object(WOR_OBJECTS + "water_armor.c");

    spell->set_spell_effect_name("Kataraktas");
    spell->set_spell_effect_element(SS_ELEMENT_WATER);
    spell->set_spell_effect_form(SS_FORM_CONJURATION);
    spell->set_spell_effect_power((spell_caster->query_skill(SS_ELEMENT_WATER)+
        spell_caster->query_skill(SS_FORM_CONJURATION) + 35 + 30) / 4);
    spell->set_spell_effect_caster(spell_caster);
    spell->set_spell_effect_target(spell_caster);
    spell_caster->add_magic_effect(spell);

    if (!spell->start())
    {
        spell_caster->catch_tell("Something that wasn't supposed to happen," +
            " happened. This is likely a bug, contact your guildmaster.\n");
        spell = 0;
    }

    return spell;
}

/*
  This is a variant of dispel_spell_effect, instead printing the messages
  and doing what is appropriate when the elemental becomes an armor.
*/
void
become_armor()
{
    object armor;
    object ob = spell_caster->query_prop(WOR_CREATURE_SUMMONED);

    say(QCTNAME(ob) + " suddenly engulfs " + QTNAME(spell_caster) + 
        ", solidifying into a solid ice shield.\n");
    spell_caster->catch_msg(QCTNAME(ob) + " engulfs you, solidifying into a" +
        " solid ice shield!\n");
    
    armor = make_elemental_armor();
    
    if (objectp(armor))
    {
        armor->move(spell_caster);
    }
    
    spell_caster->remove_prop(WOR_CREATURE_SUMMONED);
    cont_ob->remove_object();

    remove_spell_effect_object();
}


varargs public int
dispel_spell_effect(object dispeller)
{
    object ob = spell_caster->query_prop(WOR_CREATURE_SUMMONED);

    ob->command("emote implodes upon itself and vanishes.");
    
    spell_caster->catch_tell("You feel the power of Kataraktas has worn" +
        " off.\n");    
    
    spell_caster->remove_prop(WOR_CREATURE_SUMMONED);
    cont_ob->remove_object();

    remove_spell_effect_object();

    return 1;
}