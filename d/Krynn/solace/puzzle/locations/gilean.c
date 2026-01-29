/* The tuttivillus room. ~solace/puzzle/locations/tuttivillus */

#include "../defs.h"
#include "/sys/macros.h"
#include "/secure/std.h"
#include "/sys/language.h"
#include "../../../mucalytic/sys/language.h"

inherit ROOM_DEFS;

void reset_puzzle_room()
{
    found = 0;

    if(member_array("north", query_exit_cmds()) != -1)
        remove_exit("north");

    room_add_object(OBJECTS + "congrat_scroll");
}

int query_north_exit()
{
    if(member_array("north", query_exit_cmds()) == -1)
        return 0;
    else
        return 1;
}

void create_puzzle_room()
{
    set_short("The Tuttivillus room");
    set_long("You find yourself in a small room, hexagonal in shape. The "+
        "walls, floor and ceiling are composed of obsidian. An eerie green "+
        "luminosity comes from an undetermined source; it seems just to be "+
        "here, as if it were meant to be. In the north wall you notice "+
        "@@doorway_desc@@. On the south wall, you see a large painting.\n");

    add_exit(LOCATIONS + "sargonnas", "north", 0, 1);

    add_item("doorway", "@@doorway_check_desc");

    add_item("doorway", "@@doorway_check_desc");

    add_item(({"metal", "shiny metal", "curved metal", "shiny curved metal"}),
        "@@metal_desc");

    add_item(({"floor", "ceiling"}), "It is plain and black. So black in "+
        "fact, that you would think that there was nothing there.\n");

    add_item(({"stone", "obsidian"}), "A jet-black stone that is very hard "+
        "and durable. It is very smooth and many blocks of it go to make "+
        "the walls, floor and ceiling.\n");

    add_item(({"luminosity", "green luminosity", "eerie luminosity", "eerie "+
        "green luminosity"}), "You look around for it's source, in order to "+
        "get a better look, but cannot seem to find anywhere. It's rather "+
        "peculiar.\n");

    add_item(({"walls", "wall"}), "The walls are made from a deep black "+
        "obsidian. It's so black that you have trouble discerning the "+
        "extents of the room. On the south wall, you notice a large "+
        "painting and in the south wall, you see @@doorway_desc_item@@.\n");

    add_item(({"painting", "large painting"}), "A grand painting of a "+
        "white unicorn rearing back upon it's hind legs as the rope binding "+
        "its neck to a stake in the ground is cut by a friendly elf. In the "+
        "background, you can see may other unicorns waiting nervously for "+
        "their friend to gallop to them. Just looking at it brings joy to "+
        "your heart and hope for the future.@@extra_desc@@\n");

    add_search(({"painting", "large painting"}), "pull aside", "", "find in "+
        "a hiding-place behind it,", OBJECTS + "bag_holding");

    room_add_object(OBJECTS + "congrat_scroll");
}

string doorway_desc()
{
    if(query_north_exit())
        return "a doorway leading to another room";
    else
        return "that a large rectangular area is consists not of stone but "+
            "shiny curved metal. It looks quite strange";
}

string doorway_check_desc()
{
    if(query_north_exit())
        return "A large rectangular doorway in the north wall.\n";
    else
        return "You find no doorway.\n";
}

string metal_desc()
{
    if(query_north_exit())
        return "You find no metal.\n";
    else
        return "A bizarre area of the north wall where the stone has been "+
            "cut away and a covered flush by a sheet of shiny metal.\n";
}

string doorway_desc_item()
{
    if(query_north_exit())
        return "a doorway leads northwards";
    else
        return "a section that seems to be made from solid curved metal";
}

string extra_desc()
{
    if(found)
        return " It is hanging at an angle as if it had been searched. You "+
            "can see a hiding-place behind it.";
    else
        return "";
}

mixed search_obj(object player, string str)
{
    object obj;

    if(!strlen(str))
    {
        notify_fail("Search what?\n");
        return 0;
    }

    if(found)
        return 0;

    if(member_array(str, item) == -1)
        return 0;

    found = 1;

    if(!player->test_bit(getuid(TO), GROUP, BIT))
    {
        seteuid(getuid(TO));
        obj = clone_object(filename);

        obj->move(TO);

        tell_room(TO, QCTNAME(player)+" "+LANG_TVERB(verb1)+
            (strlen(prep) ? (" " + prep) : "")+" the "+item[0]+" and "+
            LANG_TVERB(verb2)+" "+LANG_ASHORT(obj)+"!\n", player);

        return "You "+verb1+(strlen(prep) ? (" "+prep) : "")+" the "+item[0]+
            " and "+verb2+" "+LANG_ASHORT(obj)+"!\n";
    }
    else
    {
        tell_room(TO, QCTNAME(player)+" searches the painting and finds "+
            "a hiding-place behind it, but there is nothing in it.\n", player);

        return "You search behind the painting and find a hiding-place, but "+
            "there is nothing in it.\n";
    }
}
