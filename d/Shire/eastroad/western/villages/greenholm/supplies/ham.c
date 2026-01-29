/* Steak for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("ham");
    add_name("hambone");
    set_pname("hamss");
    add_name("hambones");
    set_short("large steak");
    set_pshort("large steaks");
    set_adj("large");
    add_adj("hambone");
    set_long("Juices ooze from this nice, thick steak "+
       "as it steams slightly, fresh from the grill.\n");
    set_amount(375);
    
}    
