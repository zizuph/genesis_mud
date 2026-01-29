/* Puppy in Kendermore, Gwyneth, June 12, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";
inherit "/std/act/domove";

/* Randomizes the puppy's colour */

string *colour=({"brown", "grey", "spotted", "black", "white", "tan"});

void
create_creature()
{
    set_name("this_puppy");
    add_name("puppy");
    set_race_name("puppy");
    set_adj(colour[random(6)]);
    set_gender(G_MALE);
    set_long("This puppy has boundless energy, a perfect companion for " + 
        "a kender! Chasing his tail and barking seems to be his favoured " + 
        "activities.\n");

    set_stats(({17,17,17,6,6,17}));

    set_hp(2100);
    set_alignment(0);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_act_time(15);
    add_act("emote wags his tail.");
    add_act("emote barks playfully.");
    add_act("emote bites at your heels.");
    add_act("emote looks at you, hoping for a scrap of food.");
    add_act("@@food");
    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "left paw");
    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "right paw");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    set_random_move(20);
    set_restrain_path(KROOM);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_GET, 0); /* Can be picked up */
    add_prop(OBJ_M_NO_DROP, 0);
    add_prop(CONT_I_WEIGHT, 700);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " barks loudly and chases his tail. He " + 
        "seems more interested in chasing his tail than anything else!\n");
}

string
food()
{
    mixed *food;
    int num;
    food = (all_inventory(TO) + all_inventory(E(TO)));
    for (num = 0; sizeof(food) < num; num++)
    {
        if (food[num]->create_food())
        {
            write("Debug, eat food.\n");
/*        
            TO->command("eat " + food[num]);
*/
            return ""
        }
        if (food[num]->create_food() == 0)
        {
            write("Debug not food.\n");
/*
            write(QCTNAME(TO) + " looks mournfully around for some food.\n");
*/
            return "";    
        }
    return "";
    }
}

