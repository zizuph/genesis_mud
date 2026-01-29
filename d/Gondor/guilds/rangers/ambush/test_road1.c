/*
 *  /d/Gondor/guilds/rangers/ambush/test_road1.c
 *
 *  A road room for testing the ambush entrances
 *
 *  Coded by Alto, 03 May 2001
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

public int            move_ranger();
public string         exa_bushes();

void
create_gondor()
{
    set_short("A place somewhere in the middle of nowhere.");
    set_long("This is a road. You have no idea where it leads or how "
        + "you got here. Perhaps there is something interesting about "
        + "it, perhaps not.\n");

    add_item(({"place", "road"}), "There doesn't seem to be anything "
        + "particularly appealing about that and your attention quickly "
        + "slips away from it.\n");
    add_item(({"bush", "bushes"}), &exa_bushes());
    add_cmd_item(({"bush", "bushes", "the bush", "the bushes"}),
        "enter", &move_ranger());

    add_exit(RANGERS_AMB_DIR + "test_road2", "south");


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
    tell_room(RANGERS_AMB_DIR + "ambush_1a", QCTNAME(TP) + " is suddenly "
        + "standing beside you.\n");

    TP->move_living("M", RANGERS_AMB_DIR + "ambush_1a", 1, 0);
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
