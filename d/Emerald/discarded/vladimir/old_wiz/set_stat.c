/* 
 * Stat setter
 *
 * This tool allows you to set your stats until you logout (or reset)
 *
 *
 */

inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>

#ifndef CHECK_SO_WIZ
#define CHECK_SO_WIZ  if (!this_player()->query_wiz_level()) return 0
#endif

create_object()
{
    set_short("set stat object");
    set_name(({"stat object", "stat", "object", "set_stat", "set_stats"}));
    set_long("This stat object lets you set_stats to a value\n" +
             "Your stats should be restored when you next log in.\n");
    add_prop(OBJ_M_NO_DROP, "You decide not to let the mortals " +
             "get their grubby little hands on this!\n");
}

query_auto_load()
{
    return MASTER;
}

init()
{
    ::init();

    CHECK_SO_WIZ;
    add_action("set_stat", "set_stat");
    add_action("set_stat", "set_stats");
}

/*
 * Function Name: to_lower(string)
 * Arguments:     String to change case
 * Description:   Makes <string> lower case
 * Returns:       The lower case version of <string> 
 */
to_lower(string old)
{
    string new;
    int i;
    
    new = old;
    for (i=0; i<strlen(old); i++)  {
        if (old[i]>='A' && old[i]<='Z')
            new[i] -= 'A' - 'a';
    }
    return new;
}

/*
 * Function Name: set_stat
 * Arguments:     Player's command string
 * Description:   Player Command
 */
set_stat(string str)
{
    int val, i;
    string *s;

    CHECK_SO_WIZ;
    if (!str)  {
        notify_fail("Usage:  set_stat [s[s[...]]] n\n" + 
                    "        s starts at 0 or use abbrieviated strings\n");
        return 0;
    }

    str = to_lower(str);
    s = explode(str, " ");
    if (s[0] == "all")  {
        s[0] = "";
        str = implode(s, " ");
        return set_stat(str[1..strlen(str)]);
    }
    if (sizeof(s) == 1)  {
        val = atoi(str);
        for (i=0; i<6; ++i)
            this_player()->set_base_stat(i, val);
        this_player()->catch_msg("All stats set to : " + val + "\n");
    }
    else  {
        write("Changed stats: ");
        val = atoi(s[sizeof(s)-1]);  /* Last arg */
        for (i=0; i<sizeof(s)-1; ++i)  {
          if (i!=0) 
              write(", ");
          switch (s[i])  {
            case "str" : case "ss_str" : case "0" :
                write("str("+this_player()->query_base_stat(0)+")");
                this_player()->set_base_stat(0, val);
                break;
            case "dex" : case "ss_dex" : case "1" :
                write("dex("+this_player()->query_base_stat(1)+")");
                this_player()->set_base_stat(1, val);
                break;
            case "con" : case "ss_con" : case "2" :
                write("con("+this_player()->query_base_stat(2)+")");
                this_player()->set_base_stat(2, val);
                break;
            case "int" : case "ss_int" : case "3" :
                write("int("+this_player()->query_base_stat(3)+")");
                this_player()->set_base_stat(3, val);
                break;
            case "wis" : case "ss_wis" : case "4" :
                write("wis("+this_player()->query_base_stat(4)+")");
                this_player()->set_base_stat(4, val);
                break;
            case "dis" : case "ss_dis" : case "5" :
                write("dis("+this_player()->query_base_stat(5)+")");
                this_player()->set_base_stat(5, val);
                break;
            default :
                write("Unknown stat: " + s[i] + "\n");
                break;
          }
        }
        write(" to " + val + "\n");
    }
    return 1;
}

