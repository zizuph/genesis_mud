inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>

#define CYCLE  3 + random(3)

int aid = 0;

public int
calc_basic()
{
    return(3*this_player()->query_skill(SS_SWIM) +
        this_player()->query_stat(SS_STR) +
        this_player()->query_stat(SS_CON) +
        this_player()->query_stat(SS_DEX));
}

public int
try_hor()
{
    int fat;

    fat = calc_basic();
    fat =(this_player()->query_prop(OBJ_I_WEIGHT) * 1000) /
         (this_player()->query_prop(OBJ_I_VOLUME) * fat);
    if (fat < 1) fat = 1;
    if (fat > 40) fat = 40;
    if (this_player()->query_fatigue() < fat)
    {
        write("You feel too tired to swim horizontally with all the stuff " +
              "you carry.\n");
        return 1;
    }
    this_player()->add_fatigue(-fat);
    return 0;
}

public int
try_up()
{
    int fat;

    fat = calc_basic();
    fat =(this_player()->query_prop(OBJ_I_WEIGHT) * 400) /
         (this_player()->query_prop(OBJ_I_VOLUME) * fat);
    if (fat < 1) fat = 1;
    if (fat > 40) fat = 40;
    if (this_player()->query_fatigue() < fat)
    {
        write("You feel too tired to swim upwards with all the stuff " +
              "you carry.\n");
        return 1;
    }
    this_player()->add_fatigue(-fat);
    return 0;
}

public int
try_down()
{
    int fat;

    fat = calc_basic();
    fat =(this_player()->query_prop(OBJ_I_VOLUME) * 700) /
         (this_player()->query_prop(OBJ_I_WEIGHT) * fat);
    if (fat < 0) fat = 0;
    if (fat > 40) fat = 40;
    if (this_player()->query_fatigue() < fat)
    {
        write("You feel too tired to swim downwards with all the stuff " +
              "you carry.\n");
        return 1;
    }
    this_player()->add_fatigue(-fat);
    return 0;
}

public void
sink_down(object thing, string room)
{
    if (!thing || environment(thing) != this_object()) return;
    
    if (living(thing)) {
        thing->catch_msg("You sink downwards.\n");
        thing->move_living("M", room);
        tell_room(this_object(), QCTNAME(thing) +
                  " sinks downwards....\n", thing);
        tell_room(room, QCTNAME(thing) +
                  " arrives from above....\n", thing);
    } else {
        thing->move(room);
        tell_room(this_object(), capitalize(LANG_ADDART(thing->short())) +
                  " sinks downwards....\n");
        tell_room(room, capitalize(LANG_ADDART(thing->short())) +
                  " arrives from above....\n");
    }
}

public void
float_up(object thing, string room)
{
    if (!thing || environment(thing) != this_object()) return;
    
    if (living(thing)) {
        thing->catch_msg("You float upwards.\n");
        thing->move_living("M", room);
        tell_room(this_object(), QCTNAME(thing) +
                  " floats upwards....\n", thing);
        tell_room(room, QCTNAME(thing) +
                  " arrives from below....\n", thing);
    } else {
        thing->move(room);
        tell_room(this_object(), capitalize(LANG_ADDART(thing->short())) +
                  " floats upwards....\n");
        tell_room(room, capitalize(LANG_ADDART(thing->short())) +
                  " arrives from below....\n");
    }
}

public int
check_things()
{
    int i, interval;
    object *op, thing;
    int breath;

    op = all_inventory();
    for (i=0; i<sizeof(op); i++)
    {
        thing = op[i];
        if (thing->query_race_name() == "fish") continue;
        if (thing->query_prop(MAGIC_I_BREATHE_WATER)) continue;
        if (living(thing))
        {
            breath = thing->query_prop("_breath_int") - 1;
            if (breath)
            {
                thing->add_prop("_breath_int", breath);
                continue;
            }
            interval = thing->query_prop("_breath_int_times");
            if (interval < 5) interval = 5;
            if (interval > 50) interval = 50;
            thing->add_prop("_breath_int", interval);
            breath = thing->query_prop("_breath");
            if (!breath)
            {
                write("You stupid " + thing->query_race() +
                    "... Why didn't you take breath or left the tunnel " +
                    "earlier? " +
                    "Now it happened - you run out of air and drown....\n");
                thing->set_hp(0);
                thing->do_die(this_object());
                continue;
            }
            breath--;
            thing->add_prop("_breath", breath);
            switch (breath)
            {
                case 12: case 11: case 10: case 9: case 8: case 7:
                case 6: tell_object(thing,
                        "You feel very well.\n"); break;
                case 5: tell_object(thing,
                        "You feel quite giddy.\n"); break;
                case 4: tell_object(thing,
                        "You feel very sick - you need air!\n"); break;
                case 3: tell_object(thing,
                        "You are really out of breath!\n"); break;
                case 2: tell_object(thing,
                        "You are completely out of breath, " +
                        "you'll drown soon!\n");
                        break;
                case 1: tell_object(thing,
                        "You are near drowning, " +
                        "actually about to die...\n");
                        break;
                case 0: tell_object(thing,
                        "You are drowning and at death's door....\n");
            }
            continue;
        }
#ifdef DOWN_ROOM
        if (thing->query_prop(OBJ_I_WEIGHT) >
            thing->query_prop(OBJ_I_VOLUME))
            set_alarm(1.0, -1.0, &sink_down(thing, DOWN_ROOM));
#endif
#ifdef UP_ROOM
        if (thing->query_prop(OBJ_I_WEIGHT) <
            thing->query_prop(OBJ_I_VOLUME))
            set_alarm(1.0, -1.0, &float_up(thing, UP_ROOM));
#endif
    }
}

public string
desc(object obj)
{
    string desc1, *sp;

    desc1 = obj->short();
    sp = explode(desc1, "");
    if (sp[0] == "a" && (sp[1] == " " || (sp[1] == "n" && sp[2] == " ")))
    {
        sp[0] = "A";
        return(implode(sp,""));
    }
    if (sp[0] == "a" || sp[0] == "e" || sp[0] == "i" || sp[0] == "o" ||
        sp[0] == "u") return ("An " + desc1);
    return("A " + desc1);
}

public int
end_dive()
{
    write("You finally get out of the water and you're very glad " +
          "you can breathe again - you were afraid you'll drown! You " +
          "feel quite relieved.\n");
    return 0;
}

public void
create_room()
{
    set_short("under water");
    set_long("You're diving in an underwater tunnel system. " +
            "You hope you have enough air in your lungs to survive here... " +
            "The water is very dirty.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    CREATEADD
}

/* To avoid alarms going in the dive rooms when they are empty I added
 * checks in enter_inv() and leave_inv() below, so that the repetive alarms
 * are only going when there is a living in the room.
 * Mortricia, May 1996
 */

/* Start the check_things() alarm if a living is entering here and
 * the alarm isn't already going.
 * If the alarm isn't going and a non-living thing enters, just
 * execute check_things once to let the thing go up, down or stay.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob || aid) return;
    
    if (living(ob)) {
        aid = set_alarm(1.0, itof(CYCLE), check_things);
    } else {
        check_things();
    }
}

public int
is_alive(object ob)
{
    if (!ob || !living(ob)) return 0;
    return 1;
}

/* Only remove the check_things alarm if there are no livings left */
public void
leave_inv(object ob, object from)
{
    object *obs;
    
    ::leave_inv(ob, from);
    
    if (!ob || !living(ob) || !aid) return;
    
    obs = filter(all_inventory(this_object()), is_alive) - ({ ob });
    
    if (sizeof(obs)) return;
    
    remove_alarm(aid);
    aid = 0;
}
