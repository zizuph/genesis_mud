/* orang1.c */
/* janus 920817 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

init()
{
  ::init();
  add_action("do_pick","pick");
}

create_room()
{
object door;
  set_short("hothouse");
  set_long(BS("You are inside a large hothouse. The air is warm " +
              "and humid. Standing in neat rows are benches packed "+
              "with claypots. Most of the pots are filled with flowers"+
              ", small bushes, and strange plants. "+
              "This seems to be the place where the gardener is " +
              "nurturing his plants before placing them in the "+
              "garden proper. \n"));
  add_exit(JANUSDIR + "garden/ghouse/gh2", "east",0);
  add_exit(JANUSDIR + "garden/ghouse/gh3", "north",0);
  add_exit(JANUSDIR + "garden/ghouse/gh4", "south",0);
  add_prop(OBJ_I_SEARCH_TIME,15);
  add_prop(OBJ_S_SEARCH_FUN,"do_search");
  add_item(({"walls","hothouse","glass"}),BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"plants","flowers","claypots","pots"}),
            BS("There is a plethora of strange plants in the pots. " +
               "All of the plants seems to be in very good shape. \n"));
  add_item(({"walls","hothouse","glass","wall"}),
     BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"bench","benches"}),BS("The benches are made out of "+
       "wood. Most of the benches are covered by pots of all kinds. "+
       "\n"));
add_item(({"bush","bushes"}),BS("These neatly trimmed bushes looks like "+
           "midget trees. The shapes are right but they are only "+
           "about 1 foot high. \n"));
  door = clone_object(JANUSDIR  + "garden/ghouse_door2");
  door -> move(this_object());
}

do_pick(string tool)
{
  object warning;
  object diploma;
  object ball;
  object ob;
  int test;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  if (diploma ){
      write(BS("There are no plants that are suitable for taking.\n"));
      return 1;
    }
  if (warning){
    write(BS("When you try to take one of the plants, a hand appears and "+
     "punches you in the face, VERY HARD ... As if by magic a Ball and "+
     "Chain locks itself around your foot.\n"));
    TP->reduce_hit_point(10);
    clone_object(JANUSDIR + "garden/balls.c")->move(TP);
    say("As "+QCNAME(TP)+" tries to take a plant, a hand materializes \n"+
	"out of nowhere and punches "+QCNAME(TP)+" right in the face. \n"+
	"As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+ 
	"foot.\n");
    TP -> do_die();
    return 1;
  }
  write( "When you try to take one of the plants, a hand appears and \n"+
	"slaps your fingers, OUCH. As if by magic something appears in\n"+
	"your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP);
  say(BS("As "+QCNAME(TP)+" tries to take a plant, a hand \n"+
	 "materializes out of nowhere and slaps "+QCNAME(TP)+"'s \n"+
	 "hand.\n"));
  TP -> do_die();
  return 1;
} 
do_search()
{
  object ob;
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
    seteuid(getuid(this_object()));
    return BS("You find nothing that you can take here.\n");
  }
   return BS("You find nothing of value among the plants.\n");
}
