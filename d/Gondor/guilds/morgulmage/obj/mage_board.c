#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/board";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include <std.h>
#include <stdproperties.h>

#define ME_DOMAINS    ({ "Gondor", "Shire" })
#define MAX_HEADER_LENGTH 41

private static mapping gWriting = ([]);
private mapping        gAuthors = ([]);

void
create_board()
{
    ::create_board();

    string  name;

    name = BOARD_DIR + "mages_board";
    set_board_name(name);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    
    FIX_EUID;
    gAuthors = restore_map(query_board_name() + "_authors");
    
    add_name("sheet");
    set_short("bulletin board of the Society of Morgul Mages");
//  set_long("A sheet of dull black metal firmly bolted to the " +
//           "stone wall at the back of the chamber serves as the " +
//           "bulletin board for the Society.\n");

    set_no_show_composite(1);

    set_remove_str("The Black Master prevents you from removing "+
        "the note!\n");


    
}

public varargs int
block_reader(int note = 0)
{
    int     wizlevel;
    string  name = this_player()->query_real_name();

    if (note && 
      (SECURITY->query_guild_is_master(GUILD_NAME, name) ||
       SECURITY->query_wiz_rank(name) >= WIZ_LORD))
    {
        /* Get the name of the writer if anonymous */
        string writer = gAuthors[query_board_name() + "/" + 
            query_headers()[note-1][1]];

        if (strlen(writer))
        {
            write("The real author of this note is: " + 
                capitalize(writer) + ".\n");
        }
    }
    
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_READ_NOTE );

    if (!(wizlevel = SECURITY->query_wiz_rank(name = TP->query_real_name())))
        return 0;

    if (member_array(SECURITY->query_wiz_dom(name), ME_DOMAINS) >= 0)
        return 0;

    if (wizlevel > WIZ_NORMAL)
        return 0;

    if (present(TP, ENV(TO)))
        write("You cannot read the notes on this board.\n");
    return 1;
}

public int
block_writer()
{
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_BOARD_NOTE );
    return 0;
}

public int
block_discard(string file)
{
    if (gAuthors[query_board_name() + "/" + file])
    {
        gAuthors = m_delete(gAuthors, query_board_name() + "/" + file);
        save_map(gAuthors, query_board_name() + "_authors");
    }

    return 0;
}

public nomask int
post_special_done_editing(string author, string message)
{
    int rank;
    string head;

    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    if (!strlen(message))
    {
        write("No message entered.\n");

        gWriting = m_delete(gWriting, this_player());
        return 0;
    }

    if (!stringp(gWriting[this_player()]))
    {
        write("Your header has been lost! No note posted. " +
            "Please make a bug report!\n");
        return 0;
    }

    head = gWriting[this_player()];
    gWriting = m_delete(gWriting, this_player());

    string name = this_player()->query_real_name();

    seteuid(getuid());
    if (this_object()->create_note(head, author, message))
    {
        gAuthors += ([query_board_name() + "/" + query_latest_note():
            name ]);

        write("Ok.\n");

        save_map(gAuthors, query_board_name() + "_authors");
        log_file("mageboard_authors", query_latest_note() + " " +
            CAP(name) + "\n", 0);
    }
    else
        write("Failed.\n");

    return 1;
}

private int
post_special_note(string header, string author)
{
    if (this_player()->query_prop(PLAYER_I_NO_NOTES))
    {
        write("You have lost the privilige of posting notes on boards in " +
            "these realms.\n");
        return 1;
    }
    
    // Player is not allowed to write a note on this board.
    if (check_writer())
    {
        notify_fail("You are not allowed to write here.\n");
        return 0;
    }
    else if (!stringp(header))
    {
        notify_fail("Please add a header.\n");
        return 0;
    }
    else if (strlen(header) > MAX_HEADER_LENGTH)
    {
        write("Message header too long. Try again.\n");
        return 1;
    }

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is writing a note");
    gWriting[this_player()] = sprintf("%-*s", MAX_HEADER_LENGTH-1, header);

    clone_object(EDITOR_OBJECT)->edit(&post_special_done_editing(author), "");
    return 1;
}

public int 
king_note(string args) {

    if(this_player()->query_nazgul() != 2 && 
       SECURITY->query_wiz_rank(TP->query_real_name()) < WIZ_NORMAL)
        return 0;
        
    return post_special_note(args, "The King");
}

public int
nine_note(string args) {

    if(!this_player()->query_nazgul() && 
       SECURITY->query_wiz_rank(TP->query_real_name()) < WIZ_NORMAL)
        return 0;
    
    return post_special_note(args, "The Nine");
}

public int
lieutenant_note(string args) {
    
    if(this_player()->query_morgul_level() != 24 && 
       SECURITY->query_wiz_rank(TP->query_real_name()) < WIZ_NORMAL &&
       !this_player()->query_nazgul())
        return 0;
        
    return post_special_note(args, "Lieutenant");    
}

public void
init()
{
    ::init();

    add_action(king_note, "knote");
    add_action(lieutenant_note, "ltnote");
    add_action(nine_note, "nnote");
}

