/* garden5.c */
/* janus 920822 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int gflowers;

reset_room()
{
  object gardener;
  gflowers=3;
}

create_room()
{

  set_short("Labyrinth entrance");
  set_long(break_string("The path ends at a large hedge. It's not the hedge"+
     " surrounding the garden, but a smaller one. In the hedge you see"+
     " a beautiful sculptured portal and a large sign across the "+
     "portal, blocking all entrance. Surrounding the portal "+
     "there is a lot of different flowers. \n",70));
  add_exit(JANUSDIR + "garden/garden3", "west",0);
  /*    add_exit(JANUSDIR + "garden/labyrinth1", "west",0); */
  add_cmd_item(({"sign","large sign"}),({"read","exa"}),
         ({"@@do_sign","@@do_sign"}));
  add_item(({"flower","flowers"}),BS("The flowers has all the " +
       "colours that you can imagine. In all this plethora of colors one "+
       "flower is markedly different. It is completely green. \n"));
  add_cmd_item(({"flower","green flower","flowers"}),({"smell","pick"}),
      ({"The flowers "+
				      "smells wonderfully.\n", "@@pick"}));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
	   "position after being moved. Awesome magic HUH? \n",70));
  add_item(({"hedge"}),break_string("A dense, almost three meter high hedge, "+
           "consisting of thorny bushes. \n",70));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
	   "position after being moved. Awesome magic HUH? \n",70));
  reset_room();
}
do_sign()
{
return ("On the sign you read is a scribbled text:\n"+
   "The labyrinth is closed for the moment. We are breeding \n"+
   "the carnivorous plants. Will open soon!!\n");
}
pick()
{
  object warning;
  object diploma;
  object ball;
  object ob;
  int test;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  test = TP -> query_prop("picked_green");
  if (test == 1){
    write(BS("You have picked your share of green flowers today. By "+
	     "picking more you will upset the delicate balance maintained "+
	     "in this garden.\n"));
    return 1;
  }
  if (diploma ){     
    write(BS("With your newfound knowledge of gardening you realise"+ 
	     " that the only flower suitable for picking is the" +
	     " green flower. With great care you take the green "+
	     "flower and put it in your pocket.\n"));
    clone_object(JANUSDIR + "garden/gflow")->move(TP, 1);
    TP -> add_prop("picked_green",1);
    say(QCNAME(TP)+" gently picks a Green flower.\n");
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
  return 1;
}
