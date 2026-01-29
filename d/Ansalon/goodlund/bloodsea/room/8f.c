#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/money.h" 

inherit BLOODSEA_OUT;

object merchant, sailor1, sailor2, sailor3, chest, money, ship;
object gem1, gem2, bottle, scroll;

#define SPINEL_GEM clone_object("/d/Genesis/gems/obj/spinel_blue")
#define BLOODSTONE clone_object("/d/Genesis/gems/obj/bloodstone")
#define BOTTLE clone_object("/d/Calia/gelan/objects/bottle")

void
reset_bloodsea_room()
{
     object boat_in;

     if (!objectp(ship)) 
     {
          ship = clone_object(BOBJ +"merchant_schooner");
          ship->move(this_object());
     }

     if(!present(ship, TO))
     {
          ship = clone_object(BOBJ +"merchant_schooner");
          ship->move(this_object());
     }

     if (!objectp(boat_in = ship->query_boat_in())) 
     {
         ship->config_boat_inside();
         boat_in = ship->query_boat_in();
     }

     if (!objectp(merchant)) 
     {
         merchant = clone_object(BNPC + "merchant");
         merchant->move_living("in his schooner", boat_in);
         merchant->arm_me();
         boat_in->set_owner(merchant); 
     }

     if (!objectp(sailor1)) 
     {
         sailor1 = clone_object(BNPC + "sailor");
         sailor1->move_living("in his schooner", boat_in);
         sailor1->arm_me();
     }

     if (!objectp(sailor2)) 
     {
         sailor2 = clone_object(BNPC + "sailor");
         sailor2->move_living("in his schooner", boat_in);
         sailor2->arm_me();
     }

     if (!objectp(sailor3)) 
     {
         sailor3 = clone_object(BNPC + "sailor");
         sailor3->move_living("in his schooner", boat_in);
         sailor3->arm_me();
     }

    if (!objectp(chest))
      {
        chest = clone_object(BOBJ + "chest");
        chest->move(boat_in);
      }

    chest->add_prop(CONT_I_CLOSED, 1);
    chest->add_prop(CONT_I_LOCK, 1);

    if (!P(scroll, chest))
      {
        if(random(2))
        {
          scroll = clone_object("/d/Krynn/common/scrolls/mage_strength_scroll");
          scroll->move(chest, 1);
        }
      }
 
    if (!P(money, chest))
      {
          money = MONEY_MAKE_GC(random(40));
          money->move(chest, 1);
      }

    if (!P(gem1, chest))
      {
          gem1 = SPINEL_GEM;
          gem1->move(chest, 1);
      }

    if (!P(gem2, chest))
      {
          gem2 = BLOODSTONE;
          gem2->move(chest, 1);

      }

    if (!P(bottle, chest))
      {
          bottle = BOTTLE;
          bottle->move(chest, 1);
          bottle->set_adj("big");
          bottle->set_short("big bottle");
          bottle->set_pshort("big bottles");
          bottle->set_max(3500);
          bottle->set_soft(bottle->query_max());
          bottle->set_filled_short(({"dwarven rum"}));
          bottle->set_alco(60 * bottle->query_max() / 100);
      }

}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(BROOM + "9f", "west", 0, 1);
    add_row_exit(BROOM + "8g", "north", 0, 1);
    add_row_exit(BROOM + "7f", "east", 0, 1);
    add_row_exit(BROOM + "8e", "south", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}


void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return bloodsea_short();
}
 
string
long_descr()
{
    return bloodsea_desc()+ "\n";
}