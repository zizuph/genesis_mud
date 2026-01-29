/*
 *  file name:   hskirt.c
 *  creator:     Zielia
 *  last update:
 *  purpose:
 *  note(s):
 *  bug(s):
 *  to-do:
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#include "zigg.h"

inherit "/std/object";

inherit "/lib/keep";
inherit "/lib/wearable_item";

public static int saunter;
public static string in, out;
private static string color = one_of_list(({
    "red", "blue", "pink", "purple",
    "yellow", "green", "orange", "black", "white", "grey",
}));

public string
query_color(void)	{ return color; }

public int
set_color(string str)
{
    remove_adj(color);
    color = str;
    add_adj(color);
    set_short(color +" double-slitted harem skirt");

    return 1;
}

public void
create_object()
{
    config_wearable_item(A_HIPS, 5, 10, TO);

    set_name(({"skirt", "loincloth", "garment"}));
    add_pname(({"clothes", "clothing"}));
    set_adj(({"harem", "double-slitted", "long", color, "sybarun", "ziggurat"}));
    set_short(color +" double-slitted harem skirt");
    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 1000);
	
   	if (IS_CLONE)
      set_item_expiration();  	
	
}

public string
my_long(void)
{
    string str;

    if (worn)
	str = "floor length, whispering over the ground as you walk, ";
    else
	str = "long, ";

    return "Almost more of a loincloth than a skirt, it is "+ str +
	"with wide slits on each side running from hem to "+
	"waist, revealing the legs beneath as much as it covers them. "+
	"It is made of lightweight, sheer "+ color +" silk of the finest "+
	"quality.\n";
}

public int
wear(object ob)
{
    if (TP != environment(TO))
	return 0;

    write("You slip the "+ short() +" over your "+
      "legs, delighting in the sensual feel of the silk "+
      "as it slides over your skin to settle at your hips.\n");

    say(QCTNAME(TP)+" pulls the "+ short() +" up to "+ HIS(TP) +
      " hips, letting it flow over "+ HIS(TP) +" legs like silken water.\n");

    return 1;
}

public int
remove(object ob)
{
    if (TP != environment(TO))
	return 0;

    if (saunter)
    {
	TP->set_m_in(in);
	TP->set_m_out(out);
    }

    write("You slip your "+ short() +" off of your hips and "+
      "allow it to slide down your legs, forming a pool of "+
      color +" silk at your feet before you pick it up.\n");

    say(QCTNAME(TP)+" slips "+ HIS(TP) +" "+ short() +" off of "+ HIS(TP) +
      " hips, allowing it to slide down "+ HIS(TP) +" legs, "+
      "forming a pool of "+ color +" silk at "+ HIS(TP) +" feet before "+
      HE(TP)+ " picks it.\n");

    return 1;
}

public void
leave_env(object from, object to)
{
    if (saunter)
    {
	TP->set_m_in(in);
	TP->set_m_out(out);
    }

    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public int
f_saunter(string str)
{
    if (!query_worn())
    {
	notify_fail("You must be wearing the skirt.\n");
	return 0;
    }

    if (TP->query_wiz_level())
    {
	notify_fail("Wizards cannot do this.\n");
	return 0;
    }

    if (!strlen(str))
    {
	notify_fail("Do you want saunter on or off?\n");
	return 0;
    }

    if (str == "on")
    {
	in = TP->query_m_in();
	out = TP->query_m_out();

	write("You will now saunter.\n");

	TP->set_m_out("swivels her hips, flashing skin beneath her "+
	  "swaying harem skirt as "+ HE(TP) +" walks");

	TP->set_m_in("saunters in, "+ HIS(TP)+" thighs flashing "+
	  "provocatively through the side slits of "+ HIS(TP) +
	  " skirt as she arrives");
	saunter = 1;
	return 1;
    }

    if (str == "off")
    {
	write("You will no longer saunter.\n");

	TP->set_m_in(in);
	TP->set_m_out(out);
	saunter = 0;
	return 1;
    }
}

public string
query_recover(void)
{
    return MASTER + ":$!" + color + "!$" +
	query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    string tmp;

    init_item_expiration_recover(arg);

    sscanf(arg, "%s$!%s!$%s", arg, tmp, arg);
    set_color(tmp);

}

public void
init(void)
{
    ::init();
    add_action(f_saunter, "saunter");
}
