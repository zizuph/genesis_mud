/* Roll for Shire Inns
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
    //set_short("sourdough roll");
    //set_pshort("sourdough rolls");
    set_adj("sourdough");
    set_long("This is a fresh, hot sourdough roll.\n");
    set_amount(20);
}
