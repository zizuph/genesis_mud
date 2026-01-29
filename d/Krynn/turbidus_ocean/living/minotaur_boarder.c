#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit M_FILE

string *gAdj1 = ({"muscular","sullen","one-eyed","huge",
  "evil","unfriendly","one-horned","black",
  "ugly","grey","merciless","tall","sturdy","grizzled"});

#define ATTACKED_ERGOTHIANS "_attacked_ergothian_sailors"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("pirate");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " pirate minotaur");
    set_race_name("minotaur");
    set_long("You look upon a minotaur pirate, one of the marauders that " +
        "terrorises the high seas.\n");
    set_stats(({80,40,40,40,40,120}));
    set_hp(5000);

    add_prop(CONT_I_HEIGHT, 220 + random(10));
    add_prop(CONT_I_WEIGHT, 160000);
    add_prop(CONT_I_VOLUME, 160000);
    add_prop(ATTACKED_ERGOTHIANS, 1);

    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_WEP_AXE, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_ACROBAT, 20);

    set_alignment(0);

    set_act_time(0);
    add_act("kill sailor");

    set_cact_time(10);
    add_cact("assist");
    add_cact("shout Take the treasure! No prisoners!");
    add_cact("say By Sargonas! Fight you weaklings!");

}
