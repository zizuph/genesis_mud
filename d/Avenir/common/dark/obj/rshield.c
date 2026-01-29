// Random shield for Avenir ogres
// made by Boriska


#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

static string *names = ({ "shield" }); 
static int name_len = sizeof (names);

static string *adjs = ({ "smelly", "dusty", "dirty", "blooded" });
static int adj_len = sizeof ( adjs );

// make sure the quality improves for bigger indices
static string *materials =
({"canvas", "hard leather", "copper", "bronze", "iron" });
static int mat_len = sizeof ( materials );

static string *longs = ({
  "Crude and heavy shield, more burdening than protecting.\n" +
  "You feel disguisted wearing it.\n"
});
static int long_len = sizeof (longs);

static int name,adj,mat,lon;

private void configure_me();

void
create_armour()
{
  set_name ("shield");
  set_short ("shield");
  name = random (name_len);
  adj = random (adj_len);
  mat = random (mat_len);
  lon = random (long_len);
  configure_me();
}

private void
configure_me()
{
  set_name (names[name]);
  set_short ( adjs[adj] + " " + materials[mat] + " " + names[name]);
  add_adj (adjs[adj]);
  set_ac (7 + mat * 3);
  set_long (longs[lon]);
  set_at ( A_SHIELD );
  add_prop (OBJ_I_WEIGHT, 5000 + 500 * name + 500 * mat );
  add_prop (OBJ_I_VOLUME, 2000 + 300 * name); 
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
