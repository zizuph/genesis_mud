/* 
 * Headmistress for the Academy of Elemental Arts
 * 
 * Xania, a female elf, is the headmistress of the Academy of Elemental Arts.
 * Officially she's known as the headmistress, and allows people to
 * enroll or leave the school. She provides some basic instructions,
 * but will mostly direct students to the Taskmaster and the Teacher.
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

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <formulas.h>

// Defines
#define DONATION_BOX (ACADEMIC_OBJS + "drop_box")

public void 
create_monster() 
{
    if (!IS_CLONE) 
        return; 
        
    set_name("xania"); 
    set_living_name("xania");
    add_name("headmistress"); 
    set_race_name("elf"); 
    set_adj(({"slender", "graceful"})); 
    set_title("the Headmistress of the Gelan Academy of Elemental Arts"); 
    set_long("This is Xania, the Headmistress of the Gelan Academy of Elemental "
        + "Arts.\n"); 
    set_stats(({170, 195, 165, 190, 190, 175 })); 
    set_hp(query_max_hp());
    
    // Add Skills Here
    set_skill(SS_UNARM_COMBAT, 100); 
    set_skill(SS_WEP_CLUB, 100); 
    set_skill(SS_PARRY, 100); 
    set_skill(SS_DEFENCE, 100); 
    set_skill(SS_AWARENESS, 60); 
    set_skill(SS_BLIND_COMBAT, 100); 
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_DEATH, 30);

    add_prop(NPC_I_NO_RUN_AWAY, 1); 
    add_prop(CONT_I_HEIGHT, 130); 
    add_prop(CONT_I_WEIGHT, 70000); 
    add_prop(NPC_I_NO_UNARMED, 1); // when wielding a weapon, don't use unarmed
    set_alignment(0); 
    set_gender(G_FEMALE); 
    set_size_descs("tall", "lean");
    
    add_ask( ({ "members", "member", "awake", "academics" }),
        "@@reply_academics" );   
    add_ask( ({ "donation", "donations" }),
        "@@reply_donations" );         
    add_ask( ({ "components", "spell components", "specific components", "supplies",
                "component", "spell component" }),
        "@@reply_components" );         
    add_ask( ({ "guild", "academy", "academy of elemental arts", "joining" }),
        "@@reply_guild");
    add_ask( ({ "help", "task" }),
        "say I don't really need any help. But if you're a member of the "
      + "Academy, I'm sure that the Taskmaster Amjal would love to talk "
      + "to you.", 1);
    add_ask( ({ "rules" }),
        "say You can read about them in <help academic rules>.");
    
    set_act_time(5);
    add_act("ponder how to help Academics afford expensive spell components.");
    add_act("emote tends to the donation box.");
    add_act("emote looks over the Academic rosters and plans for future "
        + "enrollments.");
    
    set_default_answer("say I really don't know about that. If you ask me "
      + "about the guild, I may be able to tell you more.\n", 1);
}

public int
second_life(object killer)
{
    object ghost; 

    ::second_life(killer); 
    log_file("academic", ctime(time()) + ": Xania killed by " + 
                      killer->query_real_name() + ".\n"); 
    seteuid(getuid()); 
    ghost = clone_object("/d/Calia/gelan/objects/ghost"); 
    ghost->set_ghost_des("slender graceful female elf"); 
    ghost->set_duration(900); 
    ghost->move(killer); 
    ghost->start_haunt(); 

    return 0; 
}

public string
reply_guild()
{
    command("say The Academy of Elemental Arts is a school built upon "
        + "the belief that it is possible to teach the arcane arts "
        + "to young impressionable minds.");
    command("say We seek to educate those who desire to pursue a life "
        + "of study and practice, honing their mental skills rather "
        + "than their physical ones.");
    command("say If you're interested in enrolling, please read the "
        + "scrolls we have in <help academic joining> and <help "
        + "academic rules>.");
        
    return 0;
}

public string
reply_academics()
{
    setuid();
    seteuid(getuid());

    if (IS_MEMBER(this_player()))
    {
        command("chuckle");
        command("say You don't need to ask me about that! You can see for "
            + "yourself which of your classmates are awake.");
        return 0;
    }

    mixed awake_members;
    int donation_points = DONATION_BOX->get_donation_points_for_player(this_player());
    switch (donation_points)
    {
    case 0:
        command("say Have you thought about donating spell components to the "
            + "Academy?");
        command("say If you were to donate enough, I might be inclined "
            + "to share about the current Academics who are awake.");
        command("wink");
        break;
    
    case 1..1500:
        command("say Thank you so much for donating spell components to "
            + "our students! The students certainly appreciate it.");
        command("say At this point, however, we are still a bit lacking "
            + "in supplies. If you continue to donate in such a fashion, "
            + "I will share with you about the current Academics who "
            + "are awake.");
        break;

    default:
        command("say Thank you for having been so generous to donate so many "
            + "spell components! The students are indebted to you.");
        awake_members = ACADEMIC_MANAGER->query_awake_members();
        if (!sizeof(awake_members))
        {
            command("whisper " + OB_NAME(this_player()) + " There are no "
                + "members of the Academy in the realms.");
            break;
        }
        awake_members = sort_array(map(awake_members, &capitalize() @ &->query_real_name())); 
        command("whisper " + OB_NAME(this_player()) + " " + COMPOSITE_WORDS(awake_members) + 
                ((sizeof(awake_members) > 1) ? " are " : " is ") + "in the realms.");       
    }

    return 0;
}

public string
reply_donations()
{
    if (IS_MEMBER(this_player()))
    {
        command("say Donations by others will be placed in this box. You "
            + "can check this box occasionally to find items of use.");
        return 0;
    }

    command("say The Academy of Elemental Arts is always grateful for "
        + "donations by supporters of the Academy.");
    command("say Not all the students here can afford the spell components "
        + "often necessary to fund their training.");
    command("say Donations of their specific components are especially "
        + "useful!");
    return 0;
}

public string
reply_components()
{
    if (IS_MEMBER(this_player()))
    {
        command("say Spell components are all described in the scrolls that "
            + "you receive upon learning a new spell. Be sure to read them!");
        return 0;
    }

    command("say I can't reveal the spell components that are used by "
        + "the students here.");
    command("say Perhaps you should speak with one of them and ask "
        + "them?");
    return 0;
}
