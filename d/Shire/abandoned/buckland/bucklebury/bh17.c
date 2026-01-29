inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "bh3","west",0,1
#define EXIT2 BB_DIR + "bh18","south",0,1
#define EXIT2 BB_DIR + "bh18","south",0,1

void reset_room();
void make_hob();

static object hob, hob2, hob3;

void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 2;
    areatype   = "village";
    smialsize  = "large";

    extraline = "This is the smoking room of Brandy Hall.  There are "+
    "many different kinds of tobacco here, as well as a large collection "+
    "of pipes.";


    add_item(({"pipes","collection","collection of pipes"}),"You have never "+
      "seen so many pipes in one place before.  There are all different "+
      "sizes and kinds of pipes.\n");

    add_item(({"tobacco"}),"There is a lot of tobacco kept in this room.  "+
      "It smells very strong in this room.\n");



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
    hob->set_title("Brandybuck");
    hob->arm_me();
    hob->move(TO);

    hob2 = clone_object(ER_DIR + "npc/bighobbit");
    hob2->set_title("Brandybuck");
    hob2->arm_me();
    hob2->move(TO);


    hob3 = clone_object(ER_DIR + "npc/genhobbit");
    hob3->set_title("Brandybuck");
    hob3->arm_me();
    hob3->move(TO);

}

