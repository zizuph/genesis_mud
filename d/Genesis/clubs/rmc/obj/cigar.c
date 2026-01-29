/*
* Nice Cigar sold in the Rich Men's Bar
* Coded by Conan Jan -95
*/

inherit "/std/object";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>

void
create_object()
{
  set_name("cigar");
  set_adj("fat");
  
  set_short("fat cigar");
  set_pshort("fat cigars");
  set_long("This fat cigar is a symbol of your wealth. " +
           "You can <light cigar> to enjoy its flavour.\n");
   
  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE,  15);

  seteuid(getuid(TO));
}

void
init()
{
  ::init();
  
  add_action("smoking","light");
}

int
smoking(string str)
{
  NF("Smoke what?\n");
  
  if (str=="cigar")
  {
    write("You light your cigar and start to inhale the lovely smoke.\n");
    say(QCTNAME(TP)+" lights a cigar and looks very pleased and relaxed.\n");
    set_alarm(20.0, 0.0, "inhale");
    set_alarm(40.0, 0.0, "inhale");
    set_alarm(60.0, 0.0, "inhale");
    set_alarm(80.0, 0.0, "inhale");
    set_alarm(100.0, 0.0, "nomore");
   
    return 1;
  }
  
  return 0;
}

int
inhale()
{
  write("You inhale the smoke from your cigar, you feel relaxed and "+
        "eased at mind.\n");
  say(QCTNAME(TP)+" smokes on "+HIS_HER(TP)+" cigar and creates almost perfect "+
    "rings of smoke.\n");
  
  return 1;
}

int
nomore()
{
  write("You take the last smoke on the cigar and then you drop it on "+
    "the ground, stomping on it to make sure it isn't lit.\n");
  say(QCTNAME(TP)+" takes "+HIS_HER(TP)+" last smoke on the cigar, "+
    "then drops it and stomps on it to make sure it isn't lit.\n");
  TO->remove_object();

  return 1;
}
