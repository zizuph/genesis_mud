/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
inherit INSIDE_BASE;

object sk1, sk2;

create_solace_room()
{
    object door;

    set_short("Crypt entrance");
    set_long(break_string("You are standing in a dark underground tunnel,"
	 + " in front of you to your north is a pair of double doors."
	 + " Intense evil seems to radiate from everything down here making "
         + "you wonder who or what was buried within.\n", 70));

    add_exit(PARENT + "grave8", "up", "@@stone_state");
	
    add_item(({"marble door", "door", "doors", "double door",
	"double doors", "marble doors"}), "@@doors");
    add_item(({"tunnel", "wall", "walls", "floor", "ground", "roof",
	"ceiling"}), "@@tunnel");

    DARK

    door = clone_object(OBJ + "d_hole1a");
    door->move(TO);
    door->set_key(K_HOLE1);

    reset_solace_room();
}

reset_solace_room()
{
    if (!sk1)
      {
	  sk1 = clone_object(MONSTER + "skwarrior");
	  sk1->move_living("xxx", TO);
	  clone_object(OBJ + "d_hole1_key")->move(sk1);
      }
    if (!sk2)
      {
	  sk2 = clone_object(MONSTER + "skwarrior");
	  sk2->move_living("xxx", TO);
      }
}
doors()
{
    write(BS("These doors are made of smooth black marble. Looking into them"
	     + " is like looking into death itself.", 70));
    return "";
}

tunnel()
{
    write("Looking round this place gives you the creeps.\n");
    return "";
}


stone_state()
{
    object st = present("my_stone",find_object(PARENT + "grave8"));
    if (st)
      {
	  write("You push the stone away.\n");
	  st->push("stone south");
	  return 0;
      }
    else
      return 0;
      
}
