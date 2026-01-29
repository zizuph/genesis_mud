/* Loaf for Shire Inns
 * Taveren, January 2001
 *
 * 2001/01/25 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Added adjectives.
 */

inherit "/std/food";

void
create_food()
{
     set_name("loaf");
     //set_pname("loaves");
     //set_short("wholemeal loaf");
     //set_pshort("wholemeal loaves");
     set_adj("wholemeal");
     set_long("This loaf has been made from tasty "+
          "wholemeal flour.\n");
     set_amount(60);
 
}
