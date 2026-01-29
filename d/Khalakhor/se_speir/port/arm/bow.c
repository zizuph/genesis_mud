/**********************************************************************
 * - bow.c                                                          - *
 * - Basic bow to wear in hair for bow shop in Macdunn              - *
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
private string query_bow();
string _CLOTH = query_bow();

void create_armour()
{
	set_short("" + _COL + " " + _CLOTH + " bow");
	set_pshort("" + _COL + " " + _CLOTH + " bows");
	set_adj(({"" + _CLOTH + ", " + _COL + ""}));
	set_name(({"bow", "clothing", "clothes"}));
	set_pname(({"bows"}));
	set_long("This " + short() + " has been crafted with skilled "+
	"hands. The delicate details with each stitch make this "+
	"bow quite special. The " +_CLOTH +" cloth quite attractive. "+
	"A small tag with flowing script is sewn under the bow.\n");
	add_item(({"tag", "script"}),
	"The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <adjust bow>, <tug bow>, <caress bow>.\n");
	add_cmd_item(({"script","tag"}), "read", "The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <adjust bow>, <tug bow>, <caress bow>.\n");
	set_may_not_recover();
	set_ac(5);
	add_prop(OBJ_I_VALUE, 125);
	set_at(A_HEAD);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}

private string
query_color()
{
	string *colors = ({
        "ivory", "cream", "yellow", "blue", "sapphire", "green",
        "burgendy", "black", "onyx", "ebony", "lavender", "peach",
        "aquamarine", "emerald", "grey"
        });
        return colors[random(sizeof(colors))];
}

private string
query_bow()
{
	string *cloths = ({
	"satin", "velvet"
	});
	return cloths[random(sizeof(cloths))];
}

int
tug_bow(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "bow"))
	{
		write("You descretely tug on your "+ short() +".\n");
		
                say(QCTNAME(TP)+" descretely tugs on "+
                ""+ HIS(TP) +" "+ short() +".\n");
                return 1;
                }
                else
                {
			notify_fail("Tug bow perhaps?\n");
			return 0;
		}
}

int
caress_bow(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "bow"))
	{
		write("You smooth and caress your " + short() +" thoughtfully.\n");
		
                say(QCTNAME(TP)+" smoothes and caresses " + HIS(TP) +" " + short() +" "+
                "thoughtfully.\n");
                return 1;
                }
                else
                {
			notify_fail("Caress bow perhaps?\n");
			return 0;
		}
}

int
adjust_bow(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "bow"))
	{
		write("You adjust your " + short() +" so it is "+
		"more flattering.\n");
		
		say(QCTNAME(TP)+" adjusts " + HIS(TP) +" "+
		"" + short() +" so it is more flattering.\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust bow perhaps?\n");
			return 0;
		}
}
public void
init()
{
	::init();
	/* Any init code you might have. */
	add_action(tug_bow, "tug");
	add_action(caress_bow, "caress");
	add_action(adjust_bow, "adjust");
}
