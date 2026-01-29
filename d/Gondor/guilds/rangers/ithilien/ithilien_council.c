/*
 *  /d/Gondor/guilds/rangers/ithilien/ithilien_council.c
 *
 *  Ithilien Hideout council room.
 *
 *  Coded by Elessar
 *    Modified by Alto and Gwyneth, 15 July 2001, to meet CH theme.
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
#include <composite.h>
#include <filter_funs.h>

inherit RANGERS_DIR + "council_base.c";
inherit RANGERS_ITH_DIR + "ith_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "exit.c"

#define   CHAIR3_NAME     "third chair"
#define   CHAIR2_NAME     "second chair"
#define   CHAIR_NAME      "first chair"

public string      long_desc();
public void        init();
public void        leave_inv(object ob, object dest);
public string      look_at(string arg);     /* VBFC for chairs */


string
long_desc()
{
    string torch_txt;

    if (Tstand->query_torch_is_lit())
        torch_txt = "The room is lit by an iron torch stand mounted on "
            + "the north wall.\n";
    else
        torch_txt = "An iron torch stand is mounted on the north wall.\n";


    return ("This high-ceilinged room is the council chamber of the Ithilien "
        + "Rangers. The cool stone walls and floor give the room a solid "
        + "and comfortable feel and it retains a sense of vitality. "
        + "Gathered around a large bulletin board are three chairs. "
        + "A stair leads up to a dimly lit chamber. "
        + torch_txt);
}


void
create_gondor()
{
    set_short("the council room of the Rangers of Ithilien");
    set_long(&long_desc());

    clone_object(RANGERS_OBJ + "rdoor2")->move(TO);

    ith_add_items();
    add_exit(RANGERS_ITH_DIR + "post_council", "up", &check_ranger());

    add_chair(CHAIR3_NAME,
     "[down] [in] / [on] [the] [third] 'chair' / 'armchair'", 1, "in");

    add_chair(CHAIR2_NAME,
     "[down] [in] / [on] [the] [second] 'chair' / 'armchair'", 1, "in");

    add_chair(CHAIR_NAME,
     "[down] [in] / [on] [the] [first] 'chair' / 'armchair'", 1, "in");

    add_item( ({ "first chair", "first high-backed chair"}), 
        &look_at(CHAIR_NAME) );

    add_item( ({ "second chair", "second high-backed chair" }),
        &look_at(CHAIR2_NAME) );

    add_item( ({ "third chair", "third high-backed chair" }),
        &look_at(CHAIR3_NAME) );

    add_item(({ "chairs", "high-backed chairs", "table", "furniture" }),
        "The furniture is finely carved with leaves and woodland animals. "
        + "There are three comfortable looking high-backed chairs around "
        + "the bulletin board for officers to sit upon during "
        + "important meetings.\n");
    add_item(({"animal", "animals", "leaf", "leaves"}), "The carvings "
        + "on the high-backed chairs are quite intricate and life-like.\n");
    add_item(({"carving", "carvings"}), "The high-backed chairs are "
        + "adorned with carvings of woodland animals and leaves.\n");
    add_item(({"north wall", "northern wall"}), "The north wall bears an "
        + "iron torch stand.\n");
    add_item(({"sentinel", "green-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    /* Initiate the council room for the Ithilien company. */
    init_council_votes("ithilien");

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &ith_add_torch());
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));
    set_alarm(60.0, 0.0, &finalize_votes());

}


/*
 * Function name: init
 * Description  : Mask parent so we can call init_room_chairs()
 *                and init_council_actions
 */
public void
init()
{
    ::init();

    /* Add chair verbs. */
    init_room_chairs();

    /* Add council verbs. */
    init_council_actions();
}

/*
 * Function name: prevent_enter
 * Description  : I'm using this instead of enter_inv, as it actually
 *                prevents entering, and doesn't need to eject after.
 *                Using enter_inv would allow wizards to use At commands
 *                and read the boards.
 * Arguments    : object ob - the object trying to enter
 * Returns      : 1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    string name, txt;
    object *oblist;

    /* Non-livings are allowed in. */
    if (!living(ob))
        return 0;

    name = ob->query_real_name();

    /* Council members of the north, wizards of Gondor
       and arches are allowed in. */
    if ((MANAGER->query_is_council(name) &&
         ob->query_ranger_level() == ITHILIEN_LEVEL) ||
      SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_guild_is_master("rangers", name) ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return 0;

    ob->catch_tell("No matter how hard you try, you just " +
        "can't enter that room! You'd better stop trying before " +
        "you hurt yourself!\n");

    oblist = FILTER_PLAYERS(oblist);

    txt = extract(ctime(time()), 4) + " " + CAP(name) + " attempted to " +
        "enter the Ithilien Council room.\nPresent: " +
        COMPOSITE_LIVE(oblist) + ".\n";

    log_file("intruder", txt);
    return 1;
}

/*
 * Function name: leave_inv
 * Description  : Mask parent to be sure that departing players
 *                are removed from the chair/sofa.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);

    leave_inv_room_chairs(ob, dest);
}

/*
 * Function name: look_at
 * Description  : Describes chair/sofa + occupants.
 * Arguments    : arg - the string entered by the player
 * Returns      : the description
 */
public string
look_at(string arg)
{
    if (arg == CHAIR_NAME)
    {
        return "This is the most important looking chair in the "
            + "room, and as such it has the highest back. "
            + "Officers should show respect for the captain by leaving "
            + "this chair open.\n" +
            sitting_on_chair(CHAIR_NAME, this_player(), 0);
    }

    if (arg == CHAIR2_NAME)
    { 
        return "A very comfortable chair upon which to have a pipe "
            + "during long meetings.\n" +
            sitting_on_chair(CHAIR2_NAME, this_player(), 0);
    }

    if (arg == CHAIR3_NAME)
    {
        return "A very comfortable chair upon which to have a pipe "
            + "during long meetings.\n" +
            sitting_on_chair(CHAIR3_NAME, this_player(), 0);
    }
}

