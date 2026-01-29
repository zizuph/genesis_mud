/* Magic chicory loaf for the crates
 * in the meadows in the Anorien Forest
 * 
 * reduces fatigue 70 (like eating two chicories)
 * very rare, high food amount (so you can't eat many)
 *
 *  Raymundo
 *      April, 2020
 */

inherit "/std/food";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"

#define NAME    "loaf"
#define ADJ1    "baked"
#define ADJ2    "chicory"

void
create_food()
{
   set_name(NAME);
   add_name("food");
    add_name("_dunlending_object");
   set_short(ADJ1 + " " + ADJ2 + " " + NAME);
   set_adj(ADJ1);
   set_adj(ADJ2);
   set_long("You can see bits of dried, crushed up chicory throughout "
    + "the loaf. It's about the size of a sandwich, but solid. It "
    + "doesn't look like it'd taste great, but all that chicory should "
    + "be very refreshing.\n");
   set_amount(350);
   
}

void
special_effect(object eff)
{
    object tp = this_player();
    write("You eat the " + query_short() + " and feel refreshed, "
        + "as if you just awoke from a long rest.\n");
    say(QCTNAME(tp) + " eats the " + query_short() + " and looks "
        + "much more refreshed.\n");
    tp->add_fatigue(70);
}