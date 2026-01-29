inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "bh5","east",0,1


void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 6;
    areatype   = "village";
    smialsize  = "large";

    extraline = "This room is much neater than the master bedroom.  The "+
    "Master of Brandy Hall must take pride in having his guests stay in "+
    "a clean and comfortable room.";


    add_exit(EXIT1);

    make_the_room();
}
