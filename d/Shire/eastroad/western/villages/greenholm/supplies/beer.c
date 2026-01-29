/* Beer for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
      set_name("beer");
      set_pname("beers");
      set_short("mug of good beer");
      set_pshort("mugs of good beer");
      set_adj(({"mug", "good"}));
      set_long("A very fresh, delicious beer, brewed for the "+
                     "tired Bounders to aid them in their work.\n");
      set_soft_amount(110);
      set_alco_amount(8);
    
}
