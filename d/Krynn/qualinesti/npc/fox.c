/* Fox created for Qualinesti
 *
 * Blizzard, 01/2003 
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

void
create_creature() 
{
    int i;
    set_short("sneaky red fox");
    set_race_name("fox");
    set_name("fox");
    set_adj(({ "lean", "sneaky", "red" }));
    set_long("This is a wild fox, not very large, but quite dangerous " +
        "nevertheless. He is lean and scrawny and has a thick, reddish " +
        "fur.\n");
        
    set_alarm(1.0,0.0, "set_m_in", "stealthily trots in");
    set_alarm(1.0,0.0, "set_m_out", "quickly trots");
    for (i=0;i<6;i++)
        set_base_stat(i, 15 + random(5));
    
    set_knight_prestige(0);
    set_alignment(0);
    
    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 20);
    
    set_alarm(1.0,0.0,"set_restrain_and_home",0);
    set_random_move(20);

    LEFTOVER("tail");
        
    set_act_time(1);
    add_act("emote sneaks around, looking for some small animals.");
    add_act("emote sneaks through the bushes.");
    add_act("emote trots around.");
   
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_VOLUME, 15000 + random(3000));
    add_prop(CONT_I_WEIGHT, 18000 + random(5000));

    set_attack_unarmed(0, 10, 12, W_IMPALE, 40, "bite");
    set_attack_unarmed(1, 12, 10, W_SLASH, 30, "left paw");
    set_attack_unarmed(2, 12, 10, W_SLASH, 30, "right paw");
    
    set_hitloc_unarmed(0, 7, 20, "head");
    set_hitloc_unarmed(1, 8, 50, "body");
    set_hitloc_unarmed(2, 8, 30, "paw");
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
