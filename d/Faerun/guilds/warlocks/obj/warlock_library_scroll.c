/*
*  /d/Faerun/guilds/warlocks/obj/warlock_library_scroll.c
*
*  2018, Nerull
*
*/

#include <language.h>
#include "../guild.h"

inherit WARLOCK_OBJ_DIR + "library_book";

void create_library_book()
{
    string adj, *adjs;
    string race, *races;

    // Determine the adjective
    adjs = ({ "weathered", "dusty", "faded" });
    adj = adjs[random(sizeof(adjs))];
    add_adj(adj);

    // Set the rest of the descriptions
    set_name("scroll");
    set_pname("scrolls");
    set_short(adj + " scroll");
    set_long("The " + adj + " scroll is made from the skin of " 
    +"some unlucky infants. On two sides of the "
    +"parchment a long wooden stick is attached, " 
    +"allowing the scroll to be rolled up.\n");
}


int return_library_book()
{
    int ret;

    ret = ::return_library_book();
    
    if (ret)
    {
        // reward?
    }

    return ret;
}


/*
* Function name: read_it
* Description:   Perform the actual read
*/
void
read_it(string answer)
{
    mixed data;

    ::read_it(answer);
}


/*
* Function name: submit_library_book
* Description  : Function called when we want to submit this book
* Returns      : 0 on failure, 1 on success
*/
int submit_library_book()
{
    int ret;

    ret = ::submit_library_book();

    return ret;
}
