#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <std.h>

#include "../defs.h"

object fix_board();

nomask int lick_it(string what);

void
create_room()
{
    object ob;

    set_short("In the basement of the tower or realms");

    set_long("This is the basement of the Tower of Realms. The room is rather drab and lit only by one single smoking torch on the wall. The walls are made up by rough bricks, stained and scratched by innumerable bloody battles. Apparently things can get rough down here!\n");

    add_item("torch", "Well, it's just your average magic torch, impossible to remove and impossible to extinguish. What did you expect?\n");
    add_cmd_item(({ "at wall", "at walls", "wall", "walls"}), ({ "look", "lick" }), ({ "Supposedly it was even and nice once upon a time, but since then so many battles have been fought down here as to make it almost impossible even to find a square inch of undamaged surface. Apart from the scratches and the bumps, it's liberally covered with blood and hunks of torn off hair. A gobbo probably could get a fair meal just licking the walls...\n", "@@lick_it@@"}));

    add_exit(TOWN_DIR + "tower", "up");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_STEAL, 1);
    add_prop(ROOM_M_NO_ATTACK, "This is a room for writing, not fighting.\n");
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    if (!(ob = fix_board()))
	add_my_desc("\nThere's a heap of ashes on the floor where the flame board used to be, apparently things became too hot there for a while!\n\n");
    else
        add_my_desc("\nNext to the door is a bulletin board. It's intended for verbal battles with whoever have merited your dislike. Please notice that whatever you put on the board, you'll have to be prepared to answer for later. The board is there for serious purposes. Oh, do mind your language, being mad is no excuse for profanities.\n\n");
}

nomask int
lick_it(string what)
{
    if (this_player()->query_race() == "goblin")
    {
	tell_room(environment(this_player()), QCTNAME(this_player()) + " starts licking the wall with obvious pleasure, making smacking and yumming noices.\n", this_player());
	write("Yumm!!\n");
    }
    else
    {
	tell_room(environment(this_player()), QCTNAME(this_player()) + " takes a hesitant lick at the wall, then immediately starts to retch and spit.\n", this_player());
	write("Yeeeeww!! Gross!\n");
    }
    return 1;
}

object
fix_board()
{
    object hub;

    hub = clone_object("/d/Genesis/start/human/town/basement_board");
    if (hub) {
        hub->set_board_name("/d/Genesis/start/human/town/mflame");
        hub->set_num_notes(50);
        hub->set_anonymous(0);
        hub->set_silent(1);
        hub->set_show_lvl(1);
	hub->set_remove_lvl(20);
        hub->set_remove_str("Sorry, mortals are not allowed to remove notes.");
	hub->set_err_log("/d/Genesis/start/human/town/mflame_err");

	hub->move(this_object());
	return hub;
    }
    return 0;
}
