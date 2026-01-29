/* To be inherited by all rooms in Kalad */
/* By Ashbless                           */

inherit "/std/room";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/timer.c"


int hear_bell; /*0=can't hear it, 1=faintly,2=normal,3=loud,4=def*/
int allow_npc, open, close, max;
string day_desc, night_desc, closed, dirty_msg;
static string *dirty_exits;  /*how much dirtier the player becomes*/

void setup_shop(int npc, int open_time, int close_time,
    string closed_str, int max_dirty, string dirty_str);
public varargs int add_exit (string place, string cmd,
    mixed efunc, mixed tired, mixed dirty);
public int unq_move(string str);
public int is_clean();
string list_exits(object caller);



public mixed
query_dirty_exits() { return dirty_exits + ({}); }

load_it() {}


create_room()
{

    hear_bell = 0;
    load_clock();
    call_out("load_events",0);
    call_out("check_set_hide",2);

}


string
stat_object()
{
    string str;

    str = ::stat_object();

    str = str + list_exits(TO);
    return str;
}

string
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


/* to be redefined in the individual room */
string
sign()
{
    return ("Read what?\n");
}


/* call this function from add_action and define a
     string sign() function for an easy sign        */ 
int
read_sign(string str)
{
    NF("Read what?\n");
    if (!str || str != "sign")
      return 0;

    write(sign());
    return 1;
}


public varargs int
add_exit(string place, string cmd, mixed efunc, mixed tired,mixed dirty)
{
    if (query_prop(ROOM_I_NO_EXTRA_EXIT))
        return 0;
    if (pointerp(room_exits))
        room_exits = room_exits + ({ place, cmd, efunc });
    else
        room_exits = ({ place, cmd, efunc });

    if (!pointerp(tired_exits))
        tired_exits = ({});
    if (tired)
    {
      if (tired < 0)
        tired = 0;
      tired_exits += ({ tired });
    }
    else
        tired_exits += ({ 1 }); /* Standard cost for walking.*/

    if (!pointerp(dirty_exits))
        dirty_exits = ({});
    if (dirty)
    {
      if (dirty < 0)
        dirty = 0;
      dirty_exits += ({ dirty });
    }
    else
        dirty_exits += ({ 1 }); /* Standard cost for walking.*/

/*    update_actions(); */
    ugly_update_action(cmd, 1);
    return 1;
}


public int
unq_move(string str)   /* Must have a unique name */
{
    int i, wd, carry, own, own_weight, tired, tmp, dirty, found, n;
    object d, *ob;

    room_dircmd = str;
    for (i = 0; i < sizeof(room_exits); i += 3)
        if (query_verb() == room_exits[i + 1])
        {
            if ((wd = check_call(room_exits[i + 2])) > 0)
            {
                if (wd > 1)
                    continue;
                else
                    return 1;
            }
            if (!(d = load_room(i)))
                return 1;

    /* Young players younger than 2 hours or people carrying less than
     * 20 % of their capability doesn't get tired from walking around in
     * the world... */

            if (this_player()->query_age() > 3600 &&
                        (tmp = this_player()->query_encumberance_weight())
> 20)

                if (this_player()->query_fatigue() >=
                        (tired = check_call(tired_exits[i / 3])))
                    this_player()->add_fatigue(tmp > 80 ? -tired * 2 :
-tired);
                else {
                    notify_fail("You are too tired to walk in that direction.\n");
                    return 0;
                }

            dirty = check_call(dirty_exits[i/3]);
          if (dirty > 0)
          {
            TP->add_prop(LIVE_I_DIRTY,TP->query_prop(LIVE_I_DIRTY)+dirty);
            ob = deep_inventory(TP);
            for (n = 0; n < sizeof(ob); n++)
              if (ob[n]->id("dirty"))
                found = 1;
            if (!found)
              clone_object(KALAD(std/dirtiness))->move(TP);
          }

            if ((wd == 0) || (!transport_to(room_exits[i + 1], d, -wd)))
                this_player()->move_living(room_exits[i + 1], d);
            return 1;
        }
    return 0; /* We get here if a 'block' function stopped a move */
}


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


/* function: shop
 * description: don't allow npcs to enter if allow_npc is false
 *              and don't allow entrance during closed hours
 *              or if the player is too dirty.
 */

int
shop()
{

                      /*if allow_npc is false - don't let npcs in*/
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

/* return one if player's dirty level is below the max allowed */

int
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
        write(BS("As you start to enter, you're stopped at the door " +
          "and sent back out, because you're too dirty.\n"));
      }
      return 0; /*too dirty to enter*/
    }

    else
      return 1;
    
}


set_time_desc(string day_str,string night_str)
{
      day_desc = day_str;

      night_desc = night_str;
}

string
query_time_desc()
{
    if (TO->query_prop(ROOM_NO_TIME_DESC))
      return "";

    if(DAY)
      if(day_desc && day_desc != "")
        return day_desc;
      else
        if (!TO->query_prop(ROOM_I_INSIDE) && IN_CITY)
          return "The streets are quite crowded at the moment.\n";
        else
          return "";

    else
      if(night_desc && night_desc != "")
        return night_desc;
      else
        if (!TO->query_prop(ROOM_I_INSIDE) && IN_CITY)
          return "The streets are rather deserted at the moment.\n";
        else
          return "";
}


varargs public mixed
long(string str, object for_obj)
{
    int i;
    string ret;  /*string to return*/

    if (!str)
    {
        if (obj_long)
            ret = check_call(obj_long + TDESC, for_obj);
        else
            ret = "You see a non-descript object.\n";

        while ((i = member_array(0, room_descs)) >= 0)
          room_descs = exclude_array(room_descs, i, i + 1);
        if (room_descs)
        for (i = 1; i < sizeof(room_descs); i += 2)
            ret = ret + check_call(room_descs[i]);

        if (!TO->query_noshow_obvious())
          return ret + TO->exits_description();
        else
          return ret;
    }
    if (!pointerp(obj_items))
        return 1;

    for (i = 0; i < sizeof(obj_items); i++)
        if (member_array(str,obj_items[i][0]) >= 0)
        {
            return (strlen(obj_items[i][1]) ?
                    (string) check_call(obj_items[i][1]) :
                    "You see nothing special.\n");
        }
    return 1;
}


    /* It should be easier to hide in outdoor rooms,
          in the city due to the crowdedness
          of the streets. */

check_set_hide()
{
    if (!TO->query_prop(ROOM_I_INSIDE))     /*is it outside?*/
      if (IN_CITY)                                          /*is it in the city? */
        if(TO->query_prop(ROOM_I_HIDE) == 10)     /*is it set at the default val?*/
          change_hide();

    return;     /*if the prop has been changed in the room object then we won't 
                          change it. Only if its at the default value of 10.                     */
}


/*make it easier to hide during the day in an outdoor room in the city.
     change it back at night when its less crowded .                               */

change_hide()
{
    if (DAY)
      TO->add_prop(ROOM_I_HIDE,5);   /*easy to hide - crowded streets */
    else
      TO->add_prop(ROOM_I_HIDE,10);   /*back to normal - less crowded*/

    call_out("change_hide",180); /*check every hour for change in day/night*/
}


/*returns true if the calling room is in the city of Kabal*/

int
query_in_kabal()
{
     string room_str, s1, s2;

    room_str = file_name(TO);
    if (sscanf(room_str,"%sKalad/common/wild%s",s1,s2) == 2)
      return 0;   /*if its in the wild directory, its not in the city*/
    else
      return 1;
}

/* load events for each district */
load_events()
{
    if(!find_object(MRKT_PATH(market_events)))
    {
      call_other( MRKT_PATH(market_events), "start_events");
    }   /* events for market district */
}


load_clock()
{

    if(!find_object("/d/Kalad/clock"))
    {
    call_other("/d/Kalad/clock","query_time");
    }
}


query_hear_bell()
{

    return hear_bell;

}
