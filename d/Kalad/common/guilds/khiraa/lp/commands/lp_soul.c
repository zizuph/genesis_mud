/*
 * /d/Kalad/common/guilds/khiraa/lp/commands/lp_soul
 * Purpose    : Command soul for the Lichs of the Khiraa
 * Located    : 
 * Created By : Sarr 6.Apr.97
 * Modified By: 
 */


#pragma strict_types
inherit "/d/Kalad/common/guilds/khiraa/lp/commands/common_soul";
 
#define GOUGE_WAIT_TIME         4.0   
#define DIRECT_RESET_TIME       5.0
#define DIRECT_WAIT       "_direct_wait"

#include "/d/Kalad/defs.h" // Kalad defs
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h" // Guild specific defs

/* Global var to keep track of those who are waiting to gouge */
object *gougers = ({});


public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "LP of Khiraa"; }

public mapping
query_cmdlist()
{
    return ([
#include "lp_commands.h"
            ]);
}

/* Bring in the guild specials code */

#include "specials.h"

/* Bring in the guild emotes code */

#include "emotes.h"

/* The rest are the guild special commands     */
/* Not emotes, but not exactly specials either */

/* Sets the player's special guild lich name   */

public int
c_lset(string str)
{
    if(!str)
        return 0;
    TP->set_lich_name(str);
    write("Your lich name is now set to: "+str+"\n");
    return 1;
}

/* Spell listings */

public int
allowed(int level, string spell)
{
    int rec;
    switch(spell)
    {
        case "ltell":
        case "lcrow":
            rec = 1;
        break;
        case "lhealth":
        case "ltorment":
            rec = 2;
        break;
        case "ldark":
            rec = 3;
        break;
        case "lrot":
        case "linfra":
            rec = 4;
        break;
        case "lspectre":
            rec = 5;
        break;
        case "lcorpse":
            rec = 6;
        break;
        case "lalign":
            rec = 7;
        break;
        case "lclone":
            rec = 8;
        break;
        case "ldetect":
            rec = 9;
        break;
        case "linvis":
            rec = 10;
        break;
        case "lplague":
            rec = 11;
        break;
        case "lgateway":
            rec = 12;
        break;
        case "lspeed":
            rec = 13;
        break;
        case "lshield":
            rec = 14;
        break;
        case "lpain":
            rec = 15;
        break;
        case "lrespoi":
            rec = 16;
        break;
        case "lresdeath":
            rec = 17;
        break;
        case "lhands":
            rec = 18;
        break;
        case "lphantasm":
            rec = 19;
        break;
        case "lshadow":
            rec = 20;
        break;
        case "ltouch":
            rec = 21;
        break;
        case "lbone":
            rec = 22;
        break;
        case "ldrain":
            rec = 23;
        break;
        case "lterror":
            rec = 24;
        break;
        case "lbanshee":
        case "lraise":
            rec = 25;
        break;
        case "lprism":
            rec = 26;
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
        write("ltell - Tell afar to another being in the realms.\n");
        write("lcrow - Summon a crow.\n");
    }
    if(lvl > 1)
    {
        write("ltorment - Torment things.\n");
        write("lhealth - Fake the health of someone.\n");
    }
    if(lvl > 2)
        write("ldark - Create darkness.\n");
    if(lvl > 3)
        write("linfra - See in the dark.\n");
    if(lvl > 4)
    {
        write("lrot - Rot corpses.\n");
        write("lspectre - Summon a spectre.\n");
    }
    if(lvl > 5)
        write("lcorpse - Make a corpse speak.\n");
    if(lvl > 6)
        write("lalign - Discover the alignment of a creature.\n");
    if(lvl > 7)
        write("lclone - Create a clone of something.\n");
    if(lvl > 8)
        write("ldetect - Detect magic.\n");
    if(lvl > 9)
        write("linvis - Invisibility.\n");
    if(lvl > 10)
        write("lplague - Create a plague.\n");
    if(lvl > 11)
        write("lgateway - Create a gateway to home.\n");
    if(lvl > 12)
        write("lspeed - Unholy revenant speed.\n");
    if(lvl > 13)
        write("lshield - Create a shield around someone.\n");
    if(lvl > 14)
        write("lpain - Cause a creature to feel extra pain.\n");
    if(lvl > 15)
        write("lrespoi - Create a resist poison potion.\n");
    if(lvl > 16)
        write("lresdeath - Create a resist death potion.\n");
    if(lvl > 17)
        write("lhands - Hands of doom.\n");
    if(lvl > 18)
        write("lphantasm - Phantasmal creatures.\n");
    if(lvl > 19)
        write("lshadow - Summon shadow to defend you.\n");
    if(lvl > 20)
        write("ltouch - Ghoul touch.\n");
    if(lvl > 21)
        write("lbone - Create a bone shield.\n");
    if(lvl > 22)
        write("ldrain - Life drain.\n");
    if(lvl > 23)
        write("lterror - Create Terror and Madness.\n");
    if(lvl > 24)
    {
        write("lbanshee - Summon banshee wail.\n");
        write("lraise - Animate a corpse.\n");
    }
    if(lvl > 25)
        write("lprism - Create a prism shield.\n");
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


/* The help command */

public int
c_help(string str)
{
    string file, *slist;
    slist = ({"lcrow","ltell","lhealth","ldark","linfra","lspectre",
    "lcorpse","lalign","lclone","ldetect","linvis","lplague","lgateway",
    "lspeed","lshield","lpain","lrespoi","lresdeath","lhands","lshadow",
    "ltouch","lphantasm","lbone","ldrain","lterror","lbanshee","lraise",
    "lprism","lrot","ltorment" });

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
            file = read_file(KHIRAA_DIR(doc/help_lp_emotes));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa priests":
            file = read_file(KHIRAA_DIR(doc/help_all_lp));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa titles":       
            file = read_file(KHIRAA_DIR(doc/help_all_titles));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa":
            file = read_file(KHIRAA_DIR(doc/help_lp_help));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa knights":
            file = read_file(KHIRAA_DIR(doc/help_all_dk));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa info":
            file = read_file(KHIRAA_DIR(doc/help_all_khiraa));
            TP->more(file,0);
            return 1;
            break;
        case "khiraa specials":
            file = read_file(KHIRAA_DIR(doc/help_lp_specials));
            TP->more(file,0);
            return 1;
            break;
        default:
            return 0;
    }
    return 0;
}

