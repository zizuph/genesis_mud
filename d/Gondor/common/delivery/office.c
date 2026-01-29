/*
 *   This is the inherit file for a delivery office.
 *   Note that it is possible to inherit this file in either a room or a living.
 *   It will provide the commands by default:
 *     'ask for delivery tour': give out a packet for a destination.
 *     'deliver [packet]'     : deliver a packet at its destination.
 *     'return [packet]'      : deliver a packet somewhere else, but not its destination.
 *   Of course it is possible to change these commands, but I suggest they are the
 *   same everywhere for consistancy.
 *
 *   This file modified for Gondor by Olorin, 11-may-1995
 */

#include "/d/Gondor/defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <money.h>
#include <std.h>
#include <stdproperties.h>

#include "local.h"

#define PACKET_LIST ({"dummy", })
#define MAX_STRLEN  34

string  office_name;
int     packets_per_reset = 10;
int     packets_sent;

public void
print_message(string str)
{
    write(str + "\n");
}

void
init_office()
{
    add_action("ask_for_tour","ask");
    add_action("deliver","deliver");
    add_action("return_packet","return");
}

void
reset_office()
{
    packets_sent = 0;
}

static nomask int
do_ask_for_tour(string packet_name)
{
    object  packet,
            room;
    string  dest;

    write("You ask for a packet to deliver.\n");
    say(QCTNAME(TP) + " asks for a packet.\n");
    if (objectp(TP->query_prop(PLAYER_O_DELIVERY)))
    {
        print_message("You have been sent on a delivery tour already. "
          + "You have to deliver that packet before you can get another tour.");
        say(QCTNAME(TP) + " did not get a packet.\n");
        return 1;
    }
    seteuid(getuid(TO));
    dest = DMASTER->new_destination(office_name);
    if (!strlen(dest) || (++packets_sent >= packets_per_reset))
      /* no new destination, can't give out packet. */
    {
        print_message("Unfortunately, there are no more packets here to be "
          + "delivered at this time. Please come back later.");
        say(QCTNAME(TP) + " did not get a packet.\n");
        return 1;
    }
    packet = clone_object(packet_name);
    packet->set_origin_string(office_name);
    packet->set_destination_string(dest);
    write("You are handed a packet which must be delivered to " + dest
      + " as soon as possible. You will receive your reward upon delivery.\n");
    say(QCTNAME(TP) + " receives a packet.\n");
    if (packet->move(TP)) /* too heavy, or doesn't fit? */
    {
        if (objectp(room = ENV(TO)) && room->query_prop(ROOM_I_IS))
            packet->move(room);
        else
            packet->move(TO);
        write("You cannot keep hold of the packet and drop it!\n");
        say(QCTNAME(TP) + " drops the packet.\n");
    }
    TP->add_prop(PLAYER_O_DELIVERY, packet);
    FIX_EUID
    log_file("delivery", sprintf("%s %-12s (%3d) TO DELIVER: from %-34s to %-34s\n",
        ctime(time())[0..15], TP->query_name(), TP->query_average_stat(),
        ((strlen(office_name) > MAX_STRLEN) ? office_name[0..(MAX_STRLEN-1)] : office_name),
        ((strlen(dest) > MAX_STRLEN) ? dest[0..(MAX_STRLEN-1)] : dest)));
    return 1;
}

static int
ask_for_tour(string str)
{
    string  dummy;

    NF("Ask for what? A delivery tour?\n");
    if (sscanf(str,"%sdelivery tour", dummy) != 1)
        return 0;
    dummy = ONE_OF_LIST(PACKET_LIST);
    return do_ask_for_tour(DPACKET(dummy));
}

static nomask int
do_deliver(object ob)
{
    int     price;
    string  from_office;
    object  money,
            env;

    write("You deliver the packet.\n");
    say(QCTNAME(TP) + " delivers a packet.\n");
    if (!ob->query_delivery_packet())
    {
         print_message("Hmmm, this is not a packet I should receive, here you have it back.");
         print_message("If you want to get rid of this packet, you can of course 'return' it to me.");
         say(QCTNAME(TP) + " gets "+TP->query_possessive()+" packet back.\n");
         return 1;
    }
    if (ob->query_destination_string() != office_name)
    {
        print_message("Huh? This packet is not destined for here. You better take it "
          + "where it should go to.");
        say(QCTNAME(TP) + " gets "+TP->query_possessive()+" packet back.\n");
        return 1;
    }
    from_office = ob->query_origin_string();
    price = DMASTER->query_price_for_delivery(from_office,office_name,TP,ob);
    print_message("Here's your payment: " + price + " copper coins.");
    money = MONEY_MAKE_CC(price);
    if (money->move(TP))
    {
        if (objectp(env = ENV(TO)) && (env->query_prop(ROOM_I_IS)))
            money->move(env);
        else
            money->move(TO);
        write("You drop some of the money on the floor!\n");
    }
    say(QCTNAME(TP) + " gets some money in return.\n");
    TP->remove_prop(PLAYER_O_DELIVERY);
    ob->remove_object();
    if (objectp(ob)) /* if it doesn't go away, make it go away */
        SECURITY->do_debug("destruct",ob);
    FIX_EUID
    log_file("delivery", sprintf("%s %-12s (%3d) DELIVERED:  from %-34s to %-34s\n",
        ctime(time())[0..15], TP->query_name(), TP->query_average_stat(),
        ((strlen(from_office) > MAX_STRLEN) ? from_office[0..(MAX_STRLEN-1)] : from_office),
        ((strlen(office_name) > MAX_STRLEN) ? office_name[0..(MAX_STRLEN-1)] : office_name)));
    return 1;
}

static int
deliver(string str)
{
    object  ob,
           *obs;

    NF("Deliver what?\n");
    if (!strlen(str))
        return 0;
    obs = FIND_STR_IN_OBJECT(str,TP);
    if (!obs || !sizeof(obs))
        return 0;
    ob = obs[0];
    return do_deliver(ob);
}

static nomask int
do_return_packet(object ob)
{
    string  from_office,
            dest;

    if (!ob->query_delivery_packet())
        return 0;
    write("You return the packet.\n");
    say(QCTNAME(TP) + " returns a packet.\n");
    if (!ob->query_delivery_packet())
    {
        print_message("This is not a packet I recognize, here you have it back.");
        say(QCTNAME(TP) + " gets "+TP->query_possessive()+" packet back.\n");
        return 1;
    }
    if ((dest = ob->query_destination_string()) == office_name)
    {
        print_message("This is a packet I should receive, why don't you just "
          + "'deliver' it?");
        say(QCTNAME(TP) + " gets "+TP->query_possessive()+" packet back.\n");
        return 1;
    }
    from_office = ob->query_origin_string();
    if (from_office == office_name)
    {
        print_message("You got this packet from here.");
        print_message("If you do not want to deliver it to "+dest
          + " I will take it back.");
    }
    else
    {
        print_message("This packet has another destination than this office. "
          + "For obvious reasons you will not receive any payment for now.");
    }
    log_file("delivery", sprintf("%s %-12s (%3d) RETURNED:   for  %-34s at %-34s\n",
        ctime(time())[0..15], TP->query_name(), TP->query_average_stat(),
        ((strlen(dest) > MAX_STRLEN) ? dest[0..(MAX_STRLEN-1)] : dest),
        ((strlen(office_name) > MAX_STRLEN) ? office_name[0..(MAX_STRLEN-1)] : office_name)));
    TP->remove_prop(PLAYER_O_DELIVERY);
    ob->remove_object();
    if (objectp(ob)) /* if it doesn't go away, make it go away */
        SECURITY->do_debug("destruct",ob);
    return 1;
}

static int
return_packet(string str)
{
    object  ob,
           *obs;

    NF("Return what?\n");
    obs = FIND_STR_IN_OBJECT(str,TP);
    if (!obs || !sizeof(obs))
        return 0;
    ob = obs[0];
    return do_return_packet(ob);
}

public varargs void
set_office_name(string str)
{
    office_name = str;
}

public varargs void
set_office(string str, int packets)
{
    office_name = str;
    packets_per_reset = packets;
}

string
query_office_name(string str)
{
    return office_name;
}

int
query_packets_per_reset()
{
    return packets_per_reset;
}
