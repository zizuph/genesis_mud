/*
 * Gondorian Library in Minas Tirith.
 * This room will contain lots of information for the adventurers.
 * Books of many kinds will be in this room, to read from, not take.
 * Made by Elessar, April 1992.
 *
 * Updated to use /d/Gondor/common/lib/library.c
 * Olorin, 9-nov-1994
 */
inherit "/d/Gondor/common/lib/library";

#include "/d/Gondor/defs.h"

#define BOOK_LIST	(LIBRARY_DIR + "books/mtbooks")

void
create_library()
{
    set_library_name("the Great Library of Gondor in Minas Tirith");
    set_extra_line("A doorway leads out to the entryhall north. ");
    set_librarian("Royal Scribe");
    set_book_list(BOOK_LIST);

    add_exit(MINAS_DIR + "citadel/entryhall","north", 0, 0);

    add_item(({"royal scribe", "scribe", }), BSN(
        "The Royal Scribe is a man of obviously dunadan descent. His "
      + "tasks is to keep track of the books and texts in the "
      + "Great Library of Gondor. He will probably let you leave "
      + "with books only over his dead body."));

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
      + BSN("FirstAge, FirstAgeEnd, SecondAge, Akallabeth, WhiteTree."));

    add_item("geography", BSN(
        "This shelf contains lots of loose papers, probably maps, but "
      + "also books about places of note in the world."));

    add_item(({"misc","miscellaneous"}),BSN(
        "In this shelf there's not much system. You see books and scrolls, "
      + "loose sheets of paper and great tomes of old."));

    add_item("lands", BSN(
        "In the shelf labelled 'Legends of the Lands' you see books about "
      + "special places in the world, probably where something has "
      + "happened."));

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
      + "about the Enemies of the Free Peoples."));

    add_item("artifacts", BSN(
        "In the shelf labelled 'Legends of Artifacts' you see several "
      + "old books about ancient items and artifacts."));

    add_item("peoples", BSN(
        "This shelf, labelled 'Legend of the Peoples' contains books "
      + "about the different Peoples that live and have lived in the world. "
      + "You see these titles: Edain, Dunedain, Rohirrim."));
}

