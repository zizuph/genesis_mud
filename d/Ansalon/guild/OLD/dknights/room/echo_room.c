/************************************************************
 * Area: Dargaard Keep.
 * By  : 
 * Date:
 * Desc:
 *
 *
 *
 ************************************************************/

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "../local.h"

inherit DARGAARD_IN;

void
reset_dargaard_room()
{

}

void
create_dargaard_room()
{
    set_short("Throne room");
    set_long("This is the throne room of Dargaard Keep. The exits out "+
             "of this room lies to the west and east.\n"); 

    add_exit(DROOM + "keep10","west",0);
    add_exit(DROOM + "keep11","east",0);

    add_item(({"bones","bone","bunch}),
     "This is a bunch of bones. Pieces of rotten flesh "+
     "still covers them.\n");

    add_cmd_item(({""}), "say","@@do_say");
    add_cmd_item(({""}), "'","@@do_say");
    add_cmd_item(({""}), "whisper","@@do_whisper");

    reset_dargaard_room();
}

int
do_say(string s)
{  
    if (!s)
    {   
        notify_fail("Say what?\n");
        return 0;
    }
   
    if (TP->query_prop(I_SOLVED_STEP_3) && s == "est sularus oth mithas")
    {
        // Do the final step in the Dknight entrance quest.
        TP->remove_prop(I_SOLVED_STEP_4);
        return 1;
    }

    if (TP->query_option(OPT_ECHO) == 1)
    {
        write("You say: "+ s +"\n");
        write("The room echoes the words: "+ s +"\n");
    }

    if (TP->query_option(OPT_ECHO) == 0)
    {
        write("Ok.\n");
        write("The room echoes the words: "+ s +"\n");
    }
   
    say(QTNAME(TP)+" says: "+ s+"\n");
    say("The room echoes the words: "+ s+"\n");
    return 1;
}


int
do_whisper(string s)
{  
    if (!s)
    {   
        notify_fail("Whisper what?\n");
        return 0;
    }
   
    if (TP->query_option(OPT_ECHO) == 1)
    {
        write("You whispers: "+ s +"\n");
        write("The room echoes the words: "+ s +"\n");
    }

    if (TP->query_option(OPT_ECHO) == 0)
    {
        write("The room echoes the words: "+ s +"\n");
        write("Ok.\n");
    }
   
    say(QTNAME(TP)+" whispers: "+ s+"\n");
    say(QTNAME("The room echoes the words: "+ s+"\n");
    return 1;
}

