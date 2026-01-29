inherit "/std/board";

#include "/secure/std.h"
#include "defs.h"

int initialized;

/*
 * TODO: Look at the board; this can probably be done easier with VBFC.
 */

void
create_board()
{
    set_board_name(HIN_DIR + "boards/council");
    set_num_notes(30);                /* Number of notes             */
    set_anonymous(0);                 /* You may not write anonymous */
    set_silent(0);                    /* Make noise when reading     */
    set_show_lvl(WIZLEV_PILGRIM+1);   /* Full wizards or higher      */
    set_remove_lvl(WIZLEV_PILGRIM+1); /* Full wizards or higher      */
    set_remove_str("You are not allowed to do that");
}

void
init()
{
    ::init();
    add_action("do_read", "read");   /* Control all actions */
    add_action("do_read", "mread");
    add_action("do_remove", "remove");
    add_action("do_note", "note");
    add_action("do_note", "gnote");
    add_action("do_store", "store");
}

int
do_read(string str)
{
    if (!SHIRE_COUNCIL->is_council_member(this_player()->query_real_name()))
    {
        write("The great Nob Nar prevents you from reading this.\n"
            + "Only the pure of heart will be allowed to do so.\n");
        return 1;
    }
    return ::read_msg(str);
}

int
do_remove(string str)
{
    if (!SHIRE_COUNCIL->is_council_member(this_player()->query_real_name()))
    {
        write("The shadow of ancient power emerges.\n"
            + "You are punished for your sabotage attempt.\n"
            + "Nob Nar's anger bears heavy on your shoulders.\n");
        return 1;
    }
    else
        return ::remove_msg(str);
}

int
do_note(string str)
{
    if (!SHIRE_COUNCIL->is_council_member(this_player()->query_real_name()))
    {
        write("A loud voice booms: Do not touch this sacred board, infidel!\n"
          + "It seems that only the pure of heart are allowed to write here.\n");
        return 1;
    }
    return ::new_msg(str);
}

int
do_store(string str)
{
    if (!SHIRE_COUNCIL->is_council_member(this_player()->query_real_name()))
    {
        write("The great Nob Nar lets you neither read nor save a message.\n"
            + "Only the pure of heart will be allowed to do so.\n");
        return 1;
     }
     return ::store_msg(str);
}
