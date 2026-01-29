/* Navarre June 25th 2006, added adj to make it work with
 * "exa life-stealer blade"
 * Navarre July 1st 2006, Fixed damage message to use QCTNAME
 * instead of QTNAME in a place where it should be capitalized.
 *
 * Navarre Feb 22th 2007, Added check for wielder in unwield method.
 * to avoid a runtime error when wielder died.
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";

create_weapon()
{
    set_name("sword");
    add_name("blade");
    add_adj("shadow");
    add_adj("life-stealer");
    set_short("life-stealer blade");
    set_long("Black wings adorn the hilt of this amazing two-handed sword. "+
	"Between them a dragon's head glares frighteningly at you. Two "+
	"blood red gems placed in the eye sockets seem to glow deep "+
	"crimson with an unholy light, in sharp contrast to the otherwise "+
	"black metal hilt. Black vines adorn the blade, running up it's "+
	"center. A dark shadow seems to follow the blade through the air, "+
	"leaving evil in the path of the mighty blade. You feel rather "+
	"nervous looking at this sword.\n");

    set_default_weapon(50, 50, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);

    add_item(({"gem","gems"}),"Two blood-red rubies adorn the eye sockets of "+
	"ornamental dragon head on the hilt of the sword. They glow with an unholy "+
	"light, and you can see something swirling around inside of them.\n");
    add_item(({"vine","vines"}),"The vines entertwine, and run the about three "+
	"quarters of the length of the blade.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This blade is " +
	"a feared life-stealer, endowed with dark energy that drains the life " +
	"forces from those who touch it.\n",1,
	"Only those who walk the dark path of evilness are protected " +
	"from this deadly drain, and that is only when they wield it.\n",35}));
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 13500);
    set_wf(TO);
    set_pm(({-3,0,3}));
}

void
wield_message1()
{
    write("As you wrap your hands around the blackened hilt of this sword, "+
      "you feel a dark presence enter, consuming you with bloodlust!\n");

    say("As " + QTNAME(TP) + " clutches the hilt of the massive sword, " +
	HIS(TP) + " eyes light up with an unholy light, and " + HE(TP) +
	" looks strangely around, as if searching for something...\n");
}


void
wield_message2()
{
    write("A cold commanding presence rises up inside you, and you feel a "+
	"strong tugging in your mind to take a life.\n");

    say(QCTNAME(TP) + " suddenly stiffens, and looks around with a peculiar "+
	"gleam in " + HIS(TP) + " eyes.\n");
}


mixed
wield(object what)
{

    if(TP->query_alignment() > 100)
    {
	write("You foolishly attempt to wield Shadow Blade! \n"+
	  "As you wrap your hands around the hilt, you stare in horror at the blade "+
	  "that draws heavily on your soul for your insolence!\n");
	TP->heal_hp(-800-random(200));
	say(QCTNAME(TP) + " turns horribly pale as "+HE(TP)+" wraps "+
	  HIS(TP)+" hands around the hilt of Shadow Blade!\n");

	if(TP->query_hp() <= 0)
	{
	    write("The draw upon your soul is too much for you to resist, and you "+
	      "feel a strange peace come over you as you feel no more.\n");
	    say(QCTNAME(TP)+" stiffens and looks with horror at Shadow Blade, then "+
	      "slumps slowly to the ground, drained of life.\n");
	    TP->do_die(TO);
	}
	return "You release the grip immediatly.\n";
    }


    //    wielder = TP;
    set_alarm(1.0, 0.0, wield_message1);
    set_alarm(5.0, 0.0, wield_message2);
    return 0;
}

mixed
unwield(object what)
{
    if(wielder)
    {
        wielder->catch_msg("As you release your grip on the sword, the evil " +
	                   "presence leaves your mind, and you feel in control "+
                           "once again. You feel quite relieved...\n");
        say(QCTNAME(wielder) + "'s eyes lose their disturbing gleam as " +
	    HIS(wielder) + " hands release their grip on the two-handed sword.\n");
    }
    return 0;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam, int hid)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);

    switch(phurt)
    {
    case -1:
    case -2:
	wielder->catch_msg("You swing the " + short() + " at " +
	  QTNAME(enemy) + " wildly, a dark shadow trailing the blade.\n");
	enemy->catch_msg(QCTNAME(wielder)+" swings "+HIS(wielder) +
	  " "+short()+" at you, but you manage to avoid the blade.\n");
	wielder->tell_watcher(QCTNAME(wielder)+" swings "+HIS(wielder) +
	  " "+short()+" at "+QTNAME(enemy)+" but misses leaving dark shadows "+
	  "in the air.\n", enemy);
	break;

    case 0:
	wielder->catch_msg("You swing the " + short() + " very close to " +
	  QTNAME(enemy) + ", the shadow following the blade.\n");
	enemy->catch_msg(QCTNAME(wielder) + " barely misses you with " +
	  HIS(wielder)+" "+short()+" leaving you quite unnerved at "+
	  "the sight of the evil blade.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " swings the " + short() +
	  " at " + QTNAME(enemy) + " and narrowly misses, the darkness "+
	  "following the blade coming dangerously close to "+
	  QTNAME(enemy)+".\n", enemy);
	break;

    case 1..4:
	wielder->catch_msg("You graze the " + hdesc + " of " +
	  QTNAME(enemy) + " with your " + short() + ". The shadow " +
	  "touches the wound, and "+QTNAME(enemy)+" turns a bit pale.\n");
	enemy->catch_msg(QCTNAME(wielder)+ " grazes your " + hdesc +
	  " with the " + short() + ". You are terrified, as the shadow "+
	  "brushes the wound, pulling at your soul!\n");
	wielder->tell_watcher(QCTNAME(enemy) + " turns slightly pale as "+
	  QTNAME(wielder)+" grazes "+HIS(enemy)+" "+hdesc+" with the "+
	  short()+".\n", enemy);
	break;

    case 5..9:
	wielder->catch_msg("You draw blood from "+QTNAME(enemy)+"'s "+
	  hdesc+" with your blade, the shadow brushes over the wound "+
	  "bringing obvious pain to "+HIS(enemy)+" face.\n");
	enemy->catch_msg("The darkness around the blade tugs at your "+
	  "soul as "+QTNAME(wielder)+" grazes your "+hdesc+".\n");
	wielder->tell_watcher(QCTNAME(enemy) + " winces as the blade grazes " +
	  HIS(enemy)+" "+hdesc+".\n", enemy);
	break;

    case 10..19:
	wielder->catch_msg("You tear a wound into the " + hdesc + " of " +
	  QTNAME(enemy) + " and take great pleasure as the shadow "+
	  "causes obvious pain to "+QTNAME(enemy)+".\n");
	enemy->catch_msg(QCTNAME(wielder) + " tears into your " + hdesc +
	  " with the " + short() + ". The tugging at your soul grows "+
	  "stronger, you feel yourself weakening.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " grins in satisfaction as "+
	  HIS(wielder)+" blade tears into the "+hdesc+" of "+
	  QTNAME(enemy)+", leaving "+HIM(enemy)+" visibly "+
	  "shaken.\n", enemy);
	break;

    case 20..29:
	wielder->catch_msg("You bash the hilt of your sword into "+
	  QTNAME(enemy)+"'s face and laugh coldly as "+
	  HE(enemy)+" staggers backwards.\n");
	enemy->catch_msg("You stagger as "+QTNAME(wielder)+" slams "+
	  "the hilt of "+HIS(wielder)+" sword into your face and "+
	  "are overcome with pain.\n");
	wielder->tell_watcher(QCTNAME(enemy) + " staggers as "+QTNAME(wielder)+
	  " slams the hilt of "+HIS(wielder)+" sword into "+
	  HIS(enemy)+" face.\n", enemy);
	break;

    case 30..49:
	wielder->catch_msg("You slash deeply into the "+hdesc+" of "+
	  QTNAME(enemy)+" the dark shadow licking at the wound!\n");
	enemy->catch_msg(QCTNAME(wielder) + " slashes deeply into your "+
	  hdesc+" with "+HIS(wielder)+" sword, and you feel an "+
	  "immense pain as the shadow envelopes the wound!\n");
	wielder->tell_watcher(QTNAME(enemy) + " recoils in pain as a deep wound "+
	  "is torn into "+HIS(wielder)+" "+hdesc+" with the "+short()+
	  ".\n", enemy);
	break;

    case 50..69:
	wielder->catch_msg("You brutally smash the hilt of your sword "+
	  " into "+QTNAME(enemy)+"'s face, sending "+HIM(enemy)+
	  " sprawling to the ground!\n");
	enemy->catch_msg("You feel yourself lifted of the ground from "+
	  "the sheer force of the blow as "+QTNAME(wielder)+" crushes "+
	  "the hilt of "+HIS(wielder)+" sword into your face!\n");
	wielder->tell_watcher(QCTNAME(enemy) + " is sent sprawling to the ground "+
	  "as "+QTNAME(wielder)+" brutally crushes the hilt of "+
	  HIS(wielder)+" sword into "+QTNAME(enemy)+
	  "'s face!\n", enemy);
	break;

    case 70..99:
	wielder->catch_msg("You deliver a crushing blow to the "+hdesc+
	  " of "+QTNAME(enemy)+" and feel power surge through you as "+
	  "the dark shadow invades the very being of "+QTNAME(enemy)+
	  ", sending "+HIM(enemy)+" slumping to the ground!\n");
	enemy->catch_msg("You slump to the ground, overcome by the pull "+
	  "of the shadow as "+QTNAME(wielder)+" rips deeply into your "+
	  hdesc+" with "+HIS(wielder)+" "+short()+". You feel terror "+
	  "overcome you as the dark shadows invade your very being, "+
	  "tearing the very life from you!\n");
	wielder->tell_watcher(QCTNAME(wielder)+" smashes "+HIS(wielder)+
	  " sword onto the "+hdesc+" of "+QTNAME(enemy)+" leaving a "+
	  "gaping wound! The darkness from the sword leaps out, engulfing "+
	  "the terrible wound, and sending "+QTNAME(enemy)+" slumping to "+
	  "the ground.\n", enemy);
	break;

    default:
	wielder->catch_msg("Suddenly overcome with bloodlust, you lunge "+
	  "forward and impale "+QTNAME(enemy)+" on your massive blade "+
	  "with all of your might! The power courses through your veins "+
	  "as "+HIS(enemy)+" soul is drawn into the sword, and "+
	  "adds to your power! "+QTNAME(enemy)+" falls from the blade, "+
	  "shrivelled and lifeless, as you stand coldly over the corpse.\n");
	enemy->catch_msg(QCTNAME(wielder)+" lunges forward, driving "+
	  HIS(wielder)+" blade deep into your chest. You feel "+
	  "a strange peace overtake you as you yield to the pull of the "+
	  "dark spirit of the blade, and you feel no more.\n");
	wielder->tell_watcher(QCTNAME(wielder)+" powerfully thrusts the full length "+
	  "of "+HIS(wielder)+" blade into the the chest of "+
	  QTNAME(enemy)+" dark flames invading "+HIS(enemy)+" very "+
	  "being! "+QTNAME(enemy)+" falls from the blade, a shrivelled and "+
	  "lifeless corpse. You look with terror at "+QTNAME(wielder)+" who "+
	  "stands victoriously over the corpse, a look of rapture on "+
	  HIS(wielder)+" face.\n", enemy);
	break;
    }
    return 1;
}
