/* food for the crates
 * in the meadows in the Anorien Forest
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

#define NAME    "meat"
#define ADJ1    "dried"
#define ADJ2    

void
create_food()
{
   set_name(NAME);
   add_name("food");
    add_name("_dunlending_object");
   set_short(ADJ1 + " " + NAME);
   set_adj(ADJ1);
   set_adj("horse");
   set_long("You hold a piece of dried meat in your hand. It looks as though "
    + "it was sliced thin, salted, and then hung out to dry in the sun and "
    + "wind. You have no idea what kind of meat this is without tasting "
    + "it.\n");
   set_amount(100);
}

void
init()
{
    ::init();
    add_action( "do_taste", "taste");
    add_action( "do_taste", "lick");
}

int
do_taste(string str)
{
    if(str == "meat" | str == "dried meat" | str == "dried food")
    {
        say(QCTNAME(TP) + " nibbles on a corner of the " 
            + TO->query_short() + ", only to realize what type "
            + "of meat it is!\n");
        write("You nibble on a corner of the " + TO->query_short()
            + ". It's not lamb... not beef... not venison... Then it "
            + "hits you: this must be horse meat!\n");
        return 1;
    }
    else
    {
        notify_fail("Taste what? The meat?\n");
        return 0;
    }
}