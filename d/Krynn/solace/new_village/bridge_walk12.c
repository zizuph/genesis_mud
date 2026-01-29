/*
 * The village Solace
 *
 * By Rastlin
 */

/* Navarre June 2008:  Removing the 'store closed by night' idea.
 * It is annoying for the players.
 */


#include "local.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit SOLOUTROOM;

#include "/d/Krynn/common/herbsearch.h"

reset_solace_room()
{
    set_searched(random(2));
}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_item("shop", "The shop is quaintly nestled in the " +
             "vallenwood tree. It looks like it has served many " +
             "a customer, based on the scuffed planks leading to " +
             "it.\n");
    add_item("sign","The sign reads:\nThis store has great items " +
             "for low prices, not to mention extended opening hours. " +
             "Come on in!\n");
    add_item(({"planks", "scuffed planks"}), "These planks have " +
             "felt the abuse of many a boot, yet are still sturdy.\n");
    add_cmd_item("sign","read", "This store has great items " +
                 "for low prices, not to mention extended opening hours. " +
                 "Come on in!\n");
    add_exit(TDIR + "bridge_walk13", "north");
    add_exit(TDIR + "shop", "east");
    add_exit(TDIR + "bridge_walk11", "southeast");


    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();

}

public string
my_desc()
{
    string str, people;

    str = "Located in this vallenwood tree is a shop. There " +
     "is a sign hanging outside the store. There is a small " +
     "stairway leading east into the shop. Looking down, " +
	  "you can see the intersection of the Solace Main road, " +
	  "the East road and the West road. ";

    if ((people = get_living(({TDIR + "intersection"}))))
        str += "You can see " + people + " walking on the Main road. ";

    str += "The bridge-walk continues southeast and north from here. " +
           "The limbs of the trees mesh to form a thick canopy overhead.";

    return str;
}

// Not used anymore.
int
shop_closed_at_night()
{
    int *the_time = GET_TIME;

    if (the_time[HOUR] >= 6 && the_time[HOUR] <= 20)
      return 0;

    write("The shop is closed for the night. Please come back in the morning.\n");
    return 1;
}
