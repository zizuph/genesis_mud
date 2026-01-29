/*
 * Sceptre from Port Macdunn.
 * TAPAKAH, 10/2005
 * Holding it increases player's discipline
 */

inherit "/d/Khalakhor/std/object";
inherit "/lib/holdable_item";

#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h";

#include "../../nspeir.h"

void
create_khalakhor_object()
{
  set_name("sceptre");
  add_name(VOBJID + "sceptre");
  
  set_adj(({"oblong","wolf-headed"}));
  set_short("oblong wolf-headed sceptre");
  set_long(BSN("An oblong wolf-headed sceptre lords of Khalakhor humans held."));
  
  add_prop(OBJ_I_VOLUME, 250);
  add_prop(OBJ_I_WEIGHT,1250);
  add_prop(OBJ_I_VALUE,  550);
  add_prop(OBJ_I_WIZINFO, BSN("Increases holder's discipline by 20% for good holders.\n"));

  set_slots(W_ANYH);
}
mixed
hold()
{
  int modifier;
  
  if(TP->query_alignment() > 0) {
    write("You feel more confident as you hold the sceptre.\n");
    modifier = TP->query_stat(SS_DIS)*SCEPTRE_MOD;
    TP->set_stat_extra(
		       SS_DIS,
		       modifier
		       );
    add_prop("_MY_HOLDER",modifier);
  }
  return 1;
}
mixed
release()
{

  if(TP->query_alignment() > 0) {
    write("You feel less confident as you release the sceptre.\n");
    TP->set_stat_extra(
		       SS_DIS,
		       -query_prop("_MY_HOLDER");
		       );
    add_prop("_MY_HOLDER",0);
  }
  return 1;
}
