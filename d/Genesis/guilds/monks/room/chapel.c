/*
 * File:    chapel.c
 * Creator: Cirion, 1998.06.14
 * Purpose: Chapel where monks can meditate
 */
#pragma strict_types
#include "defs.h"
#include <composite.h>
#include <tasks.h>
#include <ss_types.h>

inherit ROOMBASE;
inherit "/lib/guild_support";

#define MONK_I_PRAYING           "_monk_i_chapel_praying"
#define MONK_PRAYER_MANA_COST    10

// global vars
private object table;
public mapping disc_players = ([]);

void populate();
void reset_room();

string
chapel_long()
{
    string table_desc;

    if (present (table))
        table_desc = table->describe_table ();
    else
        table_desc = " Something is very wrong with this room!";

    return "This small chapel serves as a place of meditation "
        + "and rest. " + table_desc
        + " The rest of the floor is covered with parquet wooden "
        + "tiles staggered together. A large copper and silver lamp "
        + "hanging from the ceiling provides the only light for the "
        + "room.\n";

}

void
create_room ()
{
    set_short("chapel");
    set_long(chapel_long);
    add_item("dais",
        "It is a low, semicircular dais, made from white "
        + "marble. Sitting atop the dais is a simple altar "
        + "of dark wood.\n");
    add_item(({"image","images","bird","birds","dragon","dragons"}),
        "The images on the altar are intricate and "
        + "intertwining. They depict long, sinuous dragons "
        + "and graceful birds.\n");
    add_item(({"floor","ground","tile","tiles"}),
        "The floor is made from hard wooden tiles, fitted "
        + "together neatly.\n");
    add_item(({"lamp","copper lamp","silver lamp"}),
        "It is made from copper and silver, beaten together "
        + "in an ornate pattern. The light from within the "
        + "lamp casts irregular beams of light out along the "
        + "chapel.\n");
    add_item(({"light","beam","beams"}),
        "The copper and silver lamp casts out thin beams of  "
        + "light through the small holes in its surface. The "
        + "light shimmers along the walls in irregular patterns.\n");
    add_item(({"wall","walls"}),
        "The walls of the chapel are made from large blocks "
        + "of grey stone.\n");
    add_item("ceiling",
        "The ceiling of the chapel is high above. From the "
        + "illumination offered by the lamp, you can make "
        + "out the painted image of a long, sinuous grey "
        + "dragon.\n");
    add_cmd_item(({"lamp","copper lamp","silver lamp"}), ({"light"}),
        "It is already lit.\n");
    add_cmd_item(({"lamp","copper lamp","silver lamp"}), ({"extinguish"}),
        "You can find no way of opening it, and thus no way "
        + "to extinguish it.\n");
    add_cmd_item(({"altar","words","inscription"}), "read",
        "Pray for voice,\n"
        + "and speech will be granted thee.\n"
        + "Pray for Brotherhood,\n"
        + "and thy brethren ye shall see.\n");

    WIZINFO("This is the chapel for the monks guild, where they "
        + "may meditate and set their learning preferences. They may "
        + "also pray here for a spell token for the 'mtell' spell "
        + "( " + MONK_OBJ + "mtell_disc).\n");

    // where, command
    add_exit("hall_top", "east");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("east", "You walk through the doorway into the "
        + "small temple.\n");

    create_guild_support();
    populate();
    reset_room();
}

void
reset_room()
{
    string      *players;
    string      player;
    int         i;

    // go through all the disc players list and reduce the number
    // of discs they may have. Thus, players will be able to come
    // back after a while and get more discs.
    players = m_indices(disc_players);
    for(i=0;i<sizeof(players);i++)
    {
        player = players[i];
        disc_players[player] -= 5;
        if(disc_players[player] < 0)
            disc_players[player] = 0;
    }
}

void
dump_disc_players()
{
    dump_mapping(disc_players);
}

void
populate ()
{
    table = clone_object (MONK_OBJ + "chapel_altar");
    table->move (TO);
}

/*
 * Function name: prayer_catch_all
 * Description:   catch-all command hook to stop players
 *                from executing commands while in prayer.
 */
int
prayer_catch_all(string str)
{
    if(this_player()->query_prop(MONK_I_PRAYING))
    {
        // in case of disaster...
        if(query_verb() == "commune")
            return 0;

        write("But you are currently in prayer!\n");

        // naughty monk: executed a 'do' sequence to get
        // into prayer.
        this_player()->remove_do_alarm();

        if(this_player()->query_wiz_level())
        {
            write("...but that dosen't stop wizards.\n");
            return 0;
        }

        return 1;
    }

    return 0;
}

/*
 * Function name: prayer_hook
 * Description:   The result of praying for something
 *
 * Arguments:     who - the prayer
 *                what - the thing they prayed for
 */
void
prayer_hook(object who, string what)
{
    int     max_discs;

    who->add_mana(-(MONK_PRAYER_MANA_COST));
    set_this_player(who); // so we can use write()
    who->remove_prop(MONK_I_PRAYING);

    if(!m_query_monk()) // redundant sanity check
        return;

    switch(what)
    {
        // show a list of what monks are on
        case "brotherhood":
        case "sisterhood":
        case "friends":
        case "friendship":
        case "knowledge":
            write("You can see a vision of "
                + COMPOSITE_WORDS(filter(users(), m_query_monk)->query_name())
                + " all around you.\n");
            break;

        // try to gain a speaking coin.
        // You are limited by the number you can gain by your
        // skill in focus (1 coin for every 5 points), and there
        // is a routine task to complete before you can get it.
        case "voice":
            max_discs = who->query_skill(MONK_SKILL_FOCUS);

            if(m_query_monk(who, SS_OCCUP))
               max_discs = MIN(max_discs, who->query_stat(SS_OCCUP));
            else
               max_discs = MIN(max_discs, who->query_stat(SS_LAYMAN));

            if( (disc_players[who->query_real_name()] < max_discs) &&
                (who->resolve_task(TASK_ROUTINE, ({ MONK_SKILL_FOCUS })) > 0) )
            {
                // increment the internal counter of discs for that player
                // this is tracked in the room and not in the
                // player so that unethical players cannot quit, log
                // back in, and get more.
                disc_players[who->query_real_name()]++;

                write("You offer up your prayers for voice.\n");

                // clone a speaking coin, move it to the altar
                clone_object(MONK_OBJ + "mtell_disc")->move(table, 1);
                tell_room(this_object(), "A small iron disc forms from "
                    + "a thin cloud of dust and smoke upon the altar.\n");
            }
            else
                write("Your prayers fail.\n");
            break;


        default:
            write("Your prayers go unheard.\n");

    }

    say(QCTNAME(who) + " rises from prayer.\n");
    return;
}


/*
 * Function name: do_pray
 * Description:   Command that allows a monk in good standing
 *                to start praying for something.
 */
int
do_pray(string str)
{
    string    for_what;

    if(!m_query_monk())
    {
        write("You lower your head in prayer.\n");
        say(QCTNAME(this_player()) + " prays.\n");
        return 1;
    }

    // disgraced players cannot pray
    if(m_query_punishment(this_player(), M_PUNISH_DISGRACE))
    {
        write("It is futile to pray while disgraced.\n");
        say(QCTNAME(this_player()) + " tries with futility to "
            + "pray.\n");
        this_player()->command("cry");
        return 1;
    }

    if(!strlen(str))
    {
        write("You sit cross-legged on the floor and offer "
            + "up your prayers to Them.\n");
        say(QCTNAME(this_player()) + " sits cross-legged on the floor "
            + "before the altar and prays silently.\n");
        return 1;
    }

    sscanf(str, "for %s", for_what);
    if(!strlen(for_what))
    {
        notify_fail("Pray for what?\n");
        return 0;
    }

    if(this_player()->query_mana() < MONK_PRAYER_MANA_COST)
    {
        write("Your mind is too weak now to attempt that.\n");
        say(QCTNAME(this_player()) + " seems to want to pray.\n");
        return 1;
    }

    set_alarm(10.0, 0.0, &prayer_hook(this_player(), for_what));
    this_player()->add_prop(MONK_I_PRAYING, time());

    // only add the paralysis action if it has not already been added for
    // this player.
    if(member_array("paralysis_command", get_localcmd(this_player())) == -1)
    {
        add_action(prayer_catch_all, "", 1);
        add_action(prayer_catch_all, "paralysis_command", 1);
    }

    write("You sit cross-legged on the floor and offer "
        + "up your prayers.\n");
    say(QCTNAME(this_player()) + " sits cross-legged on the floor "
        + "before the altar and prays silently.\n");
    return 1;
}


/*
 * Function name: gs_hook_start_meditate
 * Description  : Gives a nice description when someone starts to meditate.
 */
nomask public void
gs_hook_start_meditate()
{
    write("You kneel before the altar and concentrate "
        + "all your focus inwards.\n");
    say(QCTNAME(TP) + " kneels down before the altar.\n");
}

/*
 * Function name: gs_hook_rise
 * Description  : Gives a nice description when someone is done meditating.
 */
nomask public
void gs_hook_rise()
{
    write("You rise from the floor and open your eyes.\n");
    say(QCTNAME(this_player())+" rises from the floor and opens "
        + this_player()->query_possessive() + " eyes.\n");
}


void
init()
{
    ::init();

    init_guild_support();

    add_action(do_pray, "pray");  
}

