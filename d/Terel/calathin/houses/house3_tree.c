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

object woodenball;
int climb_trunk(string str);
int climb_down(string str);
int ball;

#include <stdproperties.h>


public void
create_room()
{
    ::create_room();
    set_short("branch");
    set_long("You straddle a lower branch that extends outward " +
       "from the thick trunk of an old oak tree. The " +
       "tree swing is tied to the branch and hangs halfway " +
       "to the ground.\n");
     
    add_item(({"swing","tree swing"}),"A tree swing " +
       "hangs from the same branch that you sit upon.\n");
    add_item(({"oak tree","tree","trees"}),"Two old oak " +
       "trees grow on either side of the house. An old " +
       "swing can be seen hanging from the oak tree " +
       "to the east.\n");
    add_item(({"branch","branches"})," There are several " +
       "branches extending from the tree in different " +
       "directions. Most seem unreachable, except for the " +
       "one you sit on now.\n");
    add_item(({"treetrunk","tree trunk","trunk"}),
       "Gnarled with age, several old knotholes " +
       "are in various parts of the old tree.\n");
    add_item(({"knotholes","hole","knot hole"}),
       "Small and large, the knotholes are placed about the old " +
       "tree.\n");

    add_prop(OBJ_S_SEARCH_FUN, "search_trunk");
    add_prop(OBJ_I_SEARCH_TIME, 1);

    add_cmd_item("down","climb",climb_down);
    add_cmd_item("trunk","climb",climb_trunk);

    reset_room();
}


int
climb_trunk(string str)
{
   
      if (TP->query_skill(SS_CLIMB) > 29)      /*high climb skill required here*/
      {
         write("You manage to climb further up the tree trunk.\n");
         TP->move_living("climbs up the tree", 
           CALATHIN_DIR + "houses/house3_e_tree.c",1,0);
      return 1;
      } 
      else
         write("You slip and fall to the ground.\n");
         TP->move_living("slips and falls to the ground",
           CALATHIN_DIR + "houses/house3.c",1,0);
      return 1;
}       


int
climb_down(string str)
{
   write("You make your way down to the ground.\n");
   TP->move_living("climbs down from the tree",
      CALATHIN_DIR + "houses/house3.c",1,0);
  return 1;
}


void
reset_room()
{
    ::reset_room();
    ball = 1;
    return;
}


string 
search_trunk(object me, string arg)
{
    if(arg != "trunk")
    {
        return "";
    }
       if(ball == 1)
       {
          woodenball = clone_object(CALATHIN_DIR + "houses/obj/ball.c");
          woodenball->move(TP);
          ball = 0;
          return"You've found a small wooden ball " +
          "hidden in a knothole in the trunk.\n";      
                 
       }   
          return "Your search reveals nothing special.\n";
}
