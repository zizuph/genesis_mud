
/*
 * Stern 26-apr-2000, removed nazgul permission to remove notes from boards.
 *  (text is commented out of allow_remove() with // so as to easily
 *  reinstall).
 */

#pragma save_binary

inherit "/d/Gondor/std/board";

#include <mail.h>
#include <std.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#define ME_DOMAINS    ({ "Gondor", "Mordor", "Shire", })

void
create_board()
{
    string  name;
    ::create_board();

    name = BOARD_DIR + "nazgul_board";
    if (file_size(name) != -2)
        mkdir(name);
    set_board_name(name);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("bulletin board of the Nazgul in the Society of the Morgul Mages");
    set_remove_str("A magical force prevents you from removing "+
        "the note.\n");

    FIX_EUID;
}

int
allow_remove(int note)
{
    int     wizlevel;
    string  name;

    if (this_player()->query_nazgul())
    {
        if (!SECURITY->query_wiz_rank(query_author(note)))
        {
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_REMOVE_NOTE );
            return 1;
        }
    }

    wizlevel = SECURITY->query_wiz_rank(name = TP->query_real_name());
    if (wizlevel > WIZ_NORMAL)
        return 1;

    if (member_array(SECURITY->query_wiz_dom(name), ME_DOMAINS) >= 0)
        return 1;

    if (present(TP, ENV(TO)))
        write("The force of the Red Eye prevents you from removing the note.\n");

    return 0;
}

int
block_reader()
{
    int     wizlevel;

    if ( wizlevel = SECURITY->query_wiz_rank(TP->query_real_name()) )
    {
        if (wizlevel > WIZ_NORMAL)
        return 0;
    }

    if (TP->query_nazgul())
    {
        MORGUL_MASTER->increase_activity( TP, ACTIVITY_READ_NOTE );
        return 0;
    }

    if (present(TP, ENV(TO)))
        write("You seek the wrath of the Nine? Stay away from this board!\n");
    return 1;
}
/*
int
block_reader()
{
    int     wizlevel;
    string  name;

    if (!(wizlevel = SECURITY->query_wiz_rank(name = TP->query_real_name())))
        return 0;

    if (member_array(SECURITY->query_wiz_dom(name), ME_DOMAINS) >= 0)
        return 0;

    if (wizlevel > WIZ_NORMAL)
        return 0;

    if (present(TP, ENV(TO)))
        write("You seek the wrath of the Nine? Stay away from this board!\n");
    return 1;
}
*/
int
block_writer()
{
    int     wizlevel;
    string  name;

    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_BOARD_NOTE );
    if (!(wizlevel = SECURITY->query_wiz_rank(name = TP->query_real_name())))
        return 0;

    if (member_array(SECURITY->query_wiz_dom(name), ME_DOMAINS) >= 0)
        return 0;

    if (wizlevel > WIZ_NORMAL)
        return 0;

    if (present(TP, ENV(TO)))
        write("You cannot write the notes on this board.\n");
    return 1;
}

