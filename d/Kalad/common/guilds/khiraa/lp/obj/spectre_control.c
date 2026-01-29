/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/spectre_control.c
 * Purpose    : This is the object moved into the caster of the spell 'lspectre'. It provids the link from the caster to its spying spectre.
 * Located    : From the spell 'lspectre'.
 * Created By : Sarr 12.Apr.97
 * Modified By: 
 */ 

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"


static 	object	link_player,
		link_monster;


void
set_remove_time(float i)
{
    set_alarm(i,0.0,"remove_object");
}


public void
create_object()
{
    set_name("_spectre_obj");
    set_no_show();
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_M_NO_DROP,1);
}

public void
set_master(object master,object target)
{
    link_player = master;

    if (!link_monster)
    {
        seteuid(getuid());
        link_monster = clone_object(LP_DIR+"obj/spectre_obj");
    }

    if(!objectp(target))
        target = E(master);
    link_monster->set_tell_active(1);
    link_monster->set_sp_master(master);
    link_monster->move(target);
    tell_room(target,"A "+link_monster->short()+" fades into view.\n",
    link_monster);
    set_this_player(master);
    link_monster->do_glance(0);
}

public void
link_intext(string str)
{

    if (link_player)
    {
	str = implode(explode(str, "\n"), "\n");
        link_player->catch_msg("**"+str+"\n");
    }
}

void
init()
{
    ::init();

    if(IS_LP(TP) || IS_GUILD_MASTER(TP))
    {
        add_action("all_cmd","",1);
    }
}

int
all_cmd(string str)
{
    int index;
    string cmd, exe;
    string *dircmds,*erooms;
    if(extract(query_verb(),0,0) != "*")
    {
        write("You're concentration is broken. You lose the spectre.\n");
        set_alarm(1.0,0.0,"remove_object");
    }
    else
    {
        if (!link_monster)
        {
    	    notify_fail("No spectre linked.\n");
	    destruct();
	    return 0;
        }
        dircmds = E(link_monster)->query_exit_cmds();
        erooms = E(link_monster)->query_exit_rooms();
        
        cmd = query_verb() + (str ? (" " + str) : "");
        exe = extract(cmd, 1);
 
        if(exe == "look")
        {
            write("*");
            link_monster->do_glance(0);
            write("*");
            return 1;
        }
        if(wildmatch("examine*",exe))
        {
            link_monster->command(cmd);
            return 1;
        }
        NF("You can only make your "+link_monster->short()+" walk around.\n");
        index = member_array(exe,dircmds);
        if(index == -1)
            return 0;
        NF("You cannot move your spectre in there, it is protected by "+
        "magical forces of immortal power.\n");
        if(erooms[index]->query_prop(ROOM_M_NO_MAGIC) ||
           erooms[index]->query_prop(ROOM_M_NO_TELEPORT) ||
           erooms[index]->query_prop(ROOM_M_NO_TELEPORT_TO) ||
           erooms[index]->query_prevent_snoop())
            return 0;        
        notify_fail("*What?\n");
        
        return link_monster->command(exe);
    }
    return 0;
}

void
remove_object()
{
    if(link_monster)
    {
        tell_object(link_player,"The power of the spell fades.\n");
        tell_room(E(link_monster),"The "+link_monster->short()+" fades away.\n");
        link_monster->remove_object();
    }
    ::remove_object();
}

