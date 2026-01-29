/*
 *      /d/Gondor/arnor/fornost/l_building.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 *      19-Jul-2001, Alto:      Added RoN entrance.
 *      19-Apr-2004, Tigerlily  Tweaked ron entrance code
 *          for new rangers 
 *
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

public string  look_bushes();
public int     move_ranger(object tp);
public int     enter_bushes(string str);

object         actor;

public void
create_fornost()
{
    set_short("a large building in the ruins of Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_mound();
    add_rubble();
    add_ruins();
    add_stones();
    add_walls();

    add_item("building", "Only ruins are left of the building.\n");
    add_item("foundation", 
    "All that remains of the foundations are low mounds.\n");
    add_item(({"bush", "bushes", "shrubbery"}), &look_bushes());

    add_exit(FORNOST_DIR + "s_square", "east", 0, 3);
}

string
set_arnor_long()
{
    string desc;

    desc = "In the ruins of Fornost. Woodland shrubbery seems to be "+
    "reclaiming this area. The overgrown foundations suggests that here "+
    "once was a large building. Some of the lower parts of the walls are "+
    "still standing. To the east is an exit. ";
    desc += query_arnor_time();
    desc += "\n";
    return desc;
}


string
look_bushes()
{
    object tp = this_player();

#ifdef NEW_RANGERS_OPEN    
    if (RANGERS_FULL_MEMBER(tp) ||
        MANAGER->query_voted_in(tp->query_real_name(), "north"))
        {
        return "As you carefully inspect the bushes, you discover that "
            + "they can be squeezed through.\n";
        }

    if (tp->query_wiz_level())
        {
        return "Because you are a wily wizard, you notice the bushes "
            + "can be squeezed through.\n";
        }
#endif

    return "You carefully examine the bushes, but they are far too "
            + "dense to see much.\n";
}


public int
enter_bushes(string str)
{

    object tp = this_player();
    if (!str)
    {
    //default mud emote
    return 0;
    }
    if (str != "bushes" && str != "through bushes")
    {
        notify_fail("Squeeze whom/what [how] ?\n");
        return 0;
    }
#ifdef NEW_RANGERS_OPEN    

    if ((RANGERS_FULL_MEMBER(tp) ||
        MANAGER->query_voted_in(tp->query_real_name(), "north") ||
        tp->query_prop("ranger_north_visitor") ||
        (tp->query_wiz_level())))
    {
        set_alarm(1.0, 0.0, &move_ranger(tp));
        return 1;
    }
#endif

    tp->catch_msg("Beyond cutting yourself on the dense bushes, you fail "
        + "to accomplish much.\n");
    return 1;
}


int
move_ranger(object tp)
{
    say(QCTNAME(tp) + " crouches down.\n");
    tell_room("/d/Gondor/guilds/rangers/north/entrance", QCTNAME(tp) 
        + " arrives through the bushes.\n", ({tp}));
    tp->catch_msg("You squeeze through the dense bushes.\n");
    tp->move_living("M", (RANGERS_NOR_DIR + "entrance"), 1, 0);
    return 1;
}

void
init()
{
    ::init();
    add_action(&enter_bushes(), "squeeze");
}




