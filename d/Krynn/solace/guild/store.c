/*
 *   The storage room of the Solamnian shop, made by Nick
 *   Altered by Mucalytic May the 20th '96.
 *   Altered by Karath March 13 1997 - checked for str in enter/squeeze
 *
 */

#include "local.h"
#include "/sys/macros.h"
#include "/d/Krynn/common/defs.h"

inherit INSIDE_BASE;

#define TORCH   "solamnian_shop_torch"
#define BAG     "solamnian_shop_bag"

void
reset_solace_room()
{
    int i;
    object ob;

    seteuid(getuid(TO));

    if(!present(TORCH, TO))
    {
        for(i = 0; i < 2; i++)
        {
            ob = clone_object(OBJ + "torch");
            ob->add_name(TORCH);
            ob->move(TO);
        }
    }

    if(!present(BAG, TO))
    {
        ob = clone_object(ABAG/*OBJ + "bag"*/);
	clone_object(SHORTSWORD)->move(ob,1);
        ob->add_name(BAG);
	ob->add_prop(CONT_I_CLOSED,1);
        ob->move(TO);
    }
}

void
create_solace_room()
{
    set_short("The shop's store room");
    set_long("You find yourself in a musty-smelling room with bare walls and "+
        "floor. The air here is quite cold. This is the old store room of "+
        "the shop. The only exit leads eastwards, but it has been boarded "+
        "over with shutters from the other side.\n");

    add_item(({"floor", "walls", "bare walls"}), "You notice nothing special "+
       "or out of the ordinary.\n");
    add_item("shutters", "Someone seems to have nailed shutters across the "+
        "exit to the east. It looks all closed. You notice a narrow opening "+
        "right at the bottom, near the floor though.\n");
   add_item("opening","You think it might be possible to squeeze through if " +
	    "you make yourself very very thin.\n");
    reset_solace_room();
}

void
init()
{
    ::init();

    add_action("enter_opening", "enter");
    add_action("enter_opening", "squeeze");
}

int
enter_opening(string str)
{
    string prep = "'under' / 'through' / 'into' ";
    string msg = "[the] [narrow] 'shutters' / 'opening'";
    int hgt = TP->query_prop(CONT_I_HEIGHT), vol = TP->query_prop(OBJ_I_VOLUME);
    int avg = TP->query_average_stat();
    
    NF("What?\n");
    if (!stringp(str))
	return 0;
    
    if( str && (query_verb() == "enter" && parse_command(str, TP, msg)) ||
       (query_verb() == "squeeze" && parse_command(str, TP, prep + msg)))
    {
	if((vol / hgt) < 300 ||  avg < 35)
	{
	    write("You squeeze through the hole.\n");
	    say(QCTNAME(TP)+" lies flat on the floor and squeezes "+
		OBJECTIVE(TP)+"self under the shutters.\n");
	    
	    TP->move_living("into the opening", TDIR + "shop",1 ,0);
	}
	else
	{
            write("You are too big to fit through!\n");
            say(QCTNAME(TP)+" lies flat on the floor and gets up again, "+
                "grumbling unhappily.\n");
        }
        return 1;
    }
    else
      return 0;
}
