/*
 * File:     board.c
 * Created:  Cirion, 1998.07.18
 * Purpose:  Guild board for the monks
 * Modification Log:
 *
 */
#pragma strict_types
#pragma save_binary

#include "defs.h"
 
inherit "/std/board";
inherit MONKLIB;
#include <std.h>

void
create_board()
{
    set_board_name(MONK_LIB + "board");
    set_num_notes(80);
    set_silent(1);
    set_show_lvl(0);
    set_keep_discarded(1);
    set_remove_str("You are not permitted.\n");

    set_name("board");
    set_adj(({"message"}));
    set_short("message board");
    set_long("It is the message board for the monks. This "
        + "is where notes of interest for the guild may be written "
        + "and read.\n");
}

int
block_reader()
{
    string   name = TP->query_real_name();
    object   tp = this_player();

    // only members and wizards may read and write to the board
    if(!m_query_monk() &&
        (SECURITY->query_wiz_rank(name) < WIZ_NORMAL))
    {
        if(present(tp), environment(this_object())) // mbs support
            write("You are not permitted to view this board.\n");
        return 1;
     }

     return 0;
}

int
block_writer()
{
    // same checks to write to the board as to read it
    return block_reader();
}

int
allow_remove()
{
    string   name = TP->query_real_name();
    object   tp = this_player();

    // only council members and wizards of rank Arch
    // or higher or Genesis wizards may remove notes
    if(!m_query_council_member(this_player (), 1) &&
        (SECURITY->query_wiz_rank(name) < WIZ_ARCH) &&
        (SECURITY->query_wiz_dom(name) != "Genesis"))
    {
        if(present(tp, environment(this_object()))) // present is for mbs support
        {
            if (m_query_wizard_or_jr ()) // message when wizards try to remove a note
            {
                write("Only monk council members, Genesis wizards, "
                    + "and archwizards may remove a note from "
                    + "this board.\n");
                m_log (this_player()->query_name() + " tried to remove "
                    + "a note from the monk board");
            }
        }

        return 0; 
    }
 
    return 1;
}

/*
 * Function name: post_note_here
 * Description:   Function to allow the external
 *                posting of a note. Used for voting, automatic
 *                guild messages, etc.
 * Arguments:     header - the header of the note
 *                author - the author of the note
 *                body - the body of the note
 * Returns:       1 if successful
 */
int
post_note_here(string header, string author, string body)
{
    object *clones;

    reset_euid();
    clones = object_clones (this_object());

    if(!IS_CLONE && sizeof(clones)) // if we are the master, post the note on a clone
    {
        clones[0]->post_note_here(header, author, body);
        return 1;
    }
    else // otherwise just post to this object
    {
        if (geteuid() != geteuid(previous_object()))
        {
            MONK_ERROR(TP, "Board post error: (geteuid() != geteuid(previous_object())", "");
            return 0;
        }

        create_note(header, author, body);
        return 1;
    }
}



