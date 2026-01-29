inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
   set_name(({"Athasian axe","athasian axe","axe"}));
   set_short("wicked Athasian axe");
   set_long("This vicious axe of Athas was designed soley for slaying, killing, "+
	   "slaughtering, massacring, rampaging, fighting, slashing, beating, "+
	   "crushing, whacking, pummeling, garouting, impaling, smashing, "+
	   "attacking, ambushing, hacking, bashing, and completely obliterating "+
           "any and all who stand in the wielder's way. It is an interesting "+
           "design native to Athas. The shaft is curved to allow equal use of the "+
           "blade as well as the point and hammer. Surprisingly, it doesn't "+
	   "look like something that would be fun to discuss over tea.\n");
	set_adj("wicked");

	set_hit(30);
	set_pen(40);
	set_wt(W_AXE);
	set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
	set_hands(W_BOTH);

}
query_recover()
{
  return MASTER+":"+query_wep_recover();
}
init_recover(arg)
{
  init_wep_recover(arg);
}
