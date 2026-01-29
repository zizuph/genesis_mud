/*
 *	/d/Gondor/arnor/greenway/nr3.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance.
 *  28-Apr-2002, By Finwe of the Shire, updated for new Bree recode
 *  July, 2004: Tigerlily, added ambush code
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

public int            move_ranger();
public string         exa_bushes();


public void
create_area_room() 
{
    set_areadesc("marshy plain");
    set_areatype(8);
    set_area("northern");
    set_areaname("the Greenway");
    set_land("the lost realm of Arnor");
    set_mountain("");
    set_grass("long, dark green grass");
    set_extraline("To the north, you can see the North Downs rising. " +
        "This is a lonely, wild land where the wind " +
        "sighs through tall dark green grass. Bushes and bracken " +
        "grow along the road and encroach upon it.");
   
    add_item(({"hills","hill"}), 
         "These hills off in the distance are the North Downs.\n");

    add_exit(ARNOR_DIR + "greenway/nr4", "northwest", 0, 3);
    add_exit("/d/Shire/bree/rooms/road/nroad07", "south" ,0, 3);

   
    add_item(({"greenway","road","ground", "highway"}), BSN(
    "The road is the northern part of the Greenway, which in the old days " +
    "was built by the men of Gondor and Arnor to connect the two " +
    "kingdoms. It runs from the Gap of Rohan to Fornost. Since Arnor " +
    "has fallen and is already almost forgotten, the road has fallen " +
    "into disrepair and is overgrown."));

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
    object tp = this_player();

    if(!RANGERS_MEMBER(tp))
    {
        NF0("The bushes seem far too tangled to enter.\n");
        return 0;
    }

    if(!tp->query_autosneak())
    {
        NF0("You look nervously around, realizing that you are far "
            + "too exposed to do that safely.\n");
        return 0;
    }

    write("With as much stealth as possible, you slip through the bushes.\n");
    say("You hear a slight rustling from the side of the road.\n");
    tell_room(RANGERS_AMB_DIR + "ambush_1a", QCTNAME(tp) + " is suddenly "
        + "standing beside you.\n");

    tp->move_living("M", RANGERS_AMB_DIR + "ambush_1a", 1, 0);
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

