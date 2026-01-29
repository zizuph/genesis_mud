/*
 * File:     novlib0.c
 * Created:  Lilith
 * Purpose:  Library for the Novice members
 *
 * Revisions:
 *   Lucius, Jun 2016: Modified to use a new library base.
 *
 */
#pragma strict_types
#include "../defs.h"

#include <math.h>
#include <composite.h>

inherit BASE;
inherit (LIB + "library");

/* global vars */
private string *phrases = ({ 
  "If you aim at nothing, you are sure to hit it.",
  "Sometimes in our evolution we stagnate. "+
  "If such is the case for you, " +
  "let the reflections of these walls help show you the "+
  "layers of ego and identity which are blocking your growth. ",
});

private int words = random(sizeof(phrases));


public string 
words(void)
{
    if (!IS_MEMBER(TP))
    {
	return "As you do not recognize the script, the words "+
	"are all indecipherable.\n";
    }

    if (++words >= sizeof(phrases))
	words = 0;

    return "One of the phrases upon the scrolls reads:\n"+
	break_string(phrases[words], 55, 5)+"\n";
}

public void
union_room(void)
{
    set_short("novice library, level five");
    set_long("This is the fifth level of the Library of Novices of "+
      "the Shadow Union. Nearly identical to the rooms below, the "+
      "walls and high ceiling of this room are made of stone of "+
      "the deepest black, and draw most of the light from the room. "+
      "There are reading tables placed here and there, and "+
      "comfortable chairs to rock in and contemplate the mysteries. "+
      "A small staircase leads downward into the darkness. "+
      "A narrow set of shelves leans against the north wall.\n");

    /* Add a sign that gives instructions on how to use the library */
    add_item("sign", library_help);
    add_cmd_item("sign","read", library_help);
    add_item(({"bookshelves","bookshelf","stone bookshelves", "shelves",
	"north wall", "shelf"}),
      "They appear to be carved into the stone.\nAbove the shelves is "+
      "posted a sign that reads:\n\nYou do not have to borrow the books "+
      "inorder to read them.\n@@library_help@@\n");
    add_item(({"light",}),
      "Light filters down the stairs from an unknown source " +
      "high in the tower. Mists coalesce and float down " +
      "the stairwell, where they seem to dance in an intricate "+
      "pattern at your feet.\n");
    add_cmd_item(({"word","words","wall","inscription","inscriptions",
	"scroll", "scrolls"}), "read", words);
    add_item(({"word","words","wall","inscription","inscriptions",
	"scroll", "scrolls" }),  words);
    add_item(({"wall","walls",}), 
      "The walls are incredibly smooth and reflect the light "+
      "drifting down the stairwell. Upon closer inspection, you "+
      "realize that they are made of black obsidian glass that has " +
      "been formed by the fires of Jazur. They are cool to the touch "+
      "and very slick.\nAll along the walls hang scrolls inscribed "+
      "with words written in an elegant script.\n");
    add_item(({"tables"}), "They are simple tables designed to be "+
      "easily reached from a seated position.\n");

    add_object(OBJ + "library_table", 1);
    add_object(OBJ + "rocker", 3 + random(3));

    add_exit("novlib4", "down");

    set_library_save_path(LIBSAVE + "novice/");
    set_library_save_file(LIBSAVE + "novice/novlib5_data");
    set_library_log_file(LIBSAVE + "novice/novlib5_log");

    set_library_book_object(LIB + "book");

    add_library_access_level( "novice", "Novice"   );
    add_library_access_level(  "admin", "Mentors"  );

    set_library_librarian_level("admin");
    set_library_new_book_shelf("pending");

    set_library_allow_new_books(1);
    set_library_allow_edit_direct(1);
    set_library_allow_read_direct(1);

    set_library_cmd_prefix("u"); 

    create_library();
}

public void
init(void)
{
    ::init();
    init_library();
}

public int
query_librarian(object who)
{
    /* Mentors, Elders and GM's. */
    if (MEMBER_SPHERE(who, SPH_MENTOR))
	return 1;

    return 0;
}

public int
query_access_display(void)		{ return 0; }

public int
query_display_new_book_shelf(void)	{ return 2; }

public string *
query_player_access(object who)
{
    /* Mentors, Elders and GM's. */
    if (query_librarian(who))
	return ({ "novice", "admin" });

    /* If the player is punished with "noarchives", prevent
     * him from making use of this library.  */
    if (U_IS_PUNISHED(who, U_PUNISHED_LIBRARY))
	return ({ });

    /* Warriors. */
    if (IS_MEMBER(who))
	return ({ "novice" });

    return ({ });
}

public void
library_configure_book(object book, string book_id)
{
    ::library_configure_book(book, book_id);

    if (!strlen(book_id))
	return;

    string *adjs = ({ "small", "dark", "cloth-bound",
      "gold-embossed", "slender", "fragile" });
    string adj, nm = book->query_title();
    int index, sz = sizeof(adjs);

    // parse out spaces: name_to_random will choke on them
    nm = implode(explode(nm, " "), "");
    index = NAME_TO_RANDOM(nm, 13254, sz);

    // I am not confident that NAME_TO_RANDOM is reliable (I have
    // seen it return random numbers!). So I will do my own sanity
    // checking.
    if ((index >= 0) && (index < sz))
	adj = adjs[index];
    else
	adj = adjs[random(sz)];

    book->add_adj(adj);
    book->set_short(adj + " book");
    book->set_long("This "+ short() + " is from the Novitiate library.\n"+
      "Along the spine is writ the following: "+ book->query_title() +
      ". Scripted across the cover are the words '"+
      book->query_summary() +"'. At the bottom, embossed in elegant type: "+
      "Penned by "+ COMPOSITE_WORDS(map(book->query_authors(),
	  capitalize)) +".\n");
}

public void
leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}
