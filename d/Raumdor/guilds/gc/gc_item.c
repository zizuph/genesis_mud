/*
 * Generic guild item.
 * To be worn by Gentlemans club members
 * Invented by Damaris 10/2001
 * Created by Valen, 10/2001
 * Updated by Valen, 20020203, different implementation of move messages
 */

#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Raumdor/defs.h"
#include "guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

#define GC_M_IN  "arrives gallantly"
#define GC_M_OUT "leaves gallantly"

string old_m_in, old_m_out;


#define ITEM_HAT	0
#define ITEM_SCARF	1

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
({
    "black top hat", 	/* short desc */
    "hat",		/* name */
    ({"top", "high", "black"}), /* adj */
  
    /* long */
    "This is a fine gentleman's top hat. It is made from "+
    "fine silk, which has been dyed black. It has a narrow brim and "+
    "has a tall cylindrical crown. It has also been known as a high "+
    "hat. This hat is special as it has a special 'label' on the inside.\n",

    A_HEAD, 400, 1200, 100 /* slots, weight, volume, value */

}),({
    "long elegant scarf",
    "scarf",
    ({"long", "elegant", "white"}),
  
    "This is a fine gentleman's scarf. It is made from the "+
    "finest silk available in Raumdor. It has been specially woven by "+
    "special weavers just for the fine gentlemen of the Gentleman's "+
    "club. It's fine threads have carefully been dyed a soft creamy "+
    "white. It is silky smooth, full in length and a special label "+
    "has been woven underneath.\n",
    
    A_NECK, 400, 1200, 100,
})
});

string
labeldesc()
{
    return "This " + short() + " belongs to " +
          capitalize(this_player()->query_real_name()) +
          ", distinguished member of the Gentlemans " +
          "club. A member may use <gchelp> for assistance.\n";
}

void
create_object()
{
    set_short("gentleman's generic item");

    set_name(OBJECT_ID);

    set_long("This is a gentleman's club guild item.\n");

    add_item(({"label", "special label"}), labeldesc);

    set_wf(this_object());

    set_looseness(4);

    set_layers(5);

    add_prop(OBJ_S_WIZINFO, "Gentlemans club item.\n");

    add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
      "do that.\n");

    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
      "for you to simply give it away.\n");

    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");

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

    write("You put on your " + short() + " and tip it charmingly.\n");

    say(QCTNAME(TP) + " puts on "+ HIS(TP) +" " + short() + " and "+
        "tips it charmingly.\n");

    break;

    case ITEM_SCARF:

    write("You put your " + short() + " around your neck and adjust " +
          "it charmingly.\n");

    say(QCTNAME(TP) + " puts "+ HIS(TP) +" " + short() + " around "+
        HIS(TP) +" neck and adjusts it charmingly.\n");

    break;

    default:

    write("You wear not-configured item.\n");
    }

/*
    setuid();seteuid(getuid());
    clone_object(GC_SHADOW)->add_gc_shadow(E(TO));
*/

/*
    I know this way of changing move messages is somewhat dirty, but
    I do not see any better and/or more general solution. Valen.
*/

    old_m_in = this_player()->query_m_in();
    old_m_out = this_player()->query_m_out();

    if(old_m_in == GC_M_IN)
    {
        old_m_in = F_ALIVE_MSGIN;
    }

    if(old_m_out == GC_M_OUT)
    {
        old_m_out = F_ALIVE_MSGOUT;
    }

    this_player()->set_m_in(GC_M_IN);
    this_player()->set_m_out(GC_M_OUT);

    return 1;
}

int
remove()
{
    switch(item_type)
    {
    case ITEM_HAT:

    write("You remove your " + short() + " and flash a charming smile.\n");

    say(QCTNAME(TP) + " removes "+ HIS(TP) +" " + short() + " and flashes "+
        "a charming smile.\n");

    break;

    case ITEM_SCARF:

    write("You remove your " + short() + " and flash a charming smile.\n");

    say(QCTNAME(TP) + " removes "+ HIS(TP) +" " + short() + " and flashes " +
        "a charming smile.\n");
    
    break;

    default:
    
    write("You remove not-configured item.\n");
    }
    
/*
    E(TO)->remove_gc_shadow();
*/

    this_player()->set_m_in(old_m_in);
    this_player()->set_m_out(old_m_out);

    return 1;
}

void
remove_object()
{
    E(TO)->remove_gc_shadow();
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
adjust_gc(string str)
{
    if(item_type == ITEM_HAT &&
       ((str == "black hat") || (str == "top hat") || (str == "hat") ||
        (str == "high hat")))
    {
        if (!query_worn())
            return notify_fail("Try wearing it first.\n");

	write("You adjust your " + short() + " while flashing a "+
	"charming grin as your fingertips slowly caress the brim.\n");

	say(QCTNAME(TP)+" adjusts "+ HIS(TP) +" " + short() + " "+
	"while flashing a charming grin as "+ HIS(TP) +" fingertips "+
	"slowly caresses the brim.\n");

	return 1;
    }
    else if(item_type == ITEM_SCARF &&
        ((str == "scarf") || (str == "elegant scarf") || (str == " long scarf") ||
        (str == "white scarf")))
    {
        if (!query_worn())
            return notify_fail("Try wearing it first.\n");

	write("You charmingly adjust your " + short() +
	" so it fits more smoothly around your neck.\n");

	say(QCTNAME(TP)+" charmingly adjusts "+ HIS(TP) +" " + short() + " "+
	"so it fits more smoothly around "+ HIS(TP) +" neck.\n");

	return 1;
    }
    return notify_fail("Adjust what?\n");
}

int
flip_hat(string str)
{
    if (item_type != ITEM_HAT) return 0;

    if((str == "black hat") || (str == "top hat") || (str == "hat") ||
      (str == "high hat"))
    {
        if (!query_worn())
    	    return notify_fail("Try wearing it first.\n");

	write("You charmingly tip your " + short() + " forward then flip it "+
	"in your fingertips then back on top your head.\n");

	say(QCTNAME(TP)+" charmingly tips "+ HIS(TP) +" " + short() + " "+
	"forward then flips it in "+ HIS(TP) +" fingertips then places "+
	"it back on "+HIS(TP)+" head.\n");

	return 1;
    }

    return notify_fail("Flip what?\n");
}

int
push_hat(string str)
{
    if (item_type != ITEM_HAT) return 0;

    if((str == "black hat") || (str == "top hat") || (str == "hat") ||
      (str == "high hat"))
    {
        if (!query_worn())
    	    return notify_fail("Try wearing it first.\n");

	write("You push the brim of your " + short() + " slightly back "+
	"off your forehead for a moment.\n");

	say(QCTNAME(TP)+" pushes the brim of "+ HIS(TP) +" " + short() + " "+
	"off of "+HIS(TP)+" forehead for a moment.\n");

	return 1;
    }
    return notify_fail("Push what?\n");
}

int
secure_hat(string str)
{
    if (item_type != ITEM_HAT) return 0;

    if((str == "black hat") || (str == "top hat") || (str == "hat") ||
       (str == "high hat"))
    {
        if (!query_worn())
            return notify_fail("Try wearing it first.\n");

	write("You place your hand on top of your " + short() + " to "+
	"keep it securely in place against a gust of wind.\n");

	say(QCTNAME(TP)+" places "+ HIS(TP) +" hand on top of "+ HIS(TP) +" "+
            short() + " "+ "and holds it securely " +
	"in place against a gust of wind.\n");
	return 1;
    }
    return notify_fail("Secure what?\n");
}

int
tip_hat(string str)
{
    if (item_type != ITEM_HAT) return 0;

    if((str == "black hat") || (str == "top hat") || (str == "hat") ||
       (str == "high hat"))
    {
        if (!query_worn())
            return notify_fail("Try wearing it first.\n");

	write("You tip your " + short() + " slightly in acknowledgement.\n");

	say(QCTNAME(TP)+" tips "+ HIS(TP) +" " + short() + " "+
            "slightly in acknowledgement.\n");

	return 1;
    }
    return notify_fail("Tip what?\n");
}

int
toss_gc(string str)
{
    if(item_type == ITEM_HAT &&
      ((str == "black hat") || (str == "top hat") || (str == "hat") ||
       (str == "high hat")))
    {
	write("With the skill of a gentleman you take your "+ short() +
	      " and toss it up in the air to quickly catch it again.\n");

	say(QCTNAME(TP)+" tosses "+ HIS(TP) +" "+ short() +" high up in "+
	"the air only to catch it with the deft skill of a gentleman.\n");

	return 1;
    }

    if(item_type == ITEM_SCARF &&
      ((str == "scarf") || (str == "elegant scarf") || (str == " white scarf") ||
       (str == "long scarf")))
    {
	write("You gallantly toss your " + short() +" over your shoulder.\n");
	say(QCTNAME(TP)+" gallantly tosses " + HIS(TP) + " " +short() +
	    " over " + HIS(TP) + " shoulder.\n");
	return 1;
    }

    return notify_fail("Toss what?\n");
}

int
gc_item(string str)
{
    if(file_name(E(TP)) != JOINROOM) return 0;

    if(query_worn()) return notify_fail("Remove the item first, please.\n");

    switch(str)
    {

    case "hat":
    item_type = ITEM_HAT; configure_item(); break;

    case "scarf":
    item_type = ITEM_SCARF; configure_item(); break;

    default:
    return notify_fail("Gcitem <hat> / <scarf> ?\n");
    }
    
    write("You were given new guild item.\n");

    say(QCTNAME(TP) + " gallantly asked for a new gentleman's item " +
        "to wear, and was promptly given one.\n");
    return 1;
}

int
read_label(string str)
{
    if((str == "label") || (str == "special label"))
    {
        write("You read the label carefully:\n"+
            "This "+ short() +" belongs to a member of the Gentlemans club.\n"+
            "A member may use <gchelp> for assistance.\n");
        return 1;
    }
    
    return notify_fail("Read what?\n");
}

void
verify_validity()
{
  /* Verify gender. */
  if (environment()->query_gender() != G_MALE)
  {
    tell_object(environment(), "Gentlemen's club do not accept females.\n"+
    "Membership has been revoked!\n");
    remove_object();
    return;
  }

  /* Verify race, whatever. */
  if (environment()->query_race() == "goblin")
  {
    tell_object(environment(), "Gentlemen's club do not accept goblins.\n"+
    "Membership has been revoked!\n");
    remove_object();
    return;
  }

  /* Verify if player is not Mummer of Sybarus. */
  if (environment()->query_prop("_live_i_am_mummer"))
  {
    tell_object(environment(), "Gentlemen's club do not accept mummers.\n"+
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

    add_action(adjust_gc, "adjust");
    add_action(flip_hat, "flip");
    add_action(push_hat, "push");
    add_action(secure_hat, "secure");
    add_action(tip_hat, "tip");
    add_action(toss_gc, "toss");

    add_action(read_label, "read");
    add_action(gc_item, "gcitem");
}
