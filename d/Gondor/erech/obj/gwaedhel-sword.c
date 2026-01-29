/*
 * gwaedhel-sword.c
 * By Skippern
 * May 20 (c) 00
 *
 * A unique artifact (one of its kind only). It is a part of a pear with
 *  a spear.
 * Sword yilds extra damage and gives panic in combat. The weapon have a
 *  set of emotions and specials that can be exlored.
 */
inherit "/std/weapon";

#include "../erech.h"
#include "../lib/gwaedhil.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit E_LIB + "gwaedhil.c";

#define HIT 60
#define PEN 25

/* Prototypes */
void               create_weapon();
int                swinging();

/*
 * Function name:    create_weapon()
 * Description  :    Creates the weapon.
 */
void
create_weapon()
{
    set_name("broadsword");
    add_name("sword");
    set_adj("twin-bladed");
    add_adj("blackened");
    set_short("twin-bladed blackened broadsword");
    set_pshort("twin-bladed blackened broadswords");
    set_long("This " + short() + " is an old powerful artifact. When you " +
        "grip the hilt, you feel magical powers run through your veins, and " +
        "when you draw your finger across the edge, it feels razor sharp. " +
        "The dark colour seems to have been applied long after the sword " +
        "was forged, and it is as dark as if it consumes light. There are " +
        "some marks along the hilt and along the blade.\n");

    add_item(( { "blade", "double blade", "twin-blade" } ), "The dark blade " +
        "has razor sharp edges on both sides. There are some marks " +
        "along the blade.\n");
    add_item(("hilt"), "The hilt has a shape that fits well into your " +
	"hand. It feels good to wield this weapon. There are some marks on " +
        "it.\n");
    add_item(("marks"), "What marks did you want to examine? The marks on " +
        "the hilt or along the blade?\n");
    add_item(("words"), "What words did you want to examine? The words on " +
        "the hilt or along the blade?\n");
    add_item( ({ "marks on the hilt", "marks along the hilt",
		   "marks on hilt", "marks along hilt" }), 
        "The marks seem like a word with a small sign behind.\n");
    add_item(("sign"), "It is the personal sigel of a smithy in Tirith " +
	"Aear.\n");
    add_item( ({ "marks on the blade", "marks along the blade",
		   "marks on blade", "marks along blade" }), 
        "They seem like a line of words running accross the blade.\n");
    add_item( ({ "words on the hilt", "words along the hilt", "words on hilt",
		   "words along hilt", "words on the blade", 
		   "words along the blade", "words on blade", 
		   "words along blade" }),
        "It looks like several letters in a row forming words, maybe you " +
	"should read them?\n");
    add_cmd_item( ({ "words on hilt", "words on the hilt",
		       "words along hilt", "words along the hilt" }),
        "read", &quenya_name());
    add_cmd_item( ({ "words on blade", "words on the blade",
		       "words along the blade", "words along blade" }),
      "read", &quenya_sword());
    add_cmd_item( ({ "words on hilt", "words along hilt",
		       "words on the hilt", "words along the hilt" }),
	"translate", &translate_name());
    add_cmd_item( ({ "words on blade", "words along the blade",
		       "words on the blade", "words along blade" }),
	"translate", &translate_sword());

    set_may_not_recover();

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE | MAGIC_DT);

    set_hands(W_ANYH);

    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_RES_ACID, 10);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({ "This blade comes from the anvils of an " +
				    "elven smith in Tirith Aear.", 20,
				  "This blade comes from the anvils of an " +
				    "elven smith in Tirith Aear. It was " +
				    "given to Isildur long ago.", 40,
				  "This blade comes from the anvils of an " +
				    "elven smith in Tirith Aear. It was " +
				    "given to Isildur long ago, who gave " +
				    "it to Morthec as a token of the Oath " +
				    "of Isildur.", 60 }));
    add_prop(MAGIC_AM_MAGIC, ({ 15, "enchantment" }));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(250) + 1000 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) +
	random(50) - 25 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_S_WIZINFO, "This weapon has extra damage and it frightens " +
	"the enemy. In rare cases it can backfire on the wielder. It was " +
        "forged in Tirith Aear by elven smiths long ago, and given " +
	"to Isildur. It is a part of a pair named the Gwaedhil (Oath " +
	"sister). The hit/pen is: " + HIT + "/" + PEN + ".");

    set_wf(this_object());

    do_dream();

}

void
init()
{
    ::init();
    add_action("do_swing", "swing");
    add_action("do_kneel", "pray");
}

mixed
wield(object wep)
{
    int Undead = this_player()->query_prop(LIVE_I_UNDEAD);

    if (this_player()->query_guild_name_race() == "Dunedain" )
    {
        write("As you take the grip round the hilt of your sword you think " +
	    "back on the story of the Oath of Isildur, and the breaking " +
	    "of it in ages long ago.\n");

	say(QCTNAME(this_player()) + " becomes lost in " +
	    "thought as " + this_player()->query_pronoun() + " wields the " +
	    "twin-bladed blackened broadsword.\n");

	return 1;
    }

    if (Undead >= 1 )
    {
        write("As you grip the twin-bladed blackened broadsword, you hear " +
            "the whipering voice of Isildur in the distance.\n");
	say(QCTNAME(this_player()) + " seems troubled as " + 
	    this_player()->query_pronoun() + " hears something in the " +
	    "distance.\n");
	return 1;
    }
  
    write("As you grip your twin-bladed blackened broadsword, you feel the " +
	"might of the sword filling you.\n");

    say(QCTNAME(this_player()) + " seems filled with might as " +
	this_player()->query_pronoun() + " wields the twin-bladed blackened " +
	"broadsword.\n");

    return 1;
}

int
do_swing(string what)
{
    if (what == "sword")
        swinging();
    else
        write("Swing what?\n");

    return 1;
}

int
do_kneel(string what)
{
    int Wielded = 0;
    object Wielder = query_wielded();

    if (Wielder)
      Wielded = 1;

    if (what == "by sword")
      {
	if (Wielded == 1)
	  {
	    write("You thrust your " + short() + " into the ground and " +
		  "kneel down before it.\n");
	    say(QCTNAME(this_player()) + " thrusts " + 
		this_player()->query_possessive() + " " + short() + " into " +
		"the ground and kneels down before it.\n");
	    return 1;
	  }
	else
	  {
	    write("You lay down your sword and kneel before it.\n");
	    say(QCTNAME(this_player()) + " lays " +
		this_player()->query_possessive() + " " + short() + " down " +
		"and kneels before it.\n");
	    return 1;
	  }
      }

    else
        write("Pray what?\n");

    return 1;
}

int
swinging()
{
    write("You swing the sword round in circular motions.\n");
    say(this_player()->query_The_name(this_player()) + " swings " +
	this_player()->query_possessive() + " twin-bladed blackened " +
	"broadsword round in circular motions.\n");
    return 1;
}

mixed
unwield(object wep)
{
    object tp = this_object()->query_wielded();

    if (!living(tp))
	return 0;

    write("As you unwield your sword you think of the sad souls trapped " +
	  "in the path of Erech.\n");

    say(QCTNAME(this_player()) + " gets a sad look on " +
	this_player()->query_possessive() + " face as " + 
	this_player()->query_pronoun() + " unwields the twin-bladed " +
	"blackened broadsword.\n");
  
    return 1;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    frighten(aid, hdesc, phurt, enemy, dt, phit, dam);
    hurt_extra(aid, hdesc, phurt, enemy, dt, phit, dam);

    return 0;
}


