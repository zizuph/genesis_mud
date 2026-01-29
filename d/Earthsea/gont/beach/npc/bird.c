/*
 * Birds on the beach
 * Coded by Finwe
 * June 1997
 */

#pragma strict_types

inherit "/std/creature";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include "default.h"
#include <stdproperties.h>

#define A_BEAK 50
#define H_BODY 100
#define H_R_WING 101
#define H_L_WING 102

public void
create_creature()
{
    string type, color, size;

    add_name("bird");

    switch(random(4))
    {
        case 0:
            type = "seagull";
            color = ({ "white", "gray" })[random(2)];
        break;
        case 1:
            type = "puffin";
            color = ({ "black", "white-chested", "gray" })[random(3)];
        break;
        case 2:
            type = "kingfisher";
            color = ({ "blue-gray", "light-gray", "green-and-white"})[random(3)];
            if(color == "green-and-white") {
                add_adj("green");
                add_adj("white");
            }
        break;
        case 3:
            type = "pelican";
            color = ({ "white", "dirty-gray", "tired" })[random(3)];
        break;
    }

    add_name(type);
    add_adj(color);
    add_adj(size = ({"large", "medium", "small"})[random(3)]);

    set_short(size + " " + color + " " + type);
    set_race_name(type);
    set_long("A " + size + " " + type + ". This bird is "+
      "common along the shores and cliffs on the island of "+
      "Gont.\n");
    set_gender(0);
    set_random_move(60);
    set_restrain_path(BEACH);
    set_m_in("flies in");
    set_m_out("flies away");
    set_skill(SS_DEFENCE, 5);
    set_skill(SS_UNARM_COMBAT, 10);
    set_attack_unarmed(A_BEAK, 10, 5, W_IMPALE, 100, "snapping beak");
    set_hitloc_unarmed(H_BODY, 10, 40, "body");
    set_hitloc_unarmed(H_R_WING, 10, 30, "right wing");
    set_hitloc_unarmed(H_L_WING, 10, 30, "left wing");
    add_prop(NPC_I_NO_LOOKS, 1);

    if(type == "puffin" || type == "seagull")
    {
        add_leftover("/d/Earthsea/gont/beach/obj/gull_gut", "gut", 1, 0, 0, 0);
    }
}
