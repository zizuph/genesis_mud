//
// A candlewraught - used to make candles
// With a spool of wick cord and honeycombs (optional ground herbs),
//    a player can handmake candles.
//
// Zima 5/22/98
//
// 2021-09-27 - Cotillion
// - Fixed excess add_item issue
//
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "powder.h"
#include "defs.h"
 
// constants - state of the candlewraught
#define  READY            0
#define  HAS_WICK         1
#define  HAS_COMB         2
#define  HEATING          3
#define  HOT              4
#define  POURED           5
#define  COOLING          6
#define  DONE             7
 
#define  HEAT_COOL_TIME   60.0
#define  RM               ENV(TO)
#define  TPN              QCTNAME(TP)
 
#include "candle_herbs.h"
 
string
longd="It is a small wood and metal machine used to make a hand-made "+
      "candle. Built in a cubic wooden box frame, the candlewraught "+
      "has a metal vat in which wax is melted over a small fire pit "+
      "filled with burning coals. There is a spigot on the bottom of "+
      "the vat, which allows hot wax to be emptied into the mold. "+
      "A small plaque with instructions is nailed to the frame.\n";
 
int    state    = READY;  // current state of the machine
string herb     = "";     // powdered herb that's been added
string color    = "";     // color of wax, caused by added herbs
string wcolor   = "";     // color of the wick
 
//
// change_state()
//
void change_state(int newstate)
{
   string d,colored;
   string p = "The coals are cool.";
   string v = "It is empty.";
   string m = "There is a wick threaded through it.";
 
   state=newstate;
   if (strlen(color)) colored=color+" "; else colored="";
   switch (state)
      {
      case READY:
           d="It is empty and the coals are cool.\n";
           m="It is empty.";
           break;
      case HAS_WICK:
           d="There is a wick threaded in the mold. The vat is empty and "+
             "the coals are cool.\n";
           break;
      case HAS_COMB:
           d="There is honeycomb in the vat and a wick in the mold. "+
             "The coals are cool.\n";
           v="There is a honeycomb in it.";
           break;
      case HEATING:
           d="There is a melting honeycomb floating in liquid wax in "+
             "the vat and a wick in the mold. The coals are hot.\n";
           p="The coals are burning.";
           v="There is a melting honeycomb floating in liquid wax in it.";
           break;
      case HOT:
           d="There is liquid "+colored+"wax in the vat and a wick "+
             "in the mold. The coals are hot.\n";
           p="The coals are burning.";
           v="It is filled with hot liquid "+colored+"wax.";
           break;
      case POURED:
           d="There is liquid "+colored+"wax and a wick in the mold, "+
             "kept warm by the hot coals. The vat is empty.\n";
           p="The coals are burning.";
           m="It is filled with hot liquid "+colored+"wax with a wick "+
             "threaded through it.";
           break;
      case COOLING:
           d="Hot "+colored+"wax is cooling around a wick in the mold. The "+
             "vat is empty and the coals are cooling.\n";
           p="The coals are out and cooling.";
           m="There is hot "+colored+"wax cooling around a wick in it.";
           break;
      case DONE:
          d="There is a "+colored+"candle in the mold. The vat is empty "+
            "the coals are cool.\n";
          m="There is a "+colored+"candle in it.";
          break;
      default:
         d=v=d=m="It seems to be broken!\n";
      }
    set_long(longd+d);

    remove_item("pit");
    add_item(({"pit","fire pit","coal","coals","fire"}),
       "It is a small metal pan just below the vat. It contains "+
       "coals which heat the metal vat above. "+p+"\n");

    remove_item("vat");
    add_item("vat",
       "The vat of the candlewraught is a V-shaped pan in which "+
       "the ingredients are dropped to make the candle. It is heated "+
       "by the hot coals in the fire pit touching it along its bottom. "+
       "A spigot on one end can be opened to drain the contents of the "+
       "vat into the mold. "+v+"\n");

    remove_item("mold");
    add_item("mold",
       "The mold is a hollow cylindrical piece in the shape of a "+
       "candle. It is made of very smooth wood and has a small hole "+
       "at the lower end through which a wick is threaded. The mouth "+
       "of the mold is just under the spigot of the vat. "+m+"\n");
}
 
//
// create_object()
//
void create_object()
{
    set_name("candlewraught");
    add_name(({"contraption","machine","wraught"}));
    add_adj(({"small","candle"}));
    set_short("candlewraught");
    change_state(READY);
 
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_NO_GET,1);
 
    add_item("frame",
       "The frame of the candlewraught is made of planks of polished "+
       "stained wood constructed in the form of a box with all open "+
       "sides. Wood and metal poles hold the fire pit, vat, and mold "+
       "in place.\n");
    add_item("spigot",
       "The spigot is on the bottom of the vat, placed right over "+
       "the mold. It can be opened to allow melted wax to drain out "+
       "and fill the mold.\n");
    add_item("plaque",
       "It is nailed to the frame. Perhaps you can read it.\n");
    add_cmd_item(({"plaque","instructions"}),"read",
       "+---------------------------------------+\n"+
       "| Needed: wick and beeswax honeycomb    |\n"+
       "| - thread wick through hole in mold    |\n"+
       "| - drop honeycomb in vat               |\n"+
       "| - light coals                         |\n"+
       "| Once the wax is melted:               |\n"+
       "| - drop powder in vat (optional scent) |\n"+
       "| - open spigot                         |\n"+
       "| - extinguish coals                    |\n"+
       "| Allow the candle to cool:             |\n"+
       "| - take candle from mold               |\n"+
       "| Or to start over anytime:             |\n"+
       "| - empty candlewraught                 |\n"+
       "+---------------------------------------+\n");
 
   add_cmd_item("wick through hole in mold","thread","@@thread");
   add_cmd_item("honeycomb in vat",   "drop",        "@@drop_comb");
   add_cmd_item("coals",              "light",       "@@light_coals");
   add_cmd_item("powder in vat",      "drop",        "@@drop_powder");
   add_cmd_item("spigot",            "open",        "@@open");
   add_cmd_item("coals",              "extinguish",  "@@extinguish");
   add_cmd_item("candle from mold",   "take",        "@@take");
   add_cmd_item("candlewraught",      "empty",       "@@empty");
}
#include "cwraught.inc"
