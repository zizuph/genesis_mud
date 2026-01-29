/* Ashlar, 21 Oct 97 
 *
 * Louie April 2006 - Granted guardians of the temple see invis/darkness.
 *          Boosted stats/skills significantly.
 */

/*
 * Navarre January 4th 2008, Removed reveal_all command in init living as it got
 * to be one of the most executed commands in the game.
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#ifndef ONE_OF
#define ONE_OF(x)   (x)[random(sizeof(x))]
#endif

/* The temple guards do not team with each other, they should be lead by
   priests */

void
arm_me(int level)
{
    string *arm =
        ({ NWEP + "mace", NARM + "black_chain_shirt",
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

    add_cmdsoul(NSTD + "templar");
    update_hooks();
}

void
create_krynn_monster()
{
    int i,j = random(2) + 8;

    if (!IS_CLONE)
        return;
    
    set_name("guard");
    add_name("templeguard");
    add_name("_templeguard_");
    set_race_name(ONE_OF(({"human","human","human","half-elf","half-elf",
        "goblin","goblin"})));
    set_adj(({"imposing","bearded","scarred","weathered",
        "swarthy","dark-eyed","frowning"})[random(7)]);
    add_adj("temple");
    set_short(implode(query_adjs()," ")+" guard");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 100);

    set_long("The " + query_race() + " is a member of the Temple Guard, " +
    "responsible for the inner security of the temple. He looks like " +
    "a very good fighter.\n");

    set_stats(({ 145 + random(30), 145 + random(20),
    	        155 + random(30), 110, 110,
    	        135 + random(20) }));
    	        
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_AWARENESS, 70 + random(30));
    set_skill(SS_BLIND_COMBAT, 60);

    add_prop(LIVE_I_SEE_INVIS, 20);
    add_prop(LIVE_I_SEE_DARK, 5);

    set_alignment(-750);
    set_knight_prestige(750);

    set_all_attack_unarmed(20,20);
    set_all_hitloc_unarmed(10);

    set_aggressive("@@check_for_attack@@");
}

int
check_for_attack()
{
    return TP->query_prop(NERAKA_I_ATTACKED_TEMPLE);
}

void
attacked_by(object attacker)
{
    attacker->add_prop(NERAKA_I_ATTACKED_TEMPLE, 1);
    ::attacked_by(attacker);
}

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

void
hook_friend_attacked(object friend, object attacker)
{
    ::hook_friend_attacked(friend, attacker);

    if (member_array("priest", friend->query_names()) >= 0)
        set_alarm(2.0 + itof(random(5)), 0.0, &command("rescue priest"));
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
        command("emote shouts a battlecry and leaps into the fray.");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

int
special_attack(object enemy)
{
    int i, priest_in_team;
    object *arr;    
    
    for (i = 0, arr = this_object()->query_team_others() ; i < sizeof(arr) ; i++)
        if (member_array("priest", arr[i]->query_names()) >= 0)
            priest_in_team = 1;

    switch (random(10))
    {
        case 0..2:
            command("hit");
            return 1;
            break;
        case 3..4:
            if (priest_in_team)
                command("rescue priest");
            else
                command("rescue _templeguard_");
            return 1;
            break;
    }
    
    return 0;
}
