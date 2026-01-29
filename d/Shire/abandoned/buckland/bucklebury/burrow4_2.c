inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow4_1","south",0,1
#define EXIT2 BB_DIR + "burrow4_3","east",0,1
#define EXIT3 BB_DIR + "burrow4_4","west",0,1

void reset_room();
void make_hob();

static object hob, hob2;

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 3;
    areatype  = "village";
    smialsize = "tiny";

    extraline = "The dining room doesn't have much special about it.  It "+
    "leads to a pantry and to a pantry, or back out to the front hall.";

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);



    make_the_room();
    reset_room();
}


void
reset_room()
{

    if (!hob)
      {
      set_alarm(1.5,0.0,"make_hob");
      }
}

void
make_hob()
{

    hob = clone_object(ER_DIR + "npc/femhobbit");
    hob->arm_me();
    hob->move(TO);

    hob2 = clone_object(ER_DIR + "npc/genhobbit");
    hob2->arm_me();
    hob2->move(TO);
}
