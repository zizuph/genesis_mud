inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 40
#define PEN 45

#define QRN(x, y) (x->query_race_name() == (y)) 
#define EQRN(x) QRN(enemy, x)

int enemy_type = 0;

void
create_weapon()
{
    set_name("flail");
    add_name("folly");
    add_name("club");
    add_adj("studded");
    add_adj("ironwood");
    set_short("studded ironwood flail");
    set_long("This flail radiates dark beauty, a weapon from a period beyond " +
      "antiquity yet unravaged by time. A long thick wooden haft has been " +
      "crafted from the incredibly rare ironwood, engraved with ancient symbols " +
      "and embossed with silver. A huge spiked ball of celestial metal links " +
      "to the haft with a long chain of the same material.\n");

    add_item(({"ancient symbols","symbols"}), "@@read_runes");
    add_cmd_item(({"ancient symbols","symbols"}), "read", "@@read_runes2");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_hands(W_RIGHT);
    set_dt(W_BLUDGEON);

    set_likely_dull(1);
    set_likely_break(1);
    set_likely_corr(1);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"It was crafted during the time of the first Ogre Wars during " +
	"the Age of Dreams, over six thousand years ago!\n", 25, 
	"This weapon was forged by the 'first born' of the mortal races and the " +
	"masters of creation, the darkly beautiful race that declined over the " +
	"millenia to become ogres. When their human slaves revolted against their " +
	"masters, human-slaying weapons such as this flail were forged. In the hands " +
	"of goblinoid and monstroid creatures, this flail is enchanted to be deadly " +
	"in accuracy. It is also enchanted to cause extra damage to humans.\n", 55,
	"Being made of celestial ore, the flail wears very slowly.\n", 65}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_S_WIZINFO, "This flail, 'Igraine's Folly', is a 40/45 one handed " +
      "club that provides +10 hit in the hands of goblinoids, minotaurs or ogres. " +
      "It also has a 1 in 3 change on hitting of doing double damage against humans. " +
      "It wears considerably slower than normal weapons.\n");
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,45) + 500 + random(500)); 
}


int
read_runes2()
{
    if(TP->query_skill(SS_LANGUAGE) < 40)
    {
	write("The ancient symbols are beyond your understanding. You are unable " +
	  "to work out what they say.\n");
	return 1;
    }
    write("The ancient symbols are from a language used in the Age of Dreams by " +
      "the dark and beautiful 'first born' race that devolved over the millenia " +
      "to what is now the race of ogres. The symbols can be translated to mean " +
      "'Igraine's Folly'.\n");
    return 1;
}

string
read_runes()
{
    if(TP->query_skill(SS_LANGUAGE) < 40)
    {
	return "The ancient symbols are beyond your understanding. You are unable " +
	"to work out what they say.\n";
    }
    return "The ancient symbols are from a language used in the Age of Dreams by " +
    "the dark and beautiful 'first born' race that devolved over the millenia " +
    "to what is now the race of ogres. The symbols can be translated to mean " +
    "'Igraine's Folly'.\n";
}

void
state_change(int hit, int pen)
{ 
    set_hit(hit);
    set_pen(pen);
    wielder->update_weapon(this_object());
}

void
wield_message(object wielder)
{
    wielder->catch_tell("The haft of your " +short()+ " pulses darkly in your hand.\n");
    tell_room(E(wielder), "The haft of " +QTPNAME(wielder)+ " " + short() + 
      " pulses darkly in " +HIS(wielder)+ " hand.\n", wielder);
}

mixed
wield(object what)
{
    if (QRN(TP, "hobgoblin") || QRN(TP, "goblin") || QRN(TP, "orc") || QRN(TP, "uruk") || 
      QRN(TP, "minotaur") || QRN(TP, "uruk-hai") || QRN(TP, "irda") || 
      QRN(TP, "half-ogre") || QRN(TP, "ogre"))
    {
	set_alarm(1.0, 0.0, &wield_message(TP));
	int new_hit = HIT + 10;
	state_change(new_hit, PEN);
    }
    else
    {
	state_change(HIT, PEN);
    }

    return 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
  int phit, int dam)
{
    int r;

    if (EQRN("human") || EQRN("half-elf"))
    {
	if(!random(3))
	{
	    wielder->catch_msg("The spiked ball of your " + short() + " radiates " +
	      "a cold celestial glow as you smash it into " +QTNAME(enemy)+ "!\n");
	    enemy->catch_msg("The spiked ball of " +QTPNAME(wielder)+
	      " " +short()+ " radiates a cold celestial glow as it smashes into you!\n");
	    enemy->tell_watcher("The spiked ball of " +QTPNAME(wielder)+ " " + 
	      short() + " radiates a cold celestial glow as it smashes into " +
	      QTNAME(enemy)+ ".\n", wielder);
	    r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, 2*dam);
	}
	else
	{
	    r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
	} 
    }
    else
    {
	r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    return r;
}

int
set_dull(int du)
{
    if (!random(3))
    {
	return 1;
    }

    return 0;
}
