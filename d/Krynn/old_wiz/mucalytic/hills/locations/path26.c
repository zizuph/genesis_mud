/* A path in the foothills (26). ~mucalytic/hills/locations/path26 */

#include "../defs.h"
#include "/sys/macros.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path24", "west", "@@ch_dir1@@", 3);
    add_exit(LOCATIONS + "path18", "north", "@@ch_dir2@@", 3);

    room_add_object(NPCS + "roselda");
}

void create_room()
{
    string desc;

    ::create_room();

    desc = extract(query_long(), 0, (strlen(desc) - 2));

    desc += " A tall rectangular monolith of jet-black stone looms ominously "+
        "up from the grass not far from here.\n";

    set_long(desc);

    add_item(({"monolith", "tall monolith", "rectangular monlith", "tall "+
        "rectangular monolith"}), "The monlith looks to be about ten "+
        "metres tall and three wide. It is made of a jet black stone that "+
        "does not reflect light nor look as if it is affected by the "+
        "weather in these parts. It has writing carved into it in a "+
        "strange script that exudes strangeness.\n");
}

void init()
{
    ::init();

    add_action("do_read", "read");
}

void ch_dir1()
{
    write("The path runs through a small cave in the side of a hill and you "+
        "end up facing north.\n\n");
}

void ch_dir2()
{
    write("The path runs round the base of a hill, leading you eastwards.\n\n");
}

int do_read(string str)
{
    if(!strlen(str))
        return 0;

    if(str == "writing on monolith")
    {
        if(!TP->query_wiz_level())
        {
            write("You cannot make head nor tail of the writing on the "+
                "monolith.\n");
        }
        else
        {
            seteuid(getuid(TO));
            cat(MISC + "monolith_writing.txt");
        }

        if(!TP->query_invis())
            say(QCTNAME(TP)+" reads the writing on the monolith.\n");
        return 1;
    }
    else
        write("Read what? IE: 'read writing on monolith'.\n");        
    return 1;
}
