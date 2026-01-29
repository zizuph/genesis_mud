/* cityview.c
 * The location where the player can see the City of Qualinost. It is
 * impossible to enter it for now, thou.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

int     exit_check();

void
reset_qualinesti_room()
{
//    set_animal();
}

void
create_forest()
{
    set_long_desc("You find yourself standing on a small hill and " +
        "you realize it was not a clearing you saw from within the " +
        "forest. The trees growing on the hillside were not stopping " +
        "the sunlight, so more of it was entering the woods. And then " +
        "you notice where you are. From here you have a perfect view " +
        "on the elven city of Qualinost. Four arched bridges that run " +
        "from guard tower to guard tower and a central Tower of the Sun " +
        "are looking really astoundingly. You wish you could enter that " +
        "city some day."); 
    add_my_desc("\n");
    
    add_item("hill",
        "You are standing on the small hill, from where the beatiful " +
        "view spreads on the whole area.\n");
    add_item(({"bridge", "bridges"}),
        "The city is surrounded by four arched bridges running between " +
        "guard towers of Qualinost.\n");
    add_item("towers",
        "There are four guard towers in the city. They are conneted by " +
        "arched bridges. From this place you notice also the high Tower " +
        "of the Sun.\n");
    add_item(({"tower", "tower of the sun", "Tower of the Sun",
        "tower of the Sun", "Tower of the sun" }),
        "In the middle of the city, between four guard towers, you notice " +
        "the gold-burnished Tower of the Sun, where the Speaker of the Suns " +
        "resides.\n");
    add_item( ({"Qualinost", "qualinost", "city"}),
        "This is a magnificant city of Qualinost, founded by Kith-Kanan " +
        "when he led the Qualinesti people from the oppressive " +
        "Silvanesti homeland. Here also stands the gold-burnished " +
        "Tower of the Sun, where the Speaker of the Suns resides. " +
        "Instead of city walls, Qualinost is surrounded by four " +
        "arched bridges that run from guard tower to guard tower. " +
        "At city center lies the open square called the Hall of the " +
        "Sky, which overlooks the whole sylvan city. You can hardly " +
        "see any movement from here.\n");
    
    OUTSIDE;

    add_exit(FDIR + "qpath6.c", "east", 0, 2);
    add_exit(FDIR + "cityview.c", "south", "@@exit_check", 2);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    reset_qualinesti_room();
}

int
exit_check()
{
    write("The path ends here and it seems it is impossible to approach " +
        "the city from this place.\n");
        
    return 1;
}
