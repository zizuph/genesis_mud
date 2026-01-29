/*
 *  A small rock
 *                          Tricky, 6-7-92
 *
 *  - Added F_DARE_ATTACK - check.
 *  - Check if the attacker can see the victim. 
 *                          Rogon, 18-12-94.
 */

inherit "/std/object";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"
#include "/sys/comb_mag.h"

void
create_object()
{
    set_name(({"_prot_spell_ingr1_","stone","rock"}));
    set_adj("small");
    set_pname(({"stones","rocks"}));
    set_short("small rock");
    set_pshort("small rocks");
    set_long("This is a small piece of rock, like often found in rocky areas. "
	     + "It looks utterly useless.\n");
    
    add_prop(OBJ_I_VALUE, 2);
    add_prop(OBJ_I_WEIGHT, 507);
    add_prop(OBJ_I_VOLUME, 492);
}

init()
{
    ::init();
    add_action("do_throw","throw");
}

do_throw(str)
{
    int dex;
    string tname, tobj,tmp;
    object tp, env;
    mixed target;
    
    tp = this_player();
    env = environment(tp);
    
    if (environment() != tp)
	return notify_fail("First get the small rock.\n");
    
   if (!str ||
       (!sscanf(str,"at %s",tmp) &&
        !sscanf(str,"rock at %s",tmp) &&
        !sscanf(str,"small rock at %s",tmp)))
       return notify_fail("Throw at something or someone.\n");
    
    str = lower_case(tmp);
    target = present(str, env);
    if (!target || !CAN_SEE(TP, target))
	return notify_fail("No '" + str + "' here.\n");
    
    if (target == tp)
	return notify_fail("Why would you want to throw at yourself?\n");

    if (NPATTACK(target))
	return notify_fail("You cannot attack that way here.\n");
    
    if (living(target))
    {
	if (!F_DARE_ATTACK(TP, target))
	   return 
	       notify_fail("Uh.. Eh. Nope, you shiver from the cold as you " +
			   "simply dare not attack " + QTNAME(target) + "!\n");
	tname = QCTNAME(target);
	tobj  = target->query_objective();
    }
    else
    {
	tname = "the " + target->short();
	tobj  = "it";
    }
    
    dex = tp->query_stat(SS_DEX);
    if (dex + random(dex) > 25)
    {
	tp->catch_msg("You throw the small rock at " + tname + " and hit "
		      + tobj + ".\n");
	target->catch_msg(QCTNAME(tp) + " throws a small rock at you "
			  + "and hits you.\n");
	say(QCTNAME(tp) + " throws a small rock at " + tname + " and hits "
	    + tobj + ".\n",({target,tp}));
	tp->attack_object(target);
	target->hit_me(F_PENMOD(7,7),W_IMPALE,tp,0);
    }
    else
    {
	tp->catch_msg("You throw the small rock at " + tname + " but miss " + 
		      tobj + ".\n");
	target->catch_msg(QCTNAME(tp) + " throws a small rock at you "
			  + "but misses you.\n");
	say(QCTNAME(tp) + " throws a small rock at " + tname + " but misses "
	    + tobj + ".\n",({tp,target}));
    }
    tell_room(env, "The small rock falls on the floor.\n");
    move(env); /* And drop on the floor */
    return 1;
}
