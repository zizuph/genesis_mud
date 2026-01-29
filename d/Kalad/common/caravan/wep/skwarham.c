#include "../default.h"
inherit (STD + "weapon");

#include <ss_types.h>
#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("warhammer");
    set_adj("massive");
    add_adj("two-handed");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("massive two-handed warhammer");
    set_long("This is the largest warhammer you have ever seen. Any "+
      "ordinary individual would clearly have to use both hands to pick it "+
      "up, let alone wield it. Upon the handle is engraved an image of a "+
      "dark sun.\n");
    set_hit(41);
    set_pen(43);
    set_hands(W_BOTH);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_wf(TO);
    add_prop(OBJ_I_VALUE,960);
    add_prop(OBJ_I_WEIGHT,15000);
    add_prop(OBJ_I_VOLUME,12000);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_S_WIZINFO, "This warhammer has been specifically "+
      "enchanted to provide it with a greater chance to hit and penetrate "+
      "in combat. Because this is a holy weapon used by priests, only those "+
      "individuals with a wisdom over 100 will be able to wield it. Anyone "+
      "that tries to wield the weapon and fails will be dealt a blow from "+
      "the weapon, resulting in a random loss of hit points. This weapon "+
      "can be found on the Skull Knight(/d/Kalad/common/caravan/npc/sknight). "+
      "Also the wielder must have a strength stat over 50 to wield it, due to "+
      "the weapon's size.\n");
    add_prop(MAGIC_AM_ID_INFO,({"The warhammer is magical\n", 5,
	"The warhammer has been enchanted to hit and penetrate more.\n", 25,
	"The enchanted warhammer has been magically imbued to hit and ,"+
	"penetrate more. Failure to wield it will result in bodily harm.\n", 51}));
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
}

mixed
wield(object what)
{
    if (TP->query_base_stat(SS_WIS) > 100)
	if(TP->query_base_stat(SS_STR) > 50)
	{
	    write("As your hands slowly grip the handle of the warhammer, you "+
	      "feel a slight jolt of energy flow into your arms and then slowly "+
	      "through the rest of your body.\n");
	    say(QCTNAME(TP) + " visibly trembles as " + TP->query_pronoun() + " grips the handle of the massive two-handed warhammer.\n");
	    return 0;
	}
    TP->heal_hp(-random(150)-50);
    return "As soon as you attempt to wield the warhammer a burning jolt "+
    "of energy rips through your arms and into the rest of your body, "+
    "searing the flesh from your bones.\n";
}

void
init()
{
    ::init();
    add_action("slam","slam");
}

void
slam_effect(object tp)
{
    if (!objectp(tp))
        return;
    write("The ground below trembles and quivers like a bowlful of jelly.\n");
    say("The ground below trembles and quivers like a bowlful of jelly.\n");
    say("You gaze in fear at " + QCTNAME(tp) + ".\n");
}

int
slam()
{
    object tp = this_player();

    if (!query_wielded())
    {
	write("You must wield the warhammer first.\n");
	return 1;
    }
    write("You hold the massive two-handed warhammer high above your head, "+
      "and then slam it down upon the ground with terrible force.\n");
    say(QCTNAME(TP) + " holds the massive two-handed warhammer high above " + TP->query_possessive() + " head, and then slams it down upon the ground with terrible force.\n");
    set_alarm(3.0, 0.0, &slam_effect(tp));
    return 1;
}
