inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object door;

create_room()
{
  set_short("In the House of the Stewards");
  set_long("@@long_func");
  add_item("tables",BS("There are marble tables placed in rows here, and "+
    "upon each lies the remains of a Steward of Gondor. You are able to "+
    "count twenty-seven sleeping forms, their hands folded, and heads "+
    "pillowed upon stone. At the foot end of each table is a plaque.\n"));
  add_item(({"forms","bodies","corpses","remains","stewards"}),
    BS("These are the remains of the Stewards of Gondor, a long unbroken "+
    "family line from Pelendur of the House of Hurin and his descendants, "+
    "twenty-seven in all. Their hands are folded, and their heads are pillowed "+
    "upon stone.\n"));
  add_item("plaque","You see that the plaques have letters engraved in them,\n"+
    "forming the names of the dead Stewards, and the years of their rule.\n"+
    "You may 'read plaques' to see them all.\n");
  clone_object(MINAS_DIR+"obj/stew_door_in")->move(TO);
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
    "upon stone. But one table near at hand stands broad and bare.";
  return BS(txt+"\n");
}

do_read(str)
{
  if (!str) { notify_fail("Read what?\n"); return 0; }
  if (str != "plaques") return 0; /* Probably not meant for us then. */
  write("You walk to the end of each marble table, reading the plaques.\n");
  cat(MINAS_DIR+"obj/steward_list.txt");
  return 1;
}
