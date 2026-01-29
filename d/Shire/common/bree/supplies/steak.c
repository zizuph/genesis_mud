/* Steak for Mag Dogs Calians
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("steak");
    set_pname("steaks");
    set_short("nice juicy steak");
    set_pshort("nice juicy steaks");
    set_adj(({"nice", "juicy"}));
    set_long("A steaming, delicious steak, done to perfection.\n");
    set_amount(300);
}
