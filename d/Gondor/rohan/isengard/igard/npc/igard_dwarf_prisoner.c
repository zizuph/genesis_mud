/*
 * This file is IGARD_NPC + "igard_dwarf_prisoner.c"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_orc.c
 *
 * Olorin, July 1993
 * General upgrade, Olorin, February 1996
 * Last modified by Alto, October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_prisoner.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

public string   long_desc();
public void     long_text();
public int      find_home();
public int      go_back_home();
private void    add_team();
public  int     add_2_friends(int i);

static  int     Team_Size;

object HOME;

string long_looks;

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " dwarf who stands proud of stature and unbending beneath "
       + "the oppression of Isengard. This dwarf looks prepared to "
       + "fight to the death.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " dwarf who casts nervous glances here and there, obviously "
       + "preparing to battle the guards of Isengard when they return "
       + "in greater number.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " dwarf has been beaten almost beyond recognition. Breath "
       + "coming in ragged gasps, the dwarf astonishingly seems ready to "
       + "throw back the uruks once again.\n";
	      break;
    default:
        break;
    }
}


public void
create_elf_prisoner()
{
}

nomask void
create_igard_prisoner()
{
    int     rnd = random(31);
    int     gender = random(2);
 
    set_name("dwarf");
    set_pname("dwarves");
    set_race_name("dwarf");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    
    set_alignment(250 + rnd*10);
    set_gender(gender);

    switch(random(5))
    {
        case 0:
            default_config_npc( 45 + rnd / 3);
            set_base_stat(SS_INT, 25 + rnd / 2);
            set_base_stat(SS_WIS, 25 + rnd / 2);
            set_base_stat(SS_DIS, 55 + rnd / 6);
            set_skill(SS_WEP_SWORD,  45 + rnd / 3);
            set_skill(SS_WEP_CLUB,   45 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  45 + rnd / 3);
            set_skill(SS_PARRY,      45 + rnd / 2);
            set_skill(SS_DEFENCE,    45 + rnd / 2);
            break;
        case 1:
            default_config_npc( 55 + rnd / 3);
            set_base_stat(SS_INT, 35 + rnd / 2);
            set_base_stat(SS_WIS, 35 + rnd / 2);
            set_base_stat(SS_DIS, 65 + rnd / 6);
            set_skill(SS_WEP_SWORD,  55 + rnd / 3);
            set_skill(SS_WEP_CLUB,   55 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  55 + rnd / 3);
            set_skill(SS_PARRY,      55 + rnd / 2);
            set_skill(SS_DEFENCE,    55 + rnd / 2);
            break;
        case 2:
            default_config_npc( 65 + rnd / 3);
            set_base_stat(SS_INT, 45 + rnd / 2);
            set_base_stat(SS_WIS, 45 + rnd / 2);
            set_base_stat(SS_DIS, 75 + rnd / 6);
            set_skill(SS_WEP_SWORD,  65 + rnd / 3);
            set_skill(SS_WEP_CLUB,   65 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  65 + rnd / 3);
            set_skill(SS_PARRY,      65 + rnd / 2);
            set_skill(SS_DEFENCE,    65 + rnd / 2);
            break;
        case 3:
            default_config_npc( 75 + rnd / 3);
            set_base_stat(SS_INT, 55 + rnd / 2);
            set_base_stat(SS_WIS, 55 + rnd / 2);
            set_base_stat(SS_DIS, 85 + rnd / 6);
            set_skill(SS_WEP_SWORD,  75 + rnd / 3);
            set_skill(SS_WEP_CLUB,   75 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  75 + rnd / 3);
            set_skill(SS_PARRY,      75 + rnd / 2);
            set_skill(SS_DEFENCE,    75 + rnd / 2);
            break;
        case 4:
            default_config_npc( 85 + rnd / 3);
            set_base_stat(SS_INT, 65 + rnd / 2);
            set_base_stat(SS_WIS, 65 + rnd / 2);
            set_base_stat(SS_DIS, 95 + rnd / 6);
            set_skill(SS_WEP_SWORD,  85 + rnd / 3);
            set_skill(SS_WEP_CLUB,   85 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  85 + rnd / 3);
            set_skill(SS_PARRY,      85 + rnd / 2);
            set_skill(SS_DEFENCE,    85 + rnd / 2);
            break;
        default:
            break;
    }


    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    

    set_alarm(1.0, 0.0, &find_home());

    prisoner_acts();

    create_elf_prisoner();
}


string
long_desc()
{
    return long_looks;
}


int
find_home()
{
    HOME = environment(TO);
    return 1;
}

int
go_back_home()
{
    object foe;

    if (Victim->query_prop("_enemy_of_prisoners"))
    {
    foe = Victim;
    }

    if (environment(TO) == HOME)
    {
    return 1;
    }

    if ((TO->query_attack() != 0) || ((objectp(present(foe, ENV(TO))))
        && CAN_SEE(TO, foe)))
    {
    TO->command("kill " + foe->query_real_name());
    set_alarm(60.0, 0.0, &go_back_home());
    return 1;
    }

    tell_room(environment(TO), "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " runs off to alert the other prisoners of "
        + "danger.\n", ({TO}));

    tell_room(HOME, "A " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " runs into the cell.\n");

    TO->move_living("M", HOME, 1, 0);

    return 1;
}


private void
add_team()
{
    int     n, 
            p, 
            r;

    TO->set_leader();
    p = Team_Size + random(Team_Size/2 + 1);

    for (n = 0; n < p/3; n++)
    {
	       r = p - n*3;
       	if (r > 3) 
	       r = 3;
        set_alarm(1.0, 0.0, &add_2_friends(r));
    }
}

public void
set_team_size(int i)
{
    Team_Size = i;
}


public void
add_2_friends(int i)
{
    int    n = -1;
    object friend;
    object *arr;

    arr = filter(all_inventory(ENV(TO)), &->id("_igard_prisoner"));

    arr -= ({ TO });

    if (sizeof(arr) >= 1)
    {
    return 0;
    }

    if (i < 1) 
   	return 0;
    if (i > 3) 
   	i = 3;
    while (++n < i)
    {
        friend = clone_object(IGARD_NPC + "igard_dwarf_prisoner");
       	friend->move_living("down", ENV(TO));
       	friend->arm_me();
       	TO->team_join(friend);
    }
}



