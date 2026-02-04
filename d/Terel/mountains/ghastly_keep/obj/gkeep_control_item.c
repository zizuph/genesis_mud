/*
 *  /d/Terel/mountains/ghastly_keep/obj/gkeep_control_item
 *
 *
 *  This rings purpose it monitor the Ghastly Keep. 
 *
 *  Date:                      What is done:                           By whom:
 *  ---------------------------------------------------------------------------
 *  29/04-17                   Fixed a few bugs.                       Znagsnuf
 *  30/04-17                   Altered it a bit                        Znagsnuf
 */

#pragma strict_types

inherit "/std/armour";
inherit "/cmd/std/command_driver.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include <filter_funs.h>
#include <tasks.h>
#include <files.h>

string check_terel(string str);

void
create_armour()
{
    set_name("ring");
    set_short("spiky mithril ring");
    set_long("This is the Ghastly Keep control item. 'check keep'.\n");

    set_default_armour(5, A_ANY_FINGER, 0, this_object());

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_BUY, 1);

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE,  1);
}

string
query_recover()
{
    return 0;
}

string
query_auto_load()
{
    if (environment()->query_wiz_level())
        return MASTER;
}

public void
init()
{
    ::init();
    add_action(check_terel, "check");
}

static int
filter_in_keep(object who)
{
    object env = environment(who);

    if (!env || !objectp(env))
        return 0;

    if(who->query_wiz_level())
        return 0;

    if(!wildmatch("/d/Terel/mountains/ghastly_keep/*", file_name(env)))
        return 0;

    return 1;
}

/*
 * Function name: check_ac()
 * Description  : Check the AC of a target.
 */
string
check_terel(string str)
{
    int i,y,z,       // for-loop
        nr_stones,   // Number of stones
        nr_tears,    // Number of tears
        players;    

    object *in_terel, // All filtered users in the Keep
           *all;      // Everything in the inventory

    string print, s_quest, guild, s_lvl, p_players;

    notify_fail(capitalize(query_verb()) + " what?\n");
    if(!str)
        return 0;

    notify_fail(capitalize(query_verb()) + " what?\n");
    if (!parse_command(str, ({ }), " [the] 'keep'"))
        return 0; 

    if(!this_player()->query_wiz_level())
    {    
        write("Only wizards are able to use this ring.\n");
        return "";
    }

    in_terel = filter(users(), &filter_in_keep());

    if(!sizeof(in_terel))
    {
        write("Nobody is in the proximity of the Ghastly Keep.\n");
        return "";
    }
    
    print = ("\t _ __________________________________________________ _\n"
            +"\t| |                                                  | |\n"
            +"\t| |            Currently in Ghastly Keep:            | |\n"
            +"\t| |            ^-^-^-^-^-^-^-^-^-^-^-^-^             | |\n"
            +"\t|#|--------------------------------------------------|#|\n");

    s_quest = "No";
    guild =   "No guild";
    nr_stones = 0;
    nr_tears = 0;
    s_lvl =   "No";

    for (i=0; i<sizeof(in_terel); i++) 
    {
        if(in_terel[i]->query_prop("_gkeep_task_started"))
            s_quest = "Yes";

        if(in_terel[i]->query_guild_name_occ())
            guild = in_terel[i]->query_guild_name_occ();        
        
        if(in_terel[i]->query_prop("_gkeep_finds_door2"))
            s_lvl = "Yes";

        if (in_terel[i]->test_bit("Terel", 1, 16))
            s_quest = "Done";

        // Checking the object, and the objects in the object.
        all = deep_inventory(in_terel[i]);

        for (y=0; y<sizeof(all); y++) 
        {
            if (all[y]->id("_ghastly_keep_stone"))
                nr_stones++;
        }

        for (z=0; z<sizeof(all); z++) 
        {
            if (all[z]->id("_ghastly_keep_tear"))
                nr_tears++;
        }

        print += sprintf(
                 "\t| | Name: %-17s Offset: %4d  Gender: %2d | |\n" 
                +"\t| | Race: %-17s Level: %-17s | |\n"
                +"\t| | Guild: %-36s      | |\n"
                +"\t| | Kills in Ghastly Keep: %-5d  Started quest: %-4s| |\n"
                +"\t| | Number of stones: %-2d \t  Second Level: %-5s| |\n"
                +"\t| | Number of tears: %-2d  \t  Tears turn in: %-4d| |\n",
        capitalize(in_terel[i]->query_real_name()), 
        in_terel[i]->query_appearance_offset(),
        in_terel[i]->query_gender(),
        capitalize(in_terel[i]->query_race_name()),
        capitalize(in_terel[i]->query_exp_title()),
        guild,
        in_terel[i]->query_prop("_gkeep_finds_door"),
        s_quest,
        nr_stones,
        s_lvl,
        nr_tears,
        in_terel[i]->query_prop("_gkeep_stone_delivery"));

        // Reset.
        s_quest = "No";
        guild =   "No guild";
        nr_stones = 0;
        nr_tears = 0;
        s_lvl =   "No";

        //if(sizeof(in_terel) > 1)
        print += ("\t|#|--------------------------------------------------|#|\n");

    }

    players = (sizeof(in_terel));
    p_players =  players + " " + ((players > 1) ? "players" : "player") 
                 + " in total."; 

    print += sprintf("\t| |\t            %-30s   | |\n", p_players);
    print += ("\t|_|__________________________________________________|_|\n\n");
    write(print);

    return "";
}
