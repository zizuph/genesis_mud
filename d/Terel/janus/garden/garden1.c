/* garden1.c */
/* janus 920817 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

create_room()
{
  set_short("Crossroad");
  set_long(break_string("You are in a crossroad in a exquisite garden" +
	". The air is warm, refreshing, and filled with fragrances from "+
	"the flowers growing in neat rows along the gravel path. To the "+
	"south you can see a huge hedge and a small opening in it. The "+ 
	"path also continues to the east, west and north. At the edge of " +
	"the gravel path is a small sign on a pole.\n",70));
  add_exit(JANUSDIR + "garden/garden11", "north",0);
  add_exit(JANUSDIR + "garden/ggate", "south",0);
  add_exit(JANUSDIR + "garden/garden3", "east",0);
  add_exit(JANUSDIR + "garden/garden2", "west",0);
  add_item(({"flower","flowers"}),
	   break_string(
	"The flowers has all the " + 
	"colours that you can imagine. In all this plethora of colors one "+
	"flower is markedly different. It seems to shine with an unearthly"+
	" glow. It is of the eight color octarine."+
	"\n",70));
  add_cmd_item(({"sign","small sign"}),({"read","exa"}),
         ({"@@do_sign","@@do_sign"}));
  add_cmd_item(({"octarine flower","flower","flowers"}),
	       ({"smell", "pick"}),({"The flowers " +
		       "smells wonderfully.\n", "@@pick"}));
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
  object ob2;
  object octflow;
  int test;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  test = TP -> query_prop("picked_oct");
  if (test == 1){
    write(BS("You have picked your share of octarine flowers today. By "+
	     "picking more you will upset the delicate balance maintained "+
	     "in this garden.\n"));
    return 1;
  }
  if (diploma ){     
    write(BS("With your newfound knowledge of gardening you realise"+ 
	     " that the only flower suitable for picking is the" +
	     " octarine flower. With great care you take the octarine "+
	     "flower and put it in your pocket.\n"));
    octflow = clone_object(JANUSDIR + "garden/oflow");
    octflow -> add_prop("_oflower_finder", TP->query_name());
    octflow -> move(TP);
    TP-> add_prop("picked_oct",1);
    say(QCNAME(TP)+" gently picks a Octarine flower.\n");
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
    TP -> do_die();
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
  TP -> do_die();
  return 1;
} 

