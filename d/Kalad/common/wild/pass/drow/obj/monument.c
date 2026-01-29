inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   ::create_object();
   set_name("monument");
   set_adj("massive");
   add_adj("adamantine");
   set_long("A staggering depiction of a drow female of intense beauty, "+
      "unparalleled determination and awe-inspiring power. The "+
      "statue seems to have captured the very essence of this woman, for "+
      "were it not for its immense size, some twenty feet, you would swear "+
      "that she was a living being that had simply stepped onto the "+
      "giant pedestal upon which she stands.\n"+
      "Writing, in glowing faerie fire, is visible on the base of "+
      "the ten foot high pedestal.\n");
   add_prop(OBJ_I_VALUE,17280000);
   add_prop(OBJ_I_WEIGHT,22727000);
   add_prop(OBJ_I_VOLUME,22727000);
   add_prop(OBJ_M_NO_GET,"Are you out of your mind?!?\n");
   add_prop(OBJ_M_NO_SELL,"You must be kidding!\n");
}
void
init()
{
   ::init();
   AA(read,read);
}
int
read(string str)
{
   if(!str || str != "writing")
      {
      NF("Read what? The writing, perhaps?\n");
      return 0;
   }
   write("On the pedestal has been written:\n"+
      "Created in honor of the first and most glorious high priestess of almighty "+
      "Lolth, Undraya.\n");
   say(QCTNAME(TP) + " reads the writing on the monument's pedestal.\n");
   return 1;
}
