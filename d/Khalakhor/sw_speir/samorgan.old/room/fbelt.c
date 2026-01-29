/**********************************************************************
 * - fbelt.c                                                        - *
 * - Belts for females to be purchased in female shop in SaMorgan.  - *
 * - Created by Damaris@Genesis 05/2006                             - *
 **********************************************************************/

#pragma strict_types
#include "arm.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/armour";
private string query_belt();
string _LENGTH = query_belt();
private string query_color();
string _COL = query_color();
private string query_style();
string _STYLE = query_style();

void
create_armour()
{
	set_short("" + _LENGTH + " "+ _STYLE +" "+ _COL +" belt");
	set_name("belt");
	add_name("belt");
	set_adj( _LENGTH );
	set_long("This " + short() + " is usually worn around tunics. "+
	"There is a small tag sewn in the underside.\n");
	add_item(({"tag"}),
	"The tag reads:\n"+
	"Made in SaMorgan.\n"+
	"You may <tug belt>, <brush belt>, <adjust belt>\n");
	add_cmd_item("tag", "read", "The tag reads:\n"+
	"Made in SaMorgan.\n"+
	"You may <tug belt>, <brush belt>, <adjust belt>\n");	
	set_ac(10);
	add_prop(OBJ_I_VALUE, 350);
	set_at(A_WAIST);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}

private string
query_belt()
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
        if((str == "belt"))
	{
		write("You descretely tug on edge of "+
		"your belt.\n");
		
                say(QCTNAME(TP)+" descretely tugs on the edge "+
                "of "+ HIS(TP) +" belt.\n");
                return 1;
                }
                else
                {
			notify_fail("Tug belt perhaps?\n");
			return 0;
		}
}

int
brush_belt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "belt"))
	{
		write("You brush the dirt from your belt.\n");
		
                say(QCTNAME(TP)+" brushes the dirt from "+
                "" + HIS(TP) +" belt.\n");
                return 1;
                }
                else
                {
			notify_fail("Brush belt perhaps?\n");
			return 0;
		}
}

int
adjust_belt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "belt"))
	{
		write("You adjust your belt.\n");
		
		say(QCTNAME(TP)+" adjusts "+ HIS(TP) +" belt.\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust belt perhaps?\n");
			return 0;
		}
}
public void
init()
{
	::init();
	/* Any init code you might have. */
	add_action(tug_hem, "tug");
	add_action(brush_belt, "brush");
	add_action(adjust_belt, "adjust");
}