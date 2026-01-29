//  /bazaar/Obj/wield/bsmace.c
// creator(s): Ilyian
// last update: May 1995
// purpose: Mace for the punishers
// note: modelled after Boriska's random objects
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

string *adjs=({ "heavy", "scratched", "thick", "bright",
                    "battle-scarred", "shining", "large" });
int adj_len = sizeof ( adjs );

string *materials = ({"iron", "metal", "steel" });
int mat_len = sizeof ( materials );

int adj,mat;

create_weapon ()
{
  set_name ("mace");
  add_name ("_trolobys_mace_in_bazaar_");
  set_short ("mace");
  set_long("This heavy mace looks like it would smash most things to "
          +"a pulp. It has a large handle to fit an enormous hand. The "
          +"grip is of padded leather, and you can grip it tighter "
          +"for a better hold.\n");
  adj = random (adj_len);
  mat = random (mat_len);
  configure_me();
}

void
configure_me ()
{
  set_short ( adjs[adj] + " " + materials[mat] + " " + "mace");
  add_adj (adjs[adj]);

  add_prop (OBJ_I_WEIGHT, 100 + 20 * mat );
  add_prop (OBJ_I_VOLUME, 100 + 20 * mat );

  set_hit (22 + 2 * mat);    // the better the metal, the better the weapon
  set_pen (23 + mat);

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hands(W_RIGHT);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}

void
init()
 {
   ::init();
    add_action("grip_func", "grip");
 }

int
grip_func(string arg)
 {
    string str;

    if(arg == "club" | arg == "handle" | arg == "mace")
       {
          if (STR(TP) < 120)
           {
             write(
"You grip the handle of the "+short()+" tightly. Your small muscles "+
"bulge a little.\n");
      say(
QCTNAME(this_player()) + " grips the handle of the "+short()+", showing "+
POSSESS(this_player()) + " feeble muscles.\n");

       return 1;
            }
       write("You grip the handle of the "+short()+", flexing your "+
            "titanic muscles.\n");
       say(QCTNAME(TP)+" grips the handle of the "+short()+".\n"+
            capitalize(POSSESS(TP))+" muscles flex impressively.\n");
       TP->command("grin");
   return 1;
     }
  notify_fail("Grip what?\n");
 }


