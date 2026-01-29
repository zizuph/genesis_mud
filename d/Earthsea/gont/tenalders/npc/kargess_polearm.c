/*
 * Edited long desc and changed special to real spell, 
 *     Ckrik March 2004
 *
 * 2021-01-03 - Cotillion
 * - Added clone_unique to halberg
 */
#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/gont/tenalders/npc/karg_f";
inherit "/d/Earthsea/lib/team_protect";

inherit "/lib/unique";

#define SPELLS "/d/Earthsea/gont/tenalders/obj/spells/karg_spells"
#define SP_DELAY 3

#include "/d/Earthsea/quest_handler/quest_handler.h"
#include <ss_types.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

#define BASE_PATH ("/d/Earthsea/gont/tenalders/")

static int counter = 3;


public void
create_earthsea_monster()
{
    set_name("mara");
    add_name(({"priestess", "karg", "female"}));
    add_adj(({"beautiful", "curvaceous", "warrior", "kargish"}));
    set_height("tall");
    set_width("lean");
    set_short("beautiful curvaceous kargish female");
    set_race_name("human");
    set_long("A tall shapely female warrior. She has " +
	     "midnight-black cold eyes and the visage of a Karg " +
	     "from the East Reaches. With seemingly never ending " +
	     "legs and a fine, yet curvaceous, contour it is no " +
	     "wonder the Kargs have made her a creature of worship. " +
	     "However, her slender elegant body and pretty face belies " +
	     "the obvious truth that she is quite lethal in combat.\n" +
	     "She has waist-long raven black hair.\n");
    set_gender(G_FEMALE);
    set_appearance_offset(-100);
    set_act_time(40);
    add_act("swirl cloak");
    set_stats(({200, 200, 200, 180, 160, 170}));
    set_alignment(-70);
    add_act("swing halberd");
    add_act("emote growls: I'm going to kill that stupid drummer...");
    add_act("emote grasps her head and screams, visibily shaking " +
        "her body to the rhythm of the drums.");
    add_ask(({"drummer", "about drummer", "about the drummer",
        "kill", "killing", "about killing", "about killing the drummer",
        "drum", "drums", "about drum", "about drums", "bonesman",
        "about bonesman" }),
        "The priestess snickers and says, \"That stupid " +
        "drummer doesn't know when to quit. Bring me that " +
        "little drum of his and I'll show you what it's " +
        "supposed to be used for!\"\n");
    set_default_answer("The priestess barely lifts her lips to smirk, " +
        "clearly disinterested in what you are asking.\n");
    set_all_hitloc_unarmed(50);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_WEP_POLEARM, 120);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_ACROBAT, 100);

    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, 0, random(5) }));
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    equip(({
        clone_unique(BASE_PATH + "wep/unholy_halberd", 12, BASE_PATH + "wep/spear"),
        "/d/Earthsea/gont/tenalders/arm/bust",
        "/d/Earthsea/gont/tenalders/arm/black_cloak",
        "/d/Earthsea/gont/tenalders/arm/boots",
        "/d/Earthsea/gont/tenalders/arm/ruby_ring",
        "/d/Earthsea/gont/tenalders/arm/dragon_helm",
        "/d/Earthsea/gont/tenalders/obj/items/diamond_key"
    }));

    set_vip_importance(50);

    clone_object(SPELLS)->move(this_object());

    log_my_kills("/d/Earthsea/log/npc_logs/kargess_polearm_kills", 1);
    log_my_deaths("/d/Earthsea/log/npc_logs/kargess_polearm_deaths", 1);
}

public void
dispose_errant_drum(object drum)
{
    command("shrug");
    command("emote tosses the drum off into the distance.");
    drum->remove_object();
}

public void
respond_killed_drummer2(object ob, object tp)
{
    object to = this_object(), env = environment(to);

    if(!tp || !present(tp, env) || !CAN_SEE(to, tp) ||
        !CAN_SEE_IN_A_ROOM(to, env))
    {
        dispose_errant_drum(ob);
        return;
    }

    command("say Try again. It will require total concentration.");
    command("smirk amusedly");
    command("give drum to " + tp->query_real_name());
}

public void
respond_killed_drummer(object ob, object tp)
{
    object to = this_object(), env = environment(to);

    if(!tp || !present(tp, env) || !CAN_SEE(to, tp) ||
        !CAN_SEE_IN_A_ROOM(to, env))
    {
        dispose_errant_drum(ob);
        return;
    }

    command("peer " + tp->query_real_name());
    command("say You didn't really think I wanted my own bonesman " +
        "killed, did you?");
    set_alarm(2.0, 0.0, &respond_killed_drummer2(ob, tp));
}

public void
reward_got_drum(object drum, object tp)
{
    object to = this_object(), env = environment(to);

    if(!tp || !present(tp, env) || !CAN_SEE(to, tp) ||
        !CAN_SEE_IN_A_ROOM(to, env))
    {
        dispose_errant_drum(drum);
        return;
    }

    if(QH_QUERY_QUEST_COMPLETED(tp, "bonesmans_drum"))
    {
        command("say Why would I want another drum? You've already " +
            "proven your point.");
        dispose_errant_drum(drum);
        return;
    }

    QH_QUEST_COMPLETED(tp, "bonesmans_drum");
    command("say At last! Perhaps we'll have a moment's rest.");
    command("thank " + tp->query_real_name() + " .");
    tp->catch_tell("You feel a little more experienced.\n");
    drum->remove_object();
}

public void
enter_inv(object ob, object from)
{
    int is_drum = ob->id("__es_bonesman_drum__");

    ::enter_inv(ob, from);

    if(!from)
    {
        return;
    }

    if(!is_drum)
    {
        set_alarm(0.0, 0.0, &command("emote gives it back."));
        ob->move(from, 1);
        return;
    }

    if(ob->query_prop("__es_drum_from_corpse__"))
    {
        set_alarm(2.0, 0.0, &respond_killed_drummer(ob, from));
        return;
    }

    set_alarm(2.0, 0.0, &reward_got_drum(ob, from));
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
      return 0;
    }
  return 0;
}
