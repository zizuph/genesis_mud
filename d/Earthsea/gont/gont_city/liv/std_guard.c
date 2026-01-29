/* 
* Standard guard for Gont Port
*
* Coded by Porta, Dec 97
*/

inherit "/std/monster.c";

#include <macros.h>
#include <defs.h>
#include <ss_types.h>

/* adjlist for the guard */

#define ADJLIST ({"weathered","old","young","muscular",\
"friendly","smiling","tanned","talkative","long-armed",\
"short-legged","broad-shouldered","short","tall",\
"hook-nosed","big-nosed","slender","thin","thin-legged",\
"scarred","long-haired","dark-haired","bald",\
"middle-aged","nimble","blue-eyed","brown-eyed",\
"black-eyed","up-nosed","calm","angry","brown-haired",\
"black-haired","wise","aged","blonde",\
"dark-skinned"})

/* the different weapons */

#define SWORDONE WEP+"/g_sword1.c"
#define SWORDTWO WEP+"/g_sword2.c"
#define SPEAR    WEP+"/g_spear.c"
#define CLUB     WEP+"/g_club.c"
#define AXE      WEP+"/g_axe.c"

/* armours the guard is using */

#define SHIELD   ARM+"/g_shield.c"
#define RINGMAIL ARM+"/g_ringmail.c"
#define HELM     ARM+"/g_helm.c"
#define CLOAK    ARM+"/g_cloak.c"
#define BOOTS    ARM+"/g_boots.c"

void
create_monster()
{
    string adj;
    adj=ADJLIST[random(sizeof(ADJLIST))];

    set_gender(random(1));
    set_adj(({adj,"city"}));
    set_race_name("human");
    set_name("guard");
    set_long("This is a "+adj+" guard hired by the Lord of Gont"+
      " to keep law and order in the city. "+
      capitalize(TO->query_pronoun())+
      " looks confident"+
      " with his weapons and probably is a tough opponent,"+
      " dressed in a shiny ringmail under a white cloak.\n");

    /* set stats, fighter with better con and dex */

    set_stats(({50+random(40),70+random(40),70+random(40),
	50+random(40),50+random(40),50+random(40)}));

    /* skills. want to set weapon skill depending on
    which weapon he uses, so save them for later */

    set_skill(SS_DEFENCE,50+random(30));
    set_skill(SS_PARRY,50+random(30));
    set_skill(SS_AWARENESS,50+random(30));

    /* prevent against see darkness/darkness ;) */

    set_skill(SS_BLIND_COMBAT,60);

    set_chat_time(60);

    add_chat("The Lord of Gont is a wise man!");
    add_chat("Hail Traveller.");
    add_chat("Don't stir up trouble and I will leave"+
      " you alone.");
    add_chat("Don't block the street. Move on!");
    add_chat("The Lord of Gont hired me for ten years");
    add_chat("I will visit the pub tonight");
    add_chat("These Gontish people are so dull.. all"+
      " they care about is their stupid goats");
    add_chat("Once I saw a great wizard");
    add_chat("People from all over the Archipelago visit"+
      " Gont Port for trading.");
    add_chat("What are you looking at?");

    set_act_time(60);

    add_act("peer");
    add_act("emote looks carefully around.");
    add_act("emote straightens "+TO->query_possessive()+
      " back proudly.\n");
    add_act("emote marches around.");
    add_act("emote looks very stern.");
    add_act("smile confi");
    add_act("emote turns "+TO->query_possessive()+" head"+
      " back and forth, scanning the area for criminals.\n");
    add_act("emote salutes you.");
    add_act("poke all");

}

int
attacked_by(object ob)
{
    int p;

    p=random(5);

    if(p==0)
    {
	command("say That was one big mistake!");
	command("grumble angri");
    }

    if(p==1)
    {
	command("emote gets a grim expression in "+TO->query_possessive()+
	  " face.\n");
	command("say Die then!");
    }

    if(p==2)
    {
	command("shout Guards! Guards! To me!");
	command("smile conf");
    }

    if(p==3)
    {
	command("say A brave but dumb decision.");
	command("say I am going to kill you!");
    }

    if(p==4)
    {
	command("emote raises "+TO->query_possessive()+" weapons"+
	  " in defence confidently.");
    }

    if(p==5)
    {
	command("say This troublemaker will die for that!");
	command("cackle confi");
    }

    return 1;
}




void
arm_me()
{
    int which;
    object wep,arm;

    seteuid(getuid(TO));

    which=random(4);

    if(which==0)
    {
	wep=clone_object(AXE);
	TO->set_skill(SS_WEP_AXE,50+random(30));
    }

    if(which==1)
    {
	wep=clone_object(CLUB);
	TO->set_skill(SS_WEP_CLUB,50+random(30));
    }

    if(which==2)
    {
	wep=clone_object(SWORDONE);
	TO->set_skill(SS_WEP_SWORD,50+random(30));
    }

    if(which==3)
    {
	wep=clone_object(SWORDTWO);
	TO->set_skill(SS_WEP_SWORD,50+random(30));
    }

    if(which==4)
    {
	wep=clone_object(SPEAR);
	TO->set_skill(SS_WEP_POLEARM,50+random(30));
    }

    wep->move(TO);
    arm=clone_object(RINGMAIL);
    arm->move(TO);
    arm=clone_object(HELM);
    arm->move(TO);

    if(!which==4)
    {
	arm=clone_object(SHIELD);
	arm->move(TO);
    }

    arm=clone_object(BOOTS);
    arm->move(TO);
    arm=clone_object(CLOAK);
    arm->move(TO);

    command("emote marches in.");
    command("wield all");
    command("wear all");
}

void
do_die(object killer)
{
    int i;

    i=random(5);

    if(i==1)
    {
	command("emote falls to the ground, mortally wounded.");
    }

    if(i==2)
    {
	command("emote draws a final breath and falls to the"+
	  " ground.\n");
    }

    if(i==3)
    {
	command("emote staggers backwards, falling in a lifeless"+
	  " heap on the ground.\n");
    }

    if(i==4)
    {
	command("shout Revenge me comrades!");
	command("emote draws "+TO->query_possessive()+
	  " last breath, slumping to the ground.");
    }

    if(i==5)
    {
	command("scream");
	command("emote drops to the ground.");
    }

    ::do_die();
}
