/* vamps.c created by Shiva@Genesis
 * This file contains the code for the "vamps" command
 * This file is part of the vampire guild soul
 */

/* Description
 * -----------
 * This is a guild "who list".
 */

#include "../guild.h"
#include <macros.h>
#include <std.h>

int order_members(object a, object b);

int
filter_vamps(object who)
{
    string coven;

    if (!who->query_vampire() && !who->query_bloodguard())
    {
        return 0;
    }

    if (who == TP)
    {
        return 1;
    }

    /* Wizards see everyone */
    if (TP->query_wiz_level())
    {
        return 1;
    }

    /* Wizards are not shown unless they possess a special prop
     * and are visible
     */
    if (who->query_wiz_level() &&
        (!who->query_prop("_wiz_i_shown_on_vamp_list") ||
        who->query_invis()))
    {
        return 0;
    }

    /* Jr's are not shown */
    if (extract(who->query_real_name(), -2) == "jr")
    {
        return 0;
    }

    return 1;
}

int vamps(string str)
{
    string name, title, vtitle, str1, str2, list, coven;
    int i, size, cnt = 0, full_title;
    object *vampires;
  
    if (IS_BG(TP) && !TP->query_master())
    {
        return 0;
    }
    
    if ((TP->query_blood() < 20) && (!IS_WIZ(TP)))
    {
        write("Your powers have weakened far too much.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());
  
    full_title = (TP->query_vamp_covenmaster() || 
        (OCC_MANAGER->query_ptitles_shown()));

    vampires = sort_array(filter(users(), filter_vamps), order_members);
  
    list = "You sense the presence of:\n";
  
    size = sizeof(vampires);
    i = -1;
    while (++i < size)
    {
        str1 = "";
        str2 = "";
    
        str1 = SECURITY->query_wiz_pretitle(vampires[i]);
    
        if (strlen(name = vampires[i]->query_name()))
        {
            if (vampires[i]->query_invis())
            {
                name = "(" + name + ")";
            }
      
            str1 += (strlen(str1) ? " " + name : name);
        }
        else
        {
            continue;
        }

        /*    
        if (strlen(title = vampires[i]->query_title()))
        {
            str1 += (strlen(str1) ? " " + title : capitalize(title));
        }
        */

        if (full_title)
		{    
            vtitle = vampires[i]->query_full_vamp_title();
        }
        else
		{
		    vtitle = vampires[i]->query_vamp_title();
		}

        if (strlen(vtitle))
		{
		    if (strlen(title))
				{
                    vtitle = ", " + vtitle;
				}
                else if (strlen(str1))
				{ 
                    vtitle = " " + vtitle;
				}
                else
				{      
                    vtitle = capitalize(vtitle);
				}
      
            str1 += vtitle;
        }
    
        if (IS_WIZ(TP))
        {
            str2 = "(" + (IS_WIZ(vampires[i]) ? "wiz" :
                vampires[i]->query_vamp_stat()) + ")";
        }
    
        cnt++;
        list += sprintf("- %=-68s %-5s\n", str1, str2);
    }
  
    list += "======================================================="+
            "======================\n";
    list += "Total number of active members is " + cnt + ".\n";
  
    if (FCHAR(query_verb()) == "m")
    {
        setuid();
        seteuid(getuid());
        TP->more(list);
    }
    else
    {
        write(list);
    }
  
    return 1;
}

int order_members(object a, object b)
{
    int aocc, bocc, agen, bgen;

    if (a->query_vamp_covenmaster())
    {
        if (b->query_vamp_covenmaster())
        {
            return 0;
        }

        return -1;
    }

    if (b->query_vamp_covenmaster())
    {
        return 1;
    }

    if (a->query_bloodguard() && !b->query_bloodguard())
    {
        return 1;
    }        

    if (!a->query_bloodguard() && b->query_bloodguard())
    {
        return -1;
    }        


    aocc = a->query_vamp_stat();
    bocc = b->query_vamp_stat();
    agen = a->query_vamp_generation();
    bgen = b->query_vamp_generation();
  
    if (agen == bgen)
    {
        return (aocc < bocc ? 1 : (aocc == bocc ? 0 : -1));
    }

    return ((agen < bgen) ? -1 : 1);
}
