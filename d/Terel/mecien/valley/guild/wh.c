/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* A winged horse, used in the vocare spell as spirit 3 */
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <comb_mag.h>
#include <cmdparse.h>

#define TO            this_object()
#define TP            this_player()
#define ETO           environment(TO)
#define ETP           environment(TP)
#define NF(xx)        notify_fail(xx + "\n")
#define LOC1          "/d/Terel/mecien/mountains/mtop"
#define LOC2          "/d/Terel/mecien/mountains/skyt1"

#define A_KICK 0

#define H_BODY 0
#define H_WING 1
#define H_HEAD 2

int duration;

public void
self_destruct()
{
    tell_room(ETO, "The "+ short() + " flies off into the misty sky!\n");
    remove_object();
}

public void
init_living()
{
    ::init_living();
    add_action("mount", "mount");
}

int
mount(string str)
{
    object *obs;
    int loc;

    NF("Mount what?");
    if (!str) return 0;
    obs = FIND_STR_IN_OBJECT(str, ETP);
    if (sizeof(obs) == 0 || sizeof(obs) >= 2) return 0;
    if (obs[0] != TO) return 0;

    NF("The "+short()+" is not here at your call!");
    if (query_prop("summoner") != TP->query_name()) return 0;

    loc = ETP->query_prop("_can_summon_the_air");
    NF("The "+short()+" looks irresolute.");
    if (!loc) return 0;

    say(QCTNAME(TP) + " mounts the winged horse.\n");
    write("You mount the winged horse.\n");
    write("The winged horse flies off into the misty sky!\n");
    say("The winged horse flies off carrying " + QTNAME(TP) + ".\n");
    write("As the winged horse lands, it kneels and you dismount.\n");
    if (loc == 1) {
        TO->move_living("M", LOC2);
        TP->move_living("M", LOC2);
    } else if (loc == 2) {
        TO->move_living("M", LOC1);
        TP->move_living("M", LOC1);
        set_alarm(5.0, -1.0, self_destruct);
    }
    say(QCTNAME(TP) + " arrives upon a winged horse.\n");
    return 1;
}

public void
create_creature()
{
    set_name("winged horse");
    add_name("ulthyra");
    add_name("horse");
    set_adj("silver-white");
    set_short("silver-white winged horse");
    set_living_name("ulthyra");
    set_race_name("winged horse");
    set_long(
        "This mysterious creature seems to belong to some other world, for "
       +"it appears not to abide here in a earthly sense, being more "
       +"akin to the spirit world. It is dazzling in its silver-white "
       +"beauty, its mane glowing like silver from the forge.\n");

    set_stats(({ 65, 93, 87, 34, 45, 43 }));
    set_skill(SS_DEFENCE, 75);

    set_hp(9999);
    set_mana(9999);
    set_gender(2);

    set_attack_unarmed(A_KICK, 34, 45, W_BLUDGEON, 96, "kick");

    set_hitloc_unarmed(H_BODY, ({ 50, 50, 50, 50 }), 75, "torso");
    set_hitloc_unarmed(H_WING, ({ 40, 40, 40, 40 }), 20, "wings");
    set_hitloc_unarmed(H_HEAD, ({ 25, 25, 25, 25 }),  5, "head");
}

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    mixed hres;
    
    hres = ::hit_me(wcpen, dt, attacker, attack_id);
    
    move_living("flies off in a turbulent wind", "/d/Terel/mecien/void");
    set_alarm(5.0, -1.0, self_destruct);
    
    return hres;
}

public void
set_duration(int t)
{
    duration = t;
}
