/* 
 *    The library in Minas Morgul 
 *    copied from the Edoras library by Elessar  
 *    Olorin, Oct-1993 
 *
 *    Updated to use /d/Gondor/common/lib/library.c
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/library.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#define BOOK_LIST	(LIBRARY_DIR + "books/mmbooks")

private int     check_mage();

public void
create_library()
{
    set_library_name("the Library of Minas Morgul");
    set_extra_line("A doorway leads out to the place to the west. "
      + "In a corner, a narrow stairway is leading down. ");
    set_librarian("ancient scribe");
    set_default_books(({"Silmarils","WhiteTree",}));
    set_book_list(BOOK_LIST);

    add_exit(MORGUL_DIR + "city/square",    "west", 0, 0);
    add_exit(MORGUL_ROOM_DIR + "mage_library", "down", check_mage, 2);

    add_item(({"stairs", "stairway"}), BSN(
        "In a corner, a narrow stairway is leading down into the cellars "
      + "under the library. Looking at the dark hole into which the stairs "
      + "disappear you can sense the powerful magic protecting the way "
      + "down."));
  
    add_item(({"ancient scribe", "scribe"}), BSN(
        "He is an ancient man of dark complexion. He was probably born "
      + "in Harad, now he is in charge of the library here. His biggest "
      + "concern is probably to protect the valuable books from the orcs "
      + "in this town."));

    add_item("desk",BSN("The desk is covered with pile upon pile of books."));

    add_item("legends",
        "This shelf is parted into several divisions, and a plaque reads:\n"
      + "'Legends of:\n"
      + "Lands, Cities, Gods, Heroes, Kings, Artifacts, Enemies, Peoples.\n");

    add_item("lore",
        BSN("The shelf labelled 'Lore' seems to contain books about "
      + "several subjects of the Nature and life in the wilderness."));

    add_item("history",
        BSN("This shelf is filled with several old books, most of them "
      + "covered with dust. These are some of the titles you find:")
      + BSN("Akallabeth, MiddleEarth, WhiteTree.\n"));

    add_item("geography", BSN(
        "This shelf contains lots of loose papers, probably maps, but "
      + "also books about places of note in the world."));

    add_item(({"misc","miscellaneous"}),BSN(
        "In this shelf there's not much system. You see books and scrolls, "
      + "loose sheets of paper and great tomes of old."));

    add_item("lands", BSN(
        "In the shelf labelled 'Legends of the Lands' you see books about "
      + "different countries in the world.")
      + BSN("These titles are available: Ithilien."));

    add_item("cities", BSN(
        "This shelf labelled 'Legends of Cities' seems to contain books "
      + "about different cities."));

    add_item("gods", BSN(
        "The shelf labelled 'Legends of the Gods' contains books about "
      + "the Valar who created Arda, the Earth."));

    add_item("heroes", BSN(
        "In the shelf labelled 'Legends of Heroes' you find books about "
      + "famous people in the history of Middle-Earth."));

    add_item("kings", BSN(
        "The shelf labelled 'Legends of Kings' contains books about the "
      + "Kings of Gondor and other famous kings. The only titles you can "
      + "make out are:")
      + BSN("Kings_of_Gondor, Stewards_of_Gondor, Kings_of_Arnor, "
      + "Kings_of_Rohan."));

    add_item("enemies", BSN(
        "This shelf labelled 'Legends of the Enemies' contains books "
      + "about the Enemies of the Dark Lord."));

    add_item("artifacts", BSN(
        "In the shelf labelled 'Legends of Artifacts' you see several "
      + "old books about ancient items and artifacts.")
      + "You see these titles: Silmarils.\n");

    add_item("peoples", BSN(
        "This shelf, labelled 'Legend of the Peoples' contains books about "
      + "the different Peoples that live and have lived in the world."));
}

private int
check_mage()
{

    if (IS_MORGUL_MAGE(TP))
        return 0;
    if (TP->query_wiz_level())
    {
        write("This exit is closed for all mortals but Morgul mages!\n");
        return 0;
    }
    write("You dare not go down on the stairs. The way down seems to be "
        + "protected by powerful magic.\n");
    return 1;
} 

