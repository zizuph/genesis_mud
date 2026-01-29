/* 
   The good calian. 

   Contains the handing out of xp for the sword of light quest. 

   Coded by Glykron 

   History: 
           28/1/2001   weapon of light generalisation, and some
                       minor improvements.                        Maniac 
           31/1/97     given reward :)                            Maniac 
           30/5/96     trig --> emote_hook                        Maniac 
           10/4/96     call_out --> set_alarm                     Maniac 
           26/2/96     sword quest xp modified, more difficult    Maniac 
           25/7/95     orange task for applicants added   Digit &  Maniac 
 */ 

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include "defs.h"
#include "../specials/orange_task.h"
#include RANDOM_HEADER
#include COUNCIL_HEADER
#pragma save_binary

inherit CALIAN;


#define SOLQ_XP 400
#define SOLQ_DOM "Calia"
#define SOLQ_GROUP 0
#define SOLQ_BIT 0

object this;

#define tell_here(string) tell_room(environment(), string, this);


/* 
 * Function:     react_to_weapon 
 * Description:  The npc reacts to being given a weapon of light. 
 * 
 */ 
void 
react_to_weapon(object wep, object donor) 
{
    if (!objectp(donor) || 
        (environment(donor) != environment()) || 
        !objectp(wep)) 
        return; 

    if (wep->query_prop(OBJ_S_ORIGIN_ALIGNMENT) == "good") 
    { 
        command("say Hey! You killed the white calian " + 
                "to get this!!!"); 
        command("unwield " + query_weapon(W_RIGHT)->query_name()); 
        command("wield " + OB_NAME(wep)); 
        command("kill " + OB_NAME(donor)); 
    } 
    else if (wep->query_prop(OBJ_S_ORIGIN_ALIGNMENT) == "evil") 
    { 
        tell_here(QCTNAME(this) + " lays " + LANG_THESHORT(wep) + 
            " upon the altar, and says:\n" + 
            "You have done well.\n" + 
            "She kneels, and then " + LANG_THESHORT(wep) + " disappears.\n"); 
        wep->remove_object(); 
        if (donor->test_bit(SOLQ_DOM, SOLQ_GROUP, SOLQ_BIT))
            write("You don't feel any more experienced, though.\n"); 
        else 
        { 
            write("You feel more experienced.\n"); 
            seteuid(getuid(this_object())); 
            donor->add_exp(SOLQ_XP); 
            donor->set_bit(SOLQ_GROUP, SOLQ_BIT); 
            log_file("wol_quest", donor->query_name() + " " + ctime(time()) + 
                     ".\n"); 
        } 
    }
}


void 
react_to_orange(object orange, object donor) 
{ 
    if (!donor) 
        return; 
    command("say Thank you, I was starving!"); 
    command("emote peels and eats the orange."); 
    orange->remove_object(); 
    seteuid(getuid()); 
    clone_object(TICKET)->move(this_object()); 
    command("give ticket to " + donor->query_real_name()); 
} 


void 
enter_inv(object ob, object from) 
{ 
    ::enter_inv(ob, from); 
    if (living(from) && 
        member_array("_calia_weapon_of_light", ob->query_names()) != -1) 
    { 
        set_alarm(1.0, 0.0, &react_to_weapon(ob, from)); 
    } 
    if (living(from) && 
        member_array(ORANGE_NAME, ob->query_names()) != -1) 
    { 
        set_alarm(1.0,0.0, &react_to_orange(ob, from)); 
    } 
} 


void 
equip_me()
{
    clone_object(WEAPON("blue_sword"))->move(this);
    command("wield sword");
    clone_object(ARMOUR("blue_platemail"))->move(this);
    command("wear platemail");
    MONEY_MAKE_GC(1)->move(this);
}


void 
explain_quest() 
{ 
    command("say Could you get me a weapon of light?"); 
} 


void
create_calian()
{
    if (!IS_CLONE) 
        return; 

    add_name("good_calian"); 
    set_race_name("elf"); 
    set_adj("good"); 
    set_long("The elf is standing by the altar.\n"); 
    set_base_stat(SS_INT, 80); 
    set_base_stat(SS_WIS, 80); 
    set_base_stat(SS_DIS, 80);
    set_base_stat(SS_STR, 80); 
    set_base_stat(SS_DEX, 80); 
    set_base_stat(SS_CON, 80); 
    set_base_stat(SS_OCCUP, 80); 
    set_skill(REWARD, 2); 
    set_skill(SS_WEP_SWORD, 80); 
    set_skill(SS_WEP_POLEARM, 80); 
    set_skill(SS_PARRY, 80); 
    set_skill(SS_DEFENCE, 80); 
    set_all_hitloc_unarmed(query_average_stat() / 4); 
    set_hp(10000); 
    set_alignment(500); 
    set_whimpy(0); 
    set_calian_title("Good Calian"); 
    remove_prop(NPC_M_NO_ACCEPT_GIVE); 
    this = THIS; 
    set_alarm(1.0, 0.0, equip_me); 
}


void 
emote_hook(string emote, object actor, string adverb) 
{ 
    if (emote == "bow") 
        explain_quest(); 
} 
