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
#include "/d/Ansalon/guild/dknights/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>
#include "../local.h"

inherit DARGAARD_IN;

void
reset_room()
{

}

void
create_room()
{
    set_short("Throne room");
    set_long("This is the throne room of Dargaard Keep. The exits out "+
             "of this room lies to the west and east.\n"); 

    add_exit(DROOM + "keep10","west",0);
    add_exit(DROOM + "keep11","east",0);

    add_item(({"bones","bone","bunch"}),
     "This is a bunch of bones. Pieces of rotten flesh "+
     "still covers them.\n");

    add_item(({"words","writing"}),"The words read:\n\n\n"+

        "           'Leave behind the mortal coil,            \n"+
        "      come feast with us in this banquet of death.' \n\n"+
    
        "               'Honour and Loyalty                   \n"+
        "             holds me above the Abyss                \n"+
        "              beyond life and death.'              \n\n"+

        "             'Souls shall be reaped                  \n"+
        "                and revenge shall                    \n"+
        "              fill my hollow being.'               \n\n"+

        "              'Only Blood sweetens                   \n"+
        "                 my time in this                     \n"+
        "                 Immortal Curse.'                  \n\n"+

        "             'Est Sularus oth Mithas                 \n"+
        "                 shall ring out                      \n"+
        "              hollow and mockingly                   \n"+
        "            through these dark halls.'           \n\n\n");

    reset_room();
}

int
do_say(string s)
{  
    if (!s)
    {   
        notify_fail("What do you wish to say?\n");
        return 0;
    }
   
    if (TP->query_prop(I_SOLVED_STEP_4) && s == "est sularus oth mithas")
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

init()
{
   ::init();
   add_action("do_say", "'");
   add_action("do_say", "say");
}
