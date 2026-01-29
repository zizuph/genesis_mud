/*
 * /d/Gondor/minas/npc/painter.c
 *
 * Armour painter for Minas Tirith.
 *
 * Coded by Gwyneth on August 28, 2000
 */

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

int gMarker = 0;

public void
create_dunadan()
{
    set_name("miriel");
    add_name("painter");
    set_dunedain_house("Hallacar");
    set_race_name("human");
    set_title("Armour Designer of Minas Tirith");
    set_adj(({"skinny", "dark-haired"}));
    set_long("This woman must be in the employ of the Armourer. " +
        "A curl of hair hangs down rebelliously in front of her " +
        "eyes, and her skin is a pale ivory from infrequent exposure to " +
        "the sun. Perhaps she is too dedicated to her work of painting " +
        "armours for Calmacil to enjoy the outdoors. Her hands look " +
        "very skillful and are covered with paint splashes. She notices " +
        "your gaze and smiles, lighting up the room. She waves her hand " +
        "to the sign and returns to her work.\n");
    set_gender(G_FEMALE);
    set_alignment(250);
    default_config_npc(50 + random(10));

    set_skill(SS_WEP_CLUB, (55 + random(10)));

    set_chat_time(8);

    add_chat("My work is considered the best in all of Gondor.");
    add_chat("I can paint armours with the emblem of Gondor.");
    add_chat("Painting is delicate work.");
    add_chat("Read the sign if you would like me to paint a piece " +
        "of armour.");

    add_ask(({"paint", "armour", "paint armour"}), "say I can paint " +
        "a piece of armour for you if you like. " +
        "Read the sign for more information.", 1);
    add_ask(({"emblem", "gondor"}), "say The white tree with seven stars " +
        "above is a symbol of hope for the people.", 1);
    set_equipment(MINAS_DIR + "obj/ltunic");
}

public void
set_marker(int i)
{
    gMarker = i;
}

public int
query_marker()
{
    return gMarker;
}

public int
paint_tells(object arm, object from)
{
    string name = arm->short();

    if (gMarker)
    {
        command("say I am busy with another job right now.");
        notify_fail("It appears that you must wait your turn.");
        return 0;
    }

    set_marker(1);
    set_alarm(3.0, 0.0, &command("emote looks over the " + name +
        " carefully."));
    set_alarm(6.0, 0.0, &command("smile confidently"));
    set_alarm(9.0, 0.0, &command("emote picks up a thick brush and " +
        "dips it in a bucket of white paint."));
    set_alarm(11.0, 0.0, &command("emote sweeps the brush across the " +
        name + " with confident strokes."));
    set_alarm(15.0, 0.0, &command("emote rinses off the wide brush and " +
        "picks up a somewhat smaller brush."));
    set_alarm(18.0, 0.0, &command("emote dips the brush in silver " +
        "paint and draws a circle on the " + arm->query_name() + "."));
    set_alarm(21.5, 0.0, &command("emote replaces the brush and picks " +
        "up a very fine one."));
    set_alarm(24.5, 0.0, &command("emote dips the brush into the " +
        "paint and bends over the " + arm->query_name() + ", blocking " +
        "your view. Her face takes on a very intent look as she works."));
    set_alarm(31.0, 0.0, &command("emote straightens and presents " +
        "her work."));
    set_alarm(31.5, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(33.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(TP)));
    set_alarm(33.1, 0.0, &command("drop " + OB_NAME(arm)));
    set_alarm(33.2, 0.0, &set_marker(0));
    return 1;
}

