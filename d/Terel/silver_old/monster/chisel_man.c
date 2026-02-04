/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chisel_man.c
 *
 * This is a traveling potion salesman made by Merrygrin
 * Modified by Sorgum 941002
 *
 *  Modified: 3 May 2003, by Bleys
 *      - attacked_by() takes place before the player gets the attack
 *          message, so mortals would kill the bodyguard, then attack
 *          this guy, see him go through his exit routine, and then
 *          see "You attack 0." That's not very elegant, so I
 *          extracted his exit bit into a flee_quickly() method, and
 *          set a quick alarm in attacked_by() that calls flee_quickly.
 *
 *  Modified: 13 May 2003, by Bleys
 *      - The test for Buddy's presence was flawed. if (buddy) didn't
 *          catch the presence of the bodyguard properly, so it was
 *          common (based on several bug reports) for multiple
 *          instances of the bodyguard to be in the same room.
 *          now checking the environment.
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

inherit "/lib/trade";

#include <ss_types.h>
#include <money.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <composite.h>
#include <macros.h>

#define STORE_ROOM  this_object()
#define NUM         4
#define CHISEL      "/d/Terel/common/town/mansion/obj/chisel"
#define BUDDY       "/d/Terel/silver/monster/body_guard"

object buddy, axe;

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();

    set_name("charlie");
    add_name("salesman");
    set_adj("gruff");
    set_race_name("dwarf");
    set_long("This is a traveling salesman.  He travels this area trying " +
         "to sell his stuff.  You can try 'list' to see what he is " +
         "selling or you can buy chisels.\n");

    default_config_npc(40);
    config_default_trade();

    SET_MAX_HP;
    add_prop(LIVE_I_SEE_DARK, 3);

    add_act("shout Chisels for sale!");
    add_act("shout Fine steel chisels for sale!");
    add_act("shout Cheap chisels!");
    set_act_time(15);

    set_skill(SS_AWARENESS, 80);
    set_skill(SS_TRADING, 10);

    set_all_hitloc_unarmed(17);

    seq_new("hubba");
    seq_addfirst("hubba", ({ "@@do_give" }) );

    enable_intro();
}

public int
allowed(object who)
{
    if (!CAN_SEE(TO, who))
        return 0;

    if (member_array(who, query_my_enemies()) >= 0)
        return 0;

    if (buddy && member_array(who, buddy->query_my_enemies()) >= 0)
        return 0;

    return 1;
}

public void
buddy_sad()
{
    if (buddy && environment(buddy) == ETO) {
        buddy->command("sigh");
        buddy->command("sulk");
    }
    aid = 0;
}

public void
answer_buddy(object who)
{
    if (!who || environment(who) != ETO) {
        command("say Nah. You better stay here and defend me " +
                "instead.");
    } else {
        command("say No, " + who->query_pronoun() +
                " might want to trade with me.");
    }
    set_alarm(2.0, -1.0, buddy_sad);
}

public void
check_threat(object who)
{
    if (!who || environment(who) != ETO ||
        !buddy || environment(buddy) != ETO ||
        !CAN_SEE(buddy, who)) {
        aid = 0;
        return;
    }

    buddy->command("say Hey Boss! Should I kill this puny " +
                   who->query_race_name() + "?");

    set_alarm(2.0, -1.0, &answer_buddy(who));
}

public void
init_living()
{
    ::init_living();

    add_action("do_list", "list");
    add_action("do_buy", "buy");

    if (TP == buddy) return;

    if (!aid)
        aid = set_alarm(2.0, -1.0, &check_threat(TP));
}

public void
get_buddy()
{

    if ( present("buddy", ENV(TO)) )
    {
        return;
    }

    FIX_EUID;

    buddy = clone_object(BUDDY);
    buddy->move_living("xx", ETO);
    team_join(buddy);

}

public void
do_give()
{
    int i;

    FIX_EUID;

    MONEY_MAKE_CC(100)->move(TO);
    MONEY_MAKE_SC(10)->move(TO);
    MONEY_MAKE_GC(5)->move(TO);

    for (i=0; i<8; i++)
        clone_object(CHISEL)->move(STORE_ROOM);

    set_alarm(3.0, -1.0, get_buddy);
}

public int
do_list(string str)
{
    object *ob;
    int price, i;

    if (!allowed(TP)) return 0;

    if (!str) str = "chisel";

    if (str != "chisel") {
        command("Say Sorry, but I don't sell those!");
        return 1;
    }

    if (!parse_command(str, STORE_ROOM, "%i", ob)) {
    command("say Sorry but I don't have that for sale.");
    return 1;
    }

    if (sizeof(ob) > 1) {
    write("I've got these fine chisels:\n");
    }
    else {
    write("I've got this fine chisel:\n");
    }

    for (i=1; i<sizeof(ob); i++) {
    price = 2 * ob[i]->query_prop(OBJ_I_VALUE);
    write(capitalize(ob[i]->short()) + " and I would sell it for " +
          price + " coppers.\n");
    }

    return 1;
}

public void
buddy_attack(object ob)
{
    if (!buddy || !ob || environment(ob) != ETO) return;

    buddy->command("cheer");
    buddy->command("assist");

    ob->attack_object(buddy);
    buddy->attack_object(ob);
    ob->catch_msg(QCTNAME(buddy) + " attacks you!\n");
    tell_room(ETO, QCTNAME(ob) + " attacks " + QTNAME(TO) + " but the " +
              QTNAME(buddy) + " stands between them!\n", ob);

}


public void
flee_quickly(object ob)
{
    command("shout Shiiit!");
    command("say Sorry but I will leave now.");
    command("grin");
    tell_room(ETO, QCTNAME(TO) + " opens a vial and quaffs a potion.\n");
    tell_room(ETO, QCTNAME(TO) + " leaves through a rift in space.\n");
    ob->stop_fight(TO);
    remove_object();
}


public void
attacked_by(object ob)
{
    if (!buddy) {
    set_alarm(0.1, 0.0, &flee_quickly(ob));
    return;
    }
    command("say That was a big mistake.");
    command("shout Buddy! Kill this " + ob->query_race_name() + "!");

    if (!present(buddy, ETO))
        buddy->move_living("xx", ETO);

    set_alarm(2.0, -1.0, &buddy_attack(ob));
}

public int
do_buy(string str)
{
    object item;
    string what, for_c, get_c;
    int price, *result, change, dif, i;

    if (!allowed(TP)) return 0;

    if (!str) {
    notify_fail("Buy what did you say?");
    return 0;
    }

    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
    if (sscanf(str, "%s with %s", what, for_c) != 2)
        what = str;

    if (!parse_command(what, STORE_ROOM, "%o", item)) {
    notify_fail("I don't seem to have that chisel with me.\n"
            + "You might try again another day.\n");
    return 0;
    }

    if (axe && present(axe, STORE_ROOM) && item == axe) {
        command("say I don't think so!");
        return 1;
    }

    price = 2 * item->query_prop(OBJ_I_VALUE);

    dif = TP->query_skill(SS_TRADING) - query_skill(SS_TRADING);
    if (dif > 0) {
    price -= (price * dif)/200;
    command("say Ahhh. You drive a hard bargain!");
    command("sigh");
    }

    result = pay(price, TP, for_c, 0, TO, get_c);
    if (sizeof(result) == 1) {
    return 0;
    }

    if (item->move(TP)) {
    write("You drop the " + item->short() + " on the ground.\n");
    say(QCTNAME(TP) + " drops one " + item->short() +
           " on the ground.\n");
    item->move(ETP);
    }
    else {
    write("You get your " + item->short() + ".\n");
    say(QCTNAME(TP) + " buys the " + item->short() + ".\n");
    }

    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    change = text(result[NUM .. 2 * NUM - 1]);

    if (change)
    write("You get, " + change + " as change.\n");

    command("say Nice doing business with you.");

    return 1;

}

public int
query_knight_prestige()
{
    return -6;
}
