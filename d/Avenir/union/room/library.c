/*
 * Archives - library for the Shadow Union
 *
 * Coded by Cirion on January 3rd, 1997
 *
 * Revisions:
 *    Cirion, Aug 1998: Disallowed non-members from using the library.
 *    Lucius, Apr 2005: Use /std/library more. This causes
 *                      the age of books to be lost, but I don't think the
 *                      players had noticed it anyways.
 *    Lucius, Jun 2005: Further updates and additional commands.
 *    Lucius, Feb 2009: Changed library_admin_acces()
 *    Lucius, Jun 2016: Changed to all new library code.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;
inherit (LIB + "library");

#include <mail.h>
#include <math.h>
#include <macros.h>
#include <composite.h>

private object door, sonia;


public void
reset_room(void)
{
    /* If the NPC has been slain, then the "union_o_corpse_of_<npc>" */
    /* prop will be set in this room (from the make_corpse())        */
    /* function in NPC + "npc.c". Until the corpse is destroyed,     */
    /* the Union member will not reset.                              */
    if (!sonia)
    {
	if (!objectp(query_prop(UCORPSE_PROP("sonia"))))
	    sonia = clone_here(NPC + "sonia");
    }

    if (sonia && !present(sonia))
	sonia->move_living("away", TO);
}

/*
 * Function name: library_hook_stop_leave
 * Description  : Called when a player is stopped while carrying books,
 *              : redefine it to give your own message.
 * Arguments    : player - the player that's trying to leave
 *              : books - an array with the books that have not been returned
 *
 *     Called from prevent_leave_with_books()
 */
public void
library_hook_stop_leave(object player, object *books)
{
    if (present(sonia))
    {
	sonia->command("usto "+ OB_NAME(TP) +
	    " You may not leave until you return "+
	    COMPOSITE_DEAD(books) +".");

	switch(random(6))
	{
	case 0:
	    sonia->command("uknowledge "+ OB_NAME(TP));
	    break;
	case 1:
	    sonia->command("unote "+ OB_NAME(TP));
	    break;
	case 2:
	    sonia->command("upatient "+ OB_NAME(TP));
	    break;
	case 3:
	    sonia->command("urecord "+ OB_NAME(TP));
	    break;
	}
    }
    else
    {
	write("Shadows swirl ominously about the doorway as you leave, "+
	  "nearly blotting it out entirely as you attempt to remove "+
	  COMPOSITE_DEAD(books) +" from the Archives.\n");
    }
}

public void
union_room(void)
{
    set_short("archives");
    set_long("Deep purple granite walls frame this large room, "+
	"in the center of which is an intricately carved writing "+
	"desk. A high backed chair stands before the desk, and upon "+
	"the desk is an inkwell and a sheaf of paper. Lining the "+
	"walls are wide wooden shelves, on which are arranged "+
	"a number of books. To the west, @@door_desc@@ The floor "+
	"is made from evenly spaced tiles of rough slate, and the "+
	"ceiling is white limestone.\n");

    add_item(({"chair","seat"}),"The chair is tall and made from "+
	"strong oak. The back is high, and the armrests curve upwards, "+
	"ending in carved heads depicting some strange beast.\n");
    add_item(({"desk","table","wood","carved desk"}),
	"The desk is made from intricately carved pine, with a wide, "+
	"smooth writing surface. Sitting upon the desk is an inkwell, "+
	"pen, and a sheaf of paper, and before the desk is a chair.\n");
    add_item("pen", "It is to write books with.\n");
    add_item(({"crystal","ink","inkwell"}),
	"The inkwell is made from faceted crystal and is nearly full "+
	"of a dark shade of red ink.\n");
    add_item(({"paper","sheaf"}),
	"The paper is thin yet sturdy, ideal for writing on.\n");
    add_item(({"wall","walls","granite"}),
	"The walls are of smoothed granite, undressed and of a deep "+
	"purple hue. Tiny, almost imperceptable, veins of red gemstone "+
	"run along the walls like a spider's web.\n");
    add_item(({"gem","gemstone","vein","veins","web"}),
	"The lines that run along the walls are nearly imperceptible, "+
	"but the gemstone that fills them seem to be akin to ruby.\n");
    add_item(({"floor","ground"}),
	"The floor is of plain and flat slate tiles, worn smooth over "+
	"the years.\n");
    add_item(({"ceiling","roof","up"}),
	"There is a single word inscribed in the soft white limestone "+
	"of the ceiling.\n");

    add_cmd_item(({"shelf","shelves"}), "push",
	"The shelves will not move.\n");
    add_cmd_item(({"word","ceiling"}), "read", "Alcintaron\n");
    add_cmd_item(({"tile","tiles"}),({"push","move","lift","pull"}),
	"The tiles are firmly secured to the floor.\n");
    add_cmd_item(({"paper","sheaf","pen","inkwell","ink"}),({"get","take"}),
	"That is only useful for writing books here, and here it "+
	"shall remain.\n");

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit("library", "west", prevent_leave_with_books, 0, 1);
    //    add_exit("library_old", "old", prevent_leave_with_books);

    add_object(OBJ + "desk");
    add_object(OBJ + "libdoore");

    set_library_save_path(LIBSAVE + "archive/");
    set_library_save_file(LIBSAVE + "archive/data");
    set_library_log_file(LIBSAVE + "archive/log");

    set_library_book_object(OBJ + "book");

    add_library_access_level( "novice", "Novices"     );
    add_library_access_level( "member", "Amlis'k'mia" );
    add_library_access_level(  "admin", "Historians"  );
    add_library_access_level(  "voice", "Voice"       );

    set_library_librarian_level("admin");
    set_library_new_book_shelf("pending");
    add_library_protected_shelf("logs");

    set_library_allow_new_books(1);
    set_library_allow_edit_direct(1);
    set_library_allow_read_direct(1);

    set_library_cmd_prefix("u");

    create_library();
    reset_room();
}

static void
update_vars(void)	{ door = present("_union_door"); }

public string
door_desc(void)
{
    if (door->query_open())
	return "a solid oak door opens to a long hallway.";
    else
	return "a solid oak door, plain and unadorned, stands closed.";
}

/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 */
public int
query_librarian(object who)
{
    /* Historians, Elders and GM's. */
    if (MEMBER_SPHERE(who, SPH_HISTORY))
	return 1;

    return 0;
}

/*
 * Function name: query_player_access
 * Description  : Return a list of the levels that the player have access to
 * Arguments    : player - the player we want to check
 * Returns      : an array with access levels
 */
public string *
query_player_access(object who)
{
    /* Super-user access. GM, Elders, Voice */
    if (MEMBER_SPHERE(who, SPH_VOICE))
	return ({ "novice", "member", "admin", "voice" });

    /* Historians, Elders and GM's. */
    if (query_librarian(who))
	return ({ "novice", "member", "admin" });

    /* If the player is punished with "noarchives", prevent
     * him from making use of this library.  */
    if (U_IS_PUNISHED(who, U_PUNISHED_LIBRARY))
    {
	if (present(sonia))
	{
	    sonia->command("usto "+ OB_NAME(who) +" I am sorry, "+
	      "but the Elders have instructed me to deny "+
	      "you access to the archives.");
	}

	return ({ });
    }

    /* Novices */
    if (MEMBER_SPHERE(who, SPH_TRAINING))
	return ({ "novice" });

    /* Warriors. */
    if (IS_MEMBER(who))
	return ({ "novice", "member" });

    if (present(sonia))
	sonia->command("say I cannot allow Outlanders to see Our books.");

    return ({ });
}

#if 1
/*
 * Masked to deliver custom messages.
 */
public varargs int
add_new_book(string title, string contents, string summary, string author,
 	     string shelf = "", string filename = "", string book_id = "")
{
    int result = ::add_new_book(title, contents, summary, author,
				shelf, filename, book_id);
    if (result)
    {
	string *who = LIST->sphere_members()[SPH_HISTORY];
	string body = "The Warrior "+ capitalize(author) +" has just "+
	    "submitted a book for review.\nYou shall find it on the "+
	    "Pending shelf within Our Archives.\nThe book has been "+
	    "titled: "+ title +"\n\n     Ch'havran,\n       Sonia";

	if (sizeof(who))
	{
	    /* The 'author' is always the submitter currently, so if
	     * they are also a Historian, no need to spam others with
	     * unnecessary emails.
	     */
	    if (member_array(author, who) != -1)
		return result;

	    CREATE_MAIL("Union Archives Pending", "sonia",
		implode(who, ","), "", "Quansu Historian!\n\n" + body);
	}

	string *elders = LIST->elder_list();
	/* Prevent duplicate mails. */
	if (pointerp(who))
	    elders -= who;

	if (sizeof(elders))
	{
	    /* As the note above, if submitter is an Elder, do not
	     * bother the other Elders, but still submit to the
	     * Historians to keep the 'secrecy' alive.
	     */
	    if (member_array(author, elders) != -1)
		return result;

	    CREATE_MAIL("Union Archives Pending", "sonia",
		implode(elders, ","), "",
		"Quansu Elders of the Union!\n\n" + body);
	}
    }

    return result;
}
#endif

/*
 * Masked to customize books.
 */
public void
library_configure_book(object book, string book_id)
{
    ::library_configure_book(book, book_id);

    if (!strlen(book_id))
	return;

    book->finalize_book();
}

/*
 * Just a wrapper function to the (masked) library_help().
 */
public int
archive_help(string str)
{
    if (str != "here" && str != "archive" && str != "archives")
	return 0;

    str = library_help();
    write(str);
    return 1;
}

public void
leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

/*
 * Add custom commands and control who has them.
 */
public void
init(void)
{
    ::init();

    if (IS_MEMBER(TP) || IS_GMASTER(TP))
    {
	init_library();
	add_action(archive_help, "help");
    }
}
