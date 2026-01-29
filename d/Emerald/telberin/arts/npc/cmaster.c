/*
 * /d/Emerald/telberin/arts/npc/cmaster.c
 *
 * This old elf, Feni Arlal, is the Choir Master of Telberin. Having
 * served in this role for many many years, he has grown somewhat
 * grumpy and hard to deal with, as most people can't impress him very
 * much. He is horribly disorganized and impersonal to boot.
 *
 * Location: /d/Emerald/telberin/arts/cmasters_chambers.c
 *
 * Copyright (c) May 2000, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/std/elf";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>


/* prototypes */
public void    create_elf();
public void    introduce(object who);
public void    react_intro(object tp);


/*
 * Function name:        create_elf
 * Description  :        set up the npc
 */
public void
create_elf()
{
    set_living_name("feni");
    set_name("feni");
    add_name("feni arlal");
    set_adj("old");

    add_name("choir_master");
    set_title("Arlal, Master of the Telberin Choirs");

    set_long("This old elf looks rather grouchy. His back is bent and"
        + " his eyes are stern and preoccupied.\n");

    config_elf(60);  /* He's not the strongest fellow */

    set_act_time(20);
    add_act("emote hums quietly to himself for a moment, and then"
          + " scribbles something quickly down on a piece of"
          + " parchment.");
    add_act("emote rummages through the desk, looking for something.");
    add_act("emote grumbles to himself.");
    add_act("emote mumbles: The Sanctuary personnel are going to have"
          + " to find someone else to do their repair work from"
          + " now on!");
    add_act("emote shuffles with some papers on top of the desk,"
          + " and then returns to his writing.");

    set_cact_time(10);
    add_cact("emote tries desparately to avoid your attacks.");
    add_cact("emote peers at you in fear and anger.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote takes something from his pocket, and throws"
           + " it at you!");

    set_default_answer(
        "The old elf looks up from his desk.\n"
      + "The old elf says: I am very busy right now. Please leave"
      + " me alone, and go away.\n");

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
