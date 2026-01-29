/*      the Calian warrior guild training room in the crystalline palace

    coder(s):   Glykron & Maniac
    history:
                 5. 4.92    header added and exit up        Glykron
                 4. 5.92    guildmaster and cmdsoul added   Glykron
                14. 4.94    poster update added             Maniac
                    5.94    council modifications made      Maniac
                24.10.94    start here bug removed          Maniac
		19.11.94    calians can attack;
		            occ stat cleared when leaving   Glykron
                15.12.94    occ stat cleared when joining   Maniac
                 9.2.95     "apply_calia" command added     Maniac
                16.2.95     modified for skill decay        Maniac
                13.3.95     inherit of calian_code          Maniac
                 6.4.95     poster -> help option           Maniac
                17.5.95     caliana help option added       Maniac     
                23/5/95     exit down for Calians           Maniac
                 5/6/95     restricted polearm / 
                            sword  training added           Maniac
                10/7/95     long changed                    Maniac
                11/9/95     MEDALLION_MIN_ALIGN added       Maniac
                22/9/95     kroug raid code installed       Maniac
                2/10/95     corrections & more kroug raid stuff  Maniac
               23/10/95     krom reset                      Maniac
               3/12/95      missile&javelin moved to adv guild    Maniac
               27/2/96      recycle medallion corrected     Maniac
               18/3/96      move bug corrected              Maniac
               19/3/96      team object installation        Maniac
               13/4/96     tidied up kroug handling         Maniac
               10/6/96     used correct <more>              Maniac
               26/7/96     old raid note code taken out     Maniac
               1/11/96     updated help options             Maniac 
               7/12/96     maul skill added                 Maniac
               18/08/97    Sup. Guru Quest added            Khail
*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "/d/Calia/eldoral/guru_quest.h"
#include "/d/Calia/glykron/palace/rooms/light/defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER

#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
inherit "/lib/skill_raise";
inherit "/lib/trade";
inherit GLYKRON_SPECIALS + "calian_code";

#define NUM_SKILLS 11
#define HELP_FILE_DIR "/d/Calia/glykron/palace/texts/"
#define DOWN "/d/Calia/mountain/cr_tunnel/rooms/hallway"

int num_of_types;
string *money_types;
object guildmaster, board;


/* This checks access for going down into the tunnel from this room */
int
enter_check(object player)
{
        object *team;
        int i, enter_ok;

        seteuid(getuid());
        enter_ok = 0;

        if (COUNCIL_CODE->is_upstairs_banned(player))
                return 0;

        if (member_array(player->query_name(), 
                         COUNCIL_CODE->query_enemy_list()) > -1)
                return 0;

        if (is_calian(player))
                return 1;

        /*      else, for all non-calians, check to see
                if they're teamed with a calian
        */
        team = player->query_team_others();
        if(sizeof(team))
                for (i = 0; i < sizeof(team); i++)
                {
                        if ((is_calian(team[i]))&&
                        (!COUNCIL_CODE->is_upstairs_banned(team[i])))
                                enter_ok = 1;
                }

        return enter_ok;
}


void
set_up_skills()
{
    string me, ot;

#ifdef GURU_OPEN
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }), 0, 0, 100 );
    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM,({ me, ot }), 0, 0, 100 );
#else
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }), 0, 0, 90 );
    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM,({ me, ot }), 0, 0, 90 );
#endif
    me = "fight with two hands"; ot = me;
    sk_add_train(SS_2H_COMBAT,  ({ me, ot }), 0, 0, 65 );
    me = "parry"; ot = me;
    sk_add_train(SS_PARRY,      ({ me, ot }), 0, 0, 75 );
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,    ({ me, ot }), 0, 0, 75 );
    me = "swarm enemies"; ot = me;
    sk_add_train(SS_SWARM,      ({ me, ot }), "swarm", 100, 100);
    me = "maul enemies"; ot = me;
    sk_add_train(SS_MAUL,      ({ me, ot }), "maul", 100, 100);
    me = "move behind team members during fight"; ot = me;
    sk_add_train(SS_MOVE_BEHIND,({ me, ot }), "move behind", 50, 100);
}

#ifdef GURU_OPEN
public varargs int
sk_query_max(int snum, int silent)
{
    if (snum != SS_WEP_SWORD && snum != SS_WEP_POLEARM)
        return ::sk_query_max(snum, silent);

    if (this_player()->test_bit("Calia", GURU_QUEST_GROUP,
        GURU_QUEST_BIT))
        return ::sk_query_max(snum, silent);

    return 90;
}
#endif

int
up()
{
    object tp;

    tp = TP;
    if (!is_calian(tp))
    {
        write("You step into the white light but nothing happens.\n");
        return 1;
    }

    if (COUNCIL_CODE->is_upstairs_banned(TP))
    {
        tell_object(TP, 
	    "You have been banned from going upstairs here by the Calian " +
	    "Council, which has not yet granted you a pardon.\n");
        return 1;
    }

    write("You step into the white light, gently ascend, and then step out.\n");
    say(QCTNAME(tp) + " steps into the white light.\n");
    tell_room(ROOM("light_guild"),
        QCTNAME(tp) + " steps out of the white light.\n");
    tp->move_living("M", ROOM("light_guild"));
    return 1;
}


/* Move one player down */
void
move_down(object player)
{
    tell_room(this_object(),
        QCTNAME(player)+" steps into the white light.\n", player);
    tell_object(player, "You step into the white light, gently " +
                         "descend, and step out.\n");
    player->move_living("M", DOWN, 1);
    tell_room(environment(player), QCTNAME(player)+" steps out " +
                               "of the white light.\n", player);
}


/* Move player down and anyone he's teamed with who is allowed */
void
moves_down()
{
    int i;
    object tp, *team, *m_team;

    tp = TP;
    team = tp->query_team();
    m_team = ({ });

    for (i = 0; i < sizeof(team); i++)
        if ((environment(tp) == environment(team[i])) &&
            enter_check(team[i]))
            m_team += ({team[i]});

    move_down(tp);
    for (i = 0; i < sizeof(m_team); i++)
        move_down(m_team[i]);
}


int
down()
{
    object tp;

    tp = TP;
    if (!enter_check(tp))
    {
        write("You step into the white light but nothing happens.\n");
        return 1;
    }
    moves_down();
    return 1;
}


string
long()
{
     string str;

     str = "This is the Calian warrior's guild.  " +
        "If you wish to join, you have to type <promise trust>.  " +
        "There will be a tax of " + GUILD_TAX + "% of your future " +
        "experience imposed on you.  " +
        "You can leave whenever you like, but you will lose 1/4 of " +
        "your accumulated combat experience; just type " +
        "<break trust>.  " +
        "The guildmaster has a medallion for you if you join.  " +
        "If you ever lose yours, need it replaced, or want to recycle it, " +
        "just use <ask, replace, or recycle medallion>.  " +
        "You can examine the <list> of titles if you so choose.  " +
        "To find out which guilds you are a member of, type <list guilds>.  " +
        "Various warrior skills are taught here by the guildmaster.  " +
        "You can <learn> new skills or <improve> the ones you already have " +
        "if you are a member of the guild.  Those wishing for more " +
        "information about the guild should try <help applicant> here.  " +
        "There is a circular portal to the northeast.  " +
        "A beam of white light cuts the center of the room.  "; 
     if (is_calian(this_player()))
        str += "Being a Calian, you can go up or down from here, unless " +
               "the Council has banned you.";
     str += "\n";
     return str;
}


/* Bring guildmaster back in if he's missing */
void
reset_room()
{
    if (!objectp(guildmaster)) {
         guildmaster = clone_object(MONSTER("calian_guildmaster"));
         guildmaster->move_living("into the training room", THIS);
    }
}


void
create_room()
{ 
    set_short(GUILD_NAME);
    set_long("@@long");

    board = clone_object(OBJECT("calian_public_board"));
    board->move(this_object());

    add_item("portal",
        "The portal is encircled by a golden ring.  " +
        "It has a white sheet of light inside the ring that does not " +
        "shimmer.  " +
        "\n");
    add_item("beam",
        "The bream of white light goes from the floor to the ceiling.  " +
        "Nothing can be seen in the light.  " +
        "\n");

    add_exit(ROOM("light_hall"), "east", 0);
    add_exit(ROOM("light_training"), "north", 0);
    add_exit(ROOM("light_bank"), "southwest", 0);
    add_exit(ROOM("light_common"), "northeast", 0);

    add_prop(ROOM_I_INSIDE, 1);

    create_skill_raise();
    set_up_skills();
    config_default_trade();
    reset_room();
}

int
ask(string str)
{
    if (str != "medallion" && str != "for medallion")
        return 0;

    if (!objectp(guildmaster) || !present(guildmaster, THIS))
    {
        write("You cannot ask for a medallion while the guildmaster is not " +
            "here.\n");
        return 1;
    }

    if (!is_calian(TP))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }
 
    if (TP->query_alignment() < MEDALLION_MIN_ALIGN) {
        guildmaster->command("say No medallion until your alignment " +
                             "is positive, " + TP->query_name() + "!");
        return 1;
    }

    if (present("Calia_medallion", TP)) {
        guildmaster->command("say You have already have a medallion, " + 
                              TP->query_name() + "!");
        return 1;
    }

    if (!present("Calia_medallion", guildmaster))
        clone_object(OBJECT("calian_medallion"))->move(guildmaster);

    if (guildmaster->command("give medallion to " + TP->query_real_name())) {
        clone_object(OBJECT("calian_medallion"))->move(guildmaster);
        return 1;
    }
    
    guildmaster->command("say I can't seem to give a medallion to you, " + 
                         TP->query_name() + ".");
    guildmaster->command("shrug"); 
    return 1;
}


int
replace(string str)
{
    object medallion;

    if (str != "medallion")
        return 0;

    if (!objectp(guildmaster) || !present(guildmaster, THIS))
    {
        write("You cannot replace a medallion while the guildmaster is " +
            "not here.\n");
        return 1;
    }

    if (!is_calian(TP))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    medallion = present("Calia_medallion", TP);
    if (medallion)
    {
        write("The guildmaster takes your old medallion and then gives you a " +
            "new one.  " +
            "\n");
        say("The guildmaster takes " + QTNAME(TP) + "'s medallion and " +
            "then gives " + TP->query_objective() + " a new one.  " +
            "\n");
        medallion->remove_object();
        clone_object(OBJECT("calian_medallion"))->move(TP);
    }
    else
        write("You have no medallion to replace!\n");

    return 1;
}


/* recycle a medallion, i.e. either take a medallion away or give a new one 
   to the player.
*/
int
recycle(string str)
{
    object medallion;

    if (str != "medallion")
        return 0;

    if (!objectp(guildmaster) || !present(guildmaster, THIS))
    {
        write("You cannot recycle a medallion while the guildmaster is not " +
            "here.\n");
        return 1;
    }

    if (!is_calian(TP))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    medallion = present("Calia_medallion", TP);
    if (medallion)
    {
        write("The guildmaster takes your medallion.\n");
        say("The guildmaster takes " + QTNAME(TP) + "'s medallion.\n");
        medallion->remove_object();
    }
    else {
        write("The guildmaster gives you a medallion.\n");
        say("The guildmaster gives " + QTNAME(TP) + " a medallion.\n");
        clone_object(OBJECT("calian_medallion"))->move(TP);
    }

    return 1;
}

/*
 * Function name: sk_hook_write_header
 * Description:   Write the header to the improve or learn list
 * Arguments:     steps - How many steps we are talking about
 */
void
sk_hook_write_header(int steps)
{
    if (!steps)
        steps = 1;
    write("These are the skills you are able to " + query_verb() +
        " " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
        " here.\n");
    write("Skill:            Cost:                "+
          "Next level:         Max level:          \n"+
          "----------------------------------------"+
          "---------------------------------------\n");
}

void set_money_types(string *a)
{
    money_types = a;
    num_of_types = sizeof(a);
    ::set_money_types(a);
}

/*
 * Function name: my_text
 * Description:   Generates a text string from the array describing the coins
 * Arguments:     arr - the array holding the coins to describe
 */
mixed
my_text(int *arr)
{
    string *t_arr;
    int i;
    
    if (sizeof(arr) < num_of_types)  /* Not a valid array. */
        return ;

    t_arr = ({ });

    for (i = num_of_types - 1; i >= 0; i--)
    {
        if (arr[i] > 0)
            t_arr += ({ arr[i] + " " + explode(money_types[i], "")[0] });
    }

    return implode(t_arr, ", ");
}


/*
 * Function name: sk_fix_cost
 * Description:   Fix each line in the improve/learn list
 * Arguments:     snum  - The skill to check
 *                steps - How many steps player wants to raise
 * Returns:       A formatted string
 */
varargs string
sk_fix_cost(int snum, int steps)
{
    int this_level, next_level, max;
    string next_rank, max_rank, cost;

    this_level = this_player()->query_base_skill(snum);
    next_level = steps ? this_level + steps : this_level + 1;

    if (next_level > (max = sk_query_max(snum)))
        cost = "---";
    else
    {
        cost = my_text(split_values(sk_cost(snum, this_level, next_level)));
        /*
        cost = sk_cost(snum, this_level, next_level) + " copper";
        */
    }

    if (this_level >= 100)
        next_rank = "maxed";
    else
        next_rank = sk_rank(next_level);

    max_rank = sk_rank(max);
    if ((snum == SS_WEP_POLEARM) || (snum == SS_WEP_SWORD)) 
        max_rank += "*"; 
    if ((snum == SS_MAUL) || (snum == SS_SWARM)) 
        max_rank += "+"; 

    return sprintf("%-18s%-21s%-20s%-20s\n", sk_trains[snum][0],
                   cost, next_rank, max_rank);

/*
    return sprintf("  %-17s %13s  %-21s %-20s\n", sk_trains[snum][0],
                cost, next_rank, max_rank);
*/
}


/*
 * Function name: sk_list
 * Description:   Someone wants a list of skills
 * Arguments:     steps - How many steps the player wants to raise
 * Returns:       1
 */
int
sk_list(int steps)
{
    int i, *guild_sk, learn;

    guild_sk = sk_query_train();
    if (!steps)
        steps = 1;

    if (steps < 0)
    {
        sk_hook_skillisting();
        steps = 1;
    }
    else if (query_verb() == "learn")
    {
        guild_sk = filter(guild_sk, &sk_filter_learn(,steps));
        if (!sizeof(guild_sk))
            return sk_hook_no_list_learn();
        sk_hook_write_header(steps);
    } 
    else {
        guild_sk = filter(guild_sk, &sk_filter_improve(,steps));
        if (!sizeof(guild_sk))
            return sk_hook_no_list_improve();
        sk_hook_write_header(steps);
    }

    for (i = 0; i < sizeof(guild_sk); i++)
        write(sk_fix_cost(guild_sk[i], steps));

    if ((member_array(SS_WEP_POLEARM, guild_sk) > -1) ||
        (member_array(SS_WEP_SWORD, guild_sk) > -1))
    {
#ifdef GURU_OPEN
        if (this_player()->test_bit("Calia", GURU_QUEST_GROUP,
            GURU_QUEST_BIT))
            write ("\n* " +
                "Combined levels in sword and polearm may " +
                "average at a maximum of eminent master/expert " +
                "master (88/87 levels).\n");
        else
            write("\n* " +
                "Combined levels in sword and polearm may " +
                "average at a maximum of apprentice master/" +
                "junior master (83/82 levels).\n");
#else
         write("\n* " +
             "Combined levels in sword and polearm may average at a "+
             "maximum of confident master (85 levels).\n"); 
#endif
    }

    if ((member_array(SS_MAUL, guild_sk) > -1) ||
        (member_array(SS_SWARM, guild_sk) > -1)) 
         write("\n+ " +
             "Combined levels in swarm and maul may average at a maximum "+
             "of superior journeyman (50 levels).\n"); 

    return 1;
}


int
sk_improve(string str)
{
    object tp;
    int steps, *guild_sk, *known_sk, snum, level, cost, sub, sw, pa;
    int swarm, maul; 
    string skill, verb, *tmp;

    if (!str || sscanf(str, "%d", steps))
        return sk_list(steps);

    if (!objectp(guildmaster) || !present(guildmaster, THIS))
    {
        write("You cannot improve skills while the guildmaster is not here.\n");
        return 1;
    }

    tp = TP;
    if (!is_calian(tp))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    if (tp->query_alignment() < (tp->query_stat(SS_OCCUP) / 2) * 5)
    {
        write("I heard rumours you've been up to no good lately.  " +
            "You must atone for your deeds before I will teach you " +
            "anything.  " +
            "\n");
        return 1;
    }

    if (COUNCIL_CODE->is_train_banned(tp))
    {
       tp->catch_msg("You were banned from training by the Calian " +
                     "Council, which has not yet pardoned you.\n");
       return 1;
    }

    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = str;
        steps = 1;
    }

    guild_sk = sk_query_train();
    known_sk = this_player()->query_all_skill_types();
    if (!known_sk)
        known_sk = ({});

    verb = query_verb();
    if ((snum = sk_find_skill(skill)) < 0)
        return sk_hook_unknown_skill(skill, verb);

    level = this_player()->query_base_skill(snum);

    /* Maul must be learned upstairs as it has special requirements. */ 
    if (!level && (verb == "learn") && (snum == SS_MAUL)) { 
        write("Maul may only be learned upstairs in a special room.\n"); 
        return 1;
    } 
    if (!level && verb == "improve")
        return sk_hook_improve_unknown(skill);
    if (level && verb == "learn")
        return sk_hook_learn_known(skill);
    if (level + steps > sk_query_max(snum))
        return sk_hook_improved_max(skill);
    if (!sk_do_train(snum, this_player(), level + steps))
        return sk_hook_cant_train(skill, level + steps);

    cost = sk_cost(snum, level, level + steps);

    if (!MONEY_ADD(this_player(), -cost))
    {
        this_player()->set_skill(snum, level);
        return sk_hook_cant_pay(skill, level + steps, cost);
    }

    sk_hook_raise_rank(snum, level + steps, cost);

    if (snum == SS_WEP_POLEARM) {
        sw = tp->query_base_skill(SS_WEP_SWORD);
        pa = level + steps;
#ifdef GURU_OPEN
        if (tp->test_bit("Calia", GURU_QUEST_GROUP, GURU_QUEST_BIT))
            sub = (sw + pa) - 175;
        else
            sub = (sw + pa) - 165;
#else
        sub = (sw + pa) - 170;
#endif
        if (sub > 0) {
            tp->set_skill(SS_WEP_SWORD, sw - sub); 
            tp->catch_msg("As you specialise more in polearms you " +
                          "forget some of your sword skill.\n");
        }
    }
    else if (snum == SS_WEP_SWORD) {
        pa = tp->query_base_skill(SS_WEP_POLEARM);
        sw = level + steps;
#ifdef GURU_OPEN
        if (tp->test_bit("Calia", GURU_QUEST_GROUP, GURU_QUEST_BIT))
            sub = (sw + pa) - 175;
        else
            sub = (sw + pa) - 165;
#else
        sub = (sw + pa) - 170;
#endif
        if (sub > 0) {
            tp->set_skill(SS_WEP_POLEARM, pa - sub); 
            tp->catch_msg("As you specialise more in swords you " +
                          "forget some of your polearm skill.\n");
        }
    }
    else if (snum == SS_MAUL) {
        swarm = tp->query_base_skill(SS_SWARM);
        pa = level + steps;
        sub = (swarm + pa) - 100;
        if (sub > 0) {
            tp->set_skill(SS_SWARM, swarm - sub); 
            tp->catch_msg("As you specialise more in maul you " +
                          "forget some of your swarm skill.\n");
        }
    }
    else if (snum == SS_SWARM) {
        maul = tp->query_base_skill(SS_MAUL);
        pa = level + steps;
        sub = (maul + pa) - 100;
        if (sub > 0) {
            tp->set_skill(SS_MAUL, maul - sub); 
            tp->catch_msg("As you specialise more in swarm you " +
                          "forget some of your maul skill.\n");
            if ((maul - sub) < 1) {  
                seteuid(getuid()); 
                MAUL_CONTROL->add_swarmer(tp->query_real_name());  
            } 
        }
    }

    return 1;
}


int
list(string str)
{
    object guilds;
    if (str != "guilds")
        if (str && str != "titles") return 0;
        else
        {
            write("The following are the possible titles granted to guild " +
                "members:\n" +
                "The Calian Trainee.\n" +
                "The Calian Adventurer.\n" +
                "The Warrior of Calia.\n" +
                "The Swordsman/woman of Calia.\n" +
                "The Swashbuckler of Calia.\n" +
                "The Comrade in Arms of Calia.\n" +
                "The Cavalier of Calia.\n" +
                "The Calian Fighter.\n" +
                "The Defender of Calia.\n" +
                "The Nobleman/woman of Calia.\n" +
                "The Calian Champion.\n" +
                "The Weapon Master/Mistress of Calia.\n" +
                "The Battle Hero/Heroine of Calia.\n" +
                "The War Legend of Calia.\n" +
                "The Exalted Member of Caliana's Elite Guard.\n\n" +
                "In addition Calians get to choose a second unique " +
                "title for themselves from a range of options.\n"
            );
            return 1;
        }

    guilds = TP->list_major_guilds();
    if (guilds)
        write("You are a member of the following guilds:\n" + guilds);
    else
        write("You are not a member of any guild.\n");
    return 1;
}


/* Handle an application for the Calian guild */
int
apply()
{
    object tp = this_player();
    string n = tp->query_name();

    seteuid(getuid());
    if (tp->query_guild_name_occ()) {
        notify_fail("You are already in an occupational guild!\n");
        return 0;
    }

    if (RECRUITER_CODE->is_applicant(n)) {
        notify_fail("You have already applied!\n");
        return 0;
    }

    RECRUITER_CODE->add_app(n);
    tp->catch_msg("Your application has been officially registered.\n");
    return 1;
}


void
general_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "general_appl"));
}

void
medallion_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "medallion"));
}

void
battle_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "battle"));
}

void
kroug_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "kroug"));
}

void
caliana_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "caliana"));
}

void
council_help()
{
    seteuid(getuid());
    this_player()->catch_msg(COUNCIL_CODE->query_council());
    this_player()->more(read_file(HELP_FILE_DIR + "council"));
}

void
rules_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "rules"));
}


void
roff_help()
{
    seteuid(getuid());
    this_player()->catch_msg(RECRUITER_CODE->query_recruiters_string());
    this_player()->more(read_file(HELP_FILE_DIR + "officers"));
}


void
enemies_help()
{
    seteuid(getuid());
    this_player()->catch_msg(COUNCIL_CODE->query_enemies());
    this_player()->more(read_file(HELP_FILE_DIR + "enemies"));
}

void
calian_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "calian"));
}

void
applying_help()
{
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR+"calian_recruitment_text"));
}

void
fail_help()
{
    this_player()->catch_msg("There is no such applicant help option.\n");
}

int
help(string str)
{
    string s;
        
    if (!str) 
        return 0;
    if (str == "applicant") {
        general_help();
        return 1;
    }
    if (sscanf(str, "applicant %s", s) == 1) {
        switch (s) {
            case "applying"  : applying_help();
                               break;
            case "medallion" : medallion_help(); 
                             break;
            case "battle" : battle_help();
                            break;
            case "caliana" : caliana_help();
                           break;
            case "kroug" : kroug_help();
                           break;
            case "council" : council_help();
                             break;
            case "calian" : calian_help(); 
                              break;
            case "rules" : rules_help();
                           break;
            case "officers" : roff_help();
                              break;
            case "enemies" : enemies_help();
                             break;
            default : fail_help();
                      break;
        }
       return 1;
    }
    return 0;
}



void
init()
{
    ::init();
    init_skill_raise();
    add_action("help", "help");
    add_action("apply", "apply_calia");
    add_action("join", "promise");
    add_action("leave", "break");
    add_action("ask", "ask");
    add_action("replace", "replace");
    add_action("recycle", "recycle");
    add_action("list", "list");
    add_action("up", "up");
    add_action("down", "down");
}
