/* A jester. Mortricia 920927 */
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

#define CAMP_DIR        MORTRICIADIR +"camp/"
#define ALIGN           100

void
init_living()
{
    ::init_living();
    add_action("do_give", "give");
}

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("jester");
    set_short("drunken jester");
    set_long(BSN(
        "It's a drunken jester. He is supposed to be funny, but " +
        "now he is only drunk."
        ));
    set_adj("drunken");
    set_race_name("human");
    set_gender(0);

    set_stats(({15,15,15,15,15,10}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    set_intoxicated(4);

    set_chat_time(10);
    add_chat("I'm so thirsty!");
    add_chat("I prefer the silver beer!");

    set_act_time(5);
    add_act(({"remove hat", "drink beer", "hiccup", "wear hat"}));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

do_give(string str)
{
    string s1, s2, who, lwho;
    object *obs;
    object ob1, ob2, hat;

    if(!str) return 0;
    if(sscanf(str, "%s to %s", s1, s2) != 2) return 0;

    obs = FIND_STR_IN_OBJECT(s1, TP);
    if (sizeof(obs)==0) return 0;
    ob1 = obs[0];
    if (ob1->query_short() != "silver beer") return 0;

    obs = FIND_STR_IN_OBJECT(s2, environment(TO));
    if (sizeof(obs)==0) return 0;
    ob2 = obs[0];
    if (ob2 != TO) return 0;

    ob1 -> move(ob2);
    write("You give a silver beer to Jester.\n");
    say(QCTNAME(TP) + " gives a silver beer to Jester.\n");

    who = TP->query_name();
    lwho = lower_case(who);
    TO -> command("bow to " + lwho);
    TO -> command("thank " + lwho);
    hat = present("hat", TO);
    if (hat) {
        hat -> add_prop("q_solver", who);
	hat -> remove_prop("blood_stained");
        TO -> command("remove hat");
        TO -> command("give hat to " + lwho);
    }
    TO -> command("say Cheers! You have saved my life!");
    TO -> command("drink beer");
    return 1;
}
