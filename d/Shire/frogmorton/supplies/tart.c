/* Apple Tart for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/05 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/food";

void
create_food()
{
      //set_name("apple");
      set_name("tart");
      set_adj("apple");
      //add_name("tart");
      //set_pname("apple");
      //add_pname("tarts");
      //set_short("apple tart");
      //set_pshort("apple tarts");
      set_long("This apple tart is triangular shaped. " +
        "It's covered with a white glaze and stuffed full of " +
//        "apples. It's still warm from the oven.\n");
        "apple. It's still warm from the oven.\n");
      set_amount(200);
         
}     
     
