/*
 *  /d/Gondor/morgul/city/mm_stables/obj/leader_object.c
 *
 *  This file contains actions/emotes for the leader of a steed
 *  from the Stables of Minas Morgul.
 *
 *  Deagol, October 2002
 */

inherit "/d/Genesis/steed/new/leader_object.c";
inherit "/lib/commands";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../mm_stables.h"

int hhalt();
int hsnort();
int hhome();
int hhelp(string str);
object Steed;

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);

    if (!living(ob))
    {
        return;
    }
    add_action(hhalt, "hhalt");
    add_action(hsnort, "hsnort");
    add_action(hhome, "hhome");
    add_action(hhelp, "hhelp");
}

void
destruct_horse()
{
    Steed = TO->query_steed();
    Steed->remove_object();
}

int
hhalt()
{   
    write("You bring your steed to a halt.\n");
    say(QCTNAME(TP) + " brings " + POSSESSIVE(TP) + " steed to a halt.\n");
    return 1;
}

int
hsnort()
{
    tell_room(ENV(TP), "The large black horse snorts violently.\n");
    return 1;
}

int
hhome()
{
    if (!IS_IN_ME(TP))
    {
        write("You cannot do that out of Middle Earth.\n");
        return 1;
    }
    write("Forcing your steed to bend its neck with a firm grip on its " +
          "mane, you command it to return to Minas Morgul.\n");
    say("Forcing the large black horse to bend its neck with a firm grip " +
        "on its mane, " + QTNAME(TP) + " whispers something to it.\n");
    set_alarm(2.0, 0.0, &tell_room(ENV(TP), "The large black horse neighs " +
              "as if in obedience and makes off at full gallop, heading " +
              "eastwards. Growing ever more hazy in the distance, it soon " +
              "disappears in a cloud of dust.\n"));
    set_alarm(2.2, 0.0, &destruct_horse());
    return 1;
}

int
hhelp(string str)
{
//    if (str == "saddlebag")
//    {
//        write(HHELP_BAG_MESSAGE);	/* defined in mm_stables.h */
//        return 1;
//    }
    write(HHELP_LEADER_MESSAGE);	/* defined in mm_stables.h */
    return 1;
}
