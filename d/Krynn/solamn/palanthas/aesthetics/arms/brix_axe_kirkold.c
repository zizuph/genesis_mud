/*
 * Enchanted axe used by Kirk the leader of the
 * Brix gang of Jems Court in the aesthetics
 * quarter of Palanthas.  Taken from slain dwarf
 * it draws power from the shadows underground to
 * deal extra cold damage as a special so long as
 * there is light to create shadow.
 *
 * When I have time, I'd like to add a Neidar constable
 * who is notified whenever someone wields the axe
 * while unwrapped.  He would then follow the player
 * demanding its return.  Axe can be part of a quest
 * involving the slain Neidar from whom it was taken
 * whose bones are in the sewers nearby where the Brix
 * dumped him.
 *
 * Mortis 06.2006
 * Milan 27.12.2007 - bug fixes...
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include "../../local.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

// Prototypes
void set_up_grip();
void set_up_runes();
void wield_msg(object mwield);
void unwield_msg(object munwield);
int in_or_out();
int grip_wrapped = 1;
string spot_runes();
string read_runes();

//object wielder; //defined in /std/weapon.c  Milan

create_weapon()
{
	set_name("axe");
	add_name(({"axe"}));
	set_adj("shadow");
	add_adj(({"flickering", "onyx", "onyx-hafted", "steel"}));
	set_short("@@my_short");
	set_long("@@my_long");

	set_hit(38);
	set_pen(38);
	set_wt(W_AXE);
	set_dt(W_SLASH);
	set_hands(W_ANYH);
	set_wf(TO);

	set_likely_dull(9);   // Decr. chance to dull due to shadowstuff infusion.
	set_likely_break(10); // Same chance to break.
	
	set_keep(1);
	
	add_prop(OBJ_M_NO_SELL, "The shopkeeper cannot afford to buy " +
      "magical weapons.  You will have to find another market.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({23, "shadow"}));
    add_prop(MAGIC_AM_ID_INFO, ({"Dwarven forge magicks have harnessed the "
	+ "somber, biting cold of deep shadows into this short axe.\n", 20,
	  "If the grip is uncovered, its deep shadow magic will protect the "
	+ "wielder from cold but will not harm dwarves.\n", 40}));
	add_prop(OBJ_S_WIZINFO, "Dwarven forge magicks have harnessed the "
	+ "somber, biting cold of deep shadows into this short axe.  "
	+ "If the grip is uncovered, its deep shadow magic will protect the "
	+ "wielder from cold but will not harm dwarves.\n"
	+ "Must have hemp unwrapped from its handle first in order to gain "
	+ "cold protections when wielded.\nOffers non-cumulative 20% magic cold "
	+ "damage resistance.\n");

    add_prop(OBJ_I_WEIGHT, 2500 + random(700));
    add_prop(OBJ_I_VOLUME, 2200 + random(500));
    add_prop(OBJ_I_VALUE,  1800 + random(300));

	set_up_grip();
}

string
my_short()
{
	if (in_or_out())
		return "flickering shadow axe";

	return "onyx-hafted steel axe";
}

string
my_long()
{
  if (grip_wrapped == 1)
  {
	if (in_or_out() == 0)
		return "Angled back for wide arcing slices, the head of this short "
		+ "axe appears to have been lacquered a very dark grey except along "
		+ "its blade where its steel has been sharpened to a gleaming, razor "
		+ "edge.  A pair of lacquered, steel bands secure the back of the "
		+ "axe head to a shaft of darkwood studded with small, hemispherical "
		+ "onyx stones in steel settings that spiral down from the head to "
		+ "the handle whose contoured grip has recently been wrapped tightly "
		+ "in black hemp cloth.\n";
	
	return "Angled back for wide arcing slices, the head of this short axe "
	+ "is wrapped in flickering shadows like dark grey bands of bitingly "
	+ "cold flame that swirl gravely down its darkwood haft to its handle "
	+ "whose contoured grip has recently been wrapped tightly in black hemp "
	+ "cloth.\n";
  }
	
  if (in_or_out() == 0)
	  return "Angled back for wide arcing slices, the head of this short "
	  + "axe appears to have been lacquered a very dark grey except along "
	  + "its blade where its steel has been sharpened to a gleaming, razor "
	  + "edge.  A pair of lacquered, steel bands secure the back of the "
	  + "axe head to a shaft of darkwood studded with small, hemispherical "
	  + "onyx stones in steel settings that spiral down from the head to "
	  + "the handle whose contoured grip has been inlaid with three silver "
	  + "runes.\n";

  return "Angled back for wide arcing slices, the head of this short axe "
  + "is wrapped in flickering shadows like dark grey bands of bitingly "
  + "cold flame that swirl gravely down its darkwood haft to its handle "
  + "whose contoured grip has been inlaid with three silver runes.\n";	
}

int
in_or_out()
{
	object my_env = E(TO);

	if (living(my_env))
		my_env = E(my_env);

	if (my_env->query_prop(ROOM_I_INSIDE) &&
		my_env->query_prop(OBJ_I_LIGHT) > 0)
		return 1;

	return 0;
}

int
swing(string str)
{
	object amiwielded;

	NF("Swing what through the air?  Your " + short() + "?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] [my] [shadow] [flickering] [onyx] [onyx-hafted] [steel] 'axe' [through] [the] [air]"))
		return 0;
	
	NF("You must be wielding your " + short() + " in order to swing it.\n");
	if (!(amiwielded = query_wielded()))
		return 0;

	if (in_or_out())
	{
		write("You swipe your flickering shadow axe through the air, its "
		+ "flickering, shadow enshrouded head leaving a dark trail behind "
		+ "it momentarily.\nA cold breeze brushes past you.\n");
		say(QCTNAME(TP) + " swipes " + HIS(TP) + " flickering shadow axe "
		+ "through the air, its flickering, shadow enshrouded head leaving "
		+ "a dark trail behind it momentarily.\nA cold breeze brushes past "
		+ "you.\n");
		return 1;
	}

	write("You swing your onyx-hafted steel axe through the air.  You think "
	+ "for a moment that you felt a cool breeze brush past you.\n");
	say(QCTNAME(TP) + " swipes " + HIS(TP) + " onyx-hafted steel axe through "
	+ "the air as a cool breeze wafts by.\n");
	return 1;
}

int
unwrap(string str)
{
	NF("What?\n");
	if (grip_wrapped == 0)
		return 0;

	NF("Unwrap what?  The black hemp cloth tightly wrapped around the haft "
	+ "of your axe?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] [black] [hemp] 'cloth' [tightly] [wrapped] [around] [from] [on] [around] [axe]"))
		return 0;

	write("You unwrap the black hemp cloth tightly wrapped around the "
	+ "contoured grip of your " + short() + " revealing three silver inlaid "
	+ "runes beneath.\n");
	say(QCTNAME(TP) + " unwraps the black hemp cloth tightly wrapped around "
	+ "the contoured grip of " + HIS(TP) + " " + short() + ".\n");

	grip_wrapped = 0;
	set_up_runes();

	return 1;
}

void
init()
{
    ::init();

	ADA("swing");
	ADA("unwrap");
}

void
set_up_grip()
{
	if (grip_wrapped == 1)
	{
		ITEM(({"grip", "axegrip", "axe grip", "handle"}), "The grip of this "
		+ "short axe has recently been wrapped tightly in black hemp cloth."
		+ "@@spot_runes@@" + "\n");
	}
	else
		set_up_runes();
}

string
spot_runes()
{
	string seerunes = "";

	if (TP->query_skill(SS_AWARENESS) > 30)
	{	
		seerunes = "  Beneath the hemp cloth you can barely make out a bit "
		+ "of silver work, possibly writing, but you would have to unwrap "
		+ "it to be sure.";
	}

	return seerunes;
}

void
set_up_runes()
{
	if (grip_wrapped == 0)
	{
		remove_item("grip");
		ITEM(({"grip", "axegrip", "axe grip", "handle", "rune", "runes"}),
		  "Three silver runes have been inlaid onto the contoured grip of "
		+ "this short axe's handle" + "@@read_runes@@" + "\n");
		add_prop(OBJ_I_VALUE,  2100 + random(300));
	}
}

string
read_runes()
{
	string rrunes = ", but you cannot read them.  You believe they are "
	+ "dwarven.";

	if (TP->query_skill(SS_LANGUAGE) > 30 || TP->query_race_name() == "dwarf")
	{	
		rrunes = ".  You recognize them as Dwarven.\n"
		+ "The first is a name:  \"Shaydrach\"\n"
		+ "The second reads:     \"Deep shadow\"\n"
		+ "The third reads:      \"Cold\"\n";
	}

	return rrunes;
}

mixed
wield(object what)
{
    if (!wielder || wielder->query_npc())
    {
        return 0;
    }

    wielder->remove_magic_effect(TO);
    wielder->add_magic_effect(TO);
    set_alarm(1.0, 0.0, &wield_msg(wielder));
    return 0;
}

mixed
unwield(object what)
{
    if (!wielder || wielder->query_npc())
    {
        return 0;
    }
    
    wielder->remove_magic_effect(TO);
    set_alarm(1.0, 0.0, &unwield_msg(wielder));
    return 0;
}

void
leave_env(object to, object from)
{
    ::leave_env(to, from);

    if(!living(from))
        return;

    if (wielder)
    {
        wielder->remove_magic_effect(TO);
        wielder = 0;
    }
}

void
wield_msg(object mwield)
{
	string axegrip = "hemp wrapped handle",
		   coldmsg = "\n", coldmsg2 = "\n";

	if (!objectp(mwield)) return; // Milan

	if (grip_wrapped == 0)
	{
		axegrip = "silver-runed, contoured grip";
		coldmsg = "  A cool rush shoots up your arm!\nYou exhale a frozen "
		+ "puff of air.\n";
		coldmsg2 = "  " + QCTNAME(mwield) + "'s open wide as " + HE(mwield)
		+ " exhales a frozen puff of air.\n";
	}

	if (in_or_out())
	{
		mwield->catch_msg("The shadows enveloping your flickering shadow "
		+ "axe flare up briefly as you grasp the " + axegrip + "."
		+ coldmsg);
		say("The shadows enveloping " + QTNAME(mwield) + "'s flickering "
		+ "shadow axe flare up briefly as " + HE(mwield) + " grasps its "
		+ axegrip + "." + coldmsg2, mwield);
	}
	else
	{
		mwield->catch_msg("You get a sense of the onyx-hafted steel axe's "
		+ "exceptional balance as you grasp the " + axegrip + "." + coldmsg);
		say(QCTNAME(mwield) + " wields " + HIS(mwield) + " onyx-hafted "
		+ "steel axe deftly." + coldmsg2, mwield);
	}
}

void
unwield_msg(object munwield)
{
	string axegrip = "hemp wrapped handle", coldmsg = "\n", coldmsg2 = "\n";

	if (!objectp(munwield)) return; // Milan

	if (grip_wrapped == 0)
    {
        axegrip = "silver-runed, contoured grip";
        coldmsg = "  A warm rush floods your body through your arm.\n";
        coldmsg2 = "  " + QCTNAME(munwield) + " sighs warmly.\n";
    }

    if (in_or_out())
    {
        munwield->catch_msg("The shadows enveloping your flickering shadow "
                            + "axe swirl slowly as you release the " + axegrip + "."
                            + coldmsg);
        say("The shadows enveloping " + QTNAME(munwield) + "'s flickering "
            + "shadow axe swirl slowly as " + HE(munwield) + " releases its "
            + axegrip + "." + coldmsg2, munwield);
    }
    else
    {
        munwield->catch_msg("You unwield your onyx-hafted steel axe "
                            + "releasing your grasp on its " + axegrip + "." + coldmsg);
        say(QCTNAME(munwield) + " unwields " + HIS(munwield) + " onyx-hafted "
            + "steel axe introspectively." + coldmsg2, munwield);
    }
}

/* This function sends a message describing what the axe
 * does when its cold magic defense property is utilized.
 */
mixed
query_magic_protection(string prop, object protectee)
{
	// Doesn't work if handle is still wrapped.
	if (grip_wrapped == 1)
		return 0;

	// Doesn't work if in sunlight or complete darkness.
	if (in_or_out() == 0)
		return 0;

	if (!wielder || protectee != wielder)
		return 0;

	if (prop == MAGIC_I_RES_COLD)
	{
		wielder->catch_msg("The shadows enveloping your flickering "
		+ "shadow axe flare up briefly.\n");
		say("The shadows enveloping " + QTNAME(wielder) + "'s "
		+ "flickering shadow axe flare up briefly.\n");
		return ({20, 1});
	}

	return 0;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam,
        int hid)
{
    mixed ret = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    if (!objectp(wielder)) return ret; // Milan

	// Check 15% special first to minimize processing.
	if (random(100) >= 15)
	{
		if (random(5) != 1)
			return 0;

		enemy->catch_msg("The shadows enveloping " + QTNAME(wielder) + "'s "
		+ short() + " flutter past you like an icy breeze.\n");
		wielder->catch_msg("The shadows enveloping your " + short()
		+ " flutter past " + QTNAME(enemy) + " like an icy breeze.\n");
		say("The shadows enveloping " + QTNAME(wielder) + "'s " + short()
		+ " flutter past " + QTNAME(enemy) + " like an icy breeze.\n",
			(({enemy, wielder})));

		return 0;
	}

	// Doesn't do a special if in sunlight or complete darkness.
	if (in_or_out() == 0)
		return 0;

	// Shadows do not harm dwarves if handle is unwrapped.
	if (grip_wrapped == 0 && QRACE(enemy) == "dwarf")
		return 0;

	int cold_dmg, res = enemy->query_magic_res(MAGIC_I_RES_COLD);

	cold_dmg = dam / 2;
	cold_dmg = cold_dmg - (cold_dmg * res/100);

	enemy->hit_me(cold_dmg, MAGIC_DT, TO, -1, hid);

	if (cold_dmg < 1)
	{
		enemy->catch_msg("The shadows trailing from " + QTNAME(wielder)
		+ "'s " + short() + " pass you by like a chill breeze.\n");
		return 1;
	}

	enemy->catch_msg("The shadows enveloping " + QTNAME(wielder) + "'s "
	+ short() + " drain you icily leaving your body numb.\n");
	wielder->catch_msg("The shadows enveloping your " + short()
	+ " drain " + QTNAME(enemy) + " icily.\n");
	say("The shadows enveloping " + QTNAME(wielder) + "'s " + short()
	+ " drain " + QTNAME(enemy) + " icily.\n", (({enemy, wielder})));
  
	return 0;
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#p_u#" + grip_wrapped;
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
    sscanf(arg, "%s#p_u#%d", grip_wrapped);
}
