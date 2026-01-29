/*
 * This file is NCAMP_NPC + "ncamp_orc"
*/

#pragma strict_types

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_NPC + "ncamp_monster.c";

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
       + " orc with short crooked legs and long arms that hang almost "
       + "to the ground. Although it is not the biggest orc you have ever "
       + "seen, it looks big enough to cause trouble, especially when it "
       + "has friends around to help it.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " orc from maggot-caves of Mordor. He is so filthy "
       + "that you cannot tell what colour his skin would be when clean. He "
       + "wears the regalia of the Lidless Eye, which marks him as one of a "
       + "horde of orcs bred in the shadow of Barad-dur.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " orc seems somehow more intelligent and clever than is usual for "
       + "his kind. He watches you with a perceptive eye, as if probing for "
       + "weaknesses. He wears the regalia of the Lidless Eye, suggesting that "
       + "he was born in the land of Mordor where the shadows lie.\n";
	      break;
    case 3:
       long_looks = "This " + (implode(query_adjs()," "))
       + " orc skulks here and there, cringing and whining about the hardships of its "
       + "life. A number of lash marks are obvious on its face and back. As they say in "
       + "Mordor: 'Where there's a whip, there's a way'. Despite his beaten appearance, "
       + "the orc looks dangerous and mean.\n";
	      break;
    case 4:
       long_looks = "This " + (implode(query_adjs()," "))
       + " orc glares about with a malevolent and suspicious eye. Jagged yellow "
       + "teeth protrude from its wicked smile. Like most of its kind, this orc "
       + "enjoys the pain and suffering of others. It seems to be examining you as "
       + "a potential victim.\n";
	      break;
    case 5:
       long_looks = "This " + (implode(query_adjs()," "))
       + " orc, a soldier of the Iron Horde of Mordor, looks like he means business. "
       + "He has long arms made for throttling the innocent, jagged teeth for biting "
       + "his foes, and a look of cunning about him that warns you against turning "
       + "your back on him.\n";
	      break;
    default:
        break;
    }
}


public void
create_ncamp_orc()
{
}

nomask void
create_ncamp_monster()
{
    int     rnd = random(31);
 
    set_name("orc");
    set_pname("orcs");
    set_race_name("orc");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    
    default_config_npc( 15 + rnd / 3);
    set_base_stat(SS_INT, 5 + rnd / 2);
    set_base_stat(SS_WIS, 5 + rnd / 2);
    set_base_stat(SS_DIS, 5 + rnd / 6);

    set_alignment(-250-rnd*10);

    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    

    orc_acts();

    create_ncamp_orc();
}


string
long_desc()
{
    return long_looks;
}
