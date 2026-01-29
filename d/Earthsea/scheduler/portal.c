inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void create_object()
{
 set_name("portal");
 add_name("_invation_portal_");
 set_adj("bright");
 add_adj("red");

 set_long("Dangerously looking portal. It seems to lead to some "+
   "other dimention. You do not dare to enter it.\n");

 add_prop(OBJ_I_NO_GET,"You try to put your hands on a portal, "+
   "but they just pass through it.\n");

 add_cmd_item("portal","enter","@@enter_portal");
}

int enter_portal()
{
 write("As you try to make a step into a portal, you are thrown "+
   "away by some kind of force field!\n");
 say(QCTNAME(TP)+" is thrown away by portal's force field.\n");
 
 return 1;
}

void open_portal(object where)
{
 tell_room(where,"With a low, humming noice "+short()+" opens here!\n");
 move(where);
}

void close_portal()
{
 tell_room(ENV(TO),"Portal starts to shrink, and soon it closes "+
       "into small point that quickly disappears.\n");
 remove_object();
}

