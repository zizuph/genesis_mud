/* 
 * /d/Kalad/common/wild/pass/arm/bed_waba.c
 * Purpose    : A robe that adds a subloc to wearer
 * Located    : Used by the Bedlams in the desert
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#define SUBLOC "wearing_aba_subloc"
/* by Antharanos */
void
create_armour()
{
   ::create_armour();
   set_name("aba");
   add_name("robe");
   set_adj("concealing");
   add_adj("brown");
   set_long("A loose-fitting robe that is designed to protect the wearer "+
      "from intense heat and to conceal most of their body from view.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,160);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
}
void
enter_env(object to, object from)
{
   if (living(to))
      to -> add_subloc(SUBLOC, this_object());
   ::enter_inv(to, from);
}
void
leave_env(object from, object to)
{
   if (living(from))
      from -> remove_subloc(SUBLOC);
   ::leave_env(from, to);
}
string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;
   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "Your";
   else
      str = capitalize(carrier->query_possessive());
   return str + " body is almost totally covered by the concealing brown aba.\n";
}
