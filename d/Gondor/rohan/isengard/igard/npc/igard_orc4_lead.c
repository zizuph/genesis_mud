/*
 * This file is IGARD_NPC + "igard_orc4_lead.c"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_orc.c
 * and
 *          /d/Gondor/common/npc/redleadorc.c
 *
 * General upgrade, Olorin, February 1996
 * This orc will attack anyone attacking a member    
 * of his team                                       
 * copied in parts from /doc/examples/mobiles/troll.c
 * Revision:
 * Updated code:	Boron May 30. 1996.
 * General revision:	Olorin, 4-Feb-1997.
 * Last modified by Alto, October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_monster.c";

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

private void    add_pack();
public  int     add_3_orcs(int i);

static  int     Pack_Size;


object HOME;

string long_looks;

#define WEP_ARRAY1 ({IGARD_WEP + "i_largeclub", IGARD_WEP + "i_largescim", IGARD_WEP + "i_largehalberd", IGARD_WEP + "i_club", IGARD_WEP + "i_scim", IGARD_WEP + "i_largeaxe", IGARD_WEP + "i_axe"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY3 ({IGARD_ARM + "i_greaves", IGARD_ARM + "i_bracers"})

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " orc with short crooked legs and long arms that hang almost "
       + "to the ground. This is one of the largest orcs you have "
       + "seen, second only to the mightiest orc race, the uruks.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " orc from the caverns beneath the Misty Mountains. He is so filthy "
       + "that you cannot tell what colour his skin would be when clean. He "
       + "wears the regalia of the White Hand, which marks him as one of a "
       + "horde of orcs pressed into service by the gangmasters of Saruman.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " orc seems somehow more intelligent and clever than is usual for "
       + "his kind. He watches you with a perceptive eye, as if probing for "
       + "weaknesses. He wears the regalia of the White Hand, suggesting that "
       + "he was born in the warrens of Isengard.\n";
	      break;
    default:
        break;
    }
}


public void
create_igard_orc()
{
}

nomask void
create_igard_monster()
{
    int     rnd = random(31);
 
    set_name("orc");
    set_pname("orcs");
    set_race_name("orc");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    
    default_config_npc( 75 + rnd / 3);
    set_base_stat(SS_INT, 75 + rnd / 2);
    set_base_stat(SS_WIS, 75 + rnd / 2);
    set_base_stat(SS_DIS, 75 + rnd / 6);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  75 + rnd / 3);
    set_skill(SS_WEP_CLUB,   75 + rnd / 3);
    set_skill(SS_WEP_POLEARM,75 + rnd / 3);
    set_skill(SS_WEP_KNIFE,  75 + rnd / 3);
    set_skill(SS_PARRY,      75 + rnd / 2);
    set_skill(SS_DEFENCE,    75 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   160 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 80000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 75000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);

    set_random_move(5);

    set_alarm(1.0, 0.0, &find_home());

    orc_acts();

    create_igard_orc();
}


string
long_desc()
{
    return long_looks;
}


static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm3 = ARM_ARRAY3;

    set_all_hitloc_unarmed(20);
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

    if (Victim->query_prop("_enemy_of_igard"))
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
        + TO->query_race() + " adjusts his armours, peers dangerously around "
        + "and returns to his post.\n", ({TO}));

    tell_room(HOME, "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " arrives at his post, dusting off his "
        + "armours after a recent melee.\n");

    TO->move_living("M", HOME, 1, 0);

    return 1;
}



private void
add_pack()
{
    int     n, 
            p, 
            r;

    TO->set_leader();
    p = Pack_Size + random(Pack_Size/2 + 1);

    for (n = 0; n < p/3; n++)
    {
	       r = p - n*3;
       	if (r > 3) 
	       r = 3;
        set_alarm(1.0, 0.0, &add_3_orcs(r));
    }
}

public void
set_pack_size(int i)
{
    Pack_Size = i;
}


public void
add_3_orcs(int i)
{
    int    n = -1;
    object orc;

    if (i < 1) 
   	return 0;
    if (i > 3) 
   	i = 3;
    while (++n < i)
    {
       	orc = clone_object(IGARD_NPC + "igard_orc2");
       	orc->move_living("down", ENV(TO));
       	orc->arm_me();
       	TO->team_join(orc);
    }
}



