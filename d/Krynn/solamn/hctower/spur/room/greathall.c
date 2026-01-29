
// greathall.c
// grace aug 1994

// THIS IS THE FILE THAT CATS THE /TREE/* FILES FOR THE TPAESTRIES
#include "../local.h"

inherit SPURRM;

object guard1, guard2;

reset_spur_room()
{
   if (!guard1)
      (guard1 = clone_object(PATROL))->move_living("arrives",this_object());
   if (!guard2)
      (guard2 = clone_object(GDOG))->move_living("arrives",this_object());
   guard2->set_leader(guard1);
   guard1->team_join(guard2);
}    

/*prototype*/
void load_board();
create_spur_room()
{
   
   SHORT("Great Hall");
   LONG("This is the Great Hall of Knights' Spur.\nA multi-purpose "+
      "room, it is most commonly used for meetings of the Council "+
      "of Knights.  A table sits in the center of south wall, and "+
      "numerous benches are stacked against the north and west "+
      "ones.  Broad beams support a high ceiling from which numerous "+
      "chandeliers suspend.  Tapestries cover every available "+
      "vertical surface, their gold threads catching the light "+
      "from hundreds of candles.\n");
   
   LIGHT;
   
    seteuid(getuid(TO));
    load_board();
   clone_object(SOBJ + "l2d1a")->move(TO); 
   AE(ROOM + "passage12", "west", 0);
   
   AI(({"candles","candle","chandelier","chandeliers"}), 
      "Candles burn brightly in their chandeliers.\n");
   AI("sconces", "Stone brackets made for holding torches.\n");
   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI("table", "It is big enough to seat two dozen people.\n"); 
   AI(({"bench","benches"}), 
      "They are made of a sturdy dark wood.\n");  
   ACI(({"bench","benches"}), ({"sit","sit on","unstack"}),
      "Unless there has been a meeting called there is no "+
      "reason to sit down.\n");
   /*AI(({"tapestry","tapestries"}),
      "There are tapestries hanging on every wall, each one\n"+
      "an elaborate tree of names worked in gold threads. To\n"+
      "learn more about the tapestries, try <read tapestry>.\n");*/
   AI(({"threads", "gold threads"}), "The threads have been "+
      "used to sew words into the tapestries.\n");        
   AI(({"beam","beams", "ceiling"}), "The beams are dark and " +
      "heavy. The ceiling is high and slightly soot-stained.\n");
   
   AI(({"arch", "arches", "archway"}), "The arches are very narrow and " +
      "run from the high ceiling down to a small, waist-high wall in " +
      "the north.\n");
   ACI(({"arch", "arches", "archway"}), "enter", "It is too narrow "+
      "for you to fit into.\n");
   AI(({"walls", "wall"}), "A series of narrow arches on a waist-high " +
      "stone wall forms the wall to the north. The south wall is covered " +
      "in tapestries. The east and west walls are plain stone interrupted " +
      "with doorways.\n");
   AI("north wall", "A series of narrow arches on a waist-high " +
      "stone wall forms the wall to the north.\n");
   AI("south wall", "The south wall is covered in tapestries.\n");
   AI(({"east wall", "west wall"}), "The east and west walls are plain stone " +
      "interrupted with doorways.\n");

   reset_spur_room();
}

/* This loads the conclave bulletin board */
void
load_board()
{
    clone_object(SOBJ + "sponsor_tree")->move(TO);
    clone_object(SOBJ + "conclave_board")->move(TO);
}

do_tingle()
{
   if (TP->query_alignment() < ALIGN_WARNING)
      {
      write("As you pass through the archway, the skin on your face "+
         "feels like it has been pricked with hundreds of pins.\n");
      TP->add_panic(10); 
      return 0;
   }              
   else
      {
      write("As you pass through the archway, a warm breeze blows " +
         "over you, caressing your skin.\n");
      TP->add_fatigue(4);
   }
   return 0;
}



void
init()
{
   //ADA("read");
   ::init();
}


int
read(string str)
{
   NF("Read what?\n");
   if (!str)
      return 0;
   
   switch(str)
   {
      case "aaron":
      case "bebop":
      case "blake":
      case "cindy":
      case "dordon":      
      case "faline":
      case "grumph":
      case "gwen":
      case "lunie":
      case "pangu":
      case "rae":
      case "trojan":
      case "tapestry":
      case "tree":
      
      cat(TREE + str);
      break;
      default:
      NF("You can't read that.\n");
      return 0;
   }
   
   return 1;         
}
