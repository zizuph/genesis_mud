/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
**
*/
#include "defs.h"
#include "/sys/ss_types.h"
inherit  ROOM+"kgardbase";
 
/* room definition */
void create_khalakhor_room() {
   setup_garden_room();
   set_long((query_std_long())+"The vegetation has been cleared away "+
      "somewhat here, leaving a small clearing covered with short "+
      "grass.\n");
 
   add_exit("kgarden8","east");
   (clone_object(SR_OBJ+"obelisk"))->move(this_object());
}
void setup_kgard_herbs()
{
    herbs = ({COM_HERBS+"shamrock"});
    set_up_herbs(herbs,({"grass","here"}), 2);
}
