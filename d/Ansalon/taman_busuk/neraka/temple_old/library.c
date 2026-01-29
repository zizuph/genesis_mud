/* Ashlar, 1 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include "../guild/guild.h"

#include <macros.h>
#include <std.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>

#define STDLIB          "/d/Krynn/std/library/library"

inherit TEMPLE_BASE;
inherit STDLIB;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "You are in the library belonging to the Priests of Takhisis. " +
    "Doorways lead northwest and east out of here. There is a large " +
    "plaque set on the wall, and a sign above it.\n";
}

void
create_neraka_room()
{
    set_short("in the library");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doorway","small doorway"}),
    "The doorway is decorated with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}),
    "The frame is made of wood, but you cannot discern the type of " +
    "wood. The white paint contrasts nicely with the darker walls.\n");

    add_item(({"plaque","large plaque"}),"@@read_plaque");
    add_cmd_item(({"plaque","large plaque"}),"read","@@read_plaque");
    add_item("sign","@@read_sign");
    add_cmd_item("sign","read","@@read_sign");

    reset_room();

    add_exit(NTEMPLE + "board", "northwest", "@@go_northwest");
    add_exit(NTEMPLE + "d10", "east");

    set_lib_id("temple_of_takhisis_lib_id");
    set_lib_path(NTEMPLE + "lib/");
    set_book_file(NTEMPLE + "lib/book");
    set_lib_type(4);
    set_lib_long("the Dark Library in the Temple of Takhisis");
    set_search_delay(6.2);
    set_default_topics((["New Arrivals":1,
        "Public section":0,
        "Private section":2,
        "Trash":1]));
    setup_library();
}

void
init()
{
    init_library();
    ::init();
}

void
leave_inv(object player, object dest)
{
    ::leave_inv(player, dest);
    library_leave_inv(player, dest);
}

string
read_plaque()
{
    write("The Dark Library of the Temple of Takhisis\n" +
          "==========================================\n\n" +
      "Check the 'index' for a list of topics, and the 'catalog' of each " +
      "topic for a list of available books. You can then 'borrow' any of " +
      "the available books. Note that you must give the complete title of " +
      "a book (up to any '-') you want to borrow. Please do not forget to " +
      "return borrowed books!\n\n" +
      "To write a new book you should give the command 'blank'. " +
      "Then you will get a blank book, which is yours to " +
      "fill with whatever you want, maps, songs, or a novel perhaps? " +
      "The command to start writing is 'bedit'. You write a " +
      "book much the same way you write a note on the board.\n");
    return "";
}

string
read_sign()
{
    write("LIBRARY - QUIET PLEASE!\n\n" +
      "Current Librarian: " + (librarian && sizeof(librarian) ? C(librarian[0]) : "-") + "\n" +
      "The guild leader is responsible for 'appoint'ing or 'unappoint'ing " +
      "the librarian.\n");
    if (librarian && sizeof(librarian) && TP->query_real_name() == librarian[0])
      write("As librarian, you have these commands available:\n" +
            " Beautify <bookname>\n" +
            "       Allows you to change the title, or align the title neatly.\n" +
            " Movebook <bookname> to topic <newtopic>\n" +
            "       To remove a book completely, use 'Movebook <bookname> to topic trash'.\n" +
            " Create <new topic> <access level>\n" +
            "       Access level is: 0: everyone\n" +
            "                        1: librarian only\n" +
            "                        2: priests only\n" +
            " Uncreate <old topic>\n" +
            " Retire\n");
    return "";
}

mixed
hook_can_access_catalog(int level)
{
    /* 0: everyone can read
    * 1: librarian only can read
    * above levels are handled directly,
    * we only need to take care of the ones below
    *
    * we add these access classes:
    * 2: priests only can read 
    */
    if (level == 2)
        return ({ !!(MEMBER(TP)),"Priests of Takhisis only" });

    return ({ 0,"No access" });
}

int
hook_appoint_unappoint()
{
    if (GUILD_LEADER(TP) || TP->query_real_name()=="milan")
        return 1;

    return 0;
}

void
hook_appointed_info()
{
    write("Note: The appointed librarian must be a High Priest, " +
    "or the position will become vacated again after an " +
    "unsuccessful attempt.\n");
}

int
hook_librarian_requirements()
{
    /* Temporarily added (no high priests) */
    return (TP->query_priest_level() >= GUILD_LEVEL_PRIEST);
    
    return (TP->query_priest_level() >= GUILD_LEVEL_HIGH_PRIEST);
}

int
go_northwest()
{
    if (TP->query_wiz_level() || (TP->query_guild_member(GUILD_NAME)))
    {
        write("You feel a chill passing through you as you go northwest, and " +
        "you realise that part of the library was warded.\n");
        return 0;
    }
    else
    {
    	write("You attempt to go northwest, but you find that you cannot " +
    	"move in that direction. That part of the library must be " +
    	"warded.\n");
    	return 1;
    }
}

void
dispel_magic(int strength)
{
    tell_room(TO,"To the northwest, the corridor lights up from wall to wall " +
    "with a shimmering light as the powerful warding absorbs the dispel " +
    "attempt. The light dies down after a short while.\n");
}
