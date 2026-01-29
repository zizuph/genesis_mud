// /d/Avenir/common/outpost/gaol_cell.c
// This is where people who start fights are held.
// The call_for_guards function is called by npcs that are attacked.
// see /d/Avenir/common/outpost/mon/call_for_help.

inherit "/d/Avenir/common/outpost/fort_base";
#include "/d/Avenir/common/outpost/outpost.h"
#include "/sys/stdproperties.h"

#define GUARD       OUTPOST + "mon/punisher"
// same paralyze object as is used in the bazaar pillory.
#define PARA_OBJ    BAZAAR + "Obj/misc/freeze"
// This is 4 minutes of paralyze. It wears off but they should
// still be in jail for another 6-10 minutes.
#define PARA_TIME   240
#define LEAVE_MSG   "through a secret passage"
#define IMPRISONED  "_free_at_last"
#define SEE_EAST   ({ OUTPOST + "gaol_main"})

// prototypes
void cfg1(object prisoner);

// Global vars
mapping punishers = ([]), pobjs = ([]);

string 
east_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_EAST); i++)
    if((room = find_object(SEE_EAST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return "Through the bars of your cell you can see "+ 
       COMPOSITE_LIVE(live) +" in the center of the gaol. ";
  }
  return "It looks like the gaol is empty except for you. ";
}


public int
exit_check(void)
{
    object pobj = pobjs[this_player()];
    
    if (pobj && present(pobj, this_player()))
    {
	write("You are locked inside the gaol cell and cannot leave!\n");
	return 1;
    }
	
	if (!this_player()->query_prop(IMPRISONED))
    {
    write("You are locked inside the gaol cell and cannot leave.\n");
	return 1;
    }
	// Must have the prop in order to leave.
	write("The door swings open, allowing you to leave.\n");
    return 0;
}

void
create_fort_room()
{
    setuid();
    seteuid(getuid());
	
    set_short("the gaol cell in Fort Sybarus");
    set_long("This is one of the gaol cells of Fort Sybarus. "
      +"It is deep underground, beneath the north tower. "
      +"The walls are polished smooth, with a high enough gloss "
      +"to reflect the light from the crystal and copper lamps "
      +"hung high on the east wall. This cell is spartan, with "
      +"no bed or chair, just cold, bare floor. You get the "
      +"impression that you aren't supposed to make yourself "
      +"comfortable here. "	  
      +"@@east_view@@\n");

    // 'guests' wouldn't be able to defend themselves, as they're paralyzed
    // so no attacking in this room.	
    add_prop(ROOM_M_NO_ATTACK, "That doesn't seem possible here.\n");
	// No escaping via teleporting.
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_M_NO_STEAL, "On second thought...no.\n");
    // There is nowhere to hide here.
    add_prop(ROOM_I_HIDE, -1);
    add_prop(OBJ_S_WIZINFO, "This is the jail where people who have "+
        "attacked the guards are meant to cool their heels for 10 to "+
        "15 minutes. They are paralyzed for the first 4 minutes and "+
        "then they can do things. No one in this room can leave "+
		"via the exit unless they have the "+ IMPRISONED +
        " property added to them.\n");		
    add_exit("gaol_main", "east", exit_check);
	add_exit_views();
    add_fort_room();

    add_item(({"gaol", "main gaol", "cell", "gaol cell", "jail"}),
    "@@west_view@@\n");	
}

public void create_stun(object prisoner)
{
    object pobj = clone_object(PARA_OBJ);
    pobj->set_stop_verb("");
    pobj->set_remove_time(PARA_TIME);
    pobj->set_exit_cmds(({OUTPOST +"gaol_cell", TO}));
    pobj->set_stop_object(TO);
    pobj->set_stop_fun("release_prisoner");
    pobj->set_fastened(0);
    pobj->set_fail_message("You are held by a troloby punisher. "+
        "You cannot do that.\n");
    pobj->move(prisoner, 1);
    pobjs[prisoner] = pobj;
}

public void
release_prisoner(object prisoner)
{
    // Clean up punisher list.
    m_delkey(punishers, 0);
    object punisher,pobj;
    if (!prisoner)
	{
		return;
	}
    if (!punishers[prisoner])
    {
        punisher = clone_object(GUARD);
        punishers[prisoner] = punisher;
        punisher->move(TO);
    }
    // Now they can leave the room.	This prop has to be 
	// added to the players or they can't leave.
	prisoner->add_prop(IMPRISONED, 1);    
    punisher->command("emote unlocks the door of the gaol cell.");
    punisher->command("say to "+ prisoner->query_name() +" You're free "+
       "to go. No more fighting, you hear?");
       
    pobj = pobjs[prisoner];
    if (pobj && present(pobj, prisoner))	   
    {
	    pobj->remove_object();    
        m_delkey(pobjs, pobj);
    }

	punisher->command("emote leaves east.");
	punisher->remove_object();
    m_delkey(punishers, prisoner);
}

public void
cfg3(object prisoner)
{
    object punisher = punishers[prisoner];
    object pobj = pobjs[prisoner];
	
    if (!prisoner)
	{
		return;
	}
    if (!pobj)
    {
        create_stun(prisoner);
    }    
	pobj->set_fail_message("You are gagged and locked in the gaol." +
		  " You cannot do that.\n");	
    tell_room(TO, QCTNAME(punisher) + " drops " + QTNAME(prisoner) +
        " in the gaol cell and locks it.\n", prisoner);
	prisoner->catch_msg(QCTNAME(punisher) + " drops you into a " +
	    "gaol cell and locks it.\n");
    if (punisher)
    {
    punisher->command("say You will cool your heels here for 10 to "+
        "15 minutes, and during that time you can think about how "+
        "stupid you were to start a fight here.");
    punisher->command("emote stands just inside the cell, watching "+
        "you impassively.");
    }
    // when the paralyze wears off they can't leave unless they quit
    // or they remain until the 10-15 minute timer is up.	
    float time = (itof(600 + random(300)));
	set_alarm(time, 0.0, &release_prisoner(prisoner));
}


public void
cfg2(object prisoner)
{
    object punisher = punishers[prisoner];
    
    if (!prisoner)
	{
		return;
	}
    if (!punisher)
    {
        cfg1(prisoner);
		return;
    }
	
	prisoner->catch_msg("The troloby punisher throws you "+
         "over its shoulder and carries you off to gaol.\n");
	tell_room(environment(punisher), "The troloby punisher tosses " 
        + QTNAME(prisoner) +" over its shoulder and leaves.\n", prisoner);
    punisher->move_living(LEAVE_MSG, TO);
	prisoner->move_living("M", TO, 1, 0);
    set_alarm(5.0, 0.0, &cfg3(prisoner));
}

public void
cfg1(object prisoner)
{
    int i;
	string str;

    if (!prisoner) 
    {
	    return;
    }

    // Are they still in the Fort?
    str = file_name(environment(prisoner));
    if (!wildmatch("/d/Avenir/common/outpost/*", str))
    {
	    return;
    }
	object pobj, punisher;
    
    if (!pobjs[prisoner])
    {
        create_stun(prisoner);
    }

    if (!punisher)
    {
        punisher = clone_object(GUARD);
        punishers[prisoner] = punisher;
        punisher->move(environment(prisoner));

	if (environment(punisher) != environment(prisoner))
		punisher->move_living(LEAVE_MSG, environment(prisoner)); 	
        punisher->command("emote strides in and assesses the situation "+
            "with a glance.");	
    	punisher->command("growl at " + prisoner->query_real_name());		
	    punisher->command("say We don't allow fighting here at Fort Sybarus.");
        punisher->command("say We cannot afford the distraction with our "+
	        "enemies amassing just across the chasm.");
	    punisher->command("say to "+ prisoner->query_real_name() +
           " You'll be coming with me. Idiot.");
        set_alarm(3.0, 0.0, &cfg2(prisoner));
		
    }
	
}


public int
call_for_guards(object prisoner)
{
    set_alarm(4.0, 0.0, &cfg1(prisoner));
    return 1;
}



/*
 * Function name: enter_inv
 * Description  : This function is called each time an object enters the
 *                inventory of this object. If you mask it, be sure that
 *                you _always_ call the ::enter_inv(ob, old) function.
 * Arguments    : object ob  - the object entering our inventory.
 *                object old - wherever 'ob' came from. This can be 0.
 */
void enter_inv(object ob, object old)
{
    ::enter_inv();
    // Does player have the get out of jail prop from a 
    // previous offence? Remove it so they can't walk out 
	// until the release_prisoner is called. 
    if (ob->query_prop(IMPRISONED))
	    ob->remove_prop(IMPRISONED);
}
