/* /d/Gondor/olorin/obj/hole.c
 *
 * Created: 22-may-1993 by Olorin
 *
 */
inherit "/std/object.c";

#include <stdproperties.h>
#include <language.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

int size, maxsize;
string *snames;

create_object()
{
  set_name("_hole_");
  add_name( ({"hole", "trench", "pit"}) );
  set_short("@@my_short");
  set_long("@@my_long");
  add_prop(OBJ_M_NO_GET,1);
  size = 0;
  setup_names();
}

int
query_size()
{
  return size;
}

increase_size()
{
  if(size < sizeof(snames) -1)
    size++;
  return size;
}

my_short()
{
  return snames[size];
}

my_long()
{
  return BS("Someone has dug " + LANG_ADDART(snames[size]) + " here. You cannot imagine why anyone would " +
    "even think of digging " + LANG_ADDART(snames[size]) + " in this spot, since it clearly must " +
    "have cost him some sweat.\n");
}

setup_names()
{
  snames = ({
    "small hole",
    "ordinary hole",
    "big hole",
    "ordinary trench",
    "average trench",
    "deep trench",
    "small pit",
    "ordinary pit",
    "large pit",
    });
}
