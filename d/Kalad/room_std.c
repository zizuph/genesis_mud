/*******************************************************
 *   To be inherited by all rooms in Kalad
 *   By Ashbless
 *   Modified 8/26/96
 *   Added pragmas and using the new clock, Fysix, Nov 1997
 *******************************************************/
#pragma save_binary
#pragma strict_types

inherit "/d/Kalad/local_events";
inherit "/d/Kalad/lib/time";

#include <stdproperties.h>
#include "/d/Kalad/sys/files.h"
#include "/d/Kalad/sys/properties.h"
#include "/d/Kalad/sys/time.h"
#include "/d/Kalad/sys/macros.h"
#include "/d/Kalad/sys/areas.h"

/***************************************************************
 *   Globals
 ***************************************************************/
              /*0=can't hear it, 1=faintly,2=normal,3=loud,4=def*/
static int     hear_bell;
static int     in_kabal, allow_npc, open, close, max;
static string  day_desc, night_desc, closed, dirty_msg, district;
static mapping dirty_exits = ([]);

/* Is this necessary?                                  */
object this_room() { return this_object(); }

void
init()
{
   ::init();
   init_time();
}

/*******************************************************
 *   Function: query_dirty_exits()
 *
 *   Return the dirtiness value for each exit
 *******************************************************/
public mapping
query_dirty_exits() { return dirty_exits + ([]); }

#if 0 /* I fail to see the points of this */
/*******************************************************
 *   Function: list_exits()
 *   Arguments: object caller - the room to list exits for
 *
 *   return a list of exits for a given room, along with
 *   the fatigue and dirtiness of eacj exit.
 *******************************************************/
public string
list_exits(object caller)
{
    string str, dirstr, deststr, funstr;
    int n, i;
    int *dval, *tval;
    mixed *elist;

    if (!caller)
      caller = TO;
    str = "";

    if (sizeof(elist = caller->query_exit()))
    {
      i = 0;
      for (n=0;n < sizeof(elist);n=n+3)
      {
          dirstr = elist[n+1];
          deststr = elist[n];
          dval = caller->query_dirty_exits();
          tval = caller->query_tired_exits();

          str = str + dirstr + ": " + deststr + "\n";
          str = str + "       -tired: " + tval[i];
          if (function_exists("query_dirty_exits",caller))
            str = str + "       -dirty: " + dval[i] + "\n";
          else
            str = str + "       -dirty: 0\n";

          if (elist[n+2])
          {
            funstr = elist[n+2];
            str = str + "       -exit function: " + funstr + "\n";
          }
          i++;
      }
    }

    return str;
}

/*******************************************************
 *   Function: stat_object()
 *
 *   When someone stats our rooms, they also see
 *   the fatigue and dirtiness for each exit.
 *******************************************************/
public string
stat_object()
{
    string str;

    str = ::stat_object();

    str = str + list_exits(TO);
    return str;
}
#endif

/*******************************************************
 *   Function: sign()
 *
 *   Return the string to be read on a sign.
 *   To be redefined in the individual room.
 *   If not redefined, returns "Read what?\n".
 *******************************************************/
public string
sign()
{
    return ("Read what?\n");
}

/*******************************************************
 *   Function: read_sign()
 *
 *   Call this function from add_action and define a
 *   string sign() function for an easy sign.
 *******************************************************/
public int
read_sign(string str)
{
    notify_fail("Read what?\n");
    if (!str || str != "sign")
      return 0;

    write(sign());
    return 1;
}

/*******************************************************
 *   Function: add_exit()
 *
 *   Add dirtiness to exits in our rooms.
 *   This will be replaced soon.
 *******************************************************/
public varargs int
add_exit(string place, string cmd, mixed efunc, mixed tired, mixed dirty)
{
    int rval = ::add_exit(place, cmd, efunc, tired, 0);

    if (rval)
    {
	if (dirty < 0)
	{
	    dirty = 0;
	}
	else if (dirty == 0)
	{
	    dirty = 1;
	}
	
	dirty_exits[cmd] = dirty;
    }
    return rval;
}

public int
unq_move(string str)
{
    int	dirty, prop;
    int rval = ::unq_move(str);
    object *ob;

    if (rval)
    {
	dirty = check_call(dirty_exits[query_verb()]);
	if (dirty > 0)
	{
	    prop = this_player()->query_prop(LIVE_I_DIRTY);
	    if (prop)
	    {
		this_player()->add_prop(LIVE_I_DIRTY, prop + dirty);
	    }
	    else
	    {
		this_player()->add_prop(LIVE_I_DIRTY, dirty);
	    }

	    ob = filter(all_inventory(this_player()), 
		&operator(==)(DIRTY_OBJECT_ID) @ &->query_name());

	    if (!sizeof(ob))
	    {
		clone_object(DIRTY_OBJECT)->move(this_player(), 1);
	    }
	}
    }
    return rval;
}

#if 0 /* Didn't see any of the following three called in any files */
/****************************************************************
 * Function: is_clean()
 *
 * Return true if player's dirty level is within the max allowed
 * for the shop.
 ****************************************************************/
public int
is_clean()
{
    if (!max || max < 0)
      return 1; /*no dirtiness check*/

    if (TP->query_prop(LIVE_I_DIRTY) > max)
    {
      if (dirty_msg)       /*if fail message defined*/
        write(dirty_msg);
      else             /*otherwise use default message*/
      {
        write("As you start to enter, you're stopped at the door " +
          "and sent back out, because you're too dirty.\n");
      }
      return 0; /*too dirty to enter*/
    }

    else
      return 1;
}

/****************************************************************
 * Function: setup_shop()
 * Arguments: int npc - true if npcs can enter. Default 0.
 *            int open_time - hour shop opens. Default 7am.
 *            int close_time - hour shop closes. Default 10pm.
 *            string closed_str - string someone sees if they
 *               try to enter when closed.
 *            int max_dirty - how dirty you can be and still enter.
 *               Default is 39.
 *            string dirty_str - string someone sees if they are too
 *               dirty to enter. You must set this in your room.
 *
 * Call this to set the rules for entering your shop. You must
 * call shop() as the exit function in the exit leading to your shop
 * for these rules to be enforced.
 ****************************************************************/
public void
setup_shop(int npc=0,int open_time=7, int close_time=22,
    string closed_str="The shop is closed.\n",int max_dirty=39,string dirty_str = "Must have a default here")
{
    allow_npc = npc;
    closed = closed_str;
    open = open_time;
    close = close_time;
    dirty_msg = dirty_str;
    max = max_dirty;
}

/****************************************************************
 * function: shop()
 *
 * description: This is to be called from your exit function in
 *              exits leading to a shop. We don't allow npcs to enter
 *              if allow_npc is false and don't allow entrance during
 *              closed hours or if the player is too dirty.
 ****************************************************************/
public int
shop()
{
    // if allow_npc is false - don't let npcs in
    if (!allow_npc& TP->query_npc() )
    {
      return 2; /*let the npc try another exit*/
    }
     /*both times must be properly defined or else its always open*/
    if (!open || !close || open < 1 || open > 24 || close < 1 || close > 24 || open == close)
    {
      if (is_clean())
        return 0;
      else
        return 1;
    }

    if(open < close)
      if(TIME >= open && TIME < close)
      {
        if (is_clean())
          return 0;
        else
          return 1;
      }
      else
      {
        if(!closed)
          write("The door is locked and barred.\n");
        else
          write(closed);
        return 1;
      }

    else
      if (TIME < close || TIME >= open)
      {
        if(is_clean())
          return 0;
        else
          return 1;
      }
      else
      {
        if(!closed)
          write("The door is locked and barred.\n");
        else
          write(closed);
        return 1;
      }
  
}
#endif

/****************************************************************
 * Function: set_time_desc()
 * Args: day_desc   - the daytime description
 *       night_desc - the nighttime description
 *
 * Set the day and night time descriptions for your room.
 ****************************************************************/
public void
set_time_desc(string day_str,string night_str)
{
      day_desc = day_str;

      night_desc = night_str;
}

/****************************************************************
 * Function: query_time_desc()
 *
 * Will return the time description for the room. If no time
 * description has been set and the room is an outdoor room in
 * Kabal, the default description will be used, unless you set
 * the property ROOM_NO_TIME_DESC in the room. For any other room,
 * without a description set, no description will be used. Got it?
 ****************************************************************/
public string
query_time_desc()
{
    if (TO->query_prop(ROOM_NO_TIME_DESC))
      return "";

    if(DAY)
      if(day_desc && day_desc != "")
        return day_desc;
      else
       if (!TO->query_prop(ROOM_I_INSIDE) &&
           IN_CITY(this_object()))
          return "The streets are quite crowded at the moment.\n";
        else
          return "";

    else
      if(night_desc && night_desc != "")
        return night_desc;
      else
        if (!TO->query_prop(ROOM_I_INSIDE) &&
            IN_CITY(this_object()))
          return "The streets are rather deserted at the moment.\n";
        else
          return "";
}

/****************************************************************
 * Function: long()
 *
 * This will append the time desciption of the room to the long
 * description set with set_long(), unless no long has been set.
 *
 * Note: This added time description will show up only when people
 *       look at the room but will not show up when query_long()
 *       is called.
 ****************************************************************/
varargs public mixed
long(string str, object for_obj)
{
    mixed tmp, rval;

    if (str)
    {
	return ::long(str, for_obj);
    }

    tmp = obj_long;
    obj_long += query_time_desc();
    rval = ::long(str, for_obj);
    obj_long = tmp;

    return rval;
}

#if 0 /* This just seems pointless */
/****************************************************************
 * Function: check_set_hide()
 *
 * If the room is outdoors in the city, we want to change how hard
 * it is to hide, between day and night. It should be easier to
 * hide during the day, because the streets will be crowded. Since
 * Kalad (and Genesis with the exception of Middle Earth) does
 * not get dark at night, there will be no bonus from darkness.
 * However, the streets will be deserted so hiding won't be as easy
 * as in the daytime (busy hours).
 *
 * Note: We only change the hiding value for the room if it was
 *       set to the default value. If it has been changed by the
 *       creator of the room then we won't touch it. So if you
 *       want an outdoor room in the city to have a value of 10,
 *       set it to something close like 9 or 11, instead.
 *
 * Note: There is probably a more efficient way to do this. Maybe
 *       we'll rewrite this later.
 ****************************************************************/
public void
check_set_hide()
{
    if (!TO->query_prop(ROOM_I_INSIDE))        /*is it outside?           */
    if (IN_CITY(this_object()))  // Is this room in the city?
        if(TO->query_prop(ROOM_I_HIDE) == 10)  /*is it set at the default?*/
          change_hide();

    return; /*if the prop has been changed in the room object then we won't 
                  change it. Only if its at the default value of 10.      */
}

/**************************************************************
 *   Function: change_hide()
 *
 *   Make it easier to hide during the day in an outdoor room
 *   in the city. Change it back at night when its less crowded.
 **************************************************************/
public void
change_hide()
{
    if (DAY)
      TO->add_prop(ROOM_I_HIDE,5);   /*easy to hide - crowded streets */
    else
      TO->add_prop(ROOM_I_HIDE,10);   /*back to normal - less crowded */

      /* check every hour for change in day-night */
    set_alarm(180.0,0.0,"change_hide");
}
#endif

/**************************************************************
 *   Function: query_in_kabal()
 *
 *   Returns true if the calling room is in the city of Kabal.
 *   This is a direct function of the directory the file for the
 *   room is in. So please keep any areas in the city within
 *   the correct subdirectories or else add yours to this code.
 *
 *   The subdirectories that are currently considered (by this code)
 *   to be in the city of Kabal, are:
 *
 *   ~Kalad/common/
 *      central/  caravan/  port/  trade/  market/  noble/  sewers/
 *   ~Kalad/common/guilds/
 *      shadow_walkers/ zintra/ merchant/
 **************************************************************/
public int
query_in_kabal()
{
    return in_kabal;
}

/**************************************************************
 *   Function: query_district()
 *
 *   Returns the lowercase name of the district that the room is
 *   in. This function is used by query_in_kabal() so any changes
 *   here, effect that function too.
 **************************************************************/
public string
query_district()
{
    return district;
}

private void
find_district()
{
    string room_str, tmp;
   
    room_str = file_name(TO);
   
    if (sscanf(room_str,"%sKalad/common/central%s",tmp,tmp) == 2)
	district = "central";
    else if (sscanf(room_str,"%sKalad/common/caravan%s",tmp,tmp) == 2)
	district = "caravan";
    else if (sscanf(room_str,"%sKalad/common/port%s",tmp,tmp) == 2)
	district = "port";
    else if (sscanf(room_str,"%sKalad/common/trade%s",tmp,tmp) == 2)
	district = "tradesmen's";
    else if (sscanf(room_str,"%sKalad/common/market%s",tmp,tmp) == 2)
	district = "market";
    else if (sscanf(room_str,"%sKalad/common/noble%s",tmp,tmp) == 2)
	district = "noble";   

    if (district)
	in_kabal = 1;
    else if (sscanf(room_str,"%sKalad/common/sewers%s",tmp,tmp) == 2)
	in_kabal = 1;
    else if (sscanf(room_str,"%sKalad/common/guilds/shadow_walkers%s",tmp,tmp) == 2)
	in_kabal = 1;
    else if (sscanf(room_str,"%sKalad/common/guilds/zintra%s",tmp,tmp) == 2)
	in_kabal = 1;
    else if (sscanf(room_str,"%sKalad/common/guilds/merchant%s",tmp,tmp) == 2)
	in_kabal = 1;
}

/*******************************************************
 *   Function: query_hear_bell()
 *
 *   Can be called externally. Returns what the room
 *   should hear when the bell rings.
 *******************************************************/
public int
query_hear_bell()
{
    return hear_bell;
}

/*******************************************************
 *   Function: create_room()
 *
 *   Set defaults for our rooms.
 *******************************************************/
public void
create_room()
{
    ::create_room();
    
    hear_bell = 0;                          /* can't hear the bell        */
    find_district(); /* Set the district we are in at creation. */

#if 0 /* Why? */
    set_alarm(2.0, 0.0, "check_set_hide");
#endif
}

