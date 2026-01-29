/**********************************************************************
 * - pants.c                                                        - *
 * - Basic leggings for gentleman shop in SaMorgan                  - *
 * - Created by Damaris@Genesis 10/2005                             - *
 **********************************************************************/

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/armour";
#include "/d/Khalakhor/sys/basic.h"

private string query_color();
string _COL = query_color();
private string query_stud();
string _STUD = query_stud();
private string query_dadj();
string _ADJ = query_dadj();

void create_armour()
{
	set_short("" + _STUD + " studded " + _COL + " pair of leggings");
	set_adj(({"" + _COL + "," + _STUD + " "}));
	set_name(({"leggings", "clothing", "clothes", "pants"}));
	set_pname(({"pairs of leggings", "pairs of pants"}));
	set_long("Skilled and obviously caring hands have intricately "+
	"sewed this " + short() + ". The fine details crafted "+
	"with each stitch make this garment quite special. The sturdy "+
	"" +_COL + " cotton corduroy is quite " +_ADJ +" with its "+
	"slender yet shapely fabric, which is accentuated by "+
	""+ _STUD +" studs along the sides. A small tag has been sewn "+
	"in the lining with script.\n");
	
	add_item(({"tag"}),
	"The tag reads:\n"+
	"Made in SaMorgan by Brenetta Chalahan.\n"+
	"You may <adjust leggings>, <dust leggings>, <pick leggings>\n");
	add_cmd_item("tag", "read", "The tag reads:\n"+
	"Made in SaMorgan by Brenetta Chalahan.\n"+
	"You may <adjust leggings>, <dust leggings>, <pick leggings>\n");
	set_ac(0);
	add_prop(OBJ_I_VALUE, 610);
	set_at(A_LEGS);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}
private string
query_color()
{
	string *colors = ({
        "ivory", "cream", "yellow", "crimson", "scarlet",
        "blue", "sapphire", "green", "burgendy",
        "black", "onyx", "ebony", "purple", "lavender",
        "indigo", "grey", "burgundy",
        });
        return colors[random(sizeof(colors))];
}

private string
query_stud()
{
	string *studs = ({
	"brass", "gold", "silver", "pearl", "copper",
	"platinum", "mithril",
	});
	return studs[random(sizeof(studs))];
}

private string
query_dadj()
{
	string *dadjs = ({
	"elegant", "stunning", "noble", "charming", "warm",
	"sleek", "stylish", "refined"
	});
	return dadjs[random(sizeof(dadjs))];
}

int
dust_it(string str)
{
	if(this_player() != query_worn())
	return 0;
        if((str == "leggings"))
	{
		write("You descretely dust off your leggings.\n");
		
                say(QCTNAME(TP)+" descretely dusts off "+
                ""+ HIS(TP) +" leggings.\n");
                return 1;
                }
                else
                {
			notify_fail("Dust leggings perhaps?\n");
			return 0;
		}
}

int
pick_it(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "leggings"))
	{
		write("You pick slightly at the "+ _STUD +" studs on "+
		"your leggings in boredom.\n");
		
                say(QCTNAME(TP)+" picks slightly at the "+ _STUD +" "+
                "studs on " + HIS(TP) +" leggings looking a bit bored.\n");
                return 1;
                }
                else
                {
			notify_fail("Pick leggings perhaps?\n");
			return 0;
		}
}

int
adjust_it(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "leggings"))
	{
		write("You adjust the waistband "+
		"and smooth the sides of your leggings.\n");
		
		say(QCTNAME(TP)+" adjusts the waistband "+
		"and smooths the sides of " + HIS(TP) +" "+
		"leggings.\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust leggings perhaps?\n");
			return 0;
		}
}
public void
init()
{
	::init();
	add_action(dust_it, "dust");
	add_action(pick_it, "pick");
	add_action(adjust_it, "adjust");
}
