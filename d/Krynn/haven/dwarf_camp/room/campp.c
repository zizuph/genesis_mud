/* Dwarven camp by Morrigan */

#include "/d/Krynn/haven/local.h"
#include <macros.h>
#include <filter_funs.h>

inherit CAMPBASE;

#define I_KILLED_DWARVES "_i_killed_dwarves"

object dwarf1, dwarf2;

// Prototypes
string my_desc();
int enter_tent(string str);

void
reset_haven_room()
{
    if (!objectp(dwarf1))
    {
	dwarf1 = clone_object(STD + "dwarf_base");
	dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
	dwarf2 = clone_object(STD + "dwarf_base");
	dwarf2->move(TO);
    }
}

void
create_camp()
{
    add_my_desc(my_desc);

    add_exit(DROOM + "campk", "northwest");
    add_exit(DROOM + "campl", "north");
    add_exit(DROOM + "campm", "northeast");
    add_exit(DROOM + "campq", "east");
    add_exit(DROOM + "camp8", "south");
    add_exit(DROOM + "campo", "west");

    add_item(({"tent", "canvas tent", "large canvas tent"}),
               "The large canvas tent seems like good place to seek " +
               "protection from bad weather.\n");

    OUTSIDE;
    reset_haven_room();
}

init()
{
    add_action("play", "play");
    add_action("play", "throw");
    add_action(enter_tent, "enter");
    ::init();
}

int
enter_tent(string str)
{
   if(str &&
      str != "tent" && 
      str != "canvas tent" && 
      str != "large tent" &&
      str !="large canvas tent")
   {
       notify_fail("Enter what? The tent?\n");
       return 0;
   }
   write("You enter the canvas tent.\n");
   tell_room(this_object(), QCTNAME(TP)+" enters the canvas tent.\n", TP);
   TP->move_living("M",DROOM + "tentp",0,0);
   return 1;
}

int
play(string str)
{
    NF("What ?\n");
    if (!present(dwarf1, TO) || !present(dwarf2, TO))
    {
	return 0;
    }
    
    NF("Throw bones?\n");
    if (!str)
    {
	return 0;
    }
    
    if (str != "bones")
    {
	return 0;
    }
    write("You throw some of the bones, but just don't find the game as inter"+
      "esting as these two dwarves, and eager to play, they shove you out of "+
      "the way and resume their game.\n");
    say(QCTNAME(TP)+" throws some bones with the dwarves, but doesn't seem to "+
      "enjoy "+OBJECTIVE(TP)+"self as they do.\n");
    return 1;
}

void
bones(object ob)
{
    if (ob == dwarf1 || ob == dwarf2)
	return;

    dwarf1->command("say Ahoy there, "+ob->query_race_name()+"! Care to "+
                    "to throw a few bones with us, eh?");
    dwarf2->command("agree");
    dwarf2->command("say We promise not to take all yer money! Well, not "+
                    "all at once anyhow!");
}

void
enter_inv(object ob, object from)
{
    if (present(dwarf1, TO) && present(dwarf2, TO) && CAN_SEE(dwarf1, ob) && !ob->query_prop(I_KILLED_DWARVES) && sizeof(FILTER_LIVE(({ob}))))
    {
	if (!ob->query_leader())
	    set_alarm(1.0, 0.0, &bones(ob));
    }

    ::enter_inv(ob, from);
}

string
my_desc()
{
    if (!present(dwarf1, TO) && !present(dwarf2, TO))
    {
	return "You also notice a large canvas tent.\n";
    }
    
    if (!present(dwarf1, TO) || !present(dwarf2, TO))
    {
	return "There is a dwarf who is alone here, looking rather bored. "+
	"You also notice a large canvas tent.\n";
    }
    
    return "There are two dwarves here throwing bones, a dwarvish gambling "+
           "game. Occasionally, one of the two will roar with laughter or in "+
           "anger as a game is won or lost. You also notice a large canvas tent.\n";
}

