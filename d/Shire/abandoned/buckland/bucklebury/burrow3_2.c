inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


#define EXIT1 BB_DIR + "burrow3_1","north",0,1
#define EXIT2 BB_DIR + "burrow3_3","south",0,1

void reset_room();
void make_hob();

static object hob,hob2;

void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   =2;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "The parlour is cozy and is a good place to stop and "+
    "stay a while.  It is decorated with the same vivid colours as the "+
    "front hall.";


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

    hob2 = clone_object(ER_DIR + "npc/femhobbit");
    hob2->arm_me();
    hob2->move(TO);
}
