#include <filter_funs.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <language.h>
#include "/d/Shire/sys/defs.h"
#include <options.h>

//Prototypes
void notify_end_paralyze(mixed foo);

void
add_magic_properties()
{
    TO->add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); /* it is magic */
    TO->add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment" }));
    TO->add_prop(MAGIC_AM_ID_INFO,({"This club seems to be enchanted.\n",1,
	"It has better effect when you hit head of your enemy.\n",10,
	"It drains his mental energy when you do so.\n",25,
	"Eventually it knocks enemy completely down.\n",50 }));
}

/*
 * Function name: cb_did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from heart_beat)
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *		  dt:	 The current damagetype
 *		  phit:  The %success that we made with our weapon
 *			 If this is negative, it indicates fail
 *		  dam:   Damage we did in hit points
 */
public varargs void
cb_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
  int phit, int dam)
{
    string          how,
    what, owhat,
    where,
    with;
    object     cmbo, me = TO->query_wielded();



    if ((!enemy) || (!me))
	return;

    cmbo = me->query_combat_object();

    /*
     * Adjust our panic level
     */
    if (phurt >= 0)
	cmbo->cb_add_panic(-3 - phurt / 5);
    else
	cmbo->cb_add_panic(1);

    where = "the " + hdesc + " of " + QTNAME(enemy);

    with = cmbo->cb_attack_desc(aid);

    if (phurt == -1 || phurt == -2)
    {
	if (!me->query_option(OPT_GAG_MISSES))
	    me->catch_msg("You aim for " + where +
	      " with your " + with + " but miss.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg(QCTNAME(me) + " aims for your " + hdesc + 
	      " with " + me->query_possessive() + " " + with +
	      ", but misses.\n");
	me->tell_watcher_miss(QCTNAME(me)+" aims for "+where+" with "+
	  me->query_possessive()+" "+with+", but misses.\n",
	  enemy);
	return;
    }

    /*
     * The actual combat messages.
     */
    how = ", without effect.";
    what = "hit";
    owhat = "hits";

    if (phurt < 5)
    {
	how = ".";
	what = "tickle";
	owhat = what + "s";
    }
    else if (phurt < 10)
    {
	how = ".";
	what = "graze";
	owhat = what + "s";
    }
    else if (phurt < 20)
    {
	how = ".";
	what = "hurt";
	owhat = what + "s";
    }
    else if (phurt < 30)
    {
	how = ", rather bad.";
	what = "hurt";
	owhat = what + "s";
    }
    else if (phurt < 50)
    {
	how = ", very bad.";
	what = "hurt";
	owhat = what + "s";
    }
    else if (phurt < 70)
    {
	how = ", very hard.";
	what = "smash";
	owhat = "smashes";
    }
    else if (phurt < 90)
    {
	how = ", with a bone crushing sound.";
	what = "smash";
	owhat = "smashes";
	where = QTNAME(enemy);
    }
    else
    {
	how = ".";
	what = "massacre";
	owhat = "massacres";
	where = QTNAME(enemy);
    }

    me->catch_msg("You " + what + " " + where + " with your " + with +
      how + "\n");
    enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc + " with " +
      me->query_possessive() + " " + with + how + "\n");
    me->tell_watcher(QCTNAME(me) + " " + owhat + " the " + hdesc + " of " +
      QTNAME(enemy) + " with " + me->query_possessive() + " " + with + how +
      "\n", enemy);
}

void
notify_end_paralyze(mixed foo)
{
    object who = foo[0];
    int delay = foo[1];

    if(objectp(who))
    {
	tell_room(environment(who), 
	  QCTNAME(who)+" regains senses again.\n", who);
	who->add_prop(LIVE_I_ATTACK_DELAY, delay);
    }
    return;
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
  int dam)
{
    int mana, pmana_hurt, attack_delay, i;
    int dam_mana = 0;
    string how_dizzy, how, kkk;
    object paralyze, 
    me = TO->query_wielded();

    /* this should produce standard combat message */
    cb_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if((hdesc != "head") || (present("_senceless_by_club_", enemy))) return 1;

    mana = enemy->query_mana();
    if(dam > 0) dam_mana = random(dam)+1;
    enemy->add_mana(-dam_mana);

    if((dam_mana > 0) && (enemy->query_mana() < 1))  /* enemy is knocked out */
    {
	dam_mana = MIN(dam_mana,20+random(10));
	seteuid(getuid());
	paralyze = clone_object("/std/paralyze");
	paralyze->set_name("_senceless_by_club_");
	paralyze->set_no_show(1);
	paralyze->set_remove_time(dam_mana);
	paralyze->set_stop_message("You regain senses and notice a terrible "+
	  "headache!\n");
	paralyze->set_fail_message("You can't do that, you are still "+
	  "senseless!\n");
	paralyze->set_stop_verb("depart"); /* No command to stop the paralyze! */
	paralyze->set_stop_object(0);   /* Use the messages set above */
	paralyze->move(enemy, 1);       /* Now DO the paralyze */

	attack_delay = MAX((enemy->query_prop(LIVE_I_ATTACK_DELAY)), (dam_mana / 2));

	set_alarm(itof(dam_mana), 0.0,
	  &notify_end_paralyze(({enemy,attack_delay-(dam_mana/2)})));

	/* Stop enemy fighting back while senseless  */
	enemy->add_prop(LIVE_I_ATTACK_DELAY, attack_delay);

	/* Restore 1/10 of max mana back */
	enemy->set_mana((enemy->query_max_mana()) / 10 );

	enemy->catch_msg("You fall unconscious to the floor.\n");
	tell_room(environment(enemy), 
	  QCTNAME(enemy)+" falls unconscious to the floor.\n", enemy);
	return 1;
    }
    if(dam_mana > 0)
    {
	pmana_hurt = 100 * dam_mana / mana;
	how_dizzy = "slightly dizzy";
	if(pmana_hurt > 5) how_dizzy = "dizzy";
	if(pmana_hurt > 10) how_dizzy = "very dizzy";
	if(pmana_hurt > 20) how_dizzy = "losing senses";
	if(pmana_hurt > 40) how_dizzy = "hardly keeping senses";
	me->catch_msg(QCTNAME(enemy)+" seems to be "+how_dizzy+".\n");
	enemy->catch_msg("You are "+how_dizzy+".\n");
	me->tell_watcher(QCTNAME(enemy)+" seems to be "+how_dizzy+".\n",
	  enemy);
    }
    return 1;
}
