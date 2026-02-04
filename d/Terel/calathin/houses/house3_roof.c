/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house3_roof.c
 *
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 * 01/17/01 -- Tomas: 
 *  Egad! did i code this?? Revamped room using prop instead of a variable. Added
 *  additional checks, etc..
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

inherit STDROOM;
#include <stdproperties.h>
int jump_tree(string str);
int crawl_roof(string str);
string exa_westtree();
string exa_easttree();

public void
create_room()
{
    ::create_room();
    set_short("roof");
    set_long("You balance yourself on the eves of the thatched roof. " +
       "The roof looks in even worse shape " +
       "up close. From this angle you notice a large shadow " +
       "in the oak tree to the west.\n");
   
   add_item(({"oak trees","oaks"}),"Two large oak trees " +
      "grown on either side of the house. You notice a large " +
      "shadow well hidden in the oak tree to the west.\n");
   add_item(({"oak tree","tree"}),"Which one, the west tree " +
      "or east tree?\n");
   add_item(({"west tree", "western tree","west oak tree"}), "@@exa_westtree");
   add_item(({"east tree", "eastern tree","east oak tree"}), "@@exa_easttree");
   add_item(({"thatch roof","roof"}),"The roof is of thatch " +
       "construction. It looks in big need of repair. Careful " +
       "you dont step in the wrong place.\n");
   add_item(("shadow"),"Upon examination of the shadow it would " +
      "appear to be some sort of structure. Well hidden in the tree.\n");
   add_item(("eves"),"Supports for the thatch roof that extend " +
      "outward.\n");
   add_item(("structure"),"The structure resembles a small house " +
      "hidden in the large oak tree on the west side of the house.\n");

   reset_room();

}

void init()
{
    ::init();
       add_action(crawl_roof,"crawl");
       add_action(jump_tree,"jump");
}


string
exa_westtree()
{
   if (TP->query_prop("_I_terel_crawled"))
   {
      return "From closer examination, you notice that you might " +
             "be able to jump to the western tree from here.\n";
   }  
      return "You notice a large shadow well hidden in the tree. " +
             "Perhaps, its worth crawling over to investigate.\n";
}

string
exa_easttree()
{
   if (TP->query_prop("_I_terel_crawled"))
   {
      return "The eastern tree stands behind you alongside the southern " +
            "end of the roof.\n";  
   }  

     return "The large oak tree stands before you. Its branches, " +
            "extend outwards towards the  edge of the roof. You might " +
            "be able to jump to the east tree from here.\n";
}

int
crawl_roof(string str)
{
   if ((str != "closer" && str != "across roof" && str != "west tree"  &&
        str != "south" && str != "back" && str != "east tree" && str != "north"))
   {
      write("Crawl where?\n");
      return 1;
   }
      if ((str == "closer" || str == "across roof" || str == "west tree" || 
           str == "north"))
      {
         write("You crawl your way across the frail roof edging closer " +
               "to the west oak tree.\n");
         say(QCTNAME(TP) + " crawls across the edge of the house to " +
               "the west tree.\n");
         TP->add_prop("_I_terel_crawled",1);
         return 1;
      }

      if ((str == "south" || str == "back" || str == "east tree" && 
           TP->query_prop("_I_terel_crawled")))
      {
          write("You manage to turn around and crawl back towards " +
                "the south end of the house.\n");
          say(QCTNAME(TP) + " turns around and crawls back towards " +
                            "the south end of the house.\n");
          TP->remove_prop("_I_terel_crawled");
       return 1;
      }
}



int
jump_tree(string str)
{
   if ((str !="west tree" && str !="east tree" && str != "down"))
   {
      write("Jump where, the west tree or the east tree or down?\n");
      return 1;
   }
      if (( str == "down" ))
      {
         write("Staring at the ground below, you decide its best not to " +
               "break your leg needlessly..\n");
         return 1;
      }

      if ((str == "west tree" && TP->query_prop("_I_terel_crawled")))
      {
         write("You manage to jump to the nearest branch " +
               "on the west tree.\n");
         TP->move_living("jumps grabbing at the nearest branch " +
                         "of the west oak tree", 
             CALATHIN_DIR + "houses/house3_w_tree.c",1,0);
         TP->remove_prop("_I_terel_crawled");
         write_file(TEREL_DIR + "log/jumped_house3_w_tree",
         TP->query_name()+" " + ctime(time()) + "\n");

         return 1;
      }

      if (( str == "west tree" && !TP->query_prop("_I_terel_crawled") ))  
      {
         write("The west tree is to far away for you to jump. " +
               "You will have to get closer.\n");
         return 1;
      }

      if (( str == "east tree" && TP->query_prop("_I_terel_crawled") ))      
      {
         write("The east tree is to far away for you to jump. " +
               "You will have to get closer.\n");
         return 1;
      }

      if (( str == "east tree" && TP->query_skill(SS_ACROBAT) > 19 ))
      {
         write("You manage to jump to the closest branch on the eastern tree.\n");
         TP->move_living("jumps to one of the closest branches on the eastern tree", 
             CALATHIN_DIR + "houses/house3_e_tree.c",1,0);
         return 1;
      }
         write("You jump attempting to reach the tree branch before you.\n OUCH!!\n\n " +
               "Unfortunately you miscalculated the jump and fall " +
               "painfully to the ground below!\n");

         TP->heal_hp( - 100 + random(50));
           if(TP->query_hp() <= 0)
              TP->do_die(TO);

         TP->move_living("jumps toward the roof but misses it by a few inches " +
         "falling to the ground below", CALATHIN_DIR + "houses/house3.c",1,0);
         return 1;
  
}


