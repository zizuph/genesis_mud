inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name(({ "scalemail", "scale", "mail" }));
	set_short("shiny black scalemail");
	add_adj("shiny");
	add_adj("black");
	add_adj("scale");

	set_long("This armour was developed for an someone "+
	   "who liked to be outfitted with the most fearsome "+
	   "armour on the battle field.\n");

	set_ac(40);
	set_at(A_BODY | A_ARMS);
	set_am(({ 3, 5, -8 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
