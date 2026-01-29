/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/rohan/edoras/npc/team.c";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

public int     wake_him(string str);
public void    go_sleep();
public void    tell_uruk2(object tp);
public void    tell_uruk3(object tp);
public void    disappear();

static int     gSnore,
               gSleep,
               gInform,
               gDisappear;

public void
create_monster() 
{
    int    r = random(11);
    set_living_name("harding");
    set_name(({"harding","man","soldier"}));
    add_name("rohirrim");
    set_race_name("human");
    set_title("the Rider of Rohan");
    set_adj(({"tall","golden-haired"}));
    set_long("@@long_desc@@");
    default_config_npc(65);
    set_base_stat(SS_CON, 75 + r);
    set_base_stat(SS_STR, 75);
    set_base_stat(SS_DIS, 75);
    set_skill(SS_WEP_SWORD, 80 + r);
    set_skill(SS_DEFENCE,   90 - r);
    set_skill(SS_PARRY,     80 + r);
    set_alignment(200 + r * 20);
    set_default_answer(VBFC_ME("def_answer"));
    add_ask("name", VBFC_ME("introduce"));
    add_ask(({"task","quest","job","tasks","quests","jobs"}),
        VBFC_ME("tell_task"));
    add_ask(({"about task","about quest","about job","about tasks",
        "about quests","about jobs"}), VBFC_ME("tell_task"));
    add_ask(({"uruk","uruks","uruk-hai"}),
        VBFC_ME("tell_uruk"));
    add_ask(({"about uruk","about uruks","about uruk-hai"}),
        VBFC_ME("tell_uruk"));

    gSnore = set_alarm(10.0 + rnd() * 10.0, 10.0, &command("snore"));
}

public void
arm_me()
{
    FIX_EUID

    if (!present("sword", TO))
        clone_object(EDORAS_DIR + "obj/guardsword")->move(TO);

    if (!present("corslet", TO))
        clone_object(EDORAS_DIR + "obj/corslet")->move(TO);

    if (!present("shield", TO))
        clone_object(EDORAS_DIR + "obj/roshield")->move(TO);
}

public void
get_armed()
{
    command("wear all");
    command("wield sword");
}

public string
introduce()
{
    if (gSnore && sizeof(get_alarm(gSnore)))
        return "";

    command("say My name is Harding, I serve in the Second Eored.");
    command("introduce me");
    return "";
}

public string
long_desc()
{
    string desc = "This is a tall and fair-haired Rohirrim soldier. "
      + "His golden hair is braided on his shoulders.";

    if (gSnore && sizeof(get_alarm(gSnore)))
        desc += " He is sleeping on one of the beds.";
    else
        desc += " He looks very exhausted and tired. Probably he did "
          + "not sleep for more than a day, so he is not pleased that "
          + "someone raised him from his well earned sleep.";

    return BSN(desc);
}

public void
init_living()
{
    ::init_living();
    add_action(wake_him, "wake");
}

public int
wake_him(string str)
{
    object *obj;

    NFN("Wake whom?");

    if (!strlen(str))
       return 0;

    str = LOW(str);

    if (!sizeof(obj = FIND_STR_IN_OBJECT(str, ENV(TO))))
        return 0;

    if (member_array(TO, obj) < 0)
        return 0;

    if (!gSnore || !sizeof(get_alarm(gSnore)))
    {
        NFN("But he isn't asleep! Why would you want to wake him?");
        return 0;
    }
    if (TP->query_prop("_elfhelm_uruk_quest"))
    {
        remove_alarm(gSnore);
        gSnore = 0;
        command("emote rises from the bed.");
        set_alarm( 2.0, 0.0, get_armed);
        set_alarm( 5.0, 0.0, &command("present me"));
        command("say What do you want from me, " + TP->query_race_name() + "?");
        gSleep = set_alarm(60.0, 0.0, go_sleep);
    }
    else
    {
        command("emote growls in his sleep.");
        command("emote looks around sleepily.");
        command("say Let me sleep and be damned!");
        command("emote turns around and falls asleep again.");
    }
    return 1;
}

public string
tell_task()
{
    if (gSnore && sizeof(get_alarm(gSnore)))
        return "";
    command("say I do not know what you want from me.");
    command("say I am only a simple soldier, I do not assign tasks.");
    command("say If you are looking for a task, then go to Elfhelm the Marshal.");
    return "";
}

public string
tell_uruk()
{
    if (gSnore && sizeof(get_alarm(gSnore)) || objectp(query_attack()))
        return "";

    command("sigh");
    if (TP->query_prop("_elfhelm_uruk_quest"))
    {
        command("yawn");
        command("say Yeah, we saw an orc pack on the plain last night!");
        command("say And it was not scattered orcs as some like to believe!");
        command("say With my very own eyes, I could make out an uruk!");
        command("say A real uruk, tall and black, and he was their leader.");
        command("say But we have orders not to attack the orcs on the plains!");
        command("emote curses silently.");
        gInform = set_alarm(10.0, 0.0, &tell_uruk2(TP));
    }
    else
        command("say Uruk-hai? What do you care? It's none of your business!");
    return "";
}

public void
tell_uruk2(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)) || objectp(query_attack()))
        return;
    command("say And what troubles me most, is that they had crossed the "
      + "Deeping Stream already.");
    command("say We met them in the southern parts of the West Emnet.");
    command("say Until now, they always stayed close to Fangorn, when they "
      + "travelled to or from Isengard.");
    command("say I am extremely worried, but almost no one believes us!");
    command("say Even Elfhelm has his doubts!");
    gInform = set_alarm(15.0, 0.0, &tell_uruk3(tp));
}

public void
tell_uruk3(object tp)
{
    gInform = 0;

    if (!objectp(tp) || !present(tp, ENV(TO)) || objectp(query_attack()))
        return;

    command("say If you want to convince him, you would have to bring "
      + "parts from the corpse of an uruk!");
    command("say But it's not so easy to cut parts from an uruk, unless he's dead.");
    command("smirk");
    command("say Well, I wish you luck!");
    command("wave " + tp->query_name());
    remove_alarm(gSleep);
    gSleep = set_alarm( 6.0, 0.0, go_sleep);
}

public void
go_sleep()
{
    if (gSnore && sizeof(get_alarm(gSnore)))
       return;

    if (objectp(query_attack()) || (gInform && sizeof(get_alarm(gInform))))
    {
        gSleep = set_alarm(60.0, 0.0, go_sleep);
        return;
    }
    command("say I am very tired, I haven't slept for two days!");
    command("say I will go back to sleep now! ");
    command("yawn");
    command("unwield all");
    command("remove all");
    command("emote lies down on one of the beds.");
    command("emote falls to sleep immediately.");

    gSnore = set_alarm(10.0, 15.0, &command("snore"));
    if (gDisappear && sizeof(get_alarm(gDisappear)))
        remove_alarm(gDisappear);
    gDisappear = set_alarm(180.0, 0.0, disappear);
}

public void
disappear()
{
    if (!gSnore || !sizeof(get_alarm(gSnore)))
        return;
    command("yawn");
    command("emote rises from the bed.");
    command("emote stretches himself.");

    remove_alarm(gSnore);
    gSnore = 0;

    get_armed();
    move_living("west", EDORAS_DIR + "rooms/funohedhome");
    remove_object();
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    ob->remove_prop("_elfhelm_uruk_quest");

    if (gSnore && sizeof(get_alarm(gSnore)))
    {
        command("emote jumps up from the bed.");
        remove_alarm(gSnore);
        gSnore = 0;
        get_armed(); 
    }
    command("shout Alarm! I have been attacked!");
    command("shout You will not live to regret this, foul " + TP->query_race_name() + "!");
    command("scream");
    if (gSleep && sizeof(get_alarm(gSleep)))
        remove_alarm(gSleep);
    gSleep = set_alarm(300.0, 0.0, go_sleep);
}

public string
def_answer()
{
    if (gSnore && sizeof(get_alarm(gSnore)))
        return("He cannot hear you since he is asleep.\n");

    return("He does not seem to understand what you want from him.\n");
}

/* Solamnian prestige */
public int     query_knight_prestige() {return (-7);}
