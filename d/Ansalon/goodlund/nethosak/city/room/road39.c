#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
inherit MITHAS_OUT;

object citizen;
object citizen2;

void 
reset_mithas_room()
{
    if(!objectp(citizen))
    {
      citizen = clone_object(MNPC + "citizen");
      citizen->move(this_object());
   }
   if(!objectp(citizen2))
   {
      citizen2 = clone_object(MNPC + "citizen");
      citizen2->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Near the post office");
    set_long("@@long_descr"); 

    add_item(({"small store","store"}), "The "+
       "store is made out of grey stone.\n"); 

    add_item(({"oak tree","tree"}), "This "+
       "ancient tree stretches it's long twisted "+
       "branches high into the air, the trunk "+
       "has been partialy burned.\n");

    add_cmd_item(({"tree"}),"climb","@@climb_tree");

    add_exit(MROOM + "road40","north",0);
    add_exit(MROOM + "road23","south",0);
    add_exit(MROOM + "p_office","east",0);   
    add_exit(MROOM + "store","west",0);
    reset_mithas_room();       
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on a road next to the "+
          "post office and shop in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to north "+
          "towards the center of the town and south to the southern "+
          "gate. To the west a small store has been build, and to "+
          "the east the local post office rises. A ancient oak tree "+
          "is growing in the middle of the street here." +
          season_descr()+ "\n";
}

int
climb_tree()
{


    if(this_player()->query_skill(SS_CLIMB) < 29)
    {
        write("You begin to climb the huge oak tree. Suddenly you loose your " +
          "grip and fall to the ground.\n");
        say(QCTNAME(this_player()) + " attempts to climb the oak tree but "+
            query_pronoun() + " suddenly looses " +query_possessive()+ 
            " grip and falls to the ground.\n");
        this_player()->command("scream");
        write("You hit the ground with a thud!\n");
        this_player()->heal_hp(-200);
        return 1;
    }
    write("You easily climb up the huge oak tree.\n");
    this_player()->move_living("up the huge oak tree and disappears " +
      "in the canopy",MROOM + "up_tree1",1,0);
    return 0;
}

