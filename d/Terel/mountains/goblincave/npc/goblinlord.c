/*
   Modification Log:
      Updated to goblin eldar from orcchief 
	Tomas  -- Nov. 1999
      Added Unique clone for obsidian per AoB's request
	Tomas  -- April 2000
      Added Knight Mercy code
	Tomas  -- April 2000
      Added updated Knight Mercy Code
	Tomas  -- May 2000

      Lilith -- July 2008
	Lowered base armour class for npc due to change in 
	   the way armour works.
	Clones sword of darkness again, not sure why it was
	 changed in 2006, but seeing as the obsidian longsword 
	 had darkness for 10+ years, I am putting it back the 
	 way it was, and as the magic docs state it is. 

      Lilith -- Nov 2008
	Updated npc to clone 7 obsidian swords instead of 4.
	Updated npc to clone magical items from /d/Terel/unique/*

      Petros -- May 2009
	Removed resistances as they make no thematic sense
	Reduced exp factor to 125 as 150 is completely unreasonable
	Use NPC_I_NO_UNARMED to have better sword attacks
	Properly move all belongings to ghost when dying
	Remove unused skills. Kept all elements and those used in flurry

      Petros -- April 2010
	Made dress_me into an alarmed call. Reports from mortals that the
	  dress_up routine wasn't executed properly.
	Added command to ghost to wear armours when fighting.

      Gorboth - May 2011
	Changed the summon wolf routine to check for the number of
	wolves so players cannot trick the code to create zillion-wolf
	deathtraps for eachother.

      Lucius - Jan 2021
        Misc. cleanups.
*/
#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/lib/unique";

#include <options.h>
#include <ss_types.h>
#include <money.h>
#include <filter_funs.h>

#define ARM_DIR    (MOUNTAIN_DIR + "goblincave/armour/")
#define WEP_DIR    (MOUNTAIN_DIR + "goblincave/weapon/")
#define SPELL_DIR  (MOUNTAIN_DIR + "goblincave/spells/")
#define WOLF       (MOUNTAIN_DIR + "goblincave/monster/wolf")

void dress_me();
int query_disallow_mercy(object ob);

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    FIX_EUID;
    ::create_monster();
    set_name(({"eldar"}));
    set_adj(({"ancient","menacing"}));
    set_race_name("goblin");
    set_short("ancient goblin eldar");
    set_long("The Eldar of the Black-Feather Tribe. He looks quite old, but " +
      "seems confident enough to defend himself.\n");
    set_stats(({150, 150, 150, 125, 125, 170}));
    set_exp_factor(125);

    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_PARRY, 85);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_ELEMENT_FIRE, 80);
    set_skill(SS_ELEMENT_AIR, 80);
    set_skill(SS_ELEMENT_EARTH, 80);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_DEATH, 100);

    set_alignment(-300);
    SET_MAX_HP;
    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VOLUME, 150000);
    add_prop(CONT_I_MAX_WEIGHT, 250000);
    add_prop(CONT_I_MAX_VOLUME, 230000);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(NPC_I_NO_UNARMED, 1);

    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop(OBJ_M_HAS_MONEY, random(300));
    set_all_hitloc_unarmed(35);
    set_alarm(0.0, 0.0, dress_me);
}

int 
query_disallow_mercy(object ob)
{
    if (ob->query_merciful())
    {
	write_file(TEREL_DIR + "log/knight_mercy",
            TP->query_name()+" " + ctime(time()) + "\n");
	return 1;
    }
    return 0;
}

void
dress_me()
{
    clone_unique("/d/Terel/unique/furrobe",7,ARM_DIR + "furs")->move(TO);
    clone_unique("/d/Terel/unique/sword_w_darkness",7,WEP_DIR + "curved_sword")->move(TO);
    clone_object(SPELL_DIR + "gl_spells")->move(TO); 
    clone_object(ARM_DIR + "headdress")->move(TO);
    clone_object(ARM_DIR + "boots")->move(TO);
    command("wield all");
    command("wear all");
}

public void
do_die(object killer)
{
    if (query_hp() > 0)
	return;

    if (interactive(killer))
    {
	tell_room(ETO, "An icy chill rushes through the room after " +
	  QTNAME(killer) + " delivers the death blow to the " +
	  "goblin eldar.\n", killer);
	killer->catch_tell("An icy chill rushes through the room after " +
	  "you deliver the death blow to the goblin eldar.\n");

	object ghost = clone_object(
            MOUNTAIN_DIR + "goblincave/npc/lord_ghost");

        move_all_to(ghost);
        ghost->command("wield all");
        ghost->command("wear all");

	ghost->set_killer(killer);
	ghost->move(ETO);
	ghost->arise();
	ghost->attack();
    }
    ::do_die(killer);
}

int
special_attack(object enemy)
{
    if (TO->query_prop(LIVE_I_ATTACK_DELAY))
	return 0;

    if (TO->query_prop(LIVE_I_STUNNED))
	return 0;

    if (random(10) < 2) 
    {
	command("cast flurry " + OB_NAME(enemy));

	object *wolves = filter(FILTER_LIVE(
                all_inventory(environment(this_object()))),
            &->id("_goblin_lord_wolf"));

	if (sizeof(wolves) > 2)
	    return 1;

	command("$whistle loudly");
	clone_object(WOLF)->move_living("north", ETO, 0, 0);
	clone_object(WOLF)->move_living("north", ETO, 0, 0);
	return 1;
    }

    return 0;
}
