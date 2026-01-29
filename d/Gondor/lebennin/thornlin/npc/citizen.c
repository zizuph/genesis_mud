/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */

#include "/d/Gondor/defs.h"
inherit STD_DIR + "monster.c";

#include <ss_types.h>
#include <macros.h>
#include "attackers.c"

void
create_gondor_monster()
{
    set_name(({"citizen","man"}));
    add_name("_thornlin_citizen");
    set_race_name("human"); 
    set_short("citizen of Lossarnach");
    set_pshort("citizens of Lossarnach");
    set_long("A dark-haired and grey-eyed citizen of "
      + "Lossarnach, clearly of some Dunadan descent.\n");
    set_stats(({15+random(20), 15+random(20), 15+random(20), 
	20+random(10), 20+random(20),  5+random(25)}));

    set_alignment(150);
    set_skill(SS_WEP_KNIFE, 20 + random(20));
    set_skill(SS_DEFENCE,   20 + random(20));
    set_skill(SS_PARRY,     20 + random(20));
    set_skill(SS_AWARENESS, 20 + random(20));
    set_chat_time(50);
    add_chat("I love Thornlin.");
    add_chat("I heard that an orc was seen east of town.  Do you know if it's true?");
    add_chat("I wish that the crops grew this well every year!");
    add_chat("I fear that there will be war soon!");
}

void
arm_me()
{
    FIX_EUID
    clone_object(WEP_DIR + "knife")->move(TO);
    command("wield knife");

    clone_object(MINAS_DIR + "obj/ltunic")->move(TO);
    command("wear all");

    clone_object(MINAS_DIR + "obj/ctrousers")->move(TO);
    command("wear all");
}

/* solamnian prestige */
int     query_knight_prestige() {return (-10);}

