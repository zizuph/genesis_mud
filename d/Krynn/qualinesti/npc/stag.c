/* stag.c
 * Stag created for Krynn
 *
 * Blizzard 01/2003
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

string  *adj_list = ({ "massive", "big-nosed", "big", "alert", "large" });
string  *adj_list2 = ({ "proud", "young", "brown-furred", "wild", "old" });
string  adj1;
string  adj2;
string  race;

void
create_creature() 
{
    int i;
    if ( random(2) )
        race = "stag";
    else
        race = "deer";
    adj1 = adj_list[random(sizeof(adj_list))];
    adj2 = adj_list2[random(sizeof(adj_list2))];        
    set_short(adj1 + " " + adj2 + " " + race);
    set_race_name(race);
    set_name(race);
    set_adj(({ adj1, adj2 }));
    set_long("The massive animal standing before you is covered in a " +
        "brown fur. It walks around and presents the fully-grown antlers, " +
        "making a real impression on you. Those horns, shaped like " +
        "branches can be easily used as a dangerous weapon.\n");
    
    set_alarm(1.0,0.0, "set_m_in", "walks in");
    set_alarm(1.0,0.0, "set_m_out", "walks");
    for (i=0;i<6;i++)
        set_base_stat(i, 35 + random(5));
    
    set_knight_prestige(0);
    set_alignment(0);
    
    set_hp(query_max_hp());

    set_alarm(1.0,0.0,"set_restrain_and_home",0);
    set_random_move(25);
    
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE, 30);

    CUTLEFTOVER("antlers");
    CUTLEFTOVER("rib");
    
    set_act_time(2);
    add_act("emote paces proudly around.");
    add_act("emote lifts his head and stares into the forest.");
    add_act("emote scratches a tree with his antlers.");
   
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_WEIGHT, 50000 + random(5000));
    add_prop(CONT_I_VOLUME, 40000 + random(5000));
    
    set_attack_unarmed(0, 20, 25, W_IMPALE, 30, "antlers");
    set_attack_unarmed(1, 20, 25, W_BLUDGEON, 20, "rear hooves");
    
    set_hitloc_unarmed(0, 13, 10, "head");
    set_hitloc_unarmed(1, 12, 40, "legs");
    set_hitloc_unarmed(2, 15, 50, "body");
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
