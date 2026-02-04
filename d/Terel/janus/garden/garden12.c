/* garden12.c */
/* janus 920826 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

create_room()
{
  set_short("Garden");
  set_long(BS("This is a small crossroad in the garden, to the north "+
              "you see a small house at the top of a large stair. To "+
              "the west and east you see buildings made completely "+
              "out of clear glass. A few flowers and some bushes line "+
              "the edge of the road. \n"));
  add_exit(JANUSDIR + "garden/garden11", "south",0);
  add_exit(JANUSDIR + "garden/garden22", "west",0);
  add_exit(JANUSDIR + "garden/garden32", "east",0);
  add_exit(JANUSDIR + "garden/garden13", "north",0);
  add_item(({"purple flower","flower","flowers"}),break_string("The flowers has all the "+
		       "colours that you can imagine, but glowing almost "+
                       "with an inner light is a purple flower. \n",70));
  add_item(({"fruit","bush","bushes"}),break_string("The bushes are quite "+
                       "small but some of them have some red fruits. \n",70));
  add_cmd_item(({"flower","flowers", "purple flower"})
          ,({"smell", "pick"}),({"The flowers " +
				      "smells wonderfully.\n", "@@pick"}));
  add_cmd_item(({"fruit","red fruit"}),({"smell", "pick"}),({"The fruit " +
				      "doesn't smell.\n", "@@pick2"}));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
	   "position after being moved. Awesome magic HUH? \n",70));
}
pick()
{
  object warning;
  object diploma;
  object ball;
  object ob;
  object ob2;
  int test;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
    test = TP -> query_prop("picked_purple");
  if (test == 1){
    write(BS("You have picked your share of purple flowers for today. By "+
	     "picking more you will upset the delicate balance maintained "+
	     "in this garden.\n"));
    return 1;
  }
  if (diploma ){     
    write(BS("With your newfound knowledge of gardening you realise"+ 
	     " that the only flower suitable for picking is the " +
	     "purple flower. With great care you take the purple "+
	     "flower and put it in your pocket.\n"));
    clone_object(JANUSDIR + "garden/pflow")->move(TP, 1);
    TP-> add_prop("picked_purple",1);
    say(QCNAME(TP)+" gently picks a purple flower.\n");
    return 1;
  }
  if (warning){
    write(BS("When you try to take one of the flowers, a hand appears and "+
     "punches you in the face, VERY HARD ... As if by magic a Ball and "+
     "Chain locks itself around your foot.\n"));
    TP->reduce_hit_point(10);
    clone_object(JANUSDIR + "garden/balls.c")->move(TP, 1);
    say("As "+QCNAME(TP)+" tries to pick a flower, a hand materializes \n"+
        "out of nowhere and punches "+QCNAME(TP)+" right in the face. \n"+
        "As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+ 
        "foot.\n");
    TP->do_die();
    return 1;
  }
  write( "When you try to take one of the flowers, a hand appears and \n"+
	"slaps your fingers, OUCH. As if by magic something appears in\n"+
	"your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP, 1);
  say(BS("As "+QCNAME(TP)+" tries to pick a flower, a hand \n"+
	 "materializes out of nowhere and slaps "+QCNAME(TP)+"'s \n"+
	 "hand.\n"));
  TP->do_die();
  return 1;
} 
pick2()
{
  object warning;
  object diploma;
  object ball;
  object ob;
  object ob2;
  int test;
  test =0;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
    test = TP -> query_prop("picked_rfruit");
  if (test == 2){
    write(BS("You have picked your share of red fruits flowers for today. By "+
	     "picking more you will upset the delicate balance maintained "+
	     "in this garden.\n"));
    return 1;
  }
  if (diploma ){     
    write(BS("With your newfound knowledge of gardening you realise"+ 
	     " that the only fruit suitable for picking is the " +
	     "red purple fruit. With great care you take the red "+
	     "fruit and put it in your pocket.\n"));
    clone_object(JANUSDIR + "garden/rfruit")->move(TP, 1);
    TP-> add_prop("picked_rfruit",test + 1);
    say(QCNAME(TP)+" gently picks a red fruit.\n");
    return 1;
  }
  if (warning){
    write(BS("When you try to take one of the fruits, a hand appears and "+
     "punches you in the face, VERY HARD ... As if by magic a Ball and "+
     "Chain locks itself around your foot.\n"));
    TP->reduce_hit_point(10);
    clone_object(JANUSDIR + "garden/balls.c")->move(TP, 1);
    say("As "+QCNAME(TP)+" tries to pick a fruit, a hand materializes \n"+
        "out of nowhere and punches "+QCNAME(TP)+" right in the face. \n"+
        "As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+ 
        "foot.\n");
    TP->do_die();
    return 1;
  }
  write( "When you try to take one of the flowers, a hand appears and \n"+
	"slaps your fingers, OUCH. As if by magic something appears in\n"+
	"your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP, 1);
  say(BS("As "+QCNAME(TP)+" tries to pick a fruit, a hand \n"+
	 "materializes out of nowhere and slaps "+QCNAME(TP)+"'s \n"+
	 "hand.\n"));
  TP->do_die();
  return 1;
} 
