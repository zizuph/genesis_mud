/* This file is /d/Gondor/common/npc/leadorc.c         */
/*                                                     */
/* This orc will attack anyone attacking a member      */
/* of his team                                         */
/* copied in parts from /doc/examples/mobiles/troll.c  */

inherit "/d/Gondor/common/npc/std_orc";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

create_monster()
{
    set_adj("chief");
    ::create_monster();

    set_name("captain");
    set_pname("captains");
    set_short("orc captain");
    set_pshort("orc captains");
    set_long(BS("He looks even more evil than the rest, and he is "
        + "bigger and stronger, too. He seems to be the leader of this pack.\n"));
    default_config_npc(30+random(5));
    set_base_stat(SS_INT, 20+random(5));
    set_base_stat(SS_WIS, 20+random(5));
    set_base_stat(SS_DIS, 95+random(5));
    set_hp(1000+random(4)*100);
    set_aggressive(0);
    set_random_move(5);
    set_restrain_path(({"/d/Gondor/ithilien/road"}));
    set_monster_home(ITH_DIR + "road/mrd2");
    set_alignment(-200-random(5)*50);
    set_skill(SS_WEP_SWORD,30+random(10));
    set_skill(SS_WEP_CLUB,30+random(10));
    set_skill(SS_PARRY,25+random(5));
    set_skill(SS_DEFENCE,30+random(10));

    add_prop(CONT_I_HEIGHT,175+random(20));
    add_prop(CONT_I_WEIGHT,80000+random(10000));
    add_prop(CONT_I_VOLUME,75000+random(20000));

    add_cchat("Kill that spy!");
    add_cchat("Kill it and take his equipment! Saruman will be interested!");
    add_act("shout To me! Everyone to me!");
    add_act("shout Hurry, you bastards! Keep running!");
    add_act("snarl");   
    add_cact("spit");   
}

arm_me()
{
    object wep, arm, roarm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    if (1==random(2)) wep=clone_object(WEP_DIR + "leadsword");
    else wep = clone_object(WEP_DIR + "orcsword");
    wep->move(this_object());
    command("wield all");

    if (1<random(4))
      {
        arm = clone_object(ARM_DIR + "dustlarm");
        arm->move(this_object());
      }

    if (1<random(4))
      {
	arm = clone_object(ARM_DIR + "dushield");
	arm->move(this_object());
      }

    if (1<random(4))
      {
	arm = clone_object(ARM_DIR + "lphelmet");
	arm ->move(this_object());
      }
    command("wear all");
}

/* Solemnian prestige */
query_knight_prestige() { return 450; }
