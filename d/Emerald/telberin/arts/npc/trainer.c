/*
 *  /d/Emerald/telberin/arts/npc/trainer.c
 *
 *  Delnarra is a reknown master of the dramatic arts
 *  in Telberin, and will teacher her craft to those
 *  who are interested.
 *
 *  Location: /d/Emerald/telberin/arts/grove.c
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <const.h>


/* prototypes */
public void    create_telberin_elf();
public void    introduce(object who);
public void    react_intro(object tp);


/*
 * Function name:        create_telberin_elf
 * Description  :        set up the npc
 */
public void
create_telberin_elf()
{
    set_living_name("delnarra");
    set_name("delnarra");
    add_name("delnarra ovan");
    add_name("thespian");
    set_adj( ({ "intense", "brightly-dressed" }) );
    set_gender(G_FEMALE);

    set_title("Ovan, High Dramatist of the Actors Guild");

    set_long("With a penetrating gaze, this tall and slender"
      + " elf regards her surroundings with an air of confidence"
      + " and entitlement. She is dressed in vibrant colors, and"
      + " flowing fabric. She is here to represent the arts of"
      + " her craft to the public, and offer training to those"
      + " who wish it.\n");

    config_elf(80);  /* She's an actor, not a fighter */

    set_act_time(20);
    add_act("emote paces dramatically from side to side.");
    add_act("emote stands with feet apart, reciting prose with"
      + " confidence and authority.");
    add_act("emote narrows her eyes, and raises her chin.");
    add_act("emote casts her hand against her brow, uttering:"
      + " For thee, my Lord, have my duties been in vain!");
    add_act("emote mutters: So many hopefuls, and yet so few"
      + " with any promise ...");

    set_cact_time(10);
    add_cact("emote tries desparately to avoid your attacks.");
    add_cact("emote peers at you in fear and anger.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote declares: Would that I had choreographed more"
      + " fight scenes!");

    set_job_response("I am a trainer of the dramatic arts. If you"
      + " desire to <learn> or <improve> skills with me, I am at"
      + " your service.");
} /* create_elf */


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
    if (!present(tp, environment(this_object())))
    {
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */
