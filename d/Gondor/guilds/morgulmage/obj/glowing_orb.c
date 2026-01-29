#include <macros.h>

inherit "/std/object";

string  long_description();
int     is_lit;
int     light_alarm;

#define MANA_COST   100

void create_object()
{
    set_name("orb");
    add_adj("enchanged");
    add_adj("blood-red");
    set_short("enchanted blood-red orb");
    set_long(long_description);

    add_item( ({ "pedestal", "granite pedestal" }),
        "It is set in the southwest corner of the room. A mailed glove " +
        "holding an enchanted blood-red orb extends from it.\n");

    add_item( ({ "mailed glove", "glove" }),
        "The mailed glove extends from the granite pedestal and holds an " +
        "enchanted blood-red orb.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "You cannot seem to pry the enchanted blood-red " +
        "orb from the mailed glove's grasp.\n");

}

int query_is_lit()
{
    return is_lit;
}

string long_description()
{
    if(query_is_lit())
    {
        return "This enchanted blood-red orb is grasped in a mailed glove " +
            "extending from a granite pedestal set in the southwest corner " +
            "of the room. Its shadowy interior emits blood-red rays of " +
            "light throughout the chamber.\n";
    }

    return "This enchanted blood-red orb is grasped in a mailed glove " +
        "extending from a granite pedestal set in the southwest corner " +
        "of the room. In its dull interior lies infinite darkness.\n";

}

void light_changed(int level)
{
    if(!level) return;
}

void extinguish_orb()
{
    is_lit = 0;
    light_alarm = 0;
    tell_room(environment(this_object()),
        "The orb dims as its colour slowly dulls.\n");
}

void light_orb()
{
    light_alarm = set_alarm(60.0, 0.0, extinguish_orb);
    is_lit = 1;
    tell_room(environment(this_object()),
        "Blood-red rays of light flood the chamber.\n");
}

int touch_cmd(string args)
{
    // Do they want to touch us
    if(!parse_command(args, ({}), "[the] [enchanted] [blood-red] 'orb'"))
    {
        notify_fail("Touch what?\n", 0);
        return 0;
    }

    if(query_is_lit() || light_alarm || this_player()->query_mana() < MANA_COST)
    {
        write("You touch the enchanted blood-red orb, but nothing happens.\n");
        say(QCTNAME(this_player()) + " touches the enchanted blood-red orb.\n");
        return 1;
    }

    this_player()->add_mana(-MANA_COST);
    write("You touch the enchanted blood-red orb, and feel mentally drained.\n");
    say(QCTNAME(this_player()) + " touches the enchanted blood-red orb.\n");
    light_alarm = set_alarm(2.0, 0.0, light_orb);
    return 1;
}

void init()
{
    add_action(touch_cmd,   "touch");
}