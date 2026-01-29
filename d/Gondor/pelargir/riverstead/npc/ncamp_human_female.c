/*
 * This file is NCAMP_NPC + "ncamp_human_female.c"
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
       + " woman with a look of grave resignation on her face. She appears to be "
       + "a farmer's wife, and as such is no stranger to hardship. Although she is "
       + "obviously no soldier, she looks quite capable of defending herself. "
       + "She looks ready to defend her home to the death.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " farmer's wife from the settlements along the river Anduin. "
       + "From her hard looks and even harder stares, you see that she is "
       + "suspicious of strangers. Although she has put on a brave face, "
       + "a subtle hint of fear slips through her resolve. Despite this, "
       + "she looks prepared to defend her kith and kin.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " woman is of obvious noble heritage. She has a regal and refined "
       + "bearing that most of the settlers lack. Perhaps she is descended "
       + "from a long-ago dunadan branch that fell upon hard times and took "
       + "to the hard life of the farm. She stands tall, bravely facing "
       + "whatever dangers await.\n";
	      break;
    case 3:
       long_looks = "This " + (implode(query_adjs()," "))
       + " woman seems lost and alone. Like many of the simple farming folk "
       + "in this settlement, she has never faced the terrors of Mordor. "
       + "She seems to be in the midst of realizing that she must fight or "
       + "die.\n";
	      break;
    case 4:
       long_looks = "This " + (implode(query_adjs()," "))
       + " woman, while not of obvious noble descent, still appears to be "
       + "more affluent than most of the villagers. Perhaps she is the wife of "
       + "a village leader or elder. In this farming community, however, even "
       + "women such as this look toughened from years of hard work. No doubt "
       + "she would put up a tough fight if she were attacked.\n";
	      break;
    case 5:
       long_looks = "This " + (implode(query_adjs()," "))
       + " woman seems to know her way around weapons and armours, despite "
       + "her appearance as a simple farmer's wife. No doubt she once served "
       + "in the militia of Thornlin before falling in love with a farmer from "
       + "the banks of the Anduin. She looks perilous to any who would cross "
       + "her path. She also looks very unhappy to have orcs running about her "
       + "home.\n";
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
    add_name(({"woman", "female", "lady"}));
    set_gender(1);
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
