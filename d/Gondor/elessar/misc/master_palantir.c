/*   The Master-Palantir.
 *   Keeps track over all the palantirs and how they work.
 *   Elessar, Gondor/Genesis '93.
 */

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"
#define STD_STONE "/d/Gondor/elessar/misc/std_palantir"
#define TIRITH_STONE WT_DIR+"palantirroom"
#define ISEN_STONE ORTHANC_DIR+"8/palantirroom"
#define OSG_STONE "/d/Gondor/elessar/rooms/osgiliath"
#define SUL_STONE "/d/Gondor/elessar/rooms/weathertop"
#define ANNU_STONE "/d/Gondor/elessar/rooms/annuminas"
#define ELOS_STONE "/d/Gondor/elessar/rooms/elostirion"

object *palantir;
int in;

create_object()
{
  if (!IS_CLONE) return;
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
  initialize_palantirs();
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

initialize_palantirs()
{
  int n;
  seteuid(getuid(this_object()));
  if (in > 0) return;
  in += 1;
  write("A mist swirls in the dark crystal globe.\n");
  palantir = allocate(6);
  palantir[0] = clone_object(STD_STONE);
  palantir[0]->move(OSG_STONE);
  palantir[1] = clone_object(STD_STONE);
  palantir[1]->move(TIRITH_STONE);
  palantir[2] = clone_object(STD_STONE);
  palantir[2]->move(ISEN_STONE);
  palantir[3] = clone_object(STD_STONE);
  palantir[3]->move(SUL_STONE);
  palantir[4] = clone_object(STD_STONE);
  palantir[4]->move(ANNU_STONE);
  palantir[5] = clone_object(STD_STONE);
  palantir[5]->move(ELOS_STONE);
  while (n < sizeof(palantir)) {
    palantir[n]->set_palantir_id(n);
    palantir[n]->set_master_palantir(TO);
    n++;
    }
}

scrying(int palid, object pl)
{
  if (living(ENV(TO))) {
    ENV(TO)->catch_msg("A glowing mist swirlds in the centre of the Palantir.\n"+
    "Deep in the mist you see a face forming slowly. Bigger and bigger it\n"+
    "grows, until you can clearly make out "+QNAME(pl)+".\n");
    tell_room(ENV(ENV(TO)),QCTNAME(ENV(TO))+" stares deep into the Palantir.\n",ENV(TO));
    palantir[palid]->scrying(ENV(TO));
    return 1;
    }
  tell_room(ENV(TO),"A glowing mist swirls in the centre of the Palantir.\n"+
    "Deep in the mist a face takes form slowly. Ever more clearly, you\n"+
    "can see "+QCNAME(pl)+" in the seeing stone.\n");
  return 1;
}

