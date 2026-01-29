/* Stew made from dead Ranger by Rabbit :P
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("stew");
    set_pname("stews");
    set_short("wabbit stew");
    set_pshort("wabbit stews");
    set_adj(({"wabbit", "rabbit"}));
    set_long("This is some delicious looking wabbit stew "+
          "with chunks of taters and carrots and beans drowning in a "+
          "thick, brown gravy.\n");
    set_amount(250);
}
