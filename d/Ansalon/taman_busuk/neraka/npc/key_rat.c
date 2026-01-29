/* Ashlar, 13 Jul 97 - A small rat */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AC_FILE

#define KEY_IN_SEWER_ROOM   NSEWER + "below_hut"

object key;

void
create_creature()
{
    ::create_creature();
    set_name("rat");
    set_adj("brown");
    set_race_name("rat");
    set_long("The rat sits in a corner of the room, chittering " +
      "gleefully. It seems to be carrying something in its " +
      "mouth.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    set_stats(({5,7,5,3,3,5}));
    set_hitloc_unarmed(0,15,80,"body");
    set_hitloc_unarmed(1,10,20,"head");
    set_attack_unarmed(0,40,8,W_BLUDGEON,40,"front paws");
    set_attack_unarmed(1,40,10,W_BLUDGEON,40,"jaws");
    set_attack_unarmed(2,40,8,W_BLUDGEON,20,"back paws");

    key = 0;
}

void
set_key(object k)
{
    key = k;
}

object
query_key()
{
    return key;
}

void
plop_key()
{
    object r;
    setuid();
    seteuid(getuid(this_object()));

    catch(E(TO)->plop());
    LOAD_ERR(KEY_IN_SEWER_ROOM);
    r = find_object(KEY_IN_SEWER_ROOM);
    if (key)
    {
	key->move(r);
	tell_room(r,"You hear a plop as something falls down from above " +
	  "into the water.\n");
    }
}

void
run_away_from(object attacker)
{
    attacker->catch_msg("Intimidated by your ferocious attack, the " +
      short() + " runs away across the floor. As it runs over a " +
      "metal grating, it seems to stumble slightly, and you hear a " +
      "distinct clink of metal on metal. The rat recovers and runs " +
      "into a hole in the wall.\n");
    tell_room(E(TO),QCTNAME(attacker) + " scares the rat so badly, " +
      "it flees, running across the floor into a hole in the wall. " +
      "As it passes by a metal grating, it seems to stumble, but " +
      "it quickly recovers.\n",attacker);
    plop_key();

    remove_object();
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    set_alarm(5.0,0.0,&run_away_from(attacker));
}

void
do_die(object killer)
{
    tell_room(E(TO),"The rat drops something it had been holding in its " +
      "mouth. Unfortunately, the rat is standing right at a grating, " +
      "and whatever it was carrying falls between the bars of the " +
      "grating.\n");
    plop_key();

    ::do_die(killer);
}
