/* plain02.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("Road west of Tyr");
    set_long("You are just west of Tyr, travelling along the straight road. "+
              "Rising above the city walls to the east you can "+
              "see the Golden Tower, the Ziggurat and the walls of "+
              "the Arena. The road continues to the east and west "+
              "across the sandy plains.The Ringing Mountains loom "+
              "in the western horizon. In the shrubland to the south "+ 
              "there are few pathetic farms visible.\n");

    add_item("road","Its a road of packed earth, rising about 10ft above "+
              "the surrounding ground.\n");
    add_item("sun","The sun is blazing down on you from a clear blue sky, "+
              "and burns the life away from the land.\n");
    add_item(({"tower","Golden Tower","golden tower"}),"The home of Kalak "+
             "rises with an unmatched splendour towards the sky, its blazing "+
             "beauty shines brightly, as if in contest with the sun.\n");
    add_item(({"Ziggurat","ziggurat"}),"Kalaks latest addition to Tyr, the "+
            "Ziggurat, towers above the city as a steady reminder to the "+
            "citizens of the Might of Kalak.\n");
    add_item(({"Arena","arena"}),"The walls of the Arena are visible, where "+
            "Kalak and the citizens regularly enjoy watching matches between "+
            "gladiators and beasts of various kinds.\n");
    add_item(({"plains","farms","shrubs"}),"South across the "+
            "sandy plains there are dry shrubs and a few farms "+
            "on the verge of collapse.\n");
    add_item(({"Ringing Mountains","mountains"}),"The Ringing Mountains "+
            "cover the entire west horizon. Despite their barren apperance "+
            "they look beutiful when the sun hits the reddish colored mountains.\n");
 
    OUTSIDE
    add_exit(PASS_DIR+"plain03.c", "west", 0, 3);
    add_exit(PASS_DIR+"plain01.c", "east", 0, 3);
}
