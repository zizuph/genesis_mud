/*
 * /d/Gondor/common/jewelry/regalia.c
 *
 * This is the regalia given to the members of founded orders, for
 * a hefty price of course. A Knight Grand Cross, the highest rank
 * of an order, receives a collar (250 plats with 10 stones optionally 
 * mounted).  A Knight Commander, the second highest rank, receives a 
 * collar (150 plats with 5 stones optionally mounted). The lowest rank,
 * a Member receives a medal (50 plats).
 *
 * Brainchild of Auberon
 * Coded by Gwyneth, 08/02
 *
 * Modification log:
 * Gwyneth 1/7/04: Added log tracking in /d/Gondor/log/regalia to help
 * aid in restorations due to bugs. This is a temporary measure until
 * I can come up with a real tracking system to automate the restoration.
 */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include "jewelry.h"

#define KGC_RANK 2
#define KC_RANK 1
#define MEMBER_RANK 0

string gOrder,
       gEmblem,
       gOwner,
       gColour,
       gGem1 = "n",
       gGem2 = "n",
       gSubloc = "";
int gNum1 = 0,
    gNum2 = 0, 
    gRank = MEMBER_RANK;

public void create_object();
public void set_order(string order);
public void set_emblem(string str);
public void set_owner(string str);
public void set_colour(string colour);
public varargs void set_gems(string gem1 = "n", int num1 = 0, string gem2 = "n", int num2 = 0);
public void set_order_rank(int rank);
public void init_regalia();
public string gem_desc();
public int wear(object ob);
public int remove(object ob);
public mixed query_auto_load();
public mixed query_recover();
public void init_arg(string arg);
public void leave_env(object from, object to);
public void appraise_object(int num);

public void
create_object()
{
    set_name("regalia");
    set_wf(this_object());
    set_adj("gold");
    set_keep(1);
    setuid();
    seteuid(getuid());
    set_alarm(1.0, 0.0, &init_regalia());
}

public void
set_order(string order)
{
    gOrder = order;
}

public void
set_emblem(string emblem)
{
    gEmblem = emblem;
}

public void
set_owner(string name)
{
    gOwner = capitalize(name);
}

public void
set_colour(string colour)
{
    gColour = colour;
}

public varargs void
set_gems(string gem1 = "n", int num1 = 0, string gem2 = "n", int num2 = 0)
{
    gGem1 = gem1;
    gNum1 = num1;
    gGem2 = gem2;
    gNum2 = num2;
}

public void
set_order_rank(int rank)
{
    gRank = rank;
}

public void
banish_msg()
{
    environment()->catch_tell("\n\nThe name of " +
        gOrder + " has been banished! Your regalia crumbles into pieces " +
        "and disappears. If you believe this to be a mistake, you may " +
        "mail the wizards of Gondor ('mail gondor' in any post " +
        "office).\n\n");
}

public void
init_regalia()
{
    object chivalry;

    (JEWELRY_DIR + "chivalry")->teleledningsanka();
    chivalry = find_object(JEWELRY_DIR + "chivalry");
    if (chivalry->query_forbidden(gOrder))
    {
        set_alarm(1.0, 0.0, &banish_msg());
        set_alarm(1.0, 0.0, &remove_object());
        return;
    }

    if (gGem1 != "n")
        add_adj(gGem1);

    if (gGem2 != "n")
        add_adj(gGem2);

    switch(gRank)
    {
    case KGC_RANK:
        config_wearable_item(A_NECK, 1, 5, this_object());
        set_name("collar");
        if (!strlen(gem_desc()))
            set_short("gold collar of a Knight Grand Cross");
        else if (gGem2 != "n")
            set_short("gemstone-encrusted collar of a Knight Grand Cross");
        else
            set_short(gGem1 + "-encrusted collar of a Knight Grand Cross");

        set_long("This elegant and substantial golden collar is as " +
            "finely crafted a piece of jewelry as you could ever imagine.  " +
            "Links over an inch wide depict symbols from the history of " +
            "the Order of " + gOrder + ", and every elaborate link is " +
            "embellished with richly-coloured enamelwork.  Hanging from " +
            "the bottom of the chain is a large pendant of gold" +
            (strlen(gem_desc()) ? " encrusted with " + gem_desc() : "") + 
            ", in the form of " + gEmblem + ".  On the back of one " +
            "link is engraved the name \"" + gOwner +"\".\n");
        add_prop(OBJ_I_WEIGHT, 1000);
        add_prop(OBJ_I_VOLUME, 500);
        add_prop(OBJ_I_VALUE, 216000);
        break;
    case KC_RANK:
        config_wearable_item(A_NECK, 1, 5, this_object());
        set_name("collar");
        if (!strlen(gem_desc()))
            set_short("gold collar of a Knight Commander");
        else if (gGem2 != "n")
            set_short("gemstone-studded collar of a Knight Commander");
        else
            set_short(gGem1 + "-studded collar of a Knight Commander");
        
        set_long("A massive pendant of pure gold in the shape of " +
        gEmblem + 
        (strlen(gem_desc()) ? ", encrusted with " + gem_desc() + "," : "") +
        " is suspended from a wide " +
        "ribbon of " + gColour + " watered silk.  The pendant is " +
        "beautifully textured and detailed, with richly-hued enamels " +
        "causing it to practically glow in any but the dimmest light.  You " +
        "recognize this as the insignia of a Knight Commander of the " +
        "Order of " + gOrder + ".  On the back of the pendant is engraved " +
        "the name of the owner, \"" + gOwner + "\".\n");
        add_prop(OBJ_I_WEIGHT, 75);
        add_prop(OBJ_I_VOLUME, 75);
        add_prop(OBJ_I_VALUE, 129600);
        break;
    case MEMBER_RANK:
        config_wearable_item(A_CHEST, 1, 5, this_object());
        set_name("badge");
        set_short("gold badge");
        set_long("This is a large badge of solid gold, depicting " +
            gEmblem + ".  The gold has been worked in extremely fine " +
            "detail, and richly coloured enamels give the gold a vibrant " +
            "sheen.  A pin on the back allows for it to be worn on the " +
            "breast, and near the pin is engraved the name \"" + 
            gOwner + "\".\n");
        add_prop(OBJ_I_WEIGHT, 45);
        add_prop(OBJ_I_VOLUME, 45);
        add_prop(OBJ_I_VALUE, 43200);
        break;
    default:
        break;
    }
}

/* Function name: gem_desc
 * Description  : Gives a description for the number of gems
 * Returns      : A string along the lines of: "one ruby and 4 diamonds"
 */
public string
gem_desc()
{
    string desc;

    if (!gNum1)
        return "";

    if (gNum1 == 1)
        desc = "one " + gGem1;
    else
        desc = LANG_NUM2WORD(gNum1) + " " + LANG_PWORD(gGem1);

    if (!gNum2)
        return desc;

    if (gNum2 == 1)
        desc += " and one " + gGem2;
    else
        desc += " and " + LANG_NUM2WORD(gNum2) + " " + LANG_PWORD(gGem2);

    return desc;
}

public int
wear(object ob)
{
    object subloc_grp;

    if (ob != this_object())
        return -1;

    if (gOwner != capitalize(this_player()->query_real_name()))
        return "You are unable to wear the " + short() + ".\n";

    subloc_grp = present(ORDER_SUBLOC_GROUP, this_player());

    if (!objectp(subloc_grp))
    {

        subloc_grp = clone_object(JEWELRY_DIR + "regalia_obj");
        subloc_grp->move(this_player());
    }

    add_prop(OBJ_M_NO_DROP, "You must remove it before you can drop it.\n");
    add_prop(OBJ_M_NO_GIVE, "You must remove it first.\n");
    subloc_grp->add_to_subloc("the Order of " + gOrder, gRank);
    return 0;
}

public int
remove(object ob)
{
    object subloc_grp;

    if (ob != this_object())
        return -1;

    subloc_grp = present(ORDER_SUBLOC_GROUP, this_player());

    if (!objectp(subloc_grp))
    {
        subloc_grp = clone_object(JEWELRY_DIR + "regalia_obj");
        subloc_grp->move(this_player());
    }

    remove_prop(OBJ_I_NO_DROP);
    remove_prop(OBJ_I_NO_GIVE);
    subloc_grp->remove_from_subloc("the Order of " + gOrder, gRank);
    return 0;
}

/* Function name: query_auto_load
 * Description  : Return the filename of the object and saved variables.
 * Returns      : See description.
 */
public mixed
query_auto_load()
{
    return (MASTER + ":" + gOrder + "#" + gEmblem + "#" + gOwner + "#" +
               gColour + "#" + gGem1 + "#" + gNum1 + "#" + gGem2 + "#" + 
               gNum2 + "#" + gRank);
}

/* Function name: query_recover
 * Description  : Don't make it recover and autoload.
 * Returns      : 0 always
 */
public mixed
query_recover()
{
    return 0;
}

/* Function name: init_arg
 * Description  : Called when autoloading to set the different variables.
 *                Also calls init_jewelry
 * Arguments    : string arg - the auto-load argument
 */
public void
init_arg(string arg)
{
    string *arglist = explode(arg, "#");
    set_order(arglist[0]);
    set_emblem(arglist[1]);
    set_owner(arglist[2]);
    set_colour(arglist[3]);
    set_gems(arglist[4], atoi(arglist[5]), arglist[6], atoi(arglist[7]));
    set_order_rank(atoi(arglist[8]));

    init_regalia();
    set_alarm(1.5, 0.0, wear_me);
}

/* Function name: leave_env
 * Description  : Must be called in wearable_item to make sure we remove
 *                it before it leaves the inventory.
 */
public void
leave_env(object from, object to)
{
    string msg, name;

    ::leave_env(from, to);

    wearable_item_leave_env(from, to);

    if (!objectp(to) || !objectp(from) || !interactive(from))
        return;

    if (to->id("rich_club_obj"))
        return;

    setuid();
    seteuid(getuid());

    msg = capitalize(from->query_real_name());
    name = capitalize(to->query_real_name());

    if (!living(to))
    {
        msg += " dropped " + short() + " in " + file_name(to);
    }
    else if (interactive(to))
    {
        msg += " gave " + short() + " to " + name;
    }
    else
    {
        msg += " gave " + short() + " to " + name + " ("+
            file_name(to) + ")";
    }

    msg += ". " + ctime(time()) + ".\n";
    log_file("regalia", msg);
}

/* Function name: enter_env
 * Description  : Logs movement of item.
 * Arguments    : object to - where the item is going
 *                object from - where it came from
 */
public void
enter_env(object to, object from)
{
    string msg, name;

    ::enter_env(to, from);

    if (!objectp(from) || !objectp(to) || !interactive(to))
        return;

    if (from->id("rich_club_obj"))
        return;

    setuid();
    seteuid( getuid() );

    msg = capitalize(to->query_real_name());
    name = capitalize(from->query_real_name());

    if (!living(from))
    {
        msg += " picked up " + short() + " from " + file_name(from);
    }
    else if (interactive(from))
    {
        msg += " got " + short() + " from " + name;
    }
    else
    {
        msg += " got " + short() + " from " + name + " (" +
            file_name(from) + ")";
    }

    msg += ". "+ ctime(time())+ ".\n";
    log_file("regalia", msg);

}

/* Function name: appraise_object
 * Description  : Must be called in wearable_item to give the right
 *                appraisal.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
