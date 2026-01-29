inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("letter");
    add_name( ({ "letter from gnimpsh" }) );

    set_short("letter from Gnimpsh");

    set_long("The letter reads:\n\n"
      + "FirstMaligantAndNowMorganToo! BothGone!! HaveYouSeenHer? IDon't\n"
      + "KnowWhyThisIsHappening! WhatWillBecomeOfMyLifeQuest?!?\n\n");

    add_cmd_item( ({ "letter", "letter from gnimpsh",
                     "the letter",
                     "the letter from gnimpsh" }),
                  ({ "read" }), long);

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 3);
} 


void
get_lost(object dest)
{
    if (!living(dest))
    {
        tell_room(dest, "The letter blows away with the wind.\n");
        remove_object();
    }
}


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    set_alarm(1.0, 0.0, &get_lost(dest));
}
