/*
 * ghost.c
 * By Skippern
 *
 * With Sterns servent.c and merged_soldier.c as examples and good
 * help from Rohim and Mrpr.
 *
 * This is the standard ghost in the Path of the Dead, with random 
 * adjectives and random stats. It will also get random equipment 
 * and random skills, so that they reflect upon being a people, not
 * just some unlucky persons.
 *
 * The alignment is set to be between 150 and 650 (random). This is 
 * becouse of their role in the War of the Ring.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";        /* for humanoid monsters */
inherit "/std/act/action";     /* make it do things */
inherit "/std/act/chat";       /* make it talk */

#include "../erech.h"     /* for Erech definitions */

inherit E_LIB + "npc.c";     /* standard reactions */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define GHOST_ADJ1  ({ "transparent", "shadowy", "floating", "shady", \
			"scary", "foul-looking", "pale" })
#define GHOST_ADJ2  ({ "grinning", "one-eyed", "hairless", "toothless", \
			"young", "adolescent", "adult", "scared", \
			"tired-looking", "child", "hairy" })

#define G_PROF      ({ "smith", "farmer", "fighter", "thief", "cleric", \
                       "bard", "warrior", "soldier" })

#define G_GENDER        random(3)
#define G_ALIGN         150 + random(500)
#define MY_HEIGHT       150 + random(31)
#define MY_WEIGHT       200 + random(1200)
#define MY_VOLUME       60000 + random(30000) + random(30000) + random(40000)

#define G_RES_DEATH     1 + random(50)
#define G_SS_MAX        60 + random(40)
#define G_SS_MID        40 + random(40)
#define G_SS_MED        30 + random(30)
#define G_SS_MIN        1 + random(19)

#define G_STR           5 + random(25)
#define G_DEX           55 + random(50)
#define G_CON           20 + random(50)
#define G_WIS           30 + random(70)
#define G_INT           30 + random(70)
#define G_DIS           120 + random(25)

/* Global variables */
object      shadow;

/* Prototypes */

//public void          create_monster();
public void          make_smart(string smart);
void                 fighter_weapons(int wep);
int                  check_attack();

/*
 * Function name:    create_monster()
 * Definition   :    Creates the monster
 */
public void
create_monster()
{
    string adj2 = one_of_list(GHOST_ADJ2);

    set_race_name("ghost");
    set_living_name("_happy_ghost_of_erech_");
    set_name("oathbreaker");
    add_name("_any_ghost_of_erech_");
    set_long("It is really not much to look at, it is basically a shadow " +
	"beyond horror.\n");
  
    set_adj(one_of_list(GHOST_ADJ1));
    add_adj(adj2);
  
    set_gender(G_GENDER);
    set_alignment(G_ALIGN);
    set_aggressive(&check_attack());
  
    add_prop(CONT_I_HEIGHT, MY_HEIGHT);
    add_prop(CONT_I_WEIGHT, MY_WEIGHT);
    add_prop(CONT_I_VOLUME, MY_VOLUME);
    add_prop(LIVE_I_UNDEAD, 1 + random(20) );
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_MAX_DRINK, 100);
    add_prop(LIVE_I_MAX_EAT, 100);
    add_prop(LIVE_I_NO_GENDER_DESC, random(2) );
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);
    add_prop(MAGIC_I_RES_DEATH, G_RES_DEATH);

    set_act_time(80);
    add_act("sigh tiredly");
    add_act("emote drifts restlesly around.");
    set_cact_time(5);
    add_cact("emote stares deep into your eyes. Your limbs freeze.");
    add_cact("knee enemy");
    add_cact("kick enemy");
    add_cact("slap enemy");
    add_cact("emotes shouts out the ancient battle cry of the Edian of the " +
	     "North: Lacho calad! Drego Morn!");
    set_chat_time(65);
    add_chat("What are you doing here?");
    add_chat("I am tired of this tunnel.");
    add_chat("Three millennia is too long");
    add_chat("I have all the time in the world.");
    add_chat("This is boring.");
    add_chat("I realy long for rest now.");
    set_cchat_time(6);
    add_cchat("You misserable fool!");
    add_cchat("I am your doom.");
    add_cchat("You will regret this when you're dead.");

    set_skill(SS_ACROBAT, G_SS_MAX);
    set_skill(SS_AWARENESS, G_SS_MAX);
    set_skill(SS_DEFENCE, G_SS_MAX);
    set_skill(SS_PARRY, G_SS_MAX);

    if (adj2 == "child")
    {
	make_smart("child");

        set_base_stat(SS_STR, G_STR/2);
        set_base_stat(SS_DEX, G_DEX/2);
        set_base_stat(SS_CON, G_CON/2);
        set_base_stat(SS_WIS, G_WIS/2);
        set_base_stat(SS_INT, G_INT/2);
        set_base_stat(SS_DIS, G_DIS/2);
    }

    else
    {
	make_smart(one_of_list(G_PROF));
    
	set_base_stat(SS_STR, G_STR); 
	set_base_stat(SS_DEX, G_DEX); 
	set_base_stat(SS_CON, G_CON);
	set_base_stat(SS_WIS, G_WIS);
	set_base_stat(SS_INT, G_INT);
	set_base_stat(SS_DIS, G_DIS); 
    }

    shadow = clone_object(E_OBJ + "ghost_race_shadow.c");
    shadow->shadow_me("ghost");
 
}

public void
make_smart(string smart)
{
    set_name(smart);

    if (smart == "smith")
    {
	set_skill(SS_WEP_CLUB, G_SS_MAX);

	add_act("emote remembers the ringing of hammers beating upon " +
	    "metal.");

	clone_object(E_OBJ + "g_hammer.c")->move(this_object());
	command("wield all");
    }
    if (smart == "farmer")
    {
	set_skill(SS_HERBALISM, G_SS_MAX);
	set_skill(SS_WEP_POLEARM, G_SS_MIN);

	add_act("emote chews on an old straw.");

	clone_object(E_OBJ + "g_knife.c")->move(this_object());
	command("wield all");
    }
    if (smart == "fighter" || smart == "warrior" || smart == "soldier")
    {
	set_skill(SS_WEP_SWORD, G_SS_MAX);
	set_skill(SS_UNARM_COMBAT, G_SS_MID);
	set_skill(SS_BLIND_COMBAT, G_SS_MID);

	add_act("emote patroles the area.");

	clone_object(E_OBJ + "g_mail.c")->move(this_object());
	command("wear all");

	fighter_weapons(random(7));
    }
    if (smart == "thief")
    {
        set_skill(SS_OPEN_LOCK, G_SS_MID);
	set_skill(SS_PICK_POCKET, G_SS_MAX);
	set_skill(SS_FR_TRAP, G_SS_MAX);

	add_act("emote tries to look innocent, but failes.");
    
	clone_object(E_OBJ + "g_knife.c")->move(this_object());
	command("wield all");
    }
    if (smart == "cleric")
    {
        set_skill(SS_SPELLCRAFT, G_SS_MAX);
	set_skill(SS_HERBALISM, G_SS_MAX);
	set_skill(SS_ALCHEMY, G_SS_MAX);
	set_skill(SS_FORM_ENCHANTMENT, G_SS_MIN);
	set_skill(SS_ELEMENT_LIFE, G_SS_MED);
    
	add_act("emote searches for some herbs.");

	clone_object(E_OBJ + "g_cloak.c")->move(this_object());
	command("wear all");
    }
    if (smart == "bard")
    {
	set_skill(SS_SPELLCRAFT, G_SS_MED);
	set_skill(SS_LANGUAGE, G_SS_MAX);
	set_skill(SS_TRADING, G_SS_MID);

	add_act("emote says loadly with a clear voice: The love of Luthien " +
	    "Thenuviel and Beren was so great that they brought it all the " +
	    "way to their death.");
	add_act("emote sings: Isildur who cut the ring from the hands " +
	    "of Sauron.");
	add_act("emote remembers the tale of the Gwaedhil.");

    }
    if (smart == "child")
    {
	add_act("emote plays on the ground.");

        clone_object(E_OBJ + "g_tsword.c")->move(this_object());
        command("wield all");
    }
}

void
fighter_weapons(int wep)
{
    if (wep == 0)
    {
        clone_object(E_OBJ + "g_axe.c")->move(this_object());
	command("wield all");
    }
    if (wep == 1)
    {
        clone_object(E_OBJ + "g_knife.c")->move(this_object());
	command("wield all");
    }
    if (wep == 2)
    {
        clone_object(E_OBJ + "g_pole.c")->move(this_object());
	command("wield all");
    }
    if (wep == 3)
    {
        clone_object(E_OBJ + "g_sword.c")->move(this_object());
	command("wield all");
    }
    if (wep == 4)
    {
        clone_object(E_OBJ + "g_sword_l.c")->move(this_object());
	clone_object(E_OBJ + "g_sword_r.c")->move(this_object());
	command("wield all");
    }
    if (wep == 5)
    {
        clone_object(E_OBJ + "g_sword_rand.c")->move(this_object());
	command("wield all");
	clone_object(E_OBJ + "g_shield.c")->move(this_object());
	command("wear all");
    }
    if (wep == 6)
    {
        clone_object(E_OBJ + "g_bsword.c")->move(this_object());
	command("wield all");
    }
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

