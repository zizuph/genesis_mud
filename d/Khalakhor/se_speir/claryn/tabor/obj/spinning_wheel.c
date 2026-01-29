//
// A spinning wheel
// With a bale of wool, the player can spin a spool of thread, wick for
// candles, or a rope.
//
// Zima 5/19/98
//
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "obj.h"
 
// constants - states of the spinning wheel and for the switch setting
#define  READY          0
#define  LOADED         1
#define  SPINNING       2
#define  DONE           3
#define  THREAD         0
#define  WICK           1
#define  ROPE           2
 
#define  WOOL_FNAME     "/d/Khalakhor/se_speir/plains/obj/wool_bale"
#define  RM             ENV(TO)
#define  TPN            QCTNAME(TP)
 
int    state;           // current stat of the wheel
int    numspins=0;      // number of spins left till product is done
int    setting=THREAD;  // setting for product to be spun
string color;           // color of the wool currently loaded
 
public string query_color() { return color; }

//
// create_object()
//
void create_object()
{
    set_name("spinning wheel");
    add_name("wheel");
    add_adj(({"new","new-fangled","spinning"}));
    set_short("spinning wheel");
    set_long("It is a one of those new-fangled spinning wheels, with a "+
             "bin on top which can be loaded with a bale of wool, and "+
             "a spindle at the bottom where the thread is wound. A large "+
             "wheel is the major component, with a long handle which can "+
             "be used to spin it. You also see a small setting switch "+
             "near the spindle, and a small note attached to the bin.\n");
 
    add_item("note","It looks hastily written and is stuck on the bin "+
       "of the spinning wheel.\n");
    add_cmd_item("note","read",
       "I'm gone a fishin' w' Ossean! Help yerself to me new-fangled "+
       "spinning wheel!\n");
    add_item(({"wheel","handle"}),
       "The large wheel is the primary mechanism of the contraption, "+
       "which takes wool placed in the bin and spins it into thread, "+
       "wick cord or rope, automatically winding the product on the "+
       "spindle at the bottom. You can spin the wheel with the handle "+
       "to operate the spinning wheel.\n");
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_NO_GET,1);
 
    // examine parts
    add_item("bin",                  "@@exa_bin");
    add_item(({"spool","spindle"}),  "@@exa_spindle");
    add_item(({"switch","setting"}), "@@exa_setting");
 
    // commands to pertaining to the bin and bale of wool
    add_cmd_item(
       ({"bin","bin with wool","bin with bale","bin with bale of wool"}),
       "load", "@@load_bin");
    add_cmd_item(
       ({"wool from bin","bale from bin","bale of wool from bin", "wool"}),
       "remove","@@remove_wool");
 
    // commands to change the switch setting
    add_cmd_item("thread", "switch", "@@switch_thread");
    add_cmd_item("wick",   "switch", "@@switch_wick");
    add_cmd_item("rope",   "switch", "@@switch_rope");
 
    // commands to spin the wool and remove the spool
    add_cmd_item(({"wheel","wheel with handle","handle"}),
       ({"crank","turn","spin"}), "@@do_spin");
    add_cmd_item(({"spool","spool from spindle"}),
       "remove", "@@rem_spool");
}
 
//
// product - return name of product of current switch
//
string product()
{
   switch (setting)
      {
      case THREAD: return "thread";
      case WICK:   return "wick";
      case ROPE:   return "rope";
      }
   return "unknown";
}
 
//
// exa_bin
//
string exa_bin()
{
   string d="The bin is just a large wooden trough on top of the "+
            "spinning wheel which funnels wool down onto the wheel. ";
   switch (state)
      {
      case READY:
         d+="One could 'load bin with wool' to prepare for spinning."; break;
      case LOADED:
         d+="A bale of wool has just been placed in it, though it could be "+
            "removed.";
         break;
      case SPINNING:
         d+="A bale of wool is now in it and is entangled with the wheel, "+
            "being spun into the product.";
         break;
      case DONE:
         d+="It is empty."; break;
      }
   return (d+"\n");
}
 
//
// exa_setting
//
string exa_setting()
{
   string d="It is a small wooden switch near the spindle which controls "+
            "the thickness of the thread being spun onto the spindle. "+
            "It is marked with 'thread', 'wick' and 'rope'. It is currently "+
            "set on '"+product()+"'.  One could 'switch thread', "+
            "'switch wick', or 'switch rope' on it.\n";
   return d;
}
 
//
// exa_spindle
//
string exa_spindle()
{
   string d="The spindle is just a smooth thin wooden cylinder set "+
            "near the bottom of the spinning wheel. Thread spun by "+
            "the wheel is wound around the spindle in a spool. ";
   switch (state)
      {
      case READY:
      case LOADED:
           d+="There is nothing on it."; break;
      case SPINNING:
           d+="There is part of a spool of "+product()+" on it, but it is "+
              "not finished.";
           break;
      case DONE:
         d+="There is a completed spool of "+product()+" on it, ready "+
            "to be removed.";
         break;
      }
   return (d+"\n");
}
#include "spinning_wheel.inc"
