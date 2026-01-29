/**********************************************************************
 * - ftunic.c                                                       - *
 * - Tunic for females to be purchased in female shop in SaMorgan.  - *
 * - Created by Damaris@Genesis 05/2006                             - *
 **********************************************************************/

#pragma strict_types
#include "arm.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/armour";
private string query_tunic();
string _LENGTH = query_tunic();
private string query_color();
string _COL = query_color();
private string query_style();
string _STYLE = query_style();

void
create_armour()
{
	set_short("" + _LENGTH + " "+ _STYLE +" "+ _COL +" tunic");
	set_name("tunic");
	add_name("tunic");
	set_adj( _LENGTH );
	set_long("This " + short() + " is a loose-fitting garment "+
	"that is worn by commoners and nobles alike. There is a small "+
	"tag sewn in the underside.\n");
	add_item(({"tag"}),
	"The tag reads:\n"+
	"Made in SaMorgan.\n"+
	"You may <tug tunic>, <brush tunic>, <adjust tunic>\n");
	add_cmd_item("tag", "read", "The tag reads:\n"+
	"Made in SaMorgan.\n"+
	"You may <tug tunic>, <brush tunic>, <adjust tunic>\n");	
	set_ac(10);
	add_prop(OBJ_I_VALUE, 500);
	set_at(A_BODY);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}

private string
query_tunic()
{
	string *adjectives = ({
		"long", "short"
		});
		return adjectives[random(sizeof(adjectives))];
}

private string
query_style()
{
	string *style = ({
		"faded", "warm", "clean", "vivid", "sharp", "pale",
		"colourful", "bold", "lustrous", "deep", "brilliant",
		"flashy", "fresh", "florid", "distinctive", "soft",
		"crisp", "distinct", "plain", "cotton", "smooth",
		"comfortable", "sensible",
		});
		return style[random(sizeof(style))];
}

private string
query_color()
{
	string *colors = ({
        "white", "yellow", "blue-green", "scarlet", "red",
        "blue", "sapphire", "green", "black",
        });
        return colors[random(sizeof(colors))];
}
int
tug_hem(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "tunic"))
	{
		write("You descretely tug on the hem of "+
		"your tunic.\n");
		
                say(QCTNAME(TP)+" descretely tugs on the hem "+
                "of "+ HIS(TP) +" tunic.\n");
                return 1;
                }
                else
                {
			notify_fail("Tug tunic perhaps?\n");
			return 0;
		}
}

int
brush_tunic(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "tunic"))
	{
		write("You brush the dirt from your tunic.\n");
		
                say(QCTNAME(TP)+" brushes the dirt from "+
                "" + HIS(TP) +" tunic.\n");
                return 1;
                }
                else
                {
			notify_fail("Brush tunic perhaps?\n");
			return 0;
		}
}

int
adjust_tunic(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "tunic"))
	{
		write("You adjust your tunic.\n");
		
		say(QCTNAME(TP)+" adjusts "+ HIS(TP) +" tunic.\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust tunic perhaps?\n");
			return 0;
		}
}
public void
init()
{
	::init();
	/* Any init code you might have. */
	add_action(tug_hem, "tug");
	add_action(brush_tunic, "brush");
	add_action(adjust_tunic, "adjust");
}
