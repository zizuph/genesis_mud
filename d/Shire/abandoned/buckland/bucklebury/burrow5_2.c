inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow5_1","north",0,1


void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 5;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "This room is not exactly what you would call neat.  There "+
    "clothes scattered on the floor and bed, and some papers are lying in a "+
    "heap on the dresser.";

    add_item(({"papers","dresser"}),"These papers aren't very important, "+
      "which is a good thing considering the way they were left lying "+
      "around.\n");

    add_item(({"clothes","floor","bed"}),"Some of these clothes are clean, "+
      "and others are dirty.  The hobbit who lives here must be very busy "+
      "since he can't seem to find time to pick up after himself.\n");

    add_exit(EXIT1);

    make_the_room();
}
