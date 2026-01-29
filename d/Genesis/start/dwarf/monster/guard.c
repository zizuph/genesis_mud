#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "../defs.h"
#include "../qbits.h"

/* wh|||!! A quest! */

void
create_monster()
{
    set_name("guard");
    set_adj("sturdy");
    add_name("dwarf");
    set_race_name("dwarf");
   
    set_long("The sturdy guard looks, well, rather sturdy.\n");
//     set_short("honourary guard is guarding the entrance to the throne");
//     set_pshort("honourary guards are guarding the entrance to the throne");
    set_short("honourary guard");

    set_act_time(30+random(30));
    add_act("emote stares at you, very suspiciously.");

    default_config_npc(50);
  
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_PARRY,30);
    set_skill(SS_DEFENCE,20);
}

void
arm_me()
{
    clone_object(D_OBJ+"axe3")->move(TO);
    clone_object(D_OBJ+"mail2")->move(TO);

    command("wield all");
    command("wear all");
}



