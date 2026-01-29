/*
A bloody bandage that can be worn. It does no help at all...
Made by korat
feb 14. 1995
*/

inherit "/std/object";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
int bandage_on;
string bandage_where;
#define SUBLOC "wearing_bloody_bandage_subloc"

create_object()
{
   set_name("bandage");
   set_adj("bloodied");
   set_long("The bandage is made of a cheap cloth that is "+
      "soaked in deep red coloured, dried blood. Still "+
      "a sweet smell swifts into your nose. @@worn_where@@\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME,200);
   bandage_on = 0;
}

void
init()
{
   ::init();
   add_action("wrap_bandage","wrap");
   add_action("unwrap_bandage","unwrap");
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;
   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "You have a bloody bandage wrapped around your "+
   bandage_where + ".\n";
   else
      str = capitalize(carrier->query_pronoun()) + " has a "+
   "bloody bandage wrapped around "+ carrier->query_possessive() +
   " "+bandage_where + ".\n";
   return str;
}

int
wrap_bandage(string str)
{
   notify_fail("Wrap what around where?\n");
   if(!str) return 0;
   switch (str)
   {
      case "bandage around head":
      bandage_where="head";
      break;
       case "bandage around left arm":
      bandage_where="left arm";
      break;
       case "bandage around right arm":
      bandage_where="right arm";
      break;
       case "bandage around body":
      bandage_where="body";
      break;
       case "bandage around right leg":
      bandage_where="right leg";
      break;
       case "bandage around left leg":
      bandage_where="left leg";
      break;
      default:
      return 0;
      break;
   }
   if(bandage_on)
      {
      write("But you already wear the bandage.\n");
      return 1;
   }
   bandage_on=1;
   write("you wrap the bloody bandage onto your "+bandage_where+".\n");
   say(QCTNAME(TP) + " wraps a bloody bandage on "+TP->query_possessive()+
      " "+bandage_where+".\n");
   TP->add_subloc(SUBLOC, TO);
   return 1;
}

int
unwrap_bandage(string str)
{
   notify_fail("Unwrap what?\n");
   if (!str || str !="bandage")
      return 0;
   if (!bandage_on)
      {
      write("But you have not wrapped it on yet!\n");
      return 1;
   }
   bandage_on = 0;
   write("You unwrap the bloody bandage from your "+ bandage_where+".\n");
   say(QCTNAME(TP)+ " unwraps a bloody bandage from "+ TP->query_possessive() +
      " "+bandage_where+".\n");
   TP->remove_subloc(SUBLOC, TO);
   return 1;
}

worn_where()
{
   if (bandage_on)
      return "You have wrapped it on your "+bandage_where+".";
   else
      return "You can wrap it on yourself, but it will only "+
   "make you dirty.";
}
