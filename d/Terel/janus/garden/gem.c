/*  A small gem */

inherit "/std/object";
#include <stdproperties.h>

#include "/d/Terel/common/terel_std_rec.h"
int  i;
create_object()
{
  set_name("gem");
  i=random(3);
  if (i==2){
    set_long("Small marine blue round gem.\n");
    set_adj(({"round"}));
    add_adj("blue");
    add_adj("small");
  }
  if (i==1){
    set_long("Tiny black cylindric gem.\n");
    set_adj(({"cylindric"}));
    add_adj("tiny");
    add_adj("black");
  }
  if (i==0){
    set_long("Small turqoise oval gem.\n");
    set_adj(({"oval"}));
    add_adj("tiny");
    add_adj("turqoise");
  }
  add_prop(OBJ_I_VALUE, random(100)+213);
}

