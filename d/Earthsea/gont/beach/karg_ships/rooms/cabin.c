#pragma strict_types

#include <macros.h>
#include <const.h>

inherit "/d/Earthsea/gont/beach/karg_ships/std/base_karg_ship";
#define NUM_EUNUCHS 3
object *eunuchs = allocate(NUM_EUNUCHS);
object priestess;

public int map = 1;

string bunk_dependent()
{
  int i;

  switch (query_fire())
    {
    case 0:
      write("The velvet cushions on the bunk are soft to the touch.\n");
      tell_room(QCTNAME(this_player()) + " runs " +
		this_player()->query_possessive() + " hand " +
		"over the velvet cushions on the bunk.\n",
		this_player());
      if (objectp(priestess) && CAN_SEE(priestess, this_player()))
	{
	  switch (this_player()->query_gender())
	    {
	    case G_MALE:
	      priestess->command("$say You'd like that don't you?");
	      this_player()->catch_msg(QCTNAME(priestess) + 
				       " eyes you from head to toe.\n");
	      tell_room(environment(this_player()),
			QCTNAME(priestess) + 
			" eyes " + QTNAME(this_player()) + 
			" from head to toe.\n", this_player());
	      priestess->command("$say You're not good enough, so " +
				 "don't even " +
				 "think about it.");
	      priestess->command("$kick " + 
				 this_player()->query_real_name());
	      break;
	    case G_FEMALE:
	      priestess->command("$peer " +
				 this_player()->query_real_name());
	      priestess->command("$say I'm not into that sort of " +
				 "thing.");
	      break;
	    default:
	      priestess->command("$laugh");
	      priestess->command("$say Sorry, but I think you're " +
				 "missing some equipment.");
	      for (i = 0; i < NUM_EUNUCHS; i++)
		{
		  if (objectp(eunuchs[i]))
		    {
		      priestess->command("$say But I'll let you " +
					 "join them since you're " +
					 "saving me the trouble " +
					 "of making you lose " +
					 "something.");
		      priestess->command("$point eunuchs");
		      break;
		    }
		}
	      break;
	    }
	}
      return "";
    case 1..7:
      return "Not much remains of the cushions that once cover the " +
	"the bunk.\n";
    default:
      return "Exa what? You see nothing but ash and charred objects.\n";
    }
}

string chair_dependent()
{
  switch (query_fire())
    {
    case 0:
      return "The chair is simple and utilitarian.\n";
    case 1..7:
      return "The chair is charred by fire and no longer standing.\n";
    default:
      return "Exa what? You see nothing but ash and charred objects.\n";
    }
}

string wall_dependent()
{
  switch (query_fire())
    {
    case 0:
      return "You see an emblem painted on the wall, nothing more.\n";
    case 1..7:
      return "The emblem and wall has been blackened by fire.\n";
    default:
      return "Exa what? You see nothing but ash and charred objects.\n";
    }
}

string curtain_dependent()
{
  switch (query_fire())
    {
    case 0:
      return "The fine red curtains are draped across the window, " +
	"giving this room a bit of privacy.\n";
    case 1..7:
      return "The curtains are half burnt.\n";
    default:
      return "Exa what? You see nothing but ash and charred objects.\n";
    }
}

string table_dependent()
{
  switch (query_fire())
    {
    case 0:
      if (map)
	{
	  return "There is a curious map on the table top.\n";
	}
      return "The table top is empty.\n";
    case 1..7:
      return "The table is charred by fire and no longer standing.\n";
    default:
      return "Exa what? You see nothing but ash and charred objects.\n";
    }
}

string map_dependent()
{
  if (map)
    {
      return "You look at the map closely and notice that it is a map of " +
	"Gont. A big red X has been crossed on a city on the east side " +
	"of the island. You see two black circles around what looks " +
	"like Gont Port and a village in the mountains. Pointing to the " +
	"circles are four arrows, two from somewhere in the mountains " +
	"and two from somewhere along the coastline.\n";
    }
  return "You find no map.\n";
}

void create_karg_ship_room()
{
  set_short("Inside a cabin");
  set_long("@@fire_dependent@@");
  add_item(({"bunk", "cushions", "cushion"}),
	   "@@bunk_dependent@@");
  add_item("chair",
	   "@@chair_dependent@@");
  add_item(({"emblem", "wall"}),
	   "@@wall_dependent@@");
  add_item("table",
	   "@@table_dependent@@");
  add_item("map",
	   "@@map_dependent@@");
  add_item(({"curtain", "curtains", "window", "windows"}),
	   "@@curtain_dependent@@");
  add_exit("midaft", "out", "@@check_fight@@");
  reset_room();
}

string fire_dependent()
{
  switch(query_fire())
    {
    case 0:
      return "You are in a luxuriously decorated cabin. Red curtains " +
	"made of fine cloth drape across the windows. A bunk " +
	"lined with soft velvet cushions dominates one corner " +
	"of this small cabin. A simple chair and small table " +
	"sit across from the bunk in the other corner. The emblem " +
	"of the Kargad empire is painted on one of the walls.\n";
    case 1..7:
      return "You a in a fire damaged cabin. Half burnt " +
	"curtains drape across the windows. A charred bunk " +
	"dominates on corner of this small cabin. A simple chain " +
	"and small table, both no longer standing, rest across " +
	"from the bunk in the other corner. A blackened emblem " +
	"of the Kargad empire remains on one of the walls.\n";
    default:
      return "The entire room is blackened with fire damage. There " +
	"is nothing but charred remains of once luxurious furnishing " +
	"place in this cabin. Nothing worthwhile remains. From the " +
	"looks of things, this section of the ship will soon collapse " +
	"and the ship will sink any moment now.\n";
    }
}

void reset_room()
{
  int i;
  object here;
  here = this_object();
  if (!fire_damage)
    {
      map = 1;
    }
  if (!objectp(priestess))
    {
      priestess = 
	clone_object("/d/Earthsea/gont/tenalders/npc/kargess_unarmed");
      priestess->move(here);
      priestess->command("$emote ostentaciously strides in, her stiletto " +
			 "heels loudly striking the deck.");
    }
  for (i = 0; i < NUM_EUNUCHS; i++)
    {
      if (!objectp(eunuchs[i]))
	{
	  eunuchs[i] =
	    clone_object("/d/Earthsea/gont/tenalders/npc/eunuch");
	  eunuchs[i]->move(here);
	  priestess->team_join(eunuchs[i]);
	  eunuchs[i]->command("$emote follow the " + priestess->query_short() +
			      " in.");
	}
    }
}

public int check_fight()
{
  int i;
  object tp = this_player();

  if (priestess->query_attack() == tp)
    {
      if (!random(5))
	{
	  return 0;
	}
      switch(random(4))
	{
	case 0:
	  priestess->command("$say Think you can attack me and still " +
			     "leave this ship alive?");
	  priestess->command("$say Think again!");
	  break;
	case 1:
	  priestess->command("$say Not so fast!");
	  break;
	case 2:
	  priestess->command("$cackle");
	  priestess->command("$say You can't run... you can't hide... just "+
			     "give up and die.");
	  break;
	default:
	  priestess->command("$say Oh no, I'm not done with you yet.");
	  break;
	}
      tp->catch_msg(QCTNAME(priestess) + " steps in between you and " +
		    "the door preventing you from running away.\n");
      tell_room(environment(tp), QCTNAME(priestess) + " steps in between " +
		QTNAME(tp) + " and the door preventing " +
		tp->query_objective() + " from running away.\n",
		tp);
      return 1;
    }
  return 0;
}

void add_fire()
{
  ::add_fire();
  if (fire_damage)
    {
      map = 0;
    }
}

int get_map(string str)
{
  object the_map, tp = this_player();

  if (str == "map")
    {
      if (map)
	{
	  if (objectp(priestess) &&
	      CAN_SEE(priestess, tp))
	    {
	      tp->catch_msg("You try to take the map from the table but " +
			    QTPNAME(priestess) + " arm slaps your hand away " +
			    "just a the last moment.\n");
	      priestess->command("$say Oh no you don't!");
	      priestess->command("$kill " + tp->query_real_name());
	      return 1;
	    }
	  map = 0;
	  the_map = clone_object("/d/Earthsea/gont/beach/karg_ships/obj/map");
	  the_map->move(tp, 1);
	  write("You take the map from the table.\n");
	  tell_room(environment(tp),
		    QCTNAME(tp) + " takes something from the table.\n",
		    tp);
	  return 1;
	}
      write("Get what?\n");
      return 1;
    }
  return 0;
}

void init()
{
  ::init();
  add_action(get_map, "get");
  add_action(get_map, "take");
}
