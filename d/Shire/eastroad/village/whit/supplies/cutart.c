/* Tart for Shire Inns
 * Taveren, January 2001
 *
 * 2001/01/25 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Added adjectives.
 */

inherit "/std/food";

void
create_food()
{
     set_name("tart");
     //set_pname("tarts");
     //set_short("custard tart");
     //set_pshort("custard tarts");
     set_adj("custard");
     set_long("This tart is made with thick, warm custard.\n");
     set_amount(45);
     
}
