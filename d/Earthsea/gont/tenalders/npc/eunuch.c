#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/team_protect";

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

public void
create_earthsea_monster()
{
    set_name("eunuch");
    add_name("guard");
    add_adj("eunuch");
    set_pname("eunuchs");
    add_name(({"karg", "guard"}));
    add_name("karg");
    set_adj(({"hairless", "muscular"}));
    add_adj("karg");
    set_short("eunuch guard");
    set_pshort("eunuch guards");
    set_race_name("human");
    set_long("This karg guard is dedicated to "+
        "protecting the priestess with its life. It is bald and "+
        "hairless, yet muscular and mean-looking.\n");
    set_gender(G_NEUTER);
    set_act_time(40);
    add_act("emote opens its mouth to show you the empty stump "+
        "where its tongue should be.");
    add_act("grin");
    add_act("growl");
    add_act("emote grunts savagely.");
    set_stats(({180, 160, 175, 125, 145, 165}));
    set_all_hitloc_unarmed(1);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_PARRY, 80);
    add_equipment(({
        ({ "/d/Earthsea/gont/tenalders/wep/bronze_axe",
        "/d/Earthsea/gont/tenalders/wep/scimitar",
        "/d/Earthsea/gont/tenalders/wep/spear",
        "/d/Earthsea/gont/tenalders/wep/club" })[random(4)],
        "/d/Earthsea/gont/tenalders/arm/loincloth",
        "/d/Earthsea/gont/tenalders/arm/collar" }));
    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, random(10), 0 }));
    add_prop(NPC_I_NO_RUN_AWAY, 1);
}

public void
intro_hook(string str)
{
    command("emote opens its mouth to show you the empty "+
        "stump where its tongue should be!");
    command("emote grunts savagely.");
}

public int
query_knight_prestige()
{
    return 20;
}

public void
attacked_by(object player)
{
    object *others = query_team_others();
    ::attacked_by(player);
    others->command("$assist");
}
