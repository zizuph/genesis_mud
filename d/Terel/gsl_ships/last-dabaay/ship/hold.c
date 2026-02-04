/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Cargo Hold on the ship to Sparkle
 * Goldberry February 2000
 * Last Modified:
 *  07242002 Goldberry
 *    Changed difficulty of block
 *    Changed fatigue loss to a percentage
 */

#include "/d/Terel/include/Terel.h"
#include <tasks.h>
#include <ss_types.h>
#include "../ship.h"
//inherit STDROOM;
inherit "/d/Genesis/gsl_ships/std/shiproom";
#define DAB_NPC  DABAAY_DIR + "npc/"
/* Task difficulty for breaking the block 
   (TASK_DIFFICULT = 800, TASK_ROUTINE = 500) */
#define DIFF 600

/* Percentage of max fatigue, lost in each failed escape attempt */
int FAT_LOSS = 10;


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
  ::create_shiproom();
    set_short("In a dark cargo hold");
    set_long(
        "You are standing in the cargo hold of a ship. "+
        "There is enough light to make out a few details here. "+
        "The only exit appears to be a hatch that is above "+
        "your head.\n");
 
    add_exit(DECK, "up", "@@block");
    INSIDE;
    reset_room();
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(OBJ_S_WIZINFO,
     "This is the secret room of the pirate Dabaayhab. If a mortal finds "+
     "himself in here, then they must have either been attacked by, or "+
     "attacked Dabaayhab up on deck. "+
     "If the mortal should somehow be able to stop the "+
     "fight, Dabaayhab will attack again on any failed attempt at leaving.\n");
  
}

int
block()
{
    object pirate;
    int attempt, f_loss;
    pirate=present("dabaayhab");

    if (TP->query_prop(OBJ_I_INVIS) || TP->query_wiz_level())
       return 0;

    f_loss = (TP->query_max_fatigue() * FAT_LOSS) / 100;
    if (pirate && pirate->query_name()!="corpse")
    {
        if (f_loss > TP->query_fatigue())
        {
            write("You are too tired to get past the halfling.\n");
            say(QCTNAME(TP)+" stares weakly at the hatch.\n");
            return 1;
        }

        attempt = TP->resolve_task(DIFF,
                                   ({TS_DEX,TS_STR}),
                                   pirate, ({TS_DEX,TS_STR}));        
        
        if (attempt < 1)
        {
           write("The halfling manages to keep you away from the hatch.\n");
           say("The halfling prevents "+QCTNAME(TP)+" from "+
               "going up.\n");
           pirate->command("kill " +TP->query_real_name());
           TP->add_fatigue(-1*f_loss);
           return 1;
        }
        
        write("You struggle past the halfling.\n");
        say(QCTNAME(TP)+" manages to get past the halfling.\n");
        TP->add_fatigue(-1*(f_loss)/2);
    }
    return 0;
}
