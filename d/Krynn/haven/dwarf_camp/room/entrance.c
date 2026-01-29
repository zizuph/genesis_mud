/* Dwarven camp by Morrigan */

#include "/d/Krynn/haven/local.h"
#include <macros.h>
#include <filter_funs.h>

inherit CAMPBASE;

#define THE_ROAD RDIR + "road10"
#define THE_CAMP DROOM + "camp1"
#define I_KILLED_DWARVES "_i_killed_dwarves"

object dwarf;

// Prototypes
string my_desc();

void
reset_haven_room()
{
    if (!objectp(dwarf))
    {
	dwarf = clone_object(STD + "dwarf_base");
        dwarf->move_living("M", TO);
        tell_room(QCTNAME(dwarf) + " arrives from nearby.\n");
    }
    else if (!present(dwarf, TO))
    {
        dwarf->move_living("M", TO);
        tell_room(QCTNAME(dwarf) + " arrives from nearby.\n");
    }
}

void
create_camp()
{
    add_my_desc(my_desc);

    add_exit(RDIR + "road10", "north", "@@go_north");
    add_exit(DROOM + "camp1", "south", "@@go_south");

    OUTSIDE;
    reset_haven_room();
}

int
go_north()
{
    if (!TP->query_prop(I_KILLED_DWARVES))
    {
	return 0;
    }

    if (TP->query_prop("_live_o_last_room") == find_object(THE_ROAD))
    {
	return 0;
    }

    if (!present(dwarf, TO) || !CAN_SEE(dwarf, TP))
    {
        return 0;
    }

    dwarf->command("say If I'll let you pass after you attack my friends, "+
                   "then I'm a bearded gnome! You'll have to kill me to get out of "+
                   "here, "+TP->query_race_name()+"!");
    dwarf->command("fume");
    return 1;
}

int
so_south()
{
    if (!TP->query_prop(I_KILLED_DWARVES))
    {
	return 0;
    }
    
    if (TP->query_prop("_live_o_last_room") == find_object(THE_CAMP))
    {
	return 0;
    }
    
    if (!present(dwarf, TO) || !CAN_SEE(dwarf, TP))
    {
	return 0;
    }
    dwarf->command("say I'll not let you enter after you attack my friends!");
    dwarf->command("glare "+TP->query_real_name());
    return 1;
}

void greet_msg(object dwarf, object ob)
{
  dwarf->command("say Greetings, "+ob->query_race_name()+". Feel "+
                 "free to walk around the camp, but don't touch anything! We "+
		 "have to sell this stuff, you know.");
}

void
enter_inv(object ob, object from)
{
    if (present(dwarf, TO) && CAN_SEE(dwarf, ob) && sizeof(FILTER_LIVE( ({ ob }) )) > 0)
    {
	if (from == find_object(THE_ROAD))
	{
	    if (ob->query_prop(I_KILLED_DWARVES))
		dwarf->command("say You aren't welcome here, "+
		  ob->query_race_name()+"!");
	    else if (!ob->query_prop(I_KILLED_DWARVES) && interactive(ob))
                set_alarm(0.0, 0.0, &greet_msg(dwarf, ob));
	}
	else if (from = find_object(THE_CAMP))
	{
	    if (ob->query_prop(I_KILLED_DWARVES))
		dwarf->command("say By Reorx, I will kill you!");
	    else if (!ob->query_prop(I_KILLED_DWARVES))
		dwarf->command("say Did you find anything you liked, "+ob->query_race_name()+
		  "? It'll all be for sale in Haven soon!");
	}
    }

    ::enter_inv(ob, from);
}

string
my_desc()
{
    if (!present(dwarf, TO))
    {
	return "\n";
    }
    return "There is a "+dwarf->short()+" here, greeting those who come to the "+
           "camp, perhaps " + HE(dwarf) + " is guarding it as well.\n";
}

