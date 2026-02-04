/* A bearded woman. Mortricia 920927 */
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
#define NF(message)     notify_fail(message)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define ALIGN           100
#define HARD_TO_CUT     12
#define CAMP_DIR        MORTRICIADIR + "camp/"

init_living()
{
    add_action("do_pull", "pull");
    add_action("do_cut", "cut");
    add_action("do_cut", "shave");
    ::init_living();
}

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("woman");
    set_short("bearded woman");
    set_pshort("bearded women");
    set_long(BSN(
        "Yes, your eyes don't fool you, it's a bearded woman."
        ));
    set_adj("bearded");
    set_gender(1);
    set_race_name("human");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({12,12,12,15,15,12}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    add_prop("_bearded_woman", 1);

    add_item("beard", BSN(
        "The woman's beard looks real, so those who pay the " +
        "entrance fee to this place are by no means cheated."
        ));
}

do_pull(string what)
{
    NF("Pull what?\n");
    if (what != "beard") return 0;

    TO -> command("shout OOOUCH! That hurt!");
    return 1;
}

do_cut(string what)
{
    object beard, shaved_woman, this_room, *obs;
    object ob, ring;
    string verb, s1;

    verb = query_verb();
    NF(capitalize(verb) + " what?\n");
    if (!what) return 0;

    NF("With what?\n");
    if (what == "beard") return 0;

    NF(capitalize(verb) + " what?\n");
    if (sscanf(what, "beard with %s", s1) != 1) return 0;

    obs = FIND_STR_IN_OBJECT(s1, TP);

    NF(capitalize(verb) + " beard with what?\n");
    if (sizeof(obs) <= 0) return 0;

    NF("You must specify one item!\n");
    if (sizeof(obs) > 1) return 0;

    ob = obs[0];

    if (ob->query_wt() != W_KNIFE) {
	write("The " + ob->short() + " isn't useful for shaving!\n");
	return 1;
    }
    if (ob->query_wielded() != TP) {
	write("You do not wield the " + ob->short() + ".\n");
	return 1;
    }

    if (TP->query_skill(SS_WEP_KNIFE) + random(5) < HARD_TO_CUT ) {
        write(BSN(
            "Oops! You slipped with your " + ob->short() +
	    " and cut the poor woman!"
            ));
        say(QCTNAME(TP) + " cut the poor woman!\n");
        TO -> command("say Darn you for cutting me like that!");
        TO -> attack_object(TP);
    } else {
        seteuid(getuid());
        shaved_woman = clone_object(CAMP_DIR + "shaved_woman");
        beard = clone_object(CAMP_DIR + "beard");
	beard -> add_prop("q_solver", TP -> query_name());
        this_room = environment(TO);

        write("Nicely done! You managed to shave off the beard.\n");
        say(QCTNAME(TP) + " shaved the bearded woman.\n");

        beard -> move(this_room);

        shaved_woman -> move_living("M", this_room);
        TO -> remove_object();
    }
    return 1;
}

public void
do_die(object killer)
{
  object beard;

  if (query_hp() > 0) return;

  seteuid(getuid());
  beard = clone_object(CAMP_DIR + "beard");
  beard->add_prop("q_solver", killer->query_name());
  beard->add_prop("blood_stained", 1);
  beard->move(TO, 1);

  ::do_die(killer);

  return;
}
