/* 
 * The library in the tower of Wayreth.
 *
 * Copy of the library in Vkeep. 
 * Changed for the use in Wayreth. 
 * Jeremiah, 95/07/26
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <mail.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit TOWERROOM;
inherit "/lib/guild_library";

#define BOOKS_DIR "/d/Krynn/guilds/wohs/books/"

/* Prototypes */
public void        init();
public mixed *     library_hook_get_approval_names();
varargs mixed      add_new_book(string title, string contents, 
  string author, string shelf = "",
  string filename = "", 
  string book_id = "");

void
reset_tower_room()
{
    return;
}

void
create_tower_room()
{
    set_short("great library of the Tower of High Sorcery");
    set_long("You find yourself in a huge library. Lined along the high " +
        "walls are shelves with numerous books of different materials, " + 
        "colours and sizes. A treasure of information and " + 
        "knowledge is stored here, unrivalled in the realms with the " +
        "exception of perhaps the Library at Palanthas. Wizards may " +
        "<research> the tomes and spell scrolls here in an effort to " +
        "learn new spells. Here wizards can also pen their own " +
        "experiences, thoughts or bits of information. There is a " +
        "plaque near the entry instructing on the use of the library.\n");

    set_wall_type(2);

    add_exit(WTOWER + "study", "east", 0);

    set_library_book_object("/d/Krynn/wayreth/obj/wohs_book");

    setuid();
    seteuid(getuid());

    // Guild Library Specific Items
    set_library_save_path(BOOKS_DIR);
    set_library_allow_new_books(1);

    create_library();

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);
    add_cmd_item(({"spells","new spells","tomes","tomes and spell scrolls"}),
        "research","@@research_new_spells");
}

/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    init_library();

} /* init */


/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 */
public int 
query_librarian(object player)
{
    // By default only wizards are librarians. However, if you want,
    // return 1 here if we change that to allow players.
    //
    // Librarians have the ability to create/remove/delete, etc.

    if(QUERY_WHITE_COUNCIL(player) || QUERY_RED_COUNCIL(player) ||
       QUERY_BLACK_COUNCIL(player) || player->query_wiz_level())
       return 1;
    else
       return 0;

}


/*
 * Function name: library_hook_get_approval_names
 * Description  : This routine can be redefined in the library code to provide
 *                the names of the players who are authorized to approve books
 *                before they are added to the library. If this is the case,
 *                those players will receive a mail informing them of the fact
 *                that a new book has been submitted.
 * Returns      : string * - the list of names (in lower case).
 */
public mixed *
library_hook_get_approval_names()
{
    string * wohs_librarians = ({ });

    if(sizeof(WIZ_GUILDMASTER))
	wohs_librarians += WIZ_GUILDMASTER;

    if(WOHS_MANAGER->query_is_council_white())
	wohs_librarians += ({ WOHS_MANAGER->query_is_council_white() });

    if(WOHS_MANAGER->query_is_council_red())
	wohs_librarians += ({ WOHS_MANAGER->query_is_council_red() });

    if(WOHS_MANAGER->query_is_council_black())
	wohs_librarians += ({ WOHS_MANAGER->query_is_council_black() });

    return wohs_librarians;

} /* library_hook_get_approval_names */


/*
 * Function name: add_new_book
 * Description  : Add a new book to the shelves
 * Arguments    : title - the title of the book
 *              : contents - the contents of the book
 *              : author - the author of the book
 *              : shelf (optional) - the shelf on which to place the book
 *              : filename (optional) - which filename to use for storing the
 *              :       content
 *              : book_id (optional) - the id by which the book is known
 * Returns      : a filename which contains the contents or 0 on failure
 *
 * I mask this from the parent so that I can have it generate a mail
 * and send it to whoever I have deemed to be the current guild
 * librarian.
 */
varargs mixed
add_new_book(string title, string contents, 
  string author, string shelf = "", string filename = "", 
  string book_id = "")
{
    mixed  submitted = ::add_new_book(title, contents, author, shelf,
        filename, book_id);
    string *names = library_hook_get_approval_names();

    if (!submitted)
    {
	return 0;
    }

    CREATE_MAIL("New book " + author, "WoHSLibrary",
      implode(names, ","), "",
      "========================================================="
      + "======================\n"
      + "Title: " + title + "\n"
      + "========================================================="
      + "======================\n\n"
      + contents + "\n"
      + "---------------------------------------------------------"
      + "----------------------\n");

    return submitted;
} /* add_new_book */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * This function is redefined to force players to stand up before
 * leaving if they are currently sitting in a chair. Also, we set up
 * some special library leave functions.
 */
public void
leave_inv(object ob, object to)
{
    object   oldtp;

    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 

string
research_new_spells()
{

    if(WOHS_MANAGER->query_wayreth_study_time(this_player()) > time())
    {
	string recover_str = "a bit of time";
	int mem_time = WOHS_MANAGER->query_wayreth_study_time(this_player());
	int recover_time = mem_time - time();

	if(recover_time < 1800)
	    recover_str = "less than half an hour";
	else if(recover_time < 3600)
	    recover_str = "less than an hour";
	else if(recover_time < 7200)
	    recover_str = "approximately one hour";
	else if(recover_time < 172800)
	{
	    int recover_hours = recover_time / 3600;
	    recover_str = "approximately " +recover_hours+ " hours";
	}
	else
	{
	    int recover_days = recover_time / 86400;
	    recover_str = "approximately " +recover_days+ " days";
	}

	return "You will need to wait " +recover_str+ " before you " +
	"can continue your research in the library seeking out new " +
	"spells.\n";
    }


    // Researchable spells: dazzle, mirror portal, identify,
    //                      detect resistances, haste, scare
    //                      detect magic, speak with dead, 
    //                      fire dart, dimensional rift, blur
    //                      polymorph self (bird form),
    //                      foreshock, team teleport (final spell)
    string * eligible_spells = ({ });
    string * researchable_spells = ({"okiai",  
      "dotonobsule", 
      "odenarcanis", 
      "ickrakfethos", 
      "temep",
      "wintektor",
      "ickrakarcanis",
      "ukrisrivek",
      "apianak",
      "reskafar",
      "kadenadon",
      "thirkualtiui",
      "edarjikmada" });

    int research_result = random(100);

    foreach(string spell: researchable_spells)
    {
	if(!WOHS_MANAGER->query_scribed_spell(this_player(), spell))
	{
	    eligible_spells += ({ spell });
	    // DEBUG("Spell added to eligible_spells: " +spell+ ".");
	}
    }

    if(!sizeof(eligible_spells))
    {
        // Final learnable spell is team teleport
	if(!WOHS_MANAGER->query_scribed_spell(this_player(), "svihossalur"))
        {
	    WOHS_MANAGER->scribe_spell_to_spellbook(this_player(), "svihossalur");
	    say(QCTNAME(TP)+ " pours over the tomes and scrolls of the " +
	        "library seeking insights into new spells, and has a " +
	        "research breakthrough!\n");
	    return "You pour over the tomes and scrolls of the huge " +
	        "library, learning tidbits and interesting factoids " +
	        "about magic lore, and manage to learn svihossalur!\n";
        }
	return "There are no further spells you can learn through " +
	"study in this library. You will need to seek new spells " +
	"out in the realms!\n";
    }

    string random_spell = eligible_spells[random(sizeof(eligible_spells))];

    // The first spell new WoHS can research is 'identify magic'.

    if(!WOHS_MANAGER->query_scribed_spell(this_player(), "odenarcanis"))
        random_spell = "odenarcanis";

    WOHS_MANAGER->add_wayreth_study_time(this_player());

    switch(research_result)
    {
    case 0..49:
	say(QCTNAME(TP)+ " pours over the tomes and scrolls of the " +
	  "library seeking insights into new spells.\n");
	return "You pour over the tomes and scrolls of the huge " +
	"library, learning tidbits and interesting factoids " +
	"about magic lore. However you'll need to come back " +
	"and do more research before being close to a new " +
	"spell discovery.\n";
	break;
    default:
	WOHS_MANAGER->scribe_spell_to_spellbook(this_player(), random_spell);
	say(QCTNAME(TP)+ " pours over the tomes and scrolls of the " +
	    "library seeking insights into new spells, and has a " +
	    "research breakthrough!\n");
	return "You pour over the tomes and scrolls of the huge " +
	    "library, learning tidbits and interesting factoids " +
	    "about magic lore, and manage to learn " +random_spell+ "!\n";
	break;

    }
    return "";
}

/*
 * Function name: library_borrow_cmd 
 * Description  : The code for the 'borrow' command
 * Arguments    : args - the command line arguments
 * Returns      : 0 on failure, 1 on success
 */
int library_borrow_cmd(string args)
{
    // Syntax check
    if(!args || args == "")
    {
        notify_fail("Borrow what " + library_book_type + "?\n");
        return 0;
    }

    notify_fail("With some wizards having been found taking a liberal-kenderish " +
        "approach to 'borrowing' books from the library, you may only " +
        "'read <book number>' until further notice.\n");
    return 0;
/*
    write("You start searching the shelves for the " + library_book_type + ".\n");
    say(QCTNAME(this_player()) + " starts to search the shelves.\n");
    set_alarm(4.0, 0.0, &give_book_to_player(this_player(), args));
    return 1;

*/
}

/*
 * Function name: query_player_access
 * Description  : Return a list of the levels that the player have access to
 * Arguments    : player - the player we want to check
 * Returns      : an array with access levels
 */
string *query_player_access(object player)
{
    // Add librarian access to librarians
    if(query_librarian(player))
        return ({ "librarian", "normal", "seventh", "fifth", "third", "greater" });

    // Wizard of the 7th Circle
    if(WOHS_GUILD_LEVEL(player) > 2)
        return ({ "normal", "seventh" });

    // Wizard of the 5th Circle
    if(WOHS_GUILD_LEVEL(player) > 4)
        return ({ "normal", "seventh", "fifth" });

    // Wizard of the 3rd Circle
    if(WOHS_GUILD_LEVEL(player) > 6)
        return ({ "normal", "seventh", "fifth", "third" });

    // Greater Wizard
    if(WOHS_GUILD_LEVEL(player) > 9)
        return ({ "normal", "seventh", "fifth", "third", "greater" });    

    // Non wizzes get access to the normal shelf only
    return ({ "normal" });
}
