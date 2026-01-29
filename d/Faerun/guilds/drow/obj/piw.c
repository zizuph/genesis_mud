/*
 * Piwafwi of the Drow guild
 * Finwe, March 2008
 */

//inherit "/std/object";
inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#include "../drow.h"
#include "/d/Faerun/defs.h"
#include "/std/room/objects.c"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define MEDALLION_SUBLOC    "_piwafwi_cloak"

create_container()
{
    setuid(); 
    seteuid(getuid());
    
    set_name("piwafwi");
    add_name("robe");
    add_name("pocket");
    add_name(MEDALLION_SUBLOC);
    set_pname("piwafwis");
    set_adj("long");
    set_adj("dark");
    set_pshort("long dark piwafwis");
    set_long("This is a " + short() + ". It is woven of dark silks and other unknown fibers, and reaches nearly to the ground. The piwafwi is lightweight but durable, and perfectly fits a drow.\n");
//    set_default_armour(20, A_ROBE, (({ 0, 0, 1})), 0);
    add_prop(OBJ_I_WEIGHT, 100);   /* 360 gram */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, 200 + random (50));

    set_looseness(20);
    set_layers(1);

    clone_object("/d/Faerun/guilds/drow/obj/pocket")->move(TO);
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
  {
    return "";
  }

  if (for_obj == on)
    data = "You are ";
  else
    data = capitalize(environment(this_object())->query_pronoun()) + " is ";

  data+="wearing a " + query_short() + ".\n";

  return data;
}


enter_env(object dest,object old)
{
    ::enter_env();
  remove_name(MEDALLION_SUBLOC);

    add_name(MEDALLION_SUBLOC);
    if(living(E(TO)))
        dest->add_subloc(MEDALLION_SUBLOC, this_object());
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc(MEDALLION_SUBLOC);
}

init()
{
    ::init();
}

