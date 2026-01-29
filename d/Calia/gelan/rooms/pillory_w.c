/* 	this is a room of the town Gelan

    coder(s):   Merlin & Maniac

    history:     7.10.95    sell rotten veg for pillory     Maniac 
                  7.9.94    description added               Maniac
                20. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;

/* For each item: listing name, price in cc, buying names, path */
mixed for_sale = 
   ({ 
       ({
          "squashy tomato", 
          3, 
          ({"squashy tomato", "tomato", "rotten tomato"}),
          GELAN_OBJECTS+"squashy_tomato"
        }), 
    });

string for_sale_message;

public void
create_gelan_room()
{
    int i;

    /* descriptions */

    set_short("Pillory store");
    set_long("You are standing just to the west of the pillory in Gelan. "
      + "In front of you is a little store that sells rotten fruit and " 
      + "vegetables, which are of course indispensible items in the famed " 
      + "pastime of prisoner pelting. You may <list> stuff available here " 
      + "and <buy> it cheaply. " 
      + "A fair way to your south is the fountain of Gelan. You also " 
      + "see many buildings all around the town square.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_northend_center_w","north",0);
    add_exit(GELAN_ROOMS + "square_central_w","south",0);
    add_exit(GELAN_ROOMS + "square_nw","west",0);
    add_exit(GELAN_ROOMS + "pillory_e","east",0);
    add_exit(GELAN_ROOMS + "square_northend_w","northwest",0);
    add_exit(GELAN_ROOMS + "square_northend_center_e","northeast",0);
    add_exit(GELAN_ROOMS + "square_midw","southwest",0);
    add_exit(GELAN_ROOMS + "square_central_e","southeast",0);

    /* items in the room */

    add_item(({"store", "little store"}), "A little store that sells " +
         "rotten fruit and vegetables to pelt prisoners in the pillory " +
         "with. You may <list> what's available and <buy> it cheaply.\n"); 
    add_item("pillory", VBFC_ME("pillory_desc")); 
    add_item(({"buildings", "building"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}), DESC("floor"));
    add_item("fountain", DESC("fountain"));

    for_sale_message = "For sale at the pillory store:\n";
    for (i = 0; i < sizeof(for_sale); i++) {
        for_sale_message += "   "; 
        for_sale_message += 
                     (for_sale[i][0] + ", " + for_sale[i][1] + " cc.\n");
    }
    for_sale_message += "\n";

} /* create_room */



/* Give the pillory desc from the neighbouring room */
string
pillory_desc()
{
    return ((GELAN_ROOMS + "pillory_e")->pillory_desc());
}


/* Action to list things the store sells */
int
do_list()
{
    object tp = this_player();

    tp->catch_msg(for_sale_message);
    return 1;
}


/* Action to buy stuff on the list */
int
do_buy(string str)
{
    object tp = this_player();
    object item;

    int i, j, found;

    if (!stringp(str)) {
        notify_fail("Buy <item name>.\n");
        return 0;
    }

    found = -1;
    while ((i < sizeof(for_sale)) && (found == -1))  {
        for (j = 0; j < sizeof(for_sale[i][2]); j++)
            if (for_sale[i][2][j] == str) 
                found = i;
        i++;
    }

    if (found == -1) {
        notify_fail("No items by that name are sold here.\n");
        return 0;
    }

    if (MONEY_ADD(tp, -for_sale[found][1])) {
        item = clone_object(for_sale[found][3]);  
        tell_room(this_object(), QCTNAME(tp) + " buys " + 
                  LANG_ASHORT(item) + ".\n", tp);
        tp->catch_msg("You buy " + LANG_ASHORT(item) + ".\n");
        if (item->move(tp) != 0) {
            tp->catch_msg("Oops, you have to drop it as you can't carry " +
                          "any more.\n");
            tell_room(this_object(), capitalize(tp->query_pronoun()) + 
                          " has to drop it as " + tp->query_pronoun() +
                          " can't carry any more.\n", tp);
            item->move(environment(tp));
        }
        return 1;
    }
    notify_fail("Hmm, not enough money?\n");
    return 0;
} 


void
init()
{
    ::init();
    add_action(do_buy, "buy");
    add_action(do_list, "list");
}
