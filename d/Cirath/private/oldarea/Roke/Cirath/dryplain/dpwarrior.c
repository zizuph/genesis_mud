inherit "/std/monster";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Roke/Cirath/defs.h"


void create_monster()
{
 if(!IS_CLONE)
 return;

    set_name("isiah");
    set_short("warrior");
    set_pshort("warriors");
    set_race_name("human");
    set_gender(1);
    set_adj("big");
    add_adj("muscular");
    set_aggressive(1);
    set_long("An ancient warrior that guards these plains.\n");
    default_config_npc(random(10)+30);
    set_base_stat(SS_STR, 60+random(20));
    set_base_stat(SS_DEX, 60+random(10));
    set_base_stat(SS_CON, 60+random(10));
    set_base_stat(SS_INT, 20+random(5));
    set_base_stat(SS_WIS, 20+random(5));
    set_base_stat(SS_DIS, 80+random(5));
    set_hp(5000);
    set_skill(SS_WEP_SWORD,50+random(10));
    set_skill(SS_WEP_CLUB,40+random(10));
    set_skill(SS_PARRY,90+random(5));
    set_skill(SS_DEFENCE,100+random(10));
    add_prop(CONT_I_HEIGHT,170+random(20));
    add_prop(CONT_I_WEIGHT,65000+random(10000));
    add_prop(CONT_I_VOLUME,50000+random(20000));    
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    set_chat_time(50);
    add_chat("Where is that lazy Ikaros?\n");
    set_act_time(5);
    add_act("hmm");
    add_act("smile coldly");
    add_cact("Brothers, they are attacking me");

}