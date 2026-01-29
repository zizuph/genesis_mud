
#pragma save_binary

inherit "/std/monster";

#include "../goblins.h"

#include <ss_types.h>
#include <macros.h>

object axe;
int on_duty;

do_wield();

create_monster()
{
    set_name("korg");

    set_race_name("goblin");
    set_adj(({"hairy","green","purple","black"})[random(4)]);
    set_adj(({"broad","tall"})[random(2)]);

    set_long("The goblin bares his sharp teeth at you.\n");

    set_gender(0); /* male = 0, female = 1, other = 2 */

    set_stats(({100, 35, 50, 8, 15, 75}));

    set_alignment(-200 + random(10)*random(10));
    set_hp(10000);
    set_skill(SS_DEFENCE,      50 - random(10)+random(10));
    set_skill(SS_WEP_AXE,      50 - random(10)+random(10));
    set_skill(SS_WEP_SWORD,    50 - random(10)+random(10));
    set_skill(SS_WEP_KNIFE,    50 - random(10)+random(10));
    set_skill(SS_AWARENESS,    35 - random(10)+random(10));
    set_skill(SS_ANI_HANDL,    50 - random(10)+random(10));
    set_skill(SS_BLIND_COMBAT, 50 - random(10)+random(10));

/*
    set_pick_up(50);
*/
    set_alarm(1.0, 0.0, do_wield);
}

do_wield()
{
    if (!IS_CLONE)
	return; /* Master objects cannot wield */

    seteuid(getuid(this_object()));
    axe = clone_object(GOBLIN_OBJ_DIR + "guard_axe");
    axe->move(this_object());
    command("wield battleaxe");
}

