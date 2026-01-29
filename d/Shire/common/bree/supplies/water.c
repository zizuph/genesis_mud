/* Water for Dancing(?:) Pony Inn 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("water");
        set_pname("waters");
        set_short("glass of water");
        set_pshort("glasses of water");
	set_adj(({"glass of", "glass"}));
        set_long("A refreshing glass of cystal clear water.\n");
        set_soft_amount(60);
}
