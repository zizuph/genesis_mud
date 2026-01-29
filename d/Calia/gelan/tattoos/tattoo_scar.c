inherit "/std/object";
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Immortal/std/domain.h"

#include "tattoo_defines.h"

string location;

void
create_object()
{
  set_name("_tattoo_scar");
  set_short("tattoo scar");
  set_long("tattoo scar, will be  invisible\n");

 add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_SELL,1);
  set_no_show();
}

string
show_subloc(string subloc, object who,  object for_obj)
{
string str;

  if(subloc != "_tattoo_scar_"+location)
    return who->show_subloc(subloc,  who, for_obj);
  if(who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return "";
  if(strlen(find_object(TATTOO_OBJECT)->find_armour(location, environment())))
    return "";

  if(who == for_obj)
    str = "You have a ";
  else
    str = who->query_pronoun()+" has a ";

  str += "ugly red burn of some sort on ";

  if(who  ==  for_obj)
    str += "your ";
  else
    str += who->query_possessive()+" ";

  str += MASTER_TATTOO->query_location_names(location)+".\n";

  return str;
}


void
init()
{
  ::init();
  environment()->add_subloc("_tattoo_scar_"+location,  TO);
}

void
set_location(string  str)
{
  if(!strlen(str))
    return;
    else
    location = str;
}

void
reset_object()
{
  environment()->remove_subloc("_tattoo_scar_"+location);
  TO->remove_object();
}
