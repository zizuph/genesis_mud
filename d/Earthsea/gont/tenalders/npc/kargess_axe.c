#pragma strict_types

/*
 * Edited long desc and changed special to real spell, 
 *     Ckrik March 2004
 *
 *
 */

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/gont/tenalders/npc/karg_f";
inherit "/d/Earthsea/lib/team_protect";
inherit "/lib/unique";

#define SPELLS "/d/Earthsea/gont/tenalders/obj/spells/karg_spells"
#define SP_DELAY 3

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <options.h>

static int counter = 3;

public void
create_earthsea_monster()
{
    set_name("kara");
    add_name(({ "priestess", "warrioress", "karg", "female" }));
    set_living_name("_kara_");
    add_adj(({"beautiful", "curvaceous", "warrior", "kargish"}));
    set_height("tall");
    set_width("lean");
    set_short("beautiful curvaceous kargish female");
    set_race_name("human");
    set_long("A tall shapely female warrior. She has " +
	     "emerald-green mysterious eyes and the visage of a Karg " +
	     "from the East Reaches. With seemingly never ending " +
	     "legs and a fine, yet curvaceous, contour it is no " +
	     "wonder the Kargs have made her a creature of worship. " +
	     "However, her slender elegant body and pretty face belies " +
	     "the obvious truth that she is quite lethal in combat.\n" +
	     "She has waist-long flaming red hair.\n");
    set_gender(G_FEMALE);
    set_appearance_offset(-100);
    set_act_time(40);
    add_act("swirl cloak");
    add_act("toss axe");
    set_stats(({ 180, 170, 180, 150, 150, 150}));
    set_alignment(-20);
    clone_unique("/d/Earthsea/gont/tenalders/wep/crescent_axe",
        5, "/d/Earthsea/gont/tenalders/wep/bronze_axe",
        0, 80)->move(
        this_object());
    add_equipment(({
        "/d/Earthsea/gont/tenalders/arm/emerald_cloak",
        "/d/Earthsea/gont/tenalders/arm/dragon_helm",
        "/d/Earthsea/gont/tenalders/arm/boots",
        "/d/Earthsea/gont/tenalders/arm/bust",
        "/d/Earthsea/gont/tenalders/arm/emerald_ring",
        "/d/Earthsea/gont/tenalders/obj/items/crystal_key" }));
    set_all_hitloc_unarmed(50);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_ELEMENT_FIRE, 80);
    set_skill(SS_FORM_CONJURATION, 80);
    set_skill(SS_SPELLCRAFT, 80);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_vip_importance(25);

    clone_object(SPELLS)->move(this_object());

    log_my_kills("/d/Earthsea/log/npc_logs/kargess_axe_kills", 1);
    log_my_deaths("/d/Earthsea/log/npc_logs/kargess_axe_deaths", 1);
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    query_team_others()->command("$assist " + 
				 this_object()->query_real_name());
}

public int
query_option(int opt)
{
    if(opt != OPT_UNARMED_OFF)
    {
        return ::query_option(opt);
    }

    return 1;
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
  return 0;
}
