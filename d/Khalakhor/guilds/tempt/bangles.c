/**********************************************************************
 * - bangles.c                                                      - *
 * - Club item for temptresses. The bangles are configirable and    - *
 * - worn on both wrists.  Based on Gentlemans club item.           - *
 * - Created by Damaris@Genesis 03/2005                             - *
 **********************************************************************/
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/basic.h";

#define BANGLES_JADE    0
#define BANGLES_GOLD	1
#define BANGLES_SILVER	2
#define BANGLES_IVORY   3
#define BANGLES_ONYX    4

int item_type = BANGLES_JADE;

#define ITC		item_config[item_type]

#define ITC_SHORT	0
#define ITC_NAME	1
#define ITC_ADJ		2
#define ITC_LONG	3
#define ITC_SLOT	4
#define	ITC_WEIGHT	5
#define ITC_VOLUME	6
#define ITC_VALUE	7

void configure_item(void);

mixed *item_config = ({
	({ "pair of jade bangles", 	     /* short desc */
	   "bangles",		             /* name */
	({"pair", "jade", "bangles"}),       /* adj */
	/* long */
	"This pair of jade bangles is a rigid set of twelve very thin "+
	"bracelets each that is made from precious jade that can "+
	"only be found in the Otherworld. Hanging from the first "+
	"bangle is an ornament of a grape leaf.\n",
	A_WRISTS, 400, 1200, 100 /* slots, weight, volume, value */
	}),
	({ "pair of gold bangles", 	     /* short desc */
	   "bangles",		             /* name */
	({"pair", "gold", "bangles"}),       /* adj */
	/* long */
	"This pair of gold bangles is a rigid set of twelve very thin "+
	"bracelets each that is made from deep yellow gold that can "+
	"only be found in the Otherworld. Hanging from the first bangle "+
	"is an ornament of a grape vine.\n",
	A_WRISTS, 400, 1200, 100 /* slots, weight, volume, value */
	}),
	({ "pair of silver bangles",         /* short desc */
	   "bangles",                        /* name */
	({"pair", "silver", "bangles"}),     /* adj */
	"This pair of silver bangles is a rigid set of twelve very thin "+
	"bracelets each that is made from sterling silver that can only "+
	"be found in the Otherworld. Hanging from the first bangle is an "+
	"ornament of a succulent grape.\n",
	A_WRISTS, 400, 1200, 100,
	}),
	({ "pair of ivory bangles", 	     /* short desc */
	   "bangles",		             /* name */
	({"pair", "ivory", "bangles"}),      /* adj */
	/* long */
	"This pair of ivory bangles is a rigid set of twelve very thin "+
	"bracelets each that is made from stunning ivory that can only "+
	"be found in the Otherworld. Hanging from the first bangle is "+
	"an ornament of a slender grape leaf.\n",
	A_WRISTS, 400, 1200, 100 /* slots, weight, volume, value */
	}),
	({ "pair of onyx bangles", 	     /* short desc */
	   "bangles",		             /* name */
	({"pair", "onyx", "bangles"}),      /* adj */
	/* long */
	"This pair of onyx bangles is a rigid set of twelve very thin "+
	"bracelets each that is made from stunning onyx that can only "+
	"be found in the Otherworld. Hanging from the first bangle is "+
	"an ornament of a thin grape leaf.\n",
	A_WRISTS, 400, 1200, 100 /* slots, weight, volume, value */
	}),
});

string
ornament()
{
	return "This precious ornament is engraved with strange "+
	"symbols that denotes that this " + short() + " belongs to " +
	capitalize(this_player()->query_real_name()) +
	", sensuous temptress. A temptress may use <tchelp> "+
	"for assistance.\n";
}

void
create_object()
{
	set_short("temptress generic item");
	set_name(OBJECT_ID);
	set_long("This is a temptress item.\n");
	add_item(({"precious ornament", "ornament"}), ornament);
	set_wf(this_object());
	set_looseness(0);
	set_layers(10);
	add_prop(OBJ_S_WIZINFO, "Temptress club item.\n");
	add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
	"do that.\n");
	add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
	"for you to simply give it away.\n");
	add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it "+
	"uninteresting.\n");
	add_prop(OBJ_M_NO_STEAL, 1);
	if(item_type >= 0) configure_item();
}

void
configure_item(void)
{
	set_short(ITC[ITC_SHORT]);
	remove_name(query_name());
	set_name(ITC[ITC_NAME]);
	add_name(OBJECT_ID);
	remove_adj(query_adj());
	set_adj(ITC[ITC_ADJ]);
	set_long(ITC[ITC_LONG]);
	set_slots(ITC[ITC_SLOT]);
	add_prop(OBJ_I_WEIGHT, ITC[ITC_WEIGHT]);
	add_prop(OBJ_I_VOLUME, ITC[ITC_VOLUME]);
	add_prop(OBJ_I_VALUE, ITC[ITC_VALUE]);
}

int
wear()
{
	{
		write("You sensually slip your " + short() + " on "+
		"your wrists while jingling them.\n");
		say(QCTNAME(TP) + " sensually slips "+ HIS(TP) +" "+
		"" + short() + " over her wrists while jingling them.\n");
	}
	setuid();seteuid(getuid());
	return 1;
}

int
remove()
{
	{
		write("You remove your " + short() + " sensuously "+
		"flashing a tempting smile.\n");
		say(QCTNAME(TP) + " removes "+ HIS(TP) +" "+
		"" + short() + " sensuously while flashing a "+
		"tempting smile.\n");
	}
	return 1;
}

void
leave_env(object from, object to)
{
	::leave_env(from, to);
	wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
	::appraise_object(num);
	appraise_wearable_item();
}

int
tc_item(string str)
{
	if(file_name(ENV(TP)) != ENTRANCE) return 0;
	if(query_worn())
	return notify_fail("Remove the item first, please.\n");
	switch(str)
	{
		case "gold":
		item_type = BANGLES_GOLD; configure_item();
		break;
		case "silver":
		item_type = BANGLES_SILVER; configure_item();
		break;
		case "jade":
		item_type = BANGLES_JADE; configure_item();
		break;
		case "ivory":
		item_type = BANGLES_IVORY; configure_item();
		break;		
		case "onyx":
		item_type = BANGLES_ONYX; configure_item();
		break;
		default:
		return notify_fail("bangles <jade> / <gold> / "+
		"<silver> / <ivory> / <onyx> ?\n");
	}
	write("You were given new tempting set of bangles.\n");
	say(QCTNAME(TP) + " quietly asked for a new set of bangles "+
	"to wear, and was promptly given some.\n");
	return 1;
}

int
read_ornament(string str)
{
	if((str == "ornament") || (str == "precious ornament"))
	{
		write("You read the symbols along the ornament "+
		"carefully. The symbols denote that this "+
		"" + short() + " belongs to "+
		"" + capitalize(this_player()->query_real_name()) + ", "+
		"sensuous temptress. "+
		"A temptress may use <tchelp> for assistance.\n");
		return 1;
	}
	return notify_fail("Read what?\n");
}

int
jingle_bangles(string str)
{

	if((str == "bangles"))
       {
	       if (!query_worn())
	       return notify_fail("They work better if worn.\n");
	       
	       write("You gracefully jingle your " + short() + " to "+
	       "attract attention.\n");
	       say(QCTNAME(TP)+" gracefully jingles "+ HIS(TP) +" "+
	       "" + short() + " to attract attention.\n");
	       return 1;
	}
	return notify_fail("Jingle what?\n");
}

void
verify_validity()
{
	/* Verify gender. */
	if (environment()->query_gender() != G_FEMALE)
	{
		tell_object(environment(), "The Temptress do not "+
		"accept males.\n"+
		"Membership has been revoked!\n");
		remove_object();
		return;
	}
	/* Verify race, whatever. */
	if (environment()->query_race() == "goblin")
	{
		tell_object(environment(), "Temptress do not "+
		"accept goblins.\n"+
		"Membership has been revoked!\n");
		remove_object();
		return;
	}
	/* Verify race, whatever. */
	if (environment()->query_race_name() == "orc")
	{
		tell_object(environment(), "Temptress do not "+
		"accept Orcs.\n"+
		"Membership has been revoked!\n");
		remove_object();
		return;
	}
	/* Verify race, whatever. */
	if (environment()->query_race_name() == "minotaur")
	{
		tell_object(environment(), "Temptress do not "+
		"accept Minotaurs.\n"+
		"Membership has been revoked!\n");
		remove_object();
		return;
	}
	environment()->add_cmdsoul(SOUL);
	environment()->update_hooks();
}

public string 
query_auto_load()
{
	return MASTER + ":#it#" + item_type + "#";
}

void
init_arg(string str)
{
	string foobar;
	sscanf(str, "%s#it#%d#", foobar, item_type);
	if(item_type >= 0) configure_item();
	set_alarm(10.0, 0.0, verify_validity);
}

void
init()
{
	::init();
	add_action(read_ornament,    "read");
	add_action(tc_item,       "bangles");
	add_action(jingle_bangles, "jingle");

}
