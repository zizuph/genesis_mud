/*
 * red_bordell.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/trade";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

void snusk2(object tp);
void snusk3(object tp);
void snusk4(object tp);
void snusk5(object tp);
void snusk6(object tp);
void snusk7(object tp);
void snusk8(object tp);
void snusk9(object tp);

object luder, pimp;
int id;

string
sign()
{
    return "The sign says:\n" +
            "To get a lady companion for the night, type <companion>.\n" +
            "If you're interested in what it will cost type <cost>\n";
}

void
reset_room()
{
    if (!luder)
    {
        luder = clone_object(ROKEDIR + "npc/luder");
        luder->move(TO);
    }
    if (!pimp)
    {
        pimp = clone_object(ROKEDIR + "npc/pimp");
        pimp->move(TO);
    }
}

void
create_room()
{
    set_short("escort service");
    set_long("This is the entrance to the local so-called escort service, " +
             "which in fact is nothing but a whore-house. There is a small " +
             "sign on the southern wall stating how to use the services of " +
             "the house. Some stairs leads up to the second floor.\n");

    add_exit("red_r1", "north");
    add_cmd_item("sign", "read", "@@sign");
    add_item("sign", "@@sign");
    add_item("stairs",
             "They are guarded by a huge dwarf, stopping everyone " +
             "trying to walk up them.\n");
    add_item("dwarf", "He looks very mean.\n");
    config_default_trade();
    reset_room();
}

void
init()
{
    ::init();

    add_action("companion", "companion");
    add_action("cost", "cost");
}

int
cost()
{
    TP->catch_msg("You'll have to pay " + (TP->query_stat(SS_CON) *
                                           TP->query_stat(SS_STR)) / 12 +
                  " cc for the visit.\n");
    say(QCTNAME(TP) + " queries about the cost for a visit upstairs.\n");
    return 1;
}

int
companion(string g)
{
    int cost;
    cost = (TP->query_stat(SS_CON) * TP->query_stat(SS_STR)) / 12;

    if (TP->query_gender() != 0)
    {
        write("I'm sorry you will have to wait until my sister " +
              "is here.  She takes female clients, but you will have to " +
              "wait until she returns from vacation.\n");
        return 1;
    }

    if (!present(luder, TO))
    {
        write("You'll have to wait for someone to come and take care of you.\n");
        return 1;
    }

    if (can_pay(cost, TP) == 0)
    {
        write("We don't do any charity work here, sucker! Get more money!\n");
        return 1;
    }
    pay(cost, TP);
    TP->catch_msg("You quickly dig through your pockets and find coins " +
                  "equal to " + cost + " copper coins.\n");
    TP->catch_msg("The young lady in the couch accepts your payment and smiles. " +
                  "She walks towards you and grabs your hand firmly, " +
                  "leading you towards the stair to the second floor.\n");

    pimp->make_a_note(TP);
    id = set_alarm(5.0, 0.0, &snusk2(TP));
}

void remove()
{
    remove_alarm(id);
    id = set_alarm(5.0, 0.0, &snusk9());
}

void
snusk2(object tp)
{
    tell_room(TO,
              "The lady in the couch leaves upstairs with her customer.\n",
              ({tp}));
    tp->catch_msg("You follow her into her room.\n");
    luder->move_living("M", NYREESEDIR + "red_room");
    TP->move_living("M", NYREESEDIR + "red_room");

    id = set_alarm(5.0, 0.0, &snusk3(tp));
}

void
snusk3(object tp)
{
    tp->catch_msg("She begins to remove her clothes. Slowly.\n");
    id = set_alarm(2.0, 0.0, &snusk4(tp));
}

void
snusk4(object tp)
{
    tp->catch_msg("YES!\n");
    id = set_alarm(1.0, 0.0, &snusk5(tp));
}

void
snusk5(object tp)
{
    tp->catch_msg("You think you are dreaming... You havn't experienced anything like it before.\n");
    id = set_alarm(6.0, 0.0, &snusk6(tp));
}

void
snusk6(object tp)
{
    tp->catch_msg("Oh.... yes.... more... lower... right there...\n");
    id = set_alarm(5.0, 0.0, &snusk7(tp));
}

void
snusk7(object tp)
{
    tp->catch_msg("Yes! yes! YES!!! oh... don't stop!!! please... oh... OH... OH!!!\n");
    /*
    if (0 && random(9) < 3)     //Disabled by Glindor 960213
    {
        ROKE_LOG("infected", tp->query_real_name() + " " +
                 extract(ctime(time()), 4, 15) + "\n");
        if (!present("virus"), TP)
            clone_object(ROKEDIR + "obj/virus")->move(tp);
    }
    */
    id = set_alarm(7.0, 0.0, &snusk8(tp));
}

void
snusk8(object tp)
{
    tp->catch_msg("That felt really good! You kiss the lady good bye and " +
                  "walk down the stairs to the entrance, feeling extremly " +
                  "satisfied.\n");

    tp->move_living("M", NYREESEDIR + "red_bordell");
    tp->heal_hp(tp->query_max_hp() / 10);
    clone_object(ROKEDIR + "obj/rose.c")->move(this_object());
    tp->catch_msg("Helena throws a red rose after you...that lands on " +
                  "the floor.\n");

    /*
    if (random(20) < 3)
        tp->heal_hp(10000);     /* mega bonus to compensate virus risk */
    /**/

    id = set_alarm(14.0, 0.0, &snusk9(tp));
}

void
snusk9(object tp)
{
    id = 0;
    luder->move_living("out the door", NYREESEDIR + "red_bordell");
}
