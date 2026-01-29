/* Stew made from dead Ranger by Rabbit :P
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("stew");
    set_pname("stews");
    set_short("rabbit stew");
    set_pshort("rabbit stews");
    set_adj(({"rabbit", "rabbit"}));
    set_long("Yummy chunks of bunny meat floating in a greasy broth.\n");
    set_amount(200);
}
