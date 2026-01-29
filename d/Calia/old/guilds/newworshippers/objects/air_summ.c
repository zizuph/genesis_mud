/*

   An air elemental, summoned by the Worshippers.

   Coded by Bishop of Calia, 04/07/03.

 */

#pragma strict_types

inherit "/std/monster";
inherit "/d/Calia/std/contents_desc"; 
inherit "/d/Genesis/newmagic/spell_effect_object";

#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define COUN_CODE "/d/Calia/worshippers/specials/council_code"

/* 
 * The shout will carry 3 rooms away.
 */
#define SHOUT_DEPTH    3

mapping valid_call = ([ "help" : "Help!", 
                        "greetings" :  "Greetings!",
                        "welcome" : "Welcome!",
                        "bye" : "Farewell!", 
                        "farewell" : "Farewell!" ]); 

object cont_ob;

void create_monster()
{
    string adj;

    adj = ({"vague", "indistinct","willowy","hazy","wispy"})[random(5)];

    add_name("spirit");
    set_race_name("air spirit");
    set_gender(G_NEUTER);
    set_adj(adj);
    set_short(adj + " air spirit");

    set_long("A creature formed from winds and air, this "
        + "spirit is translucent and pale. Wisps of mist "
        + "form what might be strands of hair, billowing out "
        + "in a mad flurry.\n");

    set_m_in("floats in.");
    set_m_out("floats");
    set_mm_in("forms from merging gusts of wind.");
    set_mm_out("explodes in a fury of chaotic winds."); 

    set_alignment(0);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "You're unable to attack the air spirit.\n");
    add_prop(MAGIC_I_RES_AIR, 90);
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

    set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "airy fists");
    set_hitloc_unarmed(0, 5, 100, "airy body");
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
  return "sings in a light, airy voice";
}


void
shout_now(object *exclude, object *search, string what, int c, int max)
{
    int index, size;
    object *rooms; 

    if (SHOUT_DEPTH < 2)
    { 
        return;
    }

    if (c >= max) 
    {  
        return;
    } 

    rooms = FIND_NEIGHBOURS(search[c], SHOUT_DEPTH-1);
    rooms -= exclude; 

    index = -1;
    size = sizeof(rooms); 

    while(++index < size)
    {
        tell_room(rooms[index], "Carried on a strong gust of air, "
            + "an angelic voice sings out: " + what + ".\n");
    }

    exclude += rooms; 
    c++; 
    set_alarm(1.0, 0.0, &shout_now(exclude, search, what, c, max)); 
}


void 
do_shout(string what)
{
    object *rooms;
    object troom;
    int    size;

    if(!(troom = environment(this_object())))
        return 0;

     /* We'll take care of this shout in stages, first let's 
        find the neighbouring rooms of this room to depth 1 */  
    rooms = FIND_NEIGHBOURS(troom, 1);
    size = sizeof(rooms);

    /* Then do a shout from each of those rooms (see shout_now) */ 
    if (size > 1) 
    { 
        command("emote seems to gather strength.\n");
        set_alarm(1.0, 0.0, shout_now(({}), rooms+({}), what, 0, size)); 
    } 

    set_alarm(1.0, 0.0, &tell_room(troom, "Carried on a strong gust of air, "
        + "an angelic voice sings out: " + what + ".\n"));
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

void 
do_call(string what)
{
  object *people = filter(users(), &->is_worship());

  if (!sizeof(people))
  {
      return;
  }
 
  command("emote seems to gather strength.");

  map(people, &->catch_msg("Upon the winds a light, airy voice calls "
      + "out:\n" + break_string(what, 50) + "\n"));
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
    
    /* Shout something over a number of rooms */
    if (sscanf(str, "shout %s", what))
    {
        set_alarm(1.0, 0.0, &do_shout(what));
        return;
    }

    /* Call something out to all Worshippers. */
    if (sscanf(str, "call %s", what)) 
    {
        if (spell_caster->query_wiz_level())
        {
             what += (" (" +capitalize(nm)+")");
             set_alarm(1.0, 0.0, &do_call(what));
             return;
        }
        if (COUN_CODE->is_council_member(nm))
        {
             if (file_name(environment(spell_caster)) == 
                 WOR_TEMPLE+" s_chamber")
             {
                 what += (" (" + capitalize(nm)+")");
                 set_alarm(1.0, 0.0, &do_call(what));
                 return;
             }
       }
       if (stringp(what = valid_call[what])) 
       {   
             what += (" (" + capitalize(nm) + ")");  
             set_alarm(1.0, 0.0, &do_call(what));
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

    spell = clone_object(WOR_OBJECTS + "air_armor.c");

    spell->set_spell_effect_name("Stous");
    spell->set_spell_effect_element(SS_ELEMENT_AIR);
    spell->set_spell_effect_form(SS_FORM_CONJURATION);
    spell->set_spell_effect_power((spell_caster->query_skill(SS_ELEMENT_AIR)+
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
        ", forming a chaotic shield of wind.\n");
    spell_caster->catch_msg(QCTNAME(ob) + " engulfs you, forming a" +
        " chaotic shield of wind!\n");
    
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

    ob->command("emote dissolves into nothing.");
    
    spell_caster->catch_tell("You feel the power of Stous has worn" +
        " off.\n");    
    
    spell_caster->remove_prop(WOR_CREATURE_SUMMONED);
    cont_ob->remove_object();

    remove_spell_effect_object();

    return 1;
}