/* plain04.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("Road east of Ringing Mountains leading to Tyr");
    set_long("You are travelling along a road of packed earth. "+
              "The Ringing Mountains are not far to your west, "+
              "and eastwards you can glimpse the Golden Tower "+
              "and the Ziggurat in the city of Tyr. You think you "+
              "vaguely can make out the walls of the Arena as well. "+
              "The road continues to the east and west "+
              "across the sandy plains. Far to the south you can "+
              "also glimpse a few farms across the shrublands.\n");

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
    add_exit(WILD_PLAINS+"plains05.c","west",0,1);
    add_exit(WILD_PLAINS+"plains03.c","east",0,1);
}
