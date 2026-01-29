/*   The Palantir.
 *   Only small variations between the Orthanc and the Minas Tirith stone,
 *   so we might as well settle for one.
 *   Made by Elessar for Genesis, June 92.
 */

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

int palid;
object master_palantir;

create_object()
{
  set_name("globe");
  add_name("palantir");
  add_name("stone");
  add_name("seeing-stone");
  set_adj("crystal");
  set_adj("heavy");
  set_adj("dark");
  set_adj("shining");
  set_short("dark globe of crystal");
  set_long("@@describe");
  add_prop(OBJ_I_WEIGHT,2500);
  add_prop(OBJ_I_VOLUME,2144);
  add_prop(MAGIC_AM_MAGIC,({70, "divination"}));
  add_prop(MAGIC_AM_ID_INFO,({
     10, "The crystal ball emanates magic of some kind.\n",
     25, "It can probably be used to see far with.\n",
     40, "It can also be used to communicate via.\n",
    55, "Elven divination magic created the crystal globe.\n",
    70, "It is one of seven seeing stones; the Palantiri!\n"}));
}

describe()
{
  return "The shining globe of crystal is dark, but glowing with a heart of fire.\n";
}

init()
{
  add_action("scry_ball","scry");
  add_action("scry_ball","stare");
  add_action("send_thought","think");
}

scry_ball(string str)
{
  if (!str) return 0;
  if (str == "palantir" || str =="ball" || str=="globe" || str=="stone" ||
      str == "into palantir" || str =="into globe" || str == "into ball")
    {
    write("You stare into the dark crystal globe.\n");
    write("You only see swirling dark gases, and a glowing heart of fire.\n");
    master_palantir->scrying(palid, TP);
    return 1;
    }
  return 0;
}

send_thought(string str)
{
  if (!str) return 0;
  write("You concentrate by the dark crystal globe, and send your thoughts\n"+
    "into the swirling center. There is no reply.\n");
  return 1;
}

set_palantir_id(int pid)
{
  palid = pid;
}

query_palantir_id() { return palid; }

set_master_palantir(object ob)
{
  master_palantir = ob;
}

query_master_palantir() { return master_palantir; }

scrying(object pl)
{
  TP->catch_msg("You can vaguely make out the face of "+QCNAME(pl)+" in the swirling mist.\n");
  return 1;
}

