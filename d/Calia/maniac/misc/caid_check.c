/* Code to gather statistics to assist in the measure of penalty 
   modifiers in calculating combat aid. 

   Coded by Maniac    10/10/95
*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Calia/sys/guild_record.h"

#define COMB_DATA "/d/Calia/maniac/misc/comb_data"
#define DATA_INTERVAL 600

int samp_total; /* Total number of samples of players fighting */
int wep_total; /* Total number of creatures from sample with weapons */
int wep_th_total; /* Total number of creatures from sample with two handed
                     weapons */
int bf_cum_total; /* Blindifight skill cumulative total from samples taken */
int teamed_total; /* How many of the sample were teamed */
int att_teamed_total; /* How many of the sample were teamed and being 
                        attacked by the enemy */

int cal_samp_total; /* How many of the sample were Calians */
int cal_teamed_total; /* How many of the sample were Calians and teamed */
int cal_att_teamed_total; /* How many of the sample were Calians, teamed 
                            and being attacked by the enemy */

void
create()
{
    seteuid(getuid(this_object()));
    restore_object(COMB_DATA);
    set_alarm(1.0, 0.0, "gather_stats");
}


/* Update combat data */
int
gather_stats()
{
    int i, cal;
    object *u = ({ });
    object a;

    if (objectp(calling_object())) /* Only should be called from alarms */
        return 0;

    u = users();
    if (!sizeof(u))
        return 0;

    for (i = 0; i < sizeof(u); i++) {
        a = u[i]->query_attack(); 
        if (!objectp(a) || (u[i]->query_wiz_level()))
            continue;

        samp_total++; 
        cal = (u[i]->query_guild_name_occ() == CALIAN);
        if (cal)
            cal_samp_total++;

        if (objectp(a->query_weapon(W_LEFT)) ||  
            objectp(a->query_weapon(W_RIGHT))) 
            wep_total++;
        else if (objectp(a->query_weapon(W_BOTH))) {
            wep_total++;
            wep_th_total++;
        }

        bf_cum_total += a->query_skill(SS_BLIND_COMBAT);

        if (sizeof(u[i]->query_team_others())) {
            teamed_total++;
            if (cal) 
                cal_teamed_total++;
            if (a->query_attack() == u[i]) {
                att_teamed_total++;
                if (cal)
                    cal_att_teamed_total++;
            }
        }
    }

    save_object(COMB_DATA);
    set_alarm(itof(DATA_INTERVAL), 0.0, "gather_stats");
    return 1;
}


string
query_stats()
{
    string str; 

    str = ("Sample size of mortals who were fighting: " + samp_total + ".\n\n");

    str += ("Number of fighting mortals who were fighting in a team: " + 
            teamed_total + ".\n"); 

    str += ("Number of those mortals who were being attacked " +
            "by the attacked creature: " + att_teamed_total + ".\n\n");

    str += ("Number of creatures being attacked that wielded a weapon: " + 
            wep_total + ".\n"); 
     
    str += ("Number of those creatures that wielded a two handed weapon: " +
           wep_th_total + ".\n\n");

    str += ("Average blind combat skill for fought creatures. " + 
            (bf_cum_total/samp_total) + ".\n\n");

    str += ("Sample size of Calians who were fighting: " + cal_samp_total + 
            ".\n\n");

    str += ("Number of fighting Calians who were fighting in a team: " +
            cal_teamed_total + ".\n");

    str += ("Number of those Calians who were being attacked " +
            "by the attacked creature: " + cal_att_teamed_total + ".\n\n");

    return str;
}

