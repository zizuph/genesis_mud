/* Ashlar, 2 Aug 97 - Dragonarmy Captain */
/* Navarre 24th June 2006, raised stats a little */
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#include NERAKA_REPORT

string color = "green";
int attack_reload;
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
    string *arm = ({ NWEP + "scimitar", NARM + "oplate",
        "blargeshield", "bshinguard", NARM + "ocape" });
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

    /*
    switch(random(4))
    {
        case 0..1:
            tmp = clone_object(NOBJ + "trueblade");
            tmp->enchant(P("weapon",TO), random(20) + 50);
            break;
        case 2:
            tmp = clone_object(NOBJ + "darktouch");
            tmp->enchant(P("weapon",TO), random(30) + 40);
            break;
    }
    */
    
    command("wield all");
    command("wear all");
}

void
create_krynn_monster()
{
    int k, i, j = random(2)+9; /* j is the level */

    level = j;
    set_pick_up_team(({ "lieutenant", "sergeant", "soldier", "minotaur" }));

    set_name("captain");
    add_name("human");
    set_race_name("human");
    set_adj("dragonarmy");
    set_short("dragonarmy captain");
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("This is a captain of the dragonarmy. He is clean-shaven " +
        "and keeps his equipment in good shape. @@query_player_al@@\n"); 

    for(i=0; i<6; i++)
        set_base_stat(i, j * 15 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_PARRY, j * 8 + random(20));
    set_skill(SS_BLIND_COMBAT, j * 6 + random(20));
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
        return "The captain eyes you angrily, seeming on the verge to attack you.";
    if(TP->query_alignment() > 200)
        return "The captain studies you carefully.";
    return "The captain glances quickly at you, then ignores you.";
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

int
special_attack(object enemy)
{
    int     attacktype, pen;
    object  *wa;

    mixed hitres;
    string *how;

    if (attack_reload)
    {
        attack_reload--;
        return 0;
    }

    attacktype = random(2);
    /* Twirl and slash */
    if (attacktype == 0)
    {
        object wep;
        string hitloc;
        
        wa = query_weapon(-1);
        if (!wa || sizeof(wa) == 0)
            return 0;

        wep = wa[0];
        pen = wep->query_pen() * 3 + wep->query_hit() * 2;
        pen = (pen / 2) + random(pen);
        if (enemy->query_skill(SS_DEFENCE) > 60)
            pen = (pen * 2) / 3;
        if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO,enemy))
            pen = (pen * TO->query_skill(SS_BLIND_COMBAT)) / 100;

        if (!(wep->query_dt() & W_SLASH))
            return 0;
	    hitres = enemy->hit_me(pen, W_SLASH, TO, -1);
	    hitloc = hitres[1];

	    if (hitres[0] <= 0)
	        how = ({ "Twirling around, " + QTNAME(TO) + " slashes at you, " +
	            "but you jump aside, leaving " + HIM(TO) + " off balance.\n",
	            QCTNAME(TO) + " twirls around and slashes at " + QTNAME(enemy) +
	            ", but " + HE(enemy) + " jumps aside, leaving " + QTNAME(TO) +
	            " off balance.\n" });	            
	    else if(hitres[0] < 5)
	        how = ({ QCTNAME(TO) + " twirls around and slashes at your " +
	            hitloc + ", barely drawing blood.\n",
                QCTNAME(TO) + " twirls around and slashes at " + QTNAME(enemy) +
                "'s " + hitloc + ", barely drawing blood.\n" });                
	    else if(hitres[0] < 16)
	        how = ({ "Twirling around, " + QTNAME(TO) + " slashes " + HIS(TO) +
	            " " + wep->short() + " at you, leaving a " +
	            "bleeding gash on your " + hitloc + ".\n",
	            "Twirling around, " + QTNAME(TO) + " slashes " + HIS(TO) + " " +
	            wep->short() + " at " + QTNAME(enemy) + ", leaving a bleeding " +
	            "gash on " + HIS(enemy) + " " + hitloc + ".\n" });
	    else if(hitres[0] < 35)
            how = ({ QCTNAME(TO) + " twirls around with great speed, " +
                "cutting a deep wound in your " + hitloc + " with " + HIS(TO) +
                " " + wep->short() + ".\n",
                QCTNAME(TO) + " twirls around with great speed, cutting a " +
                "deep wound in " + QTNAME(enemy) + "'s " + hitloc + " with " +
                " the " + wep->short() + ".\n" });
        else if(hitres[0] < 100)
            how = ({ "Twirling around, " + QTNAME(TO) + " slashes deeply at " +
                "your " + hitloc + ", " + HIS(TO) + " " + wep->short() +
                "tearing through your flesh, causing you tremendous pain.\n",
                QCTNAME(enemy) + " cries out in pain as " + QTNAME(TO) +
                " slashes deeply with " + HIS(TO) + " " + wep->short() +
                ", tearing through the flesh of " + QTNAME(enemy) + "'s " +
                hitloc + ".\n" });
        else
            how = ({ "Time slows down to a trickle as you see " + QTNAME(TO) +
                " twirling around, bringing the blade of " + HIS(TO) + " " +
                wep->short() + " in a deadly arc towards you. You try to " +
                "parry in vain, but your muscles refuse to obey as you feel " +
                "the cold steel biting through your neck, and the darkness " +
                "embraces you.\n",
                "With a shout of praise to " + HIS(TO) + " Dark Queen, " +
                QTNAME(TO) + " swings the blade of " + HIS(TO) + " " +
                wep->short() + ", slashing through " + QTNAME(enemy) + "'s " +
                "neck, nearly beheading " + HIM(enemy) + ". The lifeless " +
                "body of " + QTNAME(enemy) + " slumps to the ground.\n" });

        enemy->catch_msg(how[0]);
        tell_room(E(TO), how[1], enemy);

	    if (enemy->query_hp() <= 0)
	    {
	        enemy->do_die(TO);
	    }

        attack_reload = 4;
	    return 1;
    }

    return 0;
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
        command("emote growls: That was a stupid move.");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
