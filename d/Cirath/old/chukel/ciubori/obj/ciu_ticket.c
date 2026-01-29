#include "defs.h"
inherit "/std/object";

query_recover()
{
  string name;
  int i;
  sscanf(file_name(this_object()),"%s#%d", name, i);
  return name;
}
create_object()
{
  set_short("hotel ticket");
  set_long("This is a ticket granting you a good night rest at "+
            "'Ciubori City Hotel'.\n");
  
  set_adj("hotel");
  set_name("ticket");
  add_name("ciuboribille");
}
