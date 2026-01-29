/*
 * red_brewery.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

int topen, beerleft, keyin;
int id_hb, id_em;
object drinking;
object dealer;

void heart_beat();
void empty_it();

void
reset_room()
{
    if (!sizeof(all_inventory(TO))) /* check that room empty when doing this */
    {
        topen = 0;
        beerleft = 2000;        /* 10 liter */
    }

    if (dealer)
        return;

    dealer = clone_object(ROKEDIR + "npc/ddealer");
    dealer->move(TO);
}

void
create_room()
{
    set_short("inside the brewery");
    set_long("All around you are lots of pipes, tanks, kegs and bottles. " +
             "A pleasant smell of beer being brewed is in the air, making " +
             "you feel extremly happy. You notice a small tap that is " +
             "attached to one of the pipes.\n");

    add_item("tap",
             "It seems like it is the tap that is used to fill bottles.\n" +
             "Just above it is a small key-hole.\n");

    add_cmd_item("tap", "open", "@@pour");
    add_item(({"key-hole", "hole"}),
             "You study the key-hole carefully, and realize that " +
             "you must insert a key here to be able to open the tap.\n");

    add_cmd_item("tap", "close", "@@closetap");
    add_cmd_item("beer", "drink", "@@drink");

    topen = drinking = 0;
    beerleft = 2000;

    add_exit("red_r2", "south");
    reset_room();
}

int
getkey(string s)
{
    NF("Get key from where?\n");
    if (s == "key")
        return 0;

    NF("Get what from where?\n");
    if (s != "key from hole" && s != "key from key-hole")
        return 0;

    NF("But there is no key in the key-hole.\n");
    if (!keyin)
        return 0;

    TP->catch_msg("You get the key from the key-hole.\n");
    remove_alarm(id_em);
    remove_alarm(id_hb);

    if (drinking)
        drinking->catch_msg("The beer flow stops, " + QCTNAME(TP) +
                            " took the key.\n");
    say(QCTNAME(TP) + " takes the key from the key-hole.\n", ({TP, drinking}));
    topen = 0;

    clone_object(ROKEDIR + "obj/brewkey")->move(TP);

    keyin = 0;

    return 1;
}

int
ins_key(string s)
{
    NF("Insert key in what?\n");
    if (s == "key")
        return 0;

    NF("Insert what in what?\n");
    if (s != "key into key-hole" &&
        s != "key into hole" &&
        s != "key into tap" &&
        s != "key in tap" &&
        s != "key in hole" &&
        s != "key in key-hole")
        return 0;

    NF("There is already a key in the hole.\n");
    if (keyin)
        return 0;

    NF("But you don't have any key.\n");
    if (!present("key", TP))
        return 0;

    NF("The key doesn't fit.\n");
    if (!present("cadu_beerkey", TP))
        return 0;

    present("cadu_beerkey", TP)->remove_object();
    keyin = 1;

    TP->catch_msg("You insert the key into the key-hole.\n");
    say(QCTNAME(TP) + " inserts a key into the key-hole.\n");

    return 1;
}

void
init()
{
    ::init();
    add_action("ins_key", "insert");
    add_action("getkey", "get");
    add_action("getkey", "take");
    add_action("stop", "", 1);
}

int
stop()
{
    if (TP != drinking)
        return 0;

    switch (query_verb())
    {
    case "stop":
        drinking = 0;
        remove_alarm(id_hb);
        TP->catch_msg("You stop drinking and rise from the floor.\n");
        say(QCTNAME(TP) + " stops drinking and rises from the floor.\n");
        id_em = set_alarm(10.0, 0.0, empty_it);
        return 1;
    case "look":
        TP->catch_msg("The only thing you see is a lot of beer.\n");
        return 1;
    default:
        TP->catch_msg("You can't do that unless you 'stop drinking'.\n");
        return 1;
    }
}

void
empty_it()
{
    if (drinking)
        drinking->catch_msg("You can't drink more beer. It just splashes at your face.\n");

    beerleft -= 200;

    tell_room(TO, "Some beer runs out on the floor.\n", ({drinking}));

    if (beerleft <= 0)
    {
        tell_room(TO, "It seems like there is no more beer.\n");
    }
    else
        id_em = set_alarm(10.0, 0.0, empty_it);
}

int
drink()
{
    NF("Someone is already drinking from the tap.\n");
    if (drinking)
        return 0;

    NF("The tap is closed.\n");
    if (!topen)
        return 0;

    drinking = TP;

    id_hb = set_alarm(4.0, 0.0, heart_beat);

    say(QCTNAME(TP) + " lies down and starts to drink from the tap.\n");
    TP->catch_msg("You position yourself under the tap and start to drink.\n");
    remove_alarm(id_em);

    return 1;
}

void
heart_beat()
{
    int stat;

    stat = drinking->drink_alco(8, 0) && drinking->drink_soft(40, 0);

    beerleft -= 20;

    if (stat)
    {
        drinking->catch_msg("You gulp down some beer.\n");
        tell_room(TO, QCTNAME(drinking) + " drinks some beer.\n", ({drinking}));
    }
    else
    {
        remove_alarm(id_hb);
        set_alarm(10.0, 0.0, empty_it);
        drinking->catch_msg("You can't drink any more beer.\n");
        return;
    }

    if (beerleft <= 0)
    {
        remove_alarm(id_hb);
        set_alarm(10.0, 0.0, empty_it);
        return;
    }

    id_hb = set_alarm(4.0, 0.0, heart_beat);
}

string
closetap()
{
    if (!topen)
        return "The tap isn't open.\n";

    topen = 0;
    remove_alarm(id_hb);
    remove_alarm(id_em);

    say(QCTNAME(TP) + " closes the tap.\n");
    return "You close the tap.\n";
}

string
pour()
{
    if (!keyin)
        return "You try to open the tap, but unfortunately noone has " +
                "inserted the key in the key-hole, so you fail.\n";

    if (topen)
        return "It is already open.\n";

    say(QCTNAME(TP) + " opens the tap. Beer begins to flow immedialtely.\n");

    id_em = set_alarm(10.0, 0.0, empty_it);

    topen = 1;

    return "You open the tap. Immediately beer begins to flow.\n";
}
