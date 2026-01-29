/* 
	*Moldy bread for orcs
	*Altrus, May 2005
*/

inherit "/std/food";

void
create_food()
{
	set_name("entrails");
	add_name("plate");
	set_pname("entrails");
	add_pname("plates");
	add_adj("bloody");
	add_adj("plate of");
	set_short("plate of bloody entrails");
	set_pshort("plates of bloody entrails");
	set_long("Ah! Now that is a truly revolting, yet somehow satisfying, meal.\n");
	set_amount(100);
}
