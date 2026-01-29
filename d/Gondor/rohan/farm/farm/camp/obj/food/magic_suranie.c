/* Magic suranie loaf for the crates
 * in the meadows in the Anorien Forest
 * 
 * Increases mana by 100 (like eating two suranies)
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
#define ADJ2    "suranie"

void
create_food()
{
   set_name(NAME);
   add_name("food");
    add_name("_dunlending_object");
   set_short(ADJ1 + " " + ADJ2 + " " + NAME);
   set_adj(ADJ1);
   set_adj(ADJ2);
   set_long("Dried suranie berries have been chopped and mixed throughout "
    + "the loaf. It's roughly the size of a fist and is two-fingers thick.\n");
   set_amount(350);
   
}

void
special_effect(object eff)
{
    write("You eat the " + query_short() + " and feel refreshed, "
        + "your mind more alert and focused.\n");
    say(QCTNAME(TP) + " eats the " + query_short() + " and looks "
        + "much more focused.\n");
    TP->add_mana(100);
}