inherit "/d/Shire/common/obj/tob_parent";

#include "/d/Shire/common/defs.h"


void
create_object()
{
   ::create_object();
   set_short("longbottom leaf tobacco");
   add_name("pipe-weed");
   add_name("leaf");
   set_adj("longbottom");
   set_long("This is one of the Shire's most well known and better "+
      "pipe-weeds, known as Longbottom leaf tobacco.  "+
      "The weed is found in the South Farthing of the Shire near the village "+
      "of Longbottom where it's name comes from.\n");
   
   add_prop(OBJ_I_VALUE,25);
}

string
query_flavour()
{
   return "longbottom leaf";
}
