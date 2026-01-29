/*
 * marsh_zombie.c
 * A marsh zombie for the waterfall area in NW Argos.
 * by Jaacar. August 10, 2003
 * (C) Mike Phipps
 *
 * - Removed tell_watcher function as it was incorrect (Petros)
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Genesis/gems/gem.h"
#include "defs.h"
 
#define A_LHAND 0
#define A_RHAND 1
#define A_TEETH 2
#define A_LFOOT 3
#define A_RFOOT 4
 
#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3
 
void
create_creature()
{
    object gem;

    set_name(({"marsh zombie","zombie"}));
    set_short("ugly skeletal marsh zombie");
    set_pshort("ugly skeletal marsh zombies");
    set_race_name("zombie");
    set_adj(({"ugly","skeletal"}));
    set_long("This ugly creature appears to once have been human, but has "+
        "now been turned into this awful, soulless creature. It has a "+
        "skeletal face, flesh hanging off of its bones and large claw-like "+
        "hands.\n");
 
    set_stats(({ 100, 90, 90, 85, 80, 90}));
 
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 80);
    add_prop(LIVE_I_UNDEAD, 30);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
 
    set_attack_unarmed(A_LHAND, 25, 20, W_SLASH,    20, "left hand");
    set_attack_unarmed(A_RHAND, 25, 20, W_SLASH,    20, "right hand");
    set_attack_unarmed(A_TEETH, 10, 10, W_SLASH,    20, "teeth");
    set_attack_unarmed(A_LFOOT, 20, 25, W_BLUDGEON, 20, "left foot");
    set_attack_unarmed(A_RFOOT, 20, 25, W_BLUDGEON, 20, "right foot");
 
    set_hitloc_unarmed(H_HEAD, ({10, 10, 10, 10 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10, 10, 10, 10 }), 40, "body");
    set_hitloc_unarmed(H_ARMS, ({10, 10, 10, 10 }), 20, "arms");
    set_hitloc_unarmed(H_LEGS, ({10, 10, 10, 10 }), 20, "legs");
 
    set_alignment(-300);
    gem = RANDOM_GEM_BY_RARITY(GEM_COMMON);
    gem->move(TO); 
}
