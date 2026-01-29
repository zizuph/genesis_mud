/**********************************************************************
 * - ftunic.c                                                       - *
 * - Tunic for females to be purchased in female shop in SaMorgan.  - *
 * - Created by Damaris@Genesis 05/2006                             - *
 * - Cleaned up and optimized by Tapakah, 06/2021                   - *
 **********************************************************************/

#pragma strict_types

#include <macros.h>
#include <wa_types.h>

#include "../defs.h"

inherit SM_DRESS_CLOTH;

string tag_text = "The tag reads:\n"+
  "Made in SaMorgan.\n"+
  "You may <tug tunic>, <brush tunic>, <adjust tunic>\n";

void
configure_armour ()
{
  set_name("tunic");
  add_cmd_item("tag", "read", tag_text);
  sizes  = ({ "long", "short" });
  styles = ({
    "faded", "warm", "clean", "vivid", "sharp", "pale",
    "colourful", "bold", "lustrous", "deep", "brilliant",
    "flashy", "fresh", "florid", "distinctive", "soft",
    "crisp", "distinct", "plain", "cotton", "smooth",
    "comfortable", "sensible",
  });
  colors = ({
    "white", "yellow", "blue-green", "scarlet", "red",
    "blue", "sapphire", "green", "black",
  });
  configure_desc();
  set_long("This " + short() + " is a loose-fitting garment "+
           "that is worn by commoners and nobles alike. There is a small "+
           "tag sewn in the underside.\n");
  set_at(A_BODY);
}

int
tug_tunic (string str)
{
  return act_cloth("tug", str,
                   "You discreetly tug on the hem of your tunic.\n",
                   QCTNAME(TP)+" discreetly tugs on the hem of "+
                   HIS +" tunic.\n");
}

int
brush_tunic(string str)
{
  act_cloth("brush", str,
            "You brush the dirt from your tunic.\n",
            QCTNAME(TP)+" brushes the dirt from "+ HIS +" tunic.\n");
}

int
adjust_tunic(string str)
{
  act_cloth("adjust", str,
            "You adjust your tunic.\n",
            QCTNAME(TP)+" adjusts "+ HIS +" tunic.\n");
}

void
init ()
{
  ::init();
  add_action(tug_tunic, "tug");
  add_action(brush_tunic, "brush");
  add_action(adjust_tunic, "adjust");
}
