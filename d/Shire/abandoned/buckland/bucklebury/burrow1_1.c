inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


#define EXIT1 BB_DIR + "burrow1_2","west",0,1
#define EXIT2 BB_DIR + "buroad12","east",0,1

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

    extraline = "This hall is rather small, with nothing much in particular "+
    "to look at. You would probably have a more interesting time if you "+
    "ventured further in.";

    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
    reset_room();
}

void
reset_room()
{
    if(!hob)
      {
      set_alarm(1.5,0.0,"make_hob");
      }
}

void
make_hob()
{

    hob = clone_object(ER_DIR + "npc/genhobbit");
    hob->arm_me();
    hob->move(TO);
}
