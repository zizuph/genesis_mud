// file name:        /d/Avenir/common/holm/jungle/hf10.c
// creator(s):       Lilith, Dec 96
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/hf_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
string *herbs = HERB_MASTER->query_herbs( ({"pine", "desert"}) );

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}

/* Now create the room.  */
void
create_hf_room()
{
    set_short("On a ridge overlooking the forest");
    set_long("You have reached a corner of the ridge which over"+
        "looks the verdant interior of the island. Scraggly pine "+
        "trees hug the mountainside, while small plants cling "+
        "tenaciously to the cliff-edge. Following the path "+
        "northeast will lead you further up the mountain.\n");

    add_ridge();
    add_item("path", "Its follows the ridge.\n");
    add_exit("hf6", "northeast", 0);
    add_exit("hf9", "west", 0);

    set_up_herbs(({ GET_ONE(herbs), GET_ONE(herbs), GET_ONE(herbs) }), 
        ({"pine","pines","mountainside","cliff","edge","cliff-edge"}), 5);

    reset_domain_room();
}
