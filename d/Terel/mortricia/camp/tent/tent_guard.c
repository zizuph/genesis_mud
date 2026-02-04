/* A tent guard. Mortricia 920927 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <composite.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define NUM	        4
#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define WEP_DIR         MORTRICIADIR + "weapons/"

#define ALIGN           -50
#define ENTRANCE_FEE    12

private object check_sh_pr(string sh_desc, string prop, object ob);

public void
init_living()
{
    add_action("do_pay", "pay");
    ::init_living();
}

public void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("guard");
    set_short("dark guard");
    set_long(BSN(
        "It's a dark guard, protecting this tent from trouble-makers."
    ));
    set_adj("dark");
    set_race_name("gypsy");
    set_gender(0);

    set_stats(({65,65,60,50,50,60}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN-random(11));

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_WEP_SWORD, 60);

    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(20, 20);

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

public void
dress_me()
{
    object sword, cloak;

    seteuid(getuid(TO));
    cloak = clone_object(ARM_DIR + "cloak");
    cloak->set_short("black cloak");
    cloak->set_long("A black cloak.\n");
    cloak->set_adj("black");
    cloak->move(TO);
    command("wear cloak");

    sword = clone_object(WEP_DIR + "plain_sword");
    sword->move(TO);
    command("wield sword");

    MONEY_MAKE_CC(30)->move(TO);
    MONEY_MAKE_SC(5)->move(TO);
}

public void
show_hook(object item)
{
    object ring = check_sh_pr("golden ring", "_gypsy_permit", TP);

    if (!ring) ring = check_sh_pr("iron ring", "q_solver", TP);
    if (!ring) ring = check_sh_pr("gold ring", "q_solver", TP);
    
    if (ring && ring == item && ring->query_worn() == TP) {
        write("The guard pushes you further into the tent.\n");
        TP->move_living("south", TENT_DIR + "tent_02");
    } else {
	    command("say What? Are you trying to fool me?");
    }
}

private object
check_sh_pr(string sh_desc, string prop, object ob)
{
    int i;
    object *ob_arr, r_ob=0;

    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_short() == sh_desc &&
	    ob_arr[i]->query_prop(prop) == ob->query_name()) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}

public int
do_pay(string str)
{
    string  what, for_c, get_c;
    string  change;
    int     *result;
    int     price;

    price = ENTRANCE_FEE;

    if (!str) {
	notify_fail("Pay what? Fee?\n");
        return 0;
    }

    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;

    if (what != "fee" && what != "entrance" && what != "entrance fee")
	return 0;

    set_money_give_out(what_coins(TO));

    result = pay(price, TP, for_c, 0, TO, get_c);

    if (sizeof(result) == 1)
	return 0; /* Pay() handles notify_fail if we want to. */

    write ("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    change = text(result[NUM .. 2 * NUM - 1]);
    if (change) {
	write("You get, " + change + " as change.\n");
    }
    say(QCTNAME(TP) + " pays the entrance fee.\n");
    write("The guard pushes you further south.\n");
    TP -> move_living("south", TENT_DIR + "tent_02");
    return 1;
}
