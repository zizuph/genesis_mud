// creator(s): Ilyian
// last update: Oct 1995
// purpose: Polearm for the Infidels
// note: modelled after Boriska's random objects
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "../infidel.h"

string *adjs=({ "heavy", "scratched", "thick", "bright",
                    "wide-head", "shiny", "large" });
int adj_len = sizeof (adjs);

string *materials = ({"bronze", "iron", "steel", "adamantine"});
int mat_len = sizeof (materials);

int adj,mat;

create_weapon()
{
  set_name("corseques");
  add_name("polearm");
  set_short("corseques");
  set_pname("corsequeses");
  add_pname("weapons");

  adj = random (adj_len);
  mat = random (mat_len);
  configure_me();
}

void configure_me()
{
  set_short (adjs[adj]+" corseques");
  set_pshort (adjs[adj]+" corsequeses");

  add_adj(adjs[adj]);

  set_wt(W_POLEARM);
  set_dt(W_SLASH | W_IMPALE);

  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);

   set_long("This long polearm has a very heavy "
           +"grip, unusually close to the base of "
           +"the weapon. Its wide, axe-like head is made from "
           +materials[mat]+", and has sharp edges on either "
           +"side, with a single sharp point protruding "
           +"from between the blades.\n");
    add_prop (OBJ_I_WEIGHT, 100 + 30 * mat );
    add_prop (OBJ_I_VOLUME, 100 + 25 * mat );

    set_hit (23 + 2 * mat);
    set_pen (25 + mat);
    set_hands(W_BOTH);
}
