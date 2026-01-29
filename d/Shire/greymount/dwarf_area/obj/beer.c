/* Beer for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("beer");
        set_pname("beers");
        set_short("ice cold beer");
        set_pshort("ice cold beers");
        set_adj(({"ice", "cold"}));
        set_long("This is an ice cold beer that numbs your hand as you hold it. It has a good head for its size.\n");
        set_soft_amount(110);
        set_alco_amount(4);
        
}
