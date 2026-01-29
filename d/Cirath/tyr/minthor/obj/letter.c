inherit "/std/object";
#include "/d/Cirath/common/defs.h"

void
create_object()
{
    set_short("wrinkled letter");
    set_long("This is a letter on a rough parchment that looks as if it "
	+"was crumpled up.  You also notice traces of burn marks on it.  "
	+"You could probably read it if you wanted to.\n");
    set_adj("wrinkled");
    set_name("letter");
    add_cmd_item("letter","read","You smooth out the letter and start to "
	+"read.\n\n"
	+"You already know we are willing to pay you whatever "
	+"you want to do the job.  Kill the wife and get it over "
	+"with.  When you bring us her bracelet, we will know the "
   +"job is done.  You will receive the full payment of 10000 "
  +"bits then.  Do not delay any further.  She must "
	+"die soon.  You can hide in the attic and wait until dark "
	+"to do the job.\n"
	+"MM.\n");

}


