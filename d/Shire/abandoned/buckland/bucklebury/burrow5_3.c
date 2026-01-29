inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow5_4","west",0,1
#define EXIT2 BB_DIR + "burrow5_1","east",0,1

void reset_room();
void make_hob();

static object hob;

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 3;
    areatype  = "village";
    smialsize = "tiny";

    extraline = "The table is completely set, except for the food."+
    "The kitchen is right next door to here, and you can smell some "+
    "delicous food being prepared.";

    add_exit(EXIT1);
    add_exit(EXIT2);



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
    hob = clone_object(ER_DIR + "npc/genhobbit");
    hob->arm_me();
    hob->move(TO);
}
