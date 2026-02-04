/* garden2.c */
/* janus 920822 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int oflowers;

reset_room()
{
  object gardener;
  oflowers=3;
  if(present("gardener"))return;
  gardener=clone_object(JANUSDIR + "garden/gardener");
  gardener->move(this_object());
}
create_room()
{
  
  set_short("Garden");
  set_long(break_string("Along both sides of the gravel path are row after" +
	" row of beautiful flowers. To the south you see the hedge and to"+ 
	" the west is a grove of trees. " +
	"Standing at the edge of the "+
	"gravel path is a small sign on a pole.\n",70));
  add_exit(JANUSDIR + "garden/garden1", "east",0);
  add_exit(JANUSDIR + "garden/garden4", "west",0);
  add_exit(JANUSDIR + "garden/garden21", "north",0);
  add_item(({"flower","flowers"}),break_string("The flowers have all the " +
       "colours that you can imagine. In all this plethora of colors one "+
       "flower is markedly different. It is completely black, it even " +
       "appears to suck the light from the air.\n",70));
  add_cmd_item(({"sign","small sign"}),({"read","exa"}),
         ({"@@do_sign","@@do_sign"}));
  add_cmd_item(({"black flower","flower","flowers"}),
        ({"smell", "pick"}),({"The flowers "+
				      "smells wonderfully.\n", "@@pick"}));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
	   "position after being moved. Awesome magic HUH?\n",70));
  reset_room();
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
  int test;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  test = TP -> query_prop("picked_black");
  if (test == 1){
    write(BS("You have picked your share of black flowers today. By "+
	     "picking more you will upset the delicate balance maintained "+
	     "in this garden.\n"));
    return 1;
  }
  if (diploma ){     
    write(BS("With your newfound knowledge of gardening you realise"+ 
	     " that the only flower suitable for picking is the" +
	     " black flower. With great care you take the black "+
	     "flower and put it in your pocket.\n"));
    clone_object(JANUSDIR + "garden/bflow")->move(TP, 1);
    TP -> add_prop("picked_black",1);
    say(QCNAME(TP)+" gently picks a Black flower.\n");
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
