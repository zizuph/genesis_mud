/* 
 * Taskmaster for the Academy of Elemental Arts
 * 
 * Amjal is the taskmaster of the Academy of Elemental Arts.
 * He will be the one to present the four tasks to the students
 * that will allow them to learn about how to be spellcasters
 * in the Realm.
 *
 * Created by Petros, December 2009
*/ 

#pragma save_binary

#include "../defs.h" 
#include <wa_types.h> 
#include <macros.h> 
#include <tasks.h> 
#include <options.h> 
#include <files.h> 
#include <cmdparse.h> 
#include <composite.h>

inherit "/d/Calia/gelan/monsters/stdaided";
inherit "/d/Calia/std/remember"; 
inherit "/d/Calia/std/npc_receive";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <formulas.h>
#include "/d/Genesis/gems/gem.h"

// Prototypes
public void                 report_task_1_progress(object player);
public void                 process_leftover_object(object obj, object player);
public void                 process_gem_object(object obj, object player);

public void 
create_monster() 
{
    if (!IS_CLONE) 
        return; 
        
    set_name("amjal"); 
    set_living_name("amjal");
    add_name("taskmaster"); 
    set_race_name("human"); 
    set_adj(({"stoic", "well-built"})); 
    set_title("the Taskmaster of the Gelan Academy of Elemental Arts"); 
    set_long("This is the Taskmaster of the Academy of Elemental Arts. He was "
        + "one of the few apprentices allowed to study under the "
        + "tutelage of the great Nimnal, his father. Having taken up the "
        + "efforts of his old master, he has decided to come here to the "
        + "Academy to work with others in harnessing knowledge of the study "
        + "of the elements.\n"
        + "If you are a student of the Academy and seek his guidance, you "
        + "should <ask amjal task>.\n"); 

   set_stats(({150, 153, 160, 145, 155, 140 })); 
   set_hp(query_max_hp());
   
   // Add Skills Here
   set_skill(SS_UNARM_COMBAT, 100); 
   set_skill(SS_WEP_CLUB, 100); 
   set_skill(SS_PARRY, 100); 
   set_skill(SS_DEFENCE, 100); 
   set_skill(SS_AWARENESS, 60); 
   set_skill(SS_BLIND_COMBAT, 100); 
   add_prop(NPC_I_NO_RUN_AWAY, 1); 
   add_prop(CONT_I_HEIGHT, 130); 
   add_prop(CONT_I_WEIGHT, 70000); 
   add_prop(NPC_I_NO_UNARMED, 1); // when wielding a weapon, don't use unarmed
   set_alignment(0); 
   set_gender(G_MALE); 
   
   set_default_answer("@@default_response", 1);
   add_ask( ({ "task", "help", "quest", "progress" }),
       "@@give_task");
   add_ask( ({ "nimnal" }),
      "say Ahh, my former master. He trained and helped the Lady Caliana "
    + "himself, you know. I still have his sword here in memory of his "
    + "sacrifice. If you want to learn more of this, visit the Calian "
    + "Chronicles in the Tower of the Realms.", 1);
   add_ask( ({ "gamalus" }),
      "say He is like a brother to me. We both were taught by Nimnal and are "
    + "what we are today because of Nimnal.\n", 1);
   add_ask( ({ "crystalline glass", "glass" }),
      "say Lady Caliana taught me the way of forming the rare crystalline. "
    + "Have you seen some of the docks? That's some of my work!", 1);
   add_ask( ({ "thera" }),
      "emote blushes briefly and tries to change the subject.", 1);
   add_ask( ({ "caliana", "lady caliana" }),
      "say Chosen she was. By whom or what we can only speculate, but one "
    + "thing is for certain. Her charge was to free our lands and restore "
    + "prosperity. This she did achieve. Where she is now, no one really "
    + "knows.\n", 1);
   add_ask( ({ "permission", "channeling", "class", "samoht" }),
      "say You wish to join Samoht's channeling class? You'll need my "
    + "permission first. Each time you complete a task for me, I'll grant "
    + "you permission to join his class.", 1);
   
   add_ask( ({ "components", "component" }),
      "say There are many different types of material components. Herbs, "
    + "leftovers, and gems are a few of the basic ones. Ask me about each "
    + "one.", 1);
   
   add_ask( ({ "herbs", "herb", "herb component" }),
      "say Herbs are the gift of Lady Gu, the Elemental of Earth. They are "
    + "extremely useful for the effects they can have upon your body. Around "
    + "here, you can usually find them in the Calian moors. Feel free to "
    + "ask about other components as well.", 1);
   
   add_ask( ({ "calian moors", "moors" }),
     "say The Calian moors are south of Gelan along the mountain roads.", 1);
   
   add_ask( ({ "gems", "gem", "gem component" }),
     "say Gems intrinsically hold properties that are useful for spells. They "
   + "can be obtained either by monsters dropping them or purchasing them "
   + "directly from gem stores throughout the realms.", 1);
   
   add_ask( ({ "gem stores" }),
     "say Gem stores exist in various lands in the Realm. There is one "
   + "particularly famous lapidary in the Bazaar in Avenir. Also, there's "
   + "another one in Gondor.", 1);
   
   add_ask( ({ "leftover", "leftovers" }),
     "say One can find leftovers by cutting them from corpses. Leftovers "
   + "provide the life energy that are needed in spells. Remember to bring "
   + "a knife with you on your travels!", 1);
   
   add_ask( ({ "knife" }),
     "say You can obtain a knife from donation boxes around the realms, or "
   + "you can even procure one from Bubba Hammerhead here in Gelan.", 1);
   
   add_prop(LIVE_M_NO_ACCEPT_GIVE, "@@can_accept_item");
}

public int
second_life(object killer)
{
    object ghost; 

    ::second_life(killer); 
    log_file("academic", ctime(time()) + ": Amjal killed by " + 
                      killer->query_real_name() + ".\n"); 
    seteuid(getuid()); 
    ghost = clone_object("/d/Calia/gelan/objects/ghost"); 
    ghost->set_ghost_des("stoic well-built male human"); 
    ghost->set_duration(900); 
    ghost->move(killer); 
    ghost->start_haunt(); 

    return 0; 
}

public string
default_response()
{
    object player = this_player();
    
    if (!ACADEMIC_MANAGER->completed_task_1(player)
        || ACADEMIC_MANAGER->completed_task_2(player)
        || ACADEMIC_MANAGER->completed_task_3(player)
        || ACADEMIC_MANAGER->completed_task_4(player))
    {
        return "say I don't know about that, but you can always ask me for "
            + "your next task if you wish to continue your training.";
    }
    
    return "say I don't know about that. I have other students I need to "
        + "attend to. Perhaps you should go practice or go study some "
        + "more?";
}

public string
give_task()
{
    object player = this_player();
    
    if (!IS_MEMBER(player))
    {
        return default_response();
    }
    
    if (!ACADEMIC_MANAGER->query_completed_task_1(player))
    {
        if (!player->query_prop(TASK_ONE_GIVEN))
        {
            command("say Aha. Ready for your first task are you? Well alright.");
            command("say A major part of working with the arcane is the gathering of "
                + "necessary components for your travels.");
            command("say Your first task will be to go out and return with ten "
                + "leftovers and five gems for me.");
            command("say You get leftovers from corpses normally. So slay something, "
                + "and cut the leftover from the corpse with a knife that you wield.");
            command("say Gems can be found throughout the Donut. There is a "
                + "lapidarium in the Elementalist Temple. Seek out the path there "
                + "along the beach south of the piers.");
            command("say Return here with all I asked for and I will grant "
                + "you access to your first channeling session with the Teacher "
                + "Samoht!");
            player->add_prop(TASK_ONE_GIVEN, 1);
        }
        else
        {
            command("say Your task remains the same.");
            report_task_1_progress(player);
            command("say Go on, get moving now.");
        }
        return "";
    }
    else if (!ACADEMIC_MANAGER->query_completed_task_2(player))
    {
        if (!ACADEMIC_MANAGER->acquired_fire_spell(player))
        {
            command("say Go take a channeling class with Samoht first!");
            command("say You are not yet ready for your next task.");
        }
        else if (!player->query_prop(TASK_TWO_GIVEN))
        {
            command("say The second task is a bit more demanding than the first.");
            command("say Go to Lobar, the Herbmaster of Calia. He lives nearby, "
                + "in the fishing village.");
            command ("say Ask him my name and he will tell you what to do.");
            player->add_prop(TASK_TWO_GIVEN, 1);
        }
        else
        {
            command("say Have you forgotten your task so quickly? You must "
                + "pay more attention if you wish to succeed in the Academy!");
            command("say Go to Lobar in the fishing village. Ask him my name "
                + "and do what he tells you to do.");
            command("say Go now! Hurry!");
        }
    }
    else if (!ACADEMIC_MANAGER->query_completed_task_3(player))
    {
        if (!ACADEMIC_MANAGER->acquired_water_spell(player))
        {
            command("say Go take a channeling class with Samoht first!");
            command("say You are not yet ready for your next task.");
        }
        else if (!player->query_prop(TASK_THREE_GIVEN))
        {
            command("say Your third task will teach you a bit of the art of "
                + "making potions.");
            command("say Go to Raspatoon Goldiloon here in Gelan. He is "
                + "ancient, wise and .. well.. nevermind.");
            command("say Ask him my name and he might be able to help you.");
            player->add_prop(TASK_THREE_GIVEN, 1);
        }
        else
        {
            command("say Did you pay attention to anything I told you?");
            command("say You're at the mercy of Raspatoon Goldiloon now.");
            command("chuckle");
            command("say Good luck!");
        }        
    }
    else if (!ACADEMIC_MANAGER->query_completed_task_4(player))
    {
        if (!ACADEMIC_MANAGER->acquired_elemental_spell(player))
        {
            command("say Go take a channeling class with Samoht first!");
            command("say You are not yet ready for your next task.");
        }
        else if (!player->query_prop(TASK_FOUR_GIVEN))
        {
            command("say Ready for you final test? Good!");
            command("say This next task will be a lesson on magic resistance.");
            command("say Magic resistance comes in many forms. Some creatures "
                + "have it as an innate ability, some get it from wearing "
                + "artifacts and items.");
            command("say There are even those capable of creating it through "
                + "arcane or divine spells.");
            command("say Go to Bubba Hammerhead, the smith here in Gelan, ask "
                + "him my name and he'll tell you what to do.");
            player->add_prop(TASK_FOUR_GIVEN, 1);
        }
        else
        {
            command("say I hope that you'll eventually learn to listen closely.");
            command("say Like I told you before, you need to go see Bubba "
                + "Hammerhead and ask him my name.");
            command("say He'll tell you what to do. Come back quickly. "
                + "I don't have all day, you know.");
        }        
    }
    else
    {        
        command("say You've already completed all the tasks that I have "
            + "to give you. Go out and practice what you have learned!");
    }
    return "";
}

public void
enchant_contraption(object player, object contraption)
{
    command("say Ah, yes. This is the training device from Bubba Hammerhead.");
    command("say Good good! One moment...");
    command("emote closes his eyes and concentrates.");
    command("emote mutters a few words under his breath, while slowly "
        + "weaving his hands above the contraption. You notice each "
        + "of three plates glow in response.");
    command("emote opens his eyes and carefully inspects the contraption.");
    command("say Now, I want you to go down into the practice yard, and hang "
        + "this on a rack. Afterwards, <cast hydrokine on rack>. Then "
        + "return to me for your final lesson.");
    player->catch_msg(QCTNAME(this_object()) + " gives you the contraption "
        + "back.\n");
    contraption->set_state(2);
    contraption->move(player, 1);
}

public void
finalize_task_4(object player, object contraption)
{
    command("emote inspects the contraption closely and discards it.");
    command("say Yes. I placed a spell of protection on the plates, varying "
        + "in strength from plate one to three.");
    command("say As you can tell, magic resistance of any kind has a major "
        + "impact on your spells.");
    command("say If you plan to take your skills into battle, know your enemy!");
    command("say For as the experiment here has shown you, whatever defences they "
        + "may have is vital to your success or your demise.");
    command("say Let that be my final task to you. Have the next channeling "
        + "session with Samoht.");
    command("say Go forth and complete your studies. Best of luck to you!");
    ACADEMIC_MANAGER->set_completed_task_4(player);
    contraption->remove_object();
}

// Handle the Accepting and Returning of Task Items

public string
can_accept_item()
{
    object player = this_player();
    
    if (!IS_MEMBER(player))
    {
        return mobile_deny_objects();
    }
    
    // Amjal only accepts items when players are performing tasks for him.
    if ((!ACADEMIC_MANAGER->query_completed_task_1(player)
         && player->query_prop(TASK_ONE_GIVEN))
        || 
        (!ACADEMIC_MANAGER->query_completed_task_2(player)
         && player->query_prop(TASK_TWO_GIVEN))
        ||
        (!ACADEMIC_MANAGER->query_completed_task_3(player)
         && player->query_prop(TASK_THREE_GIVEN))
        ||
        (!ACADEMIC_MANAGER->query_completed_task_4(player)
         && player->query_prop(TASK_FOUR_GIVEN)))
    {
        // Returning 0 means that we allow it.
        return 0;
    }
    
    return mobile_deny_objects();
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    receive_enter_inv(ob, from);
}

/*
 * Function:    should_accept_item
 * Description: Returns whether the item should be accepted at this time
 * Returns:     ({ wanted_items, unwanted_items })
 */
public int
should_accept_item(object obj, object from)
{
    object player = from;
    
    if (!ACADEMIC_MANAGER->query_completed_task_1(player)
        && player->query_prop(TASK_ONE_GIVEN))
    {
        // We accept leftovers and gems for the first task
        if (IS_LEFTOVER_OBJECT(obj) 
            && ACADEMIC_MANAGER->query_leftovers_collected(player) < 10)
        {
            return 1;
        }
        else if (IS_GEM_OBJECT(obj)
                 && ACADEMIC_MANAGER->query_gems_collected(player) < 5)
        {
            return 1;
        }
    }
    else if (!ACADEMIC_MANAGER->query_completed_task_2(player)
             && player->query_prop(TASK_TWO_GIVEN))
    {
        if (obj->id("academic_lobar_approval_note"))
        {
            return 1;
        }
    }
    else if (!ACADEMIC_MANAGER->query_completed_task_3(player)
             && player->query_prop(TASK_THREE_GIVEN))
    {
        if (obj->id("academic_raspatoon_potion"))
        {
            return 1;
        }
    }
    else if (!ACADEMIC_MANAGER->query_completed_task_4(player)
             && player->query_prop(TASK_FOUR_GIVEN))
    {
        if (obj->id("academic_resistance_contraption"))
        {
            return 1;
        }
    }    
    return 0;
}

public void
hook_process_accept_items(mapping items)
{
    foreach (object from, mapping objs : items)
    {
        foreach (object obj : m_indexes(objs))
        {
            if (!objectp(obj)) continue;
            if (IS_LEFTOVER_OBJECT(obj))
            {
                process_leftover_object(obj, from);
            }
            else if (IS_GEM_OBJECT(obj))
            {
                process_gem_object(obj, from);
            }
            else if (obj->id("academic_lobar_approval_note")
                     && !ACADEMIC_MANAGER->query_completed_task_2(from))
            {
                if (obj->query_owner_name() != from->query_real_name())
                {
                    command("say Hey, this approval note isn't yours! Come "
                        + "back with an approval note of your own.");
                }
                else
                {
                    ACADEMIC_MANAGER->set_completed_task_2(from);
                    command("say Well done! I hope you paid attention to Lobar's "
                        + "instructions. Now, you may attend another session of "
                        + "channeling with Samoht!");
                }
                obj->remove_object();
            }
            else if (obj->id("academic_raspatoon_potion")
                     && !ACADEMIC_MANAGER->query_completed_task_3(from))
            {
                if (obj->query_owner_name() != from->query_real_name())
                {
                    command("say Brought me some good stuff from Raspatoon?");
                    command("say Doesn't look like this is something he "
                        + "gave you. Well, I'll have it anyway.");
                    command("emote quaffs the potion.");
                }
                else
                {
                    command("emote quickly downs the potion in a swift gulp.");
                    command("grin");
                    command("say Ahh the Crazy-Krougian... no one quite mixes "
                        + "them like old Raspatoon.");
                    command("hiccup"); 
                    ACADEMIC_MANAGER->set_completed_task_3(from);
                    command("say Oh yeah, you can join another channeling "
                        + "session with Samoht now.");
                }
                obj->remove_object();
            }
            else if (obj->id("academic_resistance_contraption")
                     && !ACADEMIC_MANAGER->query_completed_task_4(from))
            {
                if (obj->query_owner_name() != from->query_real_name())
                {
                    command("say Hmm.. this isn't the contraption that you "
                        + "were given, was it? I'll take this off your hands.");
                    command("emote puts the contraption away.");
                    obj->remove_object();
                }
                else
                {
                    switch (obj->query_state())
                    {
                    case 1:
                        // We should enchant this and give them the
                        // enchanted piece
                        enchant_contraption(from, obj);
                        break;
                    
                    case 2:
                        command("say You should go to the practice yard "
                            + "with this first. Don't just hand it back "
                            + "to me!");
                        obj->move(from, 1);
                        from->catch_msg(QCTNAME(this_object()) + " hands "
                            + "the contraption back to you.\n");
                        break;
                    
                    case 3:
                        finalize_task_4(from, obj);
                        break;
                    }
                }
            }            
        }
        if (!ACADEMIC_MANAGER->query_completed_task_1(from)
            && from->query_prop(TASK_ONE_GIVEN))
        {
            report_task_1_progress(from);
        }
    }
}

public void
hook_process_unaccept_items(mapping items)
{
    foreach (object from, mapping objs : items)
    {
        foreach (object obj : m_indexes(objs))
        {
            obj->move(environment(this_object()), 1);            
        }
        command("say What is this? I don't want this!");
        command("emote drops " + COMPOSITE_DEAD(m_indexes(objs)));
    }
}

public void
report_task_1_progress(object player)
{
    int leftovers_needed, gems_needed;

    leftovers_needed = max(0, 10 - ACADEMIC_MANAGER->query_leftovers_collected(player));
    gems_needed = max(0, 5 - ACADEMIC_MANAGER->query_gems_collected(player));
    
    if (leftovers_needed == 0 && gems_needed == 0)
    {
        command("say Congratulations! You have now collected everything you "
            + "need for this task. You have now earned yourself permission "
            + "to channel with Samoht!");
        ACADEMIC_MANAGER->set_completed_task_1(player);
    }
    else
    {
        command("say You need " + (leftovers_needed ? sprintf("%d", leftovers_needed) : "no")
            + " more leftovers and " + (gems_needed ? sprintf("%d", gems_needed) : "no")
            + " more gems to complete your task.");
    }
}

public void
process_leftover_object(object obj, object player)
{
    int amount, amount_needed;
    object wanted, unwanted;
    
    // We want 10 leftovers
    amount = obj->num_heap();
    amount_needed = 10 - ACADEMIC_MANAGER->query_leftovers_collected(player); 
    if (amount > amount_needed)
    {           
        obj->split_heap(amount - amount_needed);
        wanted = obj->make_leftover_heap();
        unwanted = obj;
    }
    else
    {
        wanted = obj;
        unwanted = 0;
    }
    
    if (objectp(unwanted))
    {
        unwanted->move(environment(this_object()), 1);
        command("say I don't need this many leftovers.");
        command("emote drops " + COMPOSITE_DEAD(unwanted) + ".");
    }
        
    ACADEMIC_MANAGER->set_leftovers_collected(player,
        ACADEMIC_MANAGER->query_leftovers_collected(player) + wanted->num_heap());
    wanted->remove_object();
}

public void
process_gem_object(object obj, object player)
{
    int amount, amount_needed;
    object wanted, unwanted;
    
    // We want 5 gems
    amount = obj->num_heap();
    amount_needed = 5 - ACADEMIC_MANAGER->query_gems_collected(player); 
    if (amount > amount_needed)
    {           
        obj->split_heap(amount - amount_needed);
        wanted = obj->make_leftover_heap();
        unwanted = obj;
    }
    else
    {
        wanted = obj;
        unwanted = 0;
    }
    
    if (objectp(unwanted))
    {
        unwanted->move(environment(this_object()), 1);
        command("say I don't need this many gems.");
        command("emote drops " + COMPOSITE_DEAD(unwanted) + ".");
    }
        
    ACADEMIC_MANAGER->set_gems_collected(player,
        ACADEMIC_MANAGER->query_gems_collected(player) + wanted->num_heap());
    wanted->remove_object();
}
