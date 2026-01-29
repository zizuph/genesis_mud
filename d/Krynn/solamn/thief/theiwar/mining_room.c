/* created by Aridor 02/09/94
 *
 * Base for the mining area in the Vingaard Mountains.
 * Inherit this file to allow up to 2 metals to be
 * mined in the room. 
 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>

int    num1,  num2;
string what1, what2, my_long_desc = "";

void
reset_mining_room() { }

void
create_mining_room() { }

nomask void
create_thief_room()
{
    set_short("In a cavern");
    set_long("@@my_long");
    
    DARK;
	
    add_item(({"vein","veins"}),"@@which_vein");
    
    create_mining_room();
    
    add_item(({what1 + " veins",what1 + " vein"}),"@@num1_vein");
    add_item(({what2 + " veins",what2 + " vein"}),"@@num2_vein");
}

void
set_my_long(string str)
{
    if (stringp(str))
      {
	  if (strlen(str))
	    my_long_desc = str + " ";
	  else
	    my_long_desc = "";
      }
    else
      my_long_desc = "";
}


nomask string
my_long()
{
    string str = "There are traces of mining everywhere on the walls here. " +
      "You can see some veins of different colors, most of them exploited " +
      "to a large extent already";
    if (num1 || num2)
      str += ". You think there could be ";
    else
      str += ". You don't think there would be anything";
    if (num1)
      str += what1;
    if (num1 && num2)
      str += " and ";
    if (num2)
      str += what2;
    str += " worth mining in the veins here.\n";
    if (TP->query_race() == "dwarf")
      return "You notice excellent craftmanship here in these halls. " +
	"Only the best dwarven craftsmen were able to produce this  " +
	"fine, even and balanced work. " + check_call(my_long_desc + str);
    return check_call(my_long_desc + str);
}

void
init()
{
    ::init();
    ADD("pry_loose","mine");
    ADD("pry_loose","pry");
}

nomask void
reset_thief_room()
{
    num1 = 0;
    num2 = 0;
    reset_mining_room();
}


string
num1_vein()
{
    if (num1)
      return "It is a " + what1 + " vein. You think you might be able to pry " +
	"some of the precious metal loose from the vein.\n";
    return "You find no " + what1 + " vein.\n";
}

string
num2_vein()
{
    if (num2)
      return "It is a " + what2 + " vein. You think you might be able to pry " +
	"some of the precious metal loose from the vein.\n";
    return "You find no " + what2 + " vein.\n";
}

string
which_vein()
{
    if (num1 && num2)
      return "Which vein do you want to look at?\n";
    if (num1)
      return num1_vein();
    if (num2)
      return num2_vein();
    return "You find no real vein that would be worth mining.\n";
}

/* Function:    hook_mining_now
 * Arguments:   who, the player trying to mine
 * Description: A hook to let specific things happen in a room
 *              when a player wants to mine. eg. the dwarf
 *              attacks...
 * Returns:     1 if no mining possible (failure description
 *                                given inside hook_mining_now)
 *              0 if mining will work.
 */
int
hook_mining_now(object who) { return 0; }

int
do_the_mining(string what)
{
    if (hook_mining_now(TP))
      return 0;
    if (random(3))
      {
	  write("You set to work and mine a piece of " + what + " from the vein.\n" +
		"You quickly pick it up.\n");
	  say(QCTNAME(TP) + " gets busy at one of the walls and smiles " +
	      "triumphantly as " + PRONOUN(TP) + " finds something.\n");
	  clone_object(OBJ + what + "piece")->move(TP);
	  return 1;
      }
    else
      {
	  write("You set to work, but you just have no luck.\n");
	  say(QCTNAME(TP) + " gets busy at one of the walls but doesn't " +
	      "seem to succeed with what " + PRONOUN(TP) + " wants to do.\n");
	  return 0;
      }
}

int
pry_loose(string str)
{
    mixed *wep, which;
    
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    NF(capitalize(query_verb()) + " what from where?\n");
    if (!str)
      return 0;
    NF("You set to work, but you just have no luck.\n");
    if (str == what1 + " from vein" || str == what1)
      {
	  if (num1)
	    {
		wep = TP->query_weapon(-1);
		if (wep == ({ }))
		  {
		      write("You set to work but realize you won't succeed with your bare hands.\n");
		      say(QCTNAME(TP) + " gets busy at one of the walls but then gives up again.\n");
		      return 1;
		  }
		which = wep[random(sizeof(wep))];
		which->set_dull(which->query_dull() + random(3));
		num1 -= do_the_mining(what1);
		return 1;
	    }
	  else
	    return 0;
      }
    if (str == what2 + " from vein" || str == what2)
      {
	  if (num2)
	    {
		wep = TP->query_weapon(-1);
		if (wep == ({ }))
		  {
		      write("You set to work but realize you won't succeed with your bare hands.\n");
		      say(QCTNAME(TP) + " gets busy at one of the walls but then gives up again.\n");
		      return 1;
		  }
		which = wep[random(sizeof(wep))];
		which->set_dull(which->query_dull() + random(2));
		num2 -= do_the_mining(what2);
		return 1;
	    }
	  else
	    return 0;
      }
    NF(C(query_verb()) + " what?\n");
    return 0;
}
