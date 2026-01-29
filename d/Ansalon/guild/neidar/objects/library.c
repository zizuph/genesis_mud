/*
 *  This is the guild library for the Neidar Clan.
 *  Vitwitch 12/2020
 *
 *  Based on SOHM Library by Arman
 *  ...which was in turn...
 *  Based on /d/Sparkle/guilds/new_merc/library.c by Gorboth
 *
 */

#pragma strict_types
#include "/d/Ansalon/common/defs.h"

inherit "/d/Ansalon/estwilde/std/inside_base";
inherit "/lib/guild_support";

#include "../guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <mail.h>
#include "/d/Krynn/common/clock/clock.h"

#define BOOKSSUBDIR "books/"

#define MORTAL_LIBRARIAN "logg"
#define IMMORTAL_LIBRARIAN "vitwitch"
// GUILD_WIZ is also a Librarian

inherit "/lib/guild_library";

/* Prototypes */
string             warrant_desc();
string             fineprint_desc();
int                ask_for_new_librarian(string proposed_librarian);
public void        init();
public void        leave_inv(object ob, object to);
public mixed *     library_hook_get_approval_names();
void               library_hook_stop_leave(object player, object *books);
void               library_hook_list_books(string shelf_name, mixed *shelf_data, mixed *books);
void               library_hook_list_shelves(string *shelves);
void               library_hook_receive_book(object player, object book);
varargs mixed      add_new_book(string title, string contents, 
                                string author, string shelf = "",
                                string filename = "", 
                                string book_id = "");

string
warrant_desc()
{
    return "The warrant chiselled into the wall accords " + capitalize(MORTAL_LIBRARIAN) + 
     " of the Neidar Clan the solemn duty of Librarian of this place. Fine print"+
     " is chiselled at the bottom of the wall.\n";
}
       
string
fineprint_desc()
{
    return "The fine print at the bottom of the wall reads:"+ 
           " The Thane can <recommend> a replacement librarian to the Wizard "
              + capitalize(GUILD_WIZ) + ".\n";
}


void
reset_dwarf_room()
{       
	return;
}


void
create_dwarf_room()
{
    set_short("library of the Neidar Clan");

    set_long("You stand within the Library of the mighty Neidar Clan -- " +
        "surrounded by towering stalagmites all illuminated by torch-light. "+
        "All of Dwarven wisdom is chiselled here in strata of ring-bound "+
        "stone books; compiled and piled so to last down through the Ages. "+
        "A warrant is carved in the stone of the wall in neat chiselled runes. " +
        "A plaque explains how to access and add to the wisdom held in this place.\n");

    add_item(({"bookshelves","strata","stalagmites","stalagmite","bookshelf","shelves","shelf"}),
        "Library-types might call them bookshelves, but a true dwarf knows a stalagmite " +
        "from stalactite from a pile of paper. An impressive number of heavy stone books "+
        "are stacked here according to categories. Each book is probably too heavy for any "+
        "elf or human to read! No one can truly say for sure, because they are not suffered to " +
        "enter this place -- as it is hallowed by all dwarvenkind. Some of the strata here are "+
        "restricted to the rheumy old eyes of Elders of the Clan.\n");

    add_item(({"books","tomes","stone books"}),
        "The library has an impressive number of books and tomes. Each of these is a hefty "+
        "bundle of ring-bound pages of finest mica. A plaque " +
        "explains how to access and add to all the wisdom of the Neidar held in this place.\n");

    add_item( ({"warrant",}), "@@warrant_desc");
    add_cmd_item(({"warrant", }), "read", warrant_desc);

    add_item( ({"fine print","fineprint",}), "@@fineprint_desc");
    add_cmd_item( ({"fine print","fineprint",}), "read", fineprint_desc);

    add_item(({"plaque", "plaques", "instructions", }), library_help);
    add_cmd_item(({"plaque", "plaques", "instructions", }), "read", library_help);

    add_exit(GUILD_ROOMS + "start","north",prevent_leave_with_books,0,0);

    setuid();
    seteuid(getuid());

    // Guild Library Specific Items

    set_library_book_object(GUILD_OBJS + "neidar_book");
    set_library_save_path(GUILD_DIR + BOOKSSUBDIR);
    set_library_allow_new_books(1);
    add_library_access_level("restricted", "Restricted");
    add_library_access_level("librarian", "Librarians-only");
    add_library_access_level("normal", "All Neidar");
    create_library();

}

public int 
query_librarian(object player)
{
    string name;
    int return_value;

    return_value = 0;

    name = player->query_real_name();

    if ( name == MORTAL_LIBRARIAN ) return_value++;
    if ( name == IMMORTAL_LIBRARIAN ) return_value++;
    if ( name == GUILD_WIZ ) return_value++;

    if ( return_value > 1 ) return_value = 1;

    if ( (player->query_wiz_level()) && !return_value )
        write("Note that " + capitalize(GUILD_WIZ) +
            " holds immortal Librarian privileges here.\n");

    return return_value;

}

string *query_player_access(object player)
{
    // Librarians access all
    if(query_librarian(player))
        return ({ "librarian", "restricted", "normal" });

    // Thane or Elder of Clan
    if (IS_THANE(player) || IS_ELDER(player) )
        return ({ "restricted", "normal" });

    // Non wizzes get access to the normal shelf only
    return ({ "normal" });
}


public mixed *
library_hook_get_approval_names()
{
    return ({ IMMORTAL_LIBRARIAN, MORTAL_LIBRARIAN });
} /* library_hook_get_approval_names */


int
ask_for_new_librarian(string proposed_librarian)
{
    int exception;
    string *wiznames, *ccnames;
    string requester, title, contents, subject, replaced;

    if ( !proposed_librarian || !find_player(proposed_librarian) )
    {
        write("Who you be recommendin' now?!\n");
        return 0;
    }

    requester = this_player()->query_real_name();
    replaced = MORTAL_LIBRARIAN;

    // Look for exceptions ----
    exception = 1;

    if ( requester == MORTAL_LIBRARIAN )
    {
        title = "Encumbent Librarian";
        ccnames = ({});
        replaced = "me";
        exception = 0;
    }
    if ( IS_THANE(this_player()) )
    {
        if ( !exception )
        {
            title = sprintf("%s and Thane",title);
        }
        else
        {
            ccnames = ({ MORTAL_LIBRARIAN });
            title = "Thane";
        }
        exception = 0;
    }

    if ( exception )
        write("Your recommendin' don't carry 'nough weight!\n");

    if ( !IS_MEMBER(proposed_librarian) )
    {
        write("Your proposed new librarian, " + proposed_librarian
               + ", is not recorded as a current member of the Neidar Clan.\n");
        exception = 1;
    }
    if ( proposed_librarian == MORTAL_LIBRARIAN )
    {
        write("Your proposed new librarian, " + proposed_librarian
               + ", is already the Librarian to the Neidar Clan.\n");
        exception = 1;
    }

    if ( exception ) return 1;
    // ---- done with exception checking

    subject = " Petition for a Change of Librarian";

    title = sprintf( "the %s of the Neidar Clan", title); 

    contents = sprintf(
      "\n ~~~~ I, %s, %s, 'umbly ask that %s be made Librarian in place of %s ~~~~\n\n", 
      capitalize(requester), title, capitalize(proposed_librarian),capitalize(replaced));

    if ( GUILD_WIZ != IMMORTAL_LIBRARIAN )
        wiznames = ({GUILD_WIZ, IMMORTAL_LIBRARIAN});
    else
        wiznames = ({GUILD_WIZ});

    // Ask Wizards for new librarian 
    CREATE_MAIL("VALIDATED" + subject, requester, implode(wiznames, ","),"", contents);

    // Copy without VALIDATION to Mortals
    CREATE_MAIL(subject, requester, implode(ccnames, ","),"", contents);

    // Notify proposed librarian of proposal
    if ( !(replaced == "me") )
        CREATE_MAIL(subject, requester, proposed_librarian,
                 "", contents);

    return 1;

} /* ask_for_new_librarian */


void library_hook_receive_book(object player, object book)
{
    // Write messages
    player->catch_msg("You find the " + library_book_type +
        " that you were looking " +
        "for and ease it out from its stalagmite "+
        "-- careful not to bring the whole place down.\n");
    tell_room(environment(player), QCTNAME(player) + " seems to " +
        "have found the " + library_book_type + " " +
        player->query_pronoun() + " was " +
        "looking for and eases it out of a tall stalagmite.\n", player);
}


void library_hook_list_books(string shelf_name, mixed *shelf_data, mixed *books)
{
    int i;

    // Check for empty shelves
    if(sizeof(books) == 0)
    {
        write("The stalagmite shelf '" + shelf_name + "' is empty of anything interesting.\n");
        return;
    }

    // Display the list
    write(shelf_data[0] + ":\n\n");
    write(sprintf("%-10s %s\n", "Number", "Title"));
    write(sprintf("%-10s %s\n", "----------", 
        "-----------------------------------------------------------------"));
    for(i=0;i<sizeof(books);i++)
    {
        write(sprintf("%-10s %s\n", 
            books[i],
            library_data["books"][books[i]][1]));
    }
}

void library_hook_list_shelves(string *shelves)
{           
    int i;

    write("You find the following stalagmite shelves:\n\n");
    write(sprintf("%-25s %-35s %s\n",
        "Shelf", "Description", "Access level"));
    write(sprintf("%-25s %-35s %s\n",
        "-------------------------", 
        "-----------------------------------", 
        "---------------"));

    for(i=0;i<sizeof(shelves);i++)
    {
        write(sprintf("%-25s %-35s %s\n",
            shelves[i],
            library_data["shelves"][shelves[i]][0],
            query_access_desc(library_data["shelves"][shelves[i]][1])));
    }
}


void library_hook_stop_leave(object player, object *books)
{
    player->catch_msg("Steady on there dwarf! You can't leave with load of " +
        COMPOSITE_DEAD(books) + ".  They belong here and your arms are gettin' "+
        "tired from the weight.\n");
}
 

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

    CREATE_MAIL("New book " + author, "NeidarLibrary",
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


public void
leave_inv(object ob, object to)
{
    object   oldtp;

    library_leave_inv(ob, to);
    ::leave_inv(ob, to);

} /* leave_inv */ 


public void
init()
{
    ::init();
    init_library();
    add_action("ask_for_new_librarian","recommend");

} /* init */

