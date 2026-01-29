/*
 *  Based on /d/Sparkle/guilds/new_merc/library.c
 *
 *  This is the guild library for the SoHM.
 *
 */
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <mail.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;
inherit "/lib/guild_library";

#define HOW_MANY 3
#define SOHM_I_SEARCH_BOOKSHELF   "_sohm_i_search_bookshelf"
#define SOHM_I_FOUND_SUACOVISP    "_sohm_i_found_suacovisp"

/* Prototypes */
public void        init();
public mixed *     library_hook_get_approval_names();
varargs mixed      add_new_book(string title, string contents, 
                                string author, string shelf = "",
                                string filename = "", 
                                string book_id = "");

void
reset_poolbottom_room()
{       
	return;
}


create_poolbottom_room()
{
    set_short("the central library of the school of High Magic");
    set_long("You stand within the central library of the school of High Magic. " +
        "Tall bookshelves of dark mahogany fill the room, creating a maze-like warren " +
        "that the careless student could easily get lost in. To the north and south " +
        "are wings of the library you can explore further, while a passageway to your " +
        "east takes you out to the great hall. A long table stands between bookshelves " +
        "here, covered with scrolls. There is a plaque near " +
        "the entry to the library to assist students who wish to use the library.\n");

    add_item(({"long table","table","scrolls"}),"@@exa_table");

    add_item(({"library","central library","large central library"}),
        "Tall bookshelves fill the room in a seemingly chaotic order, making the " +
        "size of the library seem bigger than it probably is. And while there is an " +
        "impressive number of books and tomes in here, it doesn't rival the more " +
        "famous collections rumoured to be held in the Library of Palanthas or the " +
        "Tower of Wayreth.\n");

    add_item(({"bookshelves","tall bookshelves","mahogany","bookshelf","shelves","shelf"}),
        "Tall bookshelves of dark mahogany fill the room in a seemingly chaotic order, making the " +
        "size of the library seem bigger than it probably is. And while there is an " +
        "impressive number of books and tomes in here, it doesn't rival the more " +
        "famous collections rumoured to be held in the Library of Palanthas or the " +
        "Tower of Wayreth.\n");

    add_item(({"books","tomes"}),
        "The library has an impressive number of books and tomes. A plaque near the entry to the library " +
        "explains how to access those of relevance to you.\n");

    add_item(({"north","north wing"}),"You can continue further into the north wing of the " +
        "library, where you can train spellcraft and spell forms.\n");

    add_item(({"south","south wing"}),"You can continue further into the south wing of the " +
        "library, where you can learn about the magical elements.\n");

    add_item(({"wings"}),"You can explore the north wing and south wing of the library.\n");

    add_exit(ROOM + "ng_hall","east",0);
    add_exit("/d/Krynn/guilds/sohm/room/training","north",0);
    add_exit("/d/Krynn/guilds/sohm/room/training_elements","south",0);

    set_library_book_object(EOBJ + "sohm_book");

    setuid();
    seteuid(getuid());

    // Guild Library Specific Items
    set_library_save_path(BOOKS_DIR);
    set_library_allow_new_books(1);

    create_library();

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);
    add_cmd_item("kampiunarcanis","practice","@@learn_kampiunarcanis");
    add_cmd_item("the silver-trimmed tome","study","@@learn_suacovisp");

    add_search(({"bookshelves","tall bookshelves","bookshelf","shelves","shelf"}),
        10,"search_bookshelves",1);
}

string
search_bookshelves(object searcher, string what)
{
    int times = this_player()->query_prop(SOHM_I_SEARCH_BOOKSHELF);
    if (CAN_SEE_IN_ROOM(this_player()))
      {
	  if (times >= HOW_MANY)
	    {
            if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacovisp"))
             {
		this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, HOW_MANY);

                tell_room(environment(this_player()), QCTNAME(this_player()) + 
                " searches through one of the bookshelves, looking for " +
                "something of interest.\n", ({ this_player() }));

		return ("You don't find anything else in the library that you " +
                "could learn at this stage.\n");
              }
		  this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, HOW_MANY);
		  this_player()->add_prop(SOHM_I_FOUND_SUACOVISP, 1);

                  tell_room(environment(this_player()), QCTNAME(this_player()) + 
                  " searches through one of the bookshelves, looking for " +
                  "something of interest.\n", ({ this_player() }));

		  return ("You continue searching through the bookshelves for anything " +
                  "of interest. What is this? You come across a silver-trimmed tome " +
                  "that explains the spell Wind Whisper, 'Suaco Visp'! Perhaps you " +
                  "could <study the silver-trimmed tome> to scribe it into your spellbook?\n");
	    }
	  else
	    {
		this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, times + 1);
                tell_room(environment(this_player()), QCTNAME(this_player()) + 
                " searches through one of the bookshelves, looking for " +
                "something of interest.\n", ({ this_player() }));
		return ("You search through the bookshelves for spells of interest. " +
                "You don't uncover anything on this particular search.\n");
	}
    }
  return 0;
}

string
learn_suacovisp()
{

    if(!this_player()->query_prop(SOHM_I_FOUND_SUACOVISP)) 
    {
        write("Study the silver-trimmed tome? There are a number in the library.. " +
           "perhaps you should search the bookshelves for a specific one.\n");
        return "";
    }

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        write("You don't have the patience of a student to learn even basic " +
          "cantrips here!\n");
        return "";
    } 

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"kampiunarcanis"))
    {
        write("You realise you don't know how to decipher and comprehend unfamiliar " +
          "spell runes. Perhaps something in the library can help you with that?\n");
        return "";
    }

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the magical " +
        "writing in the silver-trimmed tome. Perhaps try again after preparing yourself " +
        "to 'read magic'?\n");
        return "";
    }

    if(this_player()->query_skill(SS_SPELLCRAFT) < 30)
    {
	write("Your spellcraft skills are too poor to learn even this minor cantrip. " +
        "Train your spellcraft higher before trying to learn 'Suaco Visp'.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + " tries to "+
        "comprehend what is written in a silver-trimmed tome, " +
        "but doesn't have the spellcraft skills.\n", ({ this_player() }));
	return "";
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacovisp"))
    {
        write("Having already scribed Wind Whisper in to your spellbook, " +
         "you feel no need to practise this cantrip any further here.\n");
        return "";
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"suacovisp"))
    {
    write("You read through the silver-trimmed tome, deciphering that the runes describe " +
       "a divination spell that allows you to send a message using air magic to another " +
       "person in the realms. Once comprehended, you swiftly copy the spell 'Suaco Visp' " +
       "in to your spellbook.\n");
    say("After studying a tome found on one of the library's bookshelves, " 
        +QTNAME(this_player()) + " begins copying a spell in to " +HIS(this_player())+
        " spellbook.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"suacovisp");
        return "";
    }

    return "";
}

string
exa_table()
{
    string str;

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        str = "You see a number of scrolls on the long table here " +
        "in the library, however not being a student here they aren't of much " +
        "interest to you.\n";
        return str;
    } 

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"kampiunarcanis"))
    {
        str = "Looking through the scrolls on the table you notice a number of " +
        "them are about 'Kampiun Arcanis' - mental exercises to help calm the mind, " +
        "providing the concentration required to 'read magic'. With this material you " +
        "could <practice kampiunarcanis>.\n";
        return str;
    }

    return "You see a number of scrolls on the long table here in the library, " +
        "although most you are already familiar with and don't interest you.\n";

}

string
learn_kampiunarcanis()
{
    if(this_player()->query_skill(SS_SPELLCRAFT) < 25)
    {
	write("Your spellcraft skills are too poor to learn even this minor cantrip. " +
        "Train your spellcraft higher before trying to learn 'Kampiun Arcanis'.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + " tries to "+
        "learn the mental exercises required to read magic, " +
        "but doesn't have the spellcraft skills.\n", ({ this_player() }));
	return "";
    }

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        write("You don't have the patience of a student to learn even basic " +
          "cantrips here!\n");
        return "";
    } 

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"kampiunarcanis"))
    {
        write("Having already scribed Kampiun Arcanis into your spellbook, " +
         "you feel no need to practise this cantrip any further here.\n");
        return "";
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"kampiunarcanis"))
    {
    write("After a short period of practice, you manage to learn the mental techniques of " +
       "'Kampiun Arcanis', allowing you to decipher and comprehend unfamiliar spell runes. " +
       "You swiftly copy the cantrip in to your spellbook!\n\n" +
       "Congratulations! You have scribed your first spell! You will find it now listed in " +
       "your spellbook, and you will be able to find out more details of that spell through " +
       "<help sohm kampiunarcanis>.\n\n" +
       "Note - you will not be able to cast the spell until you 'memorise' it. Once memorised " +
       "the spell will appear in your 'spells' list. You should also note that the number " +
       "of spells you can memorise increases as you progress in guild title. You can change what " +
       "spells you memorise, however how frequently you can do this is restricted by the 'Arcane " +
       "Focus' skill.\n");
    say("After a short period of practice, " +QTNAME(this_player()) + " manages to learn the " +
        "mental techniques required to to decipher and comprehend unfamiliar spell runes.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"kampiunarcanis");
        return "";
    }

    return "";
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
    return player->query_wiz_level();
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
    return ({ "arman" });
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

    CREATE_MAIL("New book " + author, "SoHMLibrary",
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

