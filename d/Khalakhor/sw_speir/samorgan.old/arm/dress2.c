/**********************************************************************
 * - dress2.c                                                       - *
 * - Basic dress for dress shop in SaMorgan                         - *
 * - Created by Damaris@Genesis 08/2005                             - *
 **********************************************************************/

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/armour";
#include "/d/Khalakhor/sys/basic.h"
private string query_shade();
string _SHD = query_shade();
private string query_color();
string _COL = query_color();
private string query_dress();
string _ADJ = query_dress();

void create_armour()
{
	set_short("" + _ADJ + " "+ _SHD +" " + _COL + " dress");
	set_pshort("" + _ADJ + " "+ _SHD +" " + _COL + " dresses");
	set_name(({"dress", "clothing", "clothes"}));
	set_pname(({"dresses"}));
	set_adj(_ADJ);
	add_adj(_COL);
	add_adj(_SHD);
	set_long("This " + short() + " has been intricately sewn by "+
	"skilled and obviously caring hands. The fine details crafted "+
	"with each stitch make this garment quite special. The cotton "+
	"cloth is quite " +_ADJ +" with its graceful scoop collar and "+
	"cuffs accenting in contrasting color. The matching lace "+
	"panels on the sides slenderize the hip then the skirt flares "+
	"into a graceful circle. A small tag has been sewn in the "+
	"lining with script.\n");
	add_item(({"script"}),
	"It is on the tag.\n");
	add_item(({"tag"}),
	"The tag reads:\n"+
	"Made in SaMorgan by Arinia Estel, weaver of cloths.\n"+
	"You may <lift dress>, <spin dress>, <adjust dress>\n");
	add_cmd_item("tag", "read", "The tag reads:\n"+
	"Made in SaMorgan by Arinia Estel, weaver of cloths.\n"+
	"You may <lift dress>, <spin dress>, <adjust dress>\n");
	set_ac(0);
	add_prop(OBJ_I_VALUE, 620);
	set_at(A_BODY);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}
private string
query_shade()
{
	string *shades = ({
		"light", "faded", "dark", "pale", "bright"
		});
		return shades[random(sizeof(shades))];
}

private string
query_color()
{
	string *colors = ({
		"ivory", "cream", "yellow", "red", "crimson", "scarlet",
		"blue", "sapphire", "green", "burgendy", "pink", "purple", 
		"lavender", "peach", "aquamarine", "indigo",
		});
		return colors[random(sizeof(colors))];
}

private string
query_dress()
{
	string *adjectives = ({
		"attractive", "elegant", "alluring", "pretty",
		"stunning", "appealing", "pleasant", "noble",
		"charming", "pleasing", "lovely", "captivatingly",
		"soft", "smooth", "flowing", "delicate", "petite",
		"sleek", "slenderizing", "stylish", "refined"
		});
		return adjectives[random(sizeof(adjectives))];
}
int
lift_hem(string str)
{
	if(this_player() != query_worn())
	return 0;
	if((str == "dress"))
	{
		write("You descretely lift the hem of "+
		"your dress.\n");
		say(QCTNAME(TP)+" descretely lifts the hem "+
                "of "+ HIS(TP) +" dress.\n");
                return 1;
                }
                else
                {
			notify_fail("Lift dress perhaps?\n");
			return 0;
		}
}

int
spin_dress(string str)
{
	if(this_player() != query_worn())
	return 0;
	if((str == "dress"))
	{
		write("You spin around gracefully flaring "+
		"the skirt of your dress.\n");	
                say(QCTNAME(TP)+" spins around gracefully flaring "+
                "the skirt of " + HIS(TP) +" dress.\n");
                return 1;
                }
                else
                {
			notify_fail("Spin dress perhaps?\n");
			return 0;
			}
}

int
adjust_dress(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "dress"))
	{
		write("You gracefully adjust the collar "+
		"and smooth the skirt of your dress.\n");		
		say(QCTNAME(TP)+" gracefully adjusts the collar "+
		"and smooths the skirt of " + HIS(TP) +" "+
		"dress.\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust dress perhaps?\n");
			return 0;
		}
}
public void
init()
{
	::init();
	/* Any init code you might have. */
	add_action(lift_hem, "lift");
	add_action(spin_dress, "spin");
	add_action(adjust_dress, "adjust");
}
