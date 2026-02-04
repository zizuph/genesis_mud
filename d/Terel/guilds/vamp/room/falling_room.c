/*
 * Falling off the balcony 
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#define WATER_ROOM (ROOM_DIR+"water_room")

//proto
void hit_water(object ob);
int fall_fall_fall();

void
create_vamp_room()
{
    set_short("falling through the air");
    set_long("You are plummeting towards the crashing waves of a "+
        "large body of water.  "+
        "What unfortunate series of events led you to this?  "+
        "The cliff face is a mere inches away, and it is unclear which "+
        "is more likely to be your doom - drowning, or being dashed "+
        "along the rocks at the bottom of the cliff.  "+
        "\n");
    
    add_exit(WATER_ROOM, "down", fall_fall_fall);

    add_item(({"water","below","down"}),
        "Below you are the crashing waves of a large body of water.  "+
        "Assuming you survive the impact, you should be able to take a "+
        "raft to land again.  "+
        "You did bring a raft, right?  "+
        "\n");

    add_item(({"ledge","lip","stone lip","low lip","low stone lip",
        "balcony ledge","balcony"}),
        "Far above you is the balcony.  Was it really so bad up there?  "+
        "\n");

    add_item(({"cliff", "cliff face"}),
        "The cliff face appears to be rushing by you at extreme speed, "+
        "although of course it is you who is in rapid motion.  "+
        "The rocky surface is very near you, although you do not "+
        "think you will hit it before you hit the water.  "+
        "At the bottom of the cliff face is a multitude of rocks which "+
        "have eroded over the years.  "+
        "\n");

    add_item(({"rocks","bottom of the cliff","bottom of cliff"}),
        "At the bottom of the cliff is a multitude of rocks of various "+
        "sizes.  "+
        "Most likely broke off of the cliff face and fell below, creating "+
        "a risky landing area at best.  "+
        "From this viewpoint, you cannot help but notice a dark area "+
        "near some of the larger rocks.\n");

    add_item(({"dark area","larger rocks","area"}),
        "The dark area near the larger rocks appears to be a cave entrance "+
        "in the sheer cliff face!  "+
        "Assuming you do not splatter on the rocks, and survive the impact "+
        "of hitting the water, and do not drown, it may be possible to "+
        "swim to the cave entrance.  You quickly memorize the location, "+
        "since you are sure you will not be able to see it from below.  "+
        "\n");

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
    
}

public void
enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);

    if (ob->query_wiz_level())
        return;

    set_alarm(3.0, 0.0, &hit_water(ob));


}

void
hit_water(object ob)
{
    if (!ob)
        return;
    if (ENV(ob)!=TO)
    {
        return;
    }

    if (living(ob))
    {
        ob->catch_msg("\nYou hit the water with a tremendous splash!\n\n");
        say(QCTNAME(ob)+" hits the water with a tremendous splash!\n");
        ob->move_living("M",WATER_ROOM,1, 0);
    } else {
        ob->move(WATER_ROOM);
    }
}


int
fall_fall_fall()
{
    if (IS_VAMP(TP))
    {
        write("You focus your energies and force yourself downwards.\n");
        return 0;
    }
    
    if (TP->query_wiz_level())
    {
        write("Oh, you're going down all right.\n");
        TP->catch_msg("\nYou hit the water with a tremendous splash!\n\n");
        say(QCTNAME(TP)+" hits the water with a tremendous splash!\n");
        TP->move_living("M",WATER_ROOM,1, 0);
        return 1;
    }
    
    write("Oh, you're going down all right.\n");
    return 1;

}