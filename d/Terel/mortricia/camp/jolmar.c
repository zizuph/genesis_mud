/* A gypsy. Mortricia 920927 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <composite.h>
#include <money.h>
#include <cmdparse.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define ALIGN           100
#define NUM             4
#define FEE             12

init_living()
{
    ::init_living();
    add_action("do_pay", "pay");
}

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("jolmar");
    set_short("fat gypsy");
    set_long(BSN(
        "It's a fat gypsy. Don't mess with him."
        ));
    set_adj("fat");
    set_race_name("gypsy");
    set_gender(0);

    set_stats(({99,99,99,99,99,99}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_WEP_CLUB, 99);
    set_skill(SS_DEFENCE, 99);
    set_skill(SS_AWARENESS, 99);

    set_all_hitloc_unarmed(1);
    set_all_attack_unarmed(40, 100);

    set_chat_time(12);
    add_chat("Wanna try?");
    add_chat("Three hits for one silver coin!");
    add_chat("Just pay the fee!");
    add_chat("Just hit the peg.");
    set_act_time(30);
    add_act("@@show_em");

    set_cact_time(10);
    add_cact("grin");

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    MONEY_MAKE_CC(30) -> move(TO);
    MONEY_MAKE_SC(7)  -> move(TO);
    MONEY_MAKE_GC(2)  -> move(TO);
    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
}

void
enter_inv(object ob, object from)
{
    if (MASTER_OB(ob) == "/d/Terel/mortricia/camp/w_club") {
        set_alarm(3.0, -1.0, "wield_club", ob);
    } else {
        if (from && ob && living(from))
            set_alarm(2.0, -1.0, "drop_it", ob);
    }
    ::enter_inv(ob, from);
}

void
drop_it(object ob)
{
    if (strlen(ob->short()))
    tell_room(environment(TO), QCTNAME(TO) + " drops " +
               ob->short() + ".\n", TO);
    ob->move(environment(TO));
}

void
wield_club()
{
    command("wield club");
}

void
give_back(object *ob)
{
    string what, name;

    what = ob[0]->short();
    name = ob[1]->query_real_name();
    command("give "+what+" to "+name);
}

string
show_em()
{
    if (sizeof(FIND_STR_IN_OBJECT("wooden club", TO))) {
        environment(TO)->set_hitter(TO);
        command("hit peg with club");
        environment(TO)->reset_hits();
    }
    return "";
}

do_pay(string str)
{
    string  what, for_c, get_c;
    string  change;
    int     *result;
    int     price;
    object  *club;
    int     give_club;

    price = FEE;

    if (!str) {
	notify_fail("Pay what? Fee?\n");
        return 0;
    }

    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;

    if (what != "fee" && what != "a silver coin" &&
        what != "the fee" && what != "silver coin" &&
        what != "gypsy" && what != "gypsy the fee" &&
        what != "gypsy a silver coin" &&
        what !=  "gypsy 1 silver coin") return 0;

    club = FIND_STR_IN_OBJECT("wooden club", TO);
    give_club = sizeof(club);
    if (!give_club) {
        club = FIND_STR_IN_OBJECT("wooden club", TP);
        if (sizeof(club) == 0) {
            command("shrug");
            command("say Sorry, I have no club.");
            return 1;
        }
    }

    set_money_give_out(what_coins(TO));

    result = pay(price, TP, for_c, 0, TO, get_c);

    if (sizeof(result) == 1)
	return 0; /* Pay() handles notify_fail if we want to. */

    write ("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    change = text(result[NUM .. 2 * NUM - 1]);
    if (change) {
	write("You get, " + change + " as change.\n");
    }
    say(QCTNAME(TP) + " pays the fee.\n");
    if (give_club)
        set_alarm(2.0, -1.0, "give_back", ({club[0], TP}));
    environment(TO)->set_hitter(TP);
    return 1;
}
