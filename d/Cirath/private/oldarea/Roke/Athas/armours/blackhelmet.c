inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("helmet");
	set_short("nasty black helmet");
	add_adj("nasty");
	add_adj("black");
	set_long("What a helmet, indeed! It offers full head protection "+
	   "and looks like it can handle plenty of abuse, too. It is "+
	   "made out of a black iron alloy imported from the far lands "+
	   "of Grimsten.\n");

	set_ac(30);
	set_at(A_HEAD);
	set_am(({ 8, 5, -13 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
