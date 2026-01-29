inherit  "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Roke/common/defs.h"

string long,whereto;

create_room() 
{
 ::create_room();

set_short("Dragonship");
set_long("@@slong");

add_item(({"wing","wings"}),"The enchanted wings stretch from the side of the ship.\n");
add_item(({"ship","dragonship"}),"It is hand crafted from wood and enchanted to fly.\n");
add_item(({"deck","wooden deck"}),"The deck is smooth and shiny, but still very strong.\n");
add_item(({"mast"}),"It is tall and holds up the sail.\n");
add_item(({"sail"}),"It is fluttering gently in the breeze.\nYou dont even think"
        + " it needs a sail.\n");

}


slong()
{
        long = (BS("You are on standing on the deck of a massive dragonship."
        + " The entire vessel is made of wood with a single mast in the"
        + " centre of the deck. A huge billowing sail flutters in the breeze."
        + " The most facinating thing are the massive pair of wings that"
        + " stretch from the side of the ship.\n",70));
        return long;
}

take_off(string s)
{
  whereto = s;
        tell_room(TO,"The dragonship wings stretch out and it takes to the air.\n");
        remove_exit("leave");
        call_out("flying",10);
}

flying()
{
        call_out("flying2",15);
        tell_room(TO,"The dragonship hurtles through the air.\n");
}
flying2()
{
        tell_room(TO,"The dragonship lands.\n");
        call_other(whereto,"ship_arrive");
	arrive(whereto);
}
arrive(string s)
{
  object *folk;
  int i;

  tell_room(TO,"The ships shakes a little and you fall off it.\n");

  folk = all_inventory(TO);
 
  if(folk)
    for(i=0;i<sizeof(folk);i++)
      {
	if(living(folk[i]))
	  folk[i]->move_living("falling down",s);
      }

}


