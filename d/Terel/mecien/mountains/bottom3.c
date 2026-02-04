inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <money.h>

reset_room(arg){

object ice, schain, sapphire, axe, cloak, money, gold, copper;
seteuid(getuid(this_object()));
if(present("schain")) return;
schain=clone_object("/d/Terel/mecien/schain");
schain->move(this_object());
if(present("sapphire")) return;
sapphire=clone_object("/d/Terel/mecien/sapphire");
sapphire->move(this_object());
if(present("axe")) return;
axe=clone_object("/d/Terel/mecien/axe");
axe->move(this_object());
if(present("cloak")) return;
cloak=clone_object("/d/Terel/mecien/cloak");
cloak->move(this_object());
money = MONEY_MAKE_SC(200);
money->move(this_object());
gold = MONEY_MAKE_GC(10);
gold->move(this_object());
copper = MONEY_MAKE_CC(1300);
copper->move(this_object());
}

create_room(){
set_short("Cave");
set_long(
"This smaller cave seems to be a treasure room. The walls are encrusted with\n"
+"crystals, making it glitter. It is very clean here.\n");
add_prop(ROOM_I_INSIDE, 1);
add_exit("/d/Terel/mecien/mountains/bottom2","west", 0);
reset_room();
}

