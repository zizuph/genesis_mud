/*
 * This file is NCAMP_NPC + "ncamp_human_male.c"
*/

#pragma strict_types

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_NPC + "ncamp_human.c";

public string   long_desc();
public void     long_text();

string long_looks;

void
long_text()
{
    switch (random(6))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " man with a look of grim resolution on his face. He looks to be "
       + "from the common stock generally found on a farm, sturdy and stout, "
       + "hard-working and reliable. He looks ready to defend his home to "
       + "the death.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " farmer from the settlements along the river Anduin. He has spent "
       + "his entire life working the soil, coaxing sustinence for his family "
       + "from the rich Gondorian soil. At the moment he looks frightened "
       + "but resolved to defend his kith and kin.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " man is of obvious noble heritage. Perhaps his grandfather took a farm "
       + "maiden as a mistress and left her with a dunadan legacy. As such, he "
       + "looks bravely toward the river with piercing and intelligent eyes. "
       + "It seems unlikely that he would run from the likes of orcs.\n";
	      break;
    case 3:
       long_looks = "This " + (implode(query_adjs()," "))
       + " man seems uncertain of what to do. He is one of the many simple "
       + "farmers and peasants in the village who have never had to fight for "
       + "their lives. Those times are past, however, and this man seems to "
       + "be quickly coming to the realization that he must fight or die.\n";
	      break;
    case 4:
       long_looks = "This " + (implode(query_adjs()," "))
       + " man seems to be a village leader of some sort, perhaps the mayor or "
       + "another functionary. In a farming community, however, even the leaders "
       + "work the fields. As such he looks toughened from years of hard work. "
       + "He will put up a tough fight against anybody brave enough to challenge "
       + "him.\n";
	      break;
    case 5:
       long_looks = "This " + (implode(query_adjs()," "))
       + " man appears to know his way around weapons and armours, despite his "
       + "obvious occupation as a farmer. Perhaps he served in the Thornlin "
       + "militia in his younger days, or maybe as a footsoldier in the army of "
       + "Gondor. Whatever the case may be, he looks like he would be deadly "
       + "in a fight.\n";
	      break;
    default:
        break;
    }
}


public void
create_ncamp_human_male()
{
}

nomask void
create_ncamp_human()
{
    int     rnd = random(31);
 
    set_name("human");
    set_pname("humans");
    set_race_name("human");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    
    default_config_npc( 15 + rnd / 3);
    set_base_stat(SS_INT, 5 + rnd / 2);
    set_base_stat(SS_WIS, 5 + rnd / 2);
    set_base_stat(SS_DIS, 5 + rnd / 6);

    set_alignment(250+rnd*10);

    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    

    human_acts();

    create_ncamp_human_male();
}


string
long_desc()
{
    return long_looks;
}
