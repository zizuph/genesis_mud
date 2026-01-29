/* Ashlar, 9 Jun 97 */

/*
 * Mercade, 26 June 2004: Torch handling recoded. Threw out the repeating
 *    alarm that would check every 10 seconds whether the NPC could still
 *    see. Ugh, with 30 NPC's, that's rather wasteful!
 */

/* Navarre 24th June 2006, raised stats a little. */

#include "../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#include NERAKA_REPORT

void
arm_me(int level)
{
    string *arm =
        ({ NWEP+"broadsword", "gplate", "chainhelm", "chaingreaves"
        });
    object tmp;
    int i;
    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(arm); i++)
    {
	    if (arm[i][0..0] == "/")
	        tmp = clone_object(arm[i]);
	    else
	        tmp = clone_object(NARM + arm[i]);
	    tmp->move(TO);
    }

    command("wield all");
    command("wear all");
}

void
create_krynn_monster()
{
    int i,j = random(2) + 8;

    if (!IS_CLONE)
        return;
    
    set_name("guard");
    add_name("cityguard");
    add_name("_cityguard_");
    set_race_name(one_of_list(({"human","human","human","half-elf","half-elf",
        "goblin","goblin"})));
    set_adj(({"imposing","bearded","scarred","weathered",
        "swarthy","dark-eyed","frowning"})[random(7)]);
    add_adj("city");
    set_short(implode(query_adjs()," ")+" guard");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    switch(query_race_name())
    {
        case "human":
            set_long("This human is a City Guard of Neraka. He " +
                "looks professional, and studies you calmly.\n");
            break;
        case "half-elf":
            set_long("This half-elf is a City Guard of Neraka. He looks " +
                "aggressive, staring at you with barely concealed anger.\n");
            break;
        case "goblin":
            set_long("This goblin is a City Guard of Neraka. He handles " +
                "his weapon with a nervous incompetence.\n");
            break;
    }

    for(i=0; i<6; i++)
        set_base_stat(i, j * 15 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_PARRY, j * 8 + random(20));
    set_skill(SS_WEP_SWORD, j * 7 + random(20));
    set_skill(SS_WEP_KNIFE, j * 7 + random(20));
    set_skill(SS_WEP_CLUB, j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_JAVELIN, j * 4 + random(20));
    set_skill(SS_WEP_AXE, j * 7 + random(20));

    set_alignment(-500);
    set_knight_prestige(0);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);

    set_pick_up_team(({"_cityguard_"}));

    set_act_time(8);
    add_act("emote polishes his sword.");
    add_act("say I hope the armies won't stir up any more trouble.");
    add_act("yawn");
    add_act("emote adjusts his armours.");
    add_act("say We will keep the peace, even if we have to fight for it.");

    set_cact_time(4);
    add_cact("sneer all");
    add_cact("smile confid");
    add_cact("say This is not respect!");
    add_cact("sweat");

    SET_NERAKA_AGGRESSIVE;
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
void
attack_object(object ob)
{
    object *arr;
    int i;

    ::attack_object(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
    {
        arr[i]->notify_ob_attacked_me(this_object(), ob);
    }
}

/*
 * Function name: aggressive_attack
 * Description:   We are aggressive, let us attack
 * Arguments:         ob - the object to attack
 */
public void
aggressive_attack(object ob)
{
    if (!objectp(ob) || !present(ob, environment(this_object())))
        return;

    command("shout Death to the enemies of Neraka!");
    command("kill " + ob->query_real_name());
}

/*
 * Function name: help_friend
 * Description:   Help a teammate in trouble by attacking someone
 * Arguments:     ob - the object to attack
 */
public void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("shout I'll get that scum!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

/*
 * Function name: check_visibility
 * Description  : Called to see whether this living can see in the room. If
 *                this is not the case, clone a torch and light it.
 */
void
check_visibility()
{
    if (!CAN_SEE_IN_ROOM(TO))
    {
        if (!present("torch") && environment()->query_prop(NERAKA_I_ROOM_HAS_TORCHES))
        {
            clone_object(NOBJ + "torch")->move(this_object(), 1);
            say(QCTNAME(TO) + " fetches a torch.\n");
        }

        if (random(2))
        {
            command("say Cursed dark in here!");
        }
        command("light torches");
    }
}

/*
 * Function name: hook_torch_burned_out
 * Description  : When the torch carried by this living burns out, we drop it.
 *                After some time look whether we can see in the room or not.
 * Arguments    : object torch - the torch that burned out.
 */
void
hook_torch_burned_out(object torch)
{
    command("drop " + OB_NAME(torch));

    set_alarm(10.0, 0.0, check_visibility);
}

/*
 * Function name: enter_env
 * Description  : Called when this NPC enters another room.
 * Arguments    : object to - where we go to.
 *                object from - where we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env();

    /* Check whether we can see in the room. */
    check_visibility();
}
