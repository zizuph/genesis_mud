/*
 * Milan
 *
 *
 * Modification log:
 *
 *   2008.06.17, Toby: fixed with 'allow' and disallow to not show errors.
 *                     fixed 'list authorized' to be more neat.
 *   2008.07.03  Novo: removed buggy description check
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include "../guild.h"

inherit SHIRE_ROOM;

#define BOARD_NAME  (AA_DIR+"boards/aa_board_priv")
#define SAVE_FILE   (AA_DIR+"save_files/AA_PRIV")

private mapping authorized;
private mapping unauthorized;
static string *names;
static int alarm;

void
create_shire_room()
{
    object board;
    int i, j;
    string *arr;
    
    set_short("Private room");
    set_long("This is the room for members of Angmar's Army. "+
        "Here you can discuss guild matters in privacy or leave a "+
        "message for other members. To the north is the big court "+
        "room while east is the entrance to the small store room. "+
        "Next to the entrance hangs a simple sign. To the south you "+
        "see yet another store room. It is a bit smaller than eastern "+
        "one and there is no sign hanging next to the entrance.\n");
    
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    
    add_exit(AA_DIR+"rooms/vote", "north");
    add_exit(AA_DIR+"rooms/train", "west");
    add_exit(AA_DIR+"rooms/store2", "south");
    add_exit(AA_DIR+"rooms/store", "east","@@block_exit");
    
    add_item(({"sign","simple sign"}), "A simple sign with writing on it.\n");
    add_item("writing", "Can you read it?\n");
    add_cmd_item(({"sign","simple sign","writing"}), "read", "\n"+
        "            AUTHORIZED PERSONNEL ONLY!!!\n\n"+
        "  Unauthorized persons will be cooked and served as dinner!\n\n"+
        "  Soldiers can:\n"+
        "       'list authorized'\n"+
        "       'list removed authorizations'\n"+
        "       'who is <short desc>'\n"+
        "  Captain, lieutenants and council members can:\n"+
        "       'allow entry to <name>'\n"+
        "       'disallow entry to <name>'\n\n"+
        "                            Emissary of the Dark Lord\n\n");
    
    FIXEUID;
    board = clone_object("/d/Shire/std/board");
    board->set_board_name(BOARD_NAME);
    board->set_num_notes(100);
    board->move(TO);
    
    authorized = ([ ]);
    unauthorized = ([ ]);
    restore_object(SAVE_FILE);
    names = m_indexes(authorized);
    for(i=0; i<sizeof(names); i++)
        if(!AA_RANKS_OBJ->aa_member(names[i]))
            authorized = m_delete(authorized, names[i]);
    names = m_indexes(authorized);
    sort_array(names);
    arr = m_indexes(unauthorized);
    for(i=0; i<sizeof(arr); i++)
    {
        for(j=0; j<sizeof(unauthorized[arr[i]]); j++)
            if(!(AA_RANKS_OBJ->aa_member(unauthorized[arr[i]][j])))
                unauthorized[arr[i]] -= ({ unauthorized[arr[i]][j] });
        if(!sizeof(unauthorized[arr[i]]))
            unauthorized = m_delete(unauthorized, arr[i]);
        else
            sort_array(unauthorized[arr[i]]);
    }
    save_object(SAVE_FILE);
}

string get_desc(string name)
{
    object ob = "/secure/master"->finger_player(LOW(name));
    string str = ob->query_nonmet_name();
    ob->remove_object();
    return str;
}

int block_exit()
{
    string name = TP->query_name();
    
    string desc = TP->query_nonmet_name();
    
    if ((name == "Milan") || (name == "Guild_cleaner")) return 0;
    if(member_array(name, names) != -1)
    {
        //if (desc != authorized[name])
        //{
        //    write("Your description doesn't match our record. "+
        //        "Authorisation removed.\n");
        //    authorized = m_delete(authorized, name);
        //    names = m_indexes(authorized);
        //    sort_array(names);
        //    FIXEUID;
        //    save_object(SAVE_FILE);
        //    return 1;
        //}
        return 0;
    }
    write("You decided that you do not want to be cooked and served as "+
        "a dinner after all.\n");
    return 1;
}

void init()
{
    ::init();
    add_action("allow","allow");
    add_action("disallow","disallow");
    add_action("list","list");
    add_action("who","who");
}

int allow(string str)
{
    string name, desc, *arr;
    int i;

    if(!str)
    {
        NF("Allow who what? Try 'allow entry to [who]'\n");
        return 0;
    }
   
    arr = explode(str, " ");

    if((sizeof(arr) != 3) || (arr[0] != "entry") || (arr[1] != "to"))
    {
        NF("Allow who what? Try 'allow entry to [who]'\n");
        return 0;
    }

    name = CAP(arr[2]);
    if(!(AA_RANKS_OBJ->aa_member(name)))
    {
        write(name+" is not a member of the army.\n");
        return 1;
    }
    if(!AA_RANKS_OBJ->lieut_cap(TP->query_name()) &&
        !AA_COUNCIL_OBJ->is_council(TP->query_name()))
    {
        write("Only Lieutenants and Council members can do that!\n");
        return 1;
    }
    if(member_array(name, names) != -1)
    {
        write(name+" is already authorized to enter store room.\n");
        return 1;
    }
    desc = TP->query_real_name();
    authorized += ([ name:desc ]);
    names = m_indexes(authorized);
    sort_array(names);
    arr = m_indexes(unauthorized);
    for(i=0; i<sizeof(arr); i++)
        if(member_array(name, unauthorized[arr[i]]) != -1)
        {
            unauthorized[arr[i]] -= ({ name });
            if(!sizeof(unauthorized[arr[i]]))
                unauthorized = m_delete(unauthorized, arr[i]);
        }
    FIXEUID;
    save_object(SAVE_FILE);
    write("You authorize "+name+" to enter the store room.\n");
    return 1;
}

int disallow(string str)
{
    string name, *arr;

    if(!str)
    {
        NF("Disallow who? Read the sign stupid!\n");
        return 0;
    }
        
    arr = explode(str, " ");

    if((sizeof(arr) != 3) || (arr[0] != "entry") || (arr[1] != "to"))
    {
        NF("Disallow who, how? Read the sign stupid!\n");
        return 0;
    }

    name = CAP(arr[2]);
    if(member_array(name, names) == -1)
    {
        write(name+" is not authorized to enter the store room.\n");
        return 1;
    }
    if(!AA_RANKS_OBJ->lieut_cap(TP->query_name()) &&
        !AA_COUNCIL_OBJ->is_council(TP->query_name()))
    {
        write("Only Lieutenants and Council members can do that!\n");
        return 1;
    }
    
    authorized = m_delete(authorized, name);
    names = m_indexes(authorized);
    sort_array(names);
    if(member_array(TP->query_name(), m_indexes(unauthorized)) == -1)
    {
        unauthorized += ([ TP->query_name():({ name }) ]);
    }
    else
    {
        unauthorized[TP->query_name()] += ({ name });
        sort_array(unauthorized[TP->query_name()]);
    }
    FIXEUID;
    save_object(SAVE_FILE);
    write("You remove authorization of "+name+" to enter store room.\n");
    return 1;
}

int list(string str)
{
    int i;
    string *arr;
    
    if(str == "authorized")
    {
        arr = m_indexes(authorized);
        if(!sizeof(arr))
            write("No one has been authorized yet!\n");
        else
            write("List of authorized personnel:\n\n"+implode(names, ", ")+"\n");
        return 1;
    }
    if(str == "removed authorizations")
    {
        arr = m_indexes(unauthorized);
        if(!sizeof(arr)){ write("No one has removed any authorization.\n"); }
        else for(i=0; i<sizeof(arr); i++)
            write(arr[i]+" removed authorization of: "+
            implode(unauthorized[arr[i]], ", ")+"\n");
        return 1;
    }
    NF("List what?\n");
    return 0;
}

int who(string str)
{
    string desc, *arr = ({ });
    int i;
    
    if (!str || !sscanf(str, "is %s", desc))
    {
        NF("Who what?\n");
        return 0;
    }
    
    for (i=0; i<sizeof(names); i++)
        if (authorized[names[i]] == desc)
            arr += ({ names[i] });
    if (!sizeof(arr))
    {
        write("There is no soldier with description '"+desc+
            "' authorized to enter the store room.\n");
        return 1;
    }
    write("Soldiers authorized into the store room with description '"+desc+
        "' are: "+implode(arr, ", ")+".\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!alarm && !living(ob))
        alarm = set_alarm(20.0, 0.0, "tidy_room");
    
    if(!living(ob) || ob->query_wiz_level() || 
        IS_MEMBER(ob) || ob->query_npc())
        return;
    
    ob->command("look");
    ob->catch_msg("A bunch of warriors come screaming at you!\n"+
        "They grab you and throw you out of their private room.\n");
    tell_room(AA_DIR+"rooms/train", QCTNAME(ob)+" comes flying from the east and "+
        "lands in one heap on the floor.\n");
    ob->move(AA_DIR+"rooms/train");
    tell_room(TO, QCNAME(ob)+" arrives.\n"+
        "A bunch of warriors come screaming at "+QTNAME(ob)+"!\n"+
        "They grab "+HIM(ob)+" and throw "+HIM(ob)+" out.\n");
}

private void
tidy_room()
{
    object cleaner;
    
    alarm = 0;
    FIXEUID;
    cleaner = clone_object("/std/monster");
    cleaner->set_name("guild_cleaner");
    cleaner->set_base_stat(SS_STR, 350);
    cleaner->set_base_stat(SS_DEX, 10);
    cleaner->set_base_stat(SS_CON, 150);
    cleaner->set_base_stat(SS_WIS, 10);
    cleaner->set_base_stat(SS_INT, 10);
    cleaner->set_base_stat(SS_DIS, 30);
    cleaner->set_pname("trolls");
    cleaner->set_race_name("troll");
    cleaner->set_adj(({"huge", "clumsy"}));
    cleaner->set_short("huge clumsy troll");
    cleaner->add_prop(LIVE_I_NEVERKNOWN, 1);
    cleaner->move(TO, 1);
    tell_room(TO, QCNAME(cleaner)+" arrives.\n");
    cleaner->command("get all");
    cleaner->command("sigh");
    cleaner->command("e");
    cleaner->command("drop all");
    cleaner->command("w");
    cleaner->command("say I have my orders... Keep this place tidy!");
    tell_room(TO, QCNAME(cleaner)+" leaves.\n");
    cleaner->remove_object();
}
