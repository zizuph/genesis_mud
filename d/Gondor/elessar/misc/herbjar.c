/*
 * A jar to contain herbs in (the third I see today)
 *
 * Coded by Lord Elessar Telcontar
 *
 * Revision history:
 * /Mercade, 23 November 1993; changed from container to receptacle
 */

inherit "/std/receptacle";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

string herbname,herb_file;
int herbs;

create_container()
{
  set_name("jar");
  set_adj("glass");
  set_adj("herb");
  set_short("@@short_func");
  set_long("@@long_func");
  add_prop(CONT_I_RIGID,1);
  add_prop(CONT_I_MAX_VOLUME,500);
  add_prop(CONT_I_MAX_WEIGHT,500);
  add_prop(CONT_I_WEIGHT,200);
  add_prop(OBJ_I_VALUE,100);
}

enter_inv(obj,from)
{
  if (!obj->query_herb_name()) no_put(obj,from);
  if (!ok_to_add(obj)) no_mix(obj,from);
  add_herb(obj,from);
  ::enter_inv(obj,from);
}

no_put(object obj, object from)
{
  obj->move(from);
  write("The glass jar is for storing herbs only.\n");
  return 1;
}

no_mix(object obj, object from)
{
  obj->move(from);
  write("The glass jar is used for storing "+herbname+" herbs, and you\n"+
    "feel you shouldn't mix them.\n");
  return 1;
}

ok_to_add(obj)
{
  return (obj->query_herb_name() == herbname);
}

add_herb(obj, from)
{
  int no, d;
  if (herbs) {
    herbs++;
    write("You put another "+herbname+" in the jar.\n");
    say(QCTNAME(TP)+" puts a "+obj->query_short()+" into a glass jar.\n");
    obj->remove_object();
    }
  herbs = 1;
  herbname = obj->query_herb_name();
  if (sscanf(file_name(obj),"%s#%d",herb_file,no) != 2) return 0;
  obj->remove_object();
  return 1;
}

init()
{
  ::init();
  add_action("get_from_jar","get");
}

get_from_jar(string str)
{
  string s1, s2;
  if (!str) { write("Get what?\n"); return 1; }
  if (sscanf(str,"%s from %s",s1,s2) != 2) return 0;
  if (s1 != herbname) return 0;
  if (s2 != "jar" && s2 != "glass jar") return 0;
  if (herbs == 1) {
    give_out_herb();
    no_more_herbs();
    return 1;
    }
  if (!herbs) { write("There are no "+s1+" in the jar!\n"); return 1; }
  give_out_herb();
  return 1;
}

give_out_herb()
{
  object h;
  h = clone_object(herb_file);
  h->move(TP);
  herbs--;
  write("You get a "+herbname+" from the jar.\n");
  say(QCTNAME(TP)+" takes a "+h->query_short()+" from a glass jar.\n",TP);
  return 1;
}

no_more_herbs()
{
  write("This was the last one; the jar is now empty.\n");
  herbs--;
  herbname == "";
  herb_file == "";
  return 1;
}

short_func()
{
  if (herbs) return "glass jar labelled "+herbname;
  return "empty glass jar";
}

long_func()
{
  if (herbs) return "This is a glass jar for storing herbs. Right now there\n"+
    "are "+herbs+" samples of "+herbname+" stored in it.\n";
  return "This is an empty glass jar for storing herbs in.\n";
}
