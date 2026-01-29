/*
 * /d/Gondor/guilds/militia/room/train.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Training room for the Thornlin Militia.
 *
 * Coded by Auberon Gwyneth on 19 February 2001
 */
inherit "/d/Gondor/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

#include "/d/Gondor/defs.h"
#include "../militia.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

object gTrainer;

public void
reset_room()
{
    if (!objectp(gTrainer))
    {
        gTrainer = clone_object(MNPC + "trainer");
        gTrainer->move(this_object(), 1);
    }
}

void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_WEP_POLEARM, "effectively use polearms", "polearm", 0, 50);
    sk_add_train(SS_DEFENCE, "defend oneself", "defence", 0, 50);
    sk_add_train(SS_PARRY, "parry weapons", "parry", 0, 50);
    sk_add_train(SS_TRADING, "make deals and trades", "trading", 0, 50);
    sk_add_train(SS_LANGUAGE, "understand other languages", "language", 0, 50);
    sk_add_train(SS_AWARENESS, "be aware of surroundings", "awareness", 0, 50);
    sk_add_train(SS_MILITIA, "use tactics of the militia", 
        "militia tactics", 50, 50);
    sk_add_train(SS_MILITIA_IMPALE, "impale", "impale", 50, 50);
}

public void
create_gondor()
{
    set_short("Practice Room");
    set_long("Here is where members of the Thornlin Militia may practice " +
        "and train their skills. The instructor waits, perfecting his " +
        "spear technique. He looks each person over as they enter, " +
        "wondering if they wish to receive their next lesson. Hanging from " +
        "the ceiling are a few stuffed dummies, and along the walls are " +
        "blunt training spears.\n");
    add_item(({"floor", "ground"}), "The floor is simply the bare earth, but " +
        "packed down from years of training.\n");
    add_item(({"wall", "walls", "bare walls", "brick"}),
        "The walls and ceiling are made of good quality brick, and the " +
        "workmanship appears to be that of local mason who took great " +
        "pride in his work and making the buildings of his town look nice. A " +
        "few training spears are propped up against the walls.\n");
    add_item(({"building", "room", "barracks"}), "You stand in the " +
        "practice room of the Thornlin Militia.\n");
    add_item(({"spears", "training spears", "blunt spears", "blunt training spears"}), 
        "The training spears aren't as sturdy as spears meant for battle, and have " +
        "their tips wrapped in cloth to take away their edge and preserve the " +
        "dummies, or anyone who happens to get in the way!\n");
    add_item(({"dummies", "stuffed dummies", "dummy", "stuffed dummy", "ceiling"}),
        "The dummies hanging from the ceiling are made of cloth and stuffed to " +
        "vaguely resemble the shapes of goblins, orcs and wolves.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(MROOM + "join.c", "west", 0, 1, 0);
    set_up_skills();
    reset_room();
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    return (IS_MILITIA(who) || who->query_wiz_level());
}

public void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 

void
remove_militia_members(object who)
{
    who->catch_tell("A stern looking guard escorts you out of the " +
        "barracks.\n");
    tell_room(this_object(), QCTNAME(who) + " is escorted out of the " +
        "barracks by a stern looking guard.\n", who);
    tell_room(THORN_DIR + "r2a", QCTNAME(who) + " is escorted out from " +
        "the barracks by a stern looking guard.\n");
    who->move_living("M", THORN_DIR + "r2a", 1, 0);
}

int
did_spit(string str)
{
    remove_militia_members(this_player());
    return 1;
}

public void
init()
{
    ::init();

    add_action(did_spit, "spit");
    init_guild_support();
    init_skill_raise();
}
