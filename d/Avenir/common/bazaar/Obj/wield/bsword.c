// Bsword.c
// creator(s): Ilyian
// last update: May 1995
// purpose: Sword for the punishers
// note: modelled after Boriska 's random objects
// bug(s):
//to - do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

string         *adjs = ({"large", "scratched", "sharp", "new-looking",
			     "battle-scarred", "shining"});
int             adj_len = sizeof(adjs);
string         *materials = ({"iron", "metal", "steel"});
int             mat_len = sizeof(materials);
int             adj, mat;

create_weapon()
{
    set_name("sword");
    add_name("_trolobys_sword_in_bazaar_");
    set_short("sword");
    set_long("This large sword has a thick handle that feels warm. The blade "
	+ "extends outwards with a very slight curve, and has a sharp tip. "
	     + "Swinging the blade would feel very satisfying.\n");
    adj = random(adj_len);
    mat = random(mat_len);
    configure_me();
}

void
configure_me()
{
    set_short(adjs[adj] + " " + materials[mat] + " " + "sword");
    add_adj(adjs[adj]);

    add_prop(OBJ_I_WEIGHT, 100 + 20 * mat);
    add_prop(OBJ_I_VOLUME, 100 + 20 * mat);

    set_hit(22 + 2 * mat);
    //the better the metal, the better the weapon
	set_pen(23 + mat);

    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
    set_likely_dull(18);
    set_likely_corr(0);
    set_likely_break(8);
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
    string          str;

    if(arg == "sword" || arg == "blade")
    {
      if(interactive(TP) && STR(TP) < 120)
      {
         write("You feebly swing the " + short() + " through the air.\n" +
               "You are unable to stop path of the " + short() + 
               ", and it flies right " +
               "out of your hands!\n");
         say(QCTNAME(this_player()) + " swings the " + short() + 
               " in an arc through the " +
               "air, but is unable to stop its motion.\nThe " + 
               short() + " flies right out of " +
               POSSESS(this_player()) + " hands.\n");

         move(ENV(TP));
         return 1;
      }

      write("You strain your muscles and swing the " + short() + 
            " through " +
            "the air.\nYou hear a satisfying 'swoosh'.\n");
      say(QCTNAME(TP) + " swings the " + short() + " through the air with " +
            "incredible strength.\nSwoosh.\n");
      return 1;
    }

    notify_fail("Swing what?\n");
    return 0;
}
