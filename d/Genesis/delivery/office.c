/* /d/Genesis/delivery/office.c
 *
 * This is the inherit file for a delivery office.
 *
 * Created by Aridor 05/95
 * Last modified by Aridor 06/07/95
 *
 * Note that it is possible to inherit this file in either a room or a living.
 * It will provide the commands by default:
 *     'ask %s delivery tour' : give out a packet for a destination.
 *     'deliver [packet]'     : deliver a packet at its destination.
 *     'return [packet]'      : deliver a packet somewhere else, but not its
 *                              destination.
 * Of course it is possible to change these commands, but I suggest they are the
 * same everywhere for consistancy.
 *
 * Look at the example_office.c file in this directory to see how to use this
 * office.
 */

#pragma save_binary

#include "/d/Genesis/delivery/delivery.h"
#include <cmdparse.h>
#include <money.h>
#include <std.h>
#include <macros.h>

#define FEE_FOR_LOST_PACKET   18 /* silver coins */
#define REPORT(x)    find_player("aridor")->catch_msg(x)

string gOffice_name;
/* each office must have a unique name, which should usually contain the name of
 * the city it is in or some other hint of where the office is located!
 * Example: 'Delivery Office in Palanthas' or 'Huntor in Minas Tirith'.
 */

int gPackets_per_reset = 3;
/* the number of packets given out by the office per reset.
 */

int gPackets_sent;
/* the number of packets already given out this reset,
 * gPackets_sent <= gPackets_per_reset is always true.
 */

object *gPlayer_allowed_clear = ({});
/* the players who may currently use the 'clear' command. This is a special command
 * to clear your name when you have failed to deliver too many packets.
 */

string *gPossible_contents;
/* an array of strings with filenames of possible contents of the packets.
 * each packet given out is empty or assigned one of this contents.
 */

string gPacket_to_clone = EXAMPLE_PACKET;
/* the pathname of the object to clone as packet.
 */

/* Function name: delivery_poster
 * Returns:       the default string for a poster with the commands available
 *                for the delivery office. This can be called eg with:
 *                add_item("poster","@@delivery_poster@@");
 */
public string
delivery_poster()
{
    return ("Delivery Office\n" +
	    "'ask for a delivery tour' if you wish to help out and earn a " +
	    "few coins\n and some general experience.\n" +
            "All you need to do with the packet you receive then is " +
	    "to bring it to\n its destination where you will also receive " +
	    "the payment. Use 'deliver\n packet' to deliver your packet at " +
	    "its destination. 'return packet' is\n for packets which are " +
	    "not destined for this office and which do not\n have this " +
	    "office set as origin.\n");
}

/* Function name: print_message
 * Arguments:     str: the message
 * Description:   Hook function which prints a message about asking for a packet
 *                and also delivering. Redefine this function if you want some
 *                NPC to say these messages instead.
 */
public void
print_message(string str)
{
    write(str + "\n");
}

/* Function name: init_office
 * Description:   Adds the commands for the office to a player. Call this
 *                from the init() in the room or init_living() in the npc.
 */
public nomask void
init_office()
{
    if (DELIVERY_MASTER->query_office_is_sending(gOffice_name))
      add_action("ask_for_tour","ask");
    if (DELIVERY_MASTER->query_office_is_receiving(gOffice_name))
      add_action("deliver","deliver");
    add_action("return_packet","return");
    add_action("clear_name","clear");
}

/* Function name: reset_office
 * Description:   Resets the office. Call this from the reset_room() or
 *                reset_living() function.
 */
public nomask void
reset_office()
{
    gPackets_sent = 0;
    gPlayer_allowed_clear = ({});
}


/* Function name: hook_no_packets_to_deliver
 * Description:   The text when there are no more packets to deliver.
 */
public void
hook_no_packets_to_deliver()
{
    say(QCTNAME(this_player()) + " didn't get a packet.\n");
    print_message("Unfortunately, there are no more packets here to be " +
		  "delivered at this time. Please come back later.");
}

/* Function name: hook_already_on_tour
 * Description:   The text when the player is already on a tour.
 */
public void
hook_already_on_tour()
{
    say(QCTNAME(this_player()) + " didn't get a packet.\n");
    print_message("You have been sent on a delivery tour already. You have " +
		  "to deliver that packet before you can get another tour.");
}

/* Function name: hook_no_trust_to_deliver
 * Description:   The text when the player has failed to deliver too many times.
 */
public void
hook_no_trust_to_deliver()
{
    print_message("I don't trust your delivering abilities anymore. With a " +
		  "fee of " + FEE_FOR_LOST_PACKET + " silver coins maybe you " +
		  "can convince me to 'clear your name from the list'.");
}

/* Function name: hook_no_trust_warning
 * Description:   The string when the player is endangered to fail to deliver
 */
public void
hook_no_trust_warning()
{
    print_message("Be warned. If you fail to deliver too many packets, you " +
		  "cannot be trusted and won't be able to do any further " +
		  "deliveries.");
}

/* Function name: hook_give_out_packet
 * Description:   The text when the packet is given out
 */
public void
hook_give_out_packet(string destination)
{
    say(QCTNAME(this_player()) + " receives a packet.\n");
    print_message("This packet must be delivered to " +
		  destination + " as soon as possible. You will receive " +
		  "your reward upon delivery.");
    print_message("I will mark your name in a chart paper to ensure its safe arrival.");
}

/* Function name: hook_no_valid_packet
 * Description:   The text when the delivered thing is not a packet.
 */
public void
hook_no_valid_packet()
{
    say(QCTNAME(this_player()) + " gets " + 
	this_player()->query_possessive() + " packet back.\n");
    print_message("Hmmm, this is not a packet I should receive, here you " +
		  "have it back.");
}

/* Function name: hook_packets_wrong_destination
 * Description:   The text when the packet is delivered at the wrong destination.
 */
public void
hook_packet_wrong_destination()
{
    say(QCTNAME(this_player()) + " gets " + 
	this_player()->query_possessive() + " packet back.\n");
    print_message("Huh? This packet is not destined for here. You better " +
		  "take it where it should go to.\nIf you want to get rid " +
		  "of this packet, you can of course 'return' it to me, " +
		  "except when you got the packet from me of course.");
}

/* Function name: hook_packet_seal_broken
 * Description:   The text when the seal of the packet has been broken
 */
public void
hook_packet_seal_broken()
{
    print_message("What is that?? The seal is broken! Of course you won't " +
		  "get your reward now! I better take this packet, though.");
}

/* Function name: hook_give_out_payment
 * Description:   The text when the payment for the packet is given.
 */
public void
hook_give_out_payment(int price)
{
    print_message("Here's your payment: " + price + " silver coins.");
}

/* Function name: hook_should_deliver_not_return_packet
 * Description:   The text when a packet is returned but should be delivered.
 */
public void
hook_should_deliver_not_return_packet()
{
    say(QCTNAME(this_player()) + " gets his packet back.\n");
    print_message("This is a packet I should receive, why don't you just " +
		  "'deliver' it?");
}

/* Function name: hook_no_return_packet
 * Description:   The text when a packet cannot be returned.
 */
public void
hook_no_return_packet()
{
    print_message("You got this packet from here. You can't just return it " +
		  "like this, please deliver it to its destination.");
}

/* Function name: hook_return_packet
 * Description:   The text when a packet is returned.
 */
public void
hook_return_packet()
{
    print_message("This packet has another destination than this office. For " +
		  "obvious reasons you will not receive any payment for this " +
		  "packet now.");
}

/* Function name: hook_no_money
 * Description:   The text when the player has not enough money to clear
 *                his/her name.
 */
public void
hook_no_money()
{
    print_message("It seems you can't pay the " + FEE_FOR_LOST_PACKET +
		  " silver coins!");
}

/* Function name: hook_reduced_name_on_list
 * Description:   The text when the player got his name cleared/reduced from
 *                the list.
 */
public void
hook_reduced_name_on_list()
{
    print_message("You get one packet cleared from the 'failed to deliver' " +
		  "list.");
}


/* Function name: clear_name
 * Arguments:     str as typed by the player
 * Description:   Someone wants to clear his name from the distrusted-list.
 * Returns:       0/1 depending on success.
 */
static nomask int
clear_name(string str)
{
    string dummy;

    notify_fail("What?\n");
    if (member_array(this_player(), gPlayer_allowed_clear) < 0)
      return 0;

    notify_fail("Clear what? Your name from the list maybe?\n");
    if (!str)
      return 0;

    if (sscanf(str,"%sname from%slist",dummy,dummy) != 2)
      return 0;

    if (!MONEY_ADD(this_player(), -12 * FEE_FOR_LOST_PACKET))
      {
	  hook_no_money();
	  return 1;
      }

    gPlayer_allowed_clear -= ({ this_player(), 0 });
    DELIVERY_MASTER->clear_player_on_tour(this_player());
    hook_reduced_name_on_list();
    return 1;
}

/* Function name: set_packet_path
 * Description:   Give the pathname of the packet object to clone.
 * Returns:       the pathname
 */
public nomask void
set_packet_path(string path)
{
    gPacket_to_clone = path;
}

/* Function name: query_packet_path
 * Description:   Give the pathname of the packet object to clone.
 * Returns:       the pathname
 */
public nomask string
query_packet_path()
{
    return gPacket_to_clone;
}

/* Function name: do_ask_for_tour
 * Arguments:     packet_name, the filename of the packet to clone
 * Description:   Someone asked for a packet, if everything is ok, clone the
 *                packet and give it to the player.
 * Returns:       1: he asked me about the tour.
 */
static nomask int
do_ask_for_tour()
{
    object packet;
    string dest;
    int times;

    write("You ask for a packet to be delivered.\n");
    say(QCTNAME(this_player()) + " asks for a packet.\n");

    if (this_player()->query_prop(PLAYER_O_DELIVERY))
      {
	  hook_already_on_tour();
	  return 1;
      }

    times = DELIVERY_MASTER->query_player_failed_to_deliver(this_player());
    if (times >= 3)
      {
	  hook_no_trust_to_deliver();
	  if (member_array(this_player(), gPlayer_allowed_clear) < 0)
	    gPlayer_allowed_clear += ({ this_player() });
	  return 1;
      }

    if (times > 0 && times < 3)
      {
	  hook_no_trust_warning();
      }

    seteuid(getuid(this_object()));
    dest = DELIVERY_MASTER->new_destination(gOffice_name);
    if (!dest || gPackets_sent >= gPackets_per_reset)
      /* no new destination, can't give out packet. */
      {
	  hook_no_packets_to_deliver();
	  return 1;
      }

    gPackets_sent++;
    packet = clone_object(query_packet_path());
    packet->set_origin_string(gOffice_name);
    packet->set_destination_string(dest);
    packet->set_contents(gPossible_contents);
    hook_give_out_packet(dest);

    if (packet->move(this_player())) /* too heavy, or doesn't fit? */
      {
	  packet->move(environment(this_player()));
	  write("You cannot keep hold of the packet and drop it!\n");
	  say(QCTNAME(this_player()) + " drops the packet.\n");
      }

    this_player()->add_prop(PLAYER_O_DELIVERY, packet);
    DELIVERY_MASTER->add_player_on_tour(this_player());

    return 1;
}

/* Function name: ask_for_tour
 * Arguments:     str, what the player asked for.
 * Description:   if the player really asked for a delivery tour, call
 *                do_ask_for_tour.
 * Returns:       0 didn't ask me, try elsewhere.
 *                1 asked me.
 */
static int
ask_for_tour(string str)
{
    string dummy;

    notify_fail("Ask for what? A delivery tour?\n");
    if (!str || sscanf(str,"%sdelivery%s", dummy, dummy) < 1)
      return 0;

    REPORT("*DELIVERY* " + this_player()->query_name() + " ASKS in " +
	   gOffice_name + ".\n");

    return do_ask_for_tour();
}

/* Function name: do_deliver
 * Arguments:     ob, the object to deliver
 * Description:   Check if its ok to deliver this object here. Calculate how
 *                much the reward is and give out the money.
 * Returns:       1, he meant me with the delivery.
 */
static nomask int
do_deliver(object ob)
{
    int price;
    string from_office;
    object money;

    write("You deliver the packet.\n");
    say(QCTNAME(this_player()) + " delivers a packet.\n");

    if (!ob->query_delivery_packet())
      {
	  hook_no_valid_packet();
	  return 1;
      }

    if (ob->query_destination_string() != gOffice_name)
      {
	  hook_packet_wrong_destination();
	  return 1;
      }

    if (!ob->query_seal()) /* No seal?? */
      {
	  hook_packet_seal_broken();
	  ob->remove_object();
	  return 1;
      }

    DELIVERY_MASTER->clear_player_on_tour(this_player());
    from_office = ob->query_origin_string();
    price = DELIVERY_MASTER->query_price_for_delivery(from_office,
	    gOffice_name, this_player(), ob);

    /* Give some general experience as well */
    this_player()->add_exp_general(DELIVERY_GENERAL_EXP(price));

    hook_give_out_payment(price);

    money = MONEY_MAKE_SC(price);
    if (money->move(this_player()))
      {
	  money->move(environment(this_player()));
	  write("You drop some of the money on the floor!\n");
      }

    say(QCTNAME(this_player()) + " gets some money in return.\n");
    this_player()->remove_prop(PLAYER_O_DELIVERY);
    ob->remove_object();
    if (ob) /* if it doesn't go away, make it go away */
      SECURITY->do_debug("destruct", ob);

    return 1;
}

/* Function name: deliver
 * Arguments:     str, what does the player want to deliver
 * Description:   find the object the player wants to deliver and if one has
 *                been found, call do_deliver.
 * Returns:       0 command not recognized
 *                1 deliver ok.
 */
static int
deliver(string str)
{
    object ob, *obs;

    notify_fail("Deliver what?\n");
    if (!str)
      return 0;

    obs = FIND_STR_IN_OBJECT(str,this_player());
    if (!obs || !sizeof(obs))
      return 0;

    ob = obs[0];
    REPORT("*DELIVERY* " + this_player()->query_name() + " DELIVERS in " +
	   gOffice_name + ".\n");

    return do_deliver(ob);
}

/* Function name: do_return_packet
 * Arguments:     ob, the object to return
 * Description:   Check if this object can be returned here. If yes, take the
 *                object back so that the player can get another tour.
 * Returns:       1, recognized the command.
 */
static nomask int
do_return_packet(object ob)
{
    string from_office;

    if (!ob->query_delivery_packet())
      return 0;

    write("You return the packet.\n");
    say(QCTNAME(this_player()) + " delivers a packet.\n");

    if (!ob->query_delivery_packet())
      {
	  hook_no_valid_packet();
	  return 1;
      }

    if (ob->query_destination_string() == gOffice_name)
      {
	  hook_should_deliver_not_return_packet();
	  return 1;
      }

    from_office = ob->query_origin_string();
    if (from_office == gOffice_name)
      {
	  hook_no_return_packet();
        return 1;
      }

    if (!ob->query_seal()) /* No seal?? */
      {
	  hook_packet_seal_broken();
	  ob->remove_object();
	  return 1;
      }

    hook_return_packet();
    this_player()->remove_prop(PLAYER_O_DELIVERY);
    ob->remove_object();
    if (ob) /* if it doesn't go away, make it go away */
      SECURITY->do_debug("destruct", ob);

    return 1;
}

/* Function name: return_packet
 * Arguments:     str, what does the player want to return?
 * Description:   Find the object the player wants to return and call
 *                do_return_packet.
 * Returns:       0 couldn't find what to return
 *                1 recognized the command.
 */
static int
return_packet(string str)
{
    object ob, *obs;

    notify_fail("Return what?\n");
    if (!str)
      return 0;

    obs = FIND_STR_IN_OBJECT(str, this_player());
    if (!obs || !sizeof(obs))
      return 0;

    ob = obs[0];
    REPORT("*DELIVERY* " + this_player()->query_name() + " RETURNS in " +
	   gOffice_name + ".\n");

    return do_return_packet(ob);
}

/* Function name: set_office
 * Arguments:     str: the name of the office
 *                packets: the number of packets that can be given out each
 *                reset.
 * Description:   Set the office name to identify it and the number of packets
 *                per reset.
 */
public varargs void
set_office(string str, int packets = 3)
{
    gOffice_name = str;
    gPackets_per_reset = packets;
}

/* Function name: set_office_name
 * Arguments:     name: the name of the office
 * Description:   Set the name of the office to identify it.
 */
public void
set_office_name(string name)
{
    gOffice_name = name;
}

/* Function name: set_office_packets_per_reset
 * Arguments:     packets: the max number of packets given out per reset
 * Description:   Set the max number of packets given out per reset
 */
public void
set_office_packets_per_reset(int packets)
{
    gPackets_per_reset = packets;
}

/* Function name: query_office_name
 * Returns:       The name and identifier of this office
 */
public string
query_office_name()
{
    return gOffice_name;
}

/* Function name: query_office_packets_per_reset
 * Returns:       The max number of packets per reset of this office.
 */
public int
query_office_packets_per_reset()
{
    return gPackets_per_reset;
}

/* Function name: add_content
 * Argument:      pathname of the thing to add
 * Description:   Add one filename to the list of possible objects this office
 *                is sending out.
 */
public nomask void
add_content(string str)
{
    if (!gPossible_contents)
      gPossible_contents = ({});
    gPossible_contents += ({ str });
}

/* Function name: query_all_contents
 * Description:   give all filenames of objects that can be inside the packet.
 * Returns:       an array of strings.
 */
public nomask string *
query_all_contents()
{
    return gPossible_contents;
}
