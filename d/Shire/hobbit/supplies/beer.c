/* Beer for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
      set_name("beer");
      set_pname("beers");
      set_short("fresh delicious beer");
      set_pshort("fresh delicious beers");
      set_adj(({"fresh", "delicious"}));
      set_long("A very fresh, delicious beer, brewed for the "+
           "Adventuresome Hobbits to aid them in their journeys.\n");
      set_soft_amount(110);
      set_alco_amount(8);
        
}
