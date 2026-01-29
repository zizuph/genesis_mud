/*  Created by Jaypeg */

#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit "/d/Shire/eastroad/eastern/npc/dwarf_warrior";
inherit KILL_LOGGER;
inherit "/lib/unique";

void
create_dwarf()
{
    if (!IS_CLONE)
	return;	

    set_living_name("khaaz");
    set_name("khaaz");
    set_race_name("dwarf");
    set_title("Trollbane, son of Balin");
    set_long("This dwarf is apparently the leader of this troll-"+
      "hunting troop. He is confident and rugged in the extreme. "+
      "He is dressed in ugly but seemingly excellent armours, and "+
      "by the glazed look in his eyes has been hitting the booze "+
      "pretty hard. His voice booms as he tells his bawdy stories "+
      "and jokes to his comrades.\n");
    set_adj(({"rugged","confident"}));
    set_stats(({150,120,170,90,100,130}));
    MAKE_MONEY;
    set_alignment(700 + random(250));

    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_WEP_AXE,100);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 55);

    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 95);
    remove_prop(LIVE_I_NEVERKNOWN);
    set_gender(G_MALE);
    set_introduce(1);
    set_kill_log_name("khaaz");

    // Add our equipment
    clone_unique(ERWEP_DIR + "warhammer", MAX_UNIQUE_ITEMS,
      ERWEP_DIR + "battleaxe")->move(TO, 1);
    add_equipment(({ERARM_DIR + "d_ghelm",
	ERARM_DIR + "d_boots", ERARM_DIR + "d_shield", ERARM_DIR + "d_chainmail"}));

    // Clear all pervious chats and acts
    clear_act();
    clear_chat();
    clear_cact();
    clear_cchat();

    set_chat_time(6);	    
    add_chat("Pass me another mug of that brandy, lad!");
    add_chat("We'll have to take a barrel of this stuff for "+
      "refreshments while we bash dem trolls!");
    add_chat("Bottoms up lads!");
    add_chat("Aye Tribble lad, was a right choice to come on "+
      "down into this smelly hole, you've sher a nose for "+
      "the good firewater!");
    add_chat("I wish we had some stinkin' orcs to practice on!");
    add_chat("Leave the wine bottles for dem skinny elves.");
    add_chat("This brandy is better than any I've had in Ered Luin!");
    add_chat("I can't wait to smash some trolls!");
    add_chat("All dat treasure! Just between us lads!");
    add_chat("Dibble! Help ya ol' uncle outa this rat hole!");

    set_act_time(7);
    add_act("roar");
    add_act("laugh");
    add_act("sneeze");
    add_act("drink brandy");
    add_act("ponder if there's enough trolls for everyone in Rhudaur.");
    add_act("emote roars in laughter like thunder.");
    add_act("emote slaps you heartily on the back. You think he "+
      "might have broken one of your ribs.");
    add_act("emote dips his large mug into a barrel.");
    add_act("emote tugs the knots out of his thick beard.");
    add_act("emote tells a bawdy joke about a goblin and a warg.");
    add_act("emote sings a ditty about trolls and their treasure.");

    set_cact_time(6);
    add_cact("shout Die! Ya orc lovin' scum!");
    add_cact("emote lines you up and charges at you.");
    add_cact("emote calls on the Valar for assistance.");
    add_cact("emote screams: RUN ye bunch o' yella-backs!");

    set_cchat_time(4);
    add_cchat("I'll pound ya hide into dust you loser!");
    add_cchat("Git 'em lads!!");
    add_cchat("Tulkas and Aule! Give me strength!");
    add_cchat("Nobody gets between me and me treasure!");

}

void
attacked_by_hook(object obj)
{
    command("say So ya wanna scrap wit me, huh?!");
    command("emote charges into combat with battle lust "+
      "in his eyes.");
}
