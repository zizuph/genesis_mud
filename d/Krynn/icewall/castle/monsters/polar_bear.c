/* a polar bear that leaves yellow snow
created for Icewall by Stevenson */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
inherit C_FILE

inherit "/std/act/domove";
inherit "/d/Krynn/std/act/follow";
inherit "/std/act/action";

object bear_follows = 0;

void 
create_creature() 
{
    int i;
    set_short("polar bear");
    set_gender(G_MALE);
    set_name("bear");
    add_name("icebear");
    set_adj("polar");
    set_race_name("bear");
    set_long("You see before you a large polar bear.  He is covered "
        + "in thick, white fur.  Because of his size you dare not attack. "
        + "\n");
   
    set_alarm(1.0, 0.0,"set_m_in", "crashes in");
    set_alarm(1.0, 0.0,"set_m_out","crashes");
   
    for (i=0;i<6;i++)
        set_base_stat(i, 70+random(5));
   
    set_skill(SS_DEFENCE, 15);
    set_knight_prestige(-4);
    set_alignment(500);
   
    set_monster_home(ICE_PLAINS + "plain_5");
    set_restrain_path(ICE_PLAINS);
    set_random_move(30);
   
    set_act_time(3);
    add_act("@@pee");
    add_act("emote growls menacingly.");
    add_act("emote rolls over in the snow.");
   
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_VOLUME,12000);
    add_prop(CONT_I_WEIGHT, 700000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
   
    set_attack_unarmed(0, 40, 40, W_BLUDGEON, 60, "paw");
    set_attack_unarmed(1, 40, 40, W_IMPALE, 30, "jaws");
    set_attack_unarmed(2, 20, 20, W_BLUDGEON, 10, "fishy breath");
   
    set_hitloc_unarmed(0, 50, 30, "leg");
    set_hitloc_unarmed(0, 50, 40,"body");
    LEFTOVER("tongue");
    LEFTOVER("skull");
    CUTLEFTOVER("innards");
}

string 
pee() 
{
    if (!P("pee",E(TO)) && (random(100)>80)) 
    {
        seteuid(getuid());
        clone_object(ICE_CAST_O+"yellow_snow")->move(E(TO));
        return "emote raises its rear leg and urinates.";
    }
    return "emote scratches himself behind the ear.";
}

void 
enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);
   
    if (ob->id("icefish") && !(from->test_bit("Krynn", 2, 17))) 
    {
        set_follow(from);
        bear_follows = from;
        ob->remove_item();
        set_alarm(1.0, 0.0, "command", "eat fish");
        set_alarm(1.0,0.0,"command","lick "+from->query_real_name());
    }
}

object 
ret_follow() 
{ 
    return bear_follows; 
}
