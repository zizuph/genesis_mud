/**********************************************************************
 * - gown2.c                                                       - *
 * - Basic gown for gown shop in Macdunn                          - *
 * - Created by Damaris@Genesis 01/2006                             - *
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
private string query_gown();
string _ADJ = query_gown();

void create_armour()
{
	set_short("" + _ADJ + " "+ _SHD +" " + _COL + " gown");
	set_pshort("" + _ADJ + " "+ _SHD +" " + _COL + " gowns");
	set_name(({"gown", "clothing", "clothes"}));
	set_pname(({"gowns"}));
	set_adj(_ADJ);
	add_adj(_COL);
	add_adj(_SHD);
	set_long("This " + short() + " has obviously been sewn by "+
	"skilled hands. The dainty details crafted with each stitch "+
	"make this garment quite special. The cotton cloth is quite "+
	"" +_ADJ +" with its attractive scoop collar and matching "+
	"cuffs accenting in contrasting color. The corresponding "+
	"lace panels on the sides slenderize the hip then the skirt "+
	"flares into a graceful circle. A small tag has been sewn "+
	"in the lining with script.\n");
	add_item(({"tag", "script"}),
	"The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <lift gown>, <spin gown>, <adjust gown>\n");
	add_cmd_item(({"script","tag"}), "read", "The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <lift gown>, <spin gown>, <adjust gown>\n");
	set_may_not_recover();
	set_ac(0);
	add_prop(OBJ_I_VALUE, 320);
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
		"ivory", "cream", "yellow", "grey", "brown", "scarlet",
		"blue", "sapphire", "green", "burgendy", "pink", "purple", 
		"lavender", "peach", "aquamarine", "indigo",
		});
		return colors[random(sizeof(colors))];
}

private string
query_gown()
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
	if((str == "gown"))
	{
		write("You descretely lift the hem of "+
		"your gown.\n");
		say(QCTNAME(TP)+" descretely lifts the hem "+
                "of "+ HIS(TP) +" gown.\n");
                return 1;
                }
                else
                {
			notify_fail("Lift gown perhaps?\n");
			return 0;
		}
}

int
spin_gown(string str)
{
	if(this_player() != query_worn())
	return 0;
	if((str == "gown"))
	{
		write("You spin around gracefully flaring "+
		"the skirt of your gown.\n");	
                say(QCTNAME(TP)+" spins around gracefully flaring "+
                "the skirt of " + HIS(TP) +" gown.\n");
                return 1;
                }
                else
                {
			notify_fail("Spin gown perhaps?\n");
			return 0;
			}
}

int
adjust_gown(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "gown"))
	{
		write("You gracefully adjust the collar "+
		"and smooth the skirt of your gown.\n");		
		say(QCTNAME(TP)+" gracefully adjusts the collar "+
		"and smooths the skirt of " + HIS(TP) +" "+
		"gown.\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust gown perhaps?\n");
			return 0;
		}
}
public void
init()
{
	::init();
	/* Any init code you might have. */
	add_action(lift_hem, "lift");
	add_action(spin_gown, "spin");
	add_action(adjust_gown, "adjust");
}
