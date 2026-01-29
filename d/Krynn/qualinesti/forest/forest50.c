/* forest50.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal, animal2, elf;

void
reset_qualinesti_room()
{
if ( !elf )
    {
        elf = clone_object(STD + "scout_base");
        elf->move(TO, 1);
        elf->command("hide");
    }

    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }
    if ( !animal2 )
    {
        animal2 = random_animal();
        animal2->move(TO, 1);
    }
}

public string
do_crawl(string where)
{
    if ( (TP->query_race() == "hobbit") || (TP->query_race() == "gnome") ||
         (TP->query_race() == "dwarf") )
    {
        write("You fall to your knees and slowly crawl under the bushes.\n");
        TP->move_living("crawling through the bushes", FDIR + "forest55", 0, 0);
        return "";
    }
    else
        return "You are too big to crawl there.\n";
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest46.c", "north", 0, 2);
    add_exit(FDIR + "forest47.c", "northeast", 0, 2);
    add_exit(FDIR + "forest51.c", "east", 0, 2);

    add_cmd_item(({ "bushes", "under bushes", "southwest" }), "crawl", 
        do_crawl);

    reset_qualinesti_room();

}
