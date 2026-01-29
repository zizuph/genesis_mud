// isword.c
// creator(s): Lilith
// last update: July 2001
// purpose: Sword for the infidels on the holm
// note: modelled after Boriska 's random objects
// bug(s):
//to - do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

string         *adjs = ({"keen", "polished", "sharp", "lethal",
			     "sinister", "shining", "curved", "barbed"});
int             adj_len = sizeof(adjs);
string         *materials = ({"steel", "blued-steel", "iron", 
                              "bone", "obsidian", "tooth"});
int             mat_len = sizeof(materials);
int             adj, mat;

create_weapon()
{
    set_name("sword");
    add_name(({"_infidel_sword_", "blade"}));
    set_short("sword");
    set_long("This is a large sword with a thick handle that "+
        "feels warm. The wooden grip is slightly worn, so it "+
        "will fit your hand. The blade extends outwards with "+
        "a very slight curve, and it has a sharp tip. "+
        "Swinging the blade would feel very satisfying.\n");
    adj = random(adj_len);
    mat = random(mat_len);
    configure_me();
}

void
configure_me()
{
    set_short(adjs[adj] + " " + materials[mat] + " " + "sword");
    add_adj(adjs[adj]);
    add_adj(explode(materials[mat], "-"));

    add_prop(OBJ_I_WEIGHT, 100 + 20 * mat);
    add_prop(OBJ_I_VOLUME, 100 + 20 * mat);

    set_hit(35 + random(6));
    set_pen(35 + random(6));

    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
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
      if(interactive(TP) && STR(TP) < 70)
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
