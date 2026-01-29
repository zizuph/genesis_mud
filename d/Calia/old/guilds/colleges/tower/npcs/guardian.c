/* 
    This is the guardian of the Marble Tower. He is not a mortal, but
    a construct made in an elemental ritual and imbued with intelligence.
    
    He may seem overpowered, but I think the power level is justified 
    considering he is a guild guardian and not intended to be killed.
    
    Bishop of Calia, July 2003.    
*/

#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Calia/std/remember.c";
inherit "/lib/unique.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <options.h>
#include <const.h>
#include <composite.h>

#include "defs.h"

#define LIVE_I_COLLEGE_HUNTED "_live_i_college_hunted"

/* Equips him */

void
equip_me()
{
    object weapon;
    
    setuid();
    seteuid(getuid(TO));
    
    weapon = clone_unique(TOWER_OBJECTS + "guardian_spear", 2, 0, 1, 100);
    
    if (!objectp(weapon))
    {
        return;
    }
    
    weapon->move(TO);
    
    command("wield all");
}


int
special_attack(object enemy)
{
    int i;
    object hunter, target, *enemies;
    
    if (random(5))
    {
        return 0;
    }

    enemies = query_enemy(-1);
    target = enemies[random(sizeof(enemies))];
    
    if (target->query_prop(LIVE_I_COLLEGE_HUNTED))
    {
        return 0;
    }
    
    setuid();
    seteuid(getuid(TO));
    
    target->catch_tell("Lightning flashes across " + 
        LANG_POSS(TO->query_the_name(target)) + " eyes as he stares" +
        " at you.\n");
    tell_room(environment(TO), "Lightning flashes across " + 
        LANG_POSS(QTNAME(TO)) + " eyes as he stares at " + 
        QTNAME(target) + ".\n", target);
    
    hunter = clone_object(TOWER_NPCS + "air_assassin");
    hunter->move_living("X", environment(TO));
    target->add_prop(LIVE_I_COLLEGE_HUNTED, 1);
    set_alarm(300.0, 0.0, &target->remove_prop(LIVE_I_COLLEGE_HUNTED));
    
    hunter->start_hunting(target);
  
    return 1;
}


void
create_monster()
{
    set_name("Myam");
    add_name("myam");
    
    set_title("the Guardian of the Marble Tower");
    
    set_race_name("human");

    set_gender(G_MALE);

    add_adj("massive");
    add_adj("herculean");

    set_long("This tall, powerfully built man has an inflappable" +
        " demeanor. He appears human, but his eyes betray an otherworldly" +
        " origin. They shift constantly, at times meeting his gaze is" +
        " like looking into a furnace, at other times it is like peering" +
        " into the bottomless ocean. He is clean-shaved and bald, and does" +
        " not blink. You doubt you could stand against him in combat.\n");
    
    add_ask(({"tower", "marble tower", "Tower", "Marble Tower"}), "say The" +
        " Marble Tower is my ward. Only students of the elements may enter.",
        1);
    add_ask(({"students", "students of the elements"}), "say Only students" +
        " of the elements may pass.", 1);
    add_ask(({"guild", "join", "joining"}), "say I am not the one to seek" +
        " out about that.", 1);
    add_ask(({"train", "training"}), "say Only students of the elements may" +
        " benefit from my training.", 1);
     
    set_default_answer("emote answers with stoic silence.", 1);    
            
    set_alignment(0);

    set_base_stat(SS_STR, 250);
    set_base_stat(SS_DEX, 300);
    set_base_stat(SS_CON, 300);
    set_base_stat(SS_INT, 200);
    set_base_stat(SS_WIS, 200);
    set_base_stat(SS_DIS, 250);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 200000);
    add_prop(CONT_I_HEIGHT, 200);
    
    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_SEE_INVIS, 10);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_I_RES_MAGIC, 95);
    add_prop(OBJ_I_RES_POISON, 100);
    
    set_all_hitloc_unarmed(70);
    equip_me();
}

string 
race_sound()
{
    return "intones";
}

void
attacked_by(object enemy)
{
    log_file("college_guardian_attacked", "Marble Tower guardian" +
        " was attacked by " + enemy->query_name() + " on " + ctime(time()) 
        + ".\n");
    ::attacked_by(enemy);
}

int 
query_option(int opt)
{ 
    if (opt == OPT_UNARMED_OFF) 
        return 1; 
   
    else return
       ::query_option(opt);
}


public void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    foos -= ({ killer });
    killers = (foos)->query_name();

    log_file("college_guardian_defeated", ctime(time())+
        " College Guardian defeated by "+ 
        killer->query_name() +"("+ killer->query_average_stat() +") "+ 
        (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo")+".\n");
    ::do_die(killer);

}
