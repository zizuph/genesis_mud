//  /bazaar/Obj/wield/gaxe.c
// creator(s): Ilyian
// last update: May 1995
// purpose: Axe for the guards in bazaar
// note: modelled after Boriska's random objects
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

string *adjs=({ "large", "scratched", "new-looking",
                "battle-scarred", "shining", "battered", "battle-worn",
                "thick", "long", "long-handled", "broad-bladed", "heavy" });
int adj_len = sizeof ( adjs );

string *materials = ({"copper", "iron", "steel", "adamantine" });
int mat_len = sizeof ( materials );

int adj,mat;

create_weapon ()
{
  set_name ("axe");
  add_name ("_guards_axe_in_bazaar_");
  set_short ("axe");
  set_long("This is a standard issue axe for the local bazaar guards. Its "
          +"long handle is wrapped in leather, providing a very good "
          +"grip on it. You can swing it through the air to test its "
          +"weight.\n");
  adj = random (adj_len);
  mat = random (mat_len);
  configure_me();
}

void
configure_me ()
{
  set_short ( adjs[adj] + " " + materials[mat] + " " + "axe");
  add_adj (adjs[adj]);

  add_prop (OBJ_I_WEIGHT, 100 + 20 * mat );
  add_prop (OBJ_I_VOLUME, 100 + 20 * mat );

  set_hit (22 + 2 * mat);    // the better the metal, the better the weapon
  set_pen (23 + mat);

  set_wt(W_AXE);
  set_dt(W_SLASH);
  set_hands(W_RIGHT);
  set_likely_dull(28);
  set_likely_corr(34);
  set_likely_break(2);
}

void
init()
 {
   ::init();
    add_action("swing_func", "swing");
 }

int
swing_func(string arg)
 {
    string str;

    if(arg == "axe")
       {
       write("You swing the "+short()+" through the air, testing "
          +"its weight out.\n");
       say(QCTNAME(TP)+" swings "+ POSSESS(this_player())+ " "+short()+
       " through the air.\n");
   return 1;
     }
 notify_fail("Swing what?\n");
 }

