/*
rat.c

The rat of the sewers of Kalaman
Created by Arcturus
11.04.2005

*/

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

inherit "/std/act/action";
inherit C_FILE
inherit "/std/act/domove";


#define A_BITE  1
#define A_LCLAW 2
#define A_RCLAW 4

#define H_HEAD 1
#define H_BODY 2


void
create_creature()
{
    if(!IS_CLONE)
      return;
    
    string *first, *second;
    
    set_name("rat");
    
    first = ({"small", "tiny", "fat", "nervous", "little", "big" });
    second = ({"black", "brown", "smelly", "white", "hairy", "spotted" });
    
    set_adj(one_of_list(first));
    add_adj(one_of_list(second));

    set_long("A typical sewer rat of Kalaman.\n");
        
    set_race_name("rat");
    
              /* STR DEX CON INT WIS DIS */
    set_stats(({ 15, 25, 7,  3,  3, 70 }));

    set_gender(random(2));
    set_hp(1000);
    set_alignment(0);
    set_random_move(3, 1);
    
    /* Arguments to set_attack_unarmed: 
     *   attack id, hit, pen, damage type, percent usage, description
     */
    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "teeth");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    /* Give the rat some hit locations */

    /* Arguments to set_hitloc_unarmed:
     *   hit location id, ac, percent hit, description
     */
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30,}), 80, "body");
    
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
    
    set_act_time(9 + random(3));
    
    add_act("emote searches around looking for food.");
    add_act("emote squeeks loudly.");
    add_act("emote looks at you for a brief moment.");
    add_act("emote briefly licks "+HIS(TO)+" paw.");
    add_act("emote flips "+HIS(TO)+" tail around.");
    
}
