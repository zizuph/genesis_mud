/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

int wet;

query_wet()
{
    return wet;
}


create_object()
{
    set_name("peat");
    add_name("block");
    add_name("block of peat");
    add_pname("blocks of peat");
    set_short("block of peat");
    set_pshort("blocks of peat");
    set_long("@@my_long");
    add_prop(OBJ_I_VALUE, 3);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_M_NO_SELL, 1);
    wet = 1;
    set_alarm(500.0,0.0,"dry");
}

init()
{
    add_action("light_peat","light");
}


my_long()
{
    string str = "This looks like ordinary peat used for fires.";
    if (wet == 1)
       str += " It seems too wet to light though.";
    else if (wet == 0)
       str += " It seems dry enough.";
    else 
      str += " It is lit and very hot.";
    return BS(str, SL);
}


dry()
{
    wet = 0;
}

light_peat(string str)
{
    int suc;
    string num, what;
    if ((str != "peat") && (str != "block") &&
	(str != "block of peat"))
    {
        if ((str == "peats") || (str == "blocks") || (str == "blocks of peat"))
	  {
	    notify_fail("You can only light one block of peat at a time.\n");
	    return 0;
	  }
        notify_fail("Light what?\n");
        return 0;
    }
    if (wet == 2)
      {
	notify_fail("The block of peat is already lit.\n");
	return 0;
      }
    if (wet)
      {
	notify_fail("The block of peat is too wet to light.\n");
	return 0;
      }
    seteuid(getuid(TO));
    write("You light a block of peat.\n");
    set_short("lit block of peat");
    set_pshort("lit blocks of peat");
    add_prop(OBJ_I_HAS_FIRE, 1);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_M_NO_GET, "Ouch, it just too hot to get.\n");
    TP->command("drop peat"); 
    wet = 2;
    set_alarm(itof(300-random(50)),0.0,"exting");
    return 1;
}


exting()
{
  seteuid(getuid(TO));
  tell_room(E(TO),"The fire slowly goes out.\n");
  TO->remove_object();
}
