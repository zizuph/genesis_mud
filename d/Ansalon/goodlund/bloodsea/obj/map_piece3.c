inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

#define MAP_ID     "_ansalon_half_map"
#define FIXED_MAP2  "_ansalon_bloodsea_map2"

void
create_object()
{
    set_name(({"map","piece","_ansalon_map_piece_3"}));
    set_adj("damp");
    set_short("damp map piece");
    set_long("This damp piece of parchment looks like one " +
      "quarter of a piece of a treasure map! Unfortunately, " +
      "you will need all four quarters to be able to decifer " +
      "where the treasure is hidden.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 0);
}

void
destroy()
{
    tell_object(E(TO),"You fit a torn piece of the map together.\n");
    seteuid(getuid());
    clone_object(BOBJ + "tq_map")->move(E(TO));
    E(TO)->add_prop(FIXED_MAP2, 1);
    remove_object();
}


enter_env(object dest, object old)
{
    mixed oblist;
    if (dest)
    {

        oblist = FIND_STR_IN_OBJECT("all " + MAP_ID + "s",dest);
        oblist -= ({ 0, TO });
        if(oblist && sizeof(oblist) > 0)
         {
            set_alarm(1.0,0.0,"destroy");
            oblist->remove_object();
         }

    }
    ::enter_env(dest,old);
}