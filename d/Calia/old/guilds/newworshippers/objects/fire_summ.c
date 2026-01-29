/*

   A fire elemental, summoned by the Worshippers.

   Coded by Bishop of Calia, 02/07/03.

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

   randadj = ({"roaring", "red", "menacing", "terrible"});
   adj = randadj[random(sizeof(randadj))];

   set_name("light-bringer");
   add_name("djinni");
   set_race_name("fire djinni");
   set_gender(G_NEUTER);
   set_adj(adj);
   set_short(adj + " fire djinni");

   set_long("Composed of roaring flames churning about in a chaos "
      + "of fiery tendrils, this creature is not of this world. "
      + "The flames shape and form themselves constantly, but there "
      + "does seem to be a vague resemblance to a humanoid "
      + "figure.\n");

   set_m_in("arrives trailing fire and smoke.");
   set_m_out("leaves");
   set_mm_in("forms from a violent explosion of smoke and flames.");
   set_mm_out("dies out and fades away.");

   set_act_time(10);
   add_act(VBFC_ME("make_flicker"));

   set_alignment(0);

   add_prop(OBJ_I_LIGHT, 2);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_M_NO_ATTACK, "The flames on its body prevent that.\n");
   add_prop(MAGIC_I_RES_FIRE, 90);
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

   set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "fiery hands");
   set_hitloc_unarmed(0, 5, 100, "fiery body");

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
  return "crackles";
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

    spell = clone_object(WOR_OBJECTS + "fire_armor.c");

    spell->set_spell_effect_name("Psotia");
    spell->set_spell_effect_element(SS_ELEMENT_FIRE);
    spell->set_spell_effect_form(SS_FORM_CONJURATION);
    spell->set_spell_effect_power((spell_caster->query_skill(SS_ELEMENT_FIRE) +
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
        ", turning into a flaming shield.\n");
    spell_caster->catch_msg(QCTNAME(ob) + " engulfs you, becoming a flaming" +
        " shield!\n");
    
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

    ob->command("emote dissipates in a puff of smoke and ash.");
    spell_caster->catch_tell("You feel the power of Psotia has worn off.\n");
    
    spell_caster->remove_prop(WOR_CREATURE_SUMMONED);
    cont_ob->remove_object();

    remove_spell_effect_object();

    return 1;
}