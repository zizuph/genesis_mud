#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include "/d/Gondor/lebennin/std/defs.h"
inherit "/std/monster";
inherit "/d/Gondor/lebennin/std/auto_teaming";

mixed corsair_adj();
void set_layout();
#define DEBUG(x) find_player("rungne")->catch_msg("[DEBUG]: " + x + "\n")

void
create_monster() {
	set_pick_up_team(({"_lebennin_corsair"}));
	set_name("corsair");
	add_name("warrior");
	add_name("_lebennin_corsair");
	set_pname("corsairs");
	add_pname("warriors");
	set_race_name("human");
	set_living_name("corsair");
	mixed adj_desc = corsair_adj();
	set_alignment(-500);
	add_prop(OBJ_M_HAS_MONEY, ({0,random(6),random(12),0}));
    set_adj(corsair_adj());
	set_gender(random(2));
	set_layout();
}

mixed
corsair_adj() {
	return (({
		CORSAIR_ADJ1[random(sizeof(CORSAIR_ADJ1))],
		CORSAIR_ADJ2[random(sizeof(CORSAIR_ADJ2))]
	}));
}

void
set_layout() {
	default_config_npc(120 + random(10));
	set_base_stat(SS_DIS, 140);
	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_AWARENESS, 50);
	set_skill(SS_BLIND_COMBAT, 90);

	int layout = random(3);
    switch(layout)
    {
    case 0: /* Axe and shield */
		set_base_stat(SS_STR, 130 + random(20));
		set_skill(SS_WEP_AXE, 70 + random(20));
		set_skill(SS_DEFENCE, 70);
		equip(({
            AREA_DIR + "wroad/obj/corsair_axe.c",
			AREA_DIR + "wroad/obj/corsair_shield.c",
            AREA_DIR + "wroad/obj/corsair_earring.c",
            AREA_DIR + "wroad/obj/corsair_helmet.c",
            AREA_DIR + "wroad/obj/corsair_chainmail.c",
            AREA_DIR + "wroad/obj/corsair_boots.c",
            AREA_DIR + "wroad/obj/corsair_gloves.c",
            AREA_DIR + "wroad/obj/corsair_breeches.c"
        }));
    	break;
    case 1: /* Sword and shield */
		set_base_stat(SS_DEX, 130 + random(20));
		set_skill(SS_WEP_SWORD, 70 + random(20));
		set_skill(SS_DEFENCE, 70);
		equip(({
            AREA_DIR + "wroad/obj/corsair_sword.c",
			AREA_DIR + "wroad/obj/corsair_shield.c",
            AREA_DIR + "wroad/obj/corsair_earring.c",
            AREA_DIR + "wroad/obj/corsair_helmet.c",
            AREA_DIR + "wroad/obj/corsair_chainmail.c",
            AREA_DIR + "wroad/obj/corsair_boots.c",
            AREA_DIR + "wroad/obj/corsair_gloves.c",
            AREA_DIR + "wroad/obj/corsair_breeches.c"
        }));
    	break;
    case 2: /* Two handed sword */
		set_base_stat(SS_DEX, 130 + random(20));
		set_skill(SS_WEP_SWORD, 75 + random(20));
		set_skill(SS_DEFENCE, 75);
		set_skill(SS_PARRY, 75);
		equip(({
			AREA_DIR + "wroad/obj/corsair_claymore.c",
            AREA_DIR + "wroad/obj/corsair_earring.c",
            AREA_DIR + "wroad/obj/corsair_helmet.c",
            AREA_DIR + "wroad/obj/corsair_chainmail.c",
            AREA_DIR + "wroad/obj/corsair_boots.c",
            AREA_DIR + "wroad/obj/corsair_gloves.c",
            AREA_DIR + "wroad/obj/corsair_breeches.c"
		}));
		break;
    }
}

/*
 * Function name: query_help_needed
 * Description:   Check if help is needed
 * Arguments:     attacker - The person who attacked my friend
 */
status
query_help_needed(object attacker)
{
	object *team;
	int size;
	int index;
	int team_average;

	team = ({ attacker }) + attacker->query_team_others();
	team = team & all_inventory(environment());
	size = sizeof(team);

    if (size > 1)
    {
        team_average = 0;
        index = -1;
        while(++index < size)
        {
            team_average += team[index]->query_average_stat();
        }
        team_average /= size;
    }
    else
    {
        team_average = attacker->query_average_stat();
    }
    if ((sizeof(attacker->query_team_others()) && team_average > SD_AV_ADEPT) ||
		(attacker->query_average_stat() > SD_AV_HERO)) {
	   	return 1;
	}
	else {
		return 0;
	}
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker if below certain avg
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object attacker)
{
    // assist if team avg is above adept or attacking player is above hero
	if (query_help_needed(attacker)) {
    	set_alarm(0.1, 0.0, &command("say I will aid you in killing " + OBJECTIVE(attacker) + "!"));
   	    set_alarm(0.2, 0.0, &command("kill " + lower_case(attacker->query_real_name())));
    }
}

/*
 * Function name: notify_attack_on_team
 * Description  : This is called when someone attacks a team member of mine.
 * Arguments    : object friend - my team member
 *		  object attacker - the attacker
 */
public void
notify_attack_on_team(object friend, object attacker)
{
    /* Already busy. */
    if (this_object()->query_attack()) {
		return;
    }
	help_friend(attacker);
}

/*
 * Function name: attacked_by
 * Description  : This routine is called when we are attacked.
 * Arguments    : object attacker - the attacker.
 */
public void
attacked_by(object attacker)
{
	if (!query_help_needed(attacker)) {
		if (sizeof(attacker->query_team_others())) {
			set_alarm(0.1, 0.0, &command("say I will deal with these pathetic cretins myself!\n"));
		}
		else {
			set_alarm(0.1, 0.0, &command("say I will deal with this pathetic cretin myself!\n"));
		}
	}
	::attacked_by(attacker);
}


/*
 * Function name: cb_death_occured
 * Description:   Called when 'me' dies
 * Arguments:     object killer: The enemy that caused our death.
 */
public void
cb_death_occured(object killer)
{
/*	environment()->_corsairs--;
	if (!sizeof(this_object()->query_team_others() && environment()->_corsairs-- >= 3)) {
		environment()->add_npc(AREA_DIR + "wroad/npc/corsair_base", 3);
	}
	::cb_death_occured(killer);
*/
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
