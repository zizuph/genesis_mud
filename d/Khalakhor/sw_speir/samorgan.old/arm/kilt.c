/**********************************************************************
 * - fkilt.c                                                       - *
 * - Tunic for females or males to be purchased in SaMorgan.        - *
 * - Created by Damaris@Genesis 05/2006                             - *
 **********************************************************************/

#pragma strict_types
#include "arm.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/armour";
private string query_kilt();
string _DESIGN = query_kilt();
private string query_color();
string _COL = query_color();
private string query_style();
string _STYLE = query_style();

void
create_armour()
{
	set_short(""+ _STYLE +" "+ _COL +" " + _DESIGN + " kilt");
	set_name("kilt");
	add_name("kilt");
	set_adj( _DESIGN );
	set_long("This " + short() + " is a loose-fitting garment "+
	"that is worn by commoners and nobles alike. There is a small "+
	"tag sewn in the underside.\n");
	add_item(({"tag"}),
	"The tag reads:\n"+
	"Made in SaMorgan.\n"+
	"You may <tug kilt>, <brush kilt>, <adjust kilt>, <flash kilt>.\n");
	add_cmd_item("tag", "read", "The tag reads:\n"+
	"Made in SaMorgan.\n"+
	"You may <tug kilt>, <brush kilt>, <adjust kilt>, <flash kilt>.\n");
//	set_layers(1);
	set_looseness(10);

	set_ac(10);
	add_prop(OBJ_I_VALUE, 500);
	set_at(A_LEGS);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}

private string
query_kilt()
{
	string *adjectives = ({
		"plaid", "striped"
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
        "white and blue", "yellow and black", "blue-green and black",
        "scarlet and white", "red and black", "blue and black",
        "sapphire and white", "green and black", "scarlet and black",
        });
        return colors[random(sizeof(colors))];
}
int
tug_hem(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You descretely tug on the hem of "+
		"your "+ short(TP) +".\n");
		
                say(QCTNAME(TP)+" descretely tugs on the hem "+
                "of "+ HIS(TP) +" "+ short(TP) +".\n");
                return 1;
                }
                else
                {
			notify_fail("Tug kilt perhaps?\n");
			return 0;
		}
}

int
brush_kilt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You brush the dirt from your "+ short(TP) +".\n");
		
                say(QCTNAME(TP)+" brushes the dirt from "+
                "" + HIS(TP) +" "+ short(TP) +".\n");
                return 1;
                }
                else
                {
			notify_fail("Brush kilt perhaps?\n");
			return 0;
		}
}

int
adjust_kilt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You adjust your "+ short(TP) +".\n");
		
		say(QCTNAME(TP)+" adjusts "+ HIS(TP) +" "+ short(TP) +".\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust kilt perhaps?\n");
			return 0;
		}
}
int
flash_kilt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You swish your "+ short(TP) +" and flash a bit "+
		"of leg.\n");
		
		say(QCTNAME(TP)+" swishes "+ HIS(TP) +" "+ short(TP) +" "+
		"and flashes a bit of leg.\n");
		return 1;
		}
		else
		{
			notify_fail("Flash kilt perhaps?\n");
			return 0;
		}
}

public void
init()
{
	::init();
	/* Any init code you might have. */
	add_action(tug_hem, "tug");
	add_action(brush_kilt, "brush");
	add_action(adjust_kilt, "adjust");
	add_action(flash_kilt, "flash");
}
