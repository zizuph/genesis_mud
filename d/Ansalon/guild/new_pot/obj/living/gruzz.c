/* Ashlar, 4 Oct 97
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "npc.h"

inherit "/d/Ansalon/guild/new_pot/obj/living/npc";

void arm_me();

void
create_pot_monster()
{
    if(!IS_CLONE)
	return;

    set_name("gruzz");
    set_living_name("gruzz");
    set_introduce(1);
    set_title("Chief of the Dungeon Guard");
    add_name("guard");

    set_race_name("goblin");
    set_adj("big");
    add_adj("swarthy");
    set_long("This goblin is the chief of the dungeon guard. " +
    "He is big for a goblin, and sprouts swarthy hair all over " +
    "his body.\n");

    add_prop(CONT_I_HEIGHT, 140);
    add_prop(CONT_I_WEIGHT, 55000);

    set_stats(({ 160, 130, 160, 90, 90, 150 }));
    set_hp(query_max_hp());

    unset_priest();

    set_skill(SS_WEP_CLUB,          100);
    set_skill(SS_DEFENCE,           100);
    set_skill(SS_PARRY,             100);
    set_skill(SS_AWARENESS,         100);

    set_all_hitloc_unarmed(6);

    set_alignment(-800);
    set_knight_prestige(800);

    set_act_time(14);
    add_act("say If you start dem troubles I will lock yas up!");
    add_act("growl");
    add_act("emote looks around carefully.");
    add_act("emote stares at you.");

    set_cact_time(5);
    add_cact("say Dis will get yas killed!");
    add_cact("emote screams in rage.");

    set_default_answer(QCTNAME(TO) + " seems confused.\n");

    add_ask(" [about] [the] 'club' ","say Yah, with dem clubz you can " +
    "hit dem .. people .. on da head! It is very useful!", 1);
    add_ask(" [about] 'defence' ","say Ohoho, dat what I use, so's " +
    "noone hitz me!", 1);
    add_ask(" [about] [the] 'dungeon' ","say I guardz the dungeon. Nem " +
    "isn't in there.", 1);
    add_ask(" [about] 'nem' ","emote taps his nose distinctly and smiles " +
    "secretively.", 1);
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    clone_object(NWEP + "mace")->move(TO,1);
    clone_object(NARM + "chain_shirt")->move(TO,1);
    clone_object(NARM + "steel_helm")->move(TO,1);

    command("wear all");
    command("wield all");

    ::arm_me();
}

string
query_guild_title_race()
{
    return "Nawng";
}

int
query_guild_family_name()
{
    return 1;
}
