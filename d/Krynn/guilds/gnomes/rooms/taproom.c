/* Created by Dajala
 * Here members can refill their supplies of wood, water etc for the 
 * modules.
 */

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <macros.h>

inherit "/d/Krynn/std/room";

int fish;  /* Small fish stuck in the tap? */
object stuck; /* Who's stuck in the tap? */

void
create_room()
{
    fish = 0;
    set_short("A small cave");

    set_long("The cave narrows here. Inventors come here to replenish "
	+ "their supplies. You see a tap and a large opaque jar with a "
	+ "small label next to them and a pile of wood.\n");

    add_exit(ROOMS + "workshop", "south", "@@stuck_check@@");
    INSIDE
    LIGHT

    add_item("label", "You can read it.\n");
    add_item(({"jar", "opaque jar", "large jar", "large opaque jar"}),
    	"You peek inside and see a white powdery substance.\n");
    add_item(({"substance", "white substance", "white powdery substance",
    	"powdery substance"}), "It seems to be ordinary flour.\n");
    
    add_cmd_item("label", "read",
	"The label reads:\nHighly purified spring water. You may "
	+ "'drink' some if you wish. Inventors can 'refill' their "
	+ "gizmo with technically refined flour or water here.\n");
    add_item(({"wood", "pile"}), "This pile of wood is for use with the steamengine-"
	+ "module. Why don't you 'grab' some?\n");
    add_item("tap", "You can get water from it. There's a label next "
	+ "to it.\n");
}

void
init()
{
	::init();
	ADA("refill");
	ADA("drink");
	ADA("grab");
	ADA("clear");
	ADA("pull");
}

int
flag(int number)
{
	int *flags;
	flags = (P("k_gizmo", TP)->query_modules());
	return (flags[number]);
}

int person_present()
{
  if(present(stuck, this_object()))
    return 1;
  return 0;
}



int
refill(string str)
{
	string *talk;
	
	NF("Refill what?\n");
	if(!str)
		return 0;
	if(!(talk = explode(str, " ")))
		return 0;
	if(talk[0] != "gizmo")
		return 0;
	NF("Refill gizmo with what?\n");
	if(sizeof(talk) < 3)
		return 0;
	if(talk[1] != "with" || (talk[2] != "flour" && talk[2] != "water"))
		return 0;

	NF("You don't have a gizmo.\n");
	if(!P("k_gizmo", TP))
		return 0;

	if(talk[2] == "water")
	{
		NF("Get yourself a waterdispenser first.\n");
		if(!flag(2))
			return 0;

		NF("Somebody is holding a finger into the tap.\n");
		if(stuck && person_present())
			return 0;

		write("You open the tap to refill your gizmo.\n");
		say(QCTNAME(TP) + " opens the tap.\n");

		set_alarm(4.0, -1.0, "tap2", TP);
		return 1;
	}
	write("You get yourself enough flour from the large jar to "
		+ "fill your gizmo.\n");
	say(QCTNAME(TP) + " helps " + OBJECTIVE(TP) + "self with "
		+ "some flour from a large jar.\n");
	P("k_gizmo", TP)->refill_flour(30);
	return 1;
}

int
fish_check(object player)
{
	if(!random(4) || fish == 1)
	{
		player->catch_msg("But it doesn't seem to work.\n");
		tell_room(TO, "But doesn't get any water.\n", player);
		if(fish == 0)
			remove_item("tap");
			add_item("tap", "An ordinary tap. But something "
				+ "seems to be blocking it. You could try "
				+ "to clear it.\n");
		fish = 1;
		return 1;
	}
	return 0;
}

void
tap2(object player)
{       
	object gizmo;

	gizmo = P("k_gizmo", player);
	if(fish_check(player))
		return;
	if((gizmo->check_water()) == 40)
	{
		player->catch_msg("But don't get any more water into it.\n");
		tell_room(TO, "But it's already full.\n", player);
		return;
	}
	player->catch_msg("And refill your gizmo.\n");
	tell_room(TO, "And refills " + POSSESSIVE(player) + " gizmo.\n"
		, player);
	gizmo->refill_water(40);
	set_alarm(2.0, -1.0, "tap_close", player);
}

int
drink(string str)
{
	NF("Drink what?\n");
	if(str != "from tap" && str != "water")
		return 0;
	NF("You cannot! Somebody is holding a finger into the tap.\n");
	if(stuck && person_present())
		return 0;
	write("You open the tap.\n");
	say(QCTNAME(TP) + " opens the tap.\n");
	if(fish_check(TP))
		return 1;

   write("You drink some water. Its taste strongly reminds you of fish.\n");
	say(QCTNAME(TP)+" drinks some fresh water.\n");
	set_alarm(2.0, -1.0, "tap_close", TP);
	return 1;
}

void
tap_close(object player)
{
  if(P(player, TO))
{
      player->catch_msg("You close the tap again.\n");
	tell_room(TO, C(PRONOUN(player)) + " then closes the tap again.\n"
		, player);
}
else
   {
    tell_room(TO, "An angry gnome runs by and closes the running tap again. "  
          + "He then decides to talk to " + lower_case(QCTNAME(player))
        + " about the incident and walks off searching for " + OBJECTIVE(player)
        + ".\n");
      player->catch_msg("A gnome runs up to you and asks you politely to "
            + "close the tap after refilling the gizmo before you leave the "
          + "room the next time you use it.\nHe then walks off.\n");
   }
}

int
grab(string str)
{
	object gizmo;

	NF("Grab what?\n");
	if(str != "wood")
		return 0;

	NF("A gnome steps in front of you and slaps your hand. "
		+ "'Guildmembers only', he says.\n");
	if(!GMEMBER(TP))
		return 0;

	NF("You need a gizmo to store the wood in.\n");
	if(!(gizmo = P("k_gizmo", TP)))
		return 0;

	NF("Get yourself a steamengine first.\n");
	if(!flag(3))
		return 0;

	NF("The storage chamber for the steamengine is already well filled.\n");
	if((gizmo->check_wood()) == 14)
		return 0;
	
	write("You grab some wood and refill the little storage chamber "
		+ "inside your gizmo.\n");
	say(QCTNAME(TP) + " grabs some wood and stores it in "
		+ POSSESSIVE(TP) + " gizmo.\n");
	gizmo->set_wood(14);
	return 1;
}

int
clear(string str)
{
    if(!fish)
        return 0;
    NF("Clear what?\n");
    if(str != "tap")
        return 0;

    if(stuck && person_present())
    {
        if(stuck == TP)
        {
            write("You already attempted that endeavor, and look where it got you, stuck!\n");
            return 1;
        }
        else
        {
            write("It seems someone else is already attempting to do that right now.\n");
            return 1;
        }
    }
    write("You put your middle finger into the tap and....\n");
    say(QCTNAME(TP) + " puts " + POSSESSIVE(TP) + " finger into the tap "
		+ "and...\n");

    set_alarm(4.0, -1.0, "clear2", TP);
    return 1;
}

string stuck_descr()
{
  if(stuck && person_present())
  {
    if(stuck == TP)
    {
      return " You have your finger stuck in it.";
    }
    else
    {
      return " The "+stuck->query_nonmet_name()+" has "+
             POSSESSIVE(stuck)+ " finger stuck in the tap.";
    }
  }
  return "";
}

void
clear2(object player)
{
	player->catch_msg("... get stuck!!\n");
	tell_room(TO, "... gets stuck!!\n", player);
	player->add_prop(LIVE_S_EXTRA_SHORT, " with " + POSSESSIVE(player)
		+ " finger stuck in the tap");
	stuck = player;
	remove_item("tap");
	add_item("tap", "An ordinary tap.@@stuck_descr@@\n");
}

int
stuck_check()
{
	if(stuck != TP)
		return 0;
	write("Your finger is still stuck in the tap!\n");
	say(QCTNAME(TP) + " tried to go south but still holds on firm to " 
		+ "the tap with " + POSSESSIVE(TP) + " finger.\n");
	return 1;
}

int
pull(string str)
{
	if(stuck != TP)
		return 0;
	NF("Pull what?\n");
	if(str != "free" && str != "finger" && str != "free from tap" && str != "finger from tap")
		return 0;

	write("You pull with all your strength and ...\n");
	say(QCTNAME(TP) + " tries to pull " + POSSESSIVE(TP) + " out "
		+ "from the tap ...\n");

	set_alarm(4.0, -1.0, "pull2", TP);
	return 1;
}

void
pull2(object player)
{
	player->catch_msg("... and come free!\n");
	tell_room(TO, " ... and comes free!\n", player);
	tell_room(TO, "Water is now flowing from the tap.\n");
	set_alarm(1.0, -1.0, "tap_close", player);
	player->remove_prop(LIVE_S_EXTRA_SHORT);
	stuck = 0;
	tell_room(TO, "A living fish falls from the tap!\n");
	fish = 0;
	clone_object(GOBJ + "obj/fish.c")->move(TO);
	set_alarm(240.0, -1.0, "remove_fish");
	remove_item("tap");
	add_item("tap", "You can get water from it. There's a label next "
		+ "to it.\n");
}

void
remove_fish()
{
	object fish;

	if(!(fish = P("tap_fish", TO)))
		return;
	fish->remove_fish();
}
