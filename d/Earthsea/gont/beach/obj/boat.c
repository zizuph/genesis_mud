inherit "/std/object";

object fisherman;

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void i_am_the_fisherman(object f) {fisherman=f;}

void create_object()
{
 set_name("boat");
 add_adj("fishing");
 set_long("This is very small fishing boat , you doubt that is good "+
   "idea to use it.\n");

 add_prop(OBJ_M_NO_GET,"Yeah , right , and put it in a pocket!\n");
 add_prop(OBJ_I_WEIGHT,100000);
 add_prop(OBJ_I_VOLUME,100000);
}

void init()
{
 ::init();
 add_action("board","board");
 add_action("board","enter");
}

int board(string what)
{
 NF("You make a step towards the boat , but suddenly realize it's "+
   "someone else's property and step back.\n");
 if(!TP->query_prop("_live_i_asked_fisheman") || 
    ENV(fisherman)!=ENV(TP)) return 0;

 NF(query_verb()+" what? Boat maybe?\n");
 if(!what || what!="boat") return 0;

 write("You "+query_verb()+" "+short()+".\n");
 say(QCTNAME(TP)+" "+query_verb()+"s "+short()+".\n");
 TP->move_living("M",INSIDE_BOAT);
 say(QCTNAME(TP)+" arrives.\n");

 (OUTSIDE)->notify_board_boat(TP);

 return 1;
}

