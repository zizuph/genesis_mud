/*
 * tent.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object leader;

void solved_it(object tp);
void reset_room();

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

    add_item("bed", "It looks like a comfortable bed.\n");
    add_item("desk",
             "It's a large oak desk. To carry it here must have been hard work " +
             "for the soldiers.\n");

    INSIDE;
    add_exit("fd", "out");

    reset_room();
}

void
reset_room()
{
    if (leader)
        return;

    leader = clone_object(ROKEDIR + "npc/campleader");
    leader->equip_me();
    leader->move(TO);
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
