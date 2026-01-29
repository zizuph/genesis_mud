/*
 * gwaedhel-spear.c
 * By Skippern
 * June 20 (c) 00
 *
 * A unique artifact (one of its kind only). It is a part of a pear with
 *  a spear.
 * Spear yilds extra damage and gives panic in combat. The weapon have a
 *  set of emotions and specials that can be exlored.
 */
inherit "/std/weapon";

#include "../erech.h"
#include "../lib/gwaedhil.h"
#include <filter_funs.h>     /* For FILTER_LIVE(x) */
#include <formulas.h>        /*Contians formulas for weight, value etc. */
#include <macros.h>
#include <stdproperties.h>   /* OBJ_I_VALUE and similar properties */
#include <wa_types.h>        /* Contains weapon-related definitions */

inherit E_LIB + "gwaedhil.c";

#define HIT 18
#define PEN 40

/* Prototypes */
void                create_weapon();
int                 do_rest(string arg);
int                 resting();
int                 break_spear();

/*
 * Function name:    create_weapon()
 * Description  :    Creates the weapon.
 */
void
create_weapon()
{
    set_name("spear");
    set_adj("black");
    add_adj("magical");
    set_short("black magical spear");
    set_pshort("black magical spears");
    set_long("This " + short() + " is an old powerful artifact. When you " +
	"grip round it you feel some magical powers runs trough your " +
        "vains, and when you drow your finger accross the head it feels " +
	"like it is razor sharp. The dark colour seem to have been applied " +
	"long after the spear was forged, and it is as dark as if it " +
	"consumes light. The spear feels very well balanced, like it is a " +
	"perfect spear. There are some marks along the shaft and the head.\n");

    add_item(( { "head", "spear head"} ), "The large diamond shaped spear " +
	"head looks terrible sharp. The edges looks razor sharp and the " +
	"is sharp as the sharpest arrow heads. There are some lines of " +
	"marks on it.\n");
    add_item(("shaft"), "A long wooden shaft, made from some strong " +
	"wood. It feels good to wield this weapon. There are some marks " +
	"along it.\n");
    add_item(("marks"), "What marks did you want to examine? The marks on " +
	"on the head or along the shaft?\n");
    add_item(("words"), "What words did you want to examine? The words on " +
	"on the head or along the shaft?\n");
    add_item( ({ "marks on the shaft", "marks along the shaft",
                   "marks on shaft", "marks along shaft" }),
	      "It seems like a word with a small sign behind.\n");
    add_item(("sign"), "It is the personal sigel of a smithy in Tirith " +
	     "Aear.\n");
    add_item( ({ "marks on the head", "marks on the spear head",
                   "marks on head", "marks on spear head" }),
	      "It seems like lines of words running in arches on both " +
	      "sides of the spear head.\n");
    add_item( ({ "words on the head", "words on the spear head",
		   "words on head", "words on spear head", "words along shaft",
		   "words along the shaft", "words on shaft", 
		   "words on the shaft" }),
	"It looks like several letters in a row forming words, maybe you " +
	"should read them?\n");
    add_cmd_item( ({ "words on shaft", "words on the shaft",
                       "words along shaft", "words along the shaft" }),
		  "read", &quenya_name());
    add_cmd_item( ({ "words on head", "words on the spear head",
                       "words on the head", "words on spear head" }),
		  "read", &quenya_spear());
    add_cmd_item( ({ "words on shaft", "words along shaft",
                       "words on the shaft", "words along the shaft" }),
		  "translate", &translate_name());
    add_cmd_item( ({ "words on head", "words on the spear head",
                       "words on the head", "words on spear head" }),
		  "translate", &translate_spear());

    set_may_not_recover();

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_BLUDGEON | MAGIC_DT);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(250) + 1000 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM) +
	random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 15, "enchantment" }));
    add_prop(OBJ_I_RES_ACID, 10);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({ "This spear was forged by elven smiths in " +
				    "Tirith Aear.", 20,
				  "This spear was forged by elven smiths in " +
				    "Tirith Aear. It was given to Isildur " +
				    "long ago.", 40,
				  "This spear was forged by elven smiths in " +
				    "Tirith Aear. It was given to Isildur, " +
				    "who gave it to Morthec as a token of " +
				    "the Oath of Isildur.", 60 }));
    add_prop(OBJ_S_WIZINFO, "This weapon have extra damage and it frightens " +
        "the enemy. In rare cases it can backfire on the wielder. It was " +
        "forged in Tirith Aear by elven smiths long ago, and given " +
        "to Isildur. It is a part of a pair named the Gwaedhil (Oath " +
	"sister). The hit/pen is: " + HIT + "/" + PEN + ".");

    set_wf(this_object());

    do_dream();

}

mixed
wield(object wep)
{
    int Undead = this_player()->query_prop(LIVE_I_UNDEAD);

    if (this_player()->query_guild_name_race() == "Dunedain" )
        {
	    write("You wield your " + short() + " feeling confident that no " +
	        "undeads can hurt you.\n");

	    say(QCTNAME(this_player()) + " wields " +
	        this_player()->query_possessive() + " " + short() + " with " +
		"great confident on " + this_player()->query_possessive() +
		" face.\n");
	    
	    return 1;
	}

    if (Undead >= 1 )
    {
	write("As you grip the " + short() + ", you hear the whispering " +
	    "voice of Isildur in the distrance.\n");
	say(QCTNAME(this_player()) + " seems troubled as " +
	    this_player()->query_pronoun() + " hears something in the " +
	    "distance.\n");
	return 1;
    }

    write("You wield your " + short() + " feeling confident.\n");

    say(QCTNAME(this_player()) + " wields " +
	this_player()->query_possessive() + " " + short() + " with " +
	"confidence.\n");

    return 1;
}

mixed
unwield(object wep)
{
    object tp = this_object()->query_wielded();

    if (!living(tp))
	return 0;

    write("You let the spear rest from your hands.\n");

    say(QCTNAME(this_player()) + " lets the spear rest from " +
	this_player()->query_possessive() + " hands.\n");

    return 1;
}

void
init()
{
    ::init();
    add_action("do_rest", "rest");
}

int
do_rest(string arg)
{
  if (arg == "on spear")
    resting();
  else
    write("Rest where?\n");

  return 1;
}

int
resting()
{
    string race = this_player()->query_race();
    int    rsize,
           tsize,
           level = this_player()->query_average_stat() / 10;

    if (race == "human" || race == "goblin" || race == "elf")
        rsize = 5;
    else if (race == "hobbit" || race == "dwarf" || race == "gnome")
        rsize = 2;
    else
        rsize = 3;

    tsize = rsize + level;

    switch(tsize)
    {
      case 0..5:
	// too small to get any rest from this.
	write("You are not strong enough to rest against the spear.\n");
	say(this_player()->query_The_name(this_player()) + " tries to " +
	    "lean against " + this_player()->query_possessive() + " spear, " +
	    "but cannot find the balance.\n");
	break;
      case 6..10:
	// result of small people resting.
	write("You rest your tired body against the erected spear.\n");
	say(this_player()->query_The_name(this_player()) + " rests " +
	    this_player()->query_possessive() + " tired body against the " +
	    "erected spear.\n");
	break;
      case 11..15:
	// result for medium players.
	write("You rest your body heavily on the spear.\n");
	say(this_player()->query_The_name(this_player()) + " rests " +
	    this_player()->query_possessive() + " body heavily on " +
	    this_player()->query_possessive() + " spear.\n");
	break;
      case 16..20:
	// result for large players.
	write("You rest your body heavily on the spear.\n");
	say(this_player()->query_The_name(this_player()) + " rests " +
	    this_player()->query_possessive() + " body heavily on " +
	    this_player()->query_possessive() + " spear. The spear sways " +
	    "under the weight of " + this_player()->query_possessive() +
	    " body.\n");
	break; 
      default:
	// OH SHIT!
	write("You rest your body heavily on the spear.\n");
	say(this_player()->query_The_name(this_player()) + " rests " +
            this_player()->query_possessive() + " body heavily on " +
            this_player()->query_possessive() + " spear. The spear sways " +
            "under the weight of " + this_player()->query_possessive() +
            " body.\n");
	break_spear();
	break;
    }
    return 1;
}

int
break_spear()
{
    int       dam, i, j;
    object    watchers;
    object    *present;

    string    jalla;

    present = FILTER_LIVE(all_inventory(environment(environment(this_object()))));

    dam = EXPLODING_SPEAR;
    write("Oh no!\n");
    add_prop(OBJ_I_BROKEN, 1);
    write("The black magical spear explodes!\n");
    say(this_player()->query_The_name(this_player()) + "'s spear explodes " +
	"in a huge flash of blue light.\n");

    this_player()->heal_hp(-dam*3);

    for (i = 0, j = sizeof(present) ; i < j ; i++)
    {
       	watchers = present[i];
	watchers->heal_hp(-dam);
	watchers->catch_tell("You are struck by some peaces from the " +
			     "spear.\n");
    }
    return 1;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    frighten(aid, hdesc, phurt, enemy, dt, phit, dam);
    hurt_extra(aid, hdesc, phurt, enemy, dt, phit, dam);

    return 0;
}
