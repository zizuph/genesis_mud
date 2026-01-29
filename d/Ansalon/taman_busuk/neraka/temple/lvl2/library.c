/* This room is supposed to be the library of the PoT.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include <composite.h>
#include <macros.h>

inherit TEMPLE + "std_temple.c";
inherit "/d/Krynn/std/library/library";

string
librarian_extra()
{
    string *tmp = map(librarian + ({ }), capitalize);

    if (member_array(TP->query_real_name(), librarian) < 0)
        return " They have " + COMPOSITE_WORDS(tmp) + " as being " +
            "responsible for the ordering.";
    else
        return " As a librarian you feel you have the ability to " +
            "to beautify books, move them between indices through " +
            "movebook, create new topics as well as uncreate them " +
            "and edit books in the shelves.";
}

void
create_temple_room()
{
    ::create_temple_room();

    set_short("The library");
    set_long("This is a large room which is divided into various sections " +
        "by heavy wooden bookshelves. There are a couple of leather " +
        "armchairs standing in a more secluded place and a small writing " +
        "desk is placed in a small private section. An archway to the " +
        "northwest opens up into a corridor and to the southeast and " +
        "southwest lie two smaller chambers.\n");

    add_item(({"bookshelves", "shelves"}), "The shelves are indexed " +
        "with various list of topics from which a catalog could " +
        "be gained.@@librarian_extra@@\n");
    add_item(({"desk", "writing desk"}), "It has several \"blank\" books " +
        "stacked, once gotten would be ready to be \"bedited\".\n");
    add_item("archway", "The archway is decorated with smooth black " +
        "stone with small carvings.\n");
    add_item(({"carvings", "pattern", "stars", "black stars"}),
        "The carvings on the archway make up a pattern of black stars.\n");
    add_item(({"armchair", "armchairs", "leather armchairs"}),
        "A couple of armchairs that stand in a secluded and undisturbed " +
        "area of this library provide a comfortable reading place.\n");

    set_lib_id("temple_of_takhisis_lib_id");
    set_lib_path("/d/Ansalon/guild/new_pot/doc/library");
    set_book_file("/d/Ansalon/guild/new_pot/doc/library/book");
    set_lib_type(4);
    set_lib_long("the Dark Library in the Temple of Takhisis");
    set_search_delay(6.2);
    set_default_topics((["New Arrivals" : 1,
        "Public Section" : 0,
        "Cleric Section" : 2,
        "Priest Section" : 3,
        "High Priest Section" : 4,
        "Council Section" : 5,
        "Trash" : 1 ]));
    /* To have a limit in itself is quite redicilous */
    set_max_librarian_num(10);
    /* All these values will be overriden by the ones set in the .o file */
    setup_library();

    add_exit( LVLTWO + "corr5.c", "northwest" );
    add_exit( LVLTWO + "board2.c", "southeast" );
    add_exit( LVLTWO + "board1.c", "southwest" );
}

mixed
hook_can_access_catalog(int level)
{
    switch (level)
    {
        case 2: /* Council section */
            return ({ (TP->query_guild_name_occ() == GUILD_NAME &&
                TP->query_priest_level() >= GUILD_LEVEL_INITIATE) ||
                member_array(TP->query_real_name(), GUILDMASTERS) >= 0,
                "Clerics of Takhisis only" });
        case 3: /* Priest section */
            return ({ (TP->query_guild_name_occ() == GUILD_NAME &&
                TP->query_priest_level() >= GUILD_LEVEL_PRIEST) ||
                member_array(TP->query_real_name(), GUILDMASTERS) >= 0,
                "Priests of Takhisis only" });
        case 4:
            return ({ (TP->query_guild_name_occ() == GUILD_NAME &&
                TP->query_priest_level() >= GUILD_LEVEL_HIGH_PRIEST) ||
                member_array(TP->query_real_name(), GUILDMASTERS) >= 0,
                "High Priests of Takhisis only" });
        case 5: /* Council section */
            return ({ member_array(TP->query_real_name(),
                GUILD_ADMIN->query_guild_council()) >= 0 ||
                member_array(TP->query_real_name(), GUILDMASTERS) >= 0,
                "Councilmembers only" });
        default: /* Other levels are handled by the std library */
            return ({ 0, "No access" });
    }
}

int
hook_appoint_unappoint()
{
    return !(!(member_array(TP->query_real_name(),
        GUILD_ADMIN->query_guild_council() + GUILDMASTERS) >= 0));
}

int
council_assign(string str)
{
    if (member_array(str, librarian) >= 0)
        return 0;

    librarian += ({ str });
    save_object(MASTER);

    return 1;
}

int
council_unassign(string str)
{
    if (member_array(str, librarian) < 0)
        return 0;

    librarian -= ({ str });
    save_object(MASTER);

    return 1;
}

void
add_council_book_if_not_present()
{
    string filename = bookname("Reports from the Council");

    if (pointerp(books[filename]))
        return;

    setuid();
    seteuid(getuid());

    books += ([ filename : ({ "Reports from the Council", "Council section",
        "Council" }) ]);
    
    write_file("/d/Ansalon/guild/new_pot/doc/library/short/" + filename,
        "iridescent black folder");
    write_file("/d/Ansalon/guild/new_pot/doc/library/long/" + filename,
        "A folder in iridescent black that has a couple of sheets of " +
        "parchment inside it.");
//    write_file(query_lib_path() + "book/" + filename, "contents");
    
    save_object(MASTER);
}

void
init()
{
    ::init();

    init_library();
}

void
leave_inv(object player, object dest)
{
    ::leave_inv(player, dest);
    
    library_leave_inv(player, dest);
}
