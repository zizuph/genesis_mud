#pragma save_binary 
#pragma strict_types 

inherit "/d/Ansalon/std/monster"; 
inherit "/std/combat/unarmed"; 

inherit "/std/act/domove"; 
#include <wa_types.h> 
#include <macros.h> 
#include <stdproperties.h> 
#include <ss_types.h> 
#include "../local.h" 

#define A_BITE 0 
#define A_LPAW 1 
#define A_RPAW 2 

#define H_HEAD 0 
#define H_BODY 1 
#define H_LEGS 2 

void 
create_krynn_monster() 
{ 
    set_name("hound");
    set_race_name("hellhound");
    set_adj("flaming-red"); 
    add_adj("hell"); 
    set_short("flaming-red hell hound"); 
    set_long("This is a hellhound. A creature of nightmares, it has been summoned "+
      "from the depths of the Abyss by the fell undead servants of Lord Soth. "+
      "Its two narrow eyes glow malevolently, and its charcoal pelt seems to smoulder "+
      "with an unholy fire.\n"); 

    add_prop(CONT_I_WEIGHT, 40000); 
    add_prop(CONT_I_VOLUME, 37000); 
    add_prop(OBJ_I_NO_INS, 1); 
    set_gender(G_NEUTER); 
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 79);
    set_skill(SS_AWARENESS, 75);
    set_alignment(-1200);
    set_knight_prestige(80);
    add_prop(LIVE_I_UNDEAD, 100);

    add_leftover(DARM + "pelt.c", "pelt", 1, 0, 0, 1); 

    /* Wep_type,      to_hit,   pen,  Dam_type,   %usage,   attack_desc */ 
    set_attack_unarmed(A_BITE,   40, 40, W_IMPALE, 70, "sharp fangs"); 
    set_attack_unarmed(A_LPAW,  35,  35, W_SLASH,  15, "left paw"); 
    set_attack_unarmed(A_RPAW,  35,  35, W_SLASH,  15, "right paw"); 

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */ 
    set_hitloc_unarmed(H_HEAD, ({ 40, 44, 46,   5 }), 25, "head"); 
    set_hitloc_unarmed(H_BODY, ({ 35, 38, 46,   0 }), 45, "body"); 
    set_hitloc_unarmed(H_LEGS, ({ 35, 38, 46,   0 }), 30, "legs"); 

    set_stats(({120,145,130,70,50,150})); 

    set_act_time(40); 
    add_act("growl"); 
    add_act("emote raises its head and howls eerily!"); 
    add_act("emote snarls aggressively."); 
} 

void 
init_living() 
{ 
    ::init_living(); 
}
