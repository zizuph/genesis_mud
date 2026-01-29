inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "bh7","west",0,1
#define EXIT2 BB_DIR + "bh12","east",0,1

void reset_room();
void make_hob();

static object hob, hob2, hob3;

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 3;
    areatype  = "village";
    smialsize = "large";

    extraline = "You can smell the aromas of food cooking drifting in "+
    "from the kitchen next door.  You could also take a wander out into "+
    "the corridor, which leads to other parts of the burrow.";

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

    hob = clone_object(ER_DIR + "npc/femhobbit");
    hob->set_title("Brandybuck");
    hob->arm_me();
    hob->move(TO);

    hob2 = clone_object(ER_DIR + "npc/genhobbit");
    hob2->set_title("Brandybuck");
    hob2->arm_me();
    hob2->move(TO);

    hob3 = clone_object(ER_DIR + "npc/wehobbit");
    hob3->set_title("Brandybuck");
    hob3->arm_me();
    hob3->move(TO);

}
