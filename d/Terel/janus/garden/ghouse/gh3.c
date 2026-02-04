/* greenhouse3.c */
/* janus 930408 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int vermin3;
init()
{
  ::init();
  vermin3=0;
}

create_room()
{
object door;
  set_short("hothouse");
  set_long(BS("You are inside a large hothouse. The air is warm " +
              "and humid. Standing in neat rows are benches packed "+
              "with claypots. Most of the pots are filled with flowers"+
              ", small bushes, and strange plants. "+
       "\n"));
  add_exit(JANUSDIR + "garden/ghouse/gh1", "south",0);
  add_exit(JANUSDIR + "garden/ghouse/gh5", "east",0);
  add_prop(OBJ_I_SEARCH_TIME,15);
  add_prop(OBJ_S_SEARCH_FUN,"do_search");
  add_item(({"walls","hothouse","glass"}),BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"bench","benches"}),BS("The benches are made out of "+
      "ordinary wood. Most of the benches are covered with pots "+
      "of all sizes and shapes. \n"));
add_item(({"bush","small bushes","small bush","bushes"}),BS("There are a few green bushes here, "+
      "almost all of them has a few dark brown leaves and partly "+
      "eaten leaves. \n"));
  add_item(({"plants","flowers","claypots","pots"}),
            BS("There are a plethora of strange plants in the pots. " +
               "Some of the plants seems to be damaged by some vermin. "+
               "Maybe if you searched the plants you could find the "+
               "bugs that have caused all this damage.\n"));
  add_item(({"walls","hothouse","glass","wall"}),
     BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"vermin","bugs"}),
     BS("Some of the plants seems to be damaged by some vermin. Maybe if you "+
        "searched you could find some bugs. The gardener would be very "+
        "happy if you killed the bugs.\n"));
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
    if(vermin3 < 4){
    seteuid(getuid(this_object()));
    vermin=clone_object(JANUSDIR + "monsters/vermin");
    vermin->move(TO);
    vermin3++;
    return BS("You hear the clicking sound from an insect. \n");
  }
    return BS("You find nothing here. \n");
  }
   return BS("You find nothing here.\n");
}



