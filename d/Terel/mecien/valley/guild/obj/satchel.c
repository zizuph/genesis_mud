/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

#define TO     this_object()
#define ETO    environment(TO)
#define TP     this_player()
#define SUBLOC "satchel_subloc"

int worn;

public void
create_container()
{
  set_name("satchel");
  set_adj("leather");
   add_name("mystic_satchel");
  set_long(
     "It is a fine leather satchel, worn over the shoulder. It has room to " +
     "hold many needed items. Its small silver clasp bears the emblem of a " +
     "silver star.\n");

  add_prop(MAGIC_AM_MAGIC, ({"enchantment", 15}));
  add_prop(CONT_I_IN, 1);
  add_prop(CONT_I_RIGID, 0);
  add_prop(CONT_I_WEIGHT, 500);
  add_prop(CONT_I_VOLUME, 500);
  add_prop(CONT_I_MAX_WEIGHT, 5000);
  add_prop(CONT_I_MAX_VOLUME, 5000);
  add_prop(OBJ_I_VALUE, 288);
}

public string
query_recover()
{
    return MASTER + ":";
}

public void
add_satchel(object who)
{
   who->add_subloc(SUBLOC, TO);
   add_prop(OBJ_M_NO_DROP, "You cannot drop the satchel while worn.\n");
   add_prop(OBJ_M_NO_SELL, "You cannot sell the satchel while worn.\n");
   worn = 1;
}

public void
remove_satchel(object who)
{
   who->remove_subloc(SUBLOC);
   remove_prop(OBJ_M_NO_SELL);
   remove_prop(OBJ_M_NO_DROP);
   worn = 0;
}

public int
do_wear(string str)
{

  if (!str || !id(str)) return 0;

  if(worn)
  {
    write("You already wear the satchel.\n");
  }
  else
  {
    add_satchel(TP);
    write("You wear the satchel over your shoulder.\n");
    say(QCTNAME(TP) + " wears a leather satchel.\n");
  }
  return 1;
}

public int
do_remove(string str)
{
   if(!str || !id(str)) return 0;

   if(!worn)
   {
      write("You are not wearing the satchel.\n");
   }
   else
   {
      remove_satchel(TP);
      write("You remove the satchel.\n");
      say(QCTNAME(this_player()) + " removes a leather satchel.\n");
   }
   return 1;
}

public void
init()
{
  ::init();
  add_action(do_wear, "wear");
  add_action(do_remove, "remove");
}

public void
leave_env(object from, object to)
{
   ::leave_env(from, to);

   if (from && living(from) && worn)
       remove_satchel(from);
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;

   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "You are wearing a leather satchel over your shoulder.\n";
   else
      str = capitalize(carrier->query_pronoun()) +
            " is wearing a leather satchel over " +
            carrier->query_possessive() + " shoulder.\n";
   return str;
}
