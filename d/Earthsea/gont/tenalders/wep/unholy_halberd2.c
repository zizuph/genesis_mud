/* unholy halberd wielded by black priestess of Ten Alders
*  Ten Alders 
*  Amelia 5/3/97
 *
 * Fixed a bug causing runtime error in present in unwield
 * Put in a fix in case mana should compute as a positive number
 * Amelia 7/18/98
 * Mana consumption and unwield message changed.  Made Keepable Ckrik 7/1998
 * Magic Info updated. Ckrik 7/1998
 * ::did_hit added.  Amelia 7/26/98
*/
inherit "/d/Earthsea/std/weapon";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>
#define SUBLOC "_unholy_aura_"


//int hit = 37;
//int pen = 49;

/*  prototypes */
mixed wield(object what);
int did_hit(int aid, string hdesc, int phurt, object enemy,
  int dt, int phit, int dam);
int unwield();
int swing_it(string str);

void
create_earthsea_weapon()
{
    set_name("halberd");
    set_adj("unholy");
    set_short("unholy halberd");
    set_long(break_string("A long-shafted halberd, which "+
	"must be wielded in both hands. It has a razor sharp "+
	"mithril axe blade on the end with a devilish hook behind. "+
	"When the halberd is swung or used in battle, dark "+
	"shadows seem to flow from it creating an aura. "+
	"The long haft is made from ebony, smoothly carved to fit "+
	"the hand and give just the right balanced weight to it. "+
	"The blade glows with a dark unholy light.\n", 70));
    set_hit(37);
    set_wt(W_POLEARM);
    set_wf(TO);
    set_pen(49);
/*    set_dt(W_BLUDGEON | W_IMPALE | W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(hit, pen) +
      random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);*/
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, "death");
    /* As of right now there is no curse, but it will probably be
     * added in the future.
     */
    add_prop(MAGIC_AM_ID_INFO, ({"The weapon is cursed.\n", 10,
	"A dark aura surrounds the " +
	"wielder when the weapon is wielded.\n", 20, "The dark " +
	"presence inside the halberd drains the wielder's mana " +
	"when attempting to wield the weapon.\n", 30, "However, " +
	"a wise person might be able to prevent the dark presence " +
	"from leeching his or her mana.\n", 40,
	"The dark presence inside the halberd prevents it from ever " +
	"dulling.\n", 45}));
    add_prop(OBJ_S_WIZINFO, "This halberd is wielded by "+
      "the karg captain in Ten Alders--Earthsea. The unholy " +
      "presence in the halberd hits for more damage. The " +
      "special is a regular hit, only there for cosmetics. " +
      "Since this weapon is enchanted it does not dull.\n");
}


int
did_hit(int aid, string hdesc, int phurt, object enemy,
  int dt, int phit, int dam)
{
    object me = environment(TO);
    object *us;
    int x = random(8);  /* special occurs 1 hit in 8 */
    int y = random(20);
    string *places;
    string place;
    string *hows;
    string how;


    // added 7/26/98 == Amelia
    ::did_hit(aid, hdesc,phurt, enemy, dt, phit, dam);

    // number of times special hits, 1 in 8
    if (x)
	return 0;


    places = ({"left cheek", "right cheek", 
      "right ear", "left ear", "nose", "left thigh",
      "face", "left calf", "right calf", "left knee", "right knee",
      "right thigh", "back", "chin",
      "groin", "buttocks"});
    hows = ({ "vigorously", 
      "nastily", "viciously", "evilly", "cruelly",
      "fiercely", "wickedly", "deftly", "expertly",
      "brutally", "savagely", "fanatically", "sadistically" });

    how = hows[random(13)];
    place = places[random(16)]; 

    if (y > 13)
	tell_room(environment(me), "Dark shadows swirl around "+
	  "the unholy halberd.\n", ({}));

    us = ({me, enemy});


    switch(phurt)
    {
    case -1:
	enemy->catch_msg(QCTNAME(me) + " swings the "+
	  TO->query_short() + " just past your right ear. You "+
	  "hear a loud hissing noise.\n");
	me->catch_msg("You barely miss "+QTNAME(enemy)+
	  " with a wide swing of your "+TO->query_short()+
	  ".\n");
	environment(this_object())->tell_watcher(QCTNAME(me) + " swings the "+
	  TO->query_short() + " just past "+ QTNAME(enemy)+
	  ", barely missing "+enemy->query_possessive()+
	  " right ear.\n", enemy, us);
	break;

    case 0..1:
	enemy->catch_msg(QCTNAME(me)+ " "+ how + " slices your "+place+
	  " with the "+TO->query_short()+", drawing a trickle of "+
	  "blood.\n");
	me->catch_msg("You "+how+" slice the "+place+ " of "+
	  QTNAME(enemy)+" with your "+TO->query_short()+", drawing "+
	  "a trickle of blood.\n");
	environment(this_object())->tell_watcher(QCTNAME(me) + " " + how + " slices the "+place+
	  " of " +QTNAME(enemy)+" with " +me->query_possessive()+
	  " "+TO->query_short()+ ", drawing a trickle of blood.\n", 
	  enemy, us);
	break;

    case 2..3:
	enemy->catch_msg(QCTNAME(me)+ " pierces your "+place+ " "+
	  "with the "+TO->query_short() + ".\n");
	me->catch_msg("You pierce " + QCTNAME(enemy) + " in the "+
	  place + " with your " + TO->query_short() + ".\n");
	environment(this_object())->tell_watcher(QCTNAME(me) + " pierces "+ QTNAME(enemy) +
	  " in the "+ place + " with the " + TO->query_short() + ".\n",
	  enemy, us);
	break;



    case 7..10:
	enemy->catch_msg(QCTNAME(me)+" "+ how + " gashes your "+place+" "+
	  "with the hook on the back side of the "+TO->query_short()+".\n"+
	  "You break out in a cold sweat!\n");
	me->catch_msg("You "+how+" gash the "+ place + " of "+
	  QTNAME(enemy) + " with the hook on the back side of the "+
	  TO->query_short()+"!\n"+
	  QCTNAME(enemy) + " begins to sweat heavily!\n");
	environment(this_object())->tell_watcher(QCTNAME(me) + how + " gashes the "+place+" of "+
	  QTNAME(enemy) + " with the hook end of the " + TO->query_short()+
	  "!\n"+QCTNAME(enemy) + " begins to sweat heavily!\n", enemy, us);
	break;




    case 16..20:
	enemy->catch_msg(QCTNAME(me)+ " viciously hacks your head "+
	  "with the edge of the "+TO->query_short()+"!\nYou are "+
	  "almost decapitated!\n");
	me->catch_msg("You viciously hack at the head of "+
	  QTNAME(enemy) + " with your "+TO->query_short()+"!\nYou almost "+
	  "succeed in decapitating " + enemy->query_objective() +".\n");
	environment(this_object())->tell_watcher(QCTNAME(me) + " viciously hacks at the head "+
	  "of "+ QTNAME(enemy)+ " with the "+TO->query_short()+"!\n"+
	  QCTNAME(enemy)+" is almost decapitated!\n", enemy, us);
	break;

    default:
	enemy->catch_msg(QCTNAME(me) + " " + how + " slashes your "+
	  place + " with the blade of the " + TO->query_short() + ".\n");
	me->catch_msg("You " + how + " slash " + QTNAME(enemy) +
	  "'s " + place + " with the blade of your "+
	  TO->query_short() + ".\n");
	environment(this_object())->tell_watcher(QCTNAME(me) + " " + how + " slashes the " + place +
	  " of " + QTNAME(enemy) + ".\n", enemy, us);
	break;
    }

    if(enemy->query_hp() <= 0)
    {
	enemy->catch_msg("You die screaming!\nAs your soul "+
	  "leaves its body, the last thing \n"+
	  "you see are the black shapes of the Nameless Ones, \n"+
	  "coming to collect you!\n");
	tell_room(environment(me), QCTNAME(enemy) + " dies "+
	  "screaming!\nA horrible wailing noise trails off "+
	  "into the distance...\n", ({enemy}));
	enemy->do_die(me);
	return 1;

    }

    return 1;

}

mixed
wield(object what)
{
    object tp = this_player();
    int mana;

    if (tp->query_stat(SS_WIS) < 60)
	return "You are not wise enough to "+
	"wield the "+ TO->query_short() + ".\n";

    //Mana consumption is 200 to 400 - the wielder's wisdom. Ckrik 7/1998
    mana = -1 * (200 + random(200) - this_player()->query_stat(SS_WIS));


    if (tp->query_mana() > -1 * mana)
    {
	tp->catch_msg("A dark aura surrounds you as you wield the "+
	  TO->query_short() + ".\nYou hear a loud crash of thunder!\n");
	tell_room(environment(tp), "As "+QTNAME(tp)+" wields "+
	  "the "+TO->query_short()+", "+tp->query_pronoun()+" is "+
	  "shrouded in a dark aura!\nYou hear a loud crash of "+
	  "thunder!\n", ({tp}));
	tp->add_subloc(SUBLOC, TO);
	tp->catch_msg("You feel mentally drained as you wield the "+
	  TO->query_short() + "!\n");
	tp->add_mana(mana);
	return 0;
    }

    return "Your mind is not strong enough to wield "+
    "the "+ TO->query_short() + ".\n";
}

int
unwield()
{
    object tp = this_player();

    if (!TO->query_wielded())
    {
	notify_fail("You don't wield the "+TO->query_short()+".\n");
	return 0;
    }
    if (tp == TO->query_wielded())
    {
	/*
		tp->remove_subloc(SUBLOC);

		tp->catch_msg("As you unwield the "+TO->query_short()+
		  ", the dark aura dissipates and the world looks brighter.\n");
		return 1;
	*/
	tp->catch_msg("The dark aura sticks to you!\n");
    }
}

void
query_recover()
{
    return MASTER+":"+query_wep_recover();
}
void
init_recover(string arg)
{
    init_wep_recover(arg);
}

string
show_subloc(string subloc, object wielder, object for_obj)
{
    string str;
    if (wielder->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return ""; /* don't show this subloc as inventory */
    if (for_obj == wielder)
	str = "You are shrouded in a dark unholy aura.\n";
    else
	str = capitalize(wielder->query_pronoun())+
	" is shrouded in a dark unholy aura.\n";
    return str;
}

void
init()
{
    ::init();
    add_action(&swing_it(), "swing");
}

int
swing_it(string str)
{
    object tp = this_player();
    object to = this_object();

    if (id(str) && (!present(to, tp)))
    {
	tp->catch_msg("You don't have the halberd.\n");
	return 1;
    }

    if (id(str) && (!to->query_wielded()))
    {
	tp->catch_msg("You do not wield the halberd.\n");
	return 1;
    }

    if (id(str))
    {
	tp->catch_msg("As you swing the " + to->query_short() + 
	  " wildly about your head, dark shadows emanate from it, "+
	  "filling the area and surrounding you in a dark aura.\n");
	tell_room(environment(tp), QCTNAME(tp) + " swings the "+
	  to->query_short() + " wildly about " + tp->query_possessive() + " "+
	  "head, and "+
	  "shadows emanate from the blade and surround "+
	  tp->query_objective() + "!\n",
	  ({tp}));
	return 1;
    }
    notify_fail("Swing what? Are you a monkey?\n");
    return 0;
}
