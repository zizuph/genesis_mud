
/*
     This is the server for the Zintra BlackHand Order of Assassins
     guild.  It will handle the names and skills that the Assassins
     gain over time.
  
     => DONE <=                            ~Rico 12.04.96
*/

#pragma strict_types
#pragma no_inherit

inherit "/d/Kalad/room_std";

#include "/d/Kalad/common/zintra/specials/defs.h"

#define ORDER    "/d/Kalad/common/zintra/specials/orders"

public void set_order_name(string name, string player);
public void remove_order_name(string player);
public string query_order_name(string player);
private mapping orders = ([ ]);

void
create_room()
{
   set_short("A dark, confined hole in the ground");
   set_long("\nA dark, confined hole in the ground.  There is barely "+
      "enough room for an average sized dwarf to stand up in here.  "+
      "How in the name of all the known Gods a mortal is expected to "+
      "get in here is a complete mystery to you.\n\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, -1);

   if(!restore_object(ORDER))
   {
      clans = ([ ]);
   }
}

public void
set_order_name(string name, string player)
{
   if (!mappingp(orders))
      orders = ([ ]);

   if (member_array(player, m_indexes(orders)) >= 0)
      return;

   orders[player] = name;
   save_object(ORDER);

   return;
}

public string
query_order_name(string player)
{
   if (!mappingp(orders))
      orders = ([ ]);

   if (member_array(player, m_indexes(orders)) < 0)
      return "";

   return orders[player];
}

public void
remove_order_name(string player)
{
   if (!mappingp(orders))
      orders = ([ ]);

   if (!orders[player])
      return;

   orders = m_delete(orders, player);

   save_object(ORDER);

   return;
}

