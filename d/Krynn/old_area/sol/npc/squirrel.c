/* squirrel created for Krynn
by Stevenson */

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
    set_short("brown squirrel");
    set_race_name("squirrel");
    set_name("squirrel");
    set_adj("brown");
    set_long("You see a small, brown squirrel. They are really quite "
	     + "common to these parts and can be seen almost anywhere."
	     + "\n");
    
    
    set_alarm(1.0,0.0,"set_m_in","scampers in");
    set_alarm(1.0,0.0,"set_m_out","scampers");
    for (i=0;i<6;i++)
      set_base_stat(i, 5 + random(5));
    
    set_knight_prestige(0);
    set_alignment(0);
    
    set_hp(query_max_hp());

    set_alarm(1.0,0.0,"set_restrain_and_home",0);
    set_random_move(30);
    
    set_act_time(2);
    add_act("emote sniffs the air hungrily.");
    add_act("emote chitters noisily.");
    add_act("emote approaches you cautiously.");
   
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_VOLUME,250);
    add_prop(CONT_I_WEIGHT,500);
    
    set_attack_unarmed(0, 10, 10, W_IMPALE, 30, "bite");
    set_attack_unarmed(1, 10, 10, W_SLASH, 20, "claw");
    
    set_hitloc_unarmed(0, 5, 30, "head");
    set_hitloc_unarmed(1, 5, 30, "tail");
    set_hitloc_unarmed(2, 7, 40, "back");
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
