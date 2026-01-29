/* Steak for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("steak");
    add_name("t-bone");
    set_pname("steaks");
    add_name("t-bones");
    set_short("large t-bone steak");
    set_pshort("large t-bone steaks");
    set_adj("large");
    add_adj("t-bone");
    set_long("Juices ooze from this nice, thick steak "+
       "as it steams slightly, fresh from the grill.\n");
    set_amount(375);
    
}
