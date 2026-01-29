/* /d/Genesis/delivery/master.c
 *
 * This is the master object for the DELIVERY SERVICE.
 *
 * Created by Aridor, 05/95
 * Last modified by Aridor 05/21/95
 * 
 * This object records all deliverances by people.
 * It maintains the current list of offices which are able
 * to send and/or receive deliveries.
 *
 *
 * This file is loaded from /d/Genesis/preload.c
 */

#pragma save_binary

inherit "/std/room";
/* Make it a room so wizzes can come here to check things.*/

#include "/d/Genesis/delivery/delivery.h"
#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#define SAVE_FILE  MASTER

static mapping all_offices = ([ ]);
/* contains all offices, is a mapping of the form:
 *                      ([ <office name>:({id,<offices to send to>,
 *                                         <offices not to send to>,domain#}),
 *                         ... ])
 *               id is an integer of: 0 send and receive packets.
 *                                    1 send packets only.
 *                                    2 receive packets only.
 *               <offices to send to>:     0 or an array of office names
 *               <offices not to send to>: 0 or an array of office names
 */

mapping lost_last_packet;
/* contains a list of player names who failed to deliver their last packet,
 * actually all players who ask for a packet are put in the list. Whoever
 * delivers his packet will be removed from the list again. The number of
 * packets failed to deliver is accumulated. When the number reaches 3, the
 * player must pay a fee of 4 gold coins before he is allowed to deliver
 * packets again.
 */

/* prototype */
private nomask void
random_clear_one_player();

/* Function name: reset_room
 * Description:   On every reset, we are very friendly and clear one player
 *                from the failed-to-deliver list
 */
void
reset_room()
{
    if (m_sizeof(lost_last_packet) > random(7))
      random_clear_one_player();
}

/* Function name: create_room
 * Description:   Make the master object.
 */
void
create_room()
{
    set_short("Delivery Service Master Room");
    set_long("You are in the Master Room of the DELIVERY SERVICES. " +
	     "The Delivery Services are a chain of offices around the " +
	     "world which need people to transport goods between the " +
	     "offices. People are then rewarded with money. This is " +
	     "intended as a way for newbies to earn honest money :-)\n" +
	     "In this room you can see who is currently on which tour " +
	     "with 'currenttours' or get a list of offices with 'offices'.\n");
    add_prop(ROOM_I_NO_CLEANUP,1);
    set_alarm(1.0,0.0,"add_all_offices");
    restore_object(SAVE_FILE);
}

/* Function name: init
 * Description:   Give the info commands to the wizard.
 */
void
init()
{
    add_action("offices", "offices");
    add_action("currenttours", "currenttours");
    ::init();
}

/* Function name: offices
 * Arguments:     anything
 * Description:   Dump the list of all offices which are currently open.
 * Returns:       1
 */
public int
offices(string str)
{
    if (!this_player()->query_wiz_level())
      return 0;
    
    dump_array(all_offices);

    return 1;
}

/* Function name: currenttours
 * Arguments:     anything
 * Description:   Display a list of all players who are currently doing a
 *                delivery.
 * Returns:       1
 */
public int
currenttours(string str)
{
    mixed *players = users();
    int size = sizeof(players);
    mixed tmp;
    int i = -1;

    if (!this_player()->query_wiz_level())
      return 0;

    write("CURRENT DELIVERIES\n");
    write("-----------------------------------------------------\n");
    while(++i < size)
      {
	  tmp = players[i]->query_prop(PLAYER_O_DELIVERY);
	  if (!tmp)
	    continue;
	  write(sprintf("%s DELIVERS FROM %s TO %s.\n",
			players[i]->query_name(),
			tmp->query_origin_string(),
			tmp->query_destination_string()));
      }

    return 1;
}

/* Function name: add_office
 * Arguments:     new_office: the office name
 *                id: 0: used for both giving out and accepting packets.
 *                    1: only gives out packets.
 *                    2: only receives packets.
 *                send_to: 0 or an array of office names to send to.
 *                not_send_to: 0 or an array of office names never to send to.
 *                domain: the domain number the office is located in.
 * Description:   Add one office to the master list of offices.
 */
public varargs void
add_office(string new_office, int id, mixed send_to, mixed not_send_to,
	   int domain)
{
    if (!all_offices)
      all_offices = ([ ]);
    all_offices += ([ new_office:({id, send_to, not_send_to, domain}) ]);
}

/* Function name: remove_office
 * Arguments:     name: the name of the office
 * Description:   Remove the office from the master list
 */
public void
remove_office(string name)
{
    m_delete(all_offices, name);
}


/* Function name: add_all_offices
 * Description:   Check all domains for the file /d/<domain>/open/delivery.c
 *                and load all office information for the domain. To see the
 *                format of the file /d/<domain>/open/delivery.c, look at
 *                /d/Krynn/open/delivery.c
 */
void
add_all_offices()
{
    string *domains = SECURITY->query_domain_list();
    int i,j,dom_num;
    string domain_file;
    mixed *data;

    for(i=0;i<sizeof(domains);i++)
      {
	  data = 0;
	  dom_num = SECURITY->query_domain_number(domains[i]);
	  domain_file = "/d/" + capitalize(domains[i]) + "/open/delivery";
	  if (file_size(domain_file + ".c") < 0 ||
	      catch(domain_file->load_me()))
	    continue;

	  data = domain_file->query_domain_delivery_offices();
	  domain_file->remove_object();

	  if (!pointerp(data))
	    continue;

	  for(j=0;j<sizeof(data);j++)
	    {
		if (!pointerp(data[j]))
		  continue;
		add_office(data[j][0], data[j][1], data[j][2], data[j][3],
			   dom_num);
	    }
      }
}

/* Function name: get_all_to_offices
 * Description:   From the list of all offices, select those which something
 *                can be delivered to.
 * Returns:       the array of offices.
 */
static mixed
get_all_to_offices()
{
    mixed tmp;
    mixed all_office_idxs = m_indexes(all_offices);
    int size = sizeof(all_office_idxs);
    mixed all_to_offices = ({ });
    int i = -1;

    while(++i < size)
      {
	  tmp = all_offices[all_office_idxs[i]][0];
	  if (tmp == 0 || tmp == 2)
	    all_to_offices += ({ all_office_idxs[i] });
      }

    return all_to_offices;
}

/* Function name: get_all_from offices
 * Description:   From the list of all offices, select those which can send
 *                packets to other offices.
 * Returns:       the array of offices
 */
static mixed
get_all_from_offices()
{
    mixed tmp;
    mixed all_office_idxs = m_indexes(all_offices);
    int size = sizeof(all_office_idxs);
    mixed all_to_offices = ({ });
    int i = -1;

    while(++i < size)
      {
	  tmp = all_offices[all_office_idxs[i]][0];
	  if (tmp == 0 || tmp == 1)
	    all_to_offices += ({ all_office_idxs[i] });
      }

    return all_to_offices;
}

/* Function name: new_destination
 * Arguments:     from_office, the office the new packet is from
 * Description:   Choose a destination for a newly created packet coming from
 *                from_office. The destination is randomly selected out of the
 *                list of all possible destinations for the packet.
 * Returns:       the destination for the new packet.
 */
public nomask string
new_destination(string from_office)
{
    mixed office_data = all_offices[from_office];
    mixed to_office;
    mixed all_to_offices = get_all_to_offices();
    int i;

    if (!office_data)
      /* Something went wrong, from_office is not officially registered. */
      return 0;

    all_to_offices -= ({ from_office }); /* Obviously :) */

    for(i=0;i<11;i++)
      {
	  to_office = all_to_offices[random(sizeof(all_to_offices))];
	  if ((office_data[1] == 0 ||
	       member_array(to_office,office_data[1]) >= 0) &&
	      (office_data[2] == 0 ||
	       member_array(to_office, office_data[2]) < 0))
	    return to_office; /* Found an office to send to, return it. */
      }

    /* We couldn't find an office to send to in 10 attempts, aborted. */
    return 0;
}

/* Function name: query_price_for_delivery
 * Arguments:     from_office: where the packet came from
 *                to_office: where the packet went to
 *                who_delivered: the person who delivered the packet
 *                packet: the packet itself.
 * Description:   Calculate the reward for a packet.
 *                This is the function that tells us how much money we get for
 *                a delivered packet. The idea is that depending on the distance
 *                between the offices and the amount of money needed to make the
 *                journey (ships!) the price will vary. Another factor is the
 *                speed of deliverance, but only to a minor degree.
 * Returns:       the money to give out in copper coins.
 */
public nomask int
query_price_for_delivery(string from_office, string to_office,
			 object who_delivered, object packet)
{
    int mini, maxi, mint, maxt;
    int packet_age = time() - packet->query_start_time_packet();
    mixed from_data = all_offices[from_office];
    mixed to_data = all_offices[to_office];

    if (from_data[3] == to_data[3]) /* within the same domain */
      {
	  mini = 24; maxt = 1800;/*originally: 12*/
	  maxi = 48; mint = 600; /*originally: 24*/
	  /* anything more than 30 minutes means 12sc within a domain */
	  if (packet_age > maxt)
	    return mini;
	  /* anything below than 10 minutes means 24sc within a domain */
	  if (packet_age < mint)
	    return maxi;
      }
    else
      {
	  mini = 72; maxt = 3600; /*originally: 36*/
	  maxi = 144; mint = 1200;/*originally: 72*/
	  /* anything more than 60 minutes means 36sc between two domains */
	  if (packet_age > maxt)
	    return mini;
	  /* anything below than 20 minutes means 72sc between two domains */
	  if (packet_age < mint)
	    return maxi;
      }

    /* by default, take a value from a linear regression */
    return maxi - ((maxi-mini) * (packet_age - mint) / (maxt - mint));
}

/* Function name: query_office_is_sending
 * Arguments:     office: the name of an office
 * Returns:       whether or not this office is able to send out packets.
 */
public nomask int
query_office_is_sending(string office)
{
    mixed office_data = all_offices[office];

    if (!sizeof(office_data))
      return 0;

    return office_data[0] <= 1;
}

/* Function name: query_office_is_receiving
 * Arguments:     office: the name of an office
 * Returns:       whether or not this office may receive packets.
 */
public nomask int
query_office_is_receiving(string office)
{
    mixed office_data = all_offices[office];

    if (!sizeof(office_data))
      return 0;

    return office_data[0] != 1;
}

/* Function name: query_player_failed_to_deliver
 * Arguments:     who: the player
 * Returns:       the number of packets the player failed
 *                to deliver before.
 */
public nomask int
query_player_failed_to_deliver(object who)
{
    string the_name = who->query_real_name();

    if (!lost_last_packet)
      lost_last_packet = ([]);
    save_object(SAVE_FILE);

    return lost_last_packet[the_name];
}

/* Function name: add_player_on_tour
 * Arguments:     who: the player
 * Description:   Add a player to the current list of people
 *                who are on a tour. This is called when a packet
 *                is asked for.
 */
public nomask void
add_player_on_tour(object who)
{
    string the_name = who->query_real_name();

    if (!lost_last_packet)
      lost_last_packet = ([]);
    if (lost_last_packet[the_name] == 0)
      lost_last_packet += ([the_name:1]);
    else
      lost_last_packet[the_name]++;
    save_object(SAVE_FILE);
}

/* Function name: clear_player_on_tour
 * Arguments:     who: the player
 * Description:   Clear a player from the current list of people
 *                who are on a tour. This is called when a packet
 *                is delivered.
 */
public nomask void
clear_player_on_tour(object who)
{
    string the_name = who->query_real_name();

    if (!lost_last_packet)
      lost_last_packet = ([]);
    if (lost_last_packet[the_name] <= 1)
      lost_last_packet = m_delete(lost_last_packet, the_name);
    else
      lost_last_packet[the_name]--;
    save_object(SAVE_FILE);
}

/* Function name: random_clear_one_player
 * Description:   Clear one packet for one player from the list of people who
 *                have failed to deliver packets. This (slowly) takes care of
 *                erased players and removes their entries from the list.
 */
private nomask void
random_clear_one_player()
{
    string the_name;
    string *who_list;

    if (!lost_last_packet)
      lost_last_packet = ([]);
    who_list = m_indexes(lost_last_packet);
    if (!who_list || !sizeof(who_list))
      return;

    the_name = who_list[random(sizeof(who_list))];
    if (lost_last_packet[the_name] <= 1)
      lost_last_packet = m_delete(lost_last_packet, the_name);
    else
      lost_last_packet[the_name]--;
    save_object(SAVE_FILE);
}
