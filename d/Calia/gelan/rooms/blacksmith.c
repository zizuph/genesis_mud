/* Blacksmiths shop in Gelan
 * The home of Bubba the Blacksmith.
 *
 * Code adapted and modified from code in Gondor by Maniac, 7/94
 * Main body separated and moved into Bubba by Maniac, June '95
 * Updated messages, Maniac, 1/4/2000
 */

#pragma save_binary

#include "defs.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include "room.h"
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;
inherit "/lib/trade";

#define LOW(x) lower_case(x)
#define ENV environment
#define CAP(x) capitalize(x)

mapping collectables = ([ ]);
object smith;

string
read_sign()
{
   if (!smith) 
       return "CLOSED! Sorry, had to pop out for supplies. Bubba.\n";
   else
       return "OPEN! I Bubba, the blacksmith of Gelan, can offer you " +
        "many services at reasonable cost. Having learned some of " +
        "my craft from the smiths of Gondor and Krynn, I have a wide " +
        "range of strengths. I am able to make various types of armour " +
        "and polearms, and can also quickly repair all kinds of " +
        "armour and weapons. (For relevant information, try " +
        "<help bubba>).\n";
}


void
rack_for_collection(string customer, object item)
{
    mixed items;
    
    if (items = collectables[customer]) { 
        items += ({item});
        collectables = m_delete(collectables, customer);
        collectables += ([customer : items]);
    }
    else
        collectables += ([customer : ({item})]);
}


string
rack()
{
    object tp = this_player();
    mixed items;
    string nm = tp->query_real_name();
    string str = "There are various weapons and armours ready for " +
                 "collection in the rack. ";
      
    items = collectables[nm];  
    if (!items)
        str += "None of it is for you though!\n";
    else
        str += "There is the following stuff there for you " +
               "to collect: " + COMPOSITE_DEAD(items) + ". You may " +
               "collect this in one go by typing <collect>.\n"; 

    return str;
}


void 
reset_room()
{
    if (!smith || !present("bubba",TO))
    {
        smith = clone_object(GELAN_MONSTERS + "bubba");
        smith->move(TO);
        tell_room(this_object(), QCTNAME(smith) + " arrives.\n");
    }
}

public void 
create_gelan_room()
{
  set_short("The workshop of the blacksmith in Gelan");

  set_long(
    "This is the shop of the blacksmith of Gelan, Bubba Hammerhead. " +
    "The heat here is quite strong, rising from the big hot forge that " +
    "stands by the inner wall. There are armours and weapons of all " +
    "kinds on the walls, the variety and quality telling you that the " +
    "blacksmith must be a master of his profession. There is an " +
    "important looking sign near the door. There is a large rack here " +
    "containing weapons and armours that are ready for collection.\n");

  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_CLEANUP,1);

  add_item("armours",
    "There are all types of armours in here, from bracers to helms, made " +
    "from a wide range of metals.\n");

  add_item("weapons",
    "The range of weapons on display, from stiletto knives to monstrous " +
    "maces, leave you in no doubt that the blacksmith knows his profession " +
    "inside out.\n");

  add_item(({"sign","poster"}),"@@read_sign");
  add_cmd_item(({"sign","poster"}), "read", "@@read_sign");

  add_item(({"rack", "large rack"}), "@@rack");

  add_item("forge",
    "The heat from the forge is incredible, you have no understanding for "+
    "how the blacksmith manages to work under these conditions every day. "+
    "A large black anvil stands next to a large bellows, and a pair of "+
    "pliers and some hammers lie on a shelf.\n");


  add_exit(GELAN_ROOMS + "square_westend_s", "north", 0);
  add_exit(GELAN_ROOMS + "square_corner_sw", "east", 0);
  reset_room();
}



void
notify_smith_player_left(string pn)
{
  if (smith) 
      smith->player_left(pn);
}


void
leave_inv(object obj, object to)
{
  int i;
  ::leave_inv(obj,to);
  if (!interactive(obj)) return;
  set_alarmv(1.0, 0.0, "notify_smith_player_left", ({obj->query_real_name()}));
}


/* Player tries to collect stuff from the rack */
int
do_collect(string str)
{
    object tp = this_player();
    mixed items;
    object *did_move = ({ });
    string nm = tp->query_real_name();
    int i;

    if (stringp(str)) {
        notify_fail("The rack's <collect> command requires " +
                    "no argument.\n"); 
        return 0; 
    } 
      
    items = collectables[nm];  
    if (!items) {
        notify_fail("Nothing for you to collect from the rack here!\n");
        return 0;
    }
    else {
        for (i = 0; i < sizeof(items); i++) 
            if (items[i]->move(tp) == 0) 
                did_move += ({items[i]});

        if (!sizeof(did_move)) {
            write("You have items in the rack but you couldn't collect " +
                  "anything. Perhaps you should check whether your " +
                  "inventory is full?\n");
            return 1;
        }
        items -= did_move;
        collectables = m_delete(collectables, nm);
        if (sizeof(items))
            collectables += ([nm : items]);

        tp->catch_msg("You collected " + COMPOSITE_DEAD(did_move) + 
                      " from the rack.\n");
        tell_room(environment(tp), QCTNAME(tp) + " collected " +
                  COMPOSITE_DEAD(did_move) + " from the rack.\n", tp);
        return 1;
    }
}

void
init()
{
    ::init();
    add_action(do_collect, "collect");
}
