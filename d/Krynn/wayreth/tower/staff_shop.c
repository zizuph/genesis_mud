/* Staff Maker of Wayreth
 * based on Gelan's Bubba.
 *
 * 
 * 
 */

#pragma save_binary
#include "/d/Krynn/wayreth/local.h"

inherit TOWERROOM;
inherit "/lib/trade";
#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>

#define LOW(x) lower_case(x)
#define ENV environment
#define CAP(x) capitalize(x)

mapping collectables = ([ ]);
object smith;

string
read_sign()
{
   if (!smith) 
       return "CLOSED! Will return later.\n";
   else
       return "OPEN! I am selling staves, designing staves, and " +
	"storing staves for members. \n";
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
    if (!smith || !present("keshir",TO))
    {
        smith = clone_object("/d/Krynn/wayreth/npc/staffmaker");
        smith->move(TO);
        tell_room(this_object(), QCTNAME(smith) + " arrives.\n");
    }
}

void 
create_tower_room()
{
  set_short("The workshop of the Tower's staff maker");

  set_long(
    "This is an amazing place with a pair of racks for holding staves, "+
    "a forge, a woodworking table, and a table with arcane equipment. "+
    "There is a sign on the wall for more help.\nThis extra line is "+
    "not to be removed until the creater is happy with the add_items.\n");

  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_CLEANUP,1);

  add_item(({"sign","poster"}),"@@read_sign");
  add_cmd_item(({"sign","poster"}), "read", "@@read_sign");

  add_item(({"rack", "staff rack", "weapon rack"}), "Which rack do you "+
	"want to look at? The ready rack, or the storage rack?\n");
  add_item("ready rack", "@@rack");
  add_item("storage rack", "@@storage_rack");

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
do_collect()
{
    object tp = this_player();
    mixed items;
    object *did_move = ({ });
    string nm = tp->query_real_name();
    int i;
      
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
            notify_fail("You collected nothing.\n");
            return 0;
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
    add_action("do_collect", "collect");
}
