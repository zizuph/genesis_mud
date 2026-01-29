/* This file is /d/Gondor/common/npc/farm/capdunl.c     
 *
 * Changes:
 *  Commented out the set_whimpy()
 *  --Raymundo, April 2020
 */
#pragma strict_types
inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";

#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string  alignlook();

void
create_monster()
{
    FIX_EUID
    	
    set_name("captain");
    add_name(({"man","leader","dunlending"}));
    set_pname("dunlendings");
    add_pname("men");
    set_pshort("men");
    set_race_name("human"); 
    set_adj(alignlook());
    set_long(BSN("A dunlending, dark-haired and green-eyed. He looks to be "+
    	"the leader of the dunlendings here. He's a giant of a man, and a "+
    	"look out of his eyes seems to be capable of killing lesser men."));
    default_config_npc(85+random(5));

    set_restrain_path( ({FARM_DIR + "farm"}) );
    set_monster_home( ({FARM_DIR + "farm/path3"}) );

    set_alignment(-300-random(200));
    set_aggressive(1);
    set_skill(SS_WEP_SWORD,80+random(5));
    set_skill(SS_PARRY,60+random(5));
    set_skill(SS_DEFENCE,80+random(5));
    add_prop(CONT_I_HEIGHT,200);
    add_prop(CONT_I_WEIGHT,85000);
    add_prop(CONT_I_VOLUME,55000);    
    add_prop(LIVE_I_NEVERKNOWN,1);

   // set_whimpy(20);

    set_chat_time(40 + random(15));
    add_chat("Burn the farm, no more looting!");
    add_chat("Get moving, we're leaving now!");
    set_cchat_time(10 + random(9));
    add_chat("All men to me! Kill him, don't let him escape!");
    add_cchat("Finish him!");
    add_cchat("No prisoners, no witnesses!");
    add_cchat("Don't let him escape, he must die so the rohirrim "
      + "don't learn about us!");
    add_cchat("You should have minded your own business!");
    set_act_time(10+random(15));
    add_act("growl");
    add_act("shout To me! Everyone to me!");
    add_act("snarl");
}

void
arm_me()
{
    clone_object(WEP_DIR + "dulsword")->move(TO);
    command("wield all");

    clone_object(ARM_DIR + "dustlarm")->move(TO);
    clone_object(ARM_DIR + "dushield")->move(TO);
    clone_object(ARM_DIR + "lphelmet")->move(TO);
    command("wear all");

    MONEY_MAKE_SC( 25 + random(51))->move(TO);
    MONEY_MAKE_GC(  5 + random(16))->move(TO);
}

string
alignlook()
{
    string *alignlooks =
        ({"veteran", "grim", "grumpy", "experienced", "sturdy", 
          "massive", "big", "cruel", "angry", "mean", "dirty", "foul",
          "brutal", "battered", "savage", "ugly", "dangerous"});
    return alignlooks[random(sizeof(alignlooks))];
}

int query_knight_prestige() { return 1000; }

