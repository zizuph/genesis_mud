/* A gypsy. Mortricia 920927 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <cmdparse.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define ALIGN           100

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
    set_all_attack_unarmed(20, 100);

    set_chat_time(12);
    add_chat("Wanna try?");
    add_chat("Three hits for one silver coin!");
    add_chat("Just hit the peg.");
    set_act_time(30);
    add_act("@@show_em");

    set_cact_time(10);
    add_cact("grin");

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
}

void
enter_inv(object ob, object from)
{
    object *club;

    if (MASTER_OB(ob) == "/d/Terel/mortricia/camp/w_club") {
        call_out("wield_club", 3, ob);
    } else if (ob->short() == "a silver coin") {
	club = FIND_STR_IN_OBJECT("wooden club", TO);
	if (sizeof(club)) {
	    call_out("give_back", 3, ({club[0], from}));
	    environment(TO)->set_hitter(from);
	} else {
	    club = FIND_STR_IN_OBJECT("wooden club", from);
	    if (sizeof(club)) {
	        environment(TO)->set_hitter(from);
	    } else {
	        call_out("give_back", 3, ({ob, from}));
	    }
	}
    } else {
        call_out("drop_it", 3, ob);
    }
    ::enter_inv(ob, from);
}

void
drop_it(object ob)
{
    command("drop "+ob->query_name());
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
