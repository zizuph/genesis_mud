inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void create_container()
{
 set_name("chest");
 add_name("_karg_design_plan_chest_");
 set_adj("large");
 add_adj("steel");
 set_long("Massive chest made of steel. It looks very sturdy "+
   "and impossible to break. It might contain very important secrets, "+
   "since lots of kargs seem to guard it. Massive lock protects the "+
   "chest from potential looters.\n");

 add_item("lock","It's massive and heavy. You doubt anything can "+
   "break it. Small keyhole looks very wierd on this massive lock.\n");

 set_no_pick();

 add_prop(OBJ_M_NO_GET,"It's too heavy for you to carry!\n");
 add_prop(OBJ_I_VALUE,1);
 add_prop(CONT_I_IN,1);
 add_prop(CONT_I_RIGID,0);
 add_prop(CONT_I_TRANSP,0);
 add_prop(CONT_I_WEIGHT, 200000);
 add_prop(CONT_I_VOLUME,100000);
 add_prop(CONT_I_MAX_WEIGHT, 220000);
 add_prop(CONT_I_MAX_VOLUME,120000);
 add_prop(CONT_I_CLOSED, 1);
 add_prop(CONT_I_LOCK, 1);

 set_key(PLAN_KEY_ID);

 setuid();
 seteuid(getuid());

 clone_object(STRHOLD_OBJ+"plans")->move(TO,1);
}

public int do_default_unlock(string str)
{
 int res;
 object key;

 res=::do_default_unlock(str);
 if(res) 
  {
   key=present(PLAN_KEY_ID,TP);
   write("As you turn the "+key->short()+" it shatters into many "+
     "pieces.\n");
   say("As "+QTNAME(TP)+" turns the "+key->short()+" it shatters "+
     "into many pieces.\n");
   key->remove_object();
  }

 return res;
}

