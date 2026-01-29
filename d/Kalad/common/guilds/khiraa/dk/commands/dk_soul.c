/*
 * /d/Kalad/common/guilds/khiraa/dk/commands/dk_soul
 * Purpose    : Command soul for the Death Knights of the Khiraa
 * Located    : 
 * Created By : Sarr 6.Mar.97
 * Modified By: 
 */


#pragma strict_types
/* commands both common to lichs and knights */
inherit "/d/Kalad/common/guilds/khiraa/lp/commands/common_soul";
 
#define WHIRLWIND_WAIT_TIME     4.0   /* Rounds */
#define BASH_WAIT_TIME          8.0   /* Rounds */

#include "/d/Kalad/defs.h" // Kalad defs
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h" // Guild specific defs

/* Global array of people waiting to whirl again */
/* Will remove if soul is updated */
object *whirlers = ({});
/* Like above, for bashstun */
object *bashers = ({});

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "DK of Khiraa"; }

public mapping
query_cmdlist()
{
    return ([
#include "dk_commands.h"
            ]);
}

/* Bring in the guild specials code */

#include "specials.h"

/* Bring in the guild emotes code */

#include "emotes.h"

/* The rest are the guild special commands     */
/* Not emotes, but not exactly specials either */

public int
allowed(int level, string spell)
{
    int rec;
    switch(spell)
    {
        case "ktell":
        case "kcrow":
            rec = 1;
        break;
        case "ktorment":
            rec = 2;
        break;
        case "kinfra":
            rec = 3;
        break;
        case "kdark":
            rec = 4;
        break;
        case "kfoul":
            rec = 5;
        break;
        case "kfear":
            rec = 6;
        break;
        case "kflame":
            rec = 7;
        break;
        case "kblade":
            rec = 8;
        break;
        case "karmour":
            rec = 9;
        break;
        case "kbones":
            rec = 10;
        break;
        default:
            rec = 30;
    }
    if(level < rec)
        return 0;
    return 1;
}

public void
print_spells(object me)
{
    int lvl;
    set_this_player(me);

    lvl = me->query_guild_order();

    write("You have been granted the following prayers by the "+
    "Unspeakable Horror whom you worship -\n");
    if(lvl > 0)    
    {
        write("ktell - Tell afar to another khiraa in the realms.\n");
        write("kcrow - Summon a crow.\n");
    }
    if(lvl > 1)
    {
        write("ktorment - Torment things.\n");
    }
    if(lvl > 2)
        write("kinfra - See in the dark.\n");
    if(lvl > 3)
        write("kdark - Create darkness.\n");
    if(lvl > 4)
    {
        write("kfoul - Create foulness.\n");
    }
    if(lvl > 5)
        write("kfear - Create an aura of fear.\n");
    if(lvl > 6)
        write("kflame - Create an arrow of flame.\n");
    if(lvl > 7)
        write("kblade - Enchant a weapon.\n");
    if(lvl > 8)
        write("karmour - Enchant an armour.\n");
    if(lvl > 9)
        write("kbones - Create a bone shield.\n");

    write("You can get help on each spell with help khiraa <spell>.\n");
}

void
print_this_spell(object me, string spell)
{
    string file;
    setuid();
    seteuid(getuid());

    file = read_file("/d/Kalad/common/guilds/khiraa/doc/spells/"+spell);
    if(!stringp(file))
        tell_object(me,"There is no listing for this spell. Contact "+
        "the guild master.\n");
    else
    {
        if( allowed(me->query_guild_order(),spell) )
            me->more(file,0);
        else
            tell_object(me,"You are not allowed info on that prayer.\n");
    }
}


public int
c_help(string str)
{
    string file, *slist;
    slist = ({"ktell","ktorment","kinfra","kflame","kfoul","kdark",
    "kfear","kbones","kcrow","karmour","kblade" });

    NF("Help what?\n");
    if(!str)
        return 0;
    setuid();
    seteuid(getuid());
    if(member_array(extract(str,7),slist) != -1)
    {
        print_this_spell(TP,extract(str,7));
        return 1;
    }
    switch(str)
    {
        case "khiraa spells":
            print_spells(TP);
            return 1;
            break;
        case "khiraa emotes":
            file = read_file(KHIRAA_DIR(doc/help_dk_emotes));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa":
            file = read_file(KHIRAA_DIR(doc/help_dk_help));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa knights":
            file = read_file(KHIRAA_DIR(doc/help_all_dk));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa titles":
            file = read_file(KHIRAA_DIR(doc/help_all_titles));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa info":
            file = read_file(KHIRAA_DIR(doc/help_all_khiraa));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa specials":
            file = read_file(KHIRAA_DIR(doc/help_dk_specials));
            TP->more(file,0);
            return 1;
            break;
        default:
            return 0;
    }
    return 0;
}

