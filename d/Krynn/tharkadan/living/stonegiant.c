/* Arman 2017 - Based on Neraka Hill Giant
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit C_FILE

string *gAdj1 = ({ "reclusive","grey-skinned","gaunt"}); 
public void remove_descr();
int standing = 1;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

void
create_creature()
{
    if(!IS_CLONE)
	return;

    set_name("giant");    
    set_race_name("giant");

    set_adj(ONE_OF(gAdj1));

    set_short(query_adj() + " stone giant");
    add_adj("stone");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("Before you is a huge humanoid, one of the rare stone " +
       "giants! It resembles little of its lesser hill giant cousins, " +
       "having granite-gray skin, gaunt features, and black, sunken " +
       "eyes that give it a a stern countenance. Despite their great " +
       "size and musculature, stone giants are lithe and graceful, " +
       "making them a lethal machine of destruction when riled! " +
       "Fortunately for most mountain dwellers, lore indicates stone " +
       "giants are generally reclusive and quiet, and peaceful when " +
       "left alone. Which, ironically, you are not currently doing.\n");

    add_prop(CONT_I_HEIGHT, 600);
    add_prop(CONT_I_WEIGHT, 550000);
    add_prop(CONT_I_VOLUME, 450000);

    set_stats(({300,250+random(20),350+random(20),190+random(20),
                190+random(20),250+random(30)}));
    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(LIVE_I_SEE_DARK, 5);

    // major resistance to earth magic and poison
    add_prop(OBJ_I_RES_EARTH, 65);
    add_prop(OBJ_I_RES_POISON, 100);

    // minor vulnerability to air magic
    add_prop(OBJ_I_RES_AIR, -20);

    set_hitloc_unarmed(1, 65, 17, "left thigh");
    set_hitloc_unarmed(2, 65, 17, "right thigh");
    set_hitloc_unarmed(3, 75, 20, "left shin");
    set_hitloc_unarmed(4, 75, 20, "right shin");
    set_hitloc_unarmed(5, 45,  6, "abdomen");
    set_hitloc_unarmed(6, 60, 15, "left foot");
    set_hitloc_unarmed(7, 60, 15, "right foot");

    set_attack_unarmed(1, 45, 60, W_BLUDGEON, 20, "left foot");
    set_attack_unarmed(2, 45, 60, W_BLUDGEON, 30, "right foot");
    set_attack_unarmed(3, 75, 45, W_BLUDGEON, 20, "left fist");
    set_attack_unarmed(4, 75, 45, W_BLUDGEON, 30, "right fist");

    set_alignment(0);
    set_knight_prestige(0);

    int braid_chance = random(10);
    int bone_chance = random(10);

    add_leftover("/std/leftover","skull", 1,"", 0, 1, 70);

    if(braid_chance == 1)
       add_leftover(ARMOUR + "stonegiant_braid","braid", 1,"", 0, 1);
    if(bone_chance == 1)
       add_leftover(WEP + "giant_thighbone","thighbone", 1,"", 0, 1, 90);

    ::create_creature();
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen;

    mixed hitres;

    string *how;

    attacktype = random(5);

    if (attacktype == 0)
    {
        hitres = enemy->hit_me(550/2, W_BLUDGEON, TO, -1);

        how = ({ QCTNAME(TO) + " tries to step on you, but you jump " +
            "aside.", QCTNAME(TO) + " tries to step on " + QTNAME(enemy) +
            ", but " + HE(enemy) + " jumps aside."});
	            
	if(hitres[0] > 0)
	    how = ({ QCTNAME(TO) + " treads on you lightly.",
	    QCTNAME(TO) + " treads on " + QTNAME(enemy) + " lightly." });
                
	if(hitres[0] > 7)
	    how = ({ QCTNAME(TO) + " steps down on you hard.",
	    QCTNAME(TO) + " steps down on " + QTNAME(enemy) + " hard." });

	if(hitres[0] > 18)
            how = ({ QCTNAME(TO) + " crushes you against the ground " +
            "with his foot.", QCTNAME(TO) + " crushes " + QTNAME(enemy) + 
            " against the ground with his foot." });
	    
	if (hitres[0] > 37)
	    how = ({ QCTNAME(TO) + " crushes you with his foot, grinding " +
	    "body into the ground.", QCTNAME(TO) + " crushes " + 
            QTNAME(enemy) + " with his foot, grinding the latter into " +
            "the ground." });

        if (hitres[0] > 99)
            how = ({ "Putting all his weight behind it, " + QTNAME(TO) +
                "puts his immense foot over you, crushing you against " +
                "the ground. The last thing you feel is your bones " +
                "snapping under the pressure...",
                "Putting all his weight behind it, " + QTNAME(TO) +
                "puts his foot over " + QTNAME(enemy) + ", and with " +
                "a bonecrushing sound drives " + HIM(enemy) + " into " +
                "the ground." });

        enemy->catch_msg(how[0] + "\n");
        tell_room(E(TO), how[1] + "\n", enemy);

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }

    return 0;
}

arm_me()
{
    seteuid(getuid(this_object()));    
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
       command("emote rises to his feet, towering over you.");
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
       command("emote rises to his feet, towering over you.");
       standing = 1;
     }
    ::attack_object(ob);
}

public void
sit_down()
{
    if(!standing)
        return;

    command("emote lowers himself down to the ground and rests " +
        "contently beside an aspen tree.");
    add_prop(LIVE_S_EXTRA_SHORT, " resting beside an aspen tree");
    standing = 0;
    return;
}


public void
stand_up()
{
    if(standing)
        return;

    remove_descr();
    command("emote rises to his feet, towering over you.");
    command("emote rumbles: You trespass little one. I do not like " +
       "being disturbed.");
    standing = 1;
    return;
}

void 
init_living() 
{

    if(CAN_SEE(TO, TP))
      set_alarm(6.0, 0.0, &stand_up());
 
    ::init_living(); 
}