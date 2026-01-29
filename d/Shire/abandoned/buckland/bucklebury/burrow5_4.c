inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow5_3","east",0,1


void reset_room();
void make_hob();

static object hob;

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 4;
    areatype  = "village";
    smialsize = "tiny";

    extraline = "It looks as if a huge feast is being prepared in here.  "+
    "There are pots on the range, and a delicious aroma fills the "+
    "room.";

    add_item(({"stove"}),"You can't tell what is in the stove because the "+
      "pot is covered.  Whatever it is though, it smells delicious.\n");
    add_item(({"range","pots","cooking range"}),"The pots on the range "+
      "are simmering away, giving off tantalizing aromas.\n");


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

    hob = clone_object(ER_DIR + "npc/femhobbit");
    hob->set_title("Brandybuck");
    hob->arm_me();
    hob->move(TO);
}

