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
    add_name( ({ "eldest", "vampire", "vamp", "sire", "ghoul",
                 "statue" }) );
    set_race_name("vampire");
    add_adj( ({ "pallid", "torpor", "etched", "torpor-etched",
                "lifelike", "life", "like", "marble", "white" }) );

    set_title("Forsaken Eldest of the Cursed Bloodlines of Terel");

    set_short("lifelike marble statue");
    set_long("Sitting in quiet and stately grace is perhaps the most"
      + " lifelike human statue you have ever seen. The surface of"
      + " the white marble is intricately detailed down to the most"
      + " subtle crease or fold of skin. More unusual still is the fact"
      + " that actual clothing dresses the stone, as if some artisan" 
      + " went to the trouble to sew garments on the statue after it"
      + " had been crafted. The expression on the face is inscrutable,"
      + " yet you yourself begin to feel a strange sense of melancholy,"
      + " and even loss the longer you gaze.\n");

    set_stats( ({ 150, 180, 175, 130, 200, 190 }) );
    set_alignment(0); /* Serves no cause but his own. */

    set_default_answer(VBFC_ME("default_answer"));

    add_prop(OBJ_M_NO_ATTACK, "What would be the point?\n");

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
    command("emote remains perfectly still.");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("emote offers you no reply, or indication of knowing that"
      + " you had spoken.");
    return "";
} /* default_answer */




