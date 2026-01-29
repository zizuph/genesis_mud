inherit "/std/object";

#include "/d/Kalad/defs.h"
#define SUBLOC "how_dirty_subloc"

string dirtiness(object carrier);

create_object()
{
   
   set_name("dirty");
   set_short("dirty");
   add_prop(OBJ_M_NO_DROP,1);
   add_prop(OBJ_M_NO_GIVE,1);
   add_prop(OBJ_M_NO_STEAL,1);
   set_no_show(1);
   
}


void
enter_env(object to, object from)
{
   if(living(to))
      to->add_subloc(SUBLOC, TO);
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
   
   if( (carrier->query_prop(LIVE_I_DIRTY) / 10) < 1)
      return "";
   else
      return C(pro) + dirtiness(carrier);
}

string
dirtiness(object carrier)
{
   string str;
   
   switch(carrier->query_prop(LIVE_I_DIRTY) / 10)
   {
      case 0:
      str = "spanking clean.\n";
      break;
      case 1:
      str = "slightly sweaty.\n";
      break;
      case 2:
      str = "sweaty and slightly dirty.\n";
      break;
      case 3:
      str = "dirty and sweaty.\n";
      break;
      case 4:
      str = "dirty and unpleasant smelling.\n";
      break;
      case 5:
      str = "very dirty and sour smelling.\n";
      break;
      case 6:
      str = "very dirty and smelling wretched.\n";
      break;
      case 7:
      str = "filthy and completely reeking.\n";
      break;
      case 8:
      str = "filthy and smelling like vomit.\n";
      break;
      case 9:
      str = "disgustingly filthy and smelling like feces.\n";
      break;
      case 10:
      str = "sickeningly filthy and unbearably putrid.\n";
      break;
      default :
      str = "so filthy it can't be described with words.\n";
      break;
   }
   
   return str;
}
