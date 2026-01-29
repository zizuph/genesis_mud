inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "bh7","south",0,1


void reset_room();
void make_hob();

static object hob, hob2;


void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 2;
    areatype  = "village";
    smialsize = "large";

    extraline = "This room is the kind that wants to make you stay and "+
    "relax for a while.  It probably has something to do with the fire "+
    "that is burning in the fireplace, giving off warmth and a soft glow.";

    add_item(({"fire","fireplace"}),"The fire is quite a large one, giving "+
      "off a lot of warmth and casting shadows on the walls.\n");

    add_exit(EXIT1);

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

    hob2 = clone_object(ER_DIR + "npc/bighobbit");
    hob2->arm_me();
    hob2->move(TO);
}
