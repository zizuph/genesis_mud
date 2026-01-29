/* fire_glove_sh.c created by Shiva@Genesis
*
*   Fire gloves recoded by Meton 2020.
*   Weapon shadows created from original fire_glove_sh.c
*   This shadow goes along with the fire gloves (fire_gloves.c).
*   It detects wielding/unwielding of weapons
*   calling the appropriate functions in the gloves.
*
*   Calls damage if wielded weapon hits, and dmg>20&phurt>=0.
*   Calls damage if worn shield is hit, and dmg>20&phurt>=0.
*/

inherit "/std/shadow";
#include <wa_types.h>
#include "../local.h"

//Integers
static object bothhands,gloves;

/*
*   Function name: remove_bothhands_flames_shadow
*   Description  : removes this shadow
*   Arguments    : 
*   Returns      : 
*/
void
remove_bothhands_flames_shadow()
{
    gloves->removal_message(bothhands);
    remove_shadow();
}

/*
*   Function name: query_bothhands_flames_shadow
*   Description  : checks this shadow
*   Arguments    : 
*   Returns      : 
*/
int
query_bothhands_flames_shadow() { return 1; }

/*
*   Function name: set_bothhands_flames_ob
*   Description  : sets the ob.
*   Arguments    : 
*   Returns      : 
*/
void
set_bothhands_flames_ob(object ob)
{
    bothhands = ob; 
}

/*
*   Function name: query_bothhands_flames_ob
*   Description  : checks the ob.
*   Arguments    : 
*   Returns      : ob
*/

void
set_gloves_ob(object ob)
{
    gloves = ob; 
}

object
query_bothhands_flames_ob() { return bothhands; }


/*
*   Function name: did_hit
*   Description  : adds fire damage.
*   Arguments    : 
*   Returns      : did_hit original call
*/
int
did_hit(int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam)
{
    if (!bothhands)
    {
        set_alarm(0.5, 0.0, &remove_shadow());
        return shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

/*  If the attack has done more than 20 hps damage we have a 25%
*   to add a bit of fire damage and returns the call to the weapon.
*/
    if ((phurt >= 0) && (dam > 20) && (!(random(3))))
    {
        string with = bothhands->query_short();

        int hurt = gloves->fire_damage(enemy);
        gloves->burn_description(hurt);
        gloves->armed_hit(with, enemy);

        return shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    return shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

/*
*   Function name: short
*   Description  : adds description
*   Arguments    : 
*   Returns      : description
*/
// Thanks to Arman for sharing enchantmentspell to describe how it works.
public varargs string
short(object for_obj)
{
    return ("flame-covered " + shadow_who->short(for_obj));
}

/*
*   Function name: long
*   Description  : adds description
*   Arguments    : 
*   Returns      : description
*/
string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "It is surrounded by flames, from the gloves.\n");
}