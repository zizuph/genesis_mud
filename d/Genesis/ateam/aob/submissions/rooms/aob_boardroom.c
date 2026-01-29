/*
 * Board Room for the AoB Team
 *
 * This room will house a board where wizards can submit their
 * balance review requests.
 *
 * Created by Petros, June 2016
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

// Defines

// Prototypes
public void load_board();

// Global Variables

public void
create_room()
{
    set_short("Balance Review Board Room");
    set_long("This room is dedicated to the massive message board in the center of "
             + "this space. If you wish to submit something for review by the AoB "
             + "team, do so by writing on the board. You can <read sign> to get "
             + "further instructions.\n\n"
             + "NOTE: Use <mread> instead of <read> for board notes.\n\n");

    load_board();
}

public void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/ateam/aob/submissions/objs/aob_board");
    bb->move(this_object());
}
 
public int 
query_prevent_snoop()
{
    return 1;
}

public int
do_read(string arg)
{
    if (!strlen(arg) || lower_case(arg) != "sign")
    {
        return 0;
    }

    string contents = read_file("/d/Genesis/ateam/aob/submissions/docs/instructions.txt", 1);
    this_player()->more(contents);
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_read, "read");
}

