/*
 * morthec.c
 * By Skippern
 *
 * With Sterns servent.c and merged_soldier.c as examples and good
 * help from Rohim and Mrpr.
 *
 * The alignment is set to be 230. This is 
 * becouse of their role in the War of the Ring.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";        /* for humanoid monsters */
inherit "/std/act/action";     /* make it do things */
inherit "/std/act/chat";       /* make it talk */
inherit "/lib/unique.c";       /* for unique cloning */

#include "../erech.h"          /* for Erech definitions */

inherit E_LIB + "npc.c";       /* standard reactions */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define MY_HEIGHT       150 + random(31)
#define MY_WEIGHT       200 + random(1200)
#define MY_VOLUME       60000 + random(30000) + random(30000) + random(40000)

#define G_RES_DEATH     1 + random(50)
#define G_SS_MAX        60 + random(40)

#define G_STR           45 + random(25)
#define G_DEX           160 + random(50)
#define G_CON           80 + random(40)
#define G_WIS           80 + random(80)
#define G_INT           80 + random(80)
#define G_DIS           180 + random(25)

/* Global variables */
object      shadow;
object      ob;

/* Prototypes */
public void          create_monster();
       void          arm_me();
       int           check_attack();


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
    set_race_name("ghost");
    set_name("morthec");
    add_name("_any_ghost_of_erech_");
    set_living_name("_morthec_the_happy_ghost_of_erech_");
    set_title("the ghost king");
    set_long("It is really not much to look at, it is basically a shadow " +
	"beyond horror.\nHe looks mighty, maybe he is a king.\n");

    set_adj("mighty-looking");
    add_adj("trasparent");
  
    set_gender(0);
    set_alignment(230);
    set_aggressive(&check_attack());
  
    add_prop(CONT_I_HEIGHT, MY_HEIGHT);
    add_prop(CONT_I_WEIGHT, MY_WEIGHT);
    add_prop(CONT_I_VOLUME, MY_VOLUME);
    add_prop(LIVE_I_UNDEAD, 1 + random(20) );
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_MAX_DRINK, 100);
    add_prop(LIVE_I_MAX_EAT, 100);
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);
    add_prop(MAGIC_I_RES_DEATH, G_RES_DEATH);
    
    set_act_time(80);
    add_act("sigh tiredly");
    add_act("emote drifts restlessly around.");
    set_cact_time(5);
    add_cact("emote stares deep into your eyes. Your limbs freeze.");
    add_cact("knee enemy");
    add_cact("kick enemy");
    add_cact("slap enemy");
    add_cact("emote shouts out the ancient battle cry of the Edian of the " +
	     "North: Lacho calad! Drego Morn!");
    set_chat_time(65);
    add_chat("What are you doing here?");
    add_chat("I am tired of this tunnel.");
    add_chat("Three millennia is too long.");
    add_chat("I have all the time in the world.");
    add_chat("This is boring.");
    add_chat("I realy long for rest now.");
    add_chat("I think I have lost a key somewhere.");
    set_cchat_time(6);
    add_cchat("You misserable fool!");
    add_cchat("I am your doom.");
    add_cchat("You will regret this when you're dead.");

    set_skill(SS_ACROBAT, G_SS_MAX);
    set_skill(SS_AWARENESS, G_SS_MAX);
    set_skill(SS_DEFENCE, G_SS_MAX);
    set_skill(SS_PARRY, G_SS_MAX);
    set_skill(SS_WEP_POLEARM, G_SS_MAX);

    set_base_stat(SS_STR, G_STR); 
    set_base_stat(SS_DEX, G_DEX); 
    set_base_stat(SS_CON, G_CON);
    set_base_stat(SS_WIS, G_WIS);
    set_base_stat(SS_INT, G_INT);
    set_base_stat(SS_DIS, G_DIS); 
  
    shadow = clone_object(E_OBJ + "ghost_race_shadow.c");
    shadow->shadow_me("morthec");

    arm_me();
}

void
arm_me()
{
    ob=clone_unique(E_OBJ + "gwaedhel-spear.c", 1, E_OBJ + "m_spear.c");
    ob->move(this_object());
    command("wield all");
    ob=clone_object(E_OBJ + "m_crown.c");
    ob->move(this_object());
    ob=clone_object(E_OBJ + "g_mail.c");
    ob->move(this_object());
    command("wear all");
}

int
check_attack()
{
    return this_player()->query_prop(I_ATTACKED_A_GHOST);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    this_player()->add_prop(I_ATTACKED_A_GHOST, 1);
    call_for_ghosts(ob);
}

void
notify_ob_attacked_me(object friend, object enemy)
{
    if (objectp(query_attack())) return;

    set_alarm(itof(random(5)+5), 0.0, &help_ghost(enemy, friend));
}

