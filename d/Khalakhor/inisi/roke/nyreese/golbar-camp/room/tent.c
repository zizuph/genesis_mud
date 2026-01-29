/*
 * tent.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Moved into new camp by Treacher, Aug 2021
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object leader;

void solved_it(object tp);

void
create_room()
{
    set_short("Tent");
    set_long("You are standing inside the large tent.\n" +
             "There are lots of different weapons around and you realize that " +
             "the leader of this group is a weapons expert. The weapons are " +
             "well ordered and it looks very impressive. " +
             "There is also a nice desk and a bed in the far end of the tent." +
             "\n");

    add_item("bed", "It looks like a comfortable bed, would be nice to sleep in it.\n");
    add_item("desk",
             "It's a large oak desk. To carry it here must have been hard work " +
             "for the soldiers.\n");

    INSIDE;
    add_exit(CAMP_ROOM + "camp-2-3", "out");

    add_npc(CAMP_NPC + "campleader", 1, &->equip_me());
}


int
sleepinbed(string s)
{
    write("You change your mind quickly when a rattlesnake bites you.\n" +
          "Fortunately it bit in one of your shoes, so you are not hurt.\n");
    return 1;
}

void
init()
{
    ::init();
    if (TP->query_prop(MQ2PROP))
        set_alarm(2.0, 0.0, &solved_it(TP));

    add_action(sleepinbed, "sleep");
}

void
solved_it(object tp)
{
    tp->remove_prop(MQ2PROP);
    tp->add_prop(MQ3PROP, 1);

    tp->catch_msg("\n\nYou feel that you have seen enough, and think that it " +
                  "would be wise to go back to the mayor and tell him what " +
                  "you know!\n\n");
}
