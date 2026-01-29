/*
 *      /d/Gondor/common/npc/farm/dunscout.c
 *
 *      Coded 1992 by Olorin.
 *
 *  Changes:
 *   Commented out the set_whimpy()
 *   --Raymundo, April 2020
 */
#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    set_name("scout");
    add_name("dunlending");
    add_name("man");
    set_pname("scouts");
    add_pname("dunlendings");
    add_pname("men");
    set_pshort("men");
    set_race_name("human"); 
    set_adj("dark-haired");
    set_long("A dunlending, dark-haired and green-eyed. He is "
        + "probably a scout, looking for easy victims for him and his "
        + "comrades to raid.\n");
 
    default_config_npc(20+random(10));
    set_base_stat(SS_INT, 25+random(5));
    set_alignment(-100-random(5)*20);

    set_skill(SS_WEP_SWORD, 20 + random(16));
    set_skill(SS_PARRY,     15 + random(16));
    set_skill(SS_BLIND_COMBAT, 40 + random(21));
    set_skill(SS_DEFENCE,   20 + random(21));
    set_skill(SS_AWARENESS, 40 + random(21));
    set_skill(SS_SNEAK,     20 + random(11));
    set_skill(SS_HIDE,      20 + random(11));

    set_aggressive(0);
    set_random_move(30);
    set_restrain_path(({FARM_DIR + "road"}));
    set_monster_home(({FARM_DIR + "road/road3"}));

    add_prop(CONT_I_HEIGHT,   180);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 72000);    
    add_prop(LIVE_I_NEVERKNOWN, 1);

    //set_whimpy(35);

    set_chat_time(10 + random(9));
    add_chat("I hope the others finished the rohirrim on that other farm.");
    add_chat("Too bad we have to hide ourselves!");
    add_chat("The stupid rohirrim will never find the path through the bushes!");
    set_cchat_time(5 + random(9));
    add_cchat("You'll regret this!");
    add_cchat("Why did you attack me? I'm just a traveller!");
    add_cchat("I will kill you for this! Die, fool!");
    add_cchat("Be damned, Rohirrim lover!");
    set_act_time(10+random(15));
    add_act("burp");
    add_act("hiss");
}

public void
arm_me()
{
    seteuid(getuid(this_object()));

    clone_object(WEP_DIR + "dussword")->move(TO);
    command("wield all");

    clone_object(ARM_DIR + "dustlarm")->move(TO);
    command("wear all");

    MONEY_MAKE_CC( 20 + random(16))->move(TO);
    MONEY_MAKE_SC(  2 + random( 5))->move(TO);
}

public int query_knight_prestige() { return 300; }

/*
 * Function name: oke_to_move
 * Description:   Checks whether the npc is fighting someone, if he is in
 *                in combat, the move-command will be delayed till the 
 *                war is over.
 * Arguments:     exit  : the exit that is generated for the monster to take.
 * Returns:       0     : if in combat
 *                string: the exit that the monster takes if not in combat.
 */
mixed
oke_to_move(string exit)
{
    if (this_object()->query_attack())
        return 0;

    return "sneak " + exit;
}
