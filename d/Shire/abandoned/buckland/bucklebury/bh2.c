inherit "/d/Shire/room";

int no_package;
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"



#define EXIT1 BB_DIR + "bh6","east",0,1
#define EXIT2 BB_DIR + "bh1","north",0,1


void reset_room();
void make_hob();
static object hob;


void
create_room()
{
object door;
   set_short("You are standing in the front entrance of Brandy Hall in "+
      "Bucklebury in the Shire");
    set_long("You are standing in the front entrance of Brandy Hall in "+
      "Bucklebury in the Shire.  The front hall is huge, extending "+
      "farther to the north, where there is another set of doors that "+
      "lead to the outside as well.  This must be the main entrance, "+
      "as it seems more used than the other one.  Further "+
      "inside, to the east, is a corridor that leads to the inner "+
      "part of the burrow.  The only piece of furniture in this room "+
      "is a small table.\n");

    add_item(({"table","small table"}),"@@check_table@@");
    add_item(({"package","brown package"}),"@@check_package@@");
    add_cmd_item(({"package","brown package"}),({"get","take"}),
      "@@get_package@@");


    add_exit(EXIT1);
    add_exit(EXIT2);

    door=clone_object(BUCK_DIR + "doors/bhdoor");
    door->set_door_id("brandy1");
    door->set_pass_command(({"w","west"}));
    door->set_other_room(BB_DIR + "buroad2");
    door->set_inside();
    door->move(this_object());


    reset_room();
}

void
reset_room()
{
    if(!hob)
      {
      set_alarm(1.5,0.0,"make_hob");
      }
    no_package=0;
}

string
check_table()
{
    if (no_package)
      return("This is a small, round table.  There are some papers lying "+
        "on it.\n");
    else
      return("This is a small, round table.  There are some papers lying "+
        "on it.  There is also a brown package on it.\n");
}

string
check_package()
{
    if (no_package)
      return("You see no package.\n");
    else
      return("You see a brown package lying on the table.  It is "+
        "addressed to ???? (to be put in later).\n");
}

string
get_package()
{
    if (no_package)
      return("There's no package here!\n");
    else
      {
      no_package=1;
      clone_object(BUCK_DIR + "obj/package")->move(TP);
      
      tell_room(this_object(),QCTNAME(TP)+" takes a package off of "+
        "the table.\n",TP);
      return("You take a package off of the table.\n");
      }
}


void
make_hob()
{

    hob = clone_object(ER_DIR + "npc/genhobbit");
    hob->set_title("Brandybuck");
    hob->arm_me();
    hob->move(TO);
}
