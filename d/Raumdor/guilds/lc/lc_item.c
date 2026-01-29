/*********************************************************************
 * - lc_item.c                                                     - *
 * - A club token                                                  - *
 * - Taken from the gc_item from Gentlemans club                   - *
 * - Created by Damaris@Genesis 5/2003                             - *
 * - Updates - Added comb as an item. Changed the remove descrtion.- *
 * - Updated by Damaris@Genesis 11/2005 / 06/2006                  - *
 * - Updated by Mirandus 2016/10/26 to fix shadowing problem       - *
 *********************************************************************/

#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Raumdor/defs.h";
#include "/d/Raumdor/guilds/lc/guild.h"
#include <wa_types.h>

#define ITEM_HAT	0
#define ITEM_GLOVES	1
#define ITEM_COMB       2

int item_type = ITEM_HAT;

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
	({ "pleated charmeuse hat", 	     /* short desc */
	   "hat",		             /* name */
	({"pleated", "charmeuse", "cream"}), /* adj */
	/* long */
	"This is a fine ladies hat. It is a small hat that denotes "+
	"style with a creamed coloured pleated charmeuse covered brim "+
	"and venise lace. It has a satin edged pouf that simply radiates "+
	"femininity. This hat is special as it has a special 'label' on "+
	"the inside.\n",
	A_HEAD, 400, 1200, 100 /* slots, weight, volume, value */
	}),
	({ "pair of long silk gloves",
	   "gloves",
	({"pair", "long", "silk", "gloves"}),
	"This is a fine pair of ladies gloves. It is made from the "+
	"finest silk available in Raumdor. It has been specially woven "+
	"by special weavers just for the fine ladies of the Ladies club. "+
	"Along the edge is infinity crystals with a matte satin touch. "+
	"It is so silky smooth with an over the elbow length and a "+
	"special label has been woven underneath.\n",
	A_HANDS, 400, 1200, 100,
	}),
	({ "pearl hair comb", 	/* short desc */
	   "comb",		/* name */
	({"pearl", "hair"}),    /* adj */
	/* long */
	"This stunning pearl hair comb is quite a treasure that simply "+
	"radiates femininity and elegance. It is made from platinum "+
	"that has been covered in perfect white pearls along the edge, "+
	"which is quite an embellishment that denotes style and grace. "+
	"This comb has a special 'label' on the inside.\n",
	A_HEAD, 400, 1200, 100 /* slots, weight, volume, value */
	}),
});

string
labeldesc()
{
	return "This " + short() + " belongs to " +
	capitalize(this_player()->query_real_name()) +
	", illustrious member of the Ladies " +
	"club. A member may use <lchelp> for assistance.\n";
}

void
create_object()
{
	set_short("ladies generic item");
	set_name(OBJECT_ID);
	set_long("This is a ladies club item.\n");
	add_item(({"label", "special label"}), labeldesc);
	set_wf(this_object());
	set_looseness(0);
	set_layers(10);
	add_prop(OBJ_S_WIZINFO, "Ladies club item.\n");
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
	switch(item_type)
	{
		case ITEM_HAT:
		write("You put on your " + short() + " and elegantly "+
		"adjust it.\n");
		say(QCTNAME(TP) + " puts on "+ HIS(TP) +" "+
		"" + short() + " and elegantly adjusts it.\n");
		break;
		
		case ITEM_GLOVES:
		write("You slide your " + short() + " onto your hands "+
		"and up your arms and adjust them elegantly as any "+
		"true lady would.\n");
		say(QCTNAME(TP) + " slides "+ HIS(TP) +" "+
		"" + short() + " onto "+ HIS(TP) +" hands then arms "+
		"while elegantly adjusting them as any true lady "+
		"would.\n");
		break;
		
		case ITEM_COMB:
		write("You slide your " + short() + " into the locks "+
		"of your hair in the stylish manner of a lady.\n");
		say(QCTNAME(TP) + " slides "+ HIS(TP) +" " + short() + " "+
		"into the locks of "+ HIS(TP) +" hair in a stylish "+
		"manner of a lady.\n");
		break;
		default:
		write("You wear not-configured item.\n");
	}
	setuid();seteuid(getuid());
	clone_object(LC_SHADOW)->shadow_me(TP);
	return 1;
}

int
remove()
{
	switch(item_type)
	{
		case ITEM_HAT:
		write("You elegantly remove your " + short() + ".\n");
		say(QCTNAME(TP) + " elegantly removes "+ HIS(TP) +" "+
		"" + short() + ".\n");
		break;
		
		case ITEM_GLOVES:
		write("You elegantly remove your " + short() + ".\n");
		say(QCTNAME(TP) + " elegantly removes "+ HIS(TP) +" "+
		"" + short() + ".\n");
		break;
		
		case ITEM_COMB:
		write("You elegantly remove your " + short() + " from "+
		"your hair.\n");
		say(QCTNAME(TP) + " elegantly removes "+ HIS(TP) +" "+
		"" + short() + " from "+ HIS(TP) +" hair.\n");
		break;
		default:
		write("You remove not-configured item.\n");
	}
	TP->remove_shadow(LC_SHADOW);
	return 1;
}

void
remove_object()
{
	TP->remove_shadow(LC_SHADOW);
	::remove_object();
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
adjust_lc(string str)
{
	if(item_type == ITEM_HAT &&
       ((str == "pleated hat") || (str == "charmeuse hat") || (str == "cream hat") || (str == "hat")))
       {
	       if (!query_worn())
	       return notify_fail("Try wearing it first.\n");
	       
	       write("You adjust your " + short() + " while flashing "+
	       "an illustrious grin as your fingertips slowly caress "+
	       "the pleated brim.\n");
	       say(QCTNAME(TP)+" adjusts "+ HIS(TP) +" " + short() + " "+
	       "while flashing an illustrious grin as "+ HIS(TP) +" "+
	       "fingertips slowly caresses the pleated brim.\n");
	       return 1;
	}
	else if(item_type == ITEM_GLOVES &&
        ((str == "gloves") || (str == "satin gloves") || (str == " gloves") ||
        (str == "cream gloves")))
        {
		if (!query_worn())
		return notify_fail("Try wearing it first.\n");
		
		write("You gracefully adjust your " + short() +	" so "+
		"it fits more smoothly up your arms.\n");
		say(QCTNAME(TP)+" gracefully adjusts "+ HIS(TP) +" "+
		"" + short() + " so it fits more smoothly up "+
		""+ HIS(TP) +" arms.\n");
		return 1;
	}
	else if(item_type == ITEM_COMB &&
        ((str == "comb") || (str == "hair comb") || (str == " pearl comb") ||
        (str == "platinum comb")))
        {
		if (!query_worn())
		return notify_fail("Try wearing it first.\n");
		
		write("You gracefully adjust your " + short() +	" so "+
		"it fits more snuggly in your hair.\n");
		say(QCTNAME(TP)+" gracefully adjusts "+ HIS(TP) +" "+
		"" + short() + " so it fits more snuggly in "+
		""+ HIS(TP) +" hair.\n");
		return 1;
	}
	return notify_fail("Adjust what?\n");
}

int
push_hat(string str)
{
	if (item_type != ITEM_HAT) return 0;
	if(item_type == ITEM_HAT &&
       ((str == "pleated hat") || (str == "charmeuse hat") || (str == "cream hat") || (str == "hat")))
       {
	       if (!query_worn())
	       return notify_fail("Try wearing it first.\n");
	       
	       write("You gracefully push the brim of your "+
	       "" + short() + " slightly back off your forehead "+
	       "for a moment.\n");
	       say(QCTNAME(TP)+" gracefully pushes the brim of "+
	       ""+ HIS(TP) +" " + short() + " off of "+HIS(TP)+" "+
	       "forehead for a moment.\n");
	       return 1;
	}
	return notify_fail("Push what?\n");
}

int
secure_hat(string str)
{
	if (item_type != ITEM_HAT) return 0;
	if(item_type == ITEM_HAT &&
       ((str == "pleated hat") || (str == "charmeuse hat") || (str == "cream hat") || (str == "hat")))
       {
	       if (!query_worn())
	       return notify_fail("Try wearing it first.\n");
	       write("You place your hand on top of your "+
	       "" + short() + " keep it securely in place against a "+
	       "gust of wind.\n");
	       say(QCTNAME(TP)+" places "+ HIS(TP) +" hand on top "+
	       "of "+ HIS(TP) +" " + short() + " and holds it securely "+
	       "in place against a gust of wind.\n");
	       return 1;
	}
	return notify_fail("Secure what?\n");
}

int
lc_item(string str)
{
	if(file_name(E(TP)) != JOINROOM) return 0;
	if(query_worn())
	return notify_fail("Remove the item first, please.\n");
	switch(str)
	{
		case "hat":
		item_type = ITEM_HAT; configure_item();
		break;
		case "gloves":
		item_type = ITEM_GLOVES; configure_item();
		break;
		case "comb":
		item_type = ITEM_COMB; configure_item();
		break;
		
		default:
		return notify_fail("Lcitem <hat> / <gloves> / <comb> ?\n");
	}
	write("You were given new club item.\n");
	say(QCTNAME(TP) + " quietly asked for a new ladies item "+
	"to wear, and was promptly given one.\n");
	return 1;
}

int
read_label(string str)
{
	if((str == "label") || (str == "special label"))
	{
		write("You read the label carefully:\n"+
		"This "+ short() +" belongs to a member of the "+
		"Ladies club.\n"+
		"A member may use <lchelp> for assistance.\n");
		return 1;
	}
	return notify_fail("Read what?\n");
}

void
verify_validity()
{
	/* Verify gender. */
	if (environment()->query_gender() != G_FEMALE)
	{
		tell_object(environment(), "The Ladies club do not "+
		"accept males.\n"+
		"Membership has been revoked!\n");
		remove_object();
		return;
	}
	/* Verify race, whatever. */
	if (environment()->query_race() == "goblin")
	{
		tell_object(environment(), "Ladies club do not "+
		"accept goblins.\n"+
		"Membership has been revoked!\n");
		remove_object();
		return;
	}
	/* Verify if player is not Dancer of the Veils. */
	if (environment()->query_prop("_live_i_am_dancer_of_veils"))
	{
		tell_object(environment(), "Ladies club do not "+
		"accept dancers.\n"+
		"Membership has been revoked!\n");
		remove_object();
		return;
	}
	environment()->add_cmdsoul(GUILD_SOUL);
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
	add_action(adjust_lc,  "adjust");
	add_action(push_hat,     "push");
	add_action(secure_hat, "secure");
	add_action(read_label,   "read");
	add_action(lc_item,    "lcitem");
}
