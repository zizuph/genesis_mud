inherit "/d/Shire/common/obj/tob_parent";

#include "/d/Shire/common/defs.h"


void
create_object()
{
   ::create_object();
   set_short("old toby tobacco");
   add_name("pipe-weed");
   set_adj(({"old","toby"}));
   set_long("This pipe-weed is an old blend, the very same that Old "+
      "Tobold Hornblower of Longbottom first brought to the Shire.  "+
      "This is a good hardy blend of pipe-weed, which will probably last "+
      "a long time burning in your pipe.\n");
   add_prop(OBJ_I_VALUE,40);
}

string
query_flavour()
{
   return "old toby";
}
