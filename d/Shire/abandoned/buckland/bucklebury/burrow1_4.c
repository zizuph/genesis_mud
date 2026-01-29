inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow1_5","east",0,1
#define EXIT2 BB_DIR + "burrow1_2","south",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 4;
    areatype  = "village";
    smialsize = "tiny";

    extraline = "This kitchen, just like the other rooms, is spotless. "+
    "This room does look like it gets a lot of use, even though there "+
    "is nothing cooking at the moment.";



    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
}



