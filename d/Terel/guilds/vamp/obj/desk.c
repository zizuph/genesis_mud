//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:

inherit "/std/container";
#include "../defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>


void
fill_desk()
{
    reset_euid();

    clone_object(OBJ_DIR +"quill")->move(TO, 1);
    clone_object(OBJ_DIR +"bowl")->move(TO, 1);
    clone_object(OBJ_DIR +"blotter")->move(TO, 1);
    clone_object(OBJ_DIR +"inkpot")->move(TO, 1);
}

int
special_sort(object a, object b)
{
    int v1, v2;

    v1 = a->query_prop(OBJ_I_VOLUME);
    v2 = b->query_prop(OBJ_I_VOLUME);

    if(v1 == v2)
        return 0;
    if (v1 < v2)
        return 1;
    if (v1 > v2)
        return -1;
}

string
external_within()
{
  object *stuff;
  string str = "";

  stuff = FILTER_DEAD(all_inventory(TO));
  if(!sizeof(stuff))
   return str + ".";
  else if(sizeof(stuff) <= 5)
   return str + "Upon the desktop lies " + COMPOSITE_DEAD(stuff) + "";
  else
   return str + "There are several things on the desktop, including "
      + COMPOSITE_DEAD(stuff) + "";
}

string within()
{
  object *stuff;
 
  if(!query_prop(CONT_I_CLOSED))
   return "";

  stuff = FILTER_DEAD(all_inventory(TO));
  if(!sizeof(stuff))
   return " The desktop is covered with a fine layer of dust";
  else
   return " Resting on the desktop is "
      +COMPOSITE_DEAD(stuff)+"";
}

public void
create_container()
{
    set_name("desk");
    set_adj(({"wood","old", "wooden", "antique"}));
    set_short("antique wood desk");
    set_long("An old wooden desk, so ancient that even the adjective "+
        "antique seems too new to describe its antiquity. The wood is "+
        "very dark brown, and the finish has crackled with age. "+
        "@@within@@. There is a central drawer underneath the desktop.\n");
    add_item(({"desktop", "desk top"}), "@@within@@");
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 12000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "It cannot be moved.\n");
    set_no_show_composite(1);  //don't want it to show up in room desc.
    seteuid(getuid());
    fill_desk();
}

