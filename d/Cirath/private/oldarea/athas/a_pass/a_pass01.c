/* a_pass01.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are at the beginning of a trail leading into "+
              "the mountains a little bit. It seems to turn "+
              "slightly to the northwest, going along the mountain "+
              "range. The barren "+
              "rocky landscape is devoid of visible life, and the "+
              "sun beats down relentlessly from above. The trail "+
              "continues to the northwest, and eastwards across the "+ 
              "plains you can glimpse the city of Tyr, home of Kalak "+
              ", the Sorceror-King.\n");
    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(PASS_DIR+"a_pass02.c","northwest",0,1);
    add_exit(PASS_DIR+"plain05.c","east",0,1);
}
