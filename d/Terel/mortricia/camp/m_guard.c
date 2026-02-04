/* A tent guard. Mortricia 920927 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define WEP_DIR         MORTRICIADIR + "weapons/"

#define ALIGN           -100

private object check_sh_pr(string sh_desc, string prop, object ob);

public void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("guard");
    set_short("dark guard");
    set_long(BSN(
        "It's a dark guard, protecting this area from trouble-makers."
    ));
    set_adj("dark");
    set_race_name("gypsy");
    set_gender(0);

    set_stats(({40,40,40,30,30,40}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_WEP_SWORD, 50);

    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(20, 20);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

public void
dress_me()
{
    object sword, cloak;

    seteuid(getuid(TO));
    cloak = clone_object(ARM_DIR + "cloak");
    cloak->set_short("white cloak");
    cloak->set_long("A white cloak.\n");
    cloak->set_adj("white");
    cloak->move(TO);
    command("wear cloak");

    sword = clone_object(WEP_DIR + "plain_sword");
    sword->move(TO);
    command("wield sword");
}

public void
show_hook(object item)
{
    object ring = check_sh_pr("golden ring", "_gypsy_permit", TP);
    
    if (!ring) ring = check_sh_pr("iron ring", "q_solver", TP);
    if (!ring) ring = check_sh_pr("gold ring", "q_solver", TP);
    
    if (ring && ring == item && ring->query_worn() == TP) {
        write("The guard pushes you west.\n");
        TP->move_living("west", CAMP_DIR + "mana_carr");
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
