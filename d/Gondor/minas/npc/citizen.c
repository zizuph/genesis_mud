inherit "/d/Gondor/minas/npc/mtirith_monster.c";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_monster()
{
    set_name(({"citizen","man"}));
    set_race_name("human"); 
    set_short("citizen of Gondor");
    set_pshort("citizens of Gondor");
    set_long(BSN("A dark-haired and grey-eyed citizen of "
      + "Lossarnach, clearly of some Dunadan descent."));
    set_stats(({15+random(20), 15+random(20), 15+random(20), 
                20+random(10), 20+random(20),  5+random(25)}));

    set_alignment(150);
    set_skill(SS_WEP_KNIFE, 20 + random(20));
    set_skill(SS_DEFENCE,   20 + random(20));
    set_skill(SS_PARRY,     20 + random(20));
    set_skill(SS_AWARENESS, 20 + random(20));
    set_chat_time(50);
    add_chat("I love Thorbardin.");
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
int     query_knight_prestige() {return (-5);}

