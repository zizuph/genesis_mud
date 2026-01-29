/* Jasmine, Rock Collector of Kendermore, Gwyneth, June 10, 1999 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

#define PLAYER_I_FOUND_STRING "_player_i_found_string"
#define PLAYER_I_GOT_STONE "_player_i_got_stone"

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("jasmine");
    set_living_name("jasmine");
    set_race_name("kender");
    set_title("Stonethrower, the Rock Collector of Kendermore");
    set_adj("red-cheeked");
    add_adj("tanned");
    set_gender(G_FEMALE);
    set_introduce(1);

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_2H_COMBAT, 50);

    set_alignment(350);
    set_knight_prestige(-40);

    set_random_move(20);
    set_restrain_path(KROOM);

    set_act_time(5);
    add_act("smile impishly");
    add_act("emote chatters merrily about all her adventures.");
    add_act("emote chatters: I just love rocks! They're so very " + 
        "interesting!");
    add_act("emote chatters: I love those birds! They sit on my shoulder " + 
        "and sing sometimes.\n"); 

    set_default_answer("She is looking at something in her pouch with " +
        "great interest, and doesn't hear your question.\n"); 
    add_ask(({"stone", "magic stone", "help", "quest", "job", "task"}), 
        VBFC_ME("string_hint"));
    add_ask(({"string", "rainbow string"}), "emote chatters: I lost it " + 
        "somewhere!", 1);
    add_ask(({"rocks", "rock"}), "emote chatters: I collect them!",1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : String hint
 * Description : Gives quest hints to questers.
 * Returns : Null
*/

string
string_hint()
{
    if(TP->test_bit("ansalon",0,2))
    {
        command("emote chatters: I don't need anymore help, thanks!");
        return "";
    }
    set_alarm(1.0,0.0, &command("emote chatters: You must have been sent " + 
        "here by Flop! He's been after my iolite stone for ages."));
    set_alarm(3.0,0.0, &command("chuckle softly"));
    set_alarm(5.0,0.0, &command("emote chatters: He thinks it's magic, but " + 
        "it's not really."));
    set_alarm(7.0,0.0, &command("ponder"));
    set_alarm(9.0,0.0, &command("emote chatters: I suppose I could let him " + 
        "have it, but I need a favour first."));
    set_alarm(11.0,0.0, &command("emote chatters: I've been looking for my " + 
        "favourite piece of string. It's rainbow coloured. Have you seen it?"));
    set_alarm(13.0,0.0, &command("smile hopefully"));
    set_alarm(15.0,0.0, &command("emote chatters: Bring it back to me, and " + 
        "I'll give you that 'magic' stone."));
    set_alarm(17.0,0.0, &command("laugh"));
    return "";
}

/* Function name : Give string
 * Description : Trades a stone for a piece of string to questers who 
 *     deserve it.
 * Returns : Null
*/

void
give_string(object from)
{
    object stone;
    string who,
    what;

    who = from->query_real_name();

    if(TP->query_prop(PLAYER_I_FOUND_STRING))
    {
        command("gasp");
        command("emote chatters: I didn't think you could find it!");
        command("thank " + who);
        command("emote chatters: Here's the stone I promised. I hope Flop " + 
            "will quit bothering me now!");
        command("emote pulls a violet-blue stone from one of many pockets.");
        stone = clone_object(KOBJ + "iolite");
        what = stone->query_short();
        stone->move(TO);
        command("give " + what + " to " + who);
        command("drop " + what);
        command("emote wanders off.");
        TP->add_prop(PLAYER_I_GOT_STONE, 1);
        remove_object();
    }
    else
    {
        command("emote chatters: I didn't think you could find it!");
        command("thank " + who);
        command("emote suddenly looks bored and wanders away without " + 
            "giving you the stone!");
        remove_object();
    }
}

/* Function name : Give it back
 * Description : Let's questers know they got the wrong item.
 * Returns : Null
*/

void
give_it_back(object ob, object from)
{
    command("emote chatters: That's not what I asked for!");
    set_alarm(1.0,0.0,"command","say But it is interesting, thanks!");
}

/* Function name : Enter inventory
 * Description : Checks items entering the kender's inventory for a quest
 *     item.
 * Returns : Null
*/

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_ansalon_r_string_"))
    {
        set_alarm(1.0, 0.0, &give_string(from));
        return;
    }

    if(ob->id("clothes"))
        return;
    if(ob->id("knife"))
        return;
    if(ob->id("dagger"))
        return;
    if(ob->id("hoopak"))
        return;
    if(ob->query_no_show())
        return;

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(KOBJ + "std_knife")->move(TO);
    clone_object(KOBJ + "hoopak")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(KOBJ + "blouse")->move(TO);

    command("wear all");
    command("wield all");
}

