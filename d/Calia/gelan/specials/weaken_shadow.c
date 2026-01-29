
/*  Weaken stat shadow, a possible side-effect of Raspatoon the Alchemist's 
    experiment in the Alchemist quest of Gelan.
  

    coder(s):   Maniac

    history:    
                21.3.95                 Created              Maniac

*/
inherit "/std/shadow";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "specials.h"
#include ALCHEMIST_QUEST

string *stat_des =  ({ "strength",  "dexterity", "constitution", 
               "intelligence", "wisdom", "self discipline" });

int w_stat = -1;


/* Identify player as having a stat weakened */
int
has_weaken_stat_shadow()
{
    return 1;
}


int
query_weakened_stat()
{
    return w_stat;
}

/* Use instead of remove_object() */
void
destruct_weaken_stat_shadow()
{
  if (w_stat > -1)
  shadow_who->catch_msg("Ah, that's better, your " + stat_des[w_stat] +
                        " seems to have returned to normal!\n");
  destruct();
}


/* Set the stat to be weakened */
void
weaken_stat()
{
    w_stat = random(6);
    shadow_who->catch_msg("Your " + stat_des[w_stat] + " seems to be " +
                          "weaker than it should be, curse that " +
                          "alchemist and his experiments!\n");  
}


/* Return weakened stat as 90% of normal, or normal for others */
int
query_stat(int s)
{
    if (w_stat == s)
       return (shadow_who->query_stat(s)*8)/10;
    else
       return shadow_who->query_stat(s);
}

