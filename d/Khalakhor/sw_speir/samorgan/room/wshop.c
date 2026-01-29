/*********************************************************************
 * - wshop.c                                                       - *
 * - Created by Damaris 7/2005                                     - *
 * Typo fixed by Gronkas Jan. 4, 2017: isn't --> is not because
 * some apostroph were no ASCII chars
 * - Cleaned up and optimized by Tapakah, 06/2021                  - *
 *********************************************************************/

#pragma strict_types

#include "../defs.h"

inherit SM_SHOP_BASE;

int *
query_local_coords ()
{
  return ({5, 9});
}

string
query_shop_sign ()
{
  return("          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
         "          |            SaMorgan Weaponry           |\n"+
         "          |         Emmit Konner Proprietor        |\n"+
         "          |________________________________________|\n"+
         "          |                                        |\n"+
         "          | Emmit proudly  supplies  SaMorgan with |\n"+
         "          | needed weapons and has also been known |\n"+
         "          | to purchase  weapons if they  meet his |\n"+
         "          | standards                              |\n"+
         "          |                                        |\n"+
         "          |                                        |\n"+
         "          | This shop operates like  any shop.  To |\n"+
         "          | see  what  items are  for sale  please |\n"+
         "          | use <list>.                            |\n"+
         "          |                                        |\n"+
         "          | You may also:                          |\n"+
         "          | cost <weapon/armour> for an estimate   |\n"+
         "          | sharpen <weapon> to sharpen the dull   |\n"+
         "          | wax <weapon>     to fix the rust       |\n"+
         "          |                                        |\n"+
         "          | We do not buy armours or non-weapons   |\n"+
         "          |                                        |\n"+
         "          |      Thank you for your patronage.     |\n"+
         "          |                                        |\n"+
         "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}

void
configure_shop ()
{
  object ob;
  set_short("SaMorgan Weaponry");
  set_long("   This small but quaint weaponry shop is a "+
           "necessity for the small village of SaMorgan. The walls "+
           "are lined up with different sheets of metal, moldings "+
           "and fittings. Through the breezeway a large forge can "+
           "be seen from here but it is quite obvious that only the "+
           "proprietor is allowed access. There is not much else to "+
           "see other than a couple of workbenches and a sign posted "+
           "next to a large counter.\n");
  add_exit("vil0704", "north");
  add_exit("vil0705", "northeast");
  smell = "The pungent smell of oils mingled with metal is everywhere.\n";
  is_buyer = SHOP_BUYS_WEP;
  is_smith = 1;

  add_item(({"wall", "walls"}),
           "The walls are light coloured with weapons scattered on "+
           "wooden displays.\n");
  add_item(({"counter", "large counter"}),
           "It is a large counter that has scratches all over it's "+
           "surface and a sign placed next to it.\n");
  add_item(({"rack", "racks"}),
           "There are racks lined along two walls filled with many "+
           "different styles of weapons.\n");
  add_item(({"first rack"}),
           "The first rack is filled with daggers and small whips.\n");
  add_item(({"second rack"}),
           "The second rack has been filled with swords and polearms.\n");
  add_item(({"bell", "small bell", "brass bell"}),
           "It is a small brass bell.\n");
  add_item(({"bin", "storage bin"}),
           "This is a special storage bin that looks as if it has been "+
           "filled with a special oil to soak weapons in.\n");
  add_item(({"workbench", "workbenches"}),
           "There are a couple of workbenches here with newly fashioned "+
           "weapons on them.\n");
  add_item(({"new weapons"}),
           "Please <read sign>.\n");
  add_item(({"breezeway"}),
           "Through the breezeway there can be seen a large forege.\n");
  add_item(({"southwest"}),
           "There is a breezeway in that direction that leads to the "+
           "forge.\n");
  add_item(({"forge"}),
           "The forge can be seen through the breezeway.\n");    
}
