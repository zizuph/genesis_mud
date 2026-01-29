inherit "/std/object";

#include "/cmd/std/tracer_tool_base.c";

#include "/sys/macros.h"
#include "/sys/log.h"
#include "/sys/filepath.h"
#include "/secure/std.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define CHECK_SO_WIZ    if (WIZ_CHECK < WIZ_NORMAL) return 0; \
                        if (this_interactive() != this_player()) return 0


#include <stdproperties.h>

#include "/d/Roke/common/defs.h"
query_auto_load() {
  string name;
  int i;
  sscanf(file_name(this_object()),"%s#%d", name, i);
  return name;
}

create_object()
{
  set_short("directory updater");
  set_name("updater");
  set_adj("directory");
  set_long("This is a nice utility built by Gresolle.\n"+
	   "cd to the desired directory, then you can use\n"+
	   "'dupd <expr>' to update files matched by <expr>.\n");

  add_prop(OBJ_I_NO_DROP,1);
}
init()
{
  ::init();

    add_action("dupd","dupd");
}
dupd(string s)
{
  int i;

  string *dir;

  dir = get_dir(this_interactive()->query_path()+"/"+s);

  for(i=0;i<sizeof(dir);i++)
    {
      update_ob(dir[i]);
    }
  return 1;
}

int
update_ob(string str)
{
    object ob;
    int kick_master;

    CHECK_SO_WIZ;

    if (!strlen(str))
    {
        notify_fail("Update what object ?\n");
        return 0;
    }
    str = FTPATH((string)this_interactive()->query_path(), str);
    if (!strlen(str))
    {
        notify_fail("Invalid file name.\n");

        return 0;
    }
    ob = find_object(str);
    if (!ob)
    {
        notify_fail("No such object.\n");
        return 0;
    }
    if (ob == find_object(SECURITY))
        kick_master = 1;

    if (ob != this_object())
    {
        ob->remove_object();
        ob = find_object(str);
        if (ob)
            destruct(ob);


        /* When updating the master object it must be reloaded at once
           and from within the GD
         */
        if (kick_master)
        {
            write(SECURITY + " was updated and reloaded.\n");
            get_dir("/*");
        }

        else if (!ob)
            write(str + " will be reloaded at next reference.\n");
        else
        {
            notify_fail("Object could not be updated.\n");
            return 0;
        }

    }
    else
    {
        write(str + " will be reloaded at next reference.\n");
        write("Destructing this object.");
        destruct(this_object());
        return 1;
    }
    return 1;
}

