inherit "/d/Khalakhor/ship/macdunn/wbeach/bbase";
#include "local.h"
object base_rm = (BEACH_DIR+"bbase")->query_pointer();
void create_khalakhor_room()
{
   create_beach_room();
   add_exit("b6","southeast");
   add_exit("b8","west");
}
 
public void enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if ((from!=TO)&&(interactive(ob)))
      base_rm->start_pound_surf();
}
