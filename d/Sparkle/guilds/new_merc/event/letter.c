/*
 *  /d/Sparkle/guilds/new_merc/event/letter.c
 *
 *  This letter is sent to players to let them know that Sparkle is
 *  under attack and to bring them into the event.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("letter");
    add_name( ({ "letter from eldon" }) );

    set_short("letter from Eldon");
    set_pshort("letters from Eldon");

    set_long("The letter reads:\n\n"
      + "  Mercenaries,\n\n"
      + "  Sparkle is in dire need of your assistance! Yesterday, an elf\n"
      + "  entered the city, horribly wounded, and beset with a type of\n"
      + "  madness, rendering him unable to speak clearly. We have tended\n"
      + "  to his wounds and today he recovered enough to to warn of a\n"
      + "  huge host of goblins marching on Sparkle from the Fortress in\n"
      + "  the Orc Woods! Our scouts have confirmed the reports of this\n"
      + "  elf, who himself claims to have escaped from their dungeons. He\n"
      + "  has warned us that the Ancient One who lurks beneath the foul\n"
      + "  temple has commanded that blood be spilt for its unfathomable\n"
      + "  purposes to begin the New Year.\n\n"
      + "  For now, we must guard the city from immediate attack! If you\n"
      + "  would stay true to your oaths, please once again come to\n"
      + "  protect Sparkle in this hour of need! Summon any allies who may\n"
      + "  be able to help in addition to your own forces! Please!\n\n"
      + "  Signed in haste,\n"
      + "  Eldon, Magistrate of the City Council of Sparkle\n");

    add_cmd_item( ({ "letter", "letter from eldon",
                     "the letter",
                     "the letter from eldon" }),
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
