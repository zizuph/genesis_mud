#pragma strict_types
/*
 * The vaults of the Union
 *
 * Certain members can "donate" things here, and their description
 * will be added as part of the room's items.
 *
 *  Cirion 122296
 *
 *  Revisions:
 *     Lucius, Apr 2005: Changed commands and added help.
 *     Lucius, Jul 2011: Refactored all code, added sorting.
 *
 */
#include "../defs.h"

#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

inherit BASE;

#define SH(x)	pieces[x][0]
#define NMS(x)	pieces[x][1]
#define DON(x)	pieces[x][2]
#define WHN(x)	pieces[x][3]
#define LON(x)	pieces[x][4]
#define IDX	m_indexes(pieces)

/*
 * pieces of form: mapping ([
 * 	file_name : ({ "short", ({ "names" }), "donator", when, "long" }),
 *   ])
 */
public mapping pieces = ([ ]);

public static string *sorted_idx = ({ });
public static string *sorted_cmp = ({ });

private static int alarm_id;


public int
sort_pieces(string file1, string file2)
{
    return WHN(file1) - WHN(file2);
}

public string
composite_item_shorts(void)
{
    if (!sizeof(sorted_cmp))
    {
	foreach(string item : sorted_idx)
	    sorted_cmp += ({ LANG_ADDART(SH(item)) });
    }

    return COMPOSITE_WORDS(sorted_cmp);
}

public void
restore_items(void)
{
    int count = 0;

    sorted_cmp = ({ });
    sorted_idx = sort_array(IDX, sort_pieces);

    foreach(string item : sorted_idx)
    {
	count++;
	add_item(({ SH(item), "pillar " + count,
	    LANG_WORD(count) + " pillar",
	    "pillar " + LANG_WNUM(count) }),
	  /*
	   * No longer include NMS(item) as there are just
	   * too many bogus and generic descriptors to be useful.
	   */
	  "It is a short, wide pillar, made from perfectly carved "+
	  "white marble. Sitting atop the pillar is "+
	  LANG_ADDART(SH(item)) +": "+ LON(item) +
	  "Carved on the pedestal are the words:\n" +
	  "Donated by " + CAP(DON(item)) + ".\n");
    }

    add_item(({"objects","donations"}), "The items displayed "+
      "atop the pillars are " + composite_item_shorts() + ".\n");
}

public void
make_base_items(void)
{
    add_item(({"ceiling","roof","up","above"}),"The ceiling, "+
	"like the walls, is of the unhewn rock formations of "+
	"a natural cavern.\n@@shadows@@");
    add_item(({"tile","tiles","squares","ground","floor"}),
      "The stone tiles that make up the ground are perfectly "+
      "smooth and glossy, as if the passing of the years has "+
      "consistently polished them.\n");
    add_item(({ "pillars", "pedestals", "pieces", "displays" }),
      "There are @@num_pillars@@ stark white pillars running down "+
      "the length of the hall. They each hold a different item atop, "+
      "and there are inscriptions on each pillar.\n");
    add_item(({"wall","walls"}),"The walls of the cavern are rough "+
	"and unformed, the rough craggy formation of a natural "+
	"cavern. The contrast between the walls and the floor "+
	"brings a sense of otherworldliness to the area.\n");
    add_item(({"pillar","pedestal"}),"There are "+
	"@@num_pillars@@ different pillars, all about waist high "+
	"and made from white marble.\n");
}

/*
 * Take away all the items in the room, and
 * then refresh them. This is trickier than
 * it would first seem.
 *
 * This is used when someone removes a donation
 * from the room, in order to update the current
 * items in the room.
 */
private void
remake_items(void)
{
    // Clear the items.
    obj_items = ({ });

    // Now rebuild the items
    make_base_items();
    restore_items();
}

public string
num_pillars(void)
{
    return LANG_WNUM(sizeof(sorted_idx));
}

public void
union_room(void)
{
    set_short("vaults");
    set_long("Wide square tiles of mottled and glossy granite cover "+
	"the floor of this long chamber. In stark contrast to the "+
	"perfection of the floor tiles, the walls are unhewn and "+
	"craggy rock, the remnants of a natural cavern. Evenly "+
	"spaced along the floor are @@num_pillars@@ white stone "+
	"pillars, about waist high, each holding an item.\n");

    add_exit("hall_e", "southwest");

    restore_object(SAVINGS + "vaults");
    remake_items();
}

private void
touch(object who)
{
    if (!objectp(who) || !present(who))
	return;

    who->catch_tell("The whispers grow to a roar in your ears, "+
	"and then suddenly die away.\n");
}

public string
shadows(void)
{
    if (TP->query_prop("union_heard_the_shadows"))
	return "";

    TP->add_prop("union_heard_the_shadows", 1);
    add_prop(ROOM_I_HIDE, -1);
    set_alarm(5.0, 0.0, &touch(TP));

    return "It is very dark and shadowy, and "+
	"you can almost hear whispers from above.\n";
}

/*
 * Get rid of names like "ob_3422" and "mystic_weapon"
 */
public string *
valid_names(object ob)
{
    string *names = ({ });

    foreach(string id : ob->query_names())
    {
	if (wildmatch("*_*", id))
	    continue;

	if (wildmatch("*:*", id))
	    continue;

	names += ({ id });
    }

    if (!sizeof(names))
	return ({ "object" });
    else
	return names;
}

public int
donate(string str)
{
    string who;

    if (!strlen(str))
	return NF("Donate what for display in the vaults?\n");

    if (!IS_MEMBER(TP) &&
	SECURITY->query_wiz_dom(TP->query_name()) != "Avenir")
    {
	write("You may not donate anything here.\n");
	return 1;
    }

    sscanf(str, "the %s", str);
    parse_command(str, ({ }), "%s 'for' %s", str, who);

    object *things = FIND_STR_IN_OBJECT(str, TP);
    int size = sizeof(things);

    if (!size)
    {
	write("Donate what for display in the vaults?\n");
	return 1;
    }

    if (size > 1)
    {
	write("You may only donate one item at a time.\n");
	return 1;
    }

    string file = MASTER_OB(things[0]);

    if (wildmatch("/std/*", file) || things[0]->num_heap() > 1)
    {
	write("The " + things[0]->short(TP) + " is not worthy.\n");
	return 1;
    }

    if (things[0]->query_prop(OBJ_M_NO_DROP))
    {
	write("You cannot seem to part with it.\n");
	return 1;
    }

    if (sizeof(pieces[file]))
    {
	write("The vaults already contain a duplicate piece.\n");
	return 1;
    }

    string long = things[0]->query_long();

    /* VBFC there? Well, let's try the for_obj construction */
    if (wildmatch("*@@*", long))
	long = things[0]->long();

    if (strlen(who))
    {
	who = lower_case(who);
	if (!SECURITY->exist_player(who))
	{
	    write("You cannot donate an item for someone who does not exist.\n");
	    return 1;
	}
    } else {
	who = TP->query_real_name();
    }

    pieces += ([ file : ({ things[0]->short(TP),
	valid_names(things[0]), who, time(), long
      }) ]);

    save_object(SAVINGS + "vaults");

    TP->catch_msg("You place the " + QSHORT(things[0]) + " on top of "+
	"a pedestal as a donation to the vaults.\n");
    say(QCTNAME(TP) + " places " + LANG_ASHORT(things[0]) + " on top "+
	"of a pedestal as a donation to the vaults.\n");

    set_alarm(0.0, 0.0, &(things[0])->remove_object());
    remake_items();

    str = NM(TP) + (TP->query_real_name() == who ? " " :
	" [for "+ CAP(who) +"] ") +"donated: "+
    things[0]->short();

    LOG_EVENT(str);
    LOG_COUNC(str);

    return 1;
}

public int
remove(string str)
{
    if (!strlen(str))
	return NF("Remove what from the vaults?\n");

    if (!IS_MEMBER(TP) &&
	SECURITY->query_wiz_dom(TP->query_name()) != "Avenir")
    {
	write("You may not remove anything from the vaults.\n");
	return 1;
    }

    if (!TP->query_wiz_level() && !MEMBER_SPHERE(TP, SPH_BEAUTY))
    {
	write("Only the Sphere of Beauty may remove items "+
	    "from the vaults.\n");
	return 1;
    }

    int flag = 0;

    foreach(string item : sorted_idx)
    {
	if (str == SH(item))
	{
	    flag++;
	    m_delkey(pieces, item);

	    write("You remove the '" + str +"' from "+
		"the vaults forever.\n");
	}
    }

    if (!flag)
    {
	write("What would you like to remove from the vaults?\n"+
	  "Possible choices are: "+ composite_item_shorts() +"?\n"+
	  "Note: You should leave off the first 'a' or 'an'.\n");
    }
    else
    {
	save_object(SAVINGS + "vaults");
	remake_items();

	str = NM(TP) +" removed '"+ str +"' from the vaults.";
	LOG_EVENT(str);
	LOG_COUNC(str);
    }

    return 1;
}

public int
help_vault(string str)
{
    if (str != "here" && str != "vault")
	return 0;

    write("Help for the Vaults of the Shadow Union:\n\n"+
      "  * vdonate <item>  -  Donate an item to the Vaults.\n"+
      "                       Also: vdonate <item> for <whom>.\n"+
      "  * vremove <item>  -  Remove an item from the Vaults.\n"+
      "\n");

    return 1;
}

private static string *sounds = ({
    "A soft, ethereal music seems to fill the room.\n",
    "The soft, distant pounding of a drum can be heard from "+
	"within the walls.\n",
    "A flute can be heard softly playing nearby.\n",
    "A noise like running water seems to be coming from high above.\n",
});

public void
sound(void)
{
    alarm_id = 0;
    tell_room(TO, one_of_list(sounds));
}

public void
init(void)
{
    ::init();

    add_action(donate, "vdonate");
    add_action(remove, "vremove");

    if (IS_MEMBER(TP) || IS_GMASTER(TP))
	add_action(help_vault, "help");

    if (!alarm_id && !random(10))
	alarm_id = set_alarm(10.0 + itof(random(100)), 0.0, sound);
}
