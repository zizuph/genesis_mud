/* A locket. By Cirion. */
/* 07/26/97 Lilith: added keepability;             
 *          remove_name("armour"); doesn't work :(
 *
 * * Lucius May 2009: Recoded the lockets to not be armours.
 * 		Lots of additional cleanups.
 *
 */
#pragma strict_types

#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/basic.h"

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/commands";
inherit "/lib/keep";

#define LOCKET_ID          "_Avenir_config_locket_id"
#define SOULDESC(x)       (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))


private int open, initialized;
private string image, who, engraving, metal = "tin";

private void
init_locket(void)
{
    if (initialized++)
	return;
    
    if (strlen(metal))
       add_adj(metal);

    if (strlen(engraving))
    {
	add_adj("engraved");
	add_item("engraving", VBFC_ME("engraving_desc"));
	add_cmd_item(({ "locket", "engraving" }), "read",
	    VBFC_ME("engraving_words") + "\n");
    }
}

public void
create_object(void)
{
    set_name("locket");
    add_name(LOCKET_ID);
    set_short(VBFC_ME("locket_short"));
    set_long(VBFC_ME("locket_long"));

    set_keep(1);
    config_wearable_item(A_NECK, 1, 10, 0);

    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 200);

    set_alarm(1.0, 0.0, init_locket);
}

public string
locket_short(void)
{
    string desc = "locket";

    if (strlen(metal))
       desc = metal + " " + desc;

    if (strlen(engraving))
       desc = "engraved " + desc;

    if (open)
       desc = "open " + desc;

    return desc;
}

public varargs string
image_desc(object for_who)
{
    // If the image is of a person, and the person is either yourself or
    // someone you know, you will recognize that fact.
    if (!who || !strlen(who) || who == "0")
        return image;

    return image + (for_who->query_real_name() == who ?
	", which you recognize as being yourself" :
	(for_who->query_met(who) ? ", who you recognize as " +
	    CAP(who) : ""));
}

public string
locket_long(void)
{
    return "It is a beautifully crafted locket"
      + (strlen(metal) ? " made from " + metal : "")
      + ", meant to be worn around the neck."
      + (strlen(engraving) ? " There is an engraving along the edge of the "
      + "locket." : "") + (open ? (strlen(image) ? " The locket is open, "
      + "showing an image of " + image_desc(TP) + "." : " The locket is open, "
      + "but is emptry inside.") : " The locket is closed.") + "\n";
}

public string
engraving_words(void)
{
    if (!strlen(engraving))
        return "Shantih.";

    string eng = engraving;
    int last = eng[strlen(eng) - 1];

    if (last < 'A' || last > 'z')
        return CAP(eng);
    else
        return CAP(eng) + ".";
}

public string
engraving_desc(void)
{
    return "Delicately engraved into the " + (strlen(metal) ?
	metal : "metal") + " of the locket are the words: " +
	engraving_words() + "\n";
}

public void
init_arg(string arg)
{
    sscanf(arg, "#OPEN#%d#METAL#%s#IMAGE#%s#ENGRAVING#%s#WHO#%s", 
           open, metal, image, engraving, who);

    if (!initialized)
       init_locket();
}

public mixed
query_auto_load(void)
{
    // Only one locket will autoload
    if (present(LOCKET_ID, ENV(TO)) != TO)
       return 0;

    if (!strlen(metal) || !strlen(image))
       return 0;

    // if it is going to auto-load, don't drop it when
    // you quit.
    add_prop(OBJ_M_NO_DROP, 1);
    set_alarm(1.0, 0.0, &remove_prop(OBJ_M_NO_DROP));

    return MASTER + ":#OPEN#" + open + 
                    "#METAL#" + metal + 
                    "#IMAGE#" + image + 
                    "#ENGRAVING#" + engraving + 
                    "#WHO#" + who;
}

public mixed
query_recover(void)		{ return 0; }

public void
set_metal(string str)		{ metal = str; }

public void
set_image(string str)		{ image = str; }

public void
set_engraving(string str)	{ engraving = str; }

public void
set_who(string str)		{ who = lower_case(str); }

private int
this_locket(string str)
{
    if (!strlen(str))
       return 0;

    sscanf(str, "the %s", str);
    sscanf(str, "my %s", str);

    object *obs = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(obs))
        obs = FIND_STR_IN_OBJECT(str, ENV(TP));

    if (!sizeof(obs) || obs[0] != TO)
        return 0;

    return 1;
}

public int
open_locket(string str)
{
    if (!this_locket(str))
       return NF(CAP(query_verb()) + " what?\n");

    if (open)
      return NF("It is already open.\n");

    write("You open up " + LANG_THESHORT(TO) + ".\n");
    say(QCTNAME(TP) + " opens " + LANG_ASHORT(TO) + ".\n");

    open = 1;
    return 1;
}

public int
close_locket(string str)
{
    if (!this_locket(str))
       return NF(CAP(query_verb()) + " what?\n");

    if (!open)
      return NF("It is already closed.\n");

    write("You close " + LANG_THESHORT(TO) + " with a soft 'click'.\n");
    say(QCTNAME(TP) + " closes " + LANG_ASHORT(TO) + ".\n");

    open = 0;
    return 1;
}

public int
hold_locket(string str)
{
    if (!this_locket(str))
       return NF(CAP(query_verb()) + " what?\n");

    write_vbfc("You hold your " + QSHORT(TO)
        + " close to your breast.\n");
    say(QCTNAME(TP) + " holds " + LANG_ASHORT(TO)
        + " close to " + HIS(TP) + " breast.\n");

    return 1;
}

public int
rub_locket(string str)
{
    if (!this_locket(str))
       return NF(CAP(query_verb()) + " what?\n");

    write_vbfc("You run your fingers along your " +
	QSHORT(TO) + ".\n");
    say(QCTNAME(TP) + " runs " + HIS(TP) + " fingers along " +
	LANG_ASHORT(TO) + ".\n");

    return 1;
}

public int
show_locket(string str)
{
    string arg1, arg2;
    object *oblist;
    int i;

    if (!strlen(str))
       return NF(CAP(query_verb()) + " what?\n");

    sscanf(str, "%s to %s", arg1, arg2);
    if (!this_locket(arg1))
       return NF(CAP(query_verb()) + " what?\n");

    if (!strlen(arg2))
       return NF("Show your locket to whom?\n");

    oblist = parse_this(arg2, "[the] %l");

    if (!sizeof(oblist))
       return NF("Show your locket to whom?\n");

    actor("You show your locket to", oblist);
    all2act(" shows " + LANG_ASHORT(TO) + " to", oblist);

    for(i=0;i<sizeof(oblist);i++)
    {
       oblist[i]->catch_msg(QCTNAME(TP) + " shows you "
           + LANG_ASHORT(TO) + (open ? ", within which is an "
           + "image of " + image_desc(oblist[i]) :
	   ", which is closed") + ".\n");
    }

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(rub_locket, "rub");
    add_action(show_locket, "show");
    add_action(hold_locket, "hold");
    add_action(open_locket, "open");
    add_action(close_locket, "close");
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

