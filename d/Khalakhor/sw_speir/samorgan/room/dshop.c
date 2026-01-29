/**********************************************************************
 * - dshop.c                                                        - *
 * - Dress shop in Samorgan                                         - *
 * - Created by Damaris@Genesis 08/2005                             - *
 * - Cleaned up and optimized by Tapakah, 06/2021                   - *
 **********************************************************************/
#pragma strict_types

#include "../defs.h"

inherit SM_SHOP_BASE;

public int *
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
         "          | `              SaMorgan Dress Shop            ` |\n"+
         "          | `            Arinia Estel Proprietor          ` |\n"+
         "          | `       *`----------------------------`*      ` |\n"+
         "          | `                                             ` |\n"+
         "          | `                                             ` |\n"+
         "          | `     This dress shop proudly supplies the    ` |\n"+
         "          | `     much  needed  stylish  and practical    ` |\n"+
         "          | `     clothing  for  women   in  SaMorgan.    ` |\n"+
         "          | `                                             ` |\n"+
         "          | `     To  see  what  items  are  for  sale    ` |\n"+
         "          | `     please use <list>.                      ` |\n"+
         "          | `                                             ` |\n"+
         "          | `       We do not  buy  items only sell.      ` |\n"+
         "          | `        Thank you for  your patronage.       ` |\n"+
         "          | `                                             ` |\n"+
         "          | `                                             ` |\n"+
         "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
         "          *--------------------*` - - `*--------------------*\n");
}

void
configure_shop ()
{
  set_short("A quaint dress shop");
  set_long("\n   This is a small shop that has been tastefully "+
           "decorated with ribbons and fabrics in a very quaint "+
           "manner. There are racks of many different types of dresses "+
           "and gowns that line two walls. There is also a small "+
           "sign next to a small counter.\n");
  add_exit("vil0504", "south");
  smell = "The sweetest smell of jasmine soothes your senses.\n";
  is_buyer = SHOP_BUYS_NONE;
  add_item(({"wall", "walls"}),
           "The walls are light coloured with lanterns and ribbons "+
           "placed in various spots.\n");
  add_item(({"counter", "small counter"}),
           "It is a small counter light in colour with bows, ribbons and "+
           "a small sign placed on it.\n");
  add_item(({"ribbon", "ribbons"}),
           "There are ribbons of many different colours that have been "+
           "draped and tied into bows along the counter and walls in "+
           "here.\n");
  add_item(({"bow", "bows"}),
           "Some ribbons have been tired into attractively festive bows.\n");
  add_item(({"fabric", "fabrics", "cloth", "cloths"}),
           "There are richly coloured fabrics in many different styles "+
           "draped elegantly around the room.\n");
  add_item(({"rack", "racks"}),
           "There are racks lined along two walls filled with many "+
           "different styles of clothing on them.\n");
  add_item(({"first rack"}),
           "The first rack is filled with clothing for gentleman.\n");
  add_item(({"second rack"}),
           "The second rack has been filled with clothing for women.\n");
  add_item(({"clothes", "clothing", "womens clothing"}),
           "There are too many clothes to look just look at, it might be "+
           "easier to 'list' them.\n");
  add_item(({"blue bow", "blue bows"}),
           "There are a few festive blue ribbons that have been elaborately "+
           "tied together to form a bow.\n");
  add_item(({"red bow", "red bows"}),
           "There are a few festive red ribbons that have been elaborately "+
           "tied together to form a bow.\n");
  add_item(({"yellow bow", "yellow bows"}),
           "There are a few festive yellow ribbons that have been "+
           "elaborately tied together to form a bow.\n");
  add_item(({"white bow", "white bows"}),
           "There are a few festive white ribbons that have been "+
           "elaborately tied together to form a bow.\n");
  add_item(({"green bow", "green bows"}),
           "There are a few festive green ribbons that have been "+
           "elaborately tied together to form a bow.\n");
  add_item(({"peach bow", "peach bows"}),
           "There are a few festive peach ribbons that have been "+
           "elaborately tied together to form a bow.\n");

}    
