/*
 * Written by Quis for the Goblin Start Area 920516
 *
 * Revision history:
 * /Mercade, 09-02-1994: Added the hint-book by Styles
 * "Start here" functionality added by /Mercade on 28 April 1994
 *
 * Changed the RACESTART check to query_race instead of query_race_name
 *
 * Added newbie poster
 * TAPAKAH, 25/05/2005
 *
 * Added newbie portal
 * TAPAKAH, 17/07/2005
 */

#pragma save_binary

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Genesis/login/login.h"

object guard1, guard2, guard3;

void reset_room();

object
make_board()
{
  object board;

    board = clone_object("/std/board");
    if (board) {
        board->set_board_name(GOBLIN_CAVERN_DIR + "board_save");
        board->set_num_notes(25);
        board->set_anonymous(0);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_lvl(30);
        board->set_remove_str("Sorry, mortals are not allowed to remove notes.");
        board->set_err_log(GOBLIN_CAVERN_DIR + "log/board_err");
        board->set_no_show_composite(1);

      board->move(this_object());
      return board;
    }
    return 0;
}

void
create_room()
{
  object ob;
  ::create_room();

  change_prop(ROOM_I_INSIDE,1);
  change_prop(ROOM_I_LIGHT,1);
  change_prop(ROOM_M_NO_ATTACK, "You decide not to break the armed truce with these goblins.\n");
  change_prop(ROOM_M_NO_ATTACK, "You decide not to break the armed truce with these goblins.\n");
  change_prop(ROOM_M_NO_MAGIC_ATTACK, "@@block_attack");
  add_prop(OBJ_S_WIZINFO, "@@wizinfo");

  set_short("Living quarters of the goblin cavern");
  set_long(break_string(
    "Here you see hundreds of goblins, sprawled out sleeping or quietly " +
    "talking.  You realize that these goblins are probably not overly " +
    "concerned about your presence, due to their large numbers. " +
    "There are tunnels leading west and southeast from this room. " +
    "You notice some youths practicing with spears to the southeast. " + 
    "There are some alcoves on the west wall. " +
    "\n",70));

  if(!(ob = make_board())) write("Board could not be created.\n");
  else add_my_desc(break_string("In one corner you see a bulletin board. " +
    "Please feel free to discuss any topic on this board.\n",70));

  add_exit("post", "north");
  add_exit(GOBLIN_CAVERN_DIR + "common", "common");
  add_exit(GOBLIN_CAVERN_DIR + "training_room","southeast");
  add_exit(GOBLIN_CAVERN_DIR + "tunnel1","west");

  add_item(({"goblins"}),"They are rather enjoying ignoring you.\n");
  add_item(({"youths"}),"They are practicing with some rather poor equipment.\n");
  add_item(({"spears","equipment"}),"These are very bad.\n");
  add_item(({"alcove","alcoves"}),
             "Closer examination reveals some murder slits concealed in the wall.\n");
  add_item(({"slit","slits","murder slit", "murder slits"}),
             break_string("These are used to shoot arrows at attackers from. " +
             "They are currently shuttered, and you cannot see through them.\n", 70));

  set_alarm(1.0, 0.0, reset_room);
  room_add_object("/d/Genesis/start/newbie/poster");
  room_add_object("/d/Genesis/start/newbie/portal");
}


void
reset_room()
{
    seteuid(getuid());

    if (!guard1 || !present(guard1, this_object())) {
        guard1 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard1->move_living("northwest", this_object());
    }

    if (!guard2 || !present(guard2, this_object())) {
        guard2 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard2->move_living("northwest", this_object());
    }

    if (!guard3 || !present(guard3, this_object())) {
        guard3 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard3->move_living("northwest", this_object());
    }

    if (!present("faq_book"))
    {
        clone_object("/d/Genesis/start/FAQ/faq_book")->move(this_object());
    }
}


#define	long_line  (strlen(ART_NONMETNAME) > 78 - strlen(arr_line[0] + \
		    arr_line[1]))

string arr_line;

query_no_snoop() { return 1; }

enter_inv(ob,from) {

    ::enter_inv(ob, from);

    if (!interactive(ob) || from)
	return;

    if (ob->query_prop("just_created") == 1)
	ob->move(GOBLIN_CAVERN_DIR + "newcomer");

    return;
}

init() {
    add_action("arrive","arrive");
    add_action("start", "start");
    ::init();
}

int
start(string str)
{
    if (str != "here")
    {
	notify_fail("Start where? Here?\n");
	return 0;
    }

    if (RACESTART[this_player()->query_race()] != MASTER)
    {
	notify_fail("This is not your racial starting location.\n");
	return 0;
    }

    if (this_player()->set_default_start_location(MASTER))
    {
	write("Next time you enter the game, you will start here.\n");
    }
    else
    {
	write(break_string("Somehow it is not possible for you to start " +
	    "here. The room apparently has not been approved of by the " +
	    "archwizards of Genesis. Please mail the archwizard of " +
	    "player affairs to get it allowed.", 74) + "\n");
    }

    return 1;
}

arrive(str) {

    arr_line = ({"stretches, yawns loudly",
    "and rolls to his feet.\n"});

    if (str=="drifting away into the void"){
	say( ({METNAME + nl_test() , ART_NONMETNAME + nl_test()}) );
	return 1;
    }
    else return 0;
}

nl_test() {
    if (long_line) return (arr_line[0] + "\n" + arr_line[1]);
    else return (arr_line[0] + " " + arr_line[1]);
}

wizinfo() {
   return (break_string(
   "This is the starting location for all players of the goblin race.\n",70));
}
