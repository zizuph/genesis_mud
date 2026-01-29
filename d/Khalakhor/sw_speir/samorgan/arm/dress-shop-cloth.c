/* Basic dress shop cloth
 * Tapakah, 06/2021
 * From Damaris's code.
 */

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit KSTDARMOUR;

string *sizes, *styles, *colors;
string *adjs = ({});

string query_size  () { return adjs[0]; }
string query_style () { return adjs[1]; }
string query_color () { return adjs[2]; }

void
configure_armour ()
{
}

varargs void
configure_desc (string preset = 0)
{
  string adj;
  string short_desc = "";

  int a;
  
  if (preset)
    adjs = explode(preset, ":");
  else {
    a = 0;
    foreach (string *group: ({ sizes, styles, colors })) {
      if (sizeof(adjs) <= a)
        adjs += ({ one_of_list(group) });
      a++;
    }
  }
  
  set_adj(adjs);
  short_desc += implode(adjs, " ") + " " + query_name();
  set_short(short_desc);
  set_ac(10);
  add_prop(OBJ_I_VALUE, 500);
  set_am( ({-1,3,-2 }) );
  set_af(this_object());
}

int
act_cloth (string verb, string str, string write_msg, string say_msg)
{
  string cloth = query_name();
  string Verb = capitalize(verb);
  
  if((str == cloth)) {
    if (query_worn() != TP)
      NF0("You are not wearing the " + cloth + "!");
    write(write_msg);
    say(say_msg);
    return 1;
  }
  else
    NF0(Verb + " the " + cloth + ", perhaps?\n");
}

void
create_khalakhor_armour ()
{
  ::create_khalakhor_armour();
  configure_armour();
}

string
query_recover ()
{
  return ::query_recover() + ":SAMORGAN_BELT:" +
    implode(({
              query_size(), query_style(), query_color(),
            }), ":");
}

void
init_recover (string arg)
{
  string ssc, str;
  sscanf(arg, "%s:SAMORGAN_BELT:%s", str, ssc);
  configure_desc(ssc);
}
