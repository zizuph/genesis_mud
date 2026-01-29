/*
 * A leather pouch to contain herbs in.
 *
 * Coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * /Mercade, 23 November 1993, changed it from container to /std/receptacle
 * /Mercade, 7 January 1994, fixed recovery of the pouch.
 * Mercade, 21 May 2004; removed decay routines.
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_container()
{
  set_name("pouch");
  set_adj("leather");
  set_short("@@short_func");
  set_pshort("leather pouches");
  set_long("@@long_func");
  add_prop(OBJ_I_VALUE,40);
  add_prop(CONT_I_IN,1);
  add_prop(CONT_I_RIGID,0);
  add_prop(CONT_I_TRANSP,0);
  add_prop(CONT_I_WEIGHT,200);
  add_prop(CONT_I_VOLUME,200);
  add_prop(CONT_I_MAX_WEIGHT,1500);
  add_prop(CONT_I_MAX_VOLUME,1500);
}

void
init()
{
  ::init();
  add_action("do_keep","keep");
}

string
short_func()
{
  if (sizeof(all_inventory(TO)) >= 1)
    return "leather pouch containing herbs";
  return "leather pouch";
}

string
long_func()
{
  string long_desc;
  long_desc = "This is a leather pouch for storing herbs in. ";
  if(query_prop(OBJ_M_NO_SELL))
    long_desc += "Presently, you do not want to sell the pouch. ";
  else
    long_desc += "If you do not want to sell the pouch, "+
      "just decide to <keep pouch>. ";
  return BSN(long_desc);
}

string
query_recover()
{
    return (MASTER + ":#sell" + query_prop(OBJ_M_NO_SELL) + "#" +
        query_container_recover());
}

void
init_recover(string arg)
{
    string foobar;
    string tmp;

    sscanf(arg, "%s#sell%s#%s", foobar, tmp, foobar);

    if (tmp != "0")
    {
        add_prop(OBJ_M_NO_SELL, tmp);
    }

    init_container_recover(arg);
}

int
do_keep(string str)
{
  if(!str || !TO->id(str))
  {
    NF("Keep what?\n");
    return 0;
  }

  if(TO->query_prop(OBJ_M_NO_SELL))
  {
    remove_prop(OBJ_M_NO_SELL);
    write("You can sell the pouch again now. \n");
  }
  else
  {
    TO->add_prop(OBJ_M_NO_SELL,"You do not want to sell the pouch!\n");
    write("You will now keep the pouch when you are selling equipment.\n"+
      "To be able to sell it again, just type <keep pouch> again.\n");
  }
  return 1;
}

