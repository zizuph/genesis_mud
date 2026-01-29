// creator(s): Ilyian
// last update: Oct 1995
// purpose: Knife for the Infidels
// note: modelled after Boriska's random objects
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "../infidel.h"

string *adjs=({ "long", "thin", "sharp", "bright",
                "shiny", "wide-blade" });
int adj_len = sizeof (adjs);

string *materials = ({"bronze", "silver", "steel"});
int mat_len = sizeof (materials);

int adj,mat;

create_weapon()
{
  set_name("bodkin");
  set_short("bodkin");
  add_name(({"dagger","knife","infide"}));
  adj = random (adj_len);
  mat = random (mat_len);
  configure_me();
}

void configure_me()
{
  set_short (adjs[adj]+" "+materials[mat]+" bodkin");
  add_adj(adjs[adj]);

  set_wt(W_KNIFE);
  set_dt(W_IMPALE);

  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);

  set_long("This is a long and sharp bodkin, much like "
          +"a stiletto, except the blades are not sharpened, "
          +"leaving only the razor "+materials[mat]+" to "
          +"do the damage. It has a beautifully carved "
          +"wooden handle, wraped in strips of soft "
          +"leather to improve the grip.\n");
  add_prop (OBJ_I_WEIGHT, 100 + 5 * mat );
  add_prop (OBJ_I_VOLUME, 100 + 5 * mat );

  set_hit (10 + 2 * mat);
  set_pen (14 + mat);
  if(random(2))
      set_hands(W_RIGHT);
  else
      set_hands(W_LEFT);
}
