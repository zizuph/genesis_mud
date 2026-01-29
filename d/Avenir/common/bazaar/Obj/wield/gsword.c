// /bazaar / Obj / wield / gsword.c
// creator(s):Ilyian
// last update:May 1995
// purpose:Sword for the guards in bazaar
//              note:modelled after Boriska 's random objects
//              bug(s):
// to - do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

string         *adjs = ({"large", "scratched", "sharp", "new-looking",
		     "battle-scarred", "shining", "battered", "battle-worn",
			     "thick", "long"});
int             adj_len = sizeof(adjs);
string         *materials = ({"copper", "iron", "steel", "adamantine"});
int             mat_len = sizeof(materials);
int             adj, mat;

create_weapon()
{
    set_name("sword");
    add_name("_guards_sword_in_bazaar_");
    set_short("sword");
    set_long("This is a standard issue sword for the local bazaar guards. It "
	     + "looks like it has seen quite a few battles, and there are "
	   + "long blood stains along it. The handle is shaped to fit your "
	     + "right hand either way, so it can be pointing upwards or "
	     + "downwards, and you can twirl it back and forth.\n");
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
    set_hands(W_RIGHT);
    set_likely_dull(28);
    set_likely_corr(34);
    set_likely_break(12);
}

void
init()
{
    ::init();
    add_action("twirl_func", "twirl");
}

int
twirl_func(string arg)
{
    string          str;

    if (arg == "sword" | arg == "blade") {
	if (DEX(TP) < 90) {
	    write(
		     "You clumsily try to twirl the " + short() + " around so it is positioned the " +
		     "other way in your hand.\n" +
		"You lose your grip on the " + short() + " alltogether.\n");
	    say(
		   QCTNAME(this_player()) + " tries to twirl the " + short() + " around in his " +
		   "hand.\nThe " + short() + " flies right out of " +
		   POSSESS(this_player()) + " hands.\n");

	    TP->command("drop _guards_sword_in_bazaar_");
	    return 1;
	}
	write("You dexteriously twirl the " + short() + " around in your hand, " +
	      "and end up holding it the other way.\n");
	say(QCTNAME(TP) + " twirls the " + short() + " around in " +
	    POSSESS(this_player()) + " hand, so it ends up facing the other way.\n");
	return 1;
    }
    notify_fail("Twirl what?\n");
}
