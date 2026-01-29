// -*-C++-*- 
// conch            /d/Avenir/common/holm/obj/conch.c       
// creator(s):      Lilith  05/18/97
// purpose:         conch shell found on the holm
// last update:     
// note:            It can be blown and listened to :)
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";
#include "/d/Avenir/common/holm/holm.h"
#include "/d/Avenir/include/deities.h"
#include <cmdparse.h>

#define DEPTH         (3)  /* How many rooms away the horn is heard.   */

void
create_object()
{
    set_name("conch");
    add_name(({"shell", "horn"}));
    set_short("pale conch shell");
    add_adj(({"pale", "conch"}));
    set_long("This is the shell of a conch. The outside is pale "+
        "cream, while the inside is flesh-pink. There is a wide, "+
        "pointed spiral at one end of the shell, and a narrow "+
        "section at the other. There is a wide outer lip running "+
        "between the ends.\n");

    add_item(({"lip", "outer lip"}), "This part of the shell is "+
        "bright flesh-pink on the inside.\n");
    add_item(({"spiral", "spiral end"}), "This end of the shell "+
        "is composed of a spiral with rounded spikes.\n");
    add_item(({"narrow end", "narrow section"}), "This is the "+
        "narrow end of the shell, and there is an opening here. "+
        "You find yourself wondering what would happen if you "+
        "blew in this end.\n");
    add_prop(OBJ_I_VALUE,  200);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 200);

    add_prop(HIZARBIN_OFFERING, 1);
}


int
do_blow(string str)
{
    object *rooms, troom;
    int    index;
    int    size;

    if (!str)
        return 0;

    if (!objectp(troom = environment(this_player())))
        return 0;

    notify_fail("You should get it, first.\n");    
    if (ENV(TO) != TP)
        return 0;

    notify_fail("Try <blow shell>.\n");
    if (!parse_command(str, ({ }),
        "[on] [the] 'shell' / 'conch' / 'horn'"))
    if (!parse_command(str, ({ }),
        "[in] [the] [narrow] 'end' / 'shell' / 'conch' / 'horn'"))
        return 0;    

    write("You raise the "+ TO->short() +" to your mouth "+
        "and blow forcefully into it.\n");
    say(QCTNAME(this_player()) +" raises a "+ TO->short() +" to "+ 
        POSSESS(TP) +" mouth and blows forcefully into it.\n");       

    rooms = FIND_NEIGHBOURS(troom, DEPTH);
    index = -1;
    size = sizeof(rooms);
    while(++index < size)
    {
        tell_room(rooms[index], "You hear a deep, reverberating sound:"+
            "   Buuuuu waaaaaah.\n");
    }
    return 1;
}

void
hear_sea()
{
    write("You think you can hear the rush and murmur of the "+
       "sea inside the "+ TO->short() +".\n");
    return;
}

int
do_listen(string str)
{
    if (!str)
        return 0;

    notify_fail("You should get it, first.\n");    
    if (ENV(TO) != TP)
        return 0;

    notify_fail("Try <listen to shell>.\n");
    if (!parse_command(str, ({ }),
        "[to] [the] 'shell' / 'conch' / 'horn'"))
        return 0;    

    write("You raise the "+ TO->short() +" to your ear.\n");
    say(QCTNAME(this_player()) +" raises a "+ TO->short() +" to "+ 
        POSSESS(TP) +" ear.\n");       
    set_alarm(1.0, 0.0, "hear_sea");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_blow,    "blow");
    add_action(do_listen,  "listen");
}

public string
query_recover()
{
    return MASTER;
}

       
