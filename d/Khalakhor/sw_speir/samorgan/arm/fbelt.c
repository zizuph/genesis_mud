/**********************************************************************
 * - fbelt.c                                                        - *
 * - Belts for females to be purchased in female shop in SaMorgan.  - *
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
  "You may <tug belt>, <brush belt>, <adjust belt>\n";

void
configure_armour ()
{
  set_name("belt");
  sizes  = ({ "wide", "narrow" });
  styles = ({
    "faded", "warm", "clean", "vivid", "sharp", "pale",
    "colourful", "bold", "lustrous", "deep", "brilliant",
    "flashy", "fresh", "florid", "distinctive", "soft",
    "crisp", "distinct", "plain", "cotton", "smooth",
    "comfortable", "sensible"
  });
  colors = ({
    "white", "yellow", "blue-green", "scarlet", "red",
    "blue", "sapphire", "green", "black",
  });
  configure_desc();
  set_long("This " + short() + " is usually worn around tunics. "+
           "There is a small tag sewn in the underside.\n");
  add_cmd_item("tag", "read", tag_text);
  set_at(A_WAIST);
}

int
tug_belt (string str)
{
  return act_cloth("tug", str,
                   "You discreetly tug on edge of your belt.\n",
                   QCTNAME(TP)+" discreetly tugs on the edge of "+
                   HIS +" belt.\n");
}

int
brush_belt (string str)
{
  return act_cloth("brush", str,
                   "You brush the dirt from your belt.\n",
                   QCTNAME(TP)+" brushes the dirt from "+
                   HIS +" belt.\n");
}

int
adjust_belt (string str)
{
  return act_cloth("adjust", str,
                   "You adjust your belt.\n",
                   QCTNAME(TP)+" adjusts "+ HIS +" belt.\n");
}

void
init ()
{
  ::init();

  add_action(tug_belt,    "tug");
  add_action(brush_belt,  "brush");
  add_action(adjust_belt, "adjust");
}
