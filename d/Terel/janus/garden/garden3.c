/* garden3.c */
/* janus 920822 */
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
  set_long(break_string("Along both sides of the gravel path are row after" +
	" row of beautiful bushes. The bushes range from green to silvery."+
	" Most of the bushes have flowers and some have fruits. There is" +
	" even a burning bush. The path continues to the east where a "+
	"complex set of hedges can be seen. On each side of the path is"+
	" a small sign. \n",70));
  add_exit(JANUSDIR + "garden/garden5", "east",0);
  add_exit(JANUSDIR + "garden/garden1", "west",0);
  add_cmd_item(({"sign","small sign"}),({"read","exa"}),
         ({"@@do_sign","@@do_sign"}));
  add_item(({"flower","flowers"}),break_string("The flowers have all the " +
			       "colours that you can imagine. \n",70));
  add_item(({"bush","bushes"}),break_string("Examining the bushes closer" +
    " you notice that they must be pruned by a master gardener. \n",70));
  add_item(({"burning bush"}),break_string("It's burning with a steady "+
				   "cool flame. \n",70));
  add_item(({"fruit","fruits"}),break_string("The fruits have all possible" +
			     " colors and shapes. \n",70));
  add_cmd_item(({"flower","flowers"}),({"smell", "pick"}),({"The flowers " +
			      "smells wonderfully.\n", "@@pick"}));
  add_cmd_item(({"fruit","fruits"}),({"smell","taste","pick"}),({
    break_string("The fruit doesn't smell at all. Maybe they taste"+
	" good ? \n",70), break_string("You must pick the fruit before" +
	" you can taste it.\n",70), "@@pick2"}));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	" at the gravel you see that each grain rolls back into its old " + 
	"position after being moved. Awesome magic HUH? \n",70));
}
do_sign()
{
   return ("You read: \n"+
"No littering or vandalism allowed. Plants should \n"+
"only be handled by a certified gardener, although \n"+
"careful removal of weeds and vermin is allowed. \n");
}
pick()
{
  object warning;
  object diploma;
  object ball;
  object ob;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  if (diploma){
    write( BS("With your newfound knowledge of gardening you realise"+
	      " that none of the flowers are suitable for picking.\n"));
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
pick2()
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
  test = TP -> query_prop("picked_tfruit");
  if (test == 2){
    write(BS("You have picked your share of turqoise fruits for today. By "+
	     "picking more you will upset the delicate balance maintained "+
	     "in this garden.\n"));
    return 1;
  }
  if (diploma ){     
    write( BS("With your newfound knowledge of gardening you realise"+
      " that there are plenty of turqoise fruits, so you take one.\n"));
   say(QCTNAME(TP)+" gently picks a turqoise fruit. \n");
    clone_object(JANUSDIR + "garden/tfruit.c")->move(TP);
    if (test == 1 ){
      TP-> add_prop("picked_tfruit",2);
    }else{
      TP-> add_prop("picked_tfruit",1);
    }
    return 1;
  }
  if (warning){
    write(BS("When you try to take one of the fruits, a hand appears and "+
     "punches you in the face, VERY HARD ... As if by magic a Ball and "+
     "Chain locks itself around your foot.\n"));
    clone_object(JANUSDIR + "garden/balls.c")->move(TP);
    say("As "+QCNAME(TP)+" tries to pick a fruit, a hand materializes \n"+
        "out of nowhere and punches "+QCNAME(TP)+" right in the face. \n"+
        "As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+ 
        "foot.\n");
    TP->reduce_hit_point(50);
    TP -> do_die(); 
    return 1;
  }
  write( "When you try to take one of the fruits, a hand appears and \n"+
	"slaps your fingers, OUCH. As if by magic something appears in\n"+
	"your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP);
  say(BS("As "+QCNAME(TP)+" tries to pick a fruit, a hand \n"+
	 "materializes out of nowhere and slaps "+QCNAME(TP)+"'s \n"+
	 "hand.\n"));
  TP -> do_die(); 
  return 1;
} 
