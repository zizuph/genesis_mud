/*
    A skeleton. Mortricia 920910
 */

inherit "/std/monster";

inherit "/std/act/seqaction";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)           break_string(message, 70)
#define TP                    this_player()
#define TO                    this_object()

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("skeleton");
    set_short("bony skeleton");
    set_long(BS(
        "A skeleton of an adult human. As far as you can tell all bones " +
        "are intact, except that its skull are missing. " +
        "This poor fellow probably got trapped in this room, and " +
        "the same might happen to you if you aren't careful.\n"
        ));
    set_adj("bony");

    set_race_name("human");
    set_gender(2);

    set_stats(({ 1, 1, 1, 1, 1, 1}));
    set_hp(9999);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_item(({"bone", "bones"}), BS(
        "The bones haven't been moved by anyone since he (or she) " +
        "moved them " +
        "himself (or herself). Behind the ribs you see something that " +
        "glitters.\n"
        ));
    add_item(({"skull"}), BS(
        "Yes, the skull is missing. Maybe you should try to find it?\n"
        ));

    set_all_hitloc_unarmed(1);
    set_all_attack_unarmed(1, 1);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object ring;

    seteuid(getuid(TO));
    ring = clone_object(MANSION + "chapel/ring");
    ring -> move(TO);
}
