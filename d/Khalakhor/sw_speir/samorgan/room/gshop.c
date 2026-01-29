/**********************************************************************
 * - gshop.c                                                        - *
 * - General purpose shop.                                          - *
 * - Created by Damaris@Genesis 04/2006                             - *
 * - Cleaned up and optimized by Tapakah, 06/2021                   - *
 **********************************************************************/
#pragma strict_types

#include "../defs.h"

inherit SM_SHOP_BASE;

int *
query_local_coords ()
{
  return ({4, 5});
}

string
query_shop_sign ()
{
  return("\n"+
         "          *--------------------*` - - `*--------------------*\n"+
         "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
         "          | `                                             ` |\n"+
         "          | `            SaMorgan General Shop            ` |\n"+
         "          | `          Drew Flannagan Proprietor          ` |\n"+
         "          | `       *`----------------------------`*      ` |\n"+
         "          | `                                             ` |\n"+
         "          | `                                             ` |\n"+
         "          | `   This general  shop  proudly serves  the   ` |\n"+
         "          | `   villagers of SaMorgan with their needs.   ` |\n"+
         "          | `                                             ` |\n"+
         "          | `   This  shop  operates   like  any  shop.   ` |\n"+
         "          | `   To see the items  for sale, use <list>.   ` |\n"+
         "          | `                                             ` |\n"+
         "          | `                                             ` |\n"+
         "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
         "          *--------------------*` - - `*--------------------*\n");
}

void
configure_shop ()
{
  set_short("A small dimly lit shop");
  set_long("\n   A small dimly lit shop with a small counter in "+
           "one corner and a set of wooden shelves in the other. Upon the "+
           "far wall between the two is a small sign. The wooden floor is "+
           "scuffed up with quite a build up of dirt and grime.\n");
  add_exit("vil0505", "south");
  smell = "The slight smell of fabric, oil and leather floats around you.";

  add_item(({"sign"}), query_shop_sign);
  add_item(({"shop", "room", "area"}), query_long);
  add_item(({"wall", "walls"}),
           "The walls are dusty and slightly grimy.\n");
  add_item(({"counter", "small counter"}),
           "It is a small counter light in colour that has darkened with "+
           "wear.\n");
  add_item(({"shelves", "shelf"}),
           "To see what is there try to <list> them.\n");
  add_item(({"floor", "flooring"}),
           "the floor is made of wood and a bit dingy and dirty.\n");
  add_item(({"wood", "wooden"}),
           "The floor, counter and shelves are made from wood.\n");
}    
