/* 
    This is an air spirit that the guardian of the Marble Tower will
    summon to attack and hunt any attackers.
    
    Bishop of Calia, July 2003.    
*/

#pragma strict_types

inherit "/std/monster.c";
inherit "/std/combat/unarmed.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <options.h>
#include <const.h>

#include "defs.h"

object hunted;

void
create_monster()
{
    set_name("spirit");
    add_name("_college_hunting_spirit");
    
    set_race_name("elemental");

    set_gender(G_NEUTER);

    add_adj("wispy");
    add_adj("translucent");
    
    set_short("wispy translucent spirit");

    set_long("This practically invisible being seems composed" +
        " entirely out of wind. You can more easily hear it than" +
        " see it.\n");        
            
    set_alignment(0);
    
    set_mm_in("blows in");
    set_mm_out("disappears");

    set_base_stat(SS_STR, 60);
    set_base_stat(SS_DEX, 140);
    set_base_stat(SS_CON, 120);
    set_base_stat(SS_INT, 30);
    set_base_stat(SS_WIS, 30);
    set_base_stat(SS_DIS, 100);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_HEIGHT, 200);
    
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_SEE_INVIS, 10);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_I_RES_AIR, 100);
    add_prop(OBJ_I_INVIS, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    set_attack_unarmed(0, 43, 35, W_BLUDGEON, 100, "windy blast");
    set_hitloc_unarmed(0, 30, 100, "body");
}

void
do_follow()
{
    if (!objectp(hunted))
    {
        move_living("X", TEMP_ROOM);
        remove_object();
        return;
    }
    
    if (!present(hunted, environment(TO)))
    {
        move_living("X", environment(hunted));
        command("kill " + OB_NAME(hunted));
    }
    
    if (!objectp(query_attack()))
    {
        move_living("X", TEMP_ROOM);
        remove_object();
        return;
    }
    
    set_alarm(1.0, 0.0, &do_follow());
}


void
start_hunting(object enemy)
{
    hunted = enemy;
 
    command("kill " + OB_NAME(hunted));
    set_alarm(1.0, 0.0, &do_follow());
}
