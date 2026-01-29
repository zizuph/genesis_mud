#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "local.h"

#define SUBLOC "_elven_glow"
#define LIGHT_I_LENGTH  523
#define ELF_GLOW_ID     "_elf_glow_id"

string set_light(object carrier);

void
create_object()
{
   set_name(ELF_GLOW_ID);
   add_name("light"); // old name, kept for compatibility.

   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_GIVE, 1);
   add_prop(OBJ_M_NO_STEAL, 1);

   set_no_show();
}

void
enter_env(object to, object from)
{
   if (living(to))
      to->add_subloc(SUBLOC, this_object());
   ::enter_inv(to, from);
}

void
leave_env(object from, object to)
{
   if(living(from))
      from->remove_subloc(SUBLOC);
   ::leave_env(from, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   string pro;   /*pronoun of carrier*/
   string pos;   /*possessive of carrier*/

   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";

   if (for_obj == carrier)
      {
      pro = "you are ";
   }
   else
      {
      pro = carrier->query_pronoun() + " is ";
   }

   if( (carrier->query_prop(LIGHT_I_LENGTH) / 10) < 1)
      return "";
   else
      return capitalize(pro) + set_light(carrier);
}

string
set_light(object carrier)
{
   switch(carrier->query_prop(LIGHT_I_LENGTH) / 10)
   {
     case 0:
      return "twinkles.\n";
     case 1:
      return "slightly glowing.\n";
     case 2:
      return "glowing.\n";
     case 3:
      return "glowing brightly.\n";
     case 4:
      return "shimmering slightly.\n";
     case 5:
      return "shimmering.\n";
     case 6:
      return "shimmering brightly.\n";
     case 7:
      return "bright.\n";
     case 8:
      return "very bright.\n";
     case 9:
      return "blindingly bright.\n";
     case 10:
      return "radiating light.\n";
     default :
      return "so filthy it can't be described with words.\n";
   }
}
