/* Food for the crates
 * in the meadows in the Anorien Forest
 *
 *  Raymundo
 *      April, 2020
 */

inherit "/std/food";

#define NAME    "biscuit"
#define ADJ1    "hard"
#define ADJ2    "camp"

void
create_food()
{
   set_name(NAME);
   add_name("food");
    add_name("_dunlending_object");
   set_short(ADJ1 + " " + ADJ2 + " " + NAME);
   set_adj(ADJ1);
   set_adj(ADJ2);
   set_long("The biscuit is about the size of the palm of your hand, and "
    + "about two nuckles thick. It's hard. But it also seems quite dry. "
    + "Likely this biscut could last for many months if you were on a "
    + "march or stuck in camp.\n");
   set_amount(80);
}
