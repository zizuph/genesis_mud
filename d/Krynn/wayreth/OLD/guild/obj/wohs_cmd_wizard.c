/*
 * The wizard command soul.
 *
 * It holds some special commands for administration purpose.
 */
inherit "/cmd/std/command_driver";

#include <macros.h>
#include <language.h>
#include <std.h>
#include "../local.h"
#include "../../local.h"

#define CHECK_WIZARD  if (!ADMIN->valid_wohs_wiz()) return 0;

static void update_books(string str);

/*
 * The name of the soul.
 */
public string 
get_soul_id() { return "Admin ommands of WoHS"; }

/*
 * It is a command soul.
 */
public int 
query_cmd_soul() 
{ 
    setuid();
    seteuid(getuid());

    return 1; 
}

/*
 * The list of verbs and functions. Please add new in alfabetical order.
 */
public mapping
query_cmdlist()
{
    return ([
	     "wupdate" : "wupdate",
	   ]);
}

private void
update_book(object player)
{
    object old_book, new_book;
    int *book_status;

    write(sprintf("%-20s", C(RNAME(player))));
    old_book = present(SPELL_BOOK, player);
    if (old_book)
    {
        if (player->query_prop(LIVE_O_CONCENTRATE) == old_book)
	{
	    write("Book is being used, trying later.\n");
	    set_alarm(10.0, 0.0, &update_books(RNAME(player)));
	}
	else
	{
	    book_status = old_book->query_book_status();
	    new_book = clone_object(WMAGIC + "spellbook");

	    if (!new_book)
	        write("Can't clone book, not updated.\n");
	    else
	    {
	        new_book->set_book_status(book_status);
		new_book->move(E(old_book));
		old_book->remove_object();
		new_book->setup_spells(player->query_wohs_level());
		write("Book updated.\n");
	    }
	}
    }
    else
        write("Don't have a book.\n");
}

static void
update_books(string str)
{
    object *mages;
    int size;

    setuid();
    seteuid(getuid());

    if (!strlen(str) || str == "all")
    {
        mages = filter(users(), &operator(==)(GUILD_NAME) @
		       &->query_guild_name_occ());

    	size = sizeof(mages);
	while(size--)
	{
	    update_book(mages[size]);
	}
    }

    return;
}

public int
wupdate(string str)
{
    string *strs, how = "";

    CHECK_WIZARD

    NF("Do 'whelp wohs wupdate' for help!\n");
    
    if (!str || !strlen(str))
         return 0;

    strs = explode(str, " ");

    if (sizeof(strs) > 1)
        how = L(strs[1]);

    switch (L(strs[0]))
    {
        case "book":
	    update_books(how);
            return 1;
	    break;
        default:
            return 0;
	    break;
    }        
}




