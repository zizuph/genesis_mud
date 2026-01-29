/*
 * farmer2.c
 * By Skippern
 *
 * With Sterns servent.c and merged_soldier.c as examples and good
 * help from Rohim and Mrpr.
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";     /* for humanoid monsters */
inherit "/std/act/action";  /* make it do things */
inherit "/std/act/chat";    /* make it talk */
inherit "/std/act/domove";  /* make it walk */

#include "../erech.h"     /* for Erech definitions */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>

#define FARM_ADJ1  ({ "sturdy", "humble", "noble", "tanned" })
#define FARM_ADJ2  ({ "black-haired", "dark-haired", "bald", \
                        "brown-haired", })

#define F_GENDER        one_of_list(G_MALE, G_FEMALE)
#define F_ALIGN         200 + random(500)
#define MY_HEIGHT       150 + random(31)
#define MY_WEIGHT       1200 + random(200)
#define MY_VOLUME       MY_WEIGHT - 50 + random(100)

//#define F_TYPE          ({ "gatherer", "shepard", "harvester" })

#define F_SS_MAX        60 + random(40)
#define F_SS_MID        40 + random(40)
#define F_SS_MED        30 + random(30)
#define F_SS_MIN        10 + random(10)

#define F_STR           50 + random(25)
#define F_DEX           160 + random(50)
#define F_CON           20 + random(100)
#define F_WIS           30 + random(180)
#define F_INT           30 + random(180)
#define F_DIS           180 + random(25)


/* Prototypes */
public void          create_monster();
public void          equip_em();

/*
 * Function name:    create_monster()
 * Definition   :    Creates the monster
 *
 * Remember     :    The `int' should be the first commands executed within
 *                   this function, since executing this command later is
 *                   illigal according to normal C codes and also for LPC.
 */
public void
create_monster()
{

    set_race_name("human");
    set_name("homer");
    set_living_name("_farmer_of_erech_farm_");
    set_long("You are looking upon a gondorian farmer.\n");
    
    set_adj(one_of_list(FARM_ADJ1));
    add_adj(one_of_list(FARM_ADJ2));
  
    set_gender(F_GENDER);
    set_alignment(F_ALIGN);
  
    add_prop(CONT_I_HEIGHT, MY_HEIGHT);
    add_prop(CONT_I_WEIGHT, MY_WEIGHT);
    add_prop(CONT_I_VOLUME, MY_VOLUME);
    add_prop(LIVE_I_MAX_DRINK, 100);
    add_prop(LIVE_I_MAX_EAT, 100);

    set_act_time(24);
    add_act("ponder");
    add_act("emote scouts the horizon for his herds.");
    set_cact_time(4);
    add_cact("emote kicks and screams fanatically.");
    add_cact("knee enemy");
    add_cact("kick enemy");
    add_cact("slap enemy");
    set_cchat_time(6);
    add_cchat("Now you have made a REAL mess of it!");
    set_chat_time(15);
    add_chat("The grain harvest last autumn was pure, I hope the next gets " +
	"better.");

    set_random_move(8, 0);
    set_restrain_path(E_FARM);

    set_skill(SS_ACROBAT, F_SS_MAX);
    set_skill(SS_HERBALISM, F_SS_MAX);
    set_skill(SS_AWARENESS, F_SS_MAX);
    set_skill(SS_DEFENCE, F_SS_MAX);
    set_skill(SS_PARRY, F_SS_MAX);
    set_skill(SS_HUNTING, F_SS_MED);
    set_skill(SS_ANI_HANDL, F_SS_MID);
  
    set_base_stat(SS_STR, F_STR); 
    set_base_stat(SS_DEX, F_DEX); 
    set_base_stat(SS_CON, F_CON);
    set_base_stat(SS_WIS, F_WIS);
    set_base_stat(SS_INT, F_INT);
    set_base_stat(SS_DIS, F_DIS); 
  
    equip_em();

}


public void
equip_em()
{
    object wep, arm, item;

    wep = clone_object(E_OBJ + "f_rake");
    wep->move(this_object());
    command("wield all");
    arm = clone_object(E_OBJ + "f_jacket");
    arm->move(this_object());
    arm = clone_object(E_OBJ + "f_trousers");
    arm->move(this_object());
    command("wear all");

    MONEY_MAKE_CC(random(30))->move(this_object());
}

