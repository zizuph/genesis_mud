/* horse.c
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
inherit "/std/act/action";

string  *adj_list = ({ "massive", "strong", "old" });
string  *adj_list2 = ({ "black", "brown", "chestnut" });
string  adj1;
string  adj2;

void
create_creature() 
{
    int i;
    adj1 = adj_list[random(sizeof(adj_list))];
    adj2 = adj_list2[random(sizeof(adj_list2))];        
    set_race_name("stallion");
    add_name("horse");
    set_name("stallion");
    set_gender(G_MALE);
    set_adj(({ adj1, adj2 }));
    set_long("This large muscular horse looks like he is " +
        "used to pull heavy loads. He paces slowly around, " +
        "resting before another course.\n");
    
    for ( i = 0; i < 6; i++)
        set_base_stat(i, 50 + random(10));
    
    set_knight_prestige(0);
    set_alignment(0);
    
    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE, 30);

    set_act_time(2);
    add_act("emote paces slowly around.");
    add_act("emote lowers his head and nibbles some grass.");
    add_act("emote lifts his head.");
    add_act("emote nibbles some leaves.");
    
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_WEIGHT, 50000 + random(5000));
    add_prop(CONT_I_VOLUME, 40000 + random(5000));
    
    set_attack_unarmed(0, 20, 25, W_IMPALE, 30, "front hooves");
    set_attack_unarmed(1, 20, 25, W_BLUDGEON, 20, "rear hooves");
    
    set_hitloc_unarmed(0, 13, 10, "head");
    set_hitloc_unarmed(1, 12, 40, "legs");
    set_hitloc_unarmed(2, 15, 50, "body");
}

