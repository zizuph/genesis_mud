#include "/d/Ansalon/taman_busuk/mountains/local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#ifndef ONE_OF
#define ONE_OF(x)   (x)[random(sizeof(x))]
#endif

string * gAdj1 = ({"grim", "scurvy", "dirty", "pale", "weathered", "young", 
                   "bearded", "big-nosed", "wicked"});
string * gAdj2 = ({"black-haired", "sniveling", "impatient", "muscular",
                   "slouching", "wily", "haggard"});

string * gWep = ({"pike", "sword"});

void
arm_me(int level)
{
    string *arm = ({ONE_OF(gWep),"mailshirt", "chainhelm"});
    object tmp;
    int i;
    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(arm); i++)
    {
        if (arm[i][0..0] == "/")
        tmp = clone_object(arm[i]);
        else
        tmp = clone_object(MOBJ + arm[i]);
        tmp->move(TO);
    }
    command("wield all");
    command("wear all");
}

void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;
    
    set_name("rebel");
    set_race_name("human");

    set_pick_up_team(({"rebel"}));
    
    if (random(2))
    {
        string *t;
        t = gAdj1;
        gAdj1 = gAdj2;
        gAdj2 = t;
    }
    set_adj(ONE_OF(gAdj1));
    set_adj(ONE_OF(gAdj2));
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_short(implode(query_adjs()," ") + " male human");
    set_long("The " + short() + " is scruffy-looking, and of ill repute. " +
             "Personal hygiene being less of a priority, his fearsome " +
             "countenance is well matched by his fearsome odor.\n");

    set_stats(({95 + random(55), 80 + random(55), 70 + random(55), 
                95 + random(45), 95 + random(45), 115 + random(40)}));

    set_skill(SS_DEFENCE, 45 + random(25));
    set_skill(SS_PARRY, 35 + random(25));
    set_skill(SS_WEP_POLEARM, 55 + random(25));
    set_skill(SS_WEP_SWORD, 55 + random(25));
    set_skill(SS_AWARENESS, 55 + random(15));

    add_prop(CONT_I_HEIGHT, 165 + random(30));
    add_prop(CONT_I_WEIGHT, (60 + random(50)) * 1000);
    add_prop(OBJ_M_HAS_MONEY, 300 + random(500));

    set_alignment(600 + random(300));
    set_knight_prestige(-5);

    set_all_attack_unarmed(20,20);
    set_all_hitloc_unarmed(10);

}

void
init_living()
{
    init_team_pickup();
    ::init_living();
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
