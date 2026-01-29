/*
 *  /d/Gondor/guilds/rangers/north/meeting_room.c
 *
 *  Board room of the Rangers of the North
 *
 *  Coded by Elessar.
 *
 *  Modified by Alto, 15 July 2001, to comply with new ranger theme
 *           by Gorboth, April 2015, adding the outlaw list here
 *
 */
inherit "/d/Gondor/std/room.c";

#include <std.h>
#include "../rangers.h"

inherit RANGERS_DIR + "election_base.c";
inherit RANGERS_NOR_DIR + "north_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "check_exit.c"

#define   CHAIR4_NAME     "fourth chair"
#define   CHAIR3_NAME     "third chair"
#define   CHAIR2_NAME     "second chair"
#define   CHAIR_NAME      "first chair"
#define	  GUILD_NUMBER    1

object             gBoard;

public string      long_desc();
public string      read_list();
public void        create_gondor();
public int         check_leave();
public void        init();
public void        leave_inv(object ob, object dest);
public string      look_at(string arg);


string
long_desc()
{
    string txt;
    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling. ";
    else
        txt = ". ";

    return "This is the meeting room of the Rangers of the North. "
        + "There is a table in the center of the room. Around the table "
        + "are high-backed chairs. Set into the "
        + "east wall is an iron torch stand" + txt + "In this room plans "
        + "are made and discussions held. The only exit leads west to a "
        + "brightly-lit room. A small alcove near the exit draws your "
        + "attention. You notice, too, a list that has been unrolled"
        + " to lie open upon the table.\n";
}


/*
 * Function name: read_list
 * Description  : Lists outlaws and NOs
 * Returns      : The list
 */
public string
read_list()
{
    string text;
    string *outlaw_list, *not_outlaw_list;
    int    i = -1, j = -1;

    outlaw_list = MANAGER->query_outlaw_members();
    not_outlaw_list = MANAGER->query_notorious_members();

    text = "These scoundrels are presently outlaws of the Westlands:\n\n";

    seteuid(getuid());

    while (++i < sizeof(outlaw_list))
    {
        if (SECURITY->exist_player(outlaw_list[i]))
            text += "- " + CAP(outlaw_list[i]) + ", Outlaw.\n";
    }

    while (++j < sizeof(not_outlaw_list))
    {
        if (SECURITY->exist_player(not_outlaw_list[j]))
            text += "- " + CAP(not_outlaw_list[j]) + ", Notorious Outlaw.\n";
    }

    return text + "\n";
}


public void
create_gondor()
{
    set_short("the meeting room of the Rangers of the North");
    set_long(&long_desc());

    north_add_items();

    add_chair(CHAIR4_NAME,
     "[down] [in] / [on] [the] [third] 'chair' / 'armchair'", 1, "in");

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

    add_item( ({ "fourth chair", "fourth high-backed chair" }),
        &look_at(CHAIR4_NAME) );

    add_item(({ "chairs", "high-backed chairs", "table", "furniture" }),
        "The furniture is finely carved with leaves and woodland animals. "
        + "There are four comfortable looking high-backed chairs around "
        + "the table for you to sit upon during important meetings.\n");
    add_item(({"animal", "animals", "leaf", "leaves"}), "The carvings "
        + "on the high-backed chairs are quite intricate and life-like.\n");
    add_item(({"carving", "carvings"}), "The high-backed chairs are "
        + "adorned with carvings of woodland animals and leaves.\n");
    add_item(({"east wall", "eastern wall"}), 
        "An iron torch stand is mounted on the eastern wall, right " +
        "beside a wide opening which leads into the library.\n");
    add_item(({"alcove", "small alcove"}), "The small alcove near the "
        + "exit is designed to allow you to nominate candidates and vote "
        + "in company elections. You may also call for the impeachment "
        + "of your Captain in this room should circumstances be dark "
        + "enough to require it. See help rangers elections for details.\n");
    add_item(({"arch", "opening", "library"}),
        "A wide opening in the eastern wall opens up into a small library.\n");
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_item("list", read_list);
    add_cmd_item("list", "read", read_list);

    add_exit(RANGERS_NOR_DIR + "song_room", "west");
    add_exit(RANGERS_DIR + "library/north_library", "east", &check_leave(), 1);

    FIX_EUID;
    gBoard = clone_object(STD_DIR + "board");
    gBoard->set_board_name(RANGERS_BOARD + "ron_board");
    gBoard->set_num_notes(50);
    gBoard->set_silent(0);
    gBoard->set_show_lvl(0);
    gBoard->set_remove_lvl(WIZ_NORMAL);
    gBoard->set_remove_str("The note is firmly affixed to the board.");
    gBoard->move(TO);

    add_prop(ROOM_I_INSIDE,1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    reset_room();
}

public int
check_leave()
{
    if (check_sitting())
        return 1;
    else
        return 0;
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}

/*
 * Function name: init
 * Description  : Masks parent so we can call init_room_chairs()
 *                and init_vote_actions().
 */
public void
init()
{
    ::init();
    init_room_chairs();
    init_vote_actions();
}

/*
 * Function name: leave_inv
 * Description  : Masks parent to be sure that departing players
 *                are removed from chair/sofa occupants
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}

/*
 * Function name: look_at
 * Description  : VBFC to describe chair/sofa + occupants
 */
public string
look_at(string arg)
{
    if (arg == CHAIR_NAME)
    {
     return "This is the most comfortable looking chair in the "
        + "room, and as such it rests at the head of the table. "
        + "Others should show respect for the captain by leaving "
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

    if (arg == CHAIR4_NAME)
    {
     return "This chair looks a little well-worn, but is probably "
        + "very comfortable nonetheless.\n" +
         sitting_on_chair(CHAIR3_NAME, this_player(), 0);
    }
}

