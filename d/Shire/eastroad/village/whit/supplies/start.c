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
     //set_short("strawberry tart");
     //set_pshort("strawberry tarts");
     set_adj("strawberry");
     set_long("This tart has large imported strawberries in it.\n");
     set_amount(45);
}
