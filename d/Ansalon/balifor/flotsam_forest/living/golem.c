

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/std/act/asking";
inherit AC_FILE


public void
add_descr(string description)
{
    add_prop(LIVE_S_EXTRA_SHORT, " " + description);
}

public void
remove_descr()
{
    remove_prop(LIVE_S_EXTRA_SHORT);
}

void
attack_object(object ob)
{
    remove_descr();
    ::attack_object(ob);
}

#define KEY "/d/Ansalon/balifor/flotsam_forest/obj/chest_key"

void
create_creature()
{
    int i;

    set_name("golem");
    set_adj("clay");
    set_race_name("golem");

    set_long("This great clay figure has been supernaturally " +
      "brought to life by mighty wizards of ages past. " +
      "You have no doubt this automation would be very " +
      "difficult to beat. A key hangs around its neck.\n");

    set_stats(({220,160,280,80,60,100}));
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_hp(10000);
    set_alignment(0);

    set_default_answer("The clay golem magically speaks its " +
      "message: You have defeated the minotaur maze, no easy " +
      "feat, and stand in the Halls of Silver. What treasure " +
      "you seek is not in these passages, yet the key to them " +
      "is well within your reach.\n");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT, 75);
    set_skill(SS_AWARENESS,100);

    NEVERKNOWN;

    set_attack_unarmed(1, 60, 60, W_BLUDGEON, 50, "left fist");
    set_attack_unarmed(2, 60, 60, W_BLUDGEON, 50,"right fist");

    set_hitloc_unarmed(1, 60, 90, "body");
    set_hitloc_unarmed(2, 30, 10, "head");


}

void
arm_me()
{
    clone_object(KEY)->move(TO,1);
}

int
special_attack(object enemy)
{
    int attacktype, pen, att, wloc;
    mixed hitres;
    string *hitloc, *attack, how;

    attacktype = random(5);

    if (attacktype == 1)
    {
	pen = 400 + random(100);
	hitres = enemy->hit_me(pen, 40, TO, -1);

	enemy->catch_msg(QCTNAME(TO) + " pounds you with his " +
	  "enchanted fists! You feel like a wall has just fallen " +
	  "on you.\n");
	tell_room(E(TO), QCTNAME(TO) + " pounds " + QTNAME(enemy) +
	  " with his fists!\n",({enemy,TO}));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}
