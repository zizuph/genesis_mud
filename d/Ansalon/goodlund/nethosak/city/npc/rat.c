/* Name: minotaur.
 * Made by: Elmore.
 * Date: April 2000.
 * Equipment: random coins. 
 * Description: A rat that wanders around. It has
 * random description of both the first and second
 * adjectives.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Ansalon/std/monster";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

string face(); 
string face2();

void
create_krynn_monster()
{ 
    set_race_name("rat"); 
    set_name(({"rat"}));
    set_adj(face()); 
    add_adj(face2()); 
    set_short(face() + " " +face2()+ " rat");
    set_long("This is just another filthy little rodent. "+
             "It has some sharp teeth that can shred "+
             "flesh.\n");
   
    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_VOLUME, 3700);
    add_prop(OBJ_I_NO_INS, 1);
    set_gender(G_NEUTER);
    set_random_move(40);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   8, 10, W_IMPALE, 80, "jaws");
    set_attack_unarmed(A_LCLAW, 15,  6, W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW, 15,  6, W_SLASH,  10, "right paw");

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 80, "body");

    set_stats(({10,10,10,10,10,10}));
}

string
face2()
{
    // Set second adjective.
    string *faces2;
    faces2 = ({"black", "grey", "white"});
    return faces2[random(sizeof(faces2))];
}
 
string
face()
{
    // Set first adjective.
    string *faces;
    faces = ({"fat", "thin", "small", "big", "dirty",
               "smelly", "large", "tiny"});
    return faces[random(sizeof(faces))];
}

void
init_living()
{
     ::init_living();
}
