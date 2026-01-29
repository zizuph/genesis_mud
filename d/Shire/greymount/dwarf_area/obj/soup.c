/* Soup for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/food";

void
create_food()
{
    set_name("soup");
    set_pname("soups");
    set_short("bowl of stone soup");
    set_pshort("bowls of stone soup");
	set_adj(({"bowl of", "bowls of", "stone"}));
    set_long("Made with vegetables, grains, and lamb cooked in a pan with a large rock, stone soup is rumored to be delicious.\n");
    set_amount(200);
}
