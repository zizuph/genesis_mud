// Dwarven battle axe with random attributes
// creator(s):   Kazz
// last update:  Feb 1995
// purpose:      random hammer for dwarven guards (initially for the outpost)
// note:a	 modelled after Boriska's random objects
// bug(s):
// to-do:        

inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
 
string *adjs=({ "sharp", "scuffed", "polished", "shiny", "new"});
int adj_len = sizeof ( adjs );
 
string *materials = ({ "metal", "steel", "iron", "alloy"});
int mat_len = sizeof ( materials );
 
// add more longs for more descriptions
string *longs = ({
    "This dwarven battle axe looks sharp enough to save your life.\n",
    "The battle axe is heavy, but a handy weapon.\n",
    "The dwarven hammer feels sturdy.\n" });
int long_len = sizeof (longs);
 
int adj,mat,lon;
 
create_weapon ()
{
  set_name ("axe");
  set_short ("axe");
  adj = random (adj_len);
  mat = random (mat_len);
  lon = random (long_len);
  configure_me();
}



void
configure_me ()
{
  set_short ( adjs[adj] + " " + materials[mat] + " " + "battle axe");
  add_adj (adjs[adj]);
  set_long (longs[lon]);
  add_prop (OBJ_I_WEIGHT, 100 + 20 * mat );
  add_prop (OBJ_I_VOLUME, 100 + 20 * mat );  // probably not very realistic
    // but let the better thing weigh more...
  set_wt (W_AXE);
  set_dt (W_SLASH);
  set_hit (10);
  set_pen (15);
  set_hands (W_ANYH);
    
}
 
