#pragma save_binary

inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#include "/sys/composite.h"
#include "/sys/macros.h"


string txt_str;

set_txt(string str)  { txt_str = str; }
query_txt()          { return txt_str; }

create_object() {
  set_name(({"page", "note"}));

  set_short("note in longhand");
  set_pshort("notes in longhand");

  set_long("This is a note, written in longhand on crisp, new parchment.\n");

  add_prop(OBJ_I_WEIGHT, 10);
  add_prop(OBJ_I_VOLUME, 10);
}

init()
{
  add_action("read_it", "read");
}

read_it(string str)
{
    object *objs;
    string desc;
    
    objs = CMDPARSE_ONE_ITEM(str, "read_one", "read_access");
    if (sizeof(objs) > 0) {
      notify_fail(""); 
      desc = COMPOSITE_DEAD(objs);
      say(QCTNAME(this_player()) + " reads " + desc + ".\n");
      return 1;
    }

    notify_fail("Read what?\n");
    return 0;
}

read_access(object obj)
{ 
  if ((environment(obj) == this_player()) &&
      (obj->is_readable()) &&
      (obj->query_short()))
    return 1;
  else
    return 0;
}

is_readable() 
{
  return 1; 
}

read_one(object obj)
{
  string txt;

  txt = obj->query_txt();

  if (txt) {
    write ("The note reads:\n" + txt);
    return 1;
  }

  write ("You cannot decipher what it says.\n");
  return 0;
}
      
