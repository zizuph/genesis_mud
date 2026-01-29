/*
 *  /d/Sparkle/area/tutorial/npc/krolock.c
 *
 *  Baron von Krolock. This is the Scourge of Silverdell himself.
 *
 *  Location: /d/Sparkle/area/tutorial/castle/combat_lair.c
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
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


/* global variables */
public int     Garlic_Effect = 0; /* Is Krolock weakened? */

/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    garlic_effect();
public void    attempt_restore();
public string  describe();
public void    init_living();
public void    notify_death(object killer);



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
                 "_tutorial_krolock" }) );
    set_adj( ({ "stately", "pale-skinned" }) );
    set_race_name("vampire");

    set_title("the Destroyer, Baron of the Night Realm");

    set_long(describe);

    default_config_npc(200);  /* Huge, when not affected by garlic */
    set_alignment(-800);      /* Oh, he's evil alright.            */

    set_skill(SS_WEP_SWORD, 1);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_DEFENCE,   1);
    set_skill(SS_PARRY,     1);

    set_act_time(2);
    add_act("emote glares at you with soulless brown eyes.");
    add_act("emote intones: Silverdell will be mine soon enough.");
    add_act("emote widens his eyes and offers a heartless laugh.");
    add_act("emote intones: My minions will burn Greenhollow to the"
          + " ground.");
    add_act("emote curls his lip, revealing a pearlescent white fang"
          + " beneath.");

    add_prop(OBJ_M_NO_ATTACK, 0); /* You can kill him. */
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_job_response("I kill people who ask me such questions!");

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
 * Function name:        arm_me
 * Description  :        give the npc his armament
 */
public void
arm_me()
{
    object    weapon = clone_object(WEP_DIR + "krolock_sword");

    weapon->move(this_object());
    command("wield all");
} /* arm_me */


/*
 * Function name:        garlic_effect
 * Description  :        When he smells garlic, Krolock shrinks down
 *                       to manageable size.
 */
public void
garlic_effect()
{
    object  here = environment(this_object());

    if (!present("_tutorial_garlic", deep_inventory(here)))
    {
        return;
    }

    command("emote chokes suddenly on the scent of garlic!");
    command("emote intones: WHAT! WHO DARES to bring ... ");
    command("emote slumps to his knees.");
    command("emote intones: ... garlic ... here ...");
    command("emote struggles to his feet, looking far weaker than"
      + " before.");

    set_stats( ({ 5, 5, 40, 5, 5, 5 }) );
    Garlic_Effect = 1;

    set_alarm(20.0, 0.0, attempt_restore);
} /* garlic_effect */


/*
 * Function name:        attempt_restore
 * Description  :        Every so often, Krolock tries to recover from
 *                       the garlic effect.
 */
public void
attempt_restore()
{
    object  here = environment(this_object());
    string *reactions = ({ "clutches his chest and shudders.",
                           "intones weakly: ... the garlic ...",
                           "coughs weakly.",
                           "chokes on the garlic scent.",
                           "looks ill and peers at you with hatred." });

    if (!present("_tutorial_garlic", deep_inventory(here)))
    {
        command("emote seems to have returned to his normal strength.");
        default_config_npc(200);
        Garlic_Effect = 0;

        return;
    }

    command("emote " + one_of_list(reactions));
    set_alarm(20.0, 0.0, attempt_restore);
} /* attempt_restore */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant long description for
 *                       the npc
 * Returns      :        string - the description
 */
public string
describe()
{
    string  txt = "Tall, thin, and gaunt, this imposing figure is"
                + " none other than Baron von Krolock. He positively"
                + " radiates evil. ";

    if (Garlic_Effect)
    {
        return txt + "He is clutching his chest, and appears to be"
                   + " struggling with some kind of affliction at"
                   + " the moment. In fact, it doesn't look like he"
                   + " would actually be all that deadly an opponent"
                   + " due to his current condition.\n";
    }

    return txt + "Never in your darkest dreams could you ever hope to"
               + " face such a foe and live. Being in his presence"
               + " brings such fear to your heart that you can"
               + " hardly keep yourself standing.\n";
} /* describe */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("glare "+this_player()->query_real_name());
    command("say Do not bother me with questions.");
    return "";
} /* default_answer */


/*
 * Function name:        init_living
 * Description  :        trigger the garlic effect every time a new
 *                       player enters the presence of krolock.
 */
void
init_living()
{
    ::init_living();

    set_alarm(5.0, 0.0, &garlic_effect(this_player()));
} /* init_living */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 *                additionally, move them to the 
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    object  weapon;
    object  destination;

    tell_room(environment(this_object()),
        QCTNAME(this_object()) + " drops his weapon and falls"
      + " lifeless to the ground.\n");

    if (living(killer))
    {
        tell_object(killer, 
            "You have slain Baron von Krolock!\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " has slain Baron von Krolock!\n",
           ({ this_object(), killer }));
    }

    tell_object(killer, "You pick up the weapon of your defeated foe.\n");
    weapon = clone_object(WEP_DIR + "krolock_sword");

    /* Force move is OK since this is newbies */
    weapon->move(killer, 1);

    tell_object(killer, "A tutorial sign appears in a puff of smoke.\n");

    set_this_player(killer);
    SET_TUTORIAL_BIT(KROLOCK_BIT);

    destination = clone_object(CASTLE_DIR + "defeat_lair");
    this_player()->add_prop(LAIR_PROP, destination);
    this_player()->move_living("M",
        this_player()->query_prop(LAIR_PROP)->get_this_object(), 1, 1);

    //environment(this_object())->reset_room();
    //set_alarm(0.1, 0.0, &remove_object());
	set_alarm(0.1, 0.0, &(environment(this_object()))->remove_object());
} /* notify_death */
