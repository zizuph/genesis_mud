/* created by Aridor 10/12/93 */
/*Copied and altered for Icewall by Macker 07/16/94*/
/*Sex change preformed by Macker 07/17/94*/


#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit C_FILE
inherit "/std/act/domove";  

void
create_creature()
{
    int i;
    
    set_name("wolf");
    set_race_name("wolf");
    set_adj("white");
    add_adj("snow");
    
    set_gender(0);
    set_long("It is a huge white wolf. He is very furry to "
	     + "withstand the cold in this icy region. The wolf's white "
	     + "coat almost camouflages him with the snow on the ground.\n");
    
    set_stats(({ 30, 40, 60, 10, 10, 30}));
    
    set_monster_home(ICE_FOREST+"forest_5.c");
    set_restrain_path(ICE_FOREST);
    set_random_move(30);
    
    set_hp(5000);
    set_alignment(-50);
    set_knight_prestige(50);
    
    NEVERKNOWN;
    
    set_skill(SS_DEFENCE, 20);
    set_attack_unarmed(1, 10, 10, W_SLASH,  25, "right claws");
    set_attack_unarmed(2, 30, 30, W_IMPALE, 50, "bite");
    set_attack_unarmed(4, 10, 8, W_BLUDGEON , 5, "left paw");
    
    set_hitloc_unarmed(1,  10, 50, "body");
    set_hitloc_unarmed(2,  10, 10, "left paw");
    set_hitloc_unarmed(4,  10, 10, "right paw");
    set_hitloc_unarmed(8,  10, 12, "left leg");
    set_hitloc_unarmed(16, 10, 12, "right leg");
    set_hitloc_unarmed(32,  5,  6, "head");
    
    
}

