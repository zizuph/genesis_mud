/*
 * Fake Moustache
 * --Raymundo, Jan 2020
 */

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";
inherit "/lib/keep";

#define AC  0
#define ADJ1	"black"
#define ADJ2	"bushy"
#define NAME	"moustache"
create_armour() {
    set_name(NAME);
	add_name("mustache");
	add_adj(ADJ1);
	add_adj(ADJ2);
	add_adj("fake");
    set_short(ADJ1 + " " + ADJ2 + " " + NAME);
    
    set_long("This " + query_short() + " is bold and full and makes quite "
		+ "the statement about what kind of man (or Dwarven woman) you are. "
		+ "It is also completely fake. You notice some small metal clips that "
		+ "attach it to your upper lip. It looks like it would pinch a bit, "
		+ "maybe even hurt, but what's a little pain when you look this "
		+ "good?\nYou see a small tag.\n");
    set_default_armour(AC,A_MOUTH,({0,0,0}),0);
   
	add_item( ({"tag", "small tag"}), "This tag looks like the kind of thing "
		+ "a person would read!\n");
   
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,(10));
    set_keep(1);
	add_prop(OBJ_M_NO_BUY);
}

void
init()
{
	::init();
	add_action("do_twist", "mtwist");
	add_action("do_stroke", "mstroke");
	add_action("do_lick", "mlick");
	add_action("do_wiggle", "mwiggle");
	add_action("do_help", "mhelp");
	add_action("do_read", "read");
}

//Moustache Emotes
string
read_tag()
{
	return("The tag reads:\n<mhelp>\n");
}

int
do_read(string str)
{
	if(str == "tag")
	{
		write(read_tag());
		return 1;
	}
	else
	{
		notify_fail("Read what? The tag?\n");
		return 0;
	}
}
int
do_help(string str)
{
	if(!strlen(str))
	{
		write(""
		+ "***********************************\n"
		+ "* THANK YOU FOR PURCHASING ONE OF *\n"
		+ "* OUR FINE MOUSTACHES. YOU MAY:   *\n"
		+ "* <mhelp>                         *\n"
		+ "* <mlick>                         *\n"
		+ "* <mstroke>                       *\n"
		+ "* <mtwist>                        *\n"
		+ "* AND <mwiggle>                   *\n"
		+ "* YOUR MOUSTACHE. THANK YOU FOR   *\n"
		+ "* YOUR SUPPORT!                   *\n"
		+ "***********************************\n\n");
		return 1;
	}
	else
	{
		notify_fail("Did you mean to <mhelp>?\n");
	}
}

int
do_wiggle(string str)
{
	if(!query_worn())
	{
		notify_fail("You must wear the " + query_short() 
			+ " first!\n");
		return 0;
	}
	if(!strlen(str))
	{
		write("You wiggle your upper lip back and forth, trying to "
			+ "draw attention to your moustache.\n");
		say(QCTNAME(TP) + " wiggles " + HIS_HER(TP) + 
            " moustache back and "
			+ "forth and you realize " + HE_SHE(TP) + " is wearing a "
			+ query_short() + "!\n");
		return 1;
	}
	else
	{
		notify_fail("Did you mean to <mwiggle> your lip?\n");
		return 0;
	}
}
	
int
do_lick(string str)
{
	if(!query_worn())
	{
		notify_fail("You must wear the " + query_short() 
			+ " first!\n");
		return 0;
	}
	if(!strlen(str))
	{
		write("You stick your tongue out and lick your moustache, "
			+ "trying to remember what you had for lunch.\n");
		say(QCTNAME(TP) + " sticks " + HIS_HER(TP) + " tongue out "
			+ "and licks " + HIS_HER(TP) + " moustache, trying "
			+ "to remember what " + HE_SHE(TP) + " had for "
			+ "lunch.\n");
			return 1;
	}
	else
	{
		notify_fail("Did you mean to <mlick> your moustache?\n");
	}
}

int
do_stroke(string str)
{
	if(!query_worn())
	{
		notify_fail("You must wear the " + query_short() 
			+ " first!\n");
		return 0;
	}
	if(!strlen(str))
	{
		write("You stroke your moustache with your index finger and "
			+ "thumb, lost in thought.\n");
		say(QCTNAME(TP) + " strokes " + HIS_HER(TP) + " moustache "
			+ "with " + HIS_HER(TP) + " index finger and thumb, "
			+ "lost in thought.\n");
		return 1;
	}
	else
	{
		notify_fail("Did you mean to <mstroke> your moustache?\n");
		return 0;
	}
}
int
do_twist(string str)
{
	if(!query_worn())
	{
		notify_fail("You must wear the " + query_short() 
			+ " first!\n");
		return 0;
	}
	if(!strlen(str))
	{
		write("You twist the edges of your " + query_short()
			+ " around your finger and then let it go, looking "
			+ "meditative.\n");
		say(QCTNAME(TP) + " twists the ends of " + HIS_HER(TP)
			+ " moustache around " + HIS_HER(TP) + " finger and "
			+ "then lets it go, looking meditative.\n");
		return 1;
	}
	else
	{
		notify_fail("Are you trying to <mtwist> your moustache?\n");
		return 0;
	}
}

string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}
