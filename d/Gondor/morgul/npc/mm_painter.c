/*
 * /w/gwyneth/mm_painter.c
 *
 * Armour painter for Minas Morgul.
 *
 * Coded by Gwyneth on August 28, 2000
 */

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

int gMarker = 0;

public void
create_monster()
{
    set_name("gruzgh");
    set_race_name("human");
    set_title("Armour Designer of Minas Morgul");
    set_adj(({"lanky", "nervous"}));

    set_long("This man must be in the employ of the Armourer. Dark " +
        "circles lie heavy under his eyes, and he seems to jump at " +
        "the slightest noise. Perhaps he knows that his life depends " +
        "on the perfection of his work. He notices your gaze and " +
        "immediately lowers his eyes, gesturing to a sign.\n");

    default_config_npc(60);

    add_prop(CONT_I_VOLUME, 32000);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 28000);

    set_alignment(-250);

    set_act_time(8);
    add_act("say Painting is the only happiness in my existance.");
    add_act("emote jumps at a sound nearby.");
    add_act("emote 's eyes shift nervously around the room.");
    add_act("emote inspects his work intently for flaws.");
    add_act("twitch");
    add_act("say My work must be perfect!");

    add_ask(({"armour", "paint armour"}), "say I can paint a " +
        "piece of armour for you if you like. Read the sign for " +
        "more information.", 1);
}

public void
arm_me()
{
    seteuid(getuid(TO));
    clone_object("/d/Gondor/morgul/obj/ltunic")->move(TO);
    command("wear all");
}

public void
introduce(string name)
{
    command("present me to " + name);
}

public void
add_introduced(string name)
{
    set_alarm(1.0, 0.0, &introduce(name));
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
    set_alarm(6.0, 0.0, &command("emote furrows his brow in thought"));
    set_alarm(9.0, 0.0, &command("emote picks up a thick brush and " +
        "dips it in a bucket of black paint."));
    set_alarm(11.0, 0.0, &command("emote sweeps the brush across the " +
        name + " with confident strokes."));
    set_alarm(16.0, 0.0, &command("emote replaces the brush and picks " +
        "up a very fine one."));
    set_alarm(19.0, 0.0, &command("emote dips the brush into the " +
        "paint and bends over the " + arm->query_name() + ", blocking " +
        "your view. His face takes on a very intent look as he works."));
    set_alarm(24.5, 0.0, &command("emote straightens and presents " +
        "his work."));
    set_alarm(27.0, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(29.0, 0.0, &command("asay humbly I hope my work is " +
        "satisfactory."));
    set_alarm(30.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(TP)));
    set_alarm(30.1, 0.0, &command("drop " + OB_NAME(arm)));
    set_alarm(30.2, 0.0, &set_marker(0));
    return 1;
}
