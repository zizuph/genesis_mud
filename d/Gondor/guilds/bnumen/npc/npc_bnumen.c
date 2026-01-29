/*
 * A npc member of the Houses of the Black Numenoreans
 *
 * Olorin, 14-nov-1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

/* Function declaration */
int     set_bnumen_house(string str);

/* Global variables */
string  Black_Numenoreans_House;

void
create_bnumen()
{
}

nomask void
create_gondor_monster()
{
    create_bnumen();

    set_race_name("human");
    add_name("bnumen");

    if (!query_scar())
        set_scar(random(1024));

    if (!query_skill(SS_WEP_AXE))
	set_skill(SS_WEP_AXE, 50);
    if (!query_skill(SS_UNARM_COMBAT))
	set_skill(SS_UNARM_COMBAT, 30);
    if (!query_skill(SS_DEFENCE))
	set_skill(SS_DEFENCE, 20);
    if (!query_skill(SS_AWARENESS))
	set_skill(SS_AWARENESS, 50);

}

static void
equip_me()
{
    add_cmdsoul(BNUMEN_SOUL);
    update_hooks();
}

public void
do_intro(object tp = TP)
{
    string  name;

    if (!present(tp, ENV(TO)) || !CAN_SEE_IN_ROOM(TO) ||
        !CAN_SEE(TO, tp) || tp->query_met(query_real_name()))
        return;

    name = tp->query_real_name();
    if (tp->query_race_name() == "elf")
        command("elfhail " + name);
    else if (tp->query_guild_name_race() == GUILD_NAME)
        command("wellmet " + name);
    else
        command("salute " + name);
    command("introduce me to " + name);
}

public string
add_introduced(string who)
{
    object  pl;

    if (objectp(pl = find_player(who)) &&
        !(pl->query_met(query_real_name())))
        set_alarm(1.0, 0.0, &do_intro(pl));
    return "";
}

string
query_guild_name_race()
{
    return GUILD_NAME;
}

string
query_bnumen_house()
{
    return Black_Numenoreans_House;
}

int
set_bnumen_house(string str)
{
    Black_Numenoreans_House = str;
    return 1;
}

string
query_guild_title_race()
{
    return "of the House of " + query_bnumen_house();
}

int
query_guild_family_name()
{
    return 1;
}

/*
 * Function name: arm_me
 * Description:   equip the npc with weapons, armour, 
 *                and by call to equip_me with a bnumen soul.
 * Argument:      int mt_equip: true if standard Minas Tirith
 *                              equipment is to be used.
 */
public void
arm_me(int mt_equip = 1)
{
    object  wep, arm;

    ::arm_me();
    equip_me();

    if (!mt_equip)
	return;

    seteuid(getuid(TO));

    wep = clone_object(MINAS_DIR + "obj/mt_weapon");
    wep->set_weapon_type("battle axe");
    wep->move(TO);
    command("wield all");
    arm = clone_object(MINAS_DIR + "obj/mtarmour");
    arm->set_armtype(0);
    arm->set_const(3 + random(5));
    arm->set_metal(3 + random(5));
    arm->move(TO);
    arm = clone_object(MINAS_DIR + "obj/mtarmour");
    arm->set_armtype(2);
    arm->set_const(2 + random(4));
    arm->set_metal(3 + random(5));
    arm->move(TO);
    command("wear all");

}
