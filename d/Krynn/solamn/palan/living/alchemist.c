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
	 set_name("Gringo");
	 set_title("the Amazing, Alchemist from Mount Nevermind");
	 add_name(({"shopkeeper","alchemist"}));
	 set_race_name("gnome");
	 set_gender(0);
	 set_adj("beady-eyed");
	 add_adj("white haired");
	 set_long("This strange looking gnome seems to be an alchemist of sorts. " +
            "Thick black eyebrows seem permanently narrowed as he carefully mixes " +
            "liquids and components in the most professional manner. However " +
            "you find it very difficult to take him too seriously due to his " +
            "shock of wild white hair that he has had little success in controlling, " +
            "obviously a result of a failed and rather explosive experiment.\n");

	 set_act_time(5);
	 add_act("emote studies a mirky potion closely.");
         add_act("emote chatters: HmmIfOnlyIHadMoreBells...");
	 add_act("emote starts cleaning out a vial with a dirty cloth.");
	 add_act("emote chatters: DoYouWantToBuyAPotion?YesYesYes?IHaveJustTheThing!");
	 add_act("emote chatters: GullyDwarvesMakeGreatTestSubjects!UnfortunatelyI"+
            "FindMostOfMyPotionsHaveTheNegativeAffectOfLimitingTheirNumericalCapacity"+
            "ToTwo...");
	 add_act("emote puts a sprig of something into his mortar.");
	 add_act("emote carefully pours a smokey liquid into his mortar, and quickly mixes "+
            "it with the contents into a smelly paste.");

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