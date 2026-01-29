/* Stew for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("stew");
    set_pname("stews");
    set_short("beef stew");
    set_pshort("beef stews");
    set_adj(({"beef"}));
    set_long("This is some delicious looking beef stew "+
      "with chunks of taters and carrots and beans drowning in a "+
      "thick, brown gravy.\n");
    set_amount(250);
    
}
