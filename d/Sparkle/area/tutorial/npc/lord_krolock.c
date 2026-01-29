/*
 *  /d/Sparkle/area/tutorial/npc/lord_krolock.c
 *
 *  Baron von Krolock. This is his all-powerful form, which is triggered
 *  when the player completes the evil side of the quest.
 *
 *  Location: /d/Sparkle/area/tutorial/castle/destroyer_lair.c
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "silverdell_npc";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    react_items(object obj, object to);
public void    show_hook(object ob);


/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Krolock");
    set_name("krolock");
    add_name( ({ "baron von krolock", "baron krolock", "baron",
                 "_lord_krolock", "lord" }) );
    set_adj( ({ "stately", "pale-skinned", "all-powerful",
                "all", "powerful" }) );
    set_race_name("vampire");

    set_title("the Destroyer, Baron of the Night Realm");

    set_short("all-powerful vampire lord");
    set_long("Baron von Krolock has risen to new stature thanks to"
      + " your assistance. He positively glows with malevolent power."
      + " You take satisfaction in knowing that you have served him"
      + " well. Perhaps someday, you too will have the opportunity"
      + " to Lord yourself over others.\n");

    /* this seems to be the only way to allow for "exa vampire lord" /*
    add_cmd_item( ({ "vampire lord", "all-powerful vampire lord" }),
                  ({ "exa" }), long);

    set_skill(SS_WEP_SWORD, 30);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_DEFENCE,   30);
    set_skill(SS_PARRY,     25);

    add_prop(OBJ_M_NO_ATTACK, 0); /* no one will have the dis, but okay */
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(2);
    add_act("emote glares at you with souless brown eyes.");
    add_act("emote intones: You have done well, Commander.");
    add_act("emote widens his eyes and offers a heartless laugh.");
    add_act("emote intones: Greenhollow lies in ashes!");
    add_act("emote curls his lip, revealing a pearlescent white fang"
          + " beneath.");

    set_job_response("Now that I rule these lands, my job is to Lord"
      + " myself over all the pathetic inhabitants!");

    default_config_npc(200);    /* Back at full strength */
    set_alignment(-800);        /* Oh, he's evil alright. */

    setuid();
    seteuid(getuid());
} /* create_silverdell_npc */


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
        command("say Where did that fool go?");
        return;
    }

    command("introduce me");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("glare ston "+this_player()->query_real_name());
    command("say Do not trouble me with such things, Commander.");
    return "";
} /* default_answer */


/*
 * Function name:        react_items
 * Description  :        have the npc respond to a specific object
 * Arguments    :        object obj - the object that was shown
 *                       object to  - the player who showed it
 */
public void
react_items(object obj, object to)
{
    object  reward;

    set_this_player(to);

    if (obj->id("_tutorial_heart"))
    {
        command("emote intones: One wasn't enough for you, eh?");
        command("cackle");
        command("emote takes the heart and eats it!");
        obj->remove_object();
        return;
    }

    if (obj->id("_krolock_heart"))
    {
        command("emote intones: That is useless to me now!");
        command("emote snaps his fingers.");
        write("In a flash of magic, the heart bursts into flames and"
          + " is consumed!\n");
        obj->remove_object();
        return;
    }

    command("emote scowls.");
} /* react_items */


/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    set_alarm(1.0, 0.0, &react_items(ob, this_player()));
} /* show_hook */
