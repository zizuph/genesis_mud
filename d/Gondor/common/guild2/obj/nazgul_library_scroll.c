#include <language.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit "/d/Gondor/common/guild2/lib/library_book";

void create_library_book()
{
    string adj, *adjs;
    string race, *races;

    // Determine the adjective
    adjs = ({ "weathered", "dusty", "faded" });
    adj = adjs[random(sizeof(adjs))];
    add_adj(adj);

    // Determine the race of the parchment
    races = ({ "dwarven", "elven", "hobbit" });
    race = races[random(sizeof(races))];

    // Set the rest of the descriptions
    set_name("scroll");
    set_pname("scrolls");
    set_short(adj + " scroll");
    set_long("The " + adj + " scroll is made from the skin of " + LANG_ADDART(race) + 
        " prisoner. On two sides of the parchment a long bone is attached, " +
        "allowing the scroll to be rolled up.\n");
}

int return_library_book()
{
    int ret;

    ret = ::return_library_book();
    if(ret)
    {
        // Reward the Nazgul
        IDLENESS->increase_activity( this_player(), EMOTION / 2);
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

    // Reward the Nazgul
    IDLENESS->increase_activity( this_player(), NAZ_LIB_READ );
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

    // Reward the Nazgul
    if(ret)
        IDLENESS->increase_activity( this_player(), NAZ_LIB_WRITE );

    return ret;
}