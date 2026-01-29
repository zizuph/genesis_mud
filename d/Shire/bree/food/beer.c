/* Beer for Dancing(?) Pony Inn 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("beer");
        set_pname("beers");
        set_short("nice cold beer");
        set_pshort("nice cold beers");
        set_adj(({"nice", "cold"}));
        set_long("You couldn't imagine what would refresh you more.\n");
        set_soft_amount(110);
        set_alco_amount(4);
        
}
