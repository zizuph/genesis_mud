inherit "/d/Khalakhor/ship/macdunn/wbeach/bbase";
#include <macros.h>
#include <ss_types.h>
#include "local.h"
#define  MIN_SS_CLIMB 40
 
object base_rm=(BEACH_DIR+"bbase")->query_pointer();
 
void create_khalakhor_room()
{
   create_beach_room();
   set_long("   You are at the end of the rocky beach, where the high "+
       "cliffs portrude directly into the sea, blocking your progress "+
       "further west. The waves crash especially hard against this "+
       "bold outcropping of the cliff, as if it is angered that the "+
       "rocks dare come directly into its waters.\n");
   add_item(({"cliff","cliffs","outcropping","plateau"}),
       "Forged by the constant crashing of the tide, the cliffs "+
       "rise high along the north side of the beach with sharp "+
       "jagged edges. "+
       "The cliff charges from its line just to the north directly "+
       "into the sea to the south. Like a massive wall, it blocks "+
       "your progress further west. There seems to be a plateau atop "+
       "the cliff overlooking the sea.\n");
 
   add_exit("b9","southeast");
}
 
public void enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if ((from!=TO)&&(interactive(ob)))
      base_rm->start_pound_surf();
}
 
public string go_rocks()
{
   if ((TP->query_skill(SS_CLIMB))<MIN_SS_CLIMB)
      {
      write("You ignorantly try to climb up the rocks of the cliff, but "+
            "slip and crash down onto the beach. You are injured on the "+
            "edges of the rocks.\n");
      say(QCTNAME(TP) + " attempts to climb up the rocks of the cliff but "+
            "slips and falls back onto the beach.\n");
      TP->heal_hp(-50);
      if (TP->query_hp() <= 0)
          TP->do_die();
      }
   else
      {
      write("You very carefully climb up the sides of the "+
            "cliff onto the plateau.\n");
      TP->move_living("climbing up the dangerous cliff",
                      BEACH_DIR+"plateau1");
      }
   return "";
}
