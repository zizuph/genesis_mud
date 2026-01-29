/* Ashlar, 5 May 97 - human sergeant (leads patrols of soldiers) */
/* Navarre 24th June 2006, raised stats a little */
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#include NERAKA_REPORT

string color = "green";
int level;

set_color(string new_color)
{
    color = new_color;
}

void
set_colour(string c)
{
    set_color(c);
}

int
query_level() { return level; }

#define OBJ "/d/Krynn/solamn/splains/obj/"

varargs void
arm_me(int level)
{
    string *arm = ({ NWEP + "scimitar", NARM + "omail",
        "blargeshield", NARM + "ocape" });
    object tmp;
    int i;
    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(arm); i++)
    {
	    if (arm[i][0..0] == "/")
	        tmp = clone_object(arm[i]);
	    else
	        tmp = clone_object(OBJ + arm[i]);
	    if (tmp->query_prop(OBJ_I_COLORABLE))
	        tmp->set_color(color);
	    tmp->move(TO);
    }

    command("wield all");
    command("wear all");
}

void
create_krynn_monster()
{
    int k, i, j = random(2)+7; /* j is the level */

    level = j;
    set_pick_up_team(({"soldier"}));

    set_name("sergeant");
    add_name("human");
    set_race_name("human");
    set_adj("dragonarmy");
    set_short("dragonarmy sergeant");
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("This is a sergeant of the dragonarmy. He is clean-shaven " +
        "and keeps his equipment in good shape. @@query_player_al@@\n"); 

    for(i=0; i<6; i++)
        set_base_stat(i, j * 16 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_PARRY, j * 8 + random(20));
    set_skill(SS_WEP_SWORD, j * 7 + random(20));
    set_skill(SS_WEP_KNIFE, j * 7 + random(20));
    set_skill(SS_WEP_CLUB, j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_JAVELIN, j * 4 + random(20));
    set_skill(SS_WEP_AXE, j * 7 + random(20));

    k = query_average_stat();
    k = k*k/10;
    set_alignment(-k);
    set_knight_prestige(k);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);

    SET_NERAKA_AGGRESSIVE;
}


string
query_player_al()
{
    if(TP->query_guild_name_occ() == "Solamnian Knights")
        return "The sergeant eyes you angrily, seeming on the verge to attack you.";
    if(TP->query_alignment() > 200)
        return "The sergeant studies you carefully.";
    return "The sergeant glances quickly at you, then ignores you.";
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

    command("shout Death to the enemies of the Dark Queen!");
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
        command("say You will pay for this.");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
