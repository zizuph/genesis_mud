/*
 *    The standard npc ranger for the ranger guild
 *
 *    Created by copying functions from files by Elessar
 *    - Olorin, 20-Jan-1995
 *
 * Modification log:
 * 24-Feb-2002, Alto: Moved, modified to fit new rangers structure.
 * 27-Oct-2003, Tigerlily: added set_size_descs
 * 24-Jan-2004, Tigerlily: updated introduce to 
 *                         inherit "/d/Genesis/lib/intro"
 *
 */
inherit "/std/monster.c";
inherit "/d/Genesis/lib/intro.c";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <state_desc.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

#define COMPANY ({ "the Westlands", "Ithilien", "the North" })
#define NUMBER_OF_COMPANIES 2
#define CNO_WESTLANDS       0
#define CNO_ITHILIEN        1
#define CNO_NORTH           2

int        company_no;
static int incognito;
int        agg_ranger, hf_aid;

/* prototypes */
public void           create_ranger();
public int            set_company_no(int no);
public void           get_company_token();
public void           arm_me();
public void           introduce(object who);
varargs void          remove_badge(object badge, object player);
public void           destroy_eyes();
public string         give_name();


/*
 *  Functions from the ranger shadow
 */
string
query_guild_name_occ()
{
    return RANGERS_GUILD_NAME;
}

public void
create_ranger()
{
}

/* Kept for backwards compatibility */
int
set_company(string str)
{
    str = lower_case(str);

    switch(str)
    {
    case "ithilien":
        set_company_no(1);
        break;
    case "north":
        set_company_no(2);
        break;
    default:
        set_company_no(0);
        break;
    }

    get_company_token();
    return 1;
}


public int
set_company_no(int no)
{
    if ((no < sizeof(COMPANY)) && (no >= 0))
    {
        company_no = no;
        return 1;
    }
    return 0;
}

public int 
query_company_no()
{
    return company_no;
}

public void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP_DIR + "dlsword")->move(TO);
    clone_object(ARM_DIR + "drcloak")->move(TO);
    clone_object(ARM_DIR + "dlboots")->move(TO);

    command("wield all");
    command("wear all");

    get_company_token();
}

/* 
 * Function name: get_company_token
 * Description  : This function is kept for backwards compatability 
 */
public void
get_company_token()
{
    if (query_company_no() == CNO_NORTH)
        clone_object(RANGERS_NOR_EMBLEM)->move(TO, 1);
    else if (query_company_no() == CNO_ITHILIEN)
        clone_object(RANGERS_ITH_EMBLEM)->move(TO, 1);
    else if (query_company_no() == CNO_WESTLANDS)
        clone_object(RANGERS_APP_EMBLEM)->move(TO, 1);

    set_alarm(2.0, 0.0, &command("wear all"));
}

string 
give_name()
{
    command("stare");
    return "";
}

void
initiate_ranger_soul()
{
    TO->add_cmdsoul(RANGERS_SOUL);
    TO->update_hooks();
}

public nomask void
create_monster()
{
    int avg_stat;

    set_name("ranger", "dunadan");
    set_race_name("human");
    if (random(2))
    {
        set_gender(G_MALE);
        add_name("man");
    }
    else
    {
        set_gender(G_FEMALE);
        add_name("woman");
    }

    set_base_stat(SS_OCCUP, 150);
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    avg_stat = query_average_stat();
    set_size_descs("tall", "lean");

    set_skill(SS_BRAWLING, 70 + random(30));
    set_skill(SS_HEARING, 70 + random(30));
    set_skill(SS_AWARENESS,70 + random(30));
    set_skill(SS_SNEAK, 70 + random(35));
    set_skill(SS_HIDE, 70 + random(35));
    set_skill(SS_HUNTING, 70 + random(35));
    set_skill(SS_LOC_SENSE, 70 + random(35));
    set_skill(SS_TRACKING, 70 + random(35));
    set_alignment(600 + random(300));
    set_cact_time(2);
    add_cact("brawl");
    add_ask("name", &give_name());
    set_default_answer("say I do not know what you are talking about!", 1);
    create_ranger();

}

public void
test_badge(object ob)
{
    object badge;

    if (objectp(badge = present("_ithilien_badge", ob)))
    {
        command("shout Dirty traitor!");
        command("kick " + OB_NAME(ob));
        remove_badge(badge, ob);
    }
}

varargs void
remove_badge(object badge, object player = TP)
{
    if (RANGERS_MEMBER(player))
        return;

    if (!objectp(badge))
        return;

    if (!badge->id("_ithilien_badge"))
        return;

    player->catch_tell(TO->query_The_name(player) + " takes your badge.\n");
    tell_room(ENV(TO), QCTNAME(TO) + " takes a badge away from " +
        QCTNAME(player) + ".\n", player);
    badge->move(TO);
    command("emote breaks the badge.");
    badge->remove_object();
    player->add_prop("_no_pass_to_ithilien", 1);
    return;
}

void
set_agg_ranger()
{
    agg_ranger = 1;
}

/* 
 * Function name: set_incognito
 * Description  : Kept for backwards compatibility
 */
void
set_incognito()
{
    incognito = !incognito;
}

/*
 * Function name: oke_to_move
 * Description  :This function makes the ranger sneak when moving randomly
 * Arguments    : string exit - the exit to take
 * Returns      : int - 0 if fighting,
 *                string - command to sneak towards an exit
 */
mixed
oke_to_move(string exit)
{
    if (this_object()->query_attack())
        return 0;

    return "sneak " + exit;
}

void
attacked_by(object ob)
{
    object room = ENV(TO), *arr;

    ::attacked_by(ob);

    test_badge(ob);
    arr = filter(all_inventory(room), &->id("ranger"));
    arr->notify_ob_attacked_me(TO, ob);
}

static void
do_attack(object victim)
{
    if (objectp(query_attack()))
        return;
    else if (!present(victim, ENV(TO)))
        return;
    else if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
    {
        if (!random(6))
            command("shout I cannot see your attacker anywhere!");
        return;
    }

    attack_object(victim);
    add_prop(LIVE_O_LAST_KILL, victim);
    command("brawl " + OB_NAME(victim));
}

void
help_friend(object ob, object friend)
{
    remove_alarm(hf_aid);
    hf_aid = 0;

    if (objectp(ob) && !objectp(query_attack()) &&
      present(ob, ENV(TO)) && ob->check_seen(TO))
    {
        command("shout " + ONE_OF_LIST( ({ "Foolish move, ", 
            "You'll regret that, ", "Flee home to the Land of Shadows, ",
            "Mandos take your soul, ", "Die, foul ", })) +
            ob->query_race_name() + "!");
        do_attack(ob);
    }
}

public varargs void
notify_ob_attacked_me(object friend, object attacker, int chance = 1)
{
    if (objectp(query_attack()) || (hf_aid && sizeof(get_alarm(hf_aid))))
        return;
    else if (chance > 0)
        hf_aid = set_alarm(4.0, 0.0, &help_friend(attacker, friend));
}

/*
 * Function name: special_attack
 * Description  : Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 *                We need this instead of using sequences for brawl
 *                since sequences are too unreliable (delay of 300 seconds
 *                if set_cact_time(2))
 * Arguments    : victim (the one we are fighting right now)
 * Returns      : 0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note         : By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
public int
special_attack(object victim)
{
    if (query_prop("_ranger_i_prepare_brawl"))
        return 0;

    if (random(2))
        command("brawl");

    return 0;
}


/*
 * Function name: enter_env
 * Description  : mask parent so we can check new env for spying eyes
 * Arguments    : to - where we're going to
 *                from - where we came from
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (objectp(present("eye", ENV(TO))))
        set_alarm(2.0, 0.0, destroy_eyes);

}

/*
 * Function name: destroy_eyes
 * Description  : smash any spying eyes in env
 */
public void
destroy_eyes()
{
    int s;
    object *eyes = filter(all_inventory(ENV(TO)), &->id("eye"));

    s = sizeof(eyes);
    if (s > 0)
    {
        command("emote smashes the glass eye" + (s > 1 ? "s." : "."));
        eyes->remove_object();
    }
}


/* 
 * Function name: greet
 * Description  : This function makes the npc do a greeting to people it
 *                already knows and to fellow npc's. It is possible to
 *                redefine, note however that it should never contain an
 *                'introduce myself' command.
 * Arguments    : object who - the living that introduced to me
 *
 */                   
public void
greet(object who)
{
      // He won't greet an enemy! 
    if (member_array(who, query_enemy(-1)) > -1) 
        command("kill " + OB_NAME(who)); 

    if (who->query_alignment() > 0)
    {
        command("nod" + who->query_real_name());
        return;
    }
} 

/* 
 * Function name:   introduce 
 * Description  :   This function makes the npc do an introduction to a 
 *                  player that has not been introed to it earlier. The 
 *                  function may be redefined to create variety. 
 * Arguments    :   object who - the living that introduced to me 
 * 
 */
public void 
introduce(object who)
{
    if (who->query_race_name() == "goblin")
    {
        command("peer suspiciously " + OB_NAME(who));
        command("rsay Be gone, foul creature!");
        return;
    }
    else if (member_array(who, query_enemy(-1)) > -1) 
    { 
        // He won't intro to an enemy 
        command("kick " + OB_NAME(who)); 
        return;
    } 

    /* secretive rangers only intro to each other */    
    if (RANGERS_MEMBER(who))
    {
        command("rbow " + who->query_real_name());
        command("rsignal Greetings, fellow ranger!");
        return;
    }
    if (who->query_alignment() > 0)
    {
        command("rconsider " + who->query_real_name());
        command("nod " + who->query_real_name());
        return;
    }
    command("nod " + who->query_real_name());
    command("stare");
    return;
}

void
init_living()
{
    ::init_living();
    initiate_ranger_soul();
}