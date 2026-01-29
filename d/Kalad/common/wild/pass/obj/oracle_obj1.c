inherit "/std/object";
#include "/d/Kalad/defs.h"
int uses=10;
/* by Antharanos */
create_object()
{
   ::create_object();
   set_name("orb");
   set_adj("dark");
   add_adj("blue");
   set_long("An orb the color of the deepest blue, faint swirling motes of "+
      "light are visible within it.\n");
   add_prop(OBJ_I_INVIS,100);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
   set_no_show();
}
init()
{
   ::init();
   AA(command,command);
}
command(s)
{
   NF(query_verb() + " what?\n");
   if(!s)
      return 0;
   if(query_verb() == "command")
      {
      if(s != "ranaht")
         return 0;
   }
   else
      if(s != "ranaht")
      return 0;
   NF("You call upon the power of the dark blue orb but nothing happens!\n");
   if(uses < 1)
      return 0;
   write("You call upon the power of the dark blue orb.\n");
   uses = uses - 1;
   remove_invis();
   return 1;
}
remove_invis()
{
   TP->add_prop(OBJ_I_INVIS,0);
   write("You become visible!");
   say(QCTNAME(TP) + " appears before you!\n");
}
