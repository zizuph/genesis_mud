/* Pickle for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/food";

void
create_food()
{
   set_name("pickle");
   //add_name("large");
   set_adj("large");
   //set_pname("pickles");
   //add_pname("large");
   //set_short("large pickle");
   //set_pshort("large pickles");
//   set_long("It is a large cucumber, picked in brine " +
   set_long("It is a small cucumber, pickled in brine " +
      "and aged for a couple of months. It looks crunchy.\n");
   set_amount(150);
}
 
