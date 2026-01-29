#pragma save_binary
#pragma strict_types

inherit "/d/Ansalon/std/monster";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

#define A_BITE  0
#define A_LHOOF 1
#define A_RHOOF 2 
#define A_HORN 3

#define H_HEAD 0
#define H_BODY 1 
#define H_HORNS 2
#define H_LEGS 3

string face(); 

void
create_krynn_monster()
{ 
    set_race_name("deer"); 
    set_name(({"deer"}));
    set_adj(face()); 
    set_short(face() + " brown deer");
    set_long("This "+short()+ ", lives in the forest of Mithas. "+
             "This creature is very agile and looks very healthy.\n");
   
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 37000);
    add_prop(OBJ_I_NO_INS, 1);
    set_gender(G_NEUTER);
    set_random_move(60);


    add_leftover(MOBJ + "deer_hide.c", "skin", 1, 0, 0, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   8, 10, W_IMPALE, 70, "sharp teeth");
    set_attack_unarmed(A_LHOOF, 15,  6, W_SLASH,  10, "left hoof");
    set_attack_unarmed(A_RHOOF, 15,  6, W_SLASH,  10, "right hoof"); 
    set_attack_unarmed(A_HORN, 30,  20, W_IMPALE,  10, "horns");

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 20, "head"); 
    set_hitloc_unarmed(H_HORNS, ({ 5, 5,  6,   5 }), 5, "horns");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 45, "body"); 
    set_hitloc_unarmed(H_LEGS, ({  5,  8, 16,   0 }), 30, "legs");

    set_stats(({50+random(20),50+random(10),60,20,20,50+random(10)})); 
    change_prop(LIVE_I_QUICKNESS, 
    query_prop(LIVE_I_QUICKNESS) + 100);

    set_act_time(40);
    add_act("emote eats some green grass.");
    add_act("emote bounces around.");
    add_act("emote looks curiously at you.");
}

string
face()
{
    // Set first adjective.
    string *faces;
    faces = ({"tiny", "small","huge","tall","young",
              "old", "muscular", "ancient"});
    return faces[random(sizeof(faces))];
}

void
init_living()
{
     ::init_living();
}

