/* created by Aridor, 08/12/94 */

#include "local.h"

inherit SOLACE_ROOM

#define PAT "/d/Krynn/haven/road/"

object leader, member1, member2, member3, member4;

void
reset_solace_room()
{
        if (!member1)
            (member1 = clone_object(PAT + "baaz_member"))->move(TO);
        if (!member2)
            (member2 = clone_object(PAT + "baaz_member"))->move(TO);
        if (!member3)
            (member3 = clone_object(PAT + "baaz_member"))->move(TO);
        if (!member4)
            (member4 = clone_object(PAT + "baaz_member"))->move(TO);
        if (!leader)
        {
            (leader = clone_object(PAT + "baaz_leader"))->move(TO);
            leader->start_patrol();
        }

}


void
create_solace_room()
{
    set_short("Fork in the road");
    set_long("Haven Road forks here. The main road runs northwest and east. " +
      "A slightly smaller road leads to the south from here. Towards " +
      "the north, you can see water sparkling and some kind of " +
      "bridge seems to lie to your east. Towards the south the road " +
      "disappears into a valley. The road to the northwest seems to " +
      "lead directly to the huge mountains that can be seen not too " +
      "far away in that same direction. Trees and bushes are dense " +
      "all around you, but you wouldn't call that a forest yet.\n");
    add_exit(HROAD + "bridge","east",0,2);
    add_exit(TO_DARKENWD + "road1","northwest",0,2);
    add_exit(HROAD + "wroad1","south",0,2);
    add_item("bridge",
      "You can't make out any details from this far away.\n");
    add_item(({"body","water","lake"}),
      "This is Crystalmir Lake, even though it is quite some " +
      "distance away, you can still imagine how big it is. " +
      "Looking further north you can see " +
      "dark clouds gathering high in the sky.\n");
    add_item("clouds",
      "These are ordinary clouds, but they still look quite dark " +
      "and menacing, even from this distance.\n");
    add_item("mountains",
      "The mountains in the northwest are quite high and barren, " +
      "and they are very near.\n");
    add_item("road",
      "It's a gravel road leading east and northwest. A smaller road " +
      "forks off to the south.\n");
    add_item(({"trees","bushes"}),
      "These are very ordinary beech trees mostly, and some bushes you " +
      "cannot identify. Hmm, hazelnut seems to be among them, too. " +
      "The trees are not very close together here, but you think you " +
      "could still hide pretty well in this area.\n");
    reset_solace_room();
}

int
closed()
{
    write("Sorry, the road is still closed.\n");
    return 1;
}
