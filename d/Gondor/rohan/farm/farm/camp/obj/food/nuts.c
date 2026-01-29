/* Food for the crates
 * in the meadows in the Anorien Forest
 *
 *  Raymundo
 *      April, 2020
 */

inherit "/std/food";

#define NAME    "nuts"
#define ADJ1    "handful"
#define ADJ2    ""

void
create_food()
{
   set_name(NAME);
   add_name("food");
    add_name("_dunlending_object");
   set_short(ADJ1 + " of " + NAME);
   set_adj(ADJ1);
   set_long("This is a handful of nuts, mostly pine nuts but also "
    + "a few walnuts and almonds. They are nutrient dense and last a "
    + "long time, and so are a favorite of people on the move.\n");
   set_amount(50);
}
