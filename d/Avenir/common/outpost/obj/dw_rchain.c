// Dwarven chainmail with random attributes
// creator(s):   Kazz
// last update:  Feb 1995
// purpose:      random chainmail for dwarven guards (initially for  outpost)
// note:a	 modelled after Boriska's random objects
// bug(s):
// to-do:        


#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

string *adjs=({ "shiny", "new", "battle-scratched", "dwarven",
                    "heavy", "ornate" });
int adj_len = sizeof ( adjs );

string *materials = ({ "copper", "steel", "metal", "iron", "alloy" });
int mat_len = sizeof ( materials );

// add more longs for more descriptions
string *longs = ({
    	"This dwarven chainmail is well crafted.\n",
        "The chainmail is recently made and feels sturdy.\n" });
int long_len = sizeof (longs);

int adj,mat,lon;

create_armour ()
{
  set_name ("chainmail");
  set_short ("chainmail");
  adj = random (adj_len);
  mat = random (mat_len);
  lon = random (long_len);
  configure_me();
}

void
configure_me ()
{
  set_short ( adjs[adj] + " " + materials[mat] + " " + "chainmail");
  add_adj (adjs[adj]);
  set_ac (15 + mat * 2);	// higher index value (mat) the better ac
  set_long (longs[lon]);
  set_at ( A_BODY );
  add_prop (OBJ_I_WEIGHT, 100 + 2000 * mat );
  add_prop (OBJ_I_VOLUME, 100 + 2000 * mat );  // probably not very realistic
    // but let the better thing weigh more...
}

