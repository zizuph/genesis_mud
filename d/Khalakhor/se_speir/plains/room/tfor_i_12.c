/* File         : /d/Khalakhor/se_speir/plains/room/tfor_i_12.c
 * Creator      : Zima@Genesis
 * Date         : ??-??-??
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications: Modified by Darragh 01-01-23
 */

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#pragma strict_types
#include "plains.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/defs.h"
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
inherit SR_DIR+"lib/branchcmd";
inherit HERBSEARCH;

void reset_room() { set_searched(0);  set_numbranches(2); }

void create_khalakhor_room()
{
   create_tforest();

   set_branchnum(4);
   set_numbranches(2);

   add_item(({"trees"}),
            "They are tall and straight, mostly pine, their "
          + "branches stretching out in all directions high "
          + "above. There is a small tree with nuts mixed in "
          + "with the pines.\n");
   add_item(({"tree","small tree","shrub"}),
              "It is a small tree, really just a large shrub, "
            + "growing amongst the pines. It has small embracted "
            + "nuts on it.\n");
   add_item(({"nuts"}),
              "There are some on the small tree, though they "
            + "look too green to pick.\n");
   add_cmd_item(({"nuts","nut","nut from tree"}),"pick",
                  "The nuts on the tree look too green to pick. "
                + "Perhaps some have fallen onto the forest floor "
                + "though.\n");

   add_exit(PLAINS + "tfor_i_11","west",0,1,1);
   add_exit(PLAINS + "tfor_h_11","northwest",0,1,1);
   add_exit(PLAINS + "tfor_h_12","north",0,1,1);
   add_exit(PLAINS + "tfor_h_13","northeast",0,1,1);
   add_exit(PLAINS + "tfor_i_13","east",0,1,1);
   add_exit(PLAINS + "tfor_j_13","southeast",0,1,1);
   add_exit(PLAINS + "tfor_j_12","south",0,1,1);
   add_exit(PLAINS + "tfor_j_11","southwest",0,1,1);


   set_long(query_long() + " It looks as if it is possible to travel "
                         + "in nearly every direction from here.\n");

   set_up_herbs(({KRHERB+"hazelnut"}), ({"here","forest","floor"}), 2);
}
void init()
{
   ::init();
   add_action(&break_branch(),"break");
}
