inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <chapel.h>
#include "/d/Emerald/sys/paths.h"

/* Prototypes */

int pick_flower(string arg);

int flowers_left = 20;


void
create_room()
{
   set_short("Chapel garden");
   
   set_long("   You stand in a beautiful garden outside "+
      "of the gazebo where private weddings are performed. The stone path "+
      "you are standing on leads southeast back the chapel garden. This garden " +
      "seems to be cut right out of the forest with tall trees towering "+
      "majestically over the garden. There is a small pond here, similar "+
      "to the one in the lower part of the garden. The flowers here are as "+
      "breathtaking as the ones in the lower garden. "+
      "A large white gazebo is here, with greenery growing all around its base "+
      "and up the lattice on its sides.\n\n");
   
   
   add_item(({"flower", "flowers"}), "The flowers are absolutely " +
      "breathtaking! There are hundereds of varieties all swaying " +
      "softly in the breeze which surrounds the garden. The blossoms of the  " +
      "flowers seem to beckon to you. Perhaps you could pick one?\n");
   add_item(({"tree", "trees"}), "The trees stand magestically as a  "+
      "border around the entire garden. Their dark green foliage blends " +
      "in harmony with the vibrant colours of the flowers.\n");
   add_item(({"path", "stone", "stones", "ground"}), "The path "+
      "is made of smooth polished stones. The path winds its " +
      "way around the pond and up to the gazebo, " +
      "before returning back to the lower part of the garden.\n");
   add_item(({"pond", "pool"}), "The pond is crystal clear "+
      "water with sunlight shimmering off of the surface. You " +
      "notice small bubbles on the surface of the water and when " +
      "you take a closer look you can see a school of brightly coloured fish  " +
      "swimming and playing close to the surface of the water.\n");
   add_item(({"lattice", "slats"}), "The white wooden slats form a  " +
      "criss cross pattern as they go up the sides of the gazebo. You see long "+
      "green vines winding their way up the lattice-work.\n");
   add_item("gazebo","Before you is a large white gazebo where outdoor weddings are held. Around the base of it a multitude of greenery grows.\n");
   add_item("creek","This creek is really nothing more that a trickle of water connecting the ponds in the two gardens.\n");
   add_item("bridge","This small bridge is crafted from stones and crosses the creek.\n");
   add_item("garden","You look around this beautiful garden and can't "+
      "help but think how appropriate it's beauty is "+
      "for being outside of a wedding chapel.\n");
   add_item("greenery","Taking a closer look you see that the greenery is a variety of sizes and shaped leaves.\n");
   
   add_exit("gazebo", "enter", "@@check_thrown_out");
   add_exit("outside", "southeast", "@@bridge_msg@@");
}

int
check_thrown_out()
{
   if (TP->query_prop(THROWN_OUT) > 2) {
      write("You start to enter the gazebo, but are stopped by an usher. " +
         "It seems you aren't wanted there.\n");
      say(QCTNAME(TP) + " tries to enter the gazebo, " +
         "but cannot get past the usher.\n");
      return 1;
   }
   write("As you enter the gazebo, the usher smiles and lets you pass.\n");
   return 0;
}

void
init()
{
   ::init();
   add_action(pick_flower,"pluck");
   add_action(pick_flower,"pick");
}

reset_room()
{
   flowers_left = 20;
}

int
pick_flower(string arg)
{
   object flower;
   
   if (!arg) return 0;
   
   if ( (arg!="flower") && (arg!="flowers") )
      {
      notify_fail("Pick What?\n");
      return 0;
   }
   if (!flowers_left)
      {
      notify_fail("It seems that this area has been picked clean of "+
            "flowers. Maybe you should let some grow back?\n");
      return 0;
   }
   
   flower = clone_object(CHAPEL_DIR + "obj/flower" +(random(3)+1));
   flower->move(TP,1);
   write("You pluck a "+flower->short()+" from the ground.\n");
   say(QCTNAME(TP)+" plucks a "+flower->short()+" from the ground.\n");
   return 1;
}

int
bridge_msg()
{
   write("You step over the bridge to the chapel ...\n\n");
   say(QCTNAME(this_player())+ " steps over the bridge to the chapel.\n");
   return 0;
}

