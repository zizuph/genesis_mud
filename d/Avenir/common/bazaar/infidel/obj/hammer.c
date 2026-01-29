// creator(s): Ilyian
// last update: Oct 1995
// purpose: Hammer for the Infidels
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
                    "battle-scarred", "shiny", "large" });
int adj_len = sizeof (adjs);

string *materials = ({"bronze", "iron", "steel", "adamantine"});
int mat_len = sizeof (materials);

int adj,mat;

create_weapon()
{
  set_name("hammer");
  set_short("hammer");
  adj = random (adj_len);
  mat = random (mat_len);
  configure_me();
}

void configure_me()
{
  set_short (adjs[adj]+" "+materials[mat]+" hammer");
  add_adj(adjs[adj]);

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);

  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);

  if(!random(3))
    {
       set_long("This large hammer has a long shaft the curves "
          +"slightly to fit the bearers grip. The "
          +materials[mat]+" head is "
          +"large and blunt, and looks like it could "
          +"crush most thing beneath it.\n");
        add_prop (OBJ_I_WEIGHT, 100 + 20 * mat );
        add_prop (OBJ_I_VOLUME, 100 + 20 * mat );

        set_hit (20 + 2 * mat);
        set_pen (22 + mat);
         if(random(2))
            set_hands(W_RIGHT);
         else
            set_hands(W_LEFT);
     }
  else     
    {
       set_long("This large hammer has a long shaft the curves "
          +"slightly to fit into both hands. The heavy "
          +materials[mat]+" head is "
          +"large and blunt, and looks like it could "
          +"crush most thing beneath it.\n");
        add_prop (OBJ_I_WEIGHT, 100 + 30 * mat );
        add_prop (OBJ_I_VOLUME, 100 + 25 * mat );

        set_hit (23 + 2 * mat);
        set_pen (25 + mat);
        set_hands(W_BOTH);
     }
}
