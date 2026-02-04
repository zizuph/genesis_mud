/*
 *  /d/Sparkle/guilds/new_merc/npc/adapt_trainer.c
 *
 *  I just copied this code from the merc trainer for use in the Vampire
 *  guild closure.
 *
 *  Created January 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../guild.h"

/* Prototypes */
public void        create_monster();
public void        introduce(object who);
public void        react_intro(object tp);


/*
 * Function name:        create_monster
 * Description  :        set up the npc
 */
public void
create_monster()
{
    set_living_name("katashi");
    set_name("katashi");
    add_name( ({ "eldest", "vampire", "vamp", "sire", "ghoul" }) );
    set_race_name("vampire");
    add_adj( ({ "pallid", "torpor", "etched", "torpor-etched" }) );

    set_title("Forsaken Eldest of the Cursed Bloodlines of Terel");

    set_short("pallid torpor-etched ghoul");
    set_long("Something terrible has happened. This, the Eldest and"
      + " most revered of Sires within the Coven has fallen into"
      + " torpor, and shall soon die forever. He beckons all who"
      + " have known his blood his <disembrace> which will release"
      + " them of the very curse which has finally come to claim"
      + " him.\n");

    set_stats( ({ 150, 180, 175, 130, 200, 190 }) );
    set_alignment(0); /* Serves no cause but his own. */

    set_default_answer(VBFC_ME("default_answer"));

    add_prop(OBJ_M_NO_ATTACK, "None shall attack the Eldest, not even"
      + " when he is in such a state as this.\n");

    set_skill(SS_WEP_SWORD, 75 + random(25));
    set_skill(SS_WEP_POLEARM, 75 + random(25));
    set_skill(SS_WEP_AXE, 75 + random(25));
    set_skill(SS_WEP_KNIFE, 75 + random(25));
    set_skill(SS_WEP_CLUB, 75 + random(25));
    set_skill(SS_DEFENCE, 75 + random(25));
    set_skill(SS_2H_COMBAT, 75 + random(25));
    set_skill(SS_BLIND_COMBAT, 75 + random(25));
    set_skill(SS_PARRY, 75 + random(25));
    set_skill(SS_DEFENCE, 75 + random(25));

    setuid();
    seteuid(getuid());
} /* create_monster */     


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    command("nod grave");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("emote says nothing, but beckons to you, offering a"
      + " <disembrace> from the curse that has come to finally claim"
      + " him.");
    return "";
} /* default_answer */


/*
 * Function name:        disembrace
 * Description  :        allow players to leave the guild
 */
public int
disembrace(string arg)
{
    if (!IS_BG(this_player()) && !IS_VAMP(this_player()))
    {
        // Cannot disembrace if you're not a vampire nor a bloodguard
        notify_fail("The pallid torpor-etched ghoul completely ignores you,"
          + " as you are not of his blood.\n");
        return 0;
    }
            
    if (arg != "forever")
    {
        notify_fail("If you wish to leave the guild, you may"
          + " <disembrace forever> now.\n");
        return 0;
    }

    write("Alas! The blood of high reknown leaves you, and you are"
      + " cleansed of its noble caress. The devastated Eldest nods"
      + " at you and bids you leave him to die.\n");

    /* Okay, Petros ... code goes here ... */
    if (IS_BG(this_player()))
    {
        this_player()->remove_bloodguard(0); // 0 == not silent
    }
    else if (IS_VAMP(this_player()))
    {
        this_player()->remove_vampire();
    }        

    return 1;
} /* disembrace */



/*
 * Function name:        init_living
 * Description  :        add actions to players
 */
public void
init_living()
{
    ::init_living();

    add_action(disembrace, "disembrace");
} /* init_living */



