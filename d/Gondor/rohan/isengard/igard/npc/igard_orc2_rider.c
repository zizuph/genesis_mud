/*
 * This file is IGARD_NPC + "igard_orc2_rider.c"
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

string long_looks;

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " orc with short crooked legs and long arms that hang almost "
       + "to the ground. Although it is not the biggest orc you have ever "
       + "seen, it looks big enough to cause trouble, especially when it "
       + "has friends around to help it.\n";
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
    
    default_config_npc( 55 + rnd / 3);
    set_base_stat(SS_INT, 35 + rnd / 2);
    set_base_stat(SS_WIS, 35 + rnd / 2);
    set_base_stat(SS_DIS, 35 + rnd / 6);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  55 + rnd / 3);
    set_skill(SS_WEP_CLUB,   55 + rnd / 3);
    set_skill(SS_WEP_KNIFE,  55 + rnd / 3);
    set_skill(SS_PARRY,      55 + rnd / 2);
    set_skill(SS_DEFENCE,    55 + rnd / 2);
    set_skill(SS_RIDING,      55 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);

    orc_acts();

    create_igard_orc();
}


string
long_desc()
{
    return long_looks;
}


