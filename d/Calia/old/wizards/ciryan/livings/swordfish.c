inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define A_BITE 0
#define A_SWORD 1

#define H_HEAD 0
#define H_SWORD 1
#define H_BODY 2
#define H_TAIL 3

create_creature()
{
    set_name(({"swordfish", "fish"}));
    set_race_name("swordfish");
    set_short("swordfish");
    set_adj(({"grey", "big"}));
    set_long("This is a big swordfish about two meters long, with a long" +
	     " narrow sword which looks very sharp. It is coloured" +
	     " in light grey and blue making it hard to see in the water." +
	     " It is moving around rapidly in the water apparently looking" +
	     " for dinner.\n");

    set_stats(({120,140,140,30,30,110}));
    set_aggressive(1);
    set_alignment(-100);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_SWIM, 100);

    set_attack_unarmed(A_BITE,35,35,W_IMPALE,30,"bite");
    set_attack_unarmed(A_SWORD,40,40,W_IMPALE,70,"sword");

    set_hitloc_unarmed(H_SWORD, 25, 20, "narrow sword");
    set_hitloc_unarmed(H_BODY, 30, 50, "body");
    set_hitloc_unarmed(H_HEAD, 25, 15, "head");
    set_hitloc_unarmed(H_TAIL, 25, 15, "tail");

    set_act_time(10);
    add_act("emote swims rapidly around in the water.");
    add_act("emote seems to watch you with its cold eyes.");
    add_act("emote swims in circles around you.");
    add_act("emote catches a small fish.");
}

static void
tell_watcher(string str, object enemy)
{
    object          me, *ob;
    int             i;
    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({me});
    ob -= ({enemy});
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->query_see_blood())
	    ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
    object          me;
    mixed          *hitresult;
    me = this_object();
    if (random(5)) {
	return 0;
    }
    hitresult = enemy->hit_me(40+ random(30), W_IMPALE, me, -1);
    if (hitresult[0] == 0) {
	enemy->catch_msg(QCTNAME(me) + " swims rapidly towards you and tries" +
		       " to impale you on his sword but misses totally.\n");
	tell_watcher(QCTNAME(me) + " tries to impale " + QCTNAME(enemy) +
		     " but misses.\n", enemy);
    }
    if (hitresult[0] > 0 && hitresult[0] < 5) {
	enemy->catch_msg(QCTNAME(me) + " scratches you with its sword" +
			 " leaving a small wound.\n");
	tell_watcher(QCTNAME(me) + " scratches " + QCTNAME(enemy) +
		     " with its sword leaving a small wound.\n", enemy);
    }
    if (hitresult[0] >= 10 && hitresult[0] < 25) {
	enemy->catch_msg(QCTNAME(me) + " charges into you with his sword" +
			 " hitting you painfully.\n");
	tell_watcher(QCTNAME(me) + " charges into " + QCTNAME(enemy) +
		     " hitting painfully.\n", enemy);
    }
    if (hitresult[0] >= 25) {
	enemy->catch_msg(QCTNAME(me) + " charges into you with his sword " +
                         "hitting you with great pain.\n");
	tell_watcher(QCTNAME(me) + " charges into " + QCTNAME(enemy) +
		     " hitting very painfully.\n", enemy);
    }
    if (enemy->query_hp <= 0) {
	enemy->do_die(me);
	return 1;
    }
}
