/* Ashlar, 9 Jun 97 */
/* Navarre june 24th, raised stats a little */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#include NERAKA_REPORT

#ifndef ONE_OF
#define ONE_OF(x)   (x)[random(sizeof(x))]
#endif

void
check_status()
{
    if (!P("torch",TO) && (E(TO)->query_prop(NERAKA_I_ROOM_HAS_TORCHES)))
    {
        object t;
        t = clone_object(NOBJ+"torch");
        if (t)
        {
            t->move(TO,1);
            say(QCTNAME(TO) + " fetches a torch.\n");
        }
    }

    if (!CAN_SEE_IN_ROOM(TO))
    {
        if(random(2))
            command("say Cursed dark in here!");
        command("light torches");
    }
}

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
    int i,j = 10;

    if (!IS_CLONE)
        return;
    
    set_name("guard");
    add_name("cityguard");
    add_name("_cityguard_leader_");
    set_race_name(ONE_OF(({"human","human","human","half-elf","half-elf",
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

    set_alignment(random(30)-15);
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

    set_alarm(itof(random(10)), 10.0, check_status);

    set_patrol_time(10);
    set_patrol_path(({"w","sw","sw","s","sw","s","s","s","s","s","s","s","s",
        "se","se","e","e","ne","ne","ne","ne","n","n","n","n","nw","n","n",
        "nw","w","w","sw","sw","s","s","s","s","s","s","se","e","e","ne","n",
        "n","n","n","nw","w","n","n","n","n","n"}));
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
        arr[i]->notify_ob_attacked_me(this_object(), ob);    
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

    command("shout Get that murdering scum!");
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
        command("say I'll get you for this.");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
