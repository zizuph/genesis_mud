/*
 *  /d/Emerald/north_shore/village/npc/elf_child.c
 *
 *  Ogre fodder. Oh, the humanity!
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/elf"; 

#include <const.h>


/* Prototypes */
public void        create_elf();
public void        attacked_by(object ob);
public void        child_react();


/*
 * Function name:        create_elf
 * Description  :        set up the npc with presets
 */
public void 
create_elf() 
{
    string   rnd_adj = one_of_list( ({ "boystrous", "tiny",
                                       "freckled", "rosy-cheeked",
                                       "cute", "wee",
                                       "squirmy", "small",
                                       "quiet", "simple", }) );

    config_elf(5 + random(5)); 
    set_gender(one_of_list( ({ G_MALE, G_FEMALE }) ) );

    set_name("child");
    set_pname("children");
    add_name( ({ "kid", "_elf_child" }) );
    add_adj( ({ rnd_adj, "little", }) );
    set_short(rnd_adj + " elf child");
    set_pshort(rnd_adj + " elf children");
    set_long("This " + rnd_adj + " little elf looks hardly old"
      + " enough to lift a sword. " + capitalize(query_pronoun())
      + " seems rather oblivious to the forboding nature of the"
      + " nearby woods. Perhaps such little children should listen"
      + " to the warnings of their parents more often.\n");

    set_act_time(5);
    add_act("emote jumps up and down.");
    add_act("emote twirls in place, giggling.");
    add_act("emote peeps: Papa says the woods are dangerous! I think"
      + " they are fun!");
    add_act("emote capers energetically about.");
    add_act("emote balances on one foot and falls over laughing.");
    add_act("emote throws a rock up in the air.");
    add_act("emote peeps: This is fun! I'm glad we didn't listen to"
      + " the elders!");
    add_act("emote peeps: Who cares about Ogres. They don't scare me!");
    add_act("emote draws a picture in the dust.");

    set_cact_time(4);
    add_cact("emote runs in circles, screaming wildly!");
    add_cact("emote screams: Papa! Papa!!");
    add_cact("emote shrieks in terror!");
    add_cact("emote tries to hide.");
    add_cact("emote shrieks: Help! Oh Daddy help!!");
    add_cact("scream");
} /* create_elf */


/*
 * Function name:        attacked_by
 * Description  :        allow the npc to react to an attack
 * Arguments    :        object enemy - the one who attacked us
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(1.0, 0.0, child_react);
} /* attacked_by */


/*
 * Function name:        child_react
 * Description  :        the child reacts to an attack
 */
public void
child_react()
{
    switch(random(5))
    {
        case 0:
        {
            command("emote turns white as a sheet.");
            break;
        }
        case 1:
        {
            command("emote screams in terror at you!");
            break;
        }
        case 2:
        {
            command("command shout No! Go away!");
            break;
        }
        case 2:
        {
            command("command shout No! Go away!");
            break;
        }
        case 3:
        {
            command("emote begins trembling and crying.");
            break;
        }
        case 4:
        {
            set_alarm(1.0, 0.0, &command("command climb tree"));
            break;
        }
    }
} /* child_react */