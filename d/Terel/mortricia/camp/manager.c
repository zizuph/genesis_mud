/* The gypsy leader. Mortricia 920927 */
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

#define ALIGN           -100
#define WEP_DIR         MORTRICIADIR + "weapons/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define QUEST_NO        4

object check_short(string sh_desc, int qno_no, object ob);

init_living()
{
    add_action("do_ask", "ask");
    ::init_living();
}

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("altmar");
    set_short("fat mustachoed gypsy");
    set_long(BSN(
        "It's the head of the gypsies. He looks very old, but " +
	"you shouldn't mess with him anyway."
        ));
    set_adj(({"fat", "mustachoed"}));
    set_race_name("gypsy");
    set_gender(0);

    set_stats(({70,60,80,60,80,70}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_WEP_KNIFE, 70);
    set_all_hitloc_unarmed(25);
    set_all_attack_unarmed(30, 30);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

do_ask(string what)
{
    object ring;

    notify_fail("Ask for what?\n");

    if (!what) return 0;

    if (what != "for job" && what != "about job" &&
        what != "fat gypsy for job" && what != "fat gypsy about job" &&
        what != "gypsy job" && what != "fat gypsy job" &&
        what != "gypsy for job" && what != "gypsy about job")
        return 0;

    if (ring=check_short("iron ring", QUEST_NO, TP)) {
        TO -> command("say Our juggler has disappeared.");
        TO -> command("say I want you to take his place.");
        TO -> command("say Learn how to juggle, and perform in " +
                  "the big tent.");
	if (!(ring->query_prop("ball_juggling")))
	    ring -> add_prop("ball_juggling", 0);
	if (!(ring->query_prop("cone_juggling")))
	    ring -> add_prop("cone_juggling", 0);
    } else {
        TO -> command("say Don't waste my time!");
        write("You are thrown out of the carriage!\n");
	say(QCTNAME(TP) + " is thrown out from the carriage!");
	TP -> move_living("east, rather unwillingly",
			  CAMP_DIR + "camp_08");
    }
    return 1;
}

dress_me()
{
    object knife, cloak;

    seteuid(getuid(TO));
    cloak = clone_object(ARM_DIR + "cloak");
    cloak -> set_short("fancy cloak");
    cloak -> set_long("A fancy cloak.\n");
    cloak -> set_adj("fancy");
    cloak -> set_default_armour(10, A_ROBE, 0, 0);
    cloak -> move(TO);
    command("wear cloak");

    knife = clone_object(WEP_DIR + "knife");
    knife -> move(TO);
    command("wield knife");
}

object
check_short(string sh_desc, int q_no, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_short() == sh_desc &&
	    ob_arr[i]->query_prop("q_solver") == ob->query_name() &&
	    ob_arr[i]->query_prop("q_number") == q_no) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}
