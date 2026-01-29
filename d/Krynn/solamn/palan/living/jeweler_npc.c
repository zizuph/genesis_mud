# pragma strict_types

# include "../local.h"
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>

inherit M_FILE

int alarm_id;

void
create_krynn_monster()
{
	 set_name("Serfelugal");
	 set_title("of Nevermind, Gemologist");
	 add_name(({"shopkeeper","keeper"}));
	 set_race_name("gnome");
	 set_gender(0);
	 set_adj("chubby");
	 add_adj("long-nosed");
	 set_long("This is a middle-aged gnome who seems quite excited by " +
            "gems.\n");

	 set_act_time(5);
	 add_act("emote studies a gem under the lens.");
         add_act("emote chatters: ...andThenWhileMiningInTheMountainsTo"+
            "TheEastOfTheCityWallsIFoundThisMostAmazingCompositeRock...");
	 add_act("emote lovingly polishes a gemstone.");
	 add_act("emote taps a tool against a gem.");
	 add_act("emote seems engrossed in his work.");
	 add_act("emote holds a gem up to the light.");
	 add_act("emote peers at his displays, muttering: NeedsMoreBellsAnd" +
             "Stuff.");
         add_act("emote chatters: ...FortunatelyMyUncleFinishedOurFamilyLifeQuestAllowing"+
             "MeToFollowMyPersonalHobbyOfGemComposition.");

	 set_all_hitloc_unarmed(50);

	 set_stats(({70,70,70,70,70}));

	 set_skill(SS_UNARM_COMBAT,50);
	 set_skill(SS_BLIND_COMBAT,100);
	 set_skill(SS_PARRY,50);
	 set_skill(SS_DEFENCE,65);
	 set_skill(SS_AWARENESS,50);
	 set_skill(SS_WEP_SWORD,50);
	 set_skill(SS_WEP_POLEARM,50);
	 set_skill(SS_WEP_CLUB,50);
	 set_skill(SS_WEP_KNIFE,50);
	 add_prop(NPC_I_NO_RUN_AWAY,1);

	 set_alignment(0);
	 set_knight_prestige(-1);

         set_alarm(1.0, 0.0, "equip_me");
	 set_mm_in("arrives.");
}

void
equip_me()
{

    clone_object("/d/Krynn/gnome/obj/cloak")->move(TO);
    command("wear all");

}