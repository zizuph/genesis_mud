/* File         : /d/Khalakhor/se_speir/plains/room/tfor_h_04.c
 * Creator      : Zima@Genesis
 * Date         : ??-??-??   
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications: Modified by Darragh 01-01-23
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
inherit SR_DIR+"lib/branchcmd";

void reset_room() { set_numbranches(2); }

void
create_khalakhor_room()
{
   create_tforest();

   add_item(({"trees"}),
            "They are tall and straight, mostly pine, their "
          + "branches stretching out in all directions high "
          + "above. There is a small thorny tree or shrub "
          + "growing amongst the pines.\n");
   add_item(({"plum","shrub","wild plum","small tree","thorny tree"}),
              "It is a small thorny tree, really a shrub, with white "
            + "flowers and burgundy colored fruits. It looks like a "
            + "wild plum.\n");
   add_item(({"plum","plums","fruit","fruits"}),
              "They are burgundy colored plums hanging on the thorny "
            + "shrub. They don't look ripe.\n");
   add_cmd_item(({"plum","fruit","plum from shrub","fruit from shrub"}),
                ({"take","get","pick","pluck"}),
                  "They are not ripe enough to pick.\n");
   set_branchnum(8); // plum
   set_numbranches(2);

   add_exit(PLAINS + "tfor_h_03","west",0,1,1);
   add_exit(PLAINS + "tfor_g_03","northwest",0,1,1);
   add_exit(PLAINS + "tfor_g_04","north",0,1,1);
   add_exit(PLAINS + "tfor_g_05","northeast",0,1,1);
   add_exit(PLAINS + "tfor_h_05","east",0,1,1);
   add_exit(PLAINS + "tfor_i_05","southeast",0,1,1);
   add_exit(PLAINS + "tfor_i_04","south",0,1,1);
   add_exit(PLAINS + "tfor_i_03","southwest",0,1,1);


   set_long(query_long() + " It looks as if it is possible to travel "
                         + "in nearly every direction from here.\n");
}
void init()
{
   ::init();
   add_action(&break_branch(),"break");
}

