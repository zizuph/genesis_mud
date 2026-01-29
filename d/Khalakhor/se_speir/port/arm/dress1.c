/**********************************************************************
 * - dress1.c                                                       - *
 * - Basic dress for dress shop in Macdunn                          - *
 * - Created by Damaris@Genesis 01/2006                             - *
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
private string query_dress();
string _CLOTH = query_dress();

void create_armour()
{
	set_short(""+ _COL +" "+ _CLOTH +" dress");
	set_pshort(""+ _COL +" "+ _CLOTH +" dresses");
	set_adj(({"" + _CLOTH + ", " + _COL + ""}));
	set_name(({"dress", "clothing", "clothes"}));
	set_pname(({"dresses"}));
	set_long("This " + short() + " has been crafted with skilled "+
	"hands. The delicate details with each stitch make this "+
	"garment quite special. The " +_CLOTH +" cloth with "+
	"its attractive v-collar and wide cuffs accenting in contrasting "+
	"color. The matching lace panels on the sides slenderize the "+
	"hip then the skirt flares into a graceful circle. A small "+
	"tag has been sewn in the cotton lining with script.\n");
	add_item(({"cotton lining", "lining"}),
	"The cotton lining is light and soft.\n");
	add_item(({"tag", "script"}),
	"The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <lift dress>, <spin dress>, <adjust dress>\n");
	add_cmd_item(({"script","tag"}), "read", "The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <lift dress>, <spin dress>, <adjust dress>\n");
	set_may_not_recover();
	set_ac(0);
	add_prop(OBJ_I_VALUE, 320);
	set_at(A_BODY);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}

private string
query_color()
{
	string *colors = ({
        "ivory", "cream", "yellow", "blue", "sapphire", "green",
        "burgendy", "black", "onyx", "ebony", "lavender", "peach",
        "aquamarine", "brown", "grey"
        });
        return colors[random(sizeof(colors))];
}

private string
query_dress()
{
	string *cloths = ({
	"cotton", "wool"
	});
	return cloths[random(sizeof(cloths))];
}

int
lift_hem(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "dress"))
	{
		write("You descretely lift the hem of "+
		"your "+ short() +".\n");
		
                say(QCTNAME(TP)+" descretely lifts the hem "+
                "of "+ HIS(TP) +" "+ short() +".\n");
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
		"the skirt of your " + short() +".\n");
		
                say(QCTNAME(TP)+" spins around gracefully flaring "+
                "the skirt of " + HIS(TP) +" " + short() +".\n");
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
		"and smooth the skirt of your " + short() +".\n");
		
		say(QCTNAME(TP)+" gracefully adjusts the collar "+
		"and smooths the skirt of " + HIS(TP) +" "+
		"" + short() +".\n");
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
