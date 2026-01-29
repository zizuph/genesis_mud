#include "/d/Ansalon/common/defs.h"
inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

public void remove_descr();
int standing = 1;

void
create_dragon_npc()
{
    ::create_dragon_npc();
    set_age("ancient");
    add_name("malachite");
    set_gender(G_MALE);
    set_colour("green");
    set_long("@@dragon_long");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_act_time(20);

    add_act("@@addact_1");
    add_act("@@addact_2");

    set_cact_time(5);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
      "terrifying roar!");
    add_cact("grin");

}

string
addact_1()
{
    if(standing)
        return "emote looks at you with cold hatred in its eyes.";
    else
        return "emote clears his throat in his sleep, emitting a " +
            "small puff of foul smelling gas.";
}

string
addact_2()
{
    if(standing)
        return "emote stalks around you, the hunter cornering its prey.";
    else
        return "emote moves slightly in his sleep.";
}

string
dragon_long()
{
    if(standing)
        return "Staring at you with blood-red malevolent eyes is a " +
            "huge green dragon! A sinuous ninety feet in length from snout " +
            "to tail tip, its armour-like scales are a deep green, scarred " +
            "and mossy - making it able to blend easily in to woodland " +
            "surroundings.\n";
    else
        return "Lying coiled asleep in the middle of the upper platform is " +
            "the sinuous form of a huge green dragon! Ninety feet in length " +
            "from snout to tail tip, its armour-like scales are a deep " +
            "green, scarred and mossy - making it able to blend easily in " +
            "to woodland surroundings.\n";

}

/*
 * Function:	attacked_by
 * Arguments:	attacker - The attacker
 * Description:	This function is called when somebody attacks this object 
 */

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    if(!standing)
    {
       remove_descr();
       command("emote roars in outrage, rising up over you " +
           "with wings aggressively outstretched."); 
    }
}

/*
 * Funtion Name: add_desc
 * Description : Adds extra short description.
 */

public void
add_descr(string description)
{
    add_prop(LIVE_S_EXTRA_SHORT, " " + description);
}

/*
 * Function:	remove_descr
 * Description:	Remove the extra description
 */

public void
remove_descr()
{
    remove_prop(LIVE_S_EXTRA_SHORT);
}

void
attack_object(object ob)
{
    if(!standing)
    {
       remove_descr();
       command("emote snarls at you with a maw full of sabre-sharp " +
           "teeth.");
       standing = 1;
     }

    ::attack_object(ob);
}

public void
sit_down()
{
    if(!standing) 
        return;

    command("emote curls amongst his treasure and closes his eyes.");
    add_prop(LIVE_S_EXTRA_SHORT, " coiled asleep in the middle of " +
        "the platform");
    standing = 0;
    return;
}

void
attack_intruder(object enemy)
{
    if(!CAN_SEE(TO, enemy))
    {
	return;
    }

    if(TO->query_attack())
      return;

    command("emote rapidly uncoils and snarls at you with a maw full " +
        "of sabre-sharp teeth!"); 
    command("kill " +enemy->query_real_name());
    return;
}

public void
stand_up(object enemy)
{
    if(standing)
        return;
    remove_descr();
    command("emote opens his eyes and stares malevolently at you.");
    command("emote hisses: Ah, breakfast has been delivered.");

    set_alarm(3.0, 0.0, &attack_intruder(TP));
    standing = 1;
    return;
}

void 
init_living() 
{
    if(CAN_SEE(TO, TP))
      set_alarm(3.0, 0.0, &stand_up(TP));
 
    ::init_living(); 
}
