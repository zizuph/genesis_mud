/* Scone for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/food";

void
create_food()
{
    //set_name("butter");
    set_name("scone");
    set_adj("butter");
    //add_name("scone");
    //set_pname("butter");
    //add_pname("scones");
    //set_short("butter scone");
    //set_pshort("butter scones");
    set_long("It is a round piece of bread that is " +
        "covered with rich butter.\n");
    set_amount(200);
    
}     
