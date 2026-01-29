/* Coded by Amelia
 *
 * Modified by Ckrik July 1998
 * Changed Grizzly Paw
 *
 * Ckrik Dec 2021
 * Added newmagical bear paw and clone_unique for the item.
 */

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/lib/unique";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
#define MAGIC_PAW "/d/Earthsea/gont/tenalders/wep/grizzly_paw_magical"
#define PAW "/d/Earthsea/gont/tenalders/wep/grizzly_paw"

public void
create_creature()
{
    set_name("bear");
    add_name("grizzly");
    set_living_name("_big_grizzly_");
    set_race_name("bear");
    add_name("_honey_bear_");
    add_adj(({"large", "brown", "grizzly"}));
    set_short("huge grizzly bear");
    add_adj("huge");
    set_long("A huge grizzly bear. He has "+
        "a massive shaggy head, and you can see his long "+
        "sharp teeth when he growls. He is brown with "+
        "honey-golden coloured streaks in his thick fur. "+
        "His nose seems to be swollen, as if by bee stings.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS, 1);

    add_leftover(
        resolve_unique(MAGIC_PAW, 25, ({ PAW }), 1, 50),
        "grizzly paw", 1, "", 1, 0);
    set_act_time(10);
    add_act("growl");
    add_act("roar");
    add_act("emote stands on his two hind legs, towering above "+
        "you.");
    add_act("emote painfully rubs his nose with a paw.");
    add_act("emote licks its massive paw.");
    set_stats(({150, 120, 180, 30, 50, 150 }));
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_SWIM, 80);
    set_skill(SS_UNARM_COMBAT, 90);
    set_attack_unarmed(A_BITE,  90, 35, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 80, 40, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 80, 40, W_SLASH,  30, "right paw");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
}

public int
special_attack(object enemy)
{
    object me = this_object();
    mixed* hitresult;

    if(random(10))
	return 0;                         /* Continue with the attack. */

    hitresult = enemy->hit_me(200 + random(30), W_IMPALE, me, -1);

    if(hitresult[0] < 0)
    {
        me->command("emote growls at you exposing his sharp teeth!");
        return 1;
    }

    if(hitresult[0] > 0 && hitresult[0] <= 2)
    {
        enemy->catch_msg(QCTNAME(me) + " slashes at you with "+
            "his long daggerlike claws!\n");
        tell_watcher(QCTNAME(me) + " slashes at "+ QTNAME(enemy) +
            " with his long daggerlike claws!\n", enemy);
    }

    if(hitresult[0] > 2 && hitresult[0] < 10)
    {
        enemy->catch_msg(QCTNAME(me) + " takes a big bite out of "+
            "you!\n");
        tell_watcher(QCTNAME(me) + " takes a big bite out of "+
            QTNAME(enemy) + "!\n", enemy);
    }

    if(hitresult[0] > 9)
    {
        enemy->catch_msg(QCTNAME(me) + " smashes you with his "+
            "giant paw!\n");
        tell_watcher(QCTNAME(me) + " smashes "+ QTNAME(enemy) + " with "+
            "his giant paw!\n", enemy);
    }

    if(enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
}

public void
give_honey(object ob, object player)
{
    if(ob->id("honey"))
    {
        command("eat honey");
        command("emote lopes off into the bushes.");
        remove_object();
        return;
    }

    ob->move(environment());
    tell_room(environment(), "The grizzly bear swats "+
        LANG_THESHORT(ob) + " right out of your hand with his massive "+
        "paw just as you try to offer it!\n");
    command("kill "+ player->query_real_name());
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(from))
        set_alarm(2.0, 0.0, &give_honey(ob, from));
}
