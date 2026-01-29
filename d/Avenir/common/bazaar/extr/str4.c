// Bazaar Street4 (/d/Avenir/common/bazaar/extr/str4.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
//               Oct 1995, added the sneaking keybearer
//               to the Infidel hideout.
//         Lilith June 2022: added entracne to the ice cream parlor

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object sneaky;

void reset_room();

init()
{
   ::init();
   ADD("do_crunch","east");
   ADD("do_crunch","south");
}
void
create_room()
{
   AE(INTR + "ice_cream_parlor", "west", );
   AE(EXTR + "str5", "east", 0);
   AE(EXTR + "str11", "south", 0);

   AI("shingle", "A part of the roof that extends outward "+
     "parallel to the ground.\n");
   AI(({"sign","slate sign", "image", "goat"}), "A slate sign upon " +
     "which is painted the image of a dancing goat.\n");
   ACI(({"sign","slate sign"}), "read", "Beneath the image of "+
     "a goat are the following words: The Dancing Goat Ice "+
     "Cream Parlor.\n");
   AI(({"parlor", "parlour", "building", "pink building", "white building",
     "pink and white building", "ice cream parlor", "dancing goat"}),
     "The Dancing Goat Ice Cream Parlor is painted pink and white. "+
     "It lies directly east of here.\n");	 
   AI(({"house"}),"The house to the north is grey and quite "+
     "uninteresting. A large oak door enters it.\n");
   add_item("inn", "What was once an inn is now an ice cream parlor.\n");

   SHORT("East of the Dancing Goat Ice Cream Parlor");
   make_the_room(" West is the entrance to a cheerily painted "+
      "white and pink building with a dancing goat depicted on "+
      "the sign hanging from the shingle. A delicious scent "+
      "emanates from the doorway. "+
      "There is a small grey house to the north.\n");

  clone_object(BAZAAR+"infidel/obj/housedoor_s")->move(TO);

  reset_room();
}

do_crunch()
   {
   write("Gravel crunches under your feet.\n");
   }

int
temp_block()
   {
   write("The inn is closed at this time.\n");
   return 1;
   }

reset_room()
{
   if(!sneaky)
      {
         sneaky = clone_object(BAZAAR+"infidel/mon/sneaky");
         sneaky->arm_me();
         sneaky->move(TO);
         sneaky->command("close door");
         sneaky->command("lock door with key");
         sneaky->sneak_away();
         sneaky->sneak_away();
       }
}
