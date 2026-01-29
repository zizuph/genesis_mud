/* 
	*Moldy bread for orcs
	*Altrus, May 2005
*/

inherit "/std/food";

void
create_food()
{
	set_name("meat");
	add_name("strip");
	set_pname("meats");
	add_pname("strips");
	add_adj("dried");
	add_adj("strip of");
	set_short("strip of dried meat");
	set_pshort("strips of dried meat");
	set_long("It is a long strip of dried, raw meat. There is dried blood on it.\n");
	set_amount(80);
}
