/*
 a crypt for the mansion graveyard redhawk 921027
 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()
#define HARD_TO_PUSH   5
#define OPEN_TIME      20

int pushed, aid=0;

public void
reset_room()
{
}

public void
create_room()
{

    set_short("crypt");
    set_long("You are now in the crypt. Long ago the owners of this " +
             "mansion buried their own dead in this crypt. " +
             "A couple of stone coffins are standing on their biers. " +
             "And on the southern wall a crucifix hangs above a stone altar. " +
             "The crucifix looks like it could be moved.\n");
    add_item(({"coffin", "coffins"}),
             "It is a huge coffin made of finest marble.\n");
    add_item(({"crucifix"}),
        "It is a large gold crucifix maybe you could push it.\n");
    add_item(({"altar"}),
        "This altar has not been used for many years, there is dust " +
        "and cobwebs all over it.\n");
    add_item(({"bier", "biers"}),
        "It is a huge bier made of stone with a coffin on it.\n");

    add_exit(MANSION + "graveyard/grv1.c", "north", 0);

    pushed = 0;
    reset_room();
}

public int
do_pray(string str)
{
    if (str) return 0;
    
    write("You pray over those who are buried here.\n");
    say(QCTNAME(TP) + " mumbles something.\n");
    return 1;
}

public int
do_preach(string str)
{
    if (str) return 0;
    
    write("You are not a priest, so your preaching sounds a bit stupid.\n");
    say(QCTNAME(TP) + " starts to preach, but " + TP->query_possessive() +
        " words are a bit stupid.\n");
    return 1;
}

public void
rexit()
{
    aid = 0;
    if (pushed) {
        remove_exit("south");
        remove_my_desc();
        pushed = 0;
    }
}

public void
ropen()
{
    if (!pushed) {
        add_exit("/d/Terel/LoD/tunnel8", "south", 0);
        add_my_desc("There is an exit next to the altar in " +
                    "the southern wall.\n");
        pushed = 1;
    }
}

public int
do_push(string str)
{
    if (str != "crucifix")
        return 0;

    if (TP->query_stat(SS_STR) < HARD_TO_PUSH) {
        write("The crucifix is too heavy for you to push.\n");
        say(QCTNAME(TP) + " tried to push the crucifix, but " +
            TP -> query_pronoun() + " is too weak.\n");
        return 1;
    }
    
    if (pushed) {
        write("You push back the crucifix and the hidden exit " +
              "disappears.\n");
        if (aid)
            remove_alarm(aid);
        rexit();
    } else {
        write("You push the crucifix and a secret exit appears in the " +
              "southern wall. You feel that the position of the crucifix " +
              "now is somewhat unstable, thus it may slip back in its " +
              "normal position very soon.\n");
        ropen();
        aid = set_alarm(itof(OPEN_TIME), -1.0, rexit);
    }
    say(QCTNAME(TP) + " pushes the crucifix.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_pray,   "pray");
    add_action(do_preach, "preach");
    add_action(do_push, "push");
}
