/* This is the master object for the DELIVERY SERVICE.
 *
 * Created by Aridor, 05/95
 * Last modified by noone, never :)
 * 
 * This object records all deliverances by people.
 * It maintains the current list of offices which are able
 * to send and/or receive deliveries.
 */

inherit "/std/room";
/* Make it a room so wizzes can come here to check things.*/

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <std.h>

mapping all_offices;
/* contains all offices, is a mapping of the form:
 *                      ([ <office name>:({id,<offices to send to>,
 *                                         <offices not to send to>,domain#}), ... ])
 *               id is an integer of: 0 send and receive packets.
 *                                    1 send packets only.
 *                                    2 receive packets only.
 *               <offices to send to>:     0 or a list of office names
 *               <offices not to send to>: 0 or a list of office names
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
    set_alarm(20.0,0.0,"add_all_offices");
}

void
init()
{
    ADA("offices");
    ADA("currenttours");
    ::init();
}

public int
offices(string str)
{
    dump_array(all_offices);
    return 1;
}

public int
currenttours(string str)
{
    mixed *players = users();
    int size = sizeof(players);
    mixed tmp;
    int i = -1;
    write("CURRENT DELIVERIES\n");
    write("-----------------------------------------------------\n");
    while(++i < size)
      {
	  tmp = players[i]->query_prop(ON_DELIVERY_TOUR);
	  if (!tmp)
	    continue;
	  write(sprintf("%s DELIVERS FROM %s TO %s.\n", players[i]->query_name(),
			tmp->query_origin_string(), tmp->query_destination_string()));
      }
    return 1;
}

/* Arguments: the office object
 *            id: 0: used for both giving out and accepting packets.
 *                1: only gives out packets.
 *                2: only receives packets.
 */
public varargs void
add_office(string new_office, int id, mixed send_to, mixed not_send_to, int domain)
{
    //find_player("aridor")->catch_msg(new_office);
    if (!all_offices)
      all_offices = ([ ]);
    all_offices += ([ new_office:({id, send_to, not_send_to, domain}) ]);
}

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
	  domain_file = "/d/" + C(domains[i]) + "/open/delivery";
	  if (catch(domain_file->load_me()))
	    continue;
	  data = domain_file->query_domain_delivery_offices();
	  domain_file->remove_object();
	  //set_this_player(find_player("aridor"));
	  //dump_array(data);
	  if (!pointerp(data))
	    continue;
	  //dump_array("here");
	  for(j=0;j<sizeof(data);j++)
	    {
		//dump_array("now this");
		if (!pointerp(data[j]))
		  continue;
		//dump_array("and this");
		add_office(data[j][0],data[j][1],data[j][2],data[j][3],dom_num);
	    }
      }
}

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

public nomask string
new_destination(string from_office)
{
    mixed office_data = all_offices[from_office];
    mixed to_office;
    mixed all_to_offices = get_all_to_offices();
    int i;

    if (!office_data)
      return 0; /* Something went wrong, from_office is not officially registered. */

    all_to_offices -= ({ from_office }); /* Obviously :) */
    for(i=0;i<11;i++)
      {
	  to_office = all_to_offices[random(sizeof(all_to_offices))];
	  if (office_data[1] == 0 || member_array(to_office,office_data[1]) >= 0)
	    return to_office; /* Found an office to send to, return it. */
      }
    return 0; /* We couldn't find an office to send to in 10 attempts, aborted. */
}

/* This is the function that tells us how much money we get for a delivered
 * packet. The idea is that depending on the distance between the offices
 * and the amount of money needed to make the journey (ships!) the price will
 * vary. Another factor is the speed of deliverance.
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
	  mini = 8;  maxt = 1800;
	  maxi = 20; mint = 420;
	  /* anything more than 30 minutes means 8cc within a domain */
	  if (packet_age > 1800)
	    return mini;
	  /* anything below than 7 minutes means 20cc within a domain */
	  if (packet_age < 420)
	    return maxi;
      }
    else
      {
	  mini = 50;  maxt = 3600;
	  maxi = 150; mint = 1200;
	  /* anything more than 60 minutes means 50cc within a domain */
	  if (packet_age > 3600)
	    return mini;
	  /* anything below than 20 minutes means 150cc within a domain */
	  if (packet_age < 1200)
	    return maxi;
      }
    /* by default, take a value from a linear regression */
    return maxi - ((maxi-mini) * (packet_age - mint) / (maxt - mint));
}

