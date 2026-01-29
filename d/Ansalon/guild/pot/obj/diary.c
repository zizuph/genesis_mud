/* Stralle @ Genesis 020722
 *
 */

#pragma strict_types

inherit "/std/book";

#include <stdproperties.h>
#include "../guild.h"

string *gArr;

void
create_book()
{
    set_name("journal");
    set_adj("grey");
    set_long("A grey journal with a tag in the middle of its front, " +
        "with the name \"Lanthala\" written in fiery letters.\n");
    
    setuid();
    seteuid(getuid());

    gArr = explode(read_file(GUILDDIR + "doc/books/lanthala"), "#\n");

    set_max_pages(sizeof(gArr));
}

string
scrollify_contents(string str)
{
    string scroll, *words, *lines;
    int x, size, crs;
    
    if (!str)
        return str;
    
    words = explode(implode(explode(str, "\n"), " "), " ");
    for (x = 0, crs = 1, lines = ({ }), size = sizeof(words) ; x < size ; x++)
    {
        lines += ({ words[x] });
        if (strlen(implode(lines, " ")) > (30 * crs))
        {
            lines[x - 1] = lines[x - 1] + "\n";
            crs++;
        }
    }
    
    lines = explode(implode(lines, " "), "\n");
    scroll = "" +
      "    ________________________________________\n" +
      "   /\\                                       \\\n" +
      "  ( / )                                      )\n" +
      "   \\\\/______________________________________/\n" +
      "   |                                       |\n" +
      "   |                                       |\n" +
      "";
    
    for (x = 0 ; x < sizeof(lines) ; x++)
       scroll += sprintf("   |  %-35s  |\n", lines[x]);

    scroll += "" +
      "   |                                       |\n" +
      "   | ______________________________________|\n" +
      "   //\\                                     \\\n" +
      "  ( \\ )                                     )\n"+
      "   \\_/_____________________________________/ \n";
                                            

    return scroll;
}

void
read_book_at_page(int which, string verb)
{
    if (strlen(gArr[which - 1]))
    {
        if (this_player()->query_wiz_level())
            write(scrollify_contents(gArr[which - 1]));
        else
            write(gArr[which - 1]);
    }
    else 
        write("That page has been ripped out of the journal.\n");
}
