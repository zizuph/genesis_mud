
/* forest5.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal;

void
reset_qualinesti_room()
{
    
}

public string
do_crawl(string where)
{
    write("You fall to your knees and crawl slowly under thick bushes.\n");
    set_dircmd("northeast");
    TP->move_living("crawling from the bushes", FDIR + "forest50", 0, 0);
    return "";
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest50", "northeast", 0, 2, 1);
    
    add_item(({ "bushes", "under bushes" }),
        "The bushes are very thick here, but still you should be able " +
        "to crawl under them in the northeast direction.\n");

    add_cmd_item(({ "bushes", "under bushes", "northeast" }), "crawl", 
        do_crawl);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    reset_qualinesti_room();

}

