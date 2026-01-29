// Dwarven helmet with random attributes
// creator(s):   Kazz
// last update:  Feb 1995
// purpose:      random helmet for dwarven guards (initially for the outpost)
// note:	 modelled after Boriska's random objects
// revisions: Lilith APr 2022: updated appears to resemble an armour that 
//              was painted by Voloda the painter. 

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

string *adjs=({ "shiny", "dented", "new", "battered", "battle-scratched",
                    "bloodied", "ornate" });
int adj_len = sizeof ( adjs );

string *materials = ({"hard leather", "copper", "steel", "iron"});
int mat_len = sizeof ( materials );

// add more longs for more descriptions
string *longs = ({
    "This dwarven helmet is well constructed and sturdy. It should protect "+
    "you well.\n" });
int long_len = sizeof (longs);

int adj,mat,lon, color;

create_armour ()
{
  set_name ("helmet");
  set_short ("helmet");
  adj = random (adj_len);
  mat = random (mat_len);
  lon = random (long_len);
  color = one_of_list(({"purple", "green", "red"}));
  configure_me();
}

void
configure_me ()
{
  set_short ( color +" sybarun helmet");
  add_adj (adjs[adj]);
  set_ac (15 + mat * 2);	// higher index value (mat) the better ac
  set_long (longs[lon] +" Studying it closely, you can tell at it used "+
      "to be "+ adjs[adj] + " " + materials[mat] + " " + "helmet.\n");
  set_at ( A_HEAD );
  add_prop (OBJ_I_WEIGHT, 100 + 200 * mat );
  add_prop (OBJ_I_VOLUME, 100 + 200 * mat );  // probably not very realistic
    // but let the better thing weigh more...
}

