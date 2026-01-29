// Sea in the underground ocean.
//   -Cirion, 1997
inherit "/std/room";

#include "../ship.h"
#include "/d/Avenir/common/common.h"

#define PARKROOM    (PK + "s_path6")

void
create_room()
{
    set_short("void");
    set_name("ship_void");
    set_long("This is a void room.\n");


}

int
present_living(object ship)
{
    string *deck = ship->query_deck();
    object *inv;
    int i;

    for(i=0;i<sizeof(deck);i++)
    {
        if(!sizeof(inv = all_inventory(find_object(deck[i]))))
           continue;

        if(sizeof(FILTER_PLAYERS(inv)))
           return 1;
     }

    return 0;
}    

/*
 * only go to the park if:
 * 1. There is an interactive on board the ship, or
 * 2. The ship has been "summoned" from the park
 */
void
enter_inv(object to, object from)
{
    object park;

    ::enter_inv(to, from);

    park = find_object(PARKROOM);
    if(!park)
    {
        PARKROOM->teleldensanka();
        park = find_object(PARKROOM);
    }

    if(!(to->id("ship")) && !(to->id("captain")))
       to->move(park, 1);

    if(!(park->query_ship_summoned()) && !present_living(to))
       return;

    to->move(park);
}


