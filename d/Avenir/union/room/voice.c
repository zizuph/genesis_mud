/*
 * File:     voice.c
 * Created:  Lucius - Augh 20177
 * Purpose:  Room where the Voice may keep records and
 *           have unofficial meetings.
 *
 * Revisions:
 *
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;
inherit (LIB + "library");


public int
query_prevent_snoop(void)	{ return 1; }

public void 
union_room(void)
{
    set_short("Chambre of Voices");
    set_long("This is a low cavern of crystalline stone that "+
      "sparkles with moisture from an unknown source. It "+
      "looks more like a massive geode than anything else, "+
      "being lined as it is with large, compact crystal "+
      "formations. It has been left almost entirely in its "+
      "natural state, except for one wall. Against the west "+
      "wall is inset a shadowed board that "+
      "glimmers with dancing sparks of white light. "+
      "Echoing through the cavern is the barely discernable "+
      "murmur of soft voices. "+
      "A narrow stone stairwell spirals downward into "+
      "brightness.\n");

    add_item(({"stairwell", "stairs", "spiral"}),
	"From this shadowy place the post office beckons brightly "+
	"from below.\n");
    add_item(({"geode"}),
	"This place resembles the hollow cavity of a massive "+
	"geode, one of those spherical rocks that, when cut "+
	"open, contain a delightful array of crystals.\n");
    add_item(({"crystal", "crystal formations", "crystals" }),
	"These are large, compact crystal formations such as "+
	"agate, jasper, and chalcedony. They glimmer gorgeously "+
	"in the shadowed light of the room.\n");       

    add_exit("post", "down");

    set_library_save_path(LIBSAVE + "voice/");
    set_library_save_file(LIBSAVE + "voice/data");
    set_library_log_file(LIBSAVE + "voice/log");

    set_library_book_object(LIB + "book");

    add_library_access_level("admin", "Voice");

    set_library_librarian_level("admin");
    set_library_new_book_shelf("pending");

    set_library_allow_new_books(1);
    set_library_allow_edit_direct(1);
    set_library_allow_read_direct(1);

    set_library_cmd_prefix("u");

    create_library();

    /* Add a sign that gives instructions on how to use the library */
    add_item(({"plaque","onyx plaque"}), library_help);
    add_cmd_item(({"plaque","onyx plaque"}), "read", library_help);
    add_item(({"shelves","bookshelves","book shelves"}), 
      "Against the wall are bookshelves constructed from "+
      "solid and dark kesoit wood native to Sybarus. You should "+
      "read the nearby plaque for instructions on how to use them.\n");
}

public void
init(void)
{
    ::init();

    /* Add the library commands */
    if (MEMBER_SPHERE(TP, SPH_VOICE))
	init_library();
}

public int
query_librarian(object who)
{
    /* Voice and above */
    return MEMBER_SPHERE(TP, SPH_VOICE);
}

public string *
query_player_access(object who)
{
    /* Mentors, Elders and GM's. */
    if (query_librarian(who))
	return ({ "admin" });

    return ({ });
}

public void
library_configure_book(object book, string book_id)
{
    ::library_configure_book(book, book_id);

    if (!strlen(book_id))
	return;

    string *adjs = ({ "viridian", "carnelian", "cerulean",
	"chartreuse", "fuchsia" });
    int index, sz = sizeof(adjs);
    string adj, nm = book->query_title();

    // parse out spaces: name_to_random will choke on them
    nm = implode(explode(nm, " "), "");
    index = NAME_TO_RANDOM(nm, 13254, sz);

    // I am not confident that NAME_TO_RANDOM is reliable (I have
    // seen it return random numbers!). So I will do my own sanity
    // checking.
    if ((index >= 0) && (index < sizeof(adjs)))
	adj = adjs[index];
    else
	adj = adjs[random(sz)];

    book->add_adj(adj);
    book->set_short(adj + " book");
    book->set_long("This book is from the Chambre of Voices library.\n"+
      "Written along the spine is \""+ book->query_title() +"\".\n");
}

public void
leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}
