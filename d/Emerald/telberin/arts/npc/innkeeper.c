/*
 *  /d/Emerald/telberin/arts/npc/innkeeper.c
 *
 *  Hvaeni is the Innkeeper at the Silver Swan Inn in
 *  Telberin. He's pretty basic.
 *
 *  Location: /d/Emerald/telberin/arts/inn.c
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/telberin/npc/telberin_elf";

#include <stdproperties.h>


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
    set_living_name("hvaeni");
    set_name("hvaeni");
    add_name("hvaeni metrius");
    add_adj( ({ "proud", "well-dressed" }) );

    set_title("Metrius, Innkeeper of the Silver Swan");

    set_short("proud well-dressed elf");
    set_long("This proud elf looks quite pleased. He appears to"
      + " take pride in his work and his surroundings.\n");

    config_elf(100);  /* He's hale and somewhat hardy */

    set_act_time(20);
    add_act("emote polishes the counter with a clean white rag.");
    add_act("emote turns to the menu, and wipes a smudge off its"
          + " side.");
    add_act("emote looks around and smiles.");
    add_act("emote mumbles: I wonder if we have enough venison"
          + " for the rest of the night.");
    add_act("emote tidies up behind the counter.");

    set_cact_time(10);
    add_cact("emote tries desperately to avoid your attacks.");
    add_cact("emote peers at you in fear and anger.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote searches madly in his apron for something to"
           + " fight you with.");

    set_job_response("I am the keeper of the Silver Swan Inn. I've been"
      + " doing this for years now.");
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
