/* Beer for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little. */

inherit "/std/drink";

void
create_drink()
{
      set_name("beer");
      //set_pname("beers");
      //set_short("fresh cold beer");
      //set_pshort("fresh cold beers");
      set_adj("fresh");
      //add_adj("delicious");
      add_adj("cold");
      //set_long("A large mug of freshly brewed in " +
      set_long("A large mug of beer, freshly brewed in " +
        "Frogmorton for hobbits to enjoy.\n");      
      set_soft_amount(110);
      set_alco_amount(8);
        
}
