// file name:        /d/Avenir/common/bazaa/infidel/weapon_poison.c
// creator(s):       Cirion, July 96
// revision history: 
// purpose:          A poison shadow to be able to poison weapons.
// note:             
// bug(s):           
// to-do:            

# pragma strict_types
# include "../infidel.h"
# include <poison_types.h>
inherit "/std/shadow";

int      pinterval = 20,
         ptime = 200,
        *pdamage = ({ POISON_FATIGUE, 100, POISON_HP, 30 }),
         pstrength = 20;

string   ptype = "assassin";

int
query_is_poisoned()
{
    return 1;
}

varargs string 
long(object for_obj)
{
    return shadow_who->long(for_obj) +
           (shadow_who->query_dt() == W_IMPALE ?
	   	"On the tip is a small coating of clear, sticky substance.\n" :
	        "Along the edge of the blade is a coating of clear, " +
                "sticky substance.\n");
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    object   poison,
             me = shadow_who->query_wielded();
    string  *msg;
    int      res = shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if ((enemy->query_magic_res(MAGIC_I_RES_POISON) > 5 + random(20)) ||
        (phit < 5))
        return res;

    if (dt == W_IMPALE)
        msg = ({ "stab", "stabs", "into" });
    else
        msg = ({ "slash", "slashes", "along" });

    me->catch_msg("As you " +
                  msg[0] + " " + LANG_THESHORT(shadow_who) + " " +
                  msg[2] + " " + QTNAME(enemy) + "'s " + hdesc +
                  ", the poison from the blade enters the wound.\n");
    enemy->catch_msg("As " + QTNAME(me) + " " +
                     msg[1] + " " + POSSESS(me) + " " + 
		     shadow_who->short(enemy) + " " + msg[2] + " your " +
		     hdesc + ", you feel a stinging sensation.\n");

    setuid();
    seteuid(getuid());

    poison = clone_object("/std/poison_effect");
    poison->set_time(ptime);
    poison->set_damage(pdamage);
    poison->set_strength(pstrength);
    poison->set_interval(pinterval);
    poison->set_type(ptype);

    poison->move(enemy, 1);
    poison->start_poison();
    set_alarm(0.0, 0.0, remove_shadow);
    return 1;
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
