/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house3_tree.c
 *
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

inherit STDROOM;
#include <stdproperties.h>
int jump_roof(string str);
int climb_down(string str);

public void
create_room()
{
    ::create_room();
    set_short("treetop");
    set_long("You cling on the upper branches of the " +
       "oak tree. The roof of the house is just out of reach " +
       "before you.\n");
     
    add_item(({"branch","branches"}),"The branches are thinner " +
       "here than they were below.\n");
    add_item(("roof"),"The roof of the house is just before you. " +
       "Perhaps, you might be able to jump for it.\n");
   
    add_cmd_item("roof","jump",jump_roof);
    add_cmd_item("down","climb",climb_down);

    reset_room();
}


int
jump_roof(string str)
{
   int HP;
   HP = TP->query_hp();

   if (TP->query_skill(SS_ACROBAT) > 19 )      
      {
          write("You manage to jump across to the roof of the house.\n");
          TP->move_living("jumps to the roof of the house", 
          CALATHIN_DIR + "houses/house3_roof.c",1,0);
       return 1;
      }

      else 
         write("You jump attempting to reach the roof before you.\n OUCH!!\n\n " +
               "Unfortunately you miscalculated the jump and fall " +
               "painfully to the ground below!\n");

         TP->heal_hp( - 100 + random(50));
           if(TP->query_hp() <= 0)
              TP->do_die(TO);

         TP->move_living("jumps toward the roof but misses it by a few inches " +
         "falling to the ground below",
         CALATHIN_DIR + "houses/house3.c",1,0);
      return 1;
}
       
int
climb_down(string str)
{
   write("You manage to slowly make your way down the tree.\n");
   TP->move_living("climbing down the tree",
   CALATHIN_DIR + "houses/house3_tree.c",1,0);
  return 1;
}
   