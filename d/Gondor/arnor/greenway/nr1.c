/*
 *	/d/Gondor/arnor/greenway/nr1.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

static object *Rabbit = allocate(2 + random(2));

public int            move_ranger();
public string         exa_bushes();

public void
create_area_room() 
{
    set_areadesc("marshy field");
    set_areatype(8);
    set_area("northern");
    set_areaname("the Greenway");
    set_land("the lost realm of Arnor");
    set_mountain("");
    set_grass("long, dark green, juicy grass");
    set_forest("Chetwood");
    set_extraline("Dark Chetwood begins just east " +
        "of the road. To the south you can see the crossing of the " +
        "Greenway and the old east road just outside the gates of " +
        "Bree. ");
    add_item(({"chetwood","forest"}), BSN(
    "The forest does not look inviting. Here it is made up mainly of " +
    "fir and hemlock growing so close that it is impossible to enter " +
    "the Chetwood from the road. "));
    add_item(({"tree","trees","fir","hemlock"}), BSN(
    "Fir and hemlock are growing so close together that it is hard " +
    "to make out a single tree. Their branches form a green wall that " +
    "makes it impossible to enter the forest from here. "));
    add_item(({"bree-hill","hill","bree hill","bree","village","town"}), BSN(
    "To the southeast rises Bree-hill, with the village of Bree nestling " +
    "to the west side of the hill, enclosed by a thick hedge and a deep " +
    "dike. "));
    add_item(({"hedge","dike"}), BSN(
    "On the western side of Bree-hill, a hedge and a dike enclose the " +
    "village of Bree. Just east of the crossing of the Greenway with " +
    "the old east road, the road pierces the hedge, entering Bree. " +
    "Here the road is " +
    "blocked by a great gate. To the southeast, you can see a small opening " +
    "in the hedge on the other side of the dike. "));
    add_item(({"hole","opening"}), BSN(
    "There is a small opening in the hedge, but from here you cannot make " +
    "out whether it is possible to enter the village through it."));
    add_item(({"gate","gates"}), "You cannot tell if the great gate is open " +
      "or closed from here.\n");
   
    add_exit(ARNOR_DIR + "greenway/nr2",   "north", 0, 3);
    add_exit(SHIRE_DIR + "bree/ngreenway", "south" ,0, 3);
   
    add_item(({"greenway","road","ground"}), BSN(
    "The road is the northern part of the Greenway, which in the old days " +
    "was built by the men of Gondor and Arnor to connect the two " +
    "kingdoms. It runs from the Gap of Rohan to Fornost. Since Arnor " +
    "has fallen and is already almost forgotten, the road has fallen " +
    "into disrepair and is overgrown. "));
    add_item(({"bush", "bushes"}), &exa_bushes());
    add_cmd_item(({"bush", "bushes", "the bush", "the bushes"}),
        "enter", &move_ranger());

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Rabbit, NPC_DIR + "rabbit", 30.0 + rnd() * 150.0, ARNOR_DIR + "road/");
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
