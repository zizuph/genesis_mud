/*
 * Changelog:
 *  November 2009 - Added function to identify whether corpse has
 *                  the vampire drained corpse shadow that results when
 *                  a vampire bites the person to death. (Petros)
 */
inherit "/std/shadow";

#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */
#include <stdproperties.h> /* For standard properties */
#include <macros.h> /* For macros */
#include <filter_funs.h> /* For easy filters */
#include <composite.h> /* Composie words */

#include "../guild.h"

object Killer;

string extra=one_of_list(({ "pale, gaunt ", 
                         "mauled, barely recognizable ",
                        "dry, sallow " }));

/*
 * Function:    has_vampire_drained_corpse_shadow
 * Description: This returns whether the corpse has this shadow.
 */
public int
has_vampire_drained_corpse_shadow()
{
    return 1;
}                         

string
short()
{
    string result= QSW->short();
    
    return extra+result;
    
}

string
plural_short()
{
    string result= QSW->plural_short();
    
    return extra+result;
    
}

string
long()
{
    string result= QSW->long();
    
    return result + 
    "This corpse has been drained of blood.\n";
   
}    

public void set_killer(object killer)
{
    Killer=killer;
}

public void drop_corpse()
{
    if (environment(QSW)==Killer)
    {
        tell_object(Killer,
        "Satiated with the blood from your kill, you drop your lifeless "+
        "prey at your feet.\n");
        
        string poss=POSS(Killer);
        
        string race=this_object()->query_prop(CORPSE_S_RACE);
        if (!race)
        {
            race="prey";
        }
        WATCHERS(Killer)->catch_msg(
            QCTNAME(Killer) + " pulls " + POSS(Killer) + 
            " head back, mouth covered in the blood of the fallen "+
            race +". Satisfied with "+
            poss + " meal, "+PRO(Killer)+" drops the newly deceased at "+
            poss+ " feet.\n");
        
        this_object()->move(environment(Killer));
    }
}

public void initiate_drop_corpse()
{
    set_alarm(3.0,0.0,drop_corpse);
}



