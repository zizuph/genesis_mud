#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "banshee.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("an underground river");
    set_long("You are an underground river with a very, very " +
        "strong current, barrelling around twists and turns " +
        "like a runaway chariot!\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_NO_EXTRA_DESC, 1);
    add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
    add_prop(ROOM_I_NO_EXTRA_ITEM, 1);
    add_prop(ROOM_M_NO_ATTACK, "You're too busy trying to " +
        "keep from drowning to fight!\n");
    add_prop(ROOM_M_NO_MAGIC, "You're too busy trying to " +
        "keep from drowning to use magic!\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

public void
wash_away(object who, object ruins)
{
    string *rooms;
    object dest;

    if (living(who))
    {
        who->catch_tell("As you drop into the frigid waters of " +
            "the underground river, the shock of the cold numbs " +
            "your body instantly, and everything goes black...\n");
        tell_room(TO, QCTNAME(who) + " drops into the frigid waters " +
            "of the underground river beside you, and appears to " +
            "lose consciousness almost instantly, slipping " +
            "beneath the cold waters.\n", ({who}));
        tell_room(ruins, QCTNAME(who) + " lands with a splash " +
            "and vanishes from view.\n");
        
        if (who->query_skill(SS_SWIM) < MIN_SWIM)
        {
            if (!random(10))
            {
                who->catch_tell("Defying all logic, despite " +
                    "your limited swimming abilities you manage " +
                    "to keep yourself on the surface in your " +
                    "nearly-unconscious state.\n");
            }
            else
            {
                who->catch_tell("Between your nearly unconscious " +
                    "condition and poor swimming abilities, you " +
                    "soon feel water rushing into your lungs, and " +
                    "a new darkness descending upon you...\n");
                log_file(BANSHEE_DEATH, who->query_name() +
                    " drowned on " + ctime(time()) + ". Statave " +
                    who->query_average_stat() + ".\n");
                who->heal_hp(-(who->query_max_hp()));
                who->do_die(TO);
                return;
            }
        }
        else
        {
            if (random(10))
            {
                who->catch_tell("Even in your nearly-unconscious "+
                    "state, your supurb swimming abilities take over " +
                    "instinctively, keeping you on the surface " +
                    "of the raging river.\n");
            }
            else
            {
                who->catch_tell("Even in your nearly-unconscious " +
                    "state, your supurb swimming abilities take over " +
                    "instinctively, keeping you on the surface of " +
                    "the raging river, until you feel a large " +
                    "object strike your head (or was it the other way " +
                    "around?) and lose consciousness completely, " +
                    "your last sensation being water flooding into " +
                    "your lungs.\n");
                log_file(BANSHEE_DEATH, who->query_name() +
                    " drowned on " + ctime(time()) + ". Statave " +
                    who->query_average_stat() + ".\n");
                who->heal_hp(-(who->query_max_hp()));
                who->do_die(TO);
                return;
            }
        }

        rooms = get_dir("/d/Khalakhor/ship/macdunn/wbeach/b*.c") - 
            ({"b1.c","bbase.c"});
        dest = ("/d/Khalakhor/ship/macdunn/wbeach/" +
            rooms[random(sizeof(rooms))])->get_this_object();
        who->move_living("M", dest, 1, 1);
        who->set_fatigue(10);
        tell_room(environment(who), QCTNAME(who) + " washes ashore " +
            "upon a wave.\n", ({who}));
        who->catch_tell("You dimly feel yourself being washed up " +
            "onto a rocky shore...you're safe!\n");
        return;
    }

    else if (function_exists("find_corpse", who) == "/std/corpse")
    {
        rooms = get_dir("/d/Khalakhor/ship/macdunn/wbeach/b*.c") - 
            ({"b1.c","bbase.c"});
        dest = ("/d/Khalakhor/ship/macdunn/wbeach/" +
            rooms[random(sizeof(rooms))])->get_this_object();
        who->move(dest, 1);
        tell_room(dest, "To your shock, a receding wave deposits " +
            LANG_ADDART(who->short()) + " on the shore!\n");
        return;
    }

    else if (!(who->query_no_show()))
    {
        tell_room(TO, capitalize(LANG_ADDART(who->short())) + " sinks " +
            "beneath the surface of the river, gone forever.\n");
        who->remove_object();
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from && (file_name(from) != PATH + "ruins"))
        return;

    set_alarm(0.0, 0.0, &wash_away(ob, from));
}
