#include <stdproperties.h>

inherit "/std/bow";

public void
create_bow()
{
    setuid(); seteuid(getuid(this_object()));
  set_adj(({"sleek", "elven"}));
  set_short("sleek elven bow");
  set_long("The bow very sleek and very light, still you feel " + 
	   "that it would require considerable strength to draw it. " +
	   "It is made from some kind of white wood that has been " +
	   "decorated with thin elven runes that seem to twine with " +
	   "the fibers of the wood.\n");
  add_prop(OBJ_I_WEIGHT, 900);
  add_prop(OBJ_I_VOLUME, 3250);
  set_hit(40);
  set_pen(58);
}
public varargs int
did_hit(int aid, string hdesc, int phurt,  object enemy, int dt, int phit, int dam)
{

    if (random(5) > 2)
    {
        write("Blah!\n");
        return 1;
    }
    return (::did_hit(aid, hdesc, phurt,  enemy,dt, phit, dam));
}


  
