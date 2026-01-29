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
#define A_LPAW 1
#define A_RPAW 2 

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

string face(); 

void
create_krynn_monster()
{ 
    set_race_name("fox"); 
    set_adj(face()); 
    set_short(face() + " red fox");
    set_long("This is a red fox from the forest "+
             "of Mithas. It isn't very big, but "+
             "it still looks quite dangerous with "+
             "it's sharp teeth and long claws.\n");
   
    add_leftover(MOBJ + "fox_hide.c", "skin", 1, 0, 0, 1);

    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 37000);
    add_prop(OBJ_I_NO_INS, 1);
    set_gender(G_NEUTER);
    set_random_move(60);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE, 20, 10, W_IMPALE, 70, "teeth");
    set_attack_unarmed(A_LPAW, 15,  6, W_SLASH,  15, "left paw");
    set_attack_unarmed(A_RPAW, 15,  6, W_SLASH,  15, "right paw"); 

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 25, "head"); 
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 45, "body"); 
    set_hitloc_unarmed(H_LEGS, ({  5,  8, 16,   0 }), 30, "legs");

    set_stats(({30+random(20),30+random(10),30,10,20,40+random(10)})); 
}

string
face()
{
    // Set first adjective.
    string *faces;
    faces = ({"small","young","mature","old",
              "dirty", "muscular"});
    return faces[random(sizeof(faces))];
}

void
init_living()
{
     ::init_living();
}

