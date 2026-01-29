/**********************************************************************
 * - cloak1.c                                                       - *
 * - Basic cloak for dress shop in Macdunn                          - *
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
private string query_cloak();
string _CLOTH = query_cloak();

void create_armour()
{
	set_short("" + _COL + " " + _CLOTH + " cloak");
	set_pshort("" + _COL + " " + _CLOTH + " cloaks");
	set_adj(({"" + _CLOTH + ", " + _COL + ""}));
	set_name(({"cloak", "clothing", "clothes"}));
	set_pname(({"cloaks"}));
	set_long("This " + short() + " has been crafted with skilled "+
	"hands. The delicate details with each stitch make this "+
	"garment quite special. The " +_CLOTH +" cloth is quite "+
	"attractive with it's full length. A small "+
	"tag has been sewn in the lining with script.\n");
	add_item(({"cotton lining", "lining"}),
	"The cotton lining is light and soft.\n");
	add_item(({"tag", "script"}),
	"The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <lift cloak>, <spin cloak>, <adjust cloak>\n");
	add_cmd_item(({"script","tag"}), "read", "The tag reads:\n"+
	"Made in Macdunn by Peggy Mae, weaver of cloths.\n"+
	"You may <lift cloak>, <spin cloak>, <adjust cloak>\n");
	set_may_not_recover();
	set_ac(0);
	add_prop(OBJ_I_VALUE, 320);
	set_at(A_ROBE);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}

private string
query_color()
{
	string *colors = ({
        "ivory", "cream", "red", "scarlet", "blue", "sapphire", "green",
        "burgendy", "emerald", "black", "onyx", "ebony", "lavender",
        "pale blue", "aquamarine", "dark brown", "brown", "grey"
        });
        return colors[random(sizeof(colors))];
}

private string
query_cloak()
{
	string *cloths = ({
	"wool", "velvet"
	});
	return cloths[random(sizeof(cloths))];
}

int
lift_cloak(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "cloak"))
	{
		write("You descretely lift the hem of "+
		"your "+ short() +" out of the way.\n");
		
                say(QCTNAME(TP)+" descretely lifts the hem "+
                "of "+ HIS(TP) +" "+ short() +" out of the way.\n");
                return 1;
                }
                else
                {
			notify_fail("Lift cloak perhaps?\n");
			return 0;
		}
}

int
spin_cloak(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "cloak"))
	{
		write("You spin around gracefully flaring "+
		"your " + short() +".\n");
		
                say(QCTNAME(TP)+" spins around gracefully flaring "+
                "" + HIS(TP) +" " + short() +".\n");
                return 1;
                }
                else
                {
			notify_fail("Spin cloak perhaps?\n");
			return 0;
		}
}

int
adjust_cloak(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "cloak"))
	{
		write("You gracefully adjust the collar "+
		"of your " + short() +".\n");
		
		say(QCTNAME(TP)+" gracefully adjusts the collar "+
		"of " + HIS(TP) +" " + short() +".\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust cloak perhaps?\n");
			return 0;
		}
}
public void
init()
{
	::init();
	/* Any init code you might have. */
	add_action(lift_cloak, "lift");
	add_action(spin_cloak, "spin");
	add_action(adjust_cloak, "adjust");
}
