/* this is an abstract room of the square in Gelan
   every room of the square is inheriting this rooms
   
   coder(s):   Deinonychus
   
   $Log: square_room.c,v $
 * Revision 1.2  1994/10/05  17:01:11  brambi
 * School added
 *
   
   purpose:    centralization of items to add in a room of the square
   exits:      
   
   objects:    none
   npcs:       none
   
   quests:     none
   special:    none
   
   to do:      
   bug:        none known
*/

#include "room.h"
#pragma save_binary

inherit "/std/room";

mapping square_items = ([
  "blacksmith":
    ({
      ({ ({"house","smithy","forge","blackened house"}), "blacksmith_house" }),
      ({ ({"sign", "sign at smithy"}), "blacksmith_sign" }),
      ({ ({"chimney", "chimney of smithy"}), "blacksmith_chimney" }),
    }),

  "bakery_e":
    ({
      ({ ({"gingerbread house","house","bakery"}), "bakery_house" }),
      ({ ({"sign"}),"bakery_sign" }),
      ({ ({"painting"}),"bakery_painting_e" }),
    }),

  "bakery_w":
    ({
      ({ ({"gingerbread house","house","bakery"}), "bakery_house" }),
      ({ ({"sign"}),"bakery_sign" }),
      ({ ({"painting"}),"bakery_painting_w" }),
    }),

  "bank":
    ({
      ({ ({"bank","cube shaped building"}), "bank_house" }),
    }),

  "gate_north":
    ({
      ({ ({"gate"}), "gate_north" }),
      ({ ({"tower","towers"}), "gate_towers" }),
    }),

  "grocery":
    ({
      ({ ({"entrance", "entrance of grocery"}), "grocery_entrance" }),
      ({ ({"grocery", "empire"}), "grocery_house" }),
      ({ ({"plant", "plants", "veggy", "veggies"}), "grocery_plants" }),
    }),

  "hairdresser":
    ({
      ({ ({"house","giant bottle","giant shampoo bottle","hairdresser"}),
         "hairdresser_house"
      }),
      ({ ({"sign"}), "hairdresser_sign" }),
    }),

  "lavatory":
    ({
      ({ ({"lavatory","blue building"}), "lavatory_house" }),
    }),

  "school":
    ({
      ({ ({"school"}), "school_house" }),
    }),

  "shop":
    ({
      ({ ({"shop"}), "shop_house" }),
    }),

]);

mapping square_cmd_items = ([
  "blacksmith":
    ({
      ({ ({"sign", "sign at smithy"}), ({"read"}), "blacksmith_sign" })
    }),
  "school":
    ({
      ({ ({"inscription", "inscription on school"}), ({"read"}), 
	   "school_inscription"
      })
    }),
]);


create_square_room(){
  add_item(({"road","floor","ground"}), DESC("floor"));
  add_item(({"marble","pieces"}), DESC("marble"));
  add_item("square", DESC("square"));
  add_item("fountain", DESC("fountain"));
  add_item("statue", DESC("fountain_statue"));
  add_item(({"building", "buildings"}), DESC("buildings"));
}

add_square_items(string str){

  int i;

  mixed *items = square_items[str];

  if(items){
    for(i = 0; i < sizeof(items); i++){
      add_item(items[i][0], DESC(items[i][1]));
    }
  }

  items = square_cmd_items[str];

  if(items){
    for(i = 0; i < sizeof(items); i++){
      add_cmd_item(items[i][0], items[i][1], DESC(items[i][2]));
    }
  }
}