inherit "/d/Earthsea/std/room.c";
inherit "/lib/trade";

#include <stdproperties.h>
#include <formulas.h>
#include <cmdparse.h>

void create_earthsea_room()
{
 set_short("Earthsea smithy");
 set_long(break_string(
   "You are in a loud , steamy smithy. You see smith working "+
   "with his hammer on some weapons. Smithy looks prety simple and "+
   "humble. Exit leads back to crowded streat.\n",75));
 config_default_trade();


add_exit("/d/Earthsea/gont/gont_city/rooms/city_street/city_road31","southwest");
}

void init()
{
 ::init();
 add_action("do_sharpen","sharpen");
}

int do_sharpen(string str)
{
 object *weapon;
 int price,*pay_res;

 weapon=FIND_STR_IN_OBJECT(str,this_player());
 if(sizeof(weapon)==0)
  {
   notify_fail("Sharpen what?\n");
   return 0;
  }
 if(sizeof(weapon)>1)
  {
   notify_fail("Be more specific!\n");
   return 0;
  }

 if (function_exists("create_object",weapon[0]) != "/std/weapon")
  {
   notify_fail("That's not a weapon!\n");
   return 0;
  }

 if(weapon[0]->query_prop(OBJ_I_BROKEN))
  {
   notify_fail("But it's broken!\n");
   return 0;
  }

 if(!F_LEGAL_WEAPON_REPAIR_DULL(weapon[0]->query_repair_dull()+1,
   weapon[0]->query_dull()))
  {
   notify_fail("Cannot sharpen any futher.\n");
   return 0;
  }

 price=weapon[0]->query_value()/10;
 write(sprintf("The cost of sharpening is %d copper coins\n",price));
 pay_res=pay(price,this_player(),0,1,0,0,0);
 if(pay_res[0]==3)
  {
   notify_fail("You cannot afford sharpening the weapon!\n");
   return 0;
  }

 weapon[0]->set_repair_dull(weapon[0]->query_repair_dull() + 1);
 write("Smith sharpens your weapon.\n");
 pay(price,this_player(),0,0,0,0,0);

 return 1;
}
