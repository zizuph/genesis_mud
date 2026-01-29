
/*
 * Library of the Elemental Temple of Calia
 * 
 * Created by Jaacar, July 2016
 *
 * - 2020-11-24 - Mirandus
 *   Fixed an issue where a player would remain
 *   in the room when linkdead.
 */

#pragma strict_types

inherit "/std/room";
inherit "/lib/guild_library";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

// Defines
#define LIVE_I_SITTING "_live_i_sitting"

// Prototypes

// Global Variables
public object   sphere = 0;
public object tahla;

void 
create_room()
{
    set_short("Elemental Temple Library");
    set_long("@@desc_long_description");    
                   
    add_exit(ELEMENTALIST_TEMPLE + "outer14a", "north", "@@check_sitting", 1);     
    
    add_item( ({ "hall", "library" }),
        "This is the Library of the Elemental Temple of Calia.\n");
    
    add_item( ({ "ceiling", "petrified wood", "beams", "wooden beams" }),
        "The ceiling here is made from the same petrified wood as the rest "
      + "of the temple. However, here it does not form "
      + "an arch, but has a flattened roofing made from beams of petrified "
      + "wood. The petrified wood seems to have grown thin stalactites, and "
      + "on the tip of each stalactite a large globe of white fluorescent "
      + "stone shines a pleasant light throughout the library.\n");
      
    add_item( ({ "door", "slender door", "north" }),
        "A tall door, crafted by an intrinsic mix of dark oak and petrified "
      + "wood is rather slender. The door itself is also remarkably hefty, "
      + "likely to prevent sounds from the outside travelling into the library.\n");
    
    add_item( ({ "globes", "globe", "glowing globes", "glowing globe",
            "massive glowing globes", "massive glowing globe", "massive globe",
            "massive globes", "stalactites", "stones", "massive stones" }),
        "Suspended from stalactites, these globes are massive stones of an "
      + "unknown origin, radiating a strong yet pleasant glow that illuminates "
      + "the library.\n");
   
    add_item( ({ "bookcases", "bookcase", "bookshelf", "bookshelves", "shelf",
        "shelves" }),
        "These tall bookcases are rather simple and devoid of any "
      + "ornamentation. They are very sturdy and made from a heavy dark oak. "
      + "Books, scrolls, and tablets of many kinds are organized neatly, "
      + "filling the shelves. You could try and <list> the shelves to "
      + "see if anything strikes your fancy.\n");
    
    add_item( ({ "books", "scrolls", "tablets", "writings", "tomes", "tome",
        "archaic tablets", "fresh scrolls", "ancient leather-bound tomes" }),
        "Writings of every kind can be found here, ranging from ancient "
      + "leather-bound tomes to fresh scrolls and archaic tablets with "
      + "obscure symbols in languages lost in the dim of time. You could "
      + "<list> the shelves to gain more knowledge, or perhaps pen works "
      + "of your own to add to the magnificence of this library.\n");
    
    add_item( ({ "symbols", "languages", "obscure symbols", "lost languages" }),
        "The obscure symbols range from Tengwar to Argosian scriptures. Some "
      + "are too ancient or obscure to possibly decipher. If you were to "
      + "<list> the shelves here, you would know which works were "
      + "available for you to read.\n");
    
    add_item( ({ "desk", "desks", "wooden desk" }),
        "Which desk, the massive wooden desk or the reading desks?\n");
    
    add_item( ({ "massive desk", "massive wooden desk", "thick filing cabinets",
        "cabinets", "filing cabinets", "cabinet", "thick filing cabinet",
        "filing cabinet", "working space" }),
        "A delicate mix of petrified wood and light ash wood have been paired "
      + "and elegantly carved into a grand L-shaped desk. A pair of "
      + "thick filing cabinets occupy the space underneath it.\n");
    
    add_item( ({ "assistants", "assistant", "elderly half-elven lady",
        "old dwarven scholar", "lady", "scholar", "dwarven scholar",
        "half-elven lady" }),
        "An elderly half-elven lady wearing a simple woolen robe with her "
      + "silvery hair in a tight bun along with an old dwarven scholar "
      + "with a massive set of spectacles and a slightly rumpled brown robe "
      + "are busy maintaining the temple library.\n");
    
    add_item( ({ "reading desks", "reading desk" }),
        "These are simple reading desks, some of which are tall allowing "
      + "one to stand while working. There are also some lower tables, each "
      + "with a comfortable wooden chair. You could try to <sit> at one "
      + "of the reading desks.\n");
      
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "A thunderous voice echoes in your mind: "
        + "This Temple is a peaceful place! There will "
        + "be no violence in this divine sanctuary.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "A thunderous voice echoes in your mind: "
        + "This Temple is a peaceful place! There will "
        + "be no violence in this divine sanctuary.\n");     
    
    set_library_save_path(LIBRARY_SAVE_PATH);
    set_library_allow_new_books(1);

    set_library_book_type("scroll");
    set_library_book_object(LIBRARY_BOOK_OBJECT);

    add_library_access_level("normal", "Everyone");
    add_library_access_level("seekers", "Seekers");
    add_library_access_level("secrecy", "Secrecy");
    add_library_access_level("worshippers", "Worshippers");
    add_library_access_level("clerics", "Clerics");
    add_library_access_level("elders", "Elder Clerics");
    add_library_access_level("kyrullians", "Kyrullians");
    add_library_access_level("council", "Council Members");
    add_library_access_level("librarian", "Librarian");
    
    set_library_librarian_level("owner");

    create_library();

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);
    reset_room();
}

public string
desc_long_description()
{
    string long_desc = 
          "You have entered a vast library hall within the Elemental "
        + "Temple of Calia. A sense of order and reverence emanates from the "
        + "very foundations of this room. The grey stone walls are covered "
        + "from floor to vaulted ceiling with massive oaken bookcases. "
        + "A massive wooden desk occupies the northeastern area of this room "
        + "along with filing cabinets used by the library staff. To the north "
        + "and southwest, wooden bookcases line the area, and the "
        + "southeastern region holds several reading desks. Suspended from "
        + "the wooden ceiling are massive glowing globes, providing the "
        + "illumination needed for both studying and writing. A slender door "
        + "leads north. Hanging from one of the pillars you see a plaque and "
        + "a sign. ";    

    return long_desc += "\n\n";
}

/*
 * Function name: library_hook_list_books
 * Description  : Called when a player lists the contents of a shelf
 * Arguments    : name - the name of the shelf being listed
 */
void library_hook_list_books(string shelf_name, mixed *shelf_data, mixed *books)
{
    int i;

    // Check for empty shelves
    if(sizeof(books) == 0)
    {
        write("The shelf '" + shelf_name + "' is empty.\n");
        return;
    }

    // Display the list
    write(shelf_data[0] + ":\n\n");
    write(sprintf("%-6s %-15s %s\n", "Number", "Author", "Title"));
    write(sprintf("%-6s %-15s %s\n", "------", "---------------", 
        "------------------------------------------------------"));
    for(i=0;i<sizeof(books);i++)
    {
        write(sprintf("%-6s %-15s %s\n", 
            books[i],
            capitalize(library_data["books"][books[i]][3]),
            library_data["books"][books[i]][1]));
    }
}

string *query_player_access(object player)
{
	if (player->query_wiz_level())
	{
		return ({ "normal", "seekers", "secrecy", "worshippers", "clerics",
		"elders", "librarian", "council", "kyrullians" });
	}

	if (GUILD_MANAGER->query_is_luminary(player))
	{
		return ({ "normal", "seekers", "secrecy", "worshippers", "clerics",
		"elders", "librarian", "council", "kyrullians" });
	}
	
	if (GUILD_MANAGER->query_is_ew_council(player))
	{
		return ({ "normal", "seekers", "secrecy", "worshippers", 
		    "council", "librarian" });
	}
	
	if (GUILD_MANAGER->query_is_ec_council(player))
	{
		return ({ "normal", "seekers", "secrecy", "worshippers", "clerics",
		"elders", "librarian", "council", "kyrullians" });
	}
	
	if (GUILD_MANAGER->query_is_elder_cleric(player))
	{
		if (GUILD_MANAGER->query_is_racial(player))
		{
			return ({ "normal", "seekers", "secrecy", "worshippers", "clerics",
				"elders", "kyrullians" });
		}
		else
		{
			return ({ "normal", "seekers", "secrecy", "worshippers", "clerics",
				"elders" });
		}
	}
	
	if (IS_CLERIC(player))
	{
		if (GUILD_MANAGER->query_is_racial(player))
		{
			return ({ "normal", "seekers", "secrecy", "worshippers", "clerics",
				"kyrullians" });
		}
		else
		{
			return ({ "normal", "seekers", "secrecy", "worshippers", 
				"clerics" });
		}
	}
	
	if (IS_WORSHIPPER(player))
	{
		 return ({ "normal", "seekers", "secrecy", "worshippers" });
	}
	
	if (IS_SEEKER(player))
	{
		if (GUILD_MANAGER->query_can_do_wor_task_four(player) == 2)
			return ({ "normal", "seekers", "secrecy" });
		else
			return ({ "normal", "seekers" });
	}

    return ({ "normal" });
}

int 
query_librarian(object player)
{
    if(player->query_wiz_level() || 
    	GUILD_MANAGER->query_is_luminary(player) ||
    	GUILD_MANAGER->query_is_ew_council(player) ||
    	GUILD_MANAGER->query_is_ec_council(player))
        return 1;

    return 0;
}

/*
 * Function name: library_help
 * Description  : Get the help based on this_player()'s permissions
 * Returns      : a string
 */
string 
library_help()
{
    string  result;

    // Header
    result = "\nThe following commands are available in this library:\n"+
        "===========================================" +
        "==========\n";
    
    // Regular commands
    result += "list [shelf]     - list the available shelves, or " + 
                library_book_type + "s on that shelf.\n" +
              "catalog [shelf]  - same as the list command\n" +
//              "borrow <" + library_book_type + ">  - borrow the " + 
//              library_book_type + " with the id <scroll>\n" +
              "read <" + library_book_type + ">    - read the " + 
              library_book_type + " with the id <scroll>\n";

    // Add text when we allow new books
    if(library_allow_new_books && (IS_MEMBER(this_player())))
    {
        result += "\nYou can write your own " + library_book_type + 
            ", just get a <blank " + library_book_type + 
            ">. Instructions for use are on the " +
            library_book_type +" itself. Once you are done, you "+
            "can then <submit "+ library_book_type + "> and it "+
            "will be submitted for review.\n";
    }

    // Give the librarian extra options
    if(query_librarian(this_player()) || this_player()->query_wiz_level())
    {
        result += "\nThe following commands are available to you as " +
            "librarian:\n===========================================" +
            "==============\n"+
            "list unpublished - will show all unpublished books\n"+
            "renumber <old id> to <new id>\n" +
			"edit <" + library_book_type + " id>\n" +
            "assign  <" + library_book_type + " id> to <shelf name>\n" +                        
            "rename <" + library_book_type + " id> to <new title>\n" +                                    
            "remove " + library_book_type + " <" + library_book_type + " id>\n" +
            "showlevels - will show current access levels\n";
    }

    // Gives more help for wizzes
    if(this_player()->query_wiz_level())
    {
        result += "\nThe following commands are available to you as " +
            "a wizard:\n===========================================" +
            "=============\n"+
            "create shelf <shelf name> with title <shelf title>\n" +
	        "rename <old shelf name> to <new shelf name>\n" +
	        "change <shelf name> to <new title>\n" +
	        "access <shelf name> for <level>\n" +
	        "remove shelf <shelf name>\n" +
	        "Immortals can also 'lock' or 'unlock' specific " + 
            library_book_type + "s for editing.\n";
    }

    return result;
}

/*
 * Function name: library_blank_cmd
 * Description  : Allow the person executing the command to get a new book
 *              : so that they can submit new things to the library
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
int library_blank_cmd(string args)
{
    object  book;
    
    if (!IS_MEMBER(this_player()))
    	return 0;

    if(!args || args != library_book_type)
    {
        notify_fail("Blank what? A blank " + library_book_type + "?\n");
        return 0;
    }

    seteuid(getuid());
    book = clone_object(library_book_object);
    book->set_library(this_object());

    if(book->move(this_player()))
    {
        // We cannot carry the book
        write("You attempt to take a blank " + library_book_type + 
            " from the shelf but it is too heavy.\n");
        say(QCTNAME(this_player()) + " attempts to take a blank " +
            library_book_type + " from the shelf, but it is too heavy.\n");

        book->remove_object();
    }
    else
    {    
        write("You take a blank " + library_book_type + " from the shelf.\n");
        say(QCTNAME(this_player()) + " takes a blank " + library_book_type + 
            " from the shelf.\n");
    }

    // Log
    library_add_log("Received blank book.");

    return 1;
}

// This allows the librarian (or wizards) to see the current access levels
int
query_access_levels()
{
	int i;
	string *levels, ret;
	
	ret = "Known levels are:\n\n";
    levels = m_indexes(library_access_levels);
    for(i=0;i<sizeof(levels);i++)
    {
        ret += sprintf("%20s - %s\n", levels[i], 
            library_access_levels[levels[i]]);
    }
    
    if (query_librarian(this_player()))
    {
    	write(ret);
    	return 1;
    }
    else
    	return 0;
}

void 
init()
{
    ::init();
    init_library();
    add_action(query_access_levels,"showlevels");
    add_action("do_sit", "sit");
    add_action("do_stand", "stand");
    add_action("do_read", "read");
}

int
do_read(string str)
{
    if (!str)
    {
        notify_fail("Read what?  The sign maybe? Or a specific scroll?\n");
        return 0;
    }

    if (str == "sign")
    {
        write("The sign reads:\n  You may buy component pouches, herb jars, "+
            "silver ingots, sheathes for knives, gloves "+
            "for herbing, lanterns and oil.\n\n");
        return 1;
    }
    
    notify_fail("Read what?  The sign maybe? Or a specific scroll?\n");
    return 0;
}

public int
check_sitting()
{
    if (!this_player()->query_prop(LIVE_I_SITTING))
    {
        return 0;
    }
    
    write("You attempt to leave but realize that you are still "+
        "sitting in the chair. You'll have to stand up first.\n");
    say(QCTNAME(this_player()) + " attempts to leave while still sitting on "+
        "the chair!\n");
    
    return 1;
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 
public int
prevent_leave(object ob)
{
    int base_value = ::prevent_leave(ob);
    if (base_value)
    {
        return base_value;
    }
    
    if (ob->query_prop(LIVE_I_SITTING))
    {
        ob->catch_tell("You can't leave while sitting down! Try to <stand> "
            + "first.\n");
        return 1;
    }
    
    return base_value;
}*/

void 
leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

/*
 * Function name: do_sit
 * Description  : Allows the player to sit at a reading desk
 * Arguments    : arg - should be empty
 * Returns      : int 1/0 - success/failure.
 */
public int
do_sit(string arg)
{
    if (this_player()->query_prop(LIVE_I_SITTING))
    {
        notify_fail("You are already sitting at one of the reading desks!\n");
        return 0;
    }

    write("You find yourself an empty reading desk and sit down.\n");
    say(QCTNAME(this_player()) + " finds an empty reading desk and "
        + "sits down.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is sitting at one of the reading desks");
    this_player()->add_prop(LIVE_I_SITTING, 1);
    return 1;
}

/*
 * Function:    do_stand
 * Description: Function to allow someone to stand up from a reading desk.
 */
public int
do_stand(string arg)
{
    if (!this_player()->query_prop(LIVE_I_SITTING))
    {
        notify_fail("You are not sitting!\n");
        return 0;
    }
    
    write("You get out of the comfortable wooden chair and stand up.\n");
    say(QCTNAME(this_player()) + " gets out of the comfortable wooden "
        + "chair and stands up.\n");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    this_player()->remove_prop(LIVE_I_SITTING);
    return 1;
}

/*
 * Function name: reset_room
 * Description  : This function should be redefined to make the room reset
 *                every half hour or so. If you redefine it, you do not have
 *                to call enable_reset() since we call it as part of our
 *                service ;-) Note that this service is only valid for rooms.
 */
public void
reset_room()
{
    ::reset_room();
    setuid(); seteuid(getuid());
    // Clone the sphere for alpha testing
    if (!objectp(sphere))
    {
        sphere = clone_object(ELEMENTALIST_OBJS + "sphere");
        sphere->move(this_object(), 1);        
    }
    if (!objectp(tahla)) { 
         tahla = clone_object(ELEMENTALIST_NPCS +"tahla");
         tahla->set_width_desc("lean");
         tahla->set_height_desc("tall"); 
         tahla->move_living("steps out from behind a shelf", TO); 
     }     
}
