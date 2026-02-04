inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define SUBLOC "satchel_subloc"

int worn;

create_container()
{
  set_name("satchel");
  set_adj("leather");
  set_long(
  "It is a fine leather satchel, worn over the shoulder. It has room\n" +
  "to hold many needed items. A small silver clasp bears the emblem of\n" +
  "a silver star.\n"
  );

   add_prop(MAGIC_AM_MAGIC, ({"enchantment", 15}));
  add_prop(CONT_I_IN,1);
  add_prop(CONT_I_RIGID,0);
  add_prop(CONT_I_WEIGHT,500);
  add_prop(CONT_I_VOLUME,500);
  add_prop(CONT_I_MAX_WEIGHT,5000);
  add_prop(CONT_I_MAX_VOLUME,5000);
  add_prop(OBJ_I_VALUE,288);
}

query_recover() { return MASTER+":"; }

void
init()
{
  ::init();
  add_action("do_wear","wear");
  add_action("do_remove", "remove");
}

int
do_wear(string str)
{

  if(!str || !TO->id(str)) return 0;

  if(worn)
  {
    write("You already wear the satchel.\n");
  }
  else
  {
  TO->add_satchel(TP);
    TO->add_prop(OBJ_M_NO_SELL,"You cannot sell the satchel while worn.\n");
    write("You wear the satchel over your shoulder.\n");
    say(QCTNAME(this_player()) + " wear a leather satchel.\n");
    worn = 1;
  }
  return 1;
}

do_remove(string str)
{
   if(!str || !TO->id(str)) return 0;
   
   if(!worn)
   {
    write("You are not wearing the satchel.\n");
   }
   else
   {
   TO->remove_prop(OBJ_M_NO_SELL);
   write("You remove the satchel.\n");
   say(QCTNAME(this_player()) + " removes a leather satchel.\n");
   TP->remove_subloc(SUBLOC);
   worn = 0;
   }
   return 1;
}

add_satchel(object who)
{
   who->add_subloc(SUBLOC, TO);
   return;
}

leave_env(object from, object to)
{
   if (living(from)) {
     if(worn){
      from->remove_subloc(SUBLOC);
      }
   }
   ::leave_env(from, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;
   
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if(for_obj == carrier)
      str = "You are wearing a leather satchel over your shoulder.\n";
   else
      str = capitalize(carrier->query_pronoun()) +
   " is wearing a leather satchel over " +
   carrier->query_possessive() + " shoulder.\n";
   return str;
}

