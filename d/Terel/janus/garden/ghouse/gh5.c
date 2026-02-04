/* greenhouse5.c */
/* janus 930408 */
/*
    Modified 3 May 2003, by Bleys
        - fixed a typo in the set_long()
*/
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int vermin5;
init()
{
  ::init();
  vermin5=0;
}

create_room()
{
  set_short("hothouse");
  set_long(BS("You are inside a large hothouse. The air is warm " +
              "and humid. Standing in neat rows are benches packed "+
              "with claypots. Most of the pots are filled with flowers, "+
              "small bushes, and strange plants. "+
        "\n"));
  add_exit(JANUSDIR + "garden/ghouse/gh2", "south",0);
  add_exit(JANUSDIR + "garden/ghouse/gh3", "west",0);
  add_prop(OBJ_I_SEARCH_TIME,15);
  add_prop(OBJ_S_SEARCH_FUN,"do_search");
  add_item(({"walls","hothouse","glass"}),BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"plants","flowers","claypots","pots"}),
            BS("There are a plethora of strange plants in the pots. " +
               "Some of the plants seems to be damaged by some vermin. "+
                "Maybe if you searched the plants you could find the "+
               "bugs that have caused all this damage.\n"));
   add_item(({"bench","benches"}),BS("These are ordinary wooden benches with pots of all kinds and "+
     "shapes on them. \n"));
  add_item(({"bush","bushes","small bush","small bushes"}),BS(
   "There are lots of strange bushes here, bushes of all colors, "+
   "shapes, and sizes. Although all of them seems damaged by some "+
   "vermin. There are no bugs that you see with a cursory glance, "+
   "they must have hidden themselves when they heard you coming. \n"));
  add_item(({"walls","hothouse","glass","wall"}),
     BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"vermin","bugs"}),
    BS("Some of the plants seems to be damaged by some bugs. Maybe if you "+
        "searched you could find some vermin. The gardener would be very "+
        "happy if you killed the vermin.\n"));
}

do_search()
{
  object ob;
  object vermin;
  int i1;
  int i2;
  i1 = TP -> query_skill(SS_AWARENESS);
  i2 = i1- random(15);
  seteuid(getuid(this_object()));
  if (!CAN_SEE_IN_ROOM(TP)){
     return BS("You are blind as a bat in the darkness, so you'd better "+
               "get some light if you want to search here. \n");
  }
  if ( i2 > 0 ){
    if(vermin5 < 3){
    seteuid(getuid(this_object()));
    vermin=clone_object(JANUSDIR + "monsters/vermin");
    vermin->move(TO);
    vermin5++;
    return BS("Hidden under a leaf you find a small insect. \n");
  }
    return BS("You find nothing here. \n");
  }
   return BS("You find nothing here.\n");
}
