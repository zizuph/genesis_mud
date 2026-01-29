/* /d/Gondor/guilds/rangers/obj/transfer_book.c
 * Book located in transfer room that tells
 * rangers about companies, skills, and choices
 * 
 * Tigerlily, Nov. 26, 2003
 */

inherit "/std/book";

#include <stdproperties.h>
#include "/d/Gondor/guilds/rangers/rangers.h"

#define TRANSFER_TXT (RANGERS_TEXT + "transfer_txt/")

void
create_book()
{
    set_name("_transfer_book");
    add_name("book");
    add_name("tome");
    set_adj(({"dark-green", "green", "leather-bound"}));
    set_short("red leather-bound tome");
    set_long("The tome is a rather large, dark-green " +
        "leather-bound book that is chained to the wall " +
        "and shows signs of much use. An image of a white " +
        "tree is stamped on the cover. The pages are made " +
        "of fine gilt-edged white parchment.\n");
    add_prop(OBJ_M_NO_GET, "The book is chained to the wall.\n");
    add_item(({"tree", "white tree"}), "The image on the cover " +
        "of the book depicts Nimloth, the white tree of Numenor.\n");
    add_item(({"page", "pages"}), "You may turn the pages of the " +
        "book and read what interests you.\n");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 800);
    set_max_pages(6);
    
}

varargs void
read_book_at_page(int which, string verb)
{
    object player = this_player();
    string txt;

    setuid(); 
    seteuid(getuid());
    switch (which)
    {
    case 1:
        txt = "Rangers of the Westlands.";
        txt += "\n\n\n";
        txt += "     Page 1: ...............  Index.\n\n";
        txt += "     Page 2: ...............  General Information.\n\n";
        txt += "     Page 3: ...............  Apprentices.\n\n";
        txt += "     Page 4: ...............  Ithilien.\n\n";
        txt += "     Page 5: ...............  North.\n\n";
        txt += "     Page 6: ...............  Leaving the Guild.\n\n";

        break;
    case 2:
        txt = read_file(TRANSFER_TXT + "intro.txt");
        break;
    case 3:
        txt = read_file(TRANSFER_TXT + "apprentice.txt");
        break;
    case 4:
        txt = read_file(TRANSFER_TXT + "ithilien.txt");
        break;
    case 5:
        txt = read_file(TRANSFER_TXT + "north.txt");
        break;
    case 6:
        txt = read_file(TRANSFER_TXT + "leaving.txt");
        break;
    default:
        txt = "This page is blank.\n";
        break;
    }

    player->catch_tell(txt);
    return;

}
