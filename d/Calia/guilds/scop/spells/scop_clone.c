#pragma strict_types

inherit "/std/monster";
#include <macros.h>

#define HIM(x) ((x)->query_objective())
#define HE(x)  ((x)->query_pronoun())
#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"

object sleeping_scop;
int player_check_alarm;

string normal_short;


string short_descr()
{
    string scop_name = sleeping_scop->query_real_name();
    if(this_player()->query_met(scop_name))
    {
        return capitalize(scop_name+" sleeping soundly");
    }
    return normal_short;
}

void
create_monster()
{
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_short(short_descr);
}

private void
destruct_me(object me)
{
  remove_alarm(player_check_alarm);
  me->remove_object();
}


void
set_nshort(string str)
{
    normal_short = str;    
}

private void safety_check(object scop, object me)
{
    if(!objectp(scop) ||
       scop->query_prop(PLAYER_S_LD_IN_ROOM) ||
       !present("_oneiro_ob_", scop))
    {
        remove_alarm(player_check_alarm);
        player_check_alarm = 0;
        destruct_me(me);
    }
}

public void set_cleric(object scop)
{
    sleeping_scop = scop;
    player_check_alarm = set_alarm(2.0, 2.0, &safety_check(scop, this_object()));  
}

public void
attacked_by(object ob)
{
    object spell_object;

    ob->catch_msg("As you attack the "+QTNAME(sleeping_scop) +
                  " "+HE(sleeping_scop)+" awakens abruptly.\n");
    tell_room(environment(ob), QCTNAME(sleeping_scop)+" wakes up " +
              "aruptly as "+QTNAME(ob)+" attacks "+HIM(sleeping_scop) +
              ".\n", ({ob, sleeping_scop}));
    sleeping_scop->catch_tell("You awaken aruptly as someone attacks you.\n");
    sleeping_scop->catch_tell("You feel somewhat out of it as you come to.\n");
    spell_object = present("_oneiro_ob_", sleeping_scop);
    if(!spell_object)
    {
      sleeping_scop->catch_tell("Your clone was attacked, but you didn't " +
                                "have your oneiro object in you, please " +
                                "report this to your guild master.\n");
      return;
    }  
    set_alarm(0.0, 0.0, &destruct_me(this_object()));
    spell_object->dispel_spell_effect(ob, 0);
    ob->attack_object(sleeping_scop);
    sleeping_scop->add_attack_delay(15, 0);
    return;
}

public void
attack_object(object ob)
{
    object spell_object;

    spell_object = present("_oneiro_ob_", sleeping_scop);
    if(!spell_object)
    {
      sleeping_scop->catch_tell("Your clone was forced to attack " +
                                "something, but your oneiro object " +
                                "wasn't present in you. "+
                                "please report this to your guild master.\n");
      return;
    }  
    set_alarm(0.0, 0.0, &destruct_me(this_object()));
    spell_object->dispel_spell_effect(ob, 0);
    tell_room(environment(ob), QCTNAME(sleeping_scop)+" is startled " +
              "and wakes up.\n", sleeping_scop);
    sleeping_scop->catch_tell("You feel startled and wake up.\n");
    sleeping_scop->catch_msg("You attack "+QTNAME(ob)+".\n");
    sleeping_scop->attack_object(ob);
    return;
}

public void 
enter_inv(object ob, object from)
{
    object spell_object;

    tell_room(environment(ob), QCTNAME(sleeping_scop)+" is startled by " +
              "something and wakes up.\n", sleeping_scop);
    sleeping_scop->catch_tell("You feel startled by something and wake up.\n");

    spell_object = present("_oneiro_ob_", sleeping_scop);
    if(!spell_object)
    {
      sleeping_scop->catch_tell("An object entered your clone, but your " +
                                "oneiro object wasn't present in you. "+
                                "Please report this to your guild master.\n");
      return;
    }  
    set_alarm(0.0, 0.0, &destruct_me(this_object()));
    spell_object->dispel_spell_effect(ob, 0);
    ob->move(sleeping_scop, 1);
    return;
}
