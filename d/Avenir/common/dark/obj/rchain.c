// Random body armour for Avenir ogres
// made by Boriska


#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

//string *names = ({ "ringmail", "chainmail", "platemail" });
static string *names = ({ "armour" });
//   sometime I'll come with better names that would combine with
// all adjectives --Boris

static int name_len = sizeof (names);

static string *adjs =
({ "rusty", "smelly", "corroded", "dusty", "dirty", "blooded" });
static int adj_len = sizeof ( adjs );

// make sure the quality improves for bigger indices
static string *materials =
({"hard leather", "quilt", "studded", "scale", "splint", "double" });
static int mat_len = sizeof ( materials );

//string *longs = ({ "Nice long for each type of chainmail.\n" });
static string *longs =
({"This dirty body armour looks like it was used for long\n"+
    "time without proper care. You wonder how pieces are still\n"+
      "hold together.\n" });

static int long_len = sizeof (longs);
static int name,adj,mat,lon;

void configure_me();

void
create_armour()
{
  set_name ("armour");
  set_short ("armour");
  name = random (name_len);
  adj = random (adj_len);
  mat = random (mat_len);
  lon = random (long_len);
  configure_me();
}

void
configure_me()
{
  set_name (names[name]);
  set_short ( adjs[adj] + " " + materials[mat] + " " + names[name]);
  add_adj (adjs[adj]);
  set_ac (15 + mat * 2);
  set_long (longs[lon]);
  set_at ( A_BODY );
  add_prop (OBJ_I_WEIGHT, 5000 + 2000 * name + 2000 * mat );
//  add_prop (OBJ_I_VOLUME, 1000 + 200 * mat);  // probably not very realistic
    // but let the better thing weigh more...
}

string
query_recover()
{
  return MASTER + ":" + query_arm_recover() +
    sprintf ("hjhj#%d#%d#%d#%d", name, adj, mat, lon);
}

void
init_recover(string arg)
{
  string foo;
  
  sscanf ( arg, "%shjhj#%d#%d#%d#%d%s", foo, name, adj, mat, lon, foo);
  init_arm_recover(arg);
  configure_me ();  
}
