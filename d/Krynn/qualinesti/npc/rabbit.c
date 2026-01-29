/* rabbit.c
 * Rabbit created for Qualinesti
 *
 * Blizzard 01/2003
 *
 * Changelog:
 *   - Fixed leftover for ears to not throw runtimes.
 */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

inherit C_FILE
inherit "/std/act/domove";
inherit "/std/act/action";

string  *adj_list1 = ({ "long-eared", "small", "big", "bouncy" });
string  *adj_list2 = ({ "brown", "reddish", "furry", "brown-furred" });
string  adj1, adj2;

void
create_creature() 
{
    int i;
    adj1 = adj_list1[random(sizeof(adj_list1))];
    adj2 = adj_list2[random(sizeof(adj_list2))];
    set_short(adj1 + " " + adj2 + " hare");
    set_pshort(adj1 + " " + adj2 + " hares");
    set_race_name("hare");
    set_name("hare");
    add_name("animal");
    set_adj(({ adj1, adj2 }));
    set_long("You see a small, " +adj2+ " hare. It looks like a rabbit but " +
        "has longer ears and legs. They are also quite common in this forest.\n");
        
    set_alarm(1.0,0.0,"set_m_in","scampers in");
    set_alarm(1.0,0.0,"set_m_out","scampers");
    for (i=0;i<6;i++)
      set_base_stat(i, 15 + random(5));
    
    set_knight_prestige(0);
    set_alignment(0);
    
    set_hp(query_max_hp());

    set_alarm(1.0,0.0,"set_restrain_and_home",0);
    set_random_move(30);

    LEFTOVER("tail");
    LEFTOVER("ear");
    
    set_skill(SS_DEFENCE, 25 + random(10));
    
    set_act_time(1);
    add_act("emote sniffs the air hungrily.");
    add_act("emote chitters noisily.");
    add_act("emote jumps around.");
   
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_VOLUME, 2000 + random(1000));
    add_prop(CONT_I_WEIGHT, 3500 + random(1000));
    
    set_attack_unarmed(0, 10, 10, W_IMPALE, 30, "bite");
    set_attack_unarmed(1, 10, 10, W_SLASH, 20, "right paw");
    set_attack_unarmed(2, 10, 10, W_SLASH, 20, "left paw");
    
    set_hitloc_unarmed(0, 5, 40, "head");
    set_hitloc_unarmed(1, 7, 60, "back");
}


/* Function:    set_restrain_and_home
 * Arguments:   depth <= 0 use the direct subdir of the monster_home
 *                         as restrain path.
 *                     > 0 go depth subdirs up in the directory list
 *                         for the restrain path.
 * Description: I set my own restrain path and home according to where
 *              I start. The restrain path will only be the subdir
 *              where the home is located. To specify a higher dir
 *              as restrain path, use the depth parameter.
 *              Call this function after cloning with an alarm > 1 if
 *              you want to set the depth to a different value.
 * Returns:     void
 */
void
set_restrain_and_home(int depth)
{
    string path = file_name(E(TO));
    string *parts = explode(path,"/");
    if (depth < 0)
      depth = 0;
    parts = parts[0..sizeof(parts)-2-depth];
    set_restrain_path(implode(parts,"/"));
    set_monster_home(file_name(E(TO)));
}
