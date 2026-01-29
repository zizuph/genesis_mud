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
#include "../local.h"
#include "/d/Ansalon/taman_busuk/neraka/guild/guild.h"

inherit AM_FILE

#define ARM1 MEDALLION_OBJ

#undef DEBUG
#define DEBUG(x)    (find_player("ashlar")->catch_msg("PRIEST: " + x + "\n"))

void arm_me();

int is_speaking = 0;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("erdin");
    set_introduce(1);
    add_name("priest");

    set_race_name("gnome");
    set_adj("short");
    add_adj("dark-cloaked");
    set_long("Not much can be seen about this gnome as he hides himself " +
    "behind a dark cloak.\n");

    add_prop(CONT_I_HEIGHT, 135);
    add_prop(CONT_I_WEIGHT, 35000);

    set_stats(({ 100, 110, 100, 130, 130, 110 }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          70);
    set_skill(SS_DEFENCE,           55);
    set_skill(SS_PARRY,             50);
    set_skill(SS_AWARENESS,         65);
    set_skill(SS_SPELLCRAFT,        65);
    set_skill(SS_ELEMENT_LIFE,      65);
    set_skill(SS_ELEMENT_AIR,       65);
    set_skill(SS_FORM_DIVINATION,   65);
    set_skill(SS_FORM_ENCHANTMENT,  60);
    set_skill(SS_FORM_ABJURATION,   60);

    set_skill(PS_GUILD_LEVEL, 70);
    set_skill(PS_SPELLS, -1);

    set_all_hitloc_unarmed(10);

    set_alignment(-800);
    set_knight_prestige(800);

    set_act_time(17);
    add_act("say BeCarefulWithThatBeaker!");
    add_act("emote studies some device.");

    set_cact_time(5);
    add_cact("say I curse you!");
    add_cact("sneer");
    add_cact("say The hatred of the Dark Queen will follow you to your grave!");

    set_default_answer(QCTNAME(TO) + " looks at you askance.\n");

    add_ask("[dragon] 'scale' / 'scales'",
        "say IKnowSomeThingsAboutDragonScales.DoYouNeedThemForIngredients?ShowMeWhatYouNeedThemFor",
        1);
    add_ask("[for] 'help' / 'hint'",
        "say IfYouNeedHelpWithSomething,ShowItToMe,AndIWillGiveYouWhatAdviceICan.",
        1);

}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    clone_object(POTSHADOW)->add_occ_shadow(TO);

    TO->init_occ_shadow();
}

int
second_life(object killer)
{
    setuid();
    seteuid(getuid());
    A_KILL_LOG("pot/npckills","Erdin",killer);
    return 0;
}

void
ded_hint(object pl, int round)
{
    if (environment(pl) != environment(this_object()))
        return;

    switch(round)
    {
        case 0:
            say(" peers the scroll.\n");
            break;

        case 1:
            command("say AhYes,It'sThatOne.TheIngredientsCanBeVery" +
            "HardToFind.EspeciallyTheScalesTheDragonsAreReluctantTo" +
            "GiveUsScalesEvenWhenWeTellThemIt'sForResearch.TheyAre" +
            "VeryTouchy.");
            command("pout");
            break;

        case 2:
            command("say LuckilyThereIsAnotherWay.AllThisOldLoreIs" +
            "WellAndGood,ButManyThingsAreRedundantAndUnnecessary." +
            "ForExampleDoYouKnowThatTheHealingSpellOriginally" +
            "RequiredAPinchOfBlackSand,ABucketOfWaterAndTwoCatpaws?");
            break;

        case 3:
            command("say No,NotManyKnowThat.Still,WeSimplifiedThat" +
            "One,AndOthersAswell.TheWorkWeDoHereIsOftenUnderestimated." +
            "FewRealiseThatWithoutOurResearchHereTheyWouldHaveTo" +
            "CarryAroundSeveralPackmulesWithIngredientsForTheirSpells.");
            break;

        case 4:
            command("say ButToTheCaseInHand.ThisRitualWorksJustAsWell" +
            "WithJustAMugOfTheDrinkCalled'BlackDragonbrew'WhichIsSold" +
            "AtAnInnHereInNeraka.ThatDrinkContainsAllTheActive" +
            "ComponentsRequiredForTheRitual.");
            break;

        case 5:
            command("smile . " + pl->query_real_name());
            is_speaking = 0;
            break;
    }

    if (round < 5)
        set_alarm(10.0,0.0, &ded_hint(pl, round+1));
}


/*
 * This function is called when the npc is shown something.
 */
void
show_hook(object ob)
{
    if (ob->id("scroll_of_dedication") && !is_speaking)
    {
        is_speaking = 1;
        ded_hint(this_player(), 0);
    }
}
    
