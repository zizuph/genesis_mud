/*
 * /d/Cirath/altaruk/npc/alt_guard.c
 *
 * Guards in Altaruk. A work in progress.
 * Has different armours for male and female.
 *
 * Azazel
 */
 
inherit "/d/Cirath/std/monster";
#include <macros.h>
#include <ss_types.h>
#include <const.h>
#include <stdproperties.h>
#include "/d/Cirath/common/teamfnc.h"
#include "../defs.h"

#define W_PATH ALT_WEP
#define WEAPON ({ W_PATH + "halberd_tmp", W_PATH + "sword_tmp", \
               W_PATH + "spear_tmp"})
#define R_PATH ({ALT_STR, ALT_SQU})

#define ARM0 ALT_ARM + "helm_tmp.c"
#define ARM1 ALT_ARM + "greaves_tmp.c"
#define ARM2 ALT_ARM + "boots_tmp.c"
#define ARM3 ALT_ARM + "bracers_tmp.c"
#define ARM4 ALT_ARM + "m_mail_tmp.c"
#define ARM5 ALT_ARM + "f_mail_tmp.c"

int  *randgender;
string *randadj, *randrace;

create_monster()
{

    int i;
    
    randgender = ({0,0,0,1});
    randadj = ({ "protective", "guarding", "watching", "attentive" });
    randrace = ({ "human", "human", "dwarf" });
    
    set_name("guard");
    add_name(({"soldier","mercenary"}));
    set_race_name(randrace[random(sizeof(randrace))]);
    set_adj(randadj[random(sizeof(randadj))]);
    add_adj("town guard");
    set_gender(randgender[random(sizeof(randgender))]);
    set_alignment(200-random(300)); 
    set_long("This mercenary is on guard duty. \n");

    for (i = 0 ; i < 6 ; i++)
        set_base_stat(i , 140 + random(60));

    set_skill(SS_WEP_SWORD, 60 + random(20));
    set_skill(SS_WEP_POLEARM, 60 + random(20));
    set_skill(SS_DEFENCE, 60 + random(20));
    set_skill(SS_PARRY, 40 + random(20));
    set_skill(SS_BLIND_COMBAT, 40 + random(10));
    set_skill(SS_AWARENESS,70);

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    refresh_mobile();
    set_random_move(8,0); 
    set_restrain_path(R_PATH);
    set_assist_cry("No one gets killed on my watch fool!");
    set_default_answer("Hey! Go sleep it of somewhere else.\n");
      
    set_act_time(10);
        add_act("sniff.");
        add_act("cough");
        add_act("emote twiches nervously.");   
        add_act("emote looks around for trubble.");  
        add_act("sigh");
        add_act("frown");

    set_chat_time(20);  
        add_chat("What do you want?");
        add_chat("What are you looking at?");
        add_chat("Wonder in if gates will be safe tonight.");
        
    set_cact_time(5);
        add_cact("sneer");   
        add_cact("grimace");
        add_cact("grin");
        add_cact("emote says: You want to mess with me, eh?");
        add_cact("emote says: I'l have your head for this!");

}


void
arm_me()
{
 
      object arm, wep;
      int tmp;
      seteuid(getuid(this_object()));
      tmp = sizeof(WEAPON);
      wep = clone_object(WEAPON[random(tmp)]);
      wep->move(this_object());
      command("wield all");

    if (this_object()->query_gender() == 0)
    clone_object(ARM4)->move(this_object());
    else
    clone_object(ARM5)->move(this_object());
    clone_object(ARM0)->move(this_object());
    clone_object(ARM1)->move(this_object());
    clone_object(ARM2)->move(this_object());
    clone_object(ARM3)->move(this_object());
        command("wear all");
}
