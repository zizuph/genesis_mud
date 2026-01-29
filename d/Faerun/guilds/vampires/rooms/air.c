/**
* This room is the flight room in which vampires will travel
* Novo May 2008
*
* Used with permission, Nerull 2021.
*/
#pragma strict_types

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <composite.h>

#include "../guild.h"
#include "travel.h"

public int Location_x,Location_y;

public object * Ld_people = ({ });

static int Dest_alarm = 0;

mixed * Destinations;
mixed Current_destination;
mixed Closest_destination;

int Flight_alarmid;

void
create_room()
{
    set_short("In midair");

    set_long("@@mylong@@");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    
    add_prop(ROOM_I_LIGHT,"@@check_light@@");

    remove_prop(CONT_I_VOLUME);
    remove_prop(CONT_I_MAX_VOLUME);
    remove_prop(CONT_I_WEIGHT);
    remove_prop(CONT_I_TRANSP);
    remove_prop(CONT_I_MAX_WEIGHT);
    remove_prop(OBJ_I_VALUE);

    add_item(({ "ground","earth" }),
        "The ground is far below, and from such heights it is difficult "+
        "to see many details.\n");

    add_item(({ "sky", "air", "open space", "space" }),
        "You are high up in the air - the sky is the limit.\n");

    add_item(({ "sky", "air" }),
        "You are high up in the air - the sky is the limit.\n");

    setuid();
    seteuid(getuid());
}

int still_ld(object who)
{
    return (who && !interactive(who));
}


public int get_distance(mixed destination)
{
    return (destination[1]-Location_x)*
           (destination[1]-Location_x) +
           (destination[2]-Location_y)*
           (destination[2]-Location_y);
}

public string direction_name(mixed destination)
{
    int dx=destination[1]-Location_x;
    int dy=destination[2]-Location_y;
    
    string result="";
    
    if (dy*dy*4>dx*dx)
    {
        if (dy>0)
        {
            result="south";
        }
        else
        {
            result="north";
        }
    }
    if (dx*dx*4>dy*dy)
    {
        if (dx>0)
        {
            result+="east";
        }
        else
        {
            result+="west";
        }
    }
    return result;
}

public void set_location(int x,int y)
{
    Location_x=x;
    Location_y=y;
}

public int * query_location()
{
    return ({ Location_x, Location_y });
}

public string destination_desc(string val)
{
    mixed * dest=filter(Destinations,&operator(==) (val) @
                    &operator([]) (,0));
    if (!sizeof(dest))
    {
        return "You do not see that.\n";
    }
    int dist=get_distance(dest[0]);
    switch (dist)
    {
        case 0:
           return "You can see "+dest[0][3]+" directly below you.\n";
        case 1..25:
            return "You see "+dest[0][3]+" not too far to the "+
                direction_name(dest[0])+".\n";
        case 26..100:
            return "You see "+dest[0][3]+" on the horizon to the "+
                direction_name(dest[0])+".\n";
        default:
            return "You are too far to see any details.\n";
     }                
}


public int match_depth(string first,string second)
{
    string * firstdirs=explode(first,"/");
    string * seconddirs=explode(second,"/");
    
    if (SAME_DIRS[seconddirs[2]])
    {
        seconddirs[2]=SAME_DIRS[seconddirs[2]];
    }
    if (SAME_DIRS[firstdirs[2]])
    {
        firstdirs[2]=SAME_DIRS[firstdirs[2]];
    }
    for (int i=0;i<min(sizeof(firstdirs),sizeof(seconddirs));i++)
    {
        if (firstdirs[i]!=seconddirs[i])
        {
            return i;
        }
    }
    return min(sizeof(firstdirs),sizeof(seconddirs));
}

public int same_domain(string first,string second)
{
    return (match_depth(first,second)>=3);
}

void move_def_start(object ob)
{
    string start;

    if (!strlen(start = ob->query_default_start_location()) &&
        !strlen(start = ob->query_def_start()))
    {
        return;
    }

    ob->move_living("X", start, 1);
}

/* this function called repeatedly when a vampire ld's
 * while melded.  This function takes care of removing
 * the object when appropriate.
 */
void wait_to_destruct()
{
    Ld_people = filter(Ld_people, still_ld);
  
    if (!sizeof(Ld_people))
    {
        remove_alarm(Dest_alarm);
        Dest_alarm = 0;
    
        if (!sizeof(all_inventory()))
        {
        remove_object();
        }
    }
}

void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
  
  
    /* We want to remove the room if it is empty, but not if
     * someone has linkdied from here.  If we get rid of it in
     * that case, the player will be sent back to his startloc
     * when he revives, and we don't want that.  So, we take
     * precautions so that the room is around as long as there
     * are ld players who might need to use it.
     */
  
    if ((VAMPIRES_MASTER->is_occ_vampires(ob->query_name()) == 0))
    {
        return;
    }
  
    if (!interactive(ob))
    {
        Ld_people += ({ ob });
    }
  
    if (!Dest_alarm && !interactive(ob))
    {
        Dest_alarm = set_alarm(10.0, 10.0, wait_to_destruct);
        return;
    }
  
    if (!Dest_alarm && !sizeof(all_inventory()))
    {
        /* keep the container around for a while in case it's 
         * needed by other functions (enter_env(), for instance)
         */
        set_alarm(2.0, 0.0, remove_object);
    }
}

public mixed * query_destinations()
{
    return Destinations;
}

public void make_item_fall(object ob)
{
    if ((VAMPIRES_MASTER->is_occ_vampires(ob->query_name()) == 1) 
        || IS_WIZ(ob))
    {
        string * names=map(Destinations,&operator([]) (,0));
        names=sort_array(map(names,&operator(+) ("'") 
                    @ &operator(+) (,"'")));
        if (sizeof(names)>1)
        {                    
            ob->catch_msg("You can fly to "+ COMPOSITE_WORDS(names)+".\n");
        }
        return;
    }

    if (living(ob))
    {
        ob->catch_msg("You are falling...\n");
        WATCHERS(ob)->catch_msg(QCTNAME(ob) + " falls out of sight.\n");
        if (!ob->move_living("M",Closest_destination[4],1,0))
        {
            WATCHERS(ob)->catch_msg(QNAME(ob) + " falls out of the sky "+
                "and slams into the ground!\n");
            ob->catch_msg("And hit the ground!\n");
            ob->set_hp(0);
            ob->do_die(this_object());
        }            
        return;
    }
    
    WATCHERS(ob)->catch_msg(capitalize(LANG_THESHORT(ob)) +
        " falls out of sight.\n"); 
    ob->move(Closest_destination[4]);
    ob->remove_broken();
    WATCHERS(ob)->catch_msg(capitalize(LANG_ASHORT(ob)) + 
        " falls out of the sky and slams into the ground!\n");
        
}

public string mylong()
{
    string desc=
    "High up in the air, there is open space visible in all directions.";
    int dist=get_distance(Closest_destination);

    if (Destinations)
    {

        mixed * under=filter(Destinations,&operator (==) (0) 
                                @ &get_distance());
        mixed * close=filter(Destinations,&operator (<) (,25) 
                                @ &get_distance()) - under;
        mixed * far=filter(Destinations,&operator (<) (,100) 
                                @ &get_distance()) - close - under;

        if (sizeof(under))
        {
            desc+=" Directly below you, you spot "+
            COMPOSITE_WORDS(map(under,&operator ([]) (,3))) + ".";
        }
        if (sizeof(close))
        {
            desc+=" Not too far away, you can see "+
            COMPOSITE_WORDS(map(close,&operator ([]) (,3))) + ".";
        }
        if (sizeof(far))
        {
            desc+=" In the distance, you can barely make out "+
            COMPOSITE_WORDS(map(far,&operator ([]) (,3))) + ".";
        }
    }
    desc+="\n";
    return desc;
    
}


void set_start_location(object player)
{
    object start=environment(player);
    
    string filename=MASTER_OB(start);
    
    Destinations=TRAVEL_LOCATIONS;
    
    int matches,sumx,sumy;
    int bestdepth=0;
    
    foreach (mixed destination : Destinations)
    {
        add_item(lower_case(destination[0]),
        ("@@destination_desc|"+destination[0]+"@@"));
        
        int depth=match_depth(filename,destination[4]);
        if (depth>bestdepth)
        {
            matches=0;
            bestdepth=depth;
            sumx=0;
            sumy=0;
        }
        if (depth==bestdepth)
        {
            matches++;
            sumx+=destination[1];
            sumy+=destination[2];
        }
    }
    if (!matches)
    {
        Location_x=50;
        Location_y=50;
    }
    else
    {
        Location_x=sumx/matches;
        Location_y=sumy/matches;
    }
    Current_destination=
    ({ "back", Location_x, Location_y, "your original location",
        filename });
    Closest_destination=Current_destination;
    Destinations+=({ Current_destination });
        
}


void enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);

    set_alarm(0.1,0.0,&make_item_fall(ob));
}

public int check_light()
{
    if (!Closest_destination)
    {
        return 1;
    }
    if (!Closest_destination[4])
    {
        return 1;
    }
    return Closest_destination[4]->query_prop(ROOM_I_LIGHT);
}


public int descend(string str)
{
    if (Location_x!=Current_destination[1] ||
        Location_y!=Current_destination[2])
    {
        write("You have yet to reach your destination.\n");
        return 1;
    }        
    
    write("You descend back from the heavens.\n");
    this_player()->move_living("M",Current_destination[4],1,0);
    object * watchers=WATCHERS(this_player());
    watchers->catch_msg(QCTNAME(this_player()) 
    + " descends from above, like a "+
    "messenger of the gods.\n");
    return 1;
}

public mixed find_closest_destination()
{
    int closest=get_distance(Closest_destination);
    mixed best=Closest_destination;
                
    foreach(mixed dest: Destinations)
    {
        int score=get_distance(dest);
        if (score<closest)
        {
            best=dest;
            closest=score;
        }
    }
    return best;
}


public void do_fly()
{
    if (Current_destination[1]<Location_x)
    {
        Location_x--;
    }
    if (Current_destination[1]>Location_x)
    {
        Location_x++;
    }
    if (Current_destination[2]<Location_y)
    {
        Location_y--;
    }
    if (Current_destination[2]>Location_y)
    {
        Location_y++;
    }
    mixed best=find_closest_destination();
    if (best!=Closest_destination)
    {
        tell_room(this_object(),"Looking down, you see that you "
        +"are approaching "+
            best[3]+".\n");
        Closest_destination=best;
        setuid();
        seteuid(getuid());
        LOAD_ERR(best[4]);
    }
    else
    {
        switch (random(15))
        {
            case 0:
            tell_room(this_object(),"The wind blows across your skin as you "
            +"travel.\n\n");
            break;
            case 1:
            tell_room(this_object(),"You see wisps of cloud pass by below "
            +"you.\n\n");
            break;
            case 2:
            tell_room(this_object(),"Various landmarks pass by "
            +"far beneath you.\n\n");
            break;
            case 3:
            tell_room(this_object(),"You travel quickly across "
            +"great distance.\n\n");
            break;
            case 4:
            tell_room(this_object(),"The ground moves below at "
            +"great speed.\n\n");
            break;
            case 5:
            tell_room(this_object(),"Life below appears like ants "
            +"from such "+
            "heights.\n\n");
            break;
        }
    }
    if (Current_destination[1]==Location_x &&
        Current_destination[2]==Location_y)
    {
        tell_room(this_object(),"You arrive at your destination.\n");
        Closest_destination=Current_destination;
        setuid();
        seteuid(getuid());
        LOAD_ERR(Closest_destination[4]);
        remove_alarm(Flight_alarmid);
    }
}

public int fly(string str)
{
    notify_fail("Fly where?\n");
    
    string dest=str;
    
    if (!str)
    {
        return 0;
    }
    
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    parse_command(str,({})," [to] %s",dest);
    str=dest;
    
    if (!dest)
    {
        return 0;
    }
    
    dest=lower_case(dest);
    mixed * next_destination=filter(Destinations,&operator(==) (dest) @
                    &lower_case() @ &operator([]) (,0));
    
    
    if (!sizeof(next_destination))
    {
        string * names=map(Destinations,&operator([]) (,0));
        names=sort_array(map(names,&operator(+) ("'") 
                    @ &operator(+) (,"'")));
        write("'"+capitalize(str)+"' is not a valid destination. " +
        "You can fly to "+ COMPOSITE_WORDS(names)+".\n");
        
        return 1;
    }
    if (next_destination[0]==Current_destination)
    {
        if (Current_destination[1]==Location_x &&
            Current_destination[2]==Location_y)
        {
            write("You have already arrived at "+Current_destination[3] +
            ".\n");
            return 1;
        }
        write("You are already travelling to "+Current_destination[3] +
        ".\n");
        return 1;
    }
    
    Current_destination=next_destination[0];
    
    write("You start to fly towards "+Current_destination[3]+".\n");
    remove_alarm(Flight_alarmid);
    Flight_alarmid=set_alarm(2.0,2.0,do_fly);
    
    return 1;
}

int
ethereal()
{
    write("You can't enter the ethereal realm while flying.\n");
    
    return 1;
}

public void init()
{
    ::init();
    add_action(descend,"descend");    
    add_action(descend,"down");    
    add_action(descend,"land");    
    add_action(fly,"fly");
    add_action(fly,"travel");
    
    add_action(ethereal,"ethereal");
}

     
void remove_object()
{
    map(deep_inventory(), move_def_start);
    ::remove_object();
}    
