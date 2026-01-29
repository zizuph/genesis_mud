/*
 *    /d/Gondor/common/guild/gondor/lib_office.c
 *
 *    Modification log:
 *    26-aug-1997, Olorin: Made this room a post office.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/post2";
inherit "/d/Gondor/common/lib/library_office";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public string exa_plaque();

string
read_aliases()
{
    return "Here you may read and write your mail as in any post office.\n"+
	"Check the mailreader for instructions.\n" +
        "The following aliases can be used here:\n" +
        "\tguildmaster - the guildmaster of the Rangers guild,\n" +
        "\tcouncil     - the Council of Rangers,\n" +
        "\tgondorian   - the Officers of Gondor Company,\n" +
        "\tnorth       - the Officers of North Company,\n" +
        "\tithilien    - the Officers of Ithilien Company,\n";
}

public void
create_room()
{
    set_short("in the office of the library of the Rangers");
    set_long(BSN("This dusty little chamber off the Library of the Rangers, "
      + "is where the librarians approve or deny new books that have been "
      + "submitted to the library. A bronze plaque on one wall has some "
      + "helpful words enscribed in it. Below it is a small sign with "
      + "more information. A narrow doorway leads back north "
      + "into the main hall of the library."));
    add_exit(RANGER_DIR + "gondor/ranger_library", "north", 0);
    add_exit(RANGER_DIR + "library/rog_library", "south");

    add_prop(ROOM_I_INSIDE, 1);

    set_save_path(RANGER_DIR + "gondor/books/waiting");
    set_library(RANGER_DIR + "gondor/ranger_library");
    set_log_file("guild");
    set_up_office();

    add_item(({"plaque", "bronze plaque", }), exa_plaque());
    add_cmd_item(({"plaque", "bronze plaque", }), "read", exa_plaque());
    add_item( ({ "sign", "aliases", }), read_aliases);
    add_cmd_item( ({ "sign", "aliases", }), "read", 
		read_aliases);
}

public void 
init()
{
    ::init();

    init_office();
    post_init();
}

/*
 * Function name: add_book_to_library
 * Description:   add a book to the library
 * Arguments:     s - name of the book
 * Returns:       1 if success, 0 else
 * Modified for a library using shelves: add <book> to shelf <shelf>
 */
int
add_book_to_library(string s)
{
    string  book,
            shelf;

    s = capitalize(lower_case(s));
    if (sscanf(s, "%s to shelf %s", book, shelf) < 2)
    {
        NFN("Add which book to which shelf? Try: add <book> to shelf <shelf>.");
        return 0;
    }

    if (member_array(CAP(shelf), lib->query_shelf()) < 0)
    {
        NFN("There is no shelf with the name \""+CAP(shelf)+"\" in the library!");
        return 0;
    }

    if (!sizeof(books[book]))
        return lib_hook_office_not_exist();
  
    lib->add_book(book,books[book][0],books[book][1],books[book][2]);
    lib->add_shelf_book(shelf, book);
    write("You add the book to " + lib->query_library_name() + ".\n");
    seteuid(getuid(this_object()));

    log_file(log_file, "LIBRARY: " + this_player()->query_name()
      + " added the book " + book + " (" + books[book][0]
      + ") to the shelf "+CAP(shelf)+" on "+ctime(time())+".\n");

    books = m_delete(books,book);
    save_object(lsave);
    check_desc();
    return 1;
}

string
exa_plaque()
{
    return
        "\n\t"+CAP(lib->query_library_name())+"\n"
      + "\n\tThe following commands are available:\n\n"
      + "\tlist           - list the submitted titles,\n"
      + "\tread <title>   - read a book without borrowing it,\n"
      + "\treject <title> - reject a submission,\n"
      + "\tadd <title> to shelf <shelf> -\n"
      + "\t                 add a book to a shelf of the library.\n"
      + "\n\tTo remove old titles, go to the library.\n\n";
}

public void
leave_inv(object ob, object to)
{
    post_leave_inv(ob, to);

    ::leave_inv(ob, to);
}

void
add_aliases(object rdr)
{
    string *wizards = ({});
    string *council = ({});

    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
      rdr->set_alias("guildmaster", wizards);

    council = R_COUNCIL->query_officers();
    council -= ({ 0 });
    rdr->set_alias("council", council);

    council = ({ R_COUNCIL->query_gondor(), 
	         R_COUNCIL->query_gondor_deputy(),
		 R_COUNCIL->query_gondor_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("gondorian", council);

    council = ({ R_COUNCIL->query_north(), 
		 R_COUNCIL->query_north_deputy(),
                 R_COUNCIL->query_north_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("north", council);

    council = ({ R_COUNCIL->query_ithilien(), 
		 R_COUNCIL->query_ithilien_deputy(),
		 R_COUNCIL->query_ithilien_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("ithilien", council);
}
 
/*
 * Function name: silent_room
 * Description  : Mask post parent to allow all commands.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - player blocked/player not blocked.
 */
public int
silent_room(string str)
{
    return 0;
}
