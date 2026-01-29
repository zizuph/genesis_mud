 // Depression    (/d/Avenir/common/bazaar/Obj/misc/depression.c)
 // creator(s):   Glinda june -95
 // last update:
 // purpose:      A curse cast upon anyone who attacks Plalgus.
 //
 // note:
 // bug(s):
 // to-do:
inherit "/std/object";

#include "/d/Avenir/common/common.h"



create_object()
{
    set_name("plalgus_curse");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
}

init()
{
 // The std food and drink uses these properties.
   TP->add_prop( TEMP_STDFOOD_CHECKED, 1);
   TP->add_prop( TEMP_STDDRINK_CHECKED, 1);
   add_action("no_drink","drink");
   add_action("no_drink","eat");
   ::init();
}

no_drink(string str)
{
   write("You decide it just isn't worth it.\n");
   switch(random(4))
   {
      case 0: TP->command("sigh");         break;
      case 1: TP->command("sob");          break;
      case 2: TP->command("groan depres"); break;
      case 3: TP->command("pout");         break;
   }
   return 1;
}
