/* Kirk of Port City - Corridor
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/25/97     Zima        Created
** 6/20/98     Zima        Added door
*/
/* inherits/includes */
#include "defs.h"
#define  OTHER ROOM+"kcorr7"
inherit  SR_LIB+"zoutdoor";
inherit  ROOM+"kcorr";
 
/* room definition */
void create_khalakhor_room()
{
   extra = "A wrought iron gate inlaid with panes of stained glass guards "+
           "the corridor to the south.";
   init_kcorr("west","east","north","south");
   add_exit("kcorr5",   "north");
   add_exit("kclassrm", "west");
   setup_outdoor("south",OTHER,({"gate"}),
      "It is a wrought iron gate, its poles twisted and cast in swirling "+
      "and interlocking lines and scrolls. Panes of stained glass are "+
      "cut and set into the gate, obscuring the corridor behind it "+
      "to the south. Its beauty is deceptive of its strength.",
      "wrought iron gate",0);
}

void init()
{
   ::init();
   add_outdoor_actions();
}
