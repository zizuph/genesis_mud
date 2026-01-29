inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow1_4","west",0,1
#define EXIT2 BB_DIR + "burrow1_6","east",0,1

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

    extraline = "The table is partially set and ready for the next meal. "+
    "The kitchen and the pantry are on either side of the dining room.";

    add_exit(EXIT1);
    add_exit(EXIT2);


    add_item("table","The table has a couple of places set, and a stack "+
      "of dishes ready to be set at the other ones.\n");

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
