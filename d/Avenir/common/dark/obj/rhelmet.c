// Random helmet for Avenir ogres
// made by Boriska

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

static string *adjs =
({"rusty", "smelly", "corroded", "dusty", "dirty", "blooded" });
static int adj_len = sizeof( adjs );

static string *materials =
({"hard leather", "quilt", "studded", "ring", "chain" });
static int mat_len = sizeof ( materials );

static string *longs = ({
  "This showing traces of long careless usage helmet was\n" +
  "just picked up by its owner from some smelly heap.\n"+
  "You doubt it will make you feel good wearing it.\n"
});
static int long_len = sizeof(longs);
static int adj,mat,lon;

private void configure_me();

void
create_armour()
{
  set_name ("helmet");
  set_short ("helmet");
  adj = random (adj_len);
  mat = random (mat_len);
  lon = random (long_len);
  configure_me();
}

private void
configure_me()
{
  set_short ( adjs[adj] + " " + materials[mat] + " " + "helmet");
  add_adj (adjs[adj]);
  set_ac (15 + mat * 2);
  set_long (longs[lon]);
  set_at ( A_HEAD );
  add_prop (OBJ_I_WEIGHT, 1000 + 200 * mat );
  add_prop (OBJ_I_VOLUME, 1000 + 200 * mat);  // probably not very realistic
    // but let the better thing weigh more...
}

string
query_recover()
{
  return MASTER + ":" + query_arm_recover() +
    sprintf ("hjhj#%d#%d#%d", adj, mat, lon);
}

void
init_recover(string arg)
{
  string foo;
  
  sscanf ( arg, "%shjhj#%d#%d#%d%s", foo, adj, mat, lon, foo);
  configure_me();  
  init_arm_recover(arg);
}

