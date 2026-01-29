/*
    Dargaard Keep, Bakaris Lieutenant of the Blue Dragonarmy.

    bakaris.c
    =========
    Coded by: Alustrial, with lots of help from Xarguul, Rastlin, 
    95/9/12   and Jeremiah. Based on Jeremiah's code nightbringer.c

    Updated : Lots so far, and probably lots more in the near future.
 
    Bakaris is the Lieutenant of the Blue Dragonarmy, and will be
    the biggest npc in Dargaard Keep, aside from Lord Soth. 
*/


#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
inherit M_FILE

void
create_krynn_monster()
{
    set_race_name("human");
    set_name("Bakaris");
    set_adj(({"handsome","blonde-haired"}));
    set_title("Lieutenant of the Blue Dragonarmy");
    add_name(({"bakaris","lieutenant"}));
    set_gender(0);
    set_stats(({180,230,200,120,100,140}));
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 120);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 80);
    set_alignment(-3000);
    set_act_time(5);
    add_act("emote slams his mailed fist down upon the table.");
    add_act("emote growls in anger.");
    add_act("emote mumbles: Where is she...");
    add_act("emote paces impatiently about the room");
    set_cact_time(4);
    add_cact("glare all");
    add_cact("emote grits his teeth, despite his injuries.");
    add_cact("laugh coldy");
    set_chat_time(9);
    add_chat("What business do you have here?");
    add_chat("What do you want?");
    add_chat("Get out of here, before I throw you out!");
    set_cchat_time(5);
    add_cchat("Fool! Now you will die.");
    add_cchat("Why do you even persist? You have no chance");
    set_alarm(0.0,0.0,"arm_me");
    trig_new("%w 'introduces' %s", "react_intro");
}


arm_me()
{
    clone_object("/d/Krynn/dargaard/weapon/baksword")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/bdragonarm")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/bshinguard")->move(TO);
    
    command("wear all");
    command("wield all");
}

int react_intro(string who)
{
    if (who)
    {
        who = lower_case(who);
        if(find_player(who))
        {
            set_alarm(3.0,0.0,"return_intro", who);
        }
        return 1;
    }
}

void return_intro(string who)
{
    command("glare coldly " + who);
    set_alarm(1.0,0.0,"command","say I care nothing for your identity?");
    set_alarm(1.5,0.0,"command","say But you would do well to remember "+
        "mine...");
    set_alarm(3.0,0.0,"command","emote draws himself to his full "+
        "height, and throws his cape over his shoulder.");
    set_alarm(3.5,0.0,"command","introduce me");
}

void do_die( object killer )
{

   int i;

   set_alarm(0.0,0.0,"command","glare angrily "+ killer->query_real_name());
   set_alarm(1.0,0.0,"command","say You think you can so easily defeat a "+
       "servant of the Dark Queen?");
   set_alarm(1.5,0.0,"command","laugh coldly " + killer->query_real_name());
   set_alarm(2.5,0.0,"command","emote slumps to the floor and stiffens.");
   set_alarm(3.0,0.0,"command","emote curses violently.");
   set_alarm(4.0,0.0,"command","say Bah! Betrayed in the end...");
   set_alarm(5.0,0.0,"command","sigh .");
   
   for(i=0;i<8000;i++) ;
   ::do_die(killer);
}
