/* Pastry for Shire Inns
 * Taveren, January 2001
 *
 * 2001/01/25 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Added adjectives.
 */

inherit "/std/food";

void
create_food()
{
     set_name("pastry");
     //set_pname("pastries");
     //set_short("hathorpe pastry");
     //set_pshort("hathorpe pastries");
     set_adj("hathorpe");
     set_long("The speciality of the Whitfurrows bakery... "+
          "Quite simply, it is delicious.\n");
     set_amount(50);
     
}
