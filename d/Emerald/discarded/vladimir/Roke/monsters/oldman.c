inherit "/std/monster.c";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void arm_me();

void
create_monster()
{
    set_name("man");
    set_race_name("human");
    set_long("This old human looks as though his ancient eyes "+
	     "have seen much.\n");
    set_short("old man");
    add_adj("ancient");

    default_config_npc(4);
    set_random_move(10);
    set_alignment(500);
    NEVERKNOWN;

    set_skill(SS_DEFENCE, 5);
    set_skill(SS_WEP_CLUB, 8);
    set_skill(SS_PARRY, 3);

    add_act("emote groans loudly.");
    add_act("emote sighs deeply.");
    add_act("emote grumbles unhappily.");
    add_act("emote passes gas.");
    set_act_time(8);
    arm_me();
}

void
arm_me()
{
    seteuid(getuid());

    clone_object("/d/Roke/varl/atuan/cape/guild/obj/wood")->move(TO);
    clone_object("/d/Roke/vladimir/obj/weapons/cane")->move(TO);
    clone_object("/d/Roke/vladimir/obj/armour/cloak")->move(TO);

    command("wear all");
    command("wield all");
}
