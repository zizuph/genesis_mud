/* A dagger  */
/* Magical elven dagger for Minas Morgul entrance quest */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_weapon()
{
  set_name("dagger"); set_pname("daggers");
  set_short("dagger"); set_pshort("daggers");
  set_adj(({"sharp","elven","long","leaf-shaped","damasked"}));
  set_short("long leaf-shaped dagger");
  set_long(BSN(
    "A long leaf-shaped dagger, of marvelous workmanship, damasked " +
    "with serpent-forms in red and gold. It is wrought from some " +
    "strange metal, light and strong and set with many fiery stones."));

  set_default_weapon(10,10,W_KNIFE,W_SLASH,W_ANYH,0);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(100)+250);
  add_prop(OBJ_I_WEIGHT, 3200);

  /* magic properties */
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop("mystic_weapon", 1);
  add_prop(MAGIC_AM_MAGIC,({40,"abjuration"}));
  add_prop(MAGIC_AM_ID_INFO, ({
    "The light gleaming of the blade tells you that the dagger is magical.\n", 1,
    "The dagger is not powerful as a weapon, but there is magic in it.\n", 10,
    BSN("The dagger is not powerful as a weapon, but the blade is magically strengthened to withstand magic."), 25,
    BSN("The dagger is not powerful as a weapon, but the blade will cut magically " +
      "protected items far better than other weapons."),50,
    })); 
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
