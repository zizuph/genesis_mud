#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit "/std/weapon";

create_weapon()
{
    set_name("life-stealer");
    add_name("sword");
    add_name("blade");
    add_adj("shadow");
    set_short("Shadow Blade");
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
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 13500);
    set_wf(TO);
    set_pm(({-3,0,3}));
    seteuid(getuid(TO));
}

void
wield_message1()
{
    write("As you wrap your hands around the blackened hilt of this sword, "+
      "you feel a dark presence enter, consuming you with bloodlust!\n");

    say("As " + QCTNAME(TP) + " clutches the hilt of the massive sword, " +
      POSSESSIVE(TP) + " eyes light up with an unholy light, and " +
      QCTNAME(TP) + " looks strangely around, as if searching for "+
      "something...\n");
}


void
wield_message2()
{
    write("A cold commanding presence rises up inside you, and you feel a "+
      "strong tugging in your mind to take a life.\n");

    say(QCTNAME(TP) + " suddenly stiffens, and looks around with a peculiar "+
      "gleam in " + POSSESSIVE(TP) + " eyes.\n");
}


mixed
wield(object what)
{

    if(TP->query_skill(SS_WEP_SWORD) < 81)
    {
        write("You foolishly attempt to wield Shadow Blade! \n"+
          "As you wrap your hands around the hilt, you stare in horror at the blade "+
          "that draws heavily on your soul for your insolence!\n");
        TP->heal_hp(-800-random(200));
        say(QCTNAME(TP) + " turns horribly pale as "+PRONOUN(TP)+" wraps "+
          POSSESSIVE(TP)+" hands around the hilt of Shadow Blade!\n");

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
    set_alarm(1.0, 0.0, "wield_message1");
    set_alarm(5.0, 0.0, "wield_message2");
    return 0;
}

mixed
unwield(object what)
{
    wielder->catch_msg("As you release your grip on the sword, the evil " +
      "presence leaves your mind, and you feel in control "+
      "once again. You feel quite relieved...\n");
    say(QCTNAME(wielder) + "'s eyes lose their disturbing gleam as " +
      POSSESSIVE(TP) + " hands release their grip on the two-handed sword.\n");
    //    wielder = 0;
    return 0;
}

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_option(OPT_BLOOD) == 0)
            ob[i]->catch_msg(str);
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{

    switch(phurt)
    {
    case -1:
    case -2:
        wielder->catch_msg("You swing the " + short() + " at " +
          QTNAME(enemy) + " wildly, a dark shadow trailing the blade.\n");
        enemy->catch_msg(QCTNAME(wielder)+" swings "+POSSESSIVE(wielder) +
          " "+short()+" at you, but you manage to avoid the blade.\n");
        tell_watcher(QCTNAME(wielder)+" swings "+POSSESSIVE(wielder) +
          " "+short()+" at "+QTNAME(enemy)+" but misses leaving dark shadows "+
          "in the air.\n", enemy);
        break;

    case 0:
        wielder->catch_msg("You swing the " + short() + " very close to " +
          QTNAME(enemy) + ", the shadow following the blade.\n");
        enemy->catch_msg(QCTNAME(wielder) + " barely misses you with " +
          POSSESSIVE(wielder)+" "+short()+" leaving you quite unnerved at "+
          "the sight of the evil blade.\n");
        tell_watcher(QCTNAME(wielder) + " swings the " + short() +
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
        tell_watcher(QTNAME(enemy) + " turns slightly pale as "+
          QTNAME(wielder)+" grazes "+POSSESSIVE(enemy)+" "+hdesc+" with the "+
          short()+".\n", enemy);
        break;

    case 5..9:
        wielder->catch_msg("You draw blood from "+QTNAME(enemy)+"'s "+
          hdesc+" with your blade, the shadow brushes over the wound "+
          "bringing obvious pain to "+POSSESSIVE(enemy)+" face.\n");
        enemy->catch_msg("The darkness around the blade tugs at your "+
          "soul as "+QTNAME(wielder)+" grazes your "+hdesc+".\n");
        tell_watcher(QCTNAME(enemy) + " winces as the blade grazes " +
          POSSESSIVE(enemy)+" "+hdesc+".\n", enemy);
        break;

    case 10..19:
        wielder->catch_msg("You tear a wound into the " + hdesc + " of " +
          QTNAME(enemy) + " and take great pleasure as the shadow "+
          "causes obvious pain to "+QTNAME(enemy)+".\n");
        enemy->catch_msg(QCTNAME(wielder) + " tears into your " + hdesc +
          " with the " + short() + ". The tugging at your soul grows "+
          "stronger, you feel yourself weakening.\n");
        tell_watcher(QCTNAME(wielder) + " grins in satisfaction as "+
          POSSESSIVE(wielder)+" blade tears into the "+hdesc+" of "+
          QTNAME(enemy)+", leaving "+PRONOUN(enemy)+" visibly "+
          "shaken.\n", enemy);
        break;

    case 20..29:
        wielder->catch_msg("You bash the hilt of your sword into "+
          QTNAME(enemy)+"'s face and laugh coldly as "+
          PRONOUN(enemy)+" staggers backwards.\n");
        enemy->catch_msg("You stagger as "+QTNAME(wielder)+" slams "+
          "the hilt of "+POSSESSIVE(wielder)+" sword into your face and "+
          "are overcome with pain.\n");
        tell_watcher(QCTNAME(enemy) + " staggers as "+QTNAME(wielder)+
          " slams the hilt of "+POSSESSIVE(wielder)+" sword into "+
          POSSESSIVE(enemy)+" face.\n", enemy);
        break;

    case 30..49:
        wielder->catch_msg("You slash deeply into the "+hdesc+" of "+
          QTNAME(enemy)+" the dark shadow licking at the wound!\n");
        enemy->catch_msg(QCTNAME(wielder) + " slashes deeply into your "+
          hdesc+" with "+POSSESSIVE(wielder)+" sword, and you feel an "+
          "immense pain as the shadow envelopes the wound!\n");
        tell_watcher(QTNAME(enemy) + " recoils in pain as a deep wound "+
          "is torn into "+POSSESSIVE(wielder)+" "+hdesc+" with the "+short()+
          ".\n", enemy);
        break;

    case 50..69:
        wielder->catch_msg("You brutally smash the hilt of your sword "+
          " into "+QTNAME(enemy)+"'s face, sending "+PRONOUN(enemy)+
          " sprawling to the ground!\n");
        enemy->catch_msg("You feel yourself lifted of the ground from "+
          "the sheer force of the blow as "+QTNAME(wielder)+" crushes "+
          "the hilt of "+POSSESSIVE(wielder)+" sword into your face!\n");
        tell_watcher(QCTNAME(enemy) + " is sent sprawling to the ground "+
          "as "+QTNAME(wielder)+" brutally crushes the hilt of "+
          POSSESSIVE(wielder)+" sword into "+QTNAME(enemy)+
          "'s face!\n", enemy);
        break;

    case 70..89:
        wielder->catch_msg("You deliver a crushing blow to the "+hdesc+
          " of "+QTNAME(enemy)+" and feel power surge through you as "+
          "the dark shadow invades the very being of "+QTNAME(enemy)+
          ", sending "+PRONOUN(enemy)+" slumping to the ground!\n");
        enemy->catch_msg("You slump to the ground, overcome by the pull "+
          "of the shadow as "+QTNAME(wielder)+" rips deeply into your "+
          hdesc+" with "+POSSESSIVE(wielder)+" "+short()+". You feel terror "+
          "overcome you as the dark shadows invade your very being, "+
          "tearing the very life from you!\n");
        tell_watcher(QCTNAME(wielder)+" smashes "+POSSESSIVE(wielder)+
          " sword onto the "+hdesc+" of "+QTNAME(enemy)+" leaving a "+
          "gaping wound! The darkness from the sword leaps out, engulfing "+
          "the terrible wound, and sending "+QTNAME(enemy)+" slumping to "+
          "the ground.\n", enemy);
        break;

    default:
        wielder->catch_msg("Suddenly overcome with bloodlust, you lunge "+
          "forward and impale "+QTNAME(enemy)+" on your massive blade "+
          "with all of your might! The power courses through your veins "+
          "as "+POSSESSIVE(enemy)+" soul is drawn into the sword, and "+
          "adds to your power! "+QTNAME(enemy)+" falls from the blade, "+
          "shrivelled and lifeless, as you stand coldly over the corpse.\n");
        enemy->catch_msg(QCTNAME(wielder)+" lunges forward, driving "+
          POSSESSIVE(wielder)+" blade deep into your chest. You feel "+
          "a strange peace overtake you as you yield to the pull of the "+
          "dark spirit of the blade, and you feel no more.\n");
        tell_watcher(QCTNAME(wielder)+" powerfully thrusts the full length "+
          "of "+POSSESSIVE(wielder)+" blade into the the chest of "+
          QTNAME(enemy)+" dark flames invade "+POSSESSIVE(enemy)+" very "+
          "being! "+QTNAME(enemy)+" falls from the blade, a shrivelled and "+
          "lifeless corpse. You look with terror at "+QTNAME(wielder)+" who "+
          "stands victoriously over the corpse, a look of rapture on "+
          POSSESSIVE(wielder)+" face.\n", enemy);
        break;
    }
    return 1;
}
