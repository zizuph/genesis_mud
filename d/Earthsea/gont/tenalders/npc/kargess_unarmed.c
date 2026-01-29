#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/gont/tenalders/npc/karg_f";
inherit "/d/Earthsea/lib/team_protect";
inherit "/lib/unique";

#define SPELLS "/d/Earthsea/gont/tenalders/obj/spells/karg_spells"
#define SP_DELAY 3

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

static int counter = 3;

public void
create_earthsea_monster()
{
    set_living_name("_ara_");
    set_name("ara");
    add_name("_ara_");
    add_name("karg");
    add_name("female");
    add_adj(({"beautiful", "curvaceous", "warrior", "kargish"}));
    set_height("tall");
    set_width("lean");
    set_short("beautiful curvaceous kargish female");
    set_race_name("human");
    set_long("A tall shapely female warrior. She has " +
	     "sky-blue intense eyes and the visage of a Karg " +
	     "from the East Reaches. With seemingly never ending " +
	     "legs and a fine, yet curvaceous, contour it is no " +
	     "wonder the Kargs have made her a creature of worship. " +
	     "However, her slender elegant body and pretty face belies " +
	     "the obvious truth that she is quite lethal in combat.\n" +
	     "She has shoulder-long wavy dirty-blond hair.\n");
    set_gender(G_FEMALE);
    set_appearance_offset(-100);
    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, 0, random(5) }));
    set_chat_time(130);
    add_chat("My sisters and I will join forces to rule Earthsea!");
    set_act_time(40);
    add_act("swirl cloak");
    set_stats(({190, 190, 190, 160, 160, 180}));
    set_alignment(-20);
    set_all_hitloc_unarmed(50);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 110);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_ELEMENT_FIRE, 90);
    set_skill(SS_FORM_CONJURATION, 90);
    set_skill(SS_SPELLCRAFT, 90);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    clone_object(SPELLS)->move(this_object());

    log_my_kills("/d/Earthsea/log/npc_logs/kargess_unarmed_kills", 1);
    log_my_deaths("/d/Earthsea/log/npc_logs/kargess_unarmed_deaths", 1);
    clone_unique("/d/Earthsea/gont/tenalders/arm/gauntlets",
        5, "/d/Earthsea/gont/tenalders/wep/club",
        0, 80)->move(
        this_object());

    set_vip_importance(25);

    add_equipment(({
        "/d/Earthsea/gont/tenalders/arm/black_ring",
        "/d/Earthsea/gont/tenalders/arm/velvet_cloak",
        "/d/Earthsea/gont/tenalders/arm/boots",
        "/d/Earthsea/gont/tenalders/arm/bust",
        "/d/Earthsea/gont/tenalders/arm/dragon_helm",
        "/d/Earthsea/gont/tenalders/obj/items/mithril_key" }));
}

public void
attacked_by(object ob)
{
    query_team_others()->command("$assist " + 
				 this_object()->query_real_name());
    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
  if (++counter >= SP_DELAY + random(2))
    {
      counter = 0;
      this_object()->command("$cast fireball");
      return 1;
    }

  if (!random(30))
    {
      trash_talk(enemy);
    }
  return 0;
}

