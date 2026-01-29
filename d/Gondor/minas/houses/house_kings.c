inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object door;

create_room()
{
  set_short("In the House of the Kings");
  set_long("@@long_func");
  add_item("tables",BS("There are marble tables placed in rows here, and "+
    "upon each lies the remains of a King of Gondor, although there are "+
    "a few tables empty. You are able to "+
    "count twenty-eight sleeping forms, their hands folded, and heads "+
    "pillowed upon stone. At the foot end of each table is a plaque.\n"));
  add_item("empty tables","You find four marble tables still unoccupied.\n"+
    "Their plaques read: Elendil the Tall, SA 3319 - 3441. Slain in Mordor\n"+
    "                    Earnil I          TA  913 - 936.  Lost at sea\n"+
    "                    Ondoher           TA 1936 - 1944. Lost at Morannon\n"+
    "                    Earnur            TA 2043 - 2050. Lost in Minas Morgul\n");
  add_item(({"forms","bodies","corpses","remains","kings"}),
    BS("These are the remains of the Kings of Gondor, all descendants of "+
    "Elendil the Tall, founder of the Kingdoms in Exile, Gondor and Arnor. "+
    "You count twenty-eight bodies in all. Their hands are folded, and their "+
    "heads are pillowed upon stone.\n"));
  add_item("plaque","You see that the plaques have letters engraved in them,\n"+
    "forming the names of the dead Kings, and the years of their rule.\n"+
    "You may 'read plaques' to see them all.\n");
  clone_object(MINAS_DIR+"obj/king_door_in")->move(TO);
}

init()
{
  ::init();
  add_action("do_read","read");
}

long_func()
{
  int l;
  string txt;
  l = TO->query_prop(OBJ_I_LIGHT);
  txt = "You are in a wide vaulted chamber, ";
  if (l>0) txt=txt+"draped with great shadows that your lightsource throws "+
    "upon its shrouded walls. In the dim light ";
  else txt=txt+"lying in darkness. With your ability to see without light, ";
  txt = txt+"you can make out many rows of tables, carved of marble; and "+
    "upon each table lies a sleeping form, hands folded, head pillowed "+
    "upon stone.";
  return BSN(txt);
}

do_read(str)
{
  if (!str) { notify_fail("Read what? The plaques?\n"); return 0; }
  if (str != "plaques") return 0; /* Probably not meant for us then. */
  write("You walk to the end of each marble table, reading the plaques.\n");
  cat(MINAS_DIR+"obj/king_list.txt");
  return 1;
}
