// file name:        /d/Avenir/common/herbs/example_herb_room.c
// creator(s):       Lilith, Jan 97
// purpose:          Ease of adding herbs to areas. No more need to 
//                   hunt around, trying to decide which of the 100+
//                   available herbs are suitable for your area.
//                   Just look at herb_master.c to see what the 
//                   pre-defined area types are, then use the one
//                   that fits best in the string *herbs (below).
//                 THIS IS JUST AN EXAMPLE OF HOW TO USE herbsearch.h
// note:             Gondor's Olorin and Elessar did all the hard
//                   work for the herb-related code. We're standing
//                   on the shoulders of giants, here.

inherit  "/std/room";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/herbs/herbsearch.h"
#define GET_ONE(x)   ((x) [random(sizeof(x))])

/* 
 * The set_up_herbs() will look for the herbs to be
 * found. *herbs will refer to the herb_master.c area
 * type defined as 'garden' and return the list of
 * herbs designated for that area type.
 */
string *herbs = HERB_MASTER->query_herbs( ({"garden"}) );

void
reset_room()
{
    set_searched(-5);
}

void
create_room()
{
    set_short("The garden");
    set_long("You are in the middle of a garden. There are rivers "+
        "flowing both east and west past this promontory in " +
        "the floodplain. The soil is rich and the beds are "+
        "well-tended, and they yield a wealth of food, herbs, "+
        "and flowers.\n");
    add_item(({"garden", "beds", "soil"}), "The soil in this garden "+
        "is renewed each spring, when the floods come. The soil is "+
        "rich with sediment washed here from upstream.\n");    

    reset_room();
    seteuid(getuid(TO));
    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ GET_ONE(herbs), GET_ONE(herbs), GET_ONE(herbs) }), 
        ({ "garden","beds","soil" }), 5);
}
