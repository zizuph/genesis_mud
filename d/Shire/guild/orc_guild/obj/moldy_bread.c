/* 
	*Moldy bread for orcs
	*Altrus, May 2005
*/

inherit "/std/food";

void
create_food()
{
	set_name("bread");
	set_pname("breads");
	add_adj("moldy");
	set_short("moldy bread");
	set_pshort("moldy breads");
	set_long("This bread looks disgusting. There crust is distinctly green-blue in color, and rather fuzzy.\n");
	set_amount(50);
}
