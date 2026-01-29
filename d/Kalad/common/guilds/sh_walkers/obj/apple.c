/*
 * /d/Kalad/common/guilds/sh_walkers/apple.c
 * Created By : Rico 7.01.97
 * First Modif:
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

void
create_food()
{
   set_name("apple");
   set_short("tasty apple");
   add_adj(({ "red", "tasty", "brightly polished", "bright",
      "polished", "tasty polished", "scrumptious" }));
   set_long("A tasty, brightly polished red apple. It's probably "+
      "pretty scrumptious!\n");

   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 5);

   /*  Set the amount that the apple fills the eater's belly by. */
   set_amount(30);
}

/*
 *  Function Name :  consume_text
 *  Description   :  Handle the eating of the apple.
 *  Returns       :  Action description.
 */
void
consume_text(object *arr, string verb)
{
    string str;

    write("You " + verb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n");
    say(QCTNAME(this_player()) + " " + verb + "s " + str + ".\n");
}

