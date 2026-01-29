/*
 * housebase.c
 *
 * A base file for houses in Genesis towns
 *
 * Varian - Jan 2020
 *
 */

#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/common/lib/room_tell";

#include "defs.h"
#include <macros.h>

string junkyard_room;

string house_name;

void set_junkyard_room(string room)
{
    junkyard_room = room;
}

string get_junkyard_room()
{
    return junkyard_room;
}

void set_house_name(string name)
{
    house_name = name;
    HOUSE_MANAGER->register_room(name, file_name(this_object()));
}

string get_house_name()
{
    return house_name;
}


public void hook_notify_item_returned(object ob, object to)
{
    tell_room(this_object(), "A maid picks up the " + ob->short() +
       " and hands it to " + QTNAME(to) + ".\n", to);    
    to->catch_msg("A maid picks up the " + ob->short() +
       " and hands it back to you.\n");
}

public void hook_notify_item_tossed(object ob, object junkyard)
{
    tell_room(this_object(), "A maid picks up the " + ob->short() +
       " and tosses it outside.\n");
    junkyard->tell_room("The door opens, and an item is thrown out it.\n");

}

public void hook_notify_item_destroyed(object ob)
{
    // We could not move the item, what to do here?
    this_object()->tell_room("A maid zaps the " + ob->short() +
       " out of existance.\n");
}

public void hook_notify_player_removed(object ob)
{
    tell_room(this_object(), "A maid picks up the " + QTNAME(ob) +
       " and removes them from the premises.\n", ob);
    object dest = find_object(junkyard_room);
    if (!objectp(dest))
    {
        // Room not loaded, try to load it.
        junkyard_room->teleledningsanka();
        dest = find_object(junkyard_room);
    }
    ob->catch_msg("You are thrown out of the house.\n");
    dest->tell_room("The door opens, and " + QTNAME(ob) + 
        " is thrown out it.\n");
}

public int can_enter_house(object player)
{
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
  
    if (mappingp(details))
    {
        if (details[KEY_OWNER] == player->query_real_name())
	    {
		    return 1;
        }
		object leader = player->query_leader();
        if (leader && details[KEY_OWNER] == leader->query_real_name())
		{
		    return 1;
		}
        if (member_array(player->query_real_name(), details[KEY_INVITED]) != -1)
		{
			return 1;
		}
    }
    if (player->query_wiz_level())
    {
        write("You should be blocked, but as a wizard you have access.\n");
        return 1;
    }
    return 0;
}

public mixed block_teleport()
{
    if (can_enter_house(this_player()))
    {
        return 0;
    }
    return "That location is private property.\n";
}

public void maybe_move_player(object ob, object from)
{
    if (!objectp(ob))
        return;
    
    string* known_houses = HOUSE_MANAGER->get_registered_rooms(house_name);
    if (from && member_array(file_name(from), known_houses) != -1)
    {
        return;
    }
    if (!can_enter_house(ob))
    {
        HOUSE_MANAGER->ejection_log(ob->query_real_name(),
            file_name(this_object()));
        hook_notify_player_removed(ob);
        object dest = find_object(junkyard_room);
        if (!objectp(dest))
        {
            // Room not loaded, try to load it.
            junkyard_room->teleledningsanka();
            dest = find_object(junkyard_room);
        }
        ob->move(dest, 1);
    }
}

public int is_owner(object player)
{
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
  
    if (mappingp(details))
    {
        if (details[KEY_OWNER] == player->query_real_name())
	    {
		    return 1;
        }
    }
    return 0;
}

public void maybe_move_item(object ob, object from)
{
    if (!objectp(ob))
        return;
    if (interactive(ob))
        return;
    if (environment(ob) != this_object())
        return;
    if (ob->query_prop(ALLOWED_IN_HOUSE))
        return;
    if (objectp(from) && interactive(from) 
        && environment(from) == this_object())
    {
        hook_notify_item_returned(ob, from);
        if (!ob->move(from))
        {
            return;
        }
    }
    if (environment(ob) != from)
    {
        object dest = find_object(junkyard_room);
        if (!objectp(dest))
        {
            // Room not loaded, try to load it.
            junkyard_room->teleledningsanka();
            dest = find_object(junkyard_room);
        }
        if (!ob->move(dest))
        {
            hook_notify_item_tossed(ob, dest);
        }
        else
        {
            // We could not move the item, what to do here?
            hook_notify_item_destroyed(ob);
            ob->remove_object();
        }
    }   
}

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (junkyard_room && objectp(from))
    {
        set_alarm(itof(random(10)), 0.0, &maybe_move_item(ob, from));
    }
    if (junkyard_room && interactive(ob))
    {        
        set_alarm(0.1, 0.0, &maybe_move_player(ob, from));
    }
    if (interactive(ob) && !is_owner(ob) &&
      ob->query_default_start_location() == file_name(this_object()))
    {
	    ob->set_default_start_location(ob->query_def_start());
    }
}

public int do_start(string str)
{
  notify_fail("Start where?");
  if (str != "here")
  {
      return 0;
  }
  object who = this_player();
  if (!is_owner(who))
  {
      write("Only the owner is allowed to start in the house.\n");
      return 1;
  }
  
  if (who->set_default_start_location(file_name(this_object())))
  {
    write("Okay, you will start here whenever you wake up.\n");
  }
  else
  {
    write("Your start location could not be set, contact a wizard.\n");
  }
  return 1;
}

