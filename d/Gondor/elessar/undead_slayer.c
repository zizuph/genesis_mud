inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_weapon() {
  set_name(({"broadsword","sword","broadsword"}));
  set_adj("mithril");
  set_adj("elven");
  set_adj("fine");
  set_short("mithril broadsword");
  set_pshort("mithril broadswords");
  set_long("This solid mithril broadsword was crafted by elves, and looks like\n"+
    "a very fine weapon.\n");
  set_default_weapon(35,35,W_SWORD,W_SLASH | W_IMPALE,W_RIGHT,0);
  add_prop(OBJ_I_WEIGHT, 2500);
  add_prop(OBJ_I_VOLUME, 600);
  add_prop(OBJ_M_NO_BUY,1);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35) + 4000);
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_MAGIC,({75, "abjuration"}));
  add_prop(MAGIC_AM_ID_INFO,({ 20, "A sword enchanted for slaying Undead creatures.\n"}));
  add_prop(OBJ_S_WIZINFO,"A sword that is still only halfway coded. The only\n"+
    "has magic properties and WC currently, but will become a sword\n"+
    "of slaying undead and the likes. Not available to mortals!\n");
}
