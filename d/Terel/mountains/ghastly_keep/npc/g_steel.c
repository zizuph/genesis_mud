/* /d/Terel/mountains/ghastly_keep/npc/g_steel.c
 *
 *  A Questmaster in the Ghastly Keep
 *
 *  Steel Wildtoe was frozen to the ground by Sabine Scarletwound, and her
 *  wide selection of potions.
 *
 *  Steel seeks now revenge, and he believes the ghastly tears is somehow 
 *  connected to the magic that drives the cruel creatures in the basement
 *  of the Ghastly Keep.   
 *   
 *
 *  Created by Znagsnuf.
 *
 *
 *  Relase date:
 *
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  22/04-17                   Altered the Quest somehow               Znagsnuf
 *  23/04-17                   Fixed typos                             Znagsnuf
 *  26/04-17                   Altered turn-ins to 20 tears            Znagsnuf
 *  28/04-17                   Added more add_ask                      Znagsnuf
 *  30/04-17                   Made the Quest_log better looking       Znagsnuf
 */

inherit "/std/monster";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "../npc_stats.h";
#include "/d/Terel/include/quest_bits.h";

public void add_introduced(string name);
public void react_to_intro(object tp);
public int check_item(object item, object from);
public void discard_item(object item);

/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_monster()
{
    seteuid(getuid());

    set_living_name("Steel");
    set_race_name("human");
    set_title("Wildtoe, Old Merchant");
    set_name("steel");
    add_name("_ghastly_keep_npc_steel");
    add_name("human");

    add_adj( ({ "bitter", "male", "blue-haired" }) );    
    set_short("bitter blue-haired male human");

    set_long("Pale, icy teeth adorn the ragged pines, snarling "
            + "down over his frozen body. A pristine white pelt cut "
            + "from a wolf cloaks the earth, stained with shades of "
            + "red and crimson blood where he sits, sunken awkwardly "
            + "into the snow, gazing listlessly at the murky heavens, "
            + "where the horned moon dances around wisps of silvery "
            + "clouds. His shuddering breath mists the chilly air before "
            + "him, once, twice..\n");

    set_gender(G_MALE);

                                    //  Just random numbers
                                    //  nothing to do with
                                    //  the creator. :)                
    add_prop(CONT_I_WEIGHT, 75000); //  75kg. 
    add_prop(CONT_I_HEIGHT, 180);   // 180cm.

    set_stats( ({100, 150, 100, 40, 40, 100}) );

    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      1);

    // Needed for the Quest
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    set_act_time(5);
    add_act("emote huddles in the cold, his shuddering breath misting "
           + "the chill air before him.");
    add_act("emote gazes listlessly into the chill air.");
    add_act("shiver viol");

    // He's frozen to the ground.
    add_prop(LIVE_S_EXTRA_SHORT, ", frozen to the ground he sits upon");
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(OBJ_S_WIZINFO,"This is the Questmaster outside the "
                          + "Ghastly Keep.\n");

    // Questmaster
    add_prop(OBJ_M_NO_ATTACK,"The bitter blue-haired male human is protected "
                            + "by a strong field of magic!\n");

    add_prop(OBJ_M_NO_MAGIC_ATTACK,"The bitter blue-haired male human is "
                                  + "protected by a field of magic!\n");

    add_ask( ({ "task", "quest", "help" }), 
        VBFC_ME("task_answer"));
    add_ask( ({ "door", "second level", "down" }), 
        VBFC_ME("door_answer"));
    add_ask( ({ "dragon", "beast", "wyrm" }), 
        VBFC_ME("dragon_answer"));
    add_ask( ({ "creatures", "creature", "inhabitants", "ghost", "sentry",
                "sentinel", "guardian" }), 
        VBFC_ME("creatures_answer"));
    add_ask( ({ "witch", "sabine" }), 
        VBFC_ME("witch_answer"));
    add_ask( ({ "tear", "tears", "ghastly tear" }), 
        VBFC_ME("tear_answer"));
    add_ask( ({ "finish", "complete", "completed", "finished", 
                "kill", "killed" ,"done", "reward", "collected" }), 
        VBFC_ME("done_answer"));
    set_default_answer(VBFC_ME("default_answer"));
}

void
remove_tears()
{
    object tears = present("_ghastly_keep_tear", this_object());
    if (objectp(tears))
        tears->remove_object();
}

public void
enter_inv(object item, object from)
{
    ::enter_inv(item, from);

    // Only want objects.
    if (!objectp(from))
        return;  

    // Do nothing if the player ain't see.
    if (!CAN_SEE(TO, from) || !CAN_SEE_IN_ROOM(TO))
    {
        command("stare");
        command("say Hello? Anyone there?");

        // Drop unwanted items
        set_alarm(1.0, 0.0, &discard_item(item));
        return;
    }

    // Only works if the person has started the quest.
    if(item->id("_ghastly_keep_tear") && from->query_prop("_gkeep_task_started"))
    {
        set_alarm(1.0, 0.0, &check_item(item, from));
        return;
    }

    // Drop unwanted items
    set_alarm(1.0, 0.0, &discard_item(item));
}

void
check_item(object item, object from)
{
    object player;
    int k, r;

    player = from;

    if (!item) 
        return;

    int count = 1;
    if (item->query_prop(HEAP_I_IS))
        count = item->num_heap(); 

    object tracker = present(GKEEP_KILL_TRACKER, from);
    if (tracker && tracker->query_kills() >= count)
    {

        // Closer to the goal
        player->inc_prop(GKEEP_STONE_DELIVERY, count);

        // Remove the kills to keep track 
        tracker->add_kill(-count);

        tell_room(ETO, QCTNAME(TO) + " squeezes the last magical drops of "
            + "liquid out of the " + QSHORT(item) + ", with his bare "
            + "hands.\n", TO);

        // Removing the tear.
        item->remove_object();
        return;
    }    

    // Steels looks at you in disbelief. Why trick an old man
    player->catch_tell(query_The_name(TO) + " looks at you with disbelief.\n");
    tell_room(ETO, QCTNAME(TO) + " looks at " + QTNAME(player) + " with "
              + "disbelief.\n", player);

    tell_room(ETO, QCTNAME(TO) + " drops " + LANG_ASHORT(item) + ".\n", TO);
    // Drop the item
    item->move(ENV(TO));
 
    command("say I might be old, but I'm not a fool.");
    command("say I asked you!");
    command("point " + player->query_real_name());
    command("say To collect the ghastly tears, not to steal from others.");
    command("curse " + player->query_real_name());
    remove_tears();
}

public void
discard_item(object item)
{
    string find_name, domain_name;
    string *explode_name;

    if (!item) 
        return;

    // Extract the domain name from the file_name string.
    find_name = file_name(item);
    explode_name = explode(find_name, "/");
    domain_name = explode_name[2];

    switch (random(3))
    {
    case 0:
        command("say I have seen this item in " + domain_name + " before!");
        command("smile secret");
        break;
    case 1:
        command("say I recall this item from one of my trips to " 
                + domain_name + ".");
        command("smile dream");
        break;
    case 2:
        command("say Ahh, what a lovely item from " + domain_name + ".");
        break;   
    }

    item->move(ENV(TO));
    command("say But, I'm afraid this " + item->query_short() + " will not "
          + "aid me in my case, traveler.");

    tell_room(ETO, QCTNAME(TO) + " places the " + item->query_short() + " on "
        + "the frozen ground.\n", TO);

}

/*
 * Function name: task_answer
 * Description  : reply to questions about a task
*/

public string
task_answer()
{
    if (TP -> test_bit("Terel", TEREL_GHASTLY_KEEP_GROUP, 
        TEREL_GHASTLY_KEEP_BIT))
    {
        command("shrug");
        command("say My friend, you have already assisted me with this "
              + "perilous work.");

        return "";
    }
    
    if (TP->query_prop("_gkeep_task_started"))
    { 
        command("shrug");
        command("say Your task doesn't get any easier if you ask "
               + "me what to do all the time.");
        command("say Now, bring me those ghastly tears!");
        command("say Let me know when you have completed your task.");
        return "";
    }

    switch (random(2))
    {
    case 0:
        command("say Yes, I have a problem you might assist me with. "
            + "I don't dare enter the basement because of its inhabitants.");
        command("say Could you help me eradicate some? Bring me their ghastly "
              + "tears as a proof you have killed them!"); 
        command("say Let me know when you have completed your task.");
        TP->add_prop("_gkeep_task_started", 1);
        break;
    case 1:
        command("say Kill them! Kill them all! The basement is filled "
              + "with nasty creatures. Slaughter them, and bring me their "
              + "ghastly tears!");
        command("say Let me know when you have completed your task.");
        TP->add_prop("_gkeep_task_started", 1);
        break;
    }
    return "";
} /* task_answer */

/*
 * Function name: creatures_answer
 * Description  : reply to questions about a task
*/

public string
creatures_answer()
{
    switch (random(2))
    {
    case 0:
        command("sneer violent");
        command("say Yes, I have a problem you might assist me with.");
        command("say I don't dare enter the basement because of its "
              + "inhabitants.");
        command("say Could you help me eradicate them?");
        command("say Collect the ghastly tears they leave behind, and "
              + "bring them to me quickly.");
        break;
    case 1:
        command("cheer eag");
        command("say Kill them! Kill them all! The basement is filled "
            + "with nasty creatures. Kill them, and bring me their ghastly "
            + "tears!");
        break;
    }
    return "";
} /* creatures_answer */

/*
 * Function name: tear_answer
 * Description  : reply to questions about a the tears
*/

public string
tear_answer()
{
    switch (random(2))
    {
    case 0:
        command("think");
        command("say Stay a while, and listen!");
        command("say Somehow the ghastly tears are connected to the dark magic"
              + " that controls the creatures in the basement.");
        break;
    case 1:
        command("smile sec");
        command("say The ghastly tears are oozing with magical powers, be "
              + "careful around them.");
        break;
    }
    return "";
} /* tear_answer */

/*
 * Function name: done_answer
 * Description  : reply to questions about a task
*/

public string
done_answer()
{
    string collected, race, l_file;

    collected = TP->query_prop(GKEEP_STONE_DELIVERY);
    race = TP->query_race_name();

    if (TP -> test_bit("Terel", TEREL_GHASTLY_KEEP_GROUP, 
        TEREL_GHASTLY_KEEP_BIT))
    {
        command("shrug");
        command("say My friend, you have already assisted me with this "
              + "perilous work.");

        return "";
    }

    switch (collected)
    {
    case 0..1:
        command("curse violent");
        command("say Done? Are you done? You haven't even started.");
        command("say You won't accomplish much in life with this "
               + "attitude.");
        command("say Bring me some more ghastly tears! And make haste, hero!");
        break;
    case 2..4:
        command("curse angrily");
        command("say I understand your intentions are pure, but your "
               + "task is far from fulfilled, " +race+ ".");
        command("say I still want you to bring me more tears!");
        break;
    case 5..7:
        command("curse");
        command("say Don't bore me with your mindless mumble."); 
        command("say Bring me some more ghastly tears, before you pester "
              + "me again.");
        break;
    case 8..10:
        command("yawn");
        command("say Getting there, I'd say. But you've only collected about"
              + " half as many as I need!");
        break;
    case 11..13:
        command("nod slow");
        command("say Listen " +race+ ", you are getting closer to your "
                + "mark, but do you have problems counting?");
        command("say Are there more tears to be collected, or are they all "
                + "gone?");
        break;
    case 14..19:
        command("smile slow");
        command("say Keep up the superb work, " +race+ "!");
        command("say I know that venturing down into the basement is perilous"
               + " work, but we are getting so close!");
        command("say Rush back, and wipe out the remaining invaders!");
        command("say And don't forget their ghastly tears!");
        break;
    case 20..1000:
        command("cheer");
        command("say Finally! You collected a total of " +collected+ " ghastly "
              + "tears from the creatures in the basement."); 
        command("say Excellent work. I've nearly the confidence to venture "
               + "down there myself, now!");

        // Remove the Quest prop
        TP->remove_prop("_gkeep_task_started", 1);
        TP->remove_prop(GKEEP_STONE_DELIVERY, 1);

        // Add prop so they can enter the second level
        present(GKEEP_KILL_TRACKER, TP)->add_kill(100);

        TP->add_exp_quest(TEREL_GHASTLY_KEEP_EXP);    
        TP->set_bit(TEREL_GHASTLY_KEEP_GROUP, TEREL_GHASTLY_KEEP_BIT);

        TP->catch_msg("You feel slightly more experienced!\n");
        tell_room(ETO, QCTNAME(TP) + " feels slightly more experienced.\n", TP);

        l_file = ("Quest completed by: ("+CAP(TP->query_real_name())+ ") with "
            + "Stat Avg: ("+ (TP->query_average_stat()) + ")\t Reward "
            +TEREL_GHASTLY_KEEP_EXP+ ". At: "+ (ctime(time())) + ".\n");    

        write_file(STEEL_QUEST_LOG, l_file);

        break;                 
    }
    return "";

} /* done_answer */ 

/*
 * Function name: default_answer
 * Description  : reply to questions about a task
*/

public string
default_answer()
{
    switch (random(3))
    {
    case 0:
        command("sob");
        command("say In that matter I know nothing.");
        break;
    case 1:
        command("hmm");
        command("say Hmmm, interesting.. but I can't help you "
              + "with that matter.");
        break;
    case 2:
        command("shrug");
        command("say Yes? No? Maybe? How should I know?");
        break;
    }
    return "";
} /* default_answer */

/*
 * Function name: dragon_answer
 * Description  : reply to questions about a task
*/

public string
dragon_answer()
{
    switch (random(3))
    {
    case 0:
        command("say I've seen many dragons in my lifetime, many...");
        break;
    case 1:
        command("say This dragon is special.");
        break;
    case 2:
        command("say I saw it myself, it split a rock in half, with "
              + "his claws!");
        break;
    }
    return "";
} /* dragon_answer */       

/*
 * Function name: witch_answer
 * Description  : reply to questions about a task
*/

public string
witch_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Yes, the witch.. We should never have trusted "
              + "her.... never..");
        break;
    case 1:
        command("say Sabine broke our trust, she conducted "
              + "evil experiments behind our backs.");
        break;
    case 2:
        command("sob");
        command("say Don't trust her!");
        break;
    }
    return "";
} /* witch_answer */              

/*
 * Function name: door_answer
 * Description  : reply to questions about a task
*/

public string
door_answer()
{
    switch (random(3))
    {
    case 0:
        command("say There is a secret door down to the second level.");
        break;
    case 1:
        command("say It's protected by some strange magic.");
        break;
    case 2:
        command("say The magic in the door seems connected to the "
              + "inhabitants in the basement beneath the castle.");
        break;
    }
    return "";
} /* door_answer */                  

/*
 * Function name:        react_to_intro
 * Description  :        respond to introduction
 * Arguments    :        object tp -- the person who intro'd
 */
public void
react_to_intro(object tp)
{
    command("introduce myself to "+ tp->query_real_name());   
} /* react_to_intro */

/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
        set_alarm(1.5, 0.0, &react_to_intro(TP));
} /* add_introduced */
