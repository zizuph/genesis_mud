/* The new library in the Solamnian guild
* 
* Aridor, 10/96
*
* Employs a librarian to sort the books.
*/

#include <ss_types.h>
#include "lib.h"
#include "../knight/guild.h"

inherit IN_BASE;
inherit STDLIB + "library";
inherit "lib/skill_raise";

object knight;

public void set_up_skills();
void reset_vin_room();

void
create_vin_room()
{
    set_short("Library of Vingaard Keep");
    set_long("You are standing in the famous library of Vingaard Keep. " +
      "Here, many generations of Knights have gathered books from all " +
      "over Krynn. There are books of various content here. Some " +
      "written by Knights, some by kender, and some by unknown authors. " +
      "There is a desk here with a plaque on it with instructions how " +
      "to use this library. On the wall hangs a sign and to the " +
      "east is a small alcove used for composing books. A new "+
      "door lies to the north, leading into a room.\n");

    add_item("desk", "@@desk");
    add_item(({"plaque","sign"}),
      "It's made of some kind of metal, words are written on it.\n");
    add_cmd_item("plaque", "read", "@@read_plaque");
    add_cmd_item("sign",   "read", "@@read_sign");

    add_exit(VROOM + "crest_room", "north", 0);
    add_exit(VROOM + "joinroom", "west", 0);
    add_exit(VLIB + "library2", "east", 0);
    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
      "teleportation in this area... or is it something else?\n");

    set_lib_id("vkeep_lib_id");
    set_lib_path(VLIB);
    set_lib_type(4);
    set_lib_long("the library of the Solamnian Knights in Vingaard Keep");
    set_search_delay(8.1);
    set_default_topics((["New Arrivals":1,
	"Maps":0,
	"Guilds in Genesis":0,
	"Places in Genesis":0,
	"Krynn in General":0,
	"Genesis in General":0,
	"Knights of Solamnia":0,
	"Histories of Knights":2,
	"Knights Private Section":2,
	"Trash":1]));
    setup_library();

    create_skill_raise();
    set_up_skills();

    reset_vin_room();
}

void
set_up_skills()
{
    sk_add_train(SS_LANGUAGE, "read and speak in other languages",    0, 0, 65 );
}

void
reset_vin_room()
{
    if (knight)
	return;

    knight = clone_object(VNPC + "sanguin");
    knight->move_living("xx", TO);
}

int
sk_improve(string sk)
{
    if (sk)
    {
	if (!MEMBER(TP))
	{
	    NF("You are no member of this guild, you cannot train "+
	      "here.\n");

	    write("Only Knights of Solamnia can improve their skills "+
	      "here.\n");
	    return 1;
	}
    }
    if (!P(knight, TO))
    {
	write("The trainer isn't here to train you.\n");
	return 1;
    }

    if (REALAGE(TP) < TP->query_skill(SS_DISGRACED))
    {
	write("You are currently banned from training!\n");
	return 1;
    }

    TP->remove_skill(SS_DISGRACED);

    return ::sk_improve(sk);
}

int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
      "seek knowledge elsewhere.\n");
    return 0;
}

string
desk()
{
    if (!knight || !present(knight, TO))
	return "Behind this desk usually stands a Knight to help " +
	"you with get the books you want but he's nowhere to be " +
	"seen now.\n";
    else
	return "Behind the desk stands a Knight, eager to " +
	"find the books you are looking for.\n";
}


void
init()
{
    init_library();
    init_skill_raise();
    ::init();
}

void
leave_inv(object player, object dest)
{
    ::leave_inv(player, dest);
    library_leave_inv(player, dest);
}

string
read_plaque()
{
    write("The Library of Vingaard Keep\n" +
      "============================\n\n" +
      "Check the 'index' for a list of topics, and the 'catalog' of each " +
      "topic for a list of available books. You can then 'borrow' any of " +
      "the available books. Note that you must give the complete title of " +
      "a book (up to any '-') you want to borrow. Please do not forget to " +
      "return borrowed books!\n\n" +
      "To write a new book you should give the command 'blank'. " +
      "Then the knight will give you a blank book, which is yours to " +
      "fill with whatever you want, maps, songs, or a novel perhaps? " +
      "The command to start writing is 'bedit'. You write a " +
      "book much the same way you write a note on the board. There " +
      "will be private rooms you can enter so others won't disturb " +
      "you if you try to write something. Good luck.\n");
    return "";
}

string
read_sign()
{
    write("LIBRARY - QUIET PLEASE!\n\n" +
      "Current Librarian: " + (librarian && sizeof(librarian) ? C(librarian[0]) : "-") + "\n" +
      "The High Clerist is responsible for 'appoint'ing or 'unappoint'ing " +
      "the librarian.\n");
    if (librarian && sizeof(librarian) && TP->query_real_name() == librarian[0])
      write("As librarian, you have these commands available:\n" +
	    " Beautify <bookname>\n" +
	    "       Allows you to change the title, or align the title neatly.\n" +
	    " Edit <bookname>\n" +
	    "       Allows you to edit a book or add to it.\n" +
	    " Movebook <bookname> to topic <newtopic>\n" +
	    "       To remove a book completely, use 'Movebook <bookname> to topic trash'.\n" +
	    " Erase <bookname> | '-all books in trash-'\n" +
	    "       Destroy a book (must be in the trash) unrecoverably.\n" +
	    " Create <new topic> <access level>\n" +
	    "       Access level is: 0: everyone\n" +
	    "                        1: librarian only\n" +
	    "                        2: knights only\n" +
	    " Uncreate <old topic>\n" +
	    " Retire\n");
    return "";
}

void
hook_leave_with_books(object who, int i)
{
    who->catch_msg("The Knight runs after you and takes the book" +
      (i > 1 ? "s" : "") + " you didn't return.\n"); 
    tell_room(TO, QCTNAME(who) + " tried to take " +
      (i > 1 ? "some books" : "a book") + " from " +
      "the library. The Knight got " +
      (i > 1 ? "them" : "it") + " back.\n",who);
}

void 
hook_borrow()
{
    write("You ask the Knight for a book, and the Knight runs off to " +
      "search for the book.\n");
    tell_room(TO, QCTNAME(TP) + " asks for a book. The Knight runs off.\n",
      TP);
    knight->move_living("into the magazine",VOID);
}

mixed
hook_can_access_catalog(int level)
{
    /* 0: everyone can read
    * 1: librarian only can read
    * above levels are handled directly,
    * we only need to take care of the ones below
    *
    * we add these access classes:
    * 2: knights only can read 
    */
    if (level == 2)
	return ({ !!(TP->query_knight_level()),"Knights only" });

    return ({ 0,"No access" });
}

int
hook_can_use_library()
{
    return !!(knight && P(knight,TO));
}

int
hook_appoint_unappoint()
{
    /* Sword conclave can appoint/unappoint */
    if ((ADMIN)->query_conclave("sword") == TP->query_name() ||
        (ADMIN)->is_grandmaster(TP->query_real_name()) ||
      member_array(TP->query_name(), GUILDMASTERS) >= 0)
	return 1;

    return 0;

    return (TP->query_knight_level() == 4 &&
      TP->query_knight_sublevel() == 11);
}

void
hook_appointed_info()
{
    write("Note: The appointed librarian must meet the requirements " +
      "(Knight of the Sword, at least Elder of Swords), otherwise " +
      "the position will become vacated again automatically after " +
      "an unsuccessful try.\n");
}

int
hook_librarian_requirements()
{
    /* Temporarily added (no sword Knights) */
    return (TP->query_knight_level() > 1);

    return (TP->query_knight_level() == 4 &&
      TP->query_knight_sublevel() > 6);
}

public int
hook_find_book(object who)
{
    knight->move_living("xx",TO);
    if (!present(who,TO))
    {
	tell_room(TO,"The Knight looks around and states: Wasn't " +
	  "there someone here looking for a book just now?\n" +
	  "The Knight shrugs helplessly.\n");
	return 0;
    }
    return 1;
}

public void
hook_found_book(object who)
{
    tell_object(who, "The Knight gives you the ordered book.\n");
    tell_room(TO, "The Knight gives out an ordered book.\n", who);
}

public void
hook_book_not_found(object who,string bname)
{
    tell_object(who, "The Knight tells you: The book that " +
      "you were looking for doesn't exist.\n");
    tell_room(TO, "The Knight is without the ordered book.\n", who);
}

public void
hook_book_currently_borrowed(object who, string bname)
{
    tell_object(who, "The Knight tells you: That book has " +
      "already been borrowed.\n");
    tell_room(TO, "The Knight is without the ordered book.\n", who);
}

public void
hook_give_blank_book(int state)
{
    say(QCTNAME(TP) + " got a blank book from the Knight.\n");  
    write("The Knight gladly hands you a blank book.\n");
    if (state)
    {
	say("But it was too heavy. The books falls to the ground.\n");
	write("It's too heavy for you, you drop it.\n");
    }
}

