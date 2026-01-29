/*      the Calian warrior guild in the crystalline palace

    coder(s):   Glykron

    history:     4. 5.92    guildmaster and cmdsoul added   Glykron
                 5. 4.92    header added and exit up        Glykron
                14.4.94     poster update added             Maniac
                   5.94     council modifications made      Maniac

    to do:      enter light

*/


inherit "/std/room";
inherit "/lib/skill_raise";
inherit "/lib/trade";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
 
#include "defs.h"
#include COUNCIL_DEFS
 
inherit POSTER_DIR + "maintain_poster";

#define NUM_SKILLS 11

static int *skill_list, num_of_types;
static string *money_types;
static object guildmaster;

int
is_calian(object living)
{
    return living->query_guild_member(GUILD_NAME);
}

void
set_up_skills()
{
    string me, ot;

    skill_list = ({ SS_WEP_SWORD, SS_WEP_POLEARM, SS_WEP_AXE, SS_WEP_KNIFE,
        SS_WEP_MISSILE, SS_WEP_JAVELIN, SS_2H_COMBAT, SS_PARRY, SS_DEFENCE,
        SS_SWARM, SS_MOVE_BEHIND });

    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }), 0, 0, 90 );
    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM,({ me, ot }), 0, 0, 80 );
    me = "use an axe"; ot = me;
    sk_add_train(SS_WEP_AXE,    ({ me, ot }), 0, 0, 30 );
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,  ({ me, ot }), 0, 0, 30 );
    me = "file a missile"; ot = me;
    sk_add_train(SS_WEP_MISSILE,({ me, ot }), 0, 0, 30 );
    me = "throw a javelin"; ot = me;
    sk_add_train(SS_WEP_JAVELIN,({ me, ot }), 0, 0, 30 );
    me = "fight with two hands"; ot = me;
    sk_add_train(SS_2H_COMBAT,  ({ me, ot }), 0, 0, 65 );
    me = "parry"; ot = me;
    sk_add_train(SS_PARRY,      ({ me, ot }), 0, 0, 75 );
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,    ({ me, ot }), 0, 0, 75 );
    me = "swarm enemies"; ot = me;
    sk_add_train(SS_SWARM,      ({ me, ot }), "swarm", 100, 100);
    me = "move behind team members during fight"; ot = me;
    sk_add_train(SS_MOVE_BEHIND,({ me, ot }), "move behind", 50, 100);
}

int
up()
{
    if (!is_calian(TP))
    {
        write("You step into the white light but nothing happens.\n");
        return 1;
    }

    seteuid(getuid());
    if (COUNCIL_CODE->is_upstairs_banned(TP))
    {
        TP->catch_msg("You have been banned from going upstairs here by " +
                      "the Calian Council, which has not yet granted you " +
                      "a pardon.\n");
        return 1;
    }

    write("You step into the white light, gently ascend, and then step out.\n");
    say(QCTNAME(TP) + " steps into the white light.\n");
    tell_room(P2_DIR + "guild",
        QCTNAME(TP) + " steps out of the white light.\n");
    return 0;
}

/*
int
enter_light(string str)
{
    if (str != "light") return 0;
    return 1;
}
*/

void
create_room()
{ 
    set_short(GUILD_NAME);

    set_long(BS(
        "This is the Calian warrior's guild.  " +
        "If you wish to join, you have to type <promise trust>.  " +
        "There will be a tax of " + GUILD_TAX + "% of your future " +
        "experience imposed on you.  " +
        "You can leave whenever you like, but it will cost you 1/10 of " +
        "your accumulated combat experience, and skills you can acquire from " +
        "this guild above superior layman will become useless; just type " +
        "<break trust>.  " +
        "The guildmaster has a medallion for you if you join.  " +
        "If you ever lose yours, need it replaced, or want to recycle it, " +
        "just use <ask, replace, or recycle medallion>.  " +
        "If you want to start in this room, type <start here>.  " +
        "You can examine the <list> of titles if you so choose.  " +
        "To find out which guilds you are a member of, type <list guilds>.  " +
        "Various warrior skills are taught here by the guildmaster.  " +
        "You can <learn> new skills or <improve> the ones you already have " +
        "if you are a member of the guild.  " +
        "There is also a circular portal to the northeast.  " +
        "A beam of white light cuts the center of the room.  " +
        "\n"));

    clone_object(GUILD_DIR + "board")->move(THIS);
    clone_object(GUILD_DIR + "book")->move(THIS);
    guildmaster = clone_object(GUILD_DIR + "guildmaster");
    guildmaster->move(THIS);

    add_item("portal", BS(
        "The portal is encircled by a golden ring.  " +
        "It has a white sheet of light inside the ring that does not " +
        "shimmer.  " +
        "\n"));
    add_item("beam", BS(
        "The beam of white light goes from the floor to the ceiling.  " +
        "Nothing can be seen in the light.  " +
        "\n"));

    add_exit(PALACE_DIR + "hall", "east", 0);
    add_exit(PALACE_DIR + "training", "north", 0);
    add_exit(PALACE_DIR + "bank", "southwest", 0);
    add_exit(PALACE_DIR + "common", "northeast", 0);
    add_exit(P2_DIR + "sanctuary", "up", "@@up");

    add_prop(OBJ_S_WIZINFO, "This is a default start location.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 10);

    create_skill_raise();
    set_up_skills();
    config_default_trade();
}


int
join(string str)
{
    object tp, orb, shadow;

    if (str != "trust" && str != "my trust")
        return 0;

    tp = TP;
    if (!present(guildmaster, THIS))
    {
        write("You cannot join the guild while the guildmaster is not here.\n");
        return 1;
    }

    if (tp->query_guild_member(GUILD_NAME))
    {
        write("You are already a member of this guild.\n");
        return 1;
    }

    if (tp->query_guild_style("magic"))
    {
        write( "You cannot join this guild while you are a member of a " +
            "mage guild.\n");
        return 1;
    }

    if (tp->query_guild_member(GUILD_TYPE))
    {
        write("You are already a member of another " + GUILD_TYPE +
            " guild.\n"); 
        return 1;
    }

    if (tp->query_alignment() < (tp->query_stat(SS_OCCUP) - 1) * 5)
    {
        write(BS(
            "I heard rumours you've been up to no good lately.  " +
            "You must atone for your deeds before you can be trusted.  " +
            "\n"));
        return 1;
    }
 

    orb = present("Calia-orb", guildmaster);
    if (!orb)
    {
        write(BS("The guildmaster says: You must give me a crystalline orb " +
            "before you can join this guild.  You'll need help from a " +
            "current member to get it.  " +
            "\n"));
        return 1;
    }

   seteuid(getuid());
    COUNCIL_CODE->carry_out_punishments(tp);
     if (COUNCIL_CODE->is_expelled(tp))
    {
        tp->catch_msg("You were expelled from the guild before, and " +
                      "have not been granted a pardon by the Calian " +
                      "Council.\n");
        return 1;
    }

    shadow = clone_object(GUILD_SHADOW);
    if (shadow->shadow_me(tp, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)
    {
        NF("For some unknown reason you cannot join this guild.\n");
        shadow->remove_shadow();
        return 1;
    }


    update_poster(capitalize(tp->query_real_name()) + " joined our " +
                  "guild!\n");

    tp->set_guild_pref(SS_OCCUP, GUILD_TAX);
    tp->set_learn_pref(TP->query_learn_pref(-1));
    orb->remove_object();
    write("The guildmaster turn the orb into dust and sprinkles it on you.\n" +
        "You are now a member of this guild.\n");
    say("The guildmaster turns the orb into dust and sprinkles it on " +
        QCTNAME(tp) + ".\n");

    if (!present("Calia_medallion", tp))
    {
        object medallion;

        write("The guildmaster gives you a medallion.\n");
        say("The guildmaster gives " + QTNAME(tp) + " a medallion.\n");
        medallion = clone_object(MEDALLION);
    }

    tp->add_cmdsoul(CALIAN_SOUL);
    tp->update_hooks();
    return 1;
}

int
truncate_skill(object tp, int skill)
{
    int old;
    old = tp->query_skill(skill);
    if (old <= 30) return 0;
    tp->set_skill(skill, 30);
    return 1;
}

int
leave(string str)
{
    object tp;

    if (str != "trust" && str != "my trust")
        return 0;

    tp = TP;
    if (!present(guildmaster, THIS))
    {
        write("You cannot leave the guild while the guildmaster is not here.\n"
            );
        return 1;
    }

    if (!is_calian(tp))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    if (tp->remove_guild_occ())
    {
        object medallion;
        int i, skills_lost;
        write("You are no longer a member of this guild.\n");
        say(QCTNAME(tp) + " leaves the guild.\n");
        tp->add_exp((-tp->query_exp_combat() / 10), 1);

        skills_lost = 0;
        for(i = 0; i < NUM_SKILLS; i++)
            if (truncate_skill(tp, skill_list[i])) skills_lost = 1;
        if (skills_lost)
            write("Some of your experience and skills have become useless.\n");
        else
            write("Some of your experience has become useless.\n");

        if (tp->query_default_start_location() == PALACE_DIR + "guild")
        {
            tp->set_default_start_location(tp->query_def_start());
            write("You no longer start here.\n");
        }

        tp->set_guild_pref(SS_OCCUP, 0);
        tp->set_learn_pref(tp->query_learn_pref(-1));
        tp->remove_cmdsoul(CALIAN_SOUL);
        tp->update_hooks();
    }
    else
        write("Because of a bug you cannot leave the guild.\n");

    return 1;
}

int
ask(string str)
{
    if (str != "medallion" && str != "for medallion")
        return 0;

    if (!present(guildmaster, THIS))
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

    write("The guildmaster gives you a medallion.\n");
    clone_object(MEDALLION)->move(TP);
    return 1;
}

int
replace(string str)
{
    object medallion;

    if (str != "medallion")
        return 0;

    if (!present(guildmaster, THIS))
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

    medallion = present("Calia_medallion", TP);
    if (medallion)
    {
        write("The guildmaster takes your old medallion and then gives you a " +
            "new one.  " +
            "\n");
        say(BS("The guildmaster takes " + QTNAME(TP) + "'s medallion and " +
            "then gives " + TP->query_objective() + " a new one.  " +
            "\n"));
        medallion->remove_object();
        clone_object(MEDALLION)->move(TP);
    }
    else
        write("You have no medallion to replace!\n");

    return 1;
}

int
recycle(string str)
{
    object medallion;

    if (str != "medallion")
        return 0;

    if (!present(guildmaster, THIS))
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

    medallion = present("Calia_medallion", TP);
    if (medallion)
    {
        write("The guildmaster takes your medallion.\n");
        say("The guildmaster takes " + QTNAME(TP) + "'s medallion.\n");
        medallion->remove_object();
    }
    else
        write("The guildmaster gives you a medallion.\n");

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

    return sprintf("%-18s%-21s%-20s%-20s\n", sk_trains[snum][0],
                cost, next_rank, max_rank);

/*
    return sprintf("  %-17s %13s  %-21s %-20s\n", sk_trains[snum][0],
                cost, next_rank, max_rank);
*/
}

int
sk_improve(string str)
{
    int steps;

    if (!str || sscanf(str, "%d", steps))
        return sk_list(steps);

    if (!present(guildmaster, THIS))
    {
        write("You cannot improve skills while the guildmaster is not here.\n");
        return 1;
    }

    if (!is_calian(TP))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    if (TP->query_alignment() < (TP->query_stat(SS_OCCUP) - 1) * 5)
    {
        write(BS(
            "I heard rumours you've been up to no good lately.  " +
            "You must atone for your deeds before I will teach you " +
            "anything.  " +
            "\n"));
        return 1;
    }

    if (COUNCIL_CODE->is_train_banned(TP))
    {
       TP->catch_msg("You were banned from training by the Calian " +
                     "Council, which has not yet pardoned you.\n"); 
       return 1;
    }

    return ::sk_improve(str);
}

int
start(string str)
{
    if (str != "here") return 0;

    if (!is_calian(TP))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    TP->set_default_start_location(PALACE_DIR + "guild");
    write("Ok, you start here now.\n");
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
                "The Swordsman of Calia.\n" +
                "The Swashbuckler of Calia.\n" +
                "The Comrade in Arms of Calia.\n" +
                "The Cavalier of Calia.\n" +
                "The Paladin of Calia.\n" +
                "The Defender of Calia.\n" +
                "The Nobleman of Calia.\n" +
                "The Calian Champion.\n" +
                "The Weapon Master of Calia.\n" +
                "The Battle Hero of Calia.\n" +
                "The War Legend of Calia.\n" +
                "The Exalted Member of Caliana's Elite Guard.\n"
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

void
init()
{
    ::init();
    add_action("join", "promise");
    add_action("leave", "break");
    add_action("ask", "ask");
    add_action("replace", "replace");
    add_action("recycle", "recycle");
    init_skill_raise();

    add_action("start", "start");
    add_action("list", "list");
}
