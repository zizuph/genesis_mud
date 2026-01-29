/* Cheese Roll for Shire Inns
 * Taveren, January 2001
 *
 * 2001/01/25 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Added adjectives.
 */

inherit "/std/food";

void
create_food()
{
    set_name("roll");
    //set_pname("rolls");
    //set_short("cheese roll");
    //set_pshort("cheese rolls");
    set_adj("cheese");
    set_long("This roll has a tasty crust of melted cheese.\n");
    set_amount(30);
}
