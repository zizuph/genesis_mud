inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


#define EXIT1 BB_DIR + "burrow4_2","north",0,1
#define EXIT2 BB_DIR + "buroad14","south",0,1

void reset_room();
void make_hob();

static object hob;

void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   =1;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "This front hall is very large and spacious.  Of course, "+
    "it may just seem that way due to the lack of furniture in here.";

    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
    reset_room();
}


void
reset_room()
{
    if(!hob)
      set_alarm(1.5,0.0,"make_hob");
}

void
make_hob()
{
    hob = clone_object(ER_DIR + "npc/genhobbit");
    hob->arm_me();
    hob->move(TO);
}

