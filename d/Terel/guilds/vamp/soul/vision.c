/* 
 * vision
 *
 * This provides the vision ability.
 *
 */

#include "../guild.h"
#include <macros.h>

inherit "/lib/commands";


public int 
create_vision(string txt,object player,string name)
{
    if (!strlen(txt))
    {
        player->catch_msg("Aborted.\n");
	    return 0;
    }

    object manager=find_object(LIB_DIR+"vision_manager");
    
    if (manager->query_vision_exists(TP,name))
    {
        if (manager->update_vision(TP,name,txt))
        {
            write("Vision updated.\n");
            return 1;
        }
    }
    else
    {
        if (manager->add_vision(TP,name,txt))
        {
            write("Vision added.\n");
            return 1;
        }
    }
    player->catch_msg("You failed to add your vision.\n");
}


public int vision(string str)
{
    setuid();
    seteuid(getuid());
    LOAD_ERR(LIB_DIR+"vision_manager");
    
    object manager=find_object(LIB_DIR+"vision_manager");
    
    if (!manager)
    {
        return 0;
    }
    
    notify_fail("Usage: vvision  add     <name>\n" +
                "                remove  <name>\n" +
                "                update  <name>\n" +
                "                list    \n" +
                "                play   <name>\n" +
                "                stop\n");

    if (!strlen(str))
    {
        return 0;
    }
    
    string cmd;
    string name;
    
    if (!parse_command(str,({}),"%w %w",cmd,name) &&
        !parse_command(str,({}),"%w",cmd))
    {
        return 0;
    }
    
    switch (cmd)
    {
        case "list":
            string * visions=manager->get_all_visions(TP);
            
            if (visions && sizeof(visions))
            {
                string str = implode(visions, "\n");
                write("You have these visions to present:\n");
                write(sprintf("%-#60s\n", str));
                return 1;
            }
            write("You have no visions defined.\n");
            return 1;
        case "remove":
            if (manager->remove_vision(TP,name))
            {
                write("You have forgotten the "+name+" vision.\n");
                return 1;
            }
            write("No such vision.\n");
            return 1;
        case "add":
            if (!strlen(name))
            {
                write("You must name your vision.\n");
                return 1;
            }
            if (manager->query_vision_exists(TP,name))
            {
                write("You already have a vision named '"+name+"'.\n");
                return 1;
            }
            setuid();
            seteuid(getuid());
            write("Write your vision from your own perspective:\n");
            write("To create a pause, add two blank lines.\n");
            clone_object("/obj/edit")->edit(&create_vision(,TP,name));
            return 1;
        case "update":
            if (!strlen(name))
            {
                write("You must name your vision.\n");
                return 1;
            }
            if (!manager->query_vision_exists(TP,name))
            {
                write("You do not have a vision named '"+name+"'.\n");
                return 1;
            }
            setuid();
            seteuid(getuid());
            write("Write your vision from your own perspective:\n");
            write("To create a pause, add two blank lines.\n");
            clone_object("/obj/edit")->edit(&create_vision(,TP,name));
            return 1;
        case "play":
            if (!strlen(name))
            {
                write("You must select a vision to play.\n");
                return 1;
            }
            if (!manager->query_vision_exists(TP,name))
            {
                write("You do not have a vision named '"+name+"'.\n");
                return 1;
            }
            if (TP->query_active_vision())
            {
                write("You are already recalling a vision.\n");
                return 1;
            }
            string vision_text=manager->query_vision(TP,name);
            if (TP->query_vamp_drain())
            {
                write("As you think back to moments past, your thoughts "+
                "pass along to your prey.\n");
            }
            else
            {
                write("You think back to moments past, and are lost in "+
                "thought.\n");
                allbb(" looks lost in thought.");
            }
            TP->play_vision(explode(vision_text,"\n\n"));
            return 1;
        case "stop":
            if (!TP->query_active_vision())
            {
                write("You are not recalling a vision.\n");
                return 1;
            }
            TP->stop_vision();
            write("Your thoughts turn back to the present.\n");
            return 1;
        default:
            return 0;
    }
}

