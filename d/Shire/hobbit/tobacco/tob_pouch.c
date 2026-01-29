inherit "/std/receptacle.c";

#include "/d/Shire/common/defs.h"

public void
create_receptacle()
{
   set_name("pouch");
   set_pname("pouches");
   set_adj(({"brown","stained","leather"}));
   set_short("brown leather pouch");
   set_pshort("brown leather pouches");
   set_long("This stained pouch is used for the storage of pipe-weed "+
      "in order to keep it at it's freshest for the purpose of "+
      "smoking it.\n");
   //    No one in their right mind would sell this!
   add_prop(OBJ_M_NO_SELL, "No one wants to buy this stained pouch.\n");
   add_prop(OBJ_I_VALUE, 100);
   add_prop(CONT_I_IN, 1);
   add_prop(CONT_I_RIGID, 0);
   add_prop(CONT_I_TRANSP, 0);
   add_prop(CONT_I_WEIGHT, 250);
   add_prop(CONT_I_VOLUME, 250);
   add_prop(CONT_I_MAX_WEIGHT, 1000);
   add_prop(CONT_I_MAX_VOLUME, 1400);
   
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   
   if (!ob->query_is_tobacco())
      {
      write("This pouch is only for the storage of pipe-weed.\n");
      ob->move(TP);
      return;
   }
   
}
