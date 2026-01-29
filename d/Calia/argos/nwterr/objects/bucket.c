inherit "std/object";
#include <stdproperties.h>
 
void
create_object()
{
    set_name(({"_argos_shepherds_bucket","bucket"}));
    set_adj("wooden");
    set_short("wooden bucket");
    add_prop("_argos_shepherds_bucket_full",0);  /* empty */
    set_long("@@exa_bucket");
 
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 400);
}
 
string
exa_bucket() {
   if (this_object()->query_prop("_argos_shepherds_bucket_full"))
      return break_string("It is a simple wooden bucket with a lamb " +
                          "whittled on the side. It is full of water. " +
                          "You wonder what you might pour the water " +
                          "into.\n",70);
   else
      return break_string("It is a simple wooden bucket with a lamb " +
                          "whittled on the side. It is empty.\n",70);
}
