/*
 * AA training room coded by Milan
 *
 *
 *   The Guild in Re Albi, original code by Styles, modified by Ged    
 *
 *     If the guild is closed you can toggle this by doing,
 *     > Call here close_guild
 *     This is a quick way to close/open it if needed
 *
 *  Modification log:
 * 
 *     2008.06.17, Toby: Fixed a message in block_exit for wizards.
 *     2008.06.27  Novo: Allow NPCs to enter rooms
 */
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "../guild.h"

inherit "/lib/skill_raise";
inherit SHIRE_ROOM;

public int block_non_member();

/*
 * Global variables
 */
int Closed;
string *Practising = ({ });

/*
 *  Prototypes
 */
void set_up_skills();

void
create_shire_room()
{
    Closed = 0; /* open by default */

    set_short("training room");
    set_long("This is the training room for Angmar's army. You see many "+
        "warriors practising their skills over and over again and hence "+
        "trying to achieve perfection.\n"+
        "   Most of them are practising fighting using shield and club. You "+
        "spy one warrior swinging his club in an extremely dangerous way. "+
        "You are relieved that you are not taking the place of his opponent "+
        "who skillfully defends himself against this assault with his shield. "+
        "Some of the warriors are even fighting blindfolded. They are "+
        "probably preparing for a night attack somewhere.\n"+
        "   Not everyone is fighting here. Some of them are playing a "+
        "strange game. They are guessing the strength or wisdom of "+
        "each other and then by solving riddles or lifting weights they can "+
        "find out whose guess was the best. Another group is playing yet "+
        "another game. They are hiding different things or themselves for "+
        "others to try and find.\n\n");

    add_item(({"warrior","warriors"}), "You see many warriors doing strange things.\n");
    add_item(({"list","paper"}), "It is only a piece of paper but there are "+
                                 "some words written on it.\n");
    add_cmd_item(({"list","paper"}), "read", "@@list@@");

    add_cmd_item("sign", "read", "@@read_sign@@");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "You can close/open guild by:\nCall here close_guild\n\n");

/*  add_exit(AA_DIR+"rooms/chapel", "north"); 
        Moved chapel near the entrance... now non-members dont wander the guild
        Varian - 2016
*/
    add_exit(AA_DIR+"rooms/start", "west");
    add_exit(AA_DIR+"rooms/c1", "south");
    add_exit(AA_DIR+"rooms/priv", "east");

    create_skill_raise();
    set_up_skills();
}

public int block_non_member()
{
    if (this_player()->query_wiz_level())
    {
        write("You are entering the member area, but as a "+
              "wizard you are allowed inside. Welcome!\n");
        return 0;
    }
    if (IS_MEMBER(this_player()) || this_player()->query_npc())
    {
        return 0;
    }
    write("You don't belong there!\n");
    return 1;
}

string
close_guild()
{
    Closed = !Closed;
    return "*** The guild is now "+(Closed ? "closed" : "open")+" ***\n";
}

string
wizinfo()
{
    return "If there is a reason you can close/open guild by typing:\n"+
        "     Call here close_guild\n"+
        "This will temporarily prevent mortals from entering. "+
        "After a reboot the guild is open by default.\n\n   Milan\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!query_ip_number(ob) || !Closed) return;

    if (ob->query_wiz_level())
        write("\nWARNING!\nI'm doing some work on the guild.\n");
    else
    {
        write("The guild is closed. Come back later.\n");
        ob->move(AA_DIR+"rooms/c1");
    }
}

void
init()
{
    init_skill_raise();
    ::init();
}

string
train_text(int skill)
{
    switch (skill)
    {
        case SS_WEP_CLUB:
            return "fight with clubs";
        case SS_PARRY:
            return "parry blows when wielding a weapon";
        case SS_DEFENCE:
            return "survive in the combat";
        case SS_BLIND_COMBAT:
            return "fight in the dark";
        case SS_SMASH:
            return "smash enemy with a club";
        case SS_SHIELD:
            return "to use shield for dodging blows";
        case SS_BASH:
            return "to use shield as a weapon";
        case SS_AWARENESS:
            return "be aware of surrounding";
        case SS_APPR_MON:
            return "be able estimate a possible oponent";
        case SS_HIDE:
            return "hide various things";
        case SS_SNEAK:
            return "sneak somewhere";
        default:
            return "do nothing. THIS IS A BUG :----)";
    }
}

void
set_up_skills()
{
    sk_add_train(SS_WEP_CLUB,     train_text(SS_WEP_CLUB),     0,0,100 );
    sk_add_train(SS_PARRY,        train_text(SS_PARRY),        0,0,80 );
    sk_add_train(SS_DEFENCE,      train_text(SS_DEFENCE),      0,0,90 );
    sk_add_train(SS_BLIND_COMBAT, train_text(SS_BLIND_COMBAT), 0,0,80 );

    sk_add_train(SS_SMASH, train_text(SS_SMASH), "smash",      75,100,SS_STR, 90);
    sk_add_train(SS_SHIELD,train_text(SS_SHIELD),"shield",     85,100,SS_DEX,110);
    sk_add_train(SS_BASH,  train_text(SS_BASH),  "shield bash",75,100,SS_DIS,110);

    sk_add_train(SS_AWARENESS,    train_text(SS_AWARENESS),    0,0,70 );
    sk_add_train(SS_APPR_MON,     train_text(SS_APPR_MON),     0,0,60 );

    sk_add_train(SS_HIDE,         train_text(SS_HIDE),         0,0,75 );
    sk_add_train(SS_SNEAK,        train_text(SS_SNEAK),        0,0,75 );
}


int
can_train_this_skill(object who, string skill, int step)
{
    int allow, s = sk_find_skill(skill);

    /*** we allow to forget anything he wants ***/
    if (step < 0) return 1;
    /*** check punishment ***/
    if (who->query_prop(AA_PUN))
    {
        who->catch_msg("You are banned from training here!\n");
        return 0;
    }
    if (who->query_aa_member_killer())
    {
        who->catch_msg("You are banned from training for killing angmar members!\n");
        return 0;
    }
    if (member_array(who->query_name(), Practising) != -1)
    {
        who->catch_msg("Your head is not capable to lear more so soon!\n");
        return 0;
    }
    /*** train only one step at a time ***/
    if (step > 1)
    {
        who->catch_msg("Training is hard process! One step at a time!\n");
        return 0;
    }
    /*** check if player is 'good' enough to train ***/
    if ( (20 * who->query_skill(s)) > 
         (who->query_aa_stat() - who->query_alignment()) )
    {
        who->catch_msg("Your position in army is too low for that!\n");
        return 0;
    }
    /*** layman restrictions ***/
    if (IS_LAYMAN(who))
    {
        switch(s)
        {
            case SS_WEP_CLUB:
            case SS_DEFENCE:
            case SS_PARRY:
            case SS_HIDE:
            case SS_AWARENESS:
            case SS_SNEAK:
                if(who->query_base_skill(s) < 50) allow = 1;
                break;
            case SS_BLIND_COMBAT:
                if(who->query_base_skill(s) < 20) allow = 1;
                break;
            default: allow = 1;
        }
        if (!allow)
        {
            who->catch_msg("Those levels are only for occupational warriors!\n");
            return 0;
        }
        return 1;
    }
    /*** guru quest ***/
    if (s == SS_WEP_CLUB)
    {
        if ((who->query_base_skill(SS_WEP_CLUB) < 90) ||
           present("_club_sup_guru_", who))
            return 1;
        who->catch_msg("You must be worthy to be able train so high!\n");
        return 0;
    }
    return 1;
}

int
sk_improve(string str)
{
    int steps;
    string skill, *tmp;

    if (!str || sscanf(str, "%d", steps))
        return sk_list(steps);

    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = str;
        steps = 1;
    }

    if (IS_MEMBER(TP))
    {
        if(can_train_this_skill(TP, skill, steps))
        {
            return ::sk_improve(str);
        }
        return 1;
    }
    write("You must be a member of the army to be able to train here.\n");
    return 1;
}

string
list()
{
    sk_list(-1);
    return "\n"+
           "    Layman members are restricted in these skills:\n"+
           "    ----------------------------------------------\n"+
           "      club .............. superior journeyman\n"+
           "      defence ........... superior journeyman\n"+
           "      parry ............. superior journeyman\n"+
           "      awareness ......... superior journeyman\n"+
           "      blindfighting ..... superior amateur\n"+
           "      sneak ............. superior journeyman\n"+
           "      hide .............. superior journeyman\n";
}

public varargs int
sk_query_max(int snum, int silent)
{
    if (TP->query_prop(AA_PUN)) return 0;
    if (TP->query_aa_member_killer() > 1) return 0;

    if (IS_LAYMAN(TP))  /* layman */
        switch (snum)
        {
            case SS_WEP_CLUB:
            case SS_DEFENCE:
            case SS_PARRY:
            case SS_AWARENESS:
            case SS_HIDE:
            case SS_SNEAK:
                return 50;
            case SS_BLIND_COMBAT:
                return 20;
        }

    if ((snum == SS_WEP_CLUB) && (!present("_club_sup_guru_", TP)))
        return 90;

    return ::sk_query_max(snum, silent);
}

string
make_string_from_list(string *names)
{
    int i, s = sizeof(names);
    string text = "";

    sort_array(names);

    if(!s) return "  ----";
    if(find_player(names[0])) text += "*";
    text += capitalize(names[0]);
    for(i = 1; i < s-1; i++)
    {
        if(find_player(names[i])) text += ", *";
        else text += ", ";
        text += capitalize(names[i]);
    }
    if(s > 1)
    {
        if(find_player(names[s-1])) text += " and *";
        else text += " and ";
        text += capitalize(names[s-1]);
    }
    return break_string(text, 60, 5);
}

string read_sign()
{
    return "\n" + 
"Register of the Soldiers of the Army of Angmar\n"+
"**********************************************\n\n"+
"Captain\n"+
"-------\n\n     "+AA_COUNCIL_OBJ->query_captain()+
"\n\n"+
"Lieutenants\n" +
"-----------\n\n     " + AA_COUNCIL_OBJ->query_lieutenant() +
"\n\n" +
"Master Sergeants\n"+
"----------------\n\n"+
make_string_from_list((AA_RANKS_OBJ->query_players_with_rank_no(5)) || (AA_RANKS_OBJ->query_players_with_rank_no(6))) +
"\n\n" +
"Sergeants\n"+
"---------\n\n"+
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(4)) + 
"\n\n"+
"Corporals\n"+
"---------\n\n"+
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(3)) +
"\n\n"+
"Lance Corporals\n"+  
"---------------\n\n"+
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(2)) +
"\n\n" +
"Standard Bearers\n"+ 
"----------------\n\n"+
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(1)) +
"\n\n" +
"Footmen\n" +
"-------\n\n" +
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(0)) +
"\n";
}