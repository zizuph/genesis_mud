/*
 *  /d/Gondor/guilds/rangers/hq/ch_council.c
 *
 *  Ranger Central Headquarters council room.
 *
 *  Coded by Elessar
 *    Modified by Alto and Gwyneth, 15 July 2001, to meet CH theme.
 * 
 *  Modified by Gwyneth, 1 April 2002 to add in voting system.
 *  Modified by Gwyneth, 3 May 2004, neatened and increased efficiency
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_DIR + "council_base.c";
inherit RANGERS_HQ_DIR + "ch_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define   CHAIR6_NAME     "sixth chair"
#define   CHAIR5_NAME     "fifth chair"
#define   CHAIR4_NAME     "fourth chair"
#define   CHAIR3_NAME     "third chair"
#define   CHAIR2_NAME     "second chair"
#define   CHAIR_NAME      "first chair"

public string      long_desc();
public void        init();
public void        leave_inv(object ob, object dest);
public string      look_at(string arg);     /* VBFC for chairs */


void
reset_room()
{
    set_alarm(60.0, 0.0, &finalize_votes());
}

string
long_desc()
{
    return "This high-ceilinged room is the council chamber of the Rangers "
        + "of the Westlands. The aged wood of the walls and floor give the "
        + "room a solid and comfortable feel, and despite the obvious "
        + "wear of the wood, the room retains a sense of vitality. Gathered "
        + "around a large bulletin board are six chairs, one for each of "
        + "the officers of the Rangers.\n";
}

void
create_gondor()
{
    set_short("the Council Room of the Rangers of the Westlands");
    set_long(&long_desc());

    clone_object(RANGERS_OBJ + "cdoor2")->move(TO);

    hideout_add_items();

    add_chair(CHAIR6_NAME,
     "[down] [in] / [on] [the] [third] 'chair' / 'armchair'", 1, "in");
    add_chair(CHAIR5_NAME,
     "[down] [in] / [on] [the] [second] 'chair' / 'armchair'", 1, "in");
    add_chair(CHAIR4_NAME,
     "[down] [in] / [on] [the] [first] 'chair' / 'armchair'", 1, "in");
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
    add_item( ({ "fourth chair", "fourth high-backed chair"}), 
        &look_at(CHAIR4_NAME) );
    add_item( ({ "fifth chair", "fifth high-backed chair" }),
        &look_at(CHAIR5_NAME) );
    add_item( ({ "sixth chair", "sixth high-backed chair" }),
        &look_at(CHAIR6_NAME) );

    add_item(({ "chairs", "high-backed chairs", "table", "furniture" }),
        "The furniture is finely carved with leaves and woodland animals. "
        + "There are six comfortable looking high-backed chairs around "
        + "the bulletin board for officers to sit upon during "
        + "important meetings.\n");
    add_item(({"animal", "animals", "leaf", "leaves"}), "The carvings "
        + "on the high-backed chairs are quite intricate and life-like.\n");
    add_item(({"carving", "carvings"}), "The high-backed chairs are "
        + "adorned with carvings of woodland animals and leaves.\n");
    add_item(({"north wall", "northern wall"}), "The north wall bears an "
        + "iron torch stand.\n");
    add_item(({"apprentice", "apprentice ranger"}), "You are too late! "
        + "Apprentice rangers are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    init_council_votes("gondor");
    reset_room();

    add_prop(ROOM_I_LIGHT, 1);
}

/*
 * Function name:   init
 * Description :    mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();
    init_room_chairs();  /* add chair verbs */
    init_council_actions();
} /* init */

/*
 * Function name: enter_inv
 * Description  : Mask the parent to make sure only ithilien rangers can enter.
 * Arguments    : object ob - the entering object, object from - previous
 *                location of ob
 */
public void
enter_inv(object ob, object from)
{
    string name;

    ::enter_inv(ob, from);

    if (!living(ob))
        return;

    name = ob->query_real_name();
    if (MANAGER->query_is_council(name) ||
      SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;

    eject_intruder(ob, from);

    return;
}
/*
 * Function name: leave_inv
 * Description  : mask parent to be sure that departing players are 
 *                removed from chair/sofa occupants
 * Arguments    : object ob - the one departing
 *                object dest - their destination
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */

/*
 * Function name: look_at
 * Description  : VBFC to describe chair/sofa + occupants
 */
public string
look_at(string arg)
{
    if (arg == CHAIR_NAME)
    {
        return "This is one of two important looking chairs in the room, "
            + "and as such it has a high back. Officers should show respect "
            + "for the captains by leaving this chair open.\n" +
            sitting_on_chair(CHAIR_NAME, this_player(), 0);
    }

    if (arg == CHAIR2_NAME)
    {
        return "This is one of two important looking chairs in the room, "
            + "and as such it has a high back. Officers should show respect "
            + "for the captains by leaving this chair open.\n" +
            sitting_on_chair(CHAIR2_NAME, this_player(), 0);
    }

    if (member_array(arg, ({ CHAIR3_NAME, CHAIR4_NAME, CHAIR5_NAME,
      CHAIR6_NAME })) != -1)
    {
        return "A very comfortable chair upon which to have a pipe during "
            + "long meetings.\n" +
            sitting_on_chair(arg, this_player(), 0);
    }

} /* look_at */
