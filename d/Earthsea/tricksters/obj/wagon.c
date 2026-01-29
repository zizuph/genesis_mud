inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

void create_object()
{
 set_name("wagon");
 add_name("_trick_wagon_");
 set_adj("rusty");
 add_adj("iron");
 add_prop(OBJ_M_NO_GET,"Well , yeah , are you Arnold Shwartseniger?\n");
 add_prop(OBJ_I_WEIGHT,2000000);
 add_prop(OBJ_I_VOLUME,2000000);
 set_long("This is old rusty wagon Tricksters use for transportation "+
   "to Gont city. Just board the wagon if you want to use it.\n");
}

void init()
{
 ::init();
 add_action("board","board");
 add_action("board","enter");
}

int board(string what)
{
 NF(C(query_verb())+" what? The wagon maybe??\n");
 if(!what) return 0;
 if(what!="wagon") return 0;

 say(QCTNAME(TP)+" "+query_verb()+"s the wagon.\n");
 TP->move_living("M",INSIDE_WAGON);
 say(QCTNAME(TP)+" arrives from outside.\n");
 return 1;
}

