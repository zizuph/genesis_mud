/* Beer for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/drink";

void
create_drink()
{
      //set_name("porter");
      set_name("mug of porter", 1);
      set_pname("mugs of porter");
      add_name("mug");
      add_name("porter");
      //add_name("mug");
      //set_pname("porter");
      //add_pname("mugs");
      set_short("mug of porter");
      set_pshort("mugs of porter");
      set_long("This porter is a dark beer made from " +
        "browned malt somewhere in the Shire.\n");
      set_soft_amount(100);
      set_alco_amount(20);
      //set_adj("dark");
       
}
