/* garden21.c */
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
  set_short("field of herbs");
  set_long(BS("This secluded part of the garden seems to serve as a " +
     "place where the gardener, grows herbs and spices of different kinds. " +
     "In the northwest corner is a small toolshed, the way to the north is "+
     "blocked by a large building. \n"));
  add_exit(JANUSDIR + "garden/garden2", "south",0);
  add_exit(JANUSDIR + "garden/garden211","northwest",0);
  add_item(({"herb","spice","spices","herbs"}),BS("There are herbs "+
     "and spices of "+
    "all kinds here. \n"));
  add_item(({"building","glass building","north building"}),BS("The house "+
     "is about 6 meters high and completely covered with glass. "+
     "It's not possible to see anything since the air inside the building is "+
     "very humid and therefore water has "+
     "condensed on the window and is blocking the view. \n"));
  add_item(({"shed","toolshed","tool shed"}),BS("It is a very small toolshed "+
     "made of wood. There is no door so you can enter the shed by going "+
     "northwest.\n"));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
      "position after being moved. Awesome magic HUH? \n",70));
}
do_pick(string herb)
{
  object warning;
  object diploma;
   object ball, oert;
  object ob,ob2,ob3,ob4;
   int test, stest;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  test = TP -> query_prop("picked_herb");
   stest = TP -> query_skill(SS_HERBALISM);
   if ( stest < 10 ) {
      write(BS("You can't recognize any of the herbs in the field. "+
        "You see something that looks like onions but "+
       "the bulbs are rose-tinged, there is also some stalked ovate "+
       "leaves and some small bushes with green leaves, and a branching "+
       "herb about three feet high with purplish flowers. "+
        "Maybe if you learned some more herbalism you'd recogize some "+
        "of the herbs. "+
               "The Master Gardener would probably be very glad to "+
               "share his knowledge. \n"));
      return 1;
    }
  if (test >3 ){
    write(BS("You have picked your share of herbs today. By "+
	     "picking more you will upset the delicate balance maintained "+
	     "in this garden.\n"));
    return 1;
  }
  if (diploma ){
    if (herb == "catnip" || herb == "purple flowers" || herb == "flowers" ){   
      write(BS("With great care you take a few purplish flowers "+
	       "and put them in your pocket.\n"));
      ob4 = clone_object("/d/Gondor/common/herbs/catnip");
      ob4 -> move(TP);
      TP-> add_prop("picked_herb",test + 1);
      say(QCNAME(TP)+" gently picks a herb.\n");
      return 1;
    }
    if (herb == "garlic" || herb == "bulb" || herb == "rose-tinged bulb" ){
      write(BS("With great care you take a rose-tinged bulb "+
	       "and put it in your pocket.\n"));
      oert = clone_object("/d/Gondor/common/herbs/garlic");
      oert -> move(TP);
      TP-> add_prop("picked_herb",test + 1);
      say(QCNAME(TP)+" gently picks a herb.\n");
      return 1;
    }
    if(herb == "oregano" || herb == "ovate leaves" || herb == "leaves" ){
      write(BS("With great care you take a few ovate leaves "+
	       "and put them in your pocket.\n"));
      clone_object("/d/Gondor/common/herbs/oregano")->move(TP, 1);
      TP-> add_prop("picked_herb",test + 1);
      say(QCNAME(TP)+" gently picks a herb.\n");
      return 1;
    }
    if (herb == "parsley" || herb == "green leaf" || herb == "leaf"){
      write(BS("With great care you take a few green leaves "+
	       "and put them in your pocket.\n"));
      clone_object("/d/Shire/common/herbs/parsley") -> move(TP);
      TP -> add_prop("picked_herb",test + 1);
      say(QCNAME(TP)+" gently picks a herb.\n");
      return 1;
    }
    if (stest > 10 ) {
      write(BS("You see that you can pick either a clove of garlic, "+
	       "catnip, oregano, or parsley.\n"));
      return 1;
    }
  }
  if (warning){
    write(BS("When you try to take one of the herbs, a hand appears and "+
	     "punches you in the face, VERY HARD...As if by magic a Ball and "+
	     "Chain locks itself around your foot.\n"));
    TP->reduce_hit_point(10);
    clone_object(JANUSDIR + "garden/balls.c")->move(TP, 1);
    say("As "+QCNAME(TP)+" tries to pick a herb, a hand materializes \n"+
        "out of nowhere and punches "+QCNAME(TP)+" right in the face. \n"+
        "As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+ 
        "foot.\n");
    TP -> do_die();
    return 1;
  }
  write( "When you try to take one of the herbs, a hand appears and \n"+
	"slaps your fingers, OUCH. As if by magic something appears in\n"+
	"your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP, 1);
  say(BS("As "+QCNAME(TP)+" tries to pick a herb, a hand \n"+
	 "materializes out of nowhere and slaps "+QCNAME(TP)+"'s \n"+
	 "hand.\n"));
  TP -> do_die();
  return 1;
} 

