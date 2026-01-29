
// Bazaar Street14 (/d/Avenir/common/bazaar/extr/str14.c)
// creator(s):   Triana 1994
// last update:  Tepisch Sept 94
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

init()
{
   ::init();
   ADD("do_crunch","west");
   ADD("do_enter", "enter");
}


void
create_room()
{
   AE(EXTR + "str8", "north", 0);
   AE(EXTR + "str15", "east", 0);
   AE(EXTR + "str13", "west", 0);
   AE(EXTR + "str21", "south", 0);
   AE(INTR + "sackshop", "tent", 0);

   AI("pub", "The infamous Icky Bods Pub appears to be "+
     "open for business. You will need to go north to "+
     "find the entrance.\n");
   AI(({"hut", "mud-brick hut"}), "The locals seem to be "+
     "fearful of whatever is in the hut. You can see them "+
     "looking furtively at it as they hurry by.\n");
   AI(({"tent", "walls", "structure", "canvas", "wall"}),
     "The pale blue canvas walls of the tent have vertical white "+
     "and green stripes.\n");
   AI("sign", "@@read_list");
    ACI("sign", "read", "@@read_list");
 
  SHORT("Eastern Market area, large blue tent");
   make_the_room(" North is the entrance to the local "+
      "pub. South of you there is a break in the crowd around "+
      "a mud-brick hut. There is a sign hanging from the front "+
      "of a large blue tent. "+
      "\n");
}



do_crunch()
   {
   write("Gravel crunches under your feet.\n");
   }

string
read_list()
{
    write("              Havec Sackmaker's Emporium\n"+
        "              ^^^^^^^^^^^^^^^^^^^^^^^^^^\n"+
        "     Havec Sackmaker has expanded his business to serve \n"+
        "     all of Sybarus. Here, you may buy ready-made sacks \n"+
        "     and wearable containers.\n\n"+  
        "       1.  Pouch (worn around the neck) --------   80 cc\n"+
        "       2.  Pouch-belt (worn around the waist) --  200 cc\n"+
        "       3.  Saddlebag (worn over the shoulder) --  310 cc\n"+
        "       4.  Scrip (worn over the shoulder) ------  250 cc\n"+
        "       5.  Knapsack (worn on the back) ---------  400 cc\n"+
        "       6.  Webcloth sack -----------------------  475 cc\n\n"+
        "     All just inside the tent! Come on in!              \n"+ 
        "     --------------------------------------------------- \n");
    return "";
}

int
do_enter(string str)
{
   if (str=="tent" || str== "merchant's tent") 
      {
      write("You step into the confines of the tent.\n");
      TP->move_living("into the tent", INTR + "sackshop");
      return 1;
   }
   write("Enter what? The tent?\n");
   return 1;
}

