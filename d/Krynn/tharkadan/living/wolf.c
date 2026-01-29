/*
 * Based on /d/Ansalon/goodlund/nethosak/forest/npc/wolf.c
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Krynn/std/monster";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define A_BITE  0
#define A_LPAW 1
#define A_RPAW 2 

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

string face();
string face2();

void
create_krynn_monster()
{ 
    set_race_name("wolf"); 
    set_adj(face());
    add_adj(face2());
    set_short(face() + " "+face2()+" wolf");
    set_long("This wolf lives in the alpine forests of the " +
             "Tharkadan mountain range. "+
             "These creatures are known to hunt in packs, however "+
             "this one seems to prefer to attack its foes alone. "+
             "As you look closer at it you see its sharp white "+
             "fangs coated with fresh blood.\n");
   
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 37000);
    set_gender(G_NEUTER);
    set_aggressive(1);

    add_leftover("/d/Ansalon/goodlund/nethosak/forest/obj/wolf_hide.c", 
        "skin", 1, 0, 0, 1);

   /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   30, 30, W_IMPALE, 40, "teeth");
    set_attack_unarmed(A_LPAW, 15,  6, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RPAW, 15,  6, W_SLASH,  30, "right paw"); 

    /* Hit_loc,                 *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 20, "head"); 
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   1 }), 45, "body"); 
    set_hitloc_unarmed(H_LEGS, ({  5,  8, 16,   1 }), 35, "legs");

    set_stats(({50+random(20),50+random(10),80,20,20,40+random(10)})); 

    change_prop(LIVE_I_QUICKNESS, 
    query_prop(LIVE_I_QUICKNESS) + 100);

    set_act_time(50);
    add_act("emote howls towards the sky.");
    add_act("drool fero");
    add_act("growl");
    add_act("smell");
    add_act("kill elk");

}

string
face()
{
    // Set first adjective.
    string *faces;
    faces = ({"aggressive", "impressive", "ferocious","strong", "young",
              "adult", "old", "ancient"});
    return faces[random(sizeof(faces))];
}

string
face2()
{
    // Set first adjective.
    string *faces2;
    faces2 = ({"white", "jet-black","deep-brown", "grey", "black",
               "brown"});
    return faces2[random(sizeof(faces2))];
}

void
init_living()
{
     ::init_living();
}


