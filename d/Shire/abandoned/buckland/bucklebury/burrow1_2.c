inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


#define EXIT1 BB_DIR + "burrow1_4","north",0,1
#define EXIT2 BB_DIR + "burrow1_1","east",0,1
#define EXIT3 BB_DIR + "burrow1_3","south",0,1
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

    extraline = "The parlour is very cozy with much more atmosphere "+
    "than the front hall. Off of the parlour are two other parts of the "+
    "burrow.  One way leads to the bedrooms, and the other leads to "+
    "the dining room and kitchen.";


    add_exit(EXIT1);
    add_exit(EXIT3);
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
