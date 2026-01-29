/*
    ../common/sewers/guard

    JnA 920115 .. MA 93

    This guard gives an example of how to use the sequence actions in
    combination with VBFC. It is used to wield and wear.

*/
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

#define WEP SEWERS(sword)
#define ARM SEWERS(shield)

create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

    set_name("perry");
    set_race_name("human"); 
    set_adj("cautious");
    set_long("He is a guard keeping watch over this area.\n");

    /* Average stat: 10
     */
    default_config_npc(10);          

    /* But we want it to have better dex
     */
    set_base_stat(SS_DEX, 20);
    set_skill(SS_WEP_SWORD,40);

    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Don't try me, punk."}));
}

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object(WEP);
    wep->move(this_object());
    command("wield sword");

    arm = clone_object(ARM);
    arm->move(this_object());
    command("wear shield");
}

/* The rest here is to get this mobile to be a nice buddy and if he is in a
 * team and he or a members gets attacked he will join the fight.
 */
/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    if (random(10))
        set_alarm(1.0, 0.0, "help_friend", attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say You'll regret this.");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

