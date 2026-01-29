/*
 * /d/Gondor/guilds/rangers/obj/delay.c
 *
 * A delay object added to a player to delay them in
 * the track task if they don't stick to the rabbit's
 * tracks, and try to brute force the matter. The
 * rabbit will return after a set time.
 *
 * Coded by Gwyneth, October 10, 2003
 *
 * Modification log:
 *
 */
inherit "/std/object";

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <macros.h>
#include <math.h>
#include <stdproperties.h>

#define RESET 30.0

string *gMessages1 = ({ "You get your foot tangled in a vine.",
                        "You sink into some quicksand hidden beneath " +
                        "the foliage.", "A feeling of great dread " +
                        "falls over you, making you paralyzed with fear.",
                        "A sudden wave of dizziness overcomes you, and " +
                        "you can't figure out where you are.",
                        "CRRRRRRRRRAAAAAAACCCCCCCKKKKKKKKKK! A tree " +
                        "limb breaks off and hits your head.",
                        "The beauty of your surroundings overcome you " +
                        "as you lapse into a daydream." });
string *gMessages2 = ({ "You wiggle your foot, desperately trying to free it.",
                        "You squirm around, but it only seems to drag you " +
                        "farther down.", "Something shrieks piercingly " +
                        "as it flies high above.", "You look around in " +
                        "confusion at your surroundings.", "You try to " +
                        "move, but your legs refuse to respond.",
                        "You imagine that all of Middle Earth is healed " +
                        "and rid of the great evil in the East." });
string *gMessages3 = ({ "You give your foot a sharp tug, and it comes free.",
                        "In panic, you manage to snag a vine and pull " +
                        "yourself free.", "The fear suddenly lifts as " +
                        "the beast flies away.", "The dizziness leaves " +
                        "you as suddenly and unexplainably as it came.",
                        "With great effort and determination, you " +
                        "force your legs to work right once again.",
                        "You suddenly realize you have a task to do and " +
                        "leave the dream for another time." });
string *gStopMess = ({ "Your foot is tangled in a vine and you can't move.",
                       "You are caught in quicksand and can't move.",
                       "You are paralyzed with fear and can't bring " +
                       "yourself to move a muscle.", "You are too dizzy " +
                       "and disoriented.", "You can't move your legs!",
                       "Your dream is too interesting to disrupt!" });
int gNum = 0;

public void
create_object()
{
    set_no_show_composite(1);

    set_name(({ "delay", "_ranger_track_task_delay" }));
    set_short("delay");
    set_long("You've been delayed!\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

public void
add_delay_items()
{
    switch(gNum)
    {
    case 0:
        add_item("vine", "What a nuisance! Your foot " +
            "is caught in a vine!\n");
        break;

    case 1:
        add_item("quicksand", "It's hard to see, but " +
            "it's pulling you down!\n");
        break;

    case 4:
        add_item(({ "tree limb", "limb" }), "Where did " +
            "that come from? It is rather large, and has left you " +
            "immobilized.\n");
        add_item("head", "Your head has a little blood " +
            "on it, but you should recover eventually.\n");
        break;

    default:
        break;

    }
}

public string
query_no_move()
{
    return gStopMess[gNum];
}

public void
last_message()
{
    environment()->catch_tell(gMessages3[gNum] + "\n");
    set_alarm(0.1, 0.0, &remove_object());
}

public void
second_message()
{
    environment()->catch_tell(gMessages2[gNum] + "\n");
    set_alarm(RESET, 0.0, &last_message());
}

public void
first_message()
{
    gNum = random(sizeof(gMessages1));

    environment()->catch_tell(gMessages1[gNum] + "\n");
    set_alarm(RESET, 0.0, &second_message());
    add_delay_items();
}

public void
enter_env(object ob, object from)
{
    ::enter_inv(ob, from);

    if (objectp(ob) && !ob->query_npc())
        first_message();
}
