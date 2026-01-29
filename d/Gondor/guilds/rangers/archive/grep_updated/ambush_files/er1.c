/*
 *      /d/Gondor/rohan/road/er1.c
 *
 *      Modification log:
 *      26-Jan-1997, Olorin:    Changed inheritance,
 *                              general revision.
 *      12-August-2002, Alto:   Added ranger ambush functions.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define RHARD   10

public int            move_ranger();
public string         exa_bushes();

public void
create_roads() 
{
    set_street("well-travelled road");
    set_where("southwest");
    set_county("Eastfold");
    set_land("Rohan");
    set_mountain("Ered Nimrais");
    set_vegetation("juicy, green grass");

    set_river_name("Snowbourn");
    set_rhard(RHARD);
    set_rwhere("north");

    set_extraline("As far as one can see to the north, the giant "
        + "plains of Rohan continue. Just north of the road, the "
        + "river Snowbourn winds through the plains. The road "
        + "continues to the west, where it meets a crossroad, and the "
        + "southeast. Far away in the south, a mountain-range is "
        + "rising, running from east to west."); 

    add_exit(ROH_DIR + "plains/h09",     "north", crossing, RHARD);
    add_exit(ROH_DIR + "road/crossroad", "west",         0,     2);
    add_exit(ROH_DIR + "plains/g10",     "east",         0,     4);
    add_exit(ROH_DIR + "road/er2",       "southeast",    0,     2);

    add_item( ({ "river", "stream", "snowbourn" }), BSN("The river "
        + "Snowbourn is one of the many rivers coming out of the "
        + "vales of the White Mountains. It flows eastwards towards "
        + "the mighty river Anduin. Here in the plains, the water in "
        + "the Snowbourn is running not too fast, and it might be "
        + "possible to cross the river here."));

    add_item( ({ "ground", "vegetation", "grass"}), BSN("On both "
        + "sides of the road, the ground is covered with juicy green "
        + "grass. This is perfect horse country!"));

    add_item( ({ "mountains", "mountain-range", "white mountains", }),
        BSN("The snow-covered peaks of the White Moutains are rising "
            + "far to the south, stretching as far as one can see "
            + "both east and west. Between the northern arms of the "
            + "mountains, many green valleys are opening."));
    add_item(({"bush", "bushes"}), &exa_bushes());
    add_cmd_item(({"bush", "bushes", "the bush", "the bushes"}),
        "enter", &move_ranger());

    reset_room();
}

string
exa_bushes()
{
    if(!RANGERS_MEMBER(TP))
    {
        return"The bushes line the road on both sides.\n";
    }

    return"The bushes are bent in such a way that you recognize "
        + "a secret ranger mark. You may enter the bushes unobserved if you "
        + "are stealthy.\n";
}

int
move_ranger()
{
    if(!RANGERS_MEMBER(TP))
    {
        NF0("The bushes seem far too tangled to enter.\n");
    }

    if(!TP->query_autosneak())
    {
        NF0("You look nervously around, realizing that you are far "
            + "too exposed to do that safely.\n");
    }

    write("With as much stealth as possible, you slip through the bushes.\n");
    say("You hear a slight rustling from the side of the road.\n");
    tell_room(RANGERS_AMB_DIR + "ambush_2a", QCTNAME(TP) + " is suddenly "
        + "standing beside you.\n");

    TP->move_living("M", RANGERS_AMB_DIR + "ambush_2a", 1, 0);
    return 1;
}


public void
bushes_alert(object ranger)
{
    ranger->catch_msg("Something about the bushes along the road catches "
        + "your eye.\n");
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(RANGERS_MEMBER(ob))
        set_alarm(0.5, 0.0, &bushes_alert(ob));

}

