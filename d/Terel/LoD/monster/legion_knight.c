
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * legion_knight.c
 *
 * A generic legion knight.  Like a soldier, but we add spell special
 * attacks.
 * Modified to use hit_me instead of reduce_hit_point, Trofast 10/1998
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "monster/legion_soldier";

#include <ss_types.h>
#include <formulas.h>

#define DARKNESS_MANA   20
#define PAIN_MANA       25
#define FIREBALL_MANA   45

#define PAIN_DAMAGE     (random(50) + 50)
#define PAIN_FATIGUE    (random(5) + 15)

#define FIREBALL_DAMAGE (random(150)+150)

#define PAIN_AVOID      100
#define FIREBALL_AVOID  150

#define SPELL_DELAY     20
#define DARK_OBJ        LOD_DIR + "obj/dark_obj"

public int query_spell_level();

/*
 * Function name: darkness
 * Description:   darkness spell.  Decrease ambient light level by 1.
 */
public void
darkness()
{
    object dark;

    TO->add_mana(-1 * DARKNESS_MANA);
    
    seteuid(getuid());
    dark = clone_object(DARK_OBJ);
    dark->set_light_value(-query_spell_level());
    dark->set_duration(5 + 3*query_spell_level());
    dark->set_enter_msg("");
    dark->set_leave_msg("");
    tell_room(ETO, QCTNAME(TO) + " creates a cloud of darkness.\n");
    dark->move(ETO);
}

/*
 * Function name: pain 
 * Description:   pain spell.  
 */
public void
pain()
{
    int i;
    object *enemies;
    int e_sk=0;

    if (TO->query_mana() <= PAIN_MANA) return;
    TO->add_mana(-1 * PAIN_MANA);
    command("say Wanna feel pain?");
    tell_room(ETO, QCTNAME(TO) + " mumbles something.\n", TO);

    enemies = query_my_enemies();
    for (i = 0; i < sizeof(enemies); i++) {
        e_sk = enemies[i]->query_stat(SS_WIS) - TO->query_stat(SS_WIS);
        e_sk += enemies[i]->query_stat(SS_DIS);
        e_sk += enemies[i]->query_magic_res(MAGIC_I_RES_DEATH);
        if (random(e_sk) < PAIN_AVOID) {
            tell_object(enemies[i],"You feel an intense pain.\n");
	    /*      enemies[i]->reduce_hit_point(PAIN_DAMAGE);*/
	    enemies[i]->hit_me(PAIN_DAMAGE, MAGIC_DT, TO, -1);
            if (enemies[i]->query_hp() <= 0)
                enemies[i]->do_die(TO);
            enemies[i]->add_fatigue(-1 * PAIN_FATIGUE);
        } else {
            tell_object(enemies[i],"You feel all tickly inside.\n");
        }
    }
    command("laugh evilly");
}

/*
 * Function name: fireball
 * Description:   fireball spell.  
 */
public void
fireball()
{
    int i;
    int e_sk;
    object *enemies;
    int dama;

    if (TO->query_mana() <= FIREBALL_MANA) return;
    TO->add_mana(-1 * FIREBALL_MANA);
    enemies = query_my_enemies();
    command("say Wanna see the fire of hell?");
    tell_room(ETO, QCTNAME(TO) + " produces a fire from hell in the air.\n");
    tell_room(ETO, "The hell-fire explodes with a loud bang!\n");
    for (i=0; i<sizeof(enemies); i++) {
        e_sk = enemies[i]->query_stat(SS_DEX) - TO->query_stat(SS_WIS);
        e_sk += enemies[i]->query_stat(SS_CON);
        e_sk += enemies[i]->query_magic_res(MAGIC_I_RES_FIRE);
        e_sk += enemies[i]->query_magic_res(MAGIC_I_RES_DEATH);
        if (random(e_sk) < FIREBALL_AVOID) {
            tell_object(enemies[i], "You get burned.\n");
	    /*            enemies[i]->reduce_hit_point(FIREBALL_DAMAGE);*/
	    enemies[i]->hit_me(FIREBALL_DAMAGE, MAGIC_DT, TO, -1);
	    if (enemies[i]->query_hp() <= 0)
                enemies[i]->do_die(TO);
        } else {
            tell_object(enemies[i], "You manage to avoid being " +
                        "damaged by the fire from hell.\n");
        }
    }
    command("say Getting closer to the devil, eh?");
}

/*
 * Function name: query_spell_level
 * Description:   spell level is used in spell_attack()
 * Returns:       this knights spell level.
 */
public int
query_spell_level()
{
    return 1;
}

/*
 * Function name: spell_attack
 * Description:   This is called by the combat system.
 * Arguments:     me -    This object
 *                enemy - The enemy we are fighting.
 */
public int
spell_attack(object me, object victim)
{
    int spell, delay;
    
    spell = random(query_spell_level()+1);
    switch (spell) {
     case 1:
        pain();
        break;
     case 2:
        darkness();
        break;
     case 3:
        pain();
        break;
     case 4:
        fireball();
        break;
     default:
        return ::spell_attack(me, victim);
    }

    delay = 10 - 2*query_spell_level() + random(SPELL_DELAY);
    set_alarm(itof(delay), -1.0, "set_spell_prop", TO);
    return 1;
}

public void
do_die(object killer)
{
    if (query_hp() > 0) return;

    command("sigh");
    
    ::do_die(killer);
}

int
query_knight_prestige()
{
    return 50;
}
