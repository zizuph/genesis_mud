/*
 * The garden in Imladris
 * By Finwe, February 1998
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/herbs/herb_list.h"
 
inherit GARDEN_BASE;
//inherit "/d/Shire/lib/herbsearch.c";

void reset_room();

string herb_here; 
void
create_garden_room()
{
    add_exit(VALLEY_DIR + "garden03",  "south");
    add_exit(VALLEY_DIR + "garden01",  "west");

    reset_room();
}


void
reset_room()
{
    fruit_counter = 0;
    veggie_counter = 0;
    set_searched(0);
}
