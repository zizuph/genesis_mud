/* /d/Genesis/delivery/packet.c
 *
 * This is the standard packet which is taken around between the offices.
 *
 * Created by Aridor, 05/95
 * Last modified by Aridor 06/07/95
 *
 * It is possible to inherit this object and add other features, but it
 * is NOT advised that these objects are of any real use!!
 *
 *
 * The NEW version of the packet puts things into the packet and allows
 * to open them. Things in the packets can include fairly valuable things,
 * a weapon or a gem for example, but may be of a more deadlier nature, too.
 * A poison or some other security mechanism. Most packets will contain
 * completely useless junk, papers or even be empty. Packets which have
 * been opened can of course not be delivered afterwards. Everyone who has
 * not delivered a packet correctly must is then warned not to fail again.
 * If he fails to deliver a total of 3 packets, he cannot deliver any
 * more packets at all until he has paid a fee to reduce his status again.
 */

#include <stdproperties.h>
#include <language.h>
#include <money.h>
#include <macros.h>
#define TP       this_player()
#define ADJ_LIST ({"round","green","blue","red","orange","violet","purple",\
		   "black","white","golden","cube-shaped"})


#pragma save_binary

inherit "/std/object";

private string origin;
/* the office name of the origin office */

private string destination;
/* the office name of the destination office */

private int start_time;
/* The time of creation for this packet */

private int seal = 1;
/* The seal of the packet, 1 = intact, 0 = broken */

private string *possible_content;
/* An array of pathnames of objects that can possibly be inside
 * this packet.
 */

private string the_content;
/* The pathname of the object to clone which will be inside
 * this packet. This is determined right after creation, but
 * after the possible_content has been set, so that the packet
 * can be assigned correct weight and volume values.
 */

/* prototypes */
public nomask string query_origin_string();
public nomask string query_destination_string();



/* Function name: create_packet
 * Description:   Make a packet
 */
void
create_packet()
{
}

/* Function name: create_object
 * Description:   Set up the basic description for a packet. All the specific
 *                setup is done in create_packet
 */
nomask void
create_object()
{
    set_name("packet");
    add_adj(ADJ_LIST[random(sizeof(ADJ_LIST))]);
    set_long("@@seal_broken@@");
    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME, 10000);
    /* set some arbitrary values first, the correct values are set in
     * choose_whats_inside
     */

    create_packet();

    add_prop(OBJ_I_VALUE,      0);
    start_time = time();
}

string
seal_broken()
{
    if (seal)
      return ("This is " + LANG_ADDART(query_adj()) + " packet. It's not " +
	      "very big and you can carry it fairly easily. It has a seal " +
	      "stamped on it, and a label with the origin of the packet " +
	      "saying '" + query_origin_string() + "' and the destination " +
	      "is marked as '" + query_destination_string() + "'.\n");
    return ("All that you hold in your hands is some wrapping paper. You " +
	    "see the remains of a seal which is broken now. This used to " +
	    "be a packet, but it's empty now and it cannot be delivered " +
	    "anymore. You find a label with the origin of the packet saying '" +
	    query_origin_string() + "' and the destination is " +
	    "marked as '" + query_destination_string() + "'.\n");
}

public nomask int
query_seal()
{
    return seal;
}

/* Function name: init
 * Description:   add the open command to the owner of the packet.
 */
void
init()
{
    add_action("open_packet","open");
    ::init();
}
/* Function name: query_origin_string
 * Returns:       The name of the office this packet is coming from.
 */
public nomask string
query_origin_string()
{
    return origin;
}

/* Function name: set_origin_string
 * Arguments:     str, the name of the office
 * Description:   If the packet has no origin yet, set the origin of the packet
 *                to an office.
 */
public nomask void
set_origin_string(string str)
{
    if (!origin)
      origin = str;
}

/* Function name: query_destination_string
 * Returns:       the name of the office the packet is destined for.
 */
public nomask string
query_destination_string()
{
    return destination;
}

/* Function name: query_delivery_packet
 * Returns:       1, this object is actually a delivery packet.
 */
public nomask int
query_delivery_packet()
{
    return 1;
}

/* Function name: set_destination_string
 * Arguments:     str, the name of the destination office
 * Description:   If the packet has no destination yet, set the destination
 *                to an office.
 */
public nomask void
set_destination_string(string str)
{
    if (!destination)
      destination = str;
}

/* Function name: query_start_time_packet
 * Returns:       the time this packet was created.
 */
public nomask int
query_start_time_packet()
{
    return start_time;
}


/* Function_name: choose_whats_inside
 * Description:   Pick one thing from a list to put inside the packet.
 */
static void
choose_whats_inside()
{
    int wght, vol;
    int size = sizeof(possible_content);

    the_content = 0;

    switch(random(7))
      {
	case 0:
	  the_content = "/std/coins";
	  /*MONEY_MAKE(random(30),({"copper","silver"})[random(2)]);*/
	  break;

	case 1:
	  switch(random(4))
	    {
	      case 0:
		the_content = "/d/Genesis/start/human/obj/axe";
		break;
	      case 1:
		the_content = "/d/Genesis/start/human/obj/knife";
		break;
	      case 2:
		the_content = "/d/Genesis/start/human/obj/lsword";
		break;
	      case 3:
		the_content = "/d/Genesis/start/human/obj/ssword";
	    }
	  break;

	case 2:
	case 3:
	  if (possible_content && size)
	    the_content = possible_content[random(size)];
	  break;

	default:
      }
    
    /* Set the correct weight and volume for the packet according
     * to what has been chosen to be inside.
     */
    seteuid(getuid(this_object()));
    the_content->load_me();

    if (the_content)
      {
	  wght = the_content->query_prop(OBJ_I_WEIGHT);
	  vol = the_content->query_prop(OBJ_I_VOLUME);
      }
    else
      {
	  wght = random(1000) + 1500;
	  vol = random(8000) + 3000;
      }
    add_prop(OBJ_I_WEIGHT, wght);
    add_prop(OBJ_I_VOLUME, vol);
}

/* Function name: open_packet
 * Arguments:     what does the player want to open?
 * Description:   Open the packet and see what's inside.
 * Returns:       0/1, depending on whether the command was recognized.
 */
public nomask int
open_packet(string str)
{
    object thing;
    object item;

    notify_fail("Open what?\n");
    if (!parse_command(str,environment(this_player()),"%o",item))
      return 0;
    
    if (!item || item != this_object())
      return 0;

    if (!seal)
      {
	  write("The seal is broken and the packet has been opened already.\n");
	  return 1;
      }

    write("You break the seal of the packet and carefully open it.\n");
    say(QCTNAME(TP) + " gets busy with a packet and opens it.\n");
    seal = 0;
    seteuid(getuid(this_object()));
    if (the_content && stringp(the_content))
      {
	  if (the_content == "/std/coins")
	    thing = MONEY_MAKE(random(30),({"copper","silver"})[random(2)]);
	  else 
	    thing = clone_object(the_content);
      }

    if (!thing || thing->move(environment(this_object())))
      {
	  thing->remove_object();
	  write("The packet is empty!\n");
	  return 1;
      }
    write("Inside the packet, you find " + LANG_ASHORT(thing) + "!\n");

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 5000);
    return 1;
}

/* Function name: add_content
 * Argument:      pathname of the thing to add
 * Description:   Add an array of objects to the list of possible objects to
 *                clone when the packet is opened AND select one of those
 *                objects already.
 */
public nomask void
set_contents(string *str)
{

    if (!possible_content)
      possible_content = ({});

    if (str && sizeof(str))
      possible_content += str;

    choose_whats_inside();
}