/* Stew for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("stew");
    set_pname("stews");
    set_short("murkey stew");
    set_pshort("murkey stews");
    set_adj(({"murkey"}));
    set_long("This is some delicious looking beef stew "+
      "with chunks of taters and carrots and beans drowning in a "+
      "thick, brown gravy.\n");
    set_amount(250);
    
}   
