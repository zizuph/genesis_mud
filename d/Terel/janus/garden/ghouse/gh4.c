/* greenhouse4.c */
/* janus 930408 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int vermin4;
init()
{
  ::init();
  vermin4=0;
}

create_room()
{
  set_short("hothouse");
  set_long(BS("You are inside a large hothouse. The air is warm " +
              "and humid. Standing in neat rows are benches packed "+
              "with claypots. Most of the pots are filled with flowers"+
              ", small bushes, and strange plants. \n"));
  add_exit(JANUSDIR + "garden/ghouse/gh1", "north",0);
  add_exit(JANUSDIR + "garden/ghouse/gh6", "east",0);
  add_prop(OBJ_I_SEARCH_TIME,15);
  add_prop(OBJ_S_SEARCH_FUN,"do_search");
  add_item(({"walls","hothouse","glass"}),BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
   add_item(({"violet flower","flower"}),BS("A beatiful violet flower, there are plenty of them "+
    "so no one would mind if you took one.\n"));
  add_item(({"bush","bushes","small bushes"}),BS("Some of the bushes "+
     "appears to be damaged by some vermin, leaves are partly eaten "+
     "and the plants seems to be in a bad condition. You can't "+
     "see any bugs, but maybe if you searched you'd find a bug or two. \n"));
add_cmd_item(({"violet flower","flower","flowers"}),({"smell", "pick"}),({"The flowers " +
                              "smells wonderfully.\n", "@@pick"}));
  add_item(({"plants","flowers","claypots","pots"}),
            BS("There are a plethora of strange plants in the pots. " +
               "Some of the plants seems to be damaged by some vermin. "+
      "But there is a pot with violet flowers that looks quite healthy. "+
               "Maybe if you searched the plants you could find the "+
               "bugs that have caused all this damage.\n"));
 add_item(({"bench","benches"}),BS("Ordinary wooden benches covered "+
   "with claypots of all sizes and shapes.\n"));
  add_item(({"walls","wall","hothouse","glass","glass wall"}),
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
    if(vermin4 < 3){
    seteuid(getuid(this_object()));
    vermin=clone_object(JANUSDIR + "monsters/vermin");
    vermin->move(TO);
    vermin4++;
    return BS("Behind a pot you see a bug. \n");
  }
    return BS("You find nothing here. \n");
  }
   return BS("You find nothing here.\n");
}
pick()
{
  object warning;
  object diploma;
  object ball;
  object ob;
  int test;
  int test2;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  test = TP -> query_prop("picked_violet");
  if (test == 1){
   write(BS("You have picked your share of violet flowers fruits for now. The "+
             "violet flowers has a hard time already with the vermin, so "+
             "by picking more you would upset the delicate "+
             "balance maintained in this green house.\n"));
    return 1;
  }
  if (diploma ){
    write( BS("With your newfound knowledge of gardening you realise"+
      " that there are plenty of violet flowers, so you take one.\n"));
    say(QCTNAME(TP)+" gently picks a violet flower. \n");
    clone_object(JANUSDIR + "garden/vflower.c")->move(TP);
    TP-> add_prop("picked_violet",1);
   return 1;
  }

  if (warning){
    write(BS("When you try to take one of the flowers, a hand appears and "+
     "punches you in the face, VERY HARD ... As if by magic a Ball and "+
     "Chain locks itself around your foot.\n"));
    TP->reduce_hit_point(10);
    TP -> do_die();
    clone_object(JANUSDIR + "garden/balls.c")->move(TP);
    say("As "+QCNAME(TP)+" tries to pick a flower, a hand materializes \n"+
        "out of nowhere and punches "+QCNAME(TP)+" right in the face.\n"+
        " As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+
        " foot.\n");
    return 1;
  }
  write( "When you try to take one of the flowers, a hand appears and \n"+
        "slaps your fingers, OUCH. As if by magic something appears in\n"+
        "your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP);
  say("As "+QCNAME(TP)+" tries to pick a flower, a hand \n"+
      "materializes out of nowhere and slaps "+QCNAME(TP)+"'s \n"+
      "hand.\n");
  TP -> do_die();
  return 1;
}

