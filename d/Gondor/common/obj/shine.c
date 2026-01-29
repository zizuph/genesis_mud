/*
 * /d/Gondor/common/obj/sdust_obj.c
 *
 * This is an invisible object cloned onto a player when they
 * toss silver/gold dust into the air. It gives them a subloc of
 * having silver/gold dust in their eyes or on their face.
 *
 * Coded by Gwyneth on September 11, 2000
 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define SHINE_SUBLOC "_shine_subloc"

int gSkill = 0;
string gColour;

public string
query_colour()
{
    return gColour;
}

public void
set_colour(string str)
{
    gColour = str;
}

public void
create_object()
{
    set_name("dust");
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == SHINE_SUBLOC)
    {
        if (!gSkill)
        {
            if (for_obj != on)
            {
                return (capitalize(on->query_pronoun()) + " has a " +
                    (query_colour() == "silver" ? "silvery":"golden") +
                    " shine to " + on->query_possessive() + " skin.\n");
            }
            else
            {
                return "You have a " +
                    (query_colour() == "silver" ? "silvery":"golden") +
                    " shine to your skin.\n";
            }
        }
        else
        {
            if (for_obj != on)
            {
                return (capitalize(on->query_pronoun()) + " has a " +
                    (query_colour() == "silver" ? "silvery":"golden") +
                    " shine to " + on->query_possessive() +
                    " skin and eyes.\n");
            }
            else
            {
                return "You have a " +
                    (query_colour() == "silver" ? "silvery":"golden") +
                    " shine to your skin.\n";
            }
        }
    }

    return 0;
}

public void
remove_dust()
{
    int new_sk;
    object ob = environment();

    new_sk = (ob->query_skill_extra(SS_AWARENESS) - gSkill);

    if (gSkill > 0)
    {
        ob->set_skill_extra(SS_AWARENESS, new_sk);
        ob->catch_tell("You blink the final flecks of " + gColour +
            " dust out of your eyes, and the world seems a " +
            "bit bleaker.\n");
    }

    ob->remove_subloc(SHINE_SUBLOC);
    remove_object();
}

public void
fun_stuff()
{
    object ob = environment();

    if (!living(ob))
    {
        remove_object();
        return;
    }
    else
    {
        ob->add_subloc(SHINE_SUBLOC, this_object());
    }

    set_alarm(3600.0, 0.0, &remove_dust());
}

public void
add_extras()
{
    object ob = environment();

    gSkill = random(5) + 10;

    ob->set_skill_extra(SS_AWARENESS,
      (ob->query_skill_extra(SS_AWARENESS) + gSkill));
}

public int
face_wash(string str)
{
    if (!environment(this_player())->query_prop(OBJ_I_CONTAIN_WATER))
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Wash what?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, ({}), " [silver] [gold] 'face' / 'dust' [off] "))
    {
        notify_fail("Wash what?\n");
        return 0;
    }

    write("You wash the dust off of your face.\n");
    say(QCTNAME(this_player()) + " washes " + 
        this_player()->query_possessive() + " face off.\n");
    set_alarm(1.0, 0.0, &remove_dust());
    return 1;
}

public void
init()
{
    ::init();

    add_action(face_wash, "wash");
}

