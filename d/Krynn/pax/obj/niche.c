/* Pax Tharkas, a niche used in Sla-Mori/o_entrance.c
 *
 * 941107 by Rastlin
 */

inherit "/std/container";

#include "/d/Krynn/common/defs.h"
#include "/sys/stdproperties.h"

create_container()
{
    set_name("niche");
    set_adj("small");

    set_long("It is a small niche, well hidden in the rock wall.\n");

    /* We don't want to see the niche on the ground */
    /*set_no_show();
    */
    set_no_show_composite(1);

    add_prop(CONT_I_MAX_WEIGHT, 1000);
    add_prop(CONT_I_MAX_VOLUME, 100);

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_IN, 1);
}

void
open_hole()
{
    E(TO)->handle_wall();
  /*   E(TO)->open_cliff();*/
}

/*     Extra function    */

void
close_hole()
{
   E(TO)->close_cliff();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(present("sla_mori_gem", TO))
	set_alarm(3.0, 0.0, "open_hole");
}

/*    Extra function    */  
void
leave_inv(object ob, object to)
{
   string *names;   

   ::leave_inv(ob, to);
   names = ob->query_names();

   if(sizeof(names) < 2)
      return;

   if(names[1] != "sla_mori_gem")
      return;

   set_alarm(3.0, 0.0, "close_hole");
}

