/*  potion */
/*  janus 920831 */
/* Fixed cloining - Cotillion, 20151120 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()
#define HOME           "/d/Terel/janus"

init()
{
  ::init();
  add_action("do_drink","quaff");
  add_action("do_drink","drink");
}

void
create_object()
{
  set_name("potion");
  set_short("magenta potion");
  set_adj("magenta");
  set_long(break_string("The potion contains a magenta coloured bubbly"+
			" liquid. \n",70));
  add_prop(OBJ_I_WEIGHT,50);
  add_prop(OBJ_I_VOLUME,50);
  add_prop(OBJ_I_VALUE, 200);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop(MAGIC_AM_MAGIC,({90,"alteration"})); 

  setuid();
  seteuid(getuid());
}

do_drink(string vad)
{
  object pcstart;
  object wheretogo;
  object krympp;
  object rath;
  object mound;
  object ob;
  if (vad == "potion" || vad == "magenta potion") {
    pcstart=environment(TP);
    mound = present("moundi",pcstart);
    rath = present("rath",pcstart);
    krympp = present("krympp",pcstart);
    if ( krympp ){     
      write(BS("The liquid taste delicious. You feel strange, very strange. "+
               "Your head spins, but nothing happens. \n"));
      return 1;
    }
    if (mound ){
        wheretogo = "/d/Terel/janus/garden/mound1";
      wheretogo -> set_pcfrom(pcstart);
      write(BS("The magenta liquid taste delicious but you feel strange, " +
               "very strange. "+
               "Your head spins and things around you grows to gargantuan "+
               "proportions. \n"));
      say(BS(QCTNAME(TP)+" drinks so something and suddenly grows smaller "+
             "and "+
             "smaller and dissapears from sight.\n"));
      TP->move_living("M", wheretogo, 1);
      TO -> remove_object();
      return 1;
    }
    if (rath ){
      wheretogo = "/d/Terel/janus/garden/rath";
      wheretogo -> set_pcfrom(pcstart);
      write(BS("The liquid taste delicious but you feel strange, very strange. "+
               "Your head spins and things around you grows to gargantuan "+
               "proportions. \n"));
      say(BS(QCTNAME(TP)+" drinks something and suddenly grows smaller and "+
             "smaller and disappears from sight.\n"));
      TP -> move(wheretogo);
      TO -> remove_object();
      return 1;
    }
    wheretogo = "/d/Terel/janus/garden/shrink";
    wheretogo -> set_pcfrom2(pcstart);
    write(BS("The liquid taste delicious but you feel strange, very strange. "+
	     "Your head spins and things around you grows to gargantuan "+
	     "proportions. \n"));
    say(BS(QCTNAME(TP)+" drinks something and suddenly grows smaller and "+
	   "smaller and dissapears from sight.\n"));
    TP -> move(wheretogo);
    TO -> remove_object();
    return 1;
  }
  return;
}
