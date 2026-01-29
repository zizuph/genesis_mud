// Random bracers for Avenir ogres
// made by Boriska

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

static string *adjs = ({ "smelly", "dusty", "dirty", "blooded" });
static int adj_len = sizeof ( adjs );

// make sure the quality improves for better materials
static string *materials = ({"copper", "bronze", "iron" });
static int mat_len = sizeof ( materials );

static string *longs = ({
  "Off-hand armour obviously made in a rush by unskilled blacksmith.\n"+
  "Only ogres and their like dare to use it.\n"
});
static int long_len = sizeof (longs);

static int adj,mat,lon;

void configure_me();

void
create_armour()
{
  set_name ("bracers");
  set_short ("bracers");
  adj = random (adj_len);
  mat = random (mat_len);
  lon = random (long_len);
  configure_me();
}

void
configure_me()
{
  set_name ("bracers");
  set_short ( adjs[adj] + " " + materials[mat] + " " + "bracers");
  add_adj (adjs[adj]);
  set_ac (7 + mat * 3);
  set_long (longs[lon]);
  set_at ( A_ARMS );
  add_prop (OBJ_I_WEIGHT, 3000 + 500 * mat );
  add_prop (OBJ_I_VOLUME, 3000 ); 
}

string
query_recover()
{
  return MASTER + ":" + query_arm_recover() + sprintf ("hjhj#%d#%d#%d#", adj, mat, lon);
}

void
init_recover(string arg)
{
  string foo;
  
  sscanf ( arg, "%shjhj#%d#%d#%d%s", foo, adj, mat, lon, foo);
  init_arm_recover(arg);
  configure_me ();  
}
