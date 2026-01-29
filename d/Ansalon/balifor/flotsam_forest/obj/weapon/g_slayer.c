/** Navarre August 16th 2007, updated the sword to do more damage against goblin kinds.
 *  The sword is well guarded, and have existed for many years, and have grown a tad
 *  useless, it is a little better now, although not any major upgrade.
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 48
#define PEN 48
 
#define HIT2 34
#define PEN2 30
 
#define EQRN enemy->query_race_name()

int enemy_type = 0;

void
create_weapon()
{
    set_name("goblinbane");
    add_name("sword");
    add_name("longsword");
    add_adj("green-tinted");
    add_adj("green");
    set_short("green-tinted longsword");
    set_long("This green-tinted longsword seems to be made of " +
      "an unusual emerald coloured steel. You notice along the " +
      "blade are written ancient runes.\n");

    add_item(({"ancient runes","runes"}),"@@read_runes");
    add_cmd_item(({"runes","ancient runes"}),"read","@@read_runes2");

    set_hit(HIT2);
    set_pen(PEN2);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_dt(W_SLASH | W_IMPALE);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"The longsword was crafted long ago for a noble " +
	"warrior in the goblin wars.\n",25,"This blade " +
	"has been enchanted to slay those of goblin heritage. " +
	"Thus goblins generally cannot wield it, although " +
	"history has shown that those rare goblins who " +
	"were pure of heart or strong willed were able to carry " +
	"this blade into battle.\n",55}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35) + 500 + random(500)); 
}


int
read_runes2()
{
    if(TP->query_skill(SS_LANGUAGE) < 40)
    {
	write("The ancient runes glow softly with an emerald light. " +
	  "You are unable to work out what they say.\n");
	return 1;
    }
    write("The ancient runes glow softly with an emerald light, " +
      "and seem to be of an ancient Solamnian language, probably old " +
      "Ergothian. You think the runes read 'Goblinbane'.\n");
    return 1;
}

string
read_runes()
{
    if(TP->query_skill(SS_LANGUAGE) < 40)
    {
	return "The ancient runes glow softly with an emerald light. " +
	"You are unable to work out what they say.\n";
    }
    return "The ancient runes glow softly with an emerald light, " +
    "and seem to be of an ancient Solamnian language, probably old " +
    "Ergothian. You think the runes read 'Goblinbane'.\n";
}


mixed
wield(object what)
{
    if(TP->query_race() == "goblin" && TP->query_alignment() < 1200)
	return "The " + short() + " refuses you. You cannot wield it.\n";
    return 0;
}

void
state_change(int hit, int pen)
{
 
    set_hit(hit);
    set_pen(pen);
 
    if (wielded && wielder)
        wielder->update_weapon(this_object());
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int r;
 
    if ((EQRN == "hobgoblin") || (EQRN == "goblin") ||
        (EQRN == "orc") || (EQRN == "uruk") || (EQRN == "uruk-hai"))
    {
	r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, 2*dam);	

        if(!random(4))
        {
            wielder->catch_tell("Your " + short() + " starts glowing " +
                "with a dark emerald light!\n");
            tell_room(E(wielder), "The " + short() + " wielded by " +
                QTNAME(wielder) + " starts glowing with a dark emerald light.\n",
                wielder);
        }


        /* Switch to high power */
        if (!enemy_type)
        {
            state_change(HIT, PEN);
            enemy_type = 1;
        }
 
    }
    else
    {
	r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
	
        /* Switch to low power */
        if (enemy_type)
        {
            state_change(HIT2, PEN2);
            enemy_type = 0;
        }
    }
    return r;
}
