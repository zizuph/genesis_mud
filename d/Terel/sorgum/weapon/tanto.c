/* -*- C++ -*- */

/*
 * Sorgum's tanto
 */

inherit "/std/weapon";
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

int given_away;
string dropped_by_wiz, cloned_by_wiz;

#define TP this_player()
#define TO this_object()
#define ETO environment(this_object())
#define ETP environment(this_player())
#define ENV(xx) environment(xx)
#define CAP(xx) capitalize(xx)

#define LOG "/d/Terel/sorgum/log/tanto"

/*
 * Function name:   wield
 * Description:     Wield a weapon.
 * Arguments:	    wep - The weapon to wield.
 * Returns:         True if wielded.
 *                  String with failure message if not wielded.
 */
public mixed
wield(object wep)
{
    object wielder;

    wielder = ENV(wep);
    if (!wielder) return 0;

    if (wielder->query_alignment() > (-300))
    {
	wielder->catch_msg("You aren't evil enough to wield it.\n");
	return 0;
    }
    
    if (wielder)
	wielder->catch_msg("You feel a dark chill as you wield the tanto.\n");
    
    return 1;
}

void
create_weapon()
{
    set_name("tanto");
    add_name("_benton_knife_");
    set_short("tanto");
    set_long(
	"This is a cold steel blade of supurb craftsmanship.  The metal " +
        "appears to have stripes where the steel has been folded during the " +
        "forging process.  The hilt is crafted from fossilzed bone and " +
        "wrapped in shark skin.");
    set_adj("steel");
   
    set_default_weapon(40, 44, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 10000); 
    add_prop(OBJ_I_VOLUME,  1000); 
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 44) + random(150));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_M_NO_GIVE,"@@test_give");
    add_prop(OBJ_M_NO_DROP, "@@drop_check");
}


int
test_give()
{
    seteuid(getuid(this_object()));
    given_away = 1;
    if (TP->query_wiz_level()) {
	write_file(LOG, TP->query_name() + " gave the tanto to " +
		   ETO->query_name() + ". " + ctime(time()) + ".\n");
    }
    return 0;
}

mixed
drop_check()
{
    if ((ETO->id("benton")) && (ETO->query_hp() > 0))
	return "Benton cannot drop his tanto.\n";
    
    if (TP->query_wiz_level() && query_verb() != "give") {
	write_file(LOG, TP->query_name() + " dropped the tanto in " +
		   file_name(ETP) + " " + ctime(time()) + ".\n");
	dropped_by_wiz = TP->query_name();
    }
    else if (TP->query_wiz_level()) {
	dropped_by_wiz = TP->query_name();
    }
    return 0;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if ((!from) || (!to)) return;
    
    seteuid(getuid(this_object()));
    if (!from && TP->query_wiz_level()) {
	cloned_by_wiz = CAP(TP->query_real_name());
	if (!living(to))
	    write_file(LOG, TP->query_name() + " cloned the tanto into " +
		       file_name(ETO) + ". " + ctime(time())+".\n");
	else write_file(LOG, TP->query_name() + " cloned the tanto. "
			+ ctime(time()) + ".\n");
    }
    else if (given_away && from->query_wiz_level()) {
	write_file(LOG, from->query_name() + " gave the tanto to " +
		   to->query_name() + ". " + ctime(time()) + ".\n");
	given_away = 0;
    }
    if (!living(from) && strlen(dropped_by_wiz)) {
	write_file(LOG, TP->query_name() + " picked up the tanto dropped " +
		   "by " + dropped_by_wiz + " in " + file_name(ETP) + ". " +
		   ctime(time()) + ".\n");
    }
    else if (!living(from) && strlen(cloned_by_wiz)) {
	write_file(LOG, TP->query_name() + " picked up the tanto cloned by " +
		   cloned_by_wiz + " in " + file_name(ETP) + ". " +
		   ctime(time()) + ".\n");
    }
}

void
leave_env(object from, object to)
{
    string fn;
    if (from->query_prop(ROOM_I_IS))
	fn = file_name(from);
    else
	fn = file_name(ENV(from));
    if (!to)
	write_file(LOG, from->query_name()
		   + " destructed the tanto, in " + fn + ". "
		   + ctime(time()) + ".\n");
    ::leave_env(from, to);
}
   

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
	int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

     if (enemy->query_alignment() < 0)
	  return 0;
     
    if (phurt == -1) {
        query_wielded()->catch_msg("The tanto just misses " +
				   QTNAME(enemy) + ".\n");
        enemy->catch_msg("The tanto comes dangerously close to you.\n");
    }
    else if (phurt == 0) {
        query_wielded()->catch_msg("The tanto cuts into the flesh of " +
                QTNAME(enemy) + ".\n");
        enemy->catch_msg("The tanto cuts into your flesh\n");
    }
    else {
	   if (random(4) == 3) {
	      query_wielded()->catch_msg("Energy courses through the evil " +
	           "blade as it shreds " +QTNAME(enemy) + ".\n");
	     enemy->catch_msg("You feel excruciating pain as the evil blade " +
                   "shreds your flesh away from the bone.\n");

	      enemy->reduce_hit_point(enemy->query_alignment()/4);
	      enemy->do_die(environment(TO));

	 }
	   return 0;
      }
}
