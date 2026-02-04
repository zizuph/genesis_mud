//-*-C++-*-
// file name:      m6.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <macros.h>

#define OTHER_SIDE  (ROOM_DIR +"mausoleum")

int door_closed, door_locked;
int query_closed();
int query_locked();
int query_closed() {    return door_closed;    }
int query_locked() {    return door_locked;    }

int lock_alarmid;

void reset_room()  
{      
    door_locked = 1;
    door_closed = 1;
}


void open_door();
void urn_unlock();

public void create_vamp_room()
{

    set_short("landing");
    set_long("This is the landing for a set of stairs leading down "+
        "into darkness. This is the midpoint between the world of "+
        "the living and the land of the dead. Here, the darkness "+
        "seems to tremble and reach toward you with greedy "+
        "fingers, drawing you toward it and away from the sun "+
        "which shines its terrible brillance south of here, "+
        "through the double copper doors. @@exa_bar");
    
    add_exit("chamber","down", "@@do_down");
    add_exit("mausoleum", "south", "@@try_south"); // invis exit
     
    add_item(({"door", "doors", "copper doors"}), 
        "These copper doors are massive. They have oxidized to the "+
        "point that no mere mortal could ever open them. Each one "+
        "has an inscription on it.\n");
    add_item(({"inscription", "inscriptions"}), 
         "The one on the east door bears "+
        "the words\nNe conjugare nobiscum.\nThe one on the "+
        "west door bears the words\nOderunt dum Metuant.\n");
    add_item(({"east door", "right door", "right inscription", 
        "east inscription"}), "This door is blue-green in colour. "+
        "The surface bears the following words:\n"+
        "     Ne conjugare nobiscum.\n");
        /* Don't fuck with us */
    add_item(({"west door", "left door", "west inscription", 
        "left inscription"}), "This door is blue-green in colour. "+
        "The surface bears the following words:\n"+
        "    Oderunt dum metuant.\n");
        /* Let them hate, so long as they fear */
    add_cmd_item(({"door", "east door", "west door", "doors", 
        "copper door", "copper doors"}), 
        ({"knock", "bang"}), "You hear a deep, gong-like sound.\n");        
    add_cmd_item(({"door", "east door", "west door", "doors", 
        "copper door", "copper doors"}), 
        ({"open", "push"}), "@@do_open");
    add_item(({"floor", "ground", "ceiling", "walls"}),
        "They are made of granite.\n");
    add_item(({"granite", "quartz", "black stone"}), 
        "The granite is dark grey in colour "+
        "and speckled with black stone and bits of quartz.\n");
    add_item(({"bar"}), "@@exa_bar");
    add_cmd_item(({"bar", "door", "doors"}), 
        ({"lift", "raise", "unlock", "unbar"}), "@@lift_bar");
    add_cmd_item(({"bar", "door", "doors"}), ({"lower", "lock", "bar"}), 
        "@@lower_bar");

    reset_room();

}

string
exa_bar()
{
    if (query_locked())
    {
        return "A steel bar has been placed across the doors. "+
            "You might be able to raise it.\n";
    }
    return "The steel bar is in its raised position. It no "+
        "longer blocks the doorway.\n";           
}


string 
lift_bar()
{
    if (!query_locked())
    {
        return "The steel bar is in its raised position. It no "+
        "longer blocks the doors.\n"; 
    }
    door_locked=0;
    return "You raise the steel bar so that it no longer blocks "+     
           "the doors.\n";
}

string 
lower_bar()
{
    if (query_locked())
    {
        return "A steel bar has already been placed across the doors.\n"+
            "You do not see another one to lower.\n";
    }
    door_locked = 1;
    if (lock_alarmid)
    {
        remove_alarm(lock_alarmid);
        lock_alarmid=0;
    }
    return "You lower the steel bar so that it blocks the doors "+
        "from opening.\n"; 

}

void 
urn_unlock()
{
    door_locked=0;
}


void
close_door()
{
    if (query_closed())
        return;

    tell_room(TO, "The copper doors swing closed with a loud metallic screech.\n");
    door_closed = 1;
    (OTHER_SIDE)->close_door();
    return;
}


void
open_door()
{
    tell_room(TO,"The copper doors swing open with a loud metallic screech.\n");
    door_closed = 0;
    return;
}


int
do_open(string str)
{
    if (!strlen(str))
        return 0;

    if (str != "door" && str != "copper door" && str != "doors")
    {
        notify_fail("Open what?  The door?\n");
        return 0;
    }

    if (!IS_VAMP(TP)  && !IS_BG(TP))
    {
        notify_fail("These heavy copper doors are so ancient "+
            "they have oxidized to the point that it would take "+
            "far greater strength than yours to force them open.\n");
        return 0;
    }
    if (TO->query_locked())
    {
        notify_fail("There is a steel bar blocking the doors from "+
            "being opened.\n");
        return 0;
    }        

    door_closed = 0;
    (OTHER_SIDE)->open_door();
    write("You push on the copper doors, opening them with a loud "+
        "metallic screech.\n");
    say(QCTNAME(TP)+ " pushes the copper doors open with a loud "+
        "metallic screech.\n");
    TP->command("$south");
    set_alarm(0.25, -1.0, "close_door");    
    return 1;
}
int
try_south()
{   
    if(door_closed)
    {
        write("That way is blocked by the copper doors.\n"); 
        return 1;
    }
    return 0;
}

int
do_down()
{
    if (IS_VAMP(TP) && IS_BG(TP))
    {
        write("Half-way down you come across a slab "+
            "of stone used to seal the crypt.\n You easily lift "+
            "the slab out of your way and continue down the "+
            "stairs.\n");      
        return 0;
    }
   
    return 0;

}

    
void
init()
{

    ::init();

    add_action(do_open, "open");
    
}
