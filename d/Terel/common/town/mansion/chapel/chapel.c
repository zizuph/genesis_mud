/* The chapel room of the mansion. Mortricia 920906. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()
#define HARD_TO_PUSH   50
#define OPEN_TIME      20

int pushed, aid=0;

public void
create_room()
{
    object door;

    set_short("chapel");
    set_long(
        "You are now in the chapel room. Long ago the owners of this " +
        "mansion used this room as their private chapel. The priests of " +
        "Calathin had to come here, when summoned, to preach and pray for " +
        "the family members and their guests. Moreover, it is rumoured " +
        "that some members of the family were buried in this very room. " +
        "There is a large marble sarcophagus along the northern wall, and " +
        "on the southern wall a crucifix hangs above a wooden altar. " +
        "A couple of benches stands on the floor.\n");

    add_item(({"sarcophagus", "marble sarcophagus"}),
        "It's a huge marble sarcophagus, covered by a marble lid.\n");
    add_item(({"crucifix"}),
        "It is a large gold crucifix firmly attached to the wall.\n");
    add_cmd_item("crucifix", "get", "It cannot be taken.\n");
    add_item(({"altar"}),
        "This altar has not been used for many years, there is dust " +
        "and cobwebs all over it.\n");
    add_cmd_item(({"altar"}), "get",
        "It's too heavy to be taken, but you notice that it is " +
        "somewhat moveable. Maybe you can push it?\n");
    add_item(({"bench", "benches"}),
        "There are two rows of wooden benches, both covered with dust.\n");
    add_cmd_item(({"bench", "benches"}), "get", "They are too heavy.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    
    add_prop(OBJ_S_WIZINFO,
        "The altar can be pushed to reveal a secret passage. " +
        "Only players with STR > 50 can do it.\n");

    add_exit(MANSION + "wing_e5", "west", 0);
    add_exit(MANSION + "graveyard/grv4.c", "east", 0);

    door = clone_object(MANSION + "chapel/sarc_door1");
    door->move(TO);
    door->set_key(77101);

    pushed = 0;
}

public int
do_pray(string str)
{
    if (str) return 0;
    
    write("You start to pray, but your prayers remain unheard.\n");
    say(QCTNAME(TP) + " mumbles something.\n");
    return 1;
}

public int
do_preach(string str)
{
    if (str) return 0;
    
    write("You are not a priest, so your preaching sounds a bit silly.\n");
    say(QCTNAME(TP) + " starts to preach, but " + TP->query_possessive() +
        " attempt sounds a bit silly.\n");
    return 1;
}

public void
rexit()
{
    if (pushed) {
        remove_exit("south");
        remove_my_desc();
        pushed = 0;
    }
    aid = 0;
}

public void
ropen()
{
    add_exit(MANSION + "chapel/wall_room", "south", 0);
    add_my_desc(
        "There is a secret exit next to the altar in the southern wall.\n");
    pushed = 1;
}

public int
do_push(string str)
{
    notify_fail("Push what?\n");
    if (str != "altar")
        return 0;

    if (TP->query_stat(SS_STR) < HARD_TO_PUSH) {
        write("The altar is too heavy for you to push.\n");
        say(QCTNAME(TP) + " tried to push the altar, but " +
            TP->query_pronoun() + " is too weak.\n");
        return 1;
    }
    if (pushed) {
        write("You push back the altar, and the hidden exit disappears.\n");
        say(QCTNAME(TP) + " pushes the altar.\n");
        if (aid) remove_alarm(aid);
        rexit();
        return 1;
    }

    write(
        "You push the altar and a secret exit appears in the southern wall. " +
        "You feel that the position of the altar now is somewhat unstable, " +
        "thus it may slip back in its normal position very soon after you " +
        "release the pressure.\n");
    say(QCTNAME(TP) + " pushes the altar.\n");
    ropen();
    aid = set_alarm(itof(OPEN_TIME + random(5)), -1.0, rexit);
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_pray,   "pray");
    add_action(do_preach, "preach");
    add_action(do_push,   "push");
}
