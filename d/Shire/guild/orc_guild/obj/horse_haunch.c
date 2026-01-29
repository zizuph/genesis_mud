/* 
	*Moldy bread for orcs
	*Altrus, May 2005
*/

inherit "/std/food";

void
create_food()
{
	set_name("haunch");
	set_pname("haunches");
	add_adj("horse");
	add_adj("large");
	set_short("large horse haunch");
	set_pshort("large horse haunches");
	set_long("This is a skinned haunch of a horse. Blood still drips from ends.\n");
	set_amount(150);
}
