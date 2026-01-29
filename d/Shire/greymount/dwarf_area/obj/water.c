/* Water for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("water");
        set_pname("waters");
        set_short("glass of water");
        set_pshort("glasses of water");
	    set_adj(({"glass of", "glass", "glasses of"}));
        set_long("This is a glass of crisp mountain water from a nearby spring.\n");
        set_soft_amount(60);
}
