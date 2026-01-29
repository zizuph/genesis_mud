/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"


void
create_room()
{
    add_prop(ROOM_I_INSIDE,1); 



    set_short("Army pub");
/*
    set_long("This is the place where Angmar's warriors would spend most " +
        "of the money they had--the pub. It is newly rebuilt in its " +
        "former days because the old one has been destroyed by angry " +
        "Angmar's warriors because of the lack of the rum. Now, it " +
        "has fallen apart. There is a sign next to the exit and a counter " +
        "with a sink. A menu is lying on the counter and behind it you " +
        "can see huge broken barrels and a shelf full of shattered " +
        "glasses and empty bottles. Since the bartender left years " +
        "ago, nothing can be ordered here anymore.\n");
*/
    set_long("The walls are blown out and black with soot from fires " +
        "that burned in this room. Charred remains of chairs and tables " +
        "are scattered about and smashed barrels and casks litter the " +
        "ground. Behind the bar is a looted cupboard full of broken " +
        "glass and bottles. Some of the bottles look ancient, as if " +
        "this was the first place to purchase them ever.\n");
    
    add_item(({"sink","water"}),
        "The sink is full of foul water. It doesn't look too appetizing.\n");
    add_item(({"shelf", "bottles", "bottle", "glasses", "glass", 
        "broken glasses", "shattered glasses", "broken bottles", 
        "broken empty bottles", "empty bottles"}), 
        "There are many kinds of bottles and glasses on the shelf. " +
        "They are now broken and shattered, lying in heaps of broken glass.\n");
  add_item(({"barrels", "barrel", "broken barrels"}), 
        "Huge barrels lie in heaps about the room. They are broken and shattered with nothing in them.\n");
  add_item("counter", "It's made out of wood. On one side there is a "+
	"sink full of water and on the other side you see a menu.\n");
  add_item("menu","An ordinary menu, what did you expected? It is here "+
	"for everyone to read it.\n");
  add_cmd_item("menu","read","@@read_menu"); 
  add_item("exit","You should use it if you want to leave.\n");
  add_item("sign","A big sign nailed to the wall.\n");
  add_cmd_item("sign","read","@@read_sign"); 

  add_exit(NEW_ANGMAR + "c2", "west");

}

string
read_menu()
{
  if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
  return "\nYou can buy:\n\n"+
	"pint or half pint of:\n"+
	"   ale ................ 13 /  7 cc\n"+
	"   apple cider ........ 20 / 10 cc\n"+
	"   dark beer .......... 30 / 16 cc\n\n"+
        "glass of\n"+
        "   light table wine ... 22 cc\n"+
	"   white wine ......... 34 cc\n"+
	"   heavy red wine ..... 45 cc\n\n"+
	"small, regular or double \n"+
	"   cherry ............. 12 /  23 /  44 cc\n"+
	"   brandy ............. 42 /  83 / 164 cc\n"+
	"   strong rum ......... 92 / 183 / 364 cc\n\n"+
	"You can also buy whole bottle of drink to take it away.\n"+
	"Please read sign for prices. Also you can ask me to\n"+
	"refill your bottle or glass with whatever is available.\n\n";
}

string
read_sign()
{
  if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
  return "\n"+
"    +--------------------------------------------------+\n"+
"    |                                                  |\n"+
"    |    No glasses out of this room!                  |\n"+
"    |      Return them on the counter before you go.   |\n"+
"    |                                                  |\n"+
"    +--------------------------------------------------+\n"+
"\n"+
"If you want to take drink with you you can buy full bottle.\n"+
"I have three sizes of bottles available:\n"+
"   small .............  96 cc\n"+
"   medium ............ 176 cc\n"+
"   big ............... 410 cc\n\n"+
"Here are prices of bottle of (excluding price of the bottle):\n"+
"   ale ................   21 /   38 /    86 cc\n"+
"   apple cider ........   31 /   56 /   128 cc\n"+
"   dark beer ..........   47 /   86 /   198 cc\n\n"+
"   light table wine ...   84 /  153 /   355 cc\n"+
"   white wine .........  136 /  248 /   576 cc\n"+
"   heavy red wine .....  178 /  326 /   758 cc\n\n"+
"   cherry .............  348 /  632 /  1472 cc\n"+
"   brandy ............. 1338 / 2432 /  5672 cc\n"+
"   strong rum ......... 2988 / 5432 / 12672 cc\n\n";
}
