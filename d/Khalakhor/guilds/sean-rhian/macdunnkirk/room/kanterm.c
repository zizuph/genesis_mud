// Kirk Anteroom - link between kirk and abbey
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/11/98     Zima        Created
//
/* inherits/includes */
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/guilds/sean-rhian/lib/zdoor.h"
#define  OPATH ROOM+"kcorr1"
inherit  SR_LIB+"zindoor";
inherit  "/d/Khalakhor/std/room";

//
// checkExit() - when door is open, player can exit west. This function 
//               adds additional checks (see: sr/lib/zindoor.c)
int checkExit(object player) {
    object book;
    if (book=present(SR_OMOS_BOOK,player)) {
        book->move(MACDUNN_KIRK+"room/kchapel.c");
        write("The " + book->query_short() + " disappears in a momentary "+
              "flash of light.\n");
    }
    return 0; // player can exit
}

void create_khalakhor_room() {
   set_short("Anteroom of the kirk");
   set_long("   This bare chamber is the anteroom of the kirk, which serves "+
            "as a passage between the kirk and the abbey. Its cold stone "+
            "walls are adorned only by a tapestry which hangs on the "+
            "east wall. A large pointed archway on the south wall marks "+
            "the entrance to the central sanctuary of the kirk, while "+
            "a heavy oak door guards the way to the abbey to the west.\n");
 
   INSIDE;
   add_prop(SR_K1SECURE,1);
   add_item("tapestry",
      "It is a wool tapestry threaded with the portrait of a wizened "+
      "white-haired manach dressed as an abbot in a white robe and a "+
      "purple scapular, cincture, mitre and cope, holding an ornate silver "+
      "crozier, a tall staff with a curling crook on the top in the shape "+
      "of a shepherd's staff.\n");
   add_item(({"arch","archway","sanctuary"}),
      "The entrance to the sanctuary to the south is marked by a wide "+
      "arch which rises to a point at the top.\n");
 
   add_exit("ksanct7","south");
 
   setup_indoor("west", OPATH, ({"door"}),
      "It is a heavy oak door used to secure the kirk while private "+
      "rites are being performed by the manachs in the kirk. It has a "+
      "bolt lock on it.",
      "heavy oak door", 0, BOLTABLE, OPENED, 100, &checkExit());
}
 
void init()
{
   ::init();
   add_indoor_actions();
}
