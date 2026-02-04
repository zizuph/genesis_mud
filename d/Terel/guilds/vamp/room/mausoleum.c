//-*-C++-*-
// file name:      mausoleum.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <macros.h>

#define OTHER_SIDE  (ROOM_DIR +"m6")

int door_closed;
void open_door();
void close_door();

void reset_room() {      door_closed = 1;     }

public void create_vamp_room()
{

    set_short("ancient mausoleum");
    set_long("This an ancient mausoleum made of a granite whose "+
        "aged stone has at last begun to crumble. It appears "+
        "to have been raised to honour the dead of a family whose line "+
        "has long since faded into the mists of time. "+
        "Like the ancient days rising to life, the dead seem free "+
        "here, their presence felt within the stone. Opposite the "+
        "entrance are two massive copper doors stained verdigris, "+
        "each bearing an inscription. "+
        "A broad walkway extends both east and west from here.\n");

    
    add_exit("outside","out");
    add_exit("m3", "east");
    add_exit("m2", "west");
    add_exit("m6", "north", "@@try_north", 1, 1); // invis exit
     
    add_item(({"door", "doors", "copper doors"}), 
        "These copper doors are massive. They have oxidized to the "+
        "point that you doubt they could ever be opened. Each door "+
        "bears an inscription.\n");
    add_item(({"inscription", "inscriptions"}), 
        "The one on the right door bears "+
        "the words\nMors ultima linea rerum est.\nThe one on the "+
        "left door bears the words\nExegi monumentum aere perennius.\n");
    add_item(({"east door", "right door", "right inscription", 
        "east inscription"}), "This door is blue-green in colour. "+
        "The surface bears the following words:\n"+
        "     Mors ultima linea rerum est\n");
        /* Death is the final limit for everything */
    add_item(({"west door", "left door", "west inscription", 
        "left inscription"}), "This door is blue-green in colour. "+
        "The surface bears the following words:\n"+
        "    Exegi monumentum aere perennius\n");
       /* I have erected a monument more lasting than bronze */
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

    reset_room();

}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */

public int
prevent_leave(object ob)
{ 
    if (present("_columbarium_urn", ob))
    {
        write("You get a bad feeling about taking the urn from its "+
            "eternal resting place.\nYour hands suddenly spasm.\n");

        ob->command("$drop urns");
        return 0;
    }

    return 0;
}

int
try_north()
{   
    if (door_closed)
    {
        write("That way is blocked by the copper doors.\n"); 
        return 1;
    }
    return 0;
    
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

    if (!IS_VAMP(TP) && !IS_BG(TP))
    {
        write("These heavy copper doors are so ancient "+
            "they have oxidized to the point that it would take "+
            "far greater strength than yours to force them open.\n");
        return 1;
    }
    if (OTHER_SIDE->query_locked())
    {
        write("The copper doors appear to be blocked "+
            "on the other side. You cannot budge them.\n");
        return 1;
    }        
    door_closed = 0;
    write("You push on the copper doors, opening them with a loud "+
        "metallic screech.\n");
    say(QCTNAME(TP)+ " pushes the copper doors open with a loud "+
        "metallic screech.\n");
    (OTHER_SIDE)->open_door();
    TP->command("$north");
    set_alarm(0.25, -1.0, "close_door");    
    return 1;
}

void
close_door()
{
    if (door_closed)
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

void
init()
{

    ::init();

    add_action(do_open, "open");
    
}