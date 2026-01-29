#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
inherit "/d/Kalad/room_std";
object ob1;

void
create_room()
{
     ::create_room();
      set_short("Cliffside Road");
     set_long("You are on Cliffside road. The road continues to the "
             +"east and west. To your south is the edge of the large "
         +"cliff that seperates the Port and Tradesman districts. "
         +"You are surrounded by the homes of the lower class, as "
         +"well as small shops owned by the poor people of the area. "
          +"To your south, a brilliant yellow sign is flapping in the "
          +"breeze, and an open door is inviting passerbys in.\n");
  add_item(({"road","roads","intersection"}),"This is a plain road, "
	+"not at all interesting in the least. It is made of worn "
	+"stone, and is dirty.\n");
  add_item(({"homes","houses","house","home"}),"They are small old "
	+"houses belonging to the lower classed tradesman of Kabal.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
	+"lower-classed people.\n");
add_item(({"sign"}),"This blazing yellow sign is hanging outside of "
                   +"the shop to the south. The sign reads: "
                   +"Cordell's Rope Shop.\n");
add_cmd_item("sign", "read", "It says: Cordell's Rope Shop.\n");
add_exit(TRADE(cliffside/cliffside_junc),"west");
add_exit(TRADE(cliffside/cliffside1),"east");
add_exit(TRADE(cliffside/ropeshop1),"south");
                                    
     hear_bell = 2;
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
        if (!ob1)
        {
        ob1 = clone_object("/d/Kalad/common/trade/tmil.c");
        ob1 ->move_living("xxx", this_object());
        }
}
                                         
