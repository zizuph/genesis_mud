/*********************************************************************
 * - ashop.c                                                       - *
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
  return ({5, 13});
}

string
query_shop_sign ()
{
  return("          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
         "          |            SaMorgan Armoury            |\n"+
         "          |        Martin Keller Proprietor        |\n"+
         "          |________________________________________|\n"+
         "          |                                        |\n"+
         "          | Martin proudly  supplies SaMorgan with |\n"+
         "          | needed armours and has also been known |\n"+
         "          | to purchase  armours if  they meet his |\n"+
         "          | standards                              |\n"+
         "          |                                        |\n"+
         "          | This shop  operates like  any shop. To |\n"+
         "          | see  what items  are for  sale  please |\n"+
         "          | use <list>.                            |\n"+
         "          |                                        |\n"+
         "          | You may also:                          |\n"+
         "          | cost <weapon/armour> for an estimate   |\n"+
         "          | mend <armour>       to fix the dents   |\n"+
         "          |                                        |\n"+
         "          | We do not buy weapons or non-armours   |\n"+
         "          |                                        |\n"+
         "          |      Thank you for your patronage.     |\n"+
         "          |                                        |\n"+
         "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}

void
configure_shop ()
{
  object ob;
  set_short("SaMorgan Armoury");
  set_long("   This is a small but quaint armoury. The walls "+
           "are lined up with different sheets of metal, moldings and "+
           "fittings. Through the breezeway a large forge can be seen "+
           "from here but it is quite obvious that only the proprietor "+
           "is allowed access. There is not much else to see other "+
           "than a couple of workbenches and a sign posted next to a "+
           "large counter.\n");
  add_exit("vil0705", "northwest");
  add_exit("vil0706", "north");
  smell = "The pungent smell of oils mingled with metal is everywhere.\n";
  is_buyer = SHOP_BUYS_ARM;
  is_smith = 1;

  add_item(({"wall", "walls"}),
           "The walls are light coloured with armours scattered on "+
           "wooden displays.\n");
  add_item(({"counter", "small counter"}),
           "It is a large counter that has scratches all over it's "+
           "surface and there is a sign placed next to it.\n");
  add_item(({"rack", "racks"}),
           "There are racks lined along two walls filled with many "+
           "different styles of armours, sheets of metals, moldings and "+
           "fittings.\n");
  add_item(({"first rack"}),
           "The first rack is filled with mails and leathers.\n");
  add_item(({"second rack"}),
           "The second rack has been filled with platemails.\n");
  add_item(({"bell", "small bell", "brass bell"}),
           "It is a small brass bell.\n");
  add_item(({"metals", "metal"}),
           "There are sheets of metal lined up along the wall.\n");
  add_item(({"fitting", "fittings"}),
           "There are fittings laying on the workbench and some haging "+
           "on the wall.\n");
  add_item(({"molding", "moldings"}),
           "Moldings of different shapes and sizes are hanging on the "+
           "wall and there are a few seen out in the forge.\n");
  add_item(({"breezeway"}),
           "Through the breezeway there can be seen a large forege.\n");
  add_item(({"northwest", "north"}),
           "The village is back out in that direction.\n");
  add_item(({"southwest", "southeast", "northeast", "west"}),
           "There is a wall in that direction.\n");
  add_item(({"south"}),
           "The storeroom is in that direction.\n");
  add_item(({"east"}),
           "There is a breezeway in that direction that leads to the "+
           "forge.\n");
  add_item(({"forge"}),
           "The forge can be seen through the breezeway.\n");
}
