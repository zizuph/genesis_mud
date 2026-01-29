/* Rye Roll for Shire Inns
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
    //set_short("rye roll");
    //set_pshort("rye rolls");
    set_adj("rye");
    set_long("This dark brown roll is made of rye.\n");
    set_amount(40);
}
