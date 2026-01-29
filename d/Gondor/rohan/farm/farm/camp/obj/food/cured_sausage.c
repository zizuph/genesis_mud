/* Cured Sausage for the crates
 * in the meadows in the Anorien Forest
 *
 *  Raymundo
 *      April, 2020
 */

inherit "/std/food";

#define NAME    "sausage"
#define ADJ1    "cured"
#define ADJ2    "pork"

void
create_food()
{
   set_name(NAME);
   add_name("food");
    add_name("_dunlending_object");
   set_short(ADJ1 + " " + ADJ2 + " " + NAME);
   set_adj(ADJ1);
   set_adj(ADJ2);
   set_long("This is a small cured sausage. It's about as big around as a "
        + "troll's thumb, and as long as a troll's index finger. It's covered "
        + "in a white mold that will preserve it for many weeks, even "
        + "if it's just stored in a crate in a tent.\n");
   set_amount(100);
}
