inherit "/std/guild/guild_race_sh";
#include <formulas.h>
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#pragma strict_types
#pragma save_binary

/*
 * Guild titles
 */

// Is the shadow initialized?
static int Initialized;

static string *titles = ({ "Grim Soldier of the Red Fang", 
            "Vicious Soldier of the Red Fang", 
            "Ferocious Soldier of the Red Fang", 
            "Fierce Soldier of the Red Fang", 
            "Grim Sergeant of the Red Fang",
            "Vicious Sergeant of the Red Fang", 
            "Ferocious Sergeant of the Red Fang", 
            "Fierce Sergeant of the Red Fang", 
            "Grim Lieutenant of the Red Fang", 
            "Vicious Lieutenant of the Red Fang", 
            "Ferocious Lieutenant of the Red Fang", 
            "Fierce Lieutenant of the Red Fang", 
            "Grim Captain of the Red Fang", 
            "Vicious Captain of the Red Fang", 
            "Ferocious Captain of the Red Fang", 
            "Fierce Captain of the Red Fang", 
            "Ruthless Major of the Red Fang", 
            "Dreaded Lieutenant-Colonel of the Red Fang",
            "Treacherous Colonel of the Red Fang", 
            "Merciless General of the Red Fang" });


#define SPECIAL_TITLE  "The Most Notorious Goblin in all of Kalad";
#define TRIBE_SUBLOC   "_kalad_tribe_subloc"

void
set_toggle(int i)
{
    MEMBERS->set_toggle(shadow_who->query_real_name(), i);
}

int
set_family(string clan, string tribe, int ft)
{
    MEMBERS->set_data(shadow_who->query_real_name(), clan, tribe, ft);
    return 1;
}


int 
roundo(float i)
{
    int t;
    float a;
    t = ftoi(i);
    a = i - itof(t);
    if(a >= 0.5)
        return (t + 1);
    else
        return t;
}

mixed *
get_tribe_info()
{
    string tribe, color;

    tribe = MEMBERS->query_tribe(shadow_who->query_real_name());

    if (!tribe)
        return ({ });

    switch(tribe)
    {
    case "Red Hand":
        color = "red";
        break;
    case "Black Tooth":
        color = "black and white";
        break;
    case "Iron Rock":
        color = "black and green";
        break;
    case "Bone Smasher":
        color = "black and red";
        break;
    case "Bloody Fist":
        color = "black and yellow";
        break;
    case "Black Blade":
        color = "black and silver";
        break;
    case "Grinning Skull":
        color = "brown and white";
        break;
    default:
        color = "bugged";
    }
    return ({ tribe, color });
}


string
show_subloc(string subloc, object on, object for_ob)
{
    string str,*info,tribe,color;

    if (subloc != TRIBE_SUBLOC)
    {
        return shadow_who->show_subloc(subloc, on, for_ob);
    }

    if(shadow_who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    info = get_tribe_info();
    if(!sizeof(info))
        return "";
    tribe = info[0];
    color = info[1];
    if(on == for_ob)
        return "Your "+color+" war paint marks you as a Kaladian "+
            "goblin of the "+tribe+" tribe.\n";
    return "Judging from "+HIS(on)+" "+color+" war paint, you "+
        "can tell "+HE(on)+" is a Kaladian goblin of the "+tribe+" "+
        "tribe.\n";
}



/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */

int
query_guild_tax_race()
{
    return TAX; /* Whatever you wish to set it to. */
}

public mixed 
query_guild_trainer_race()
{
    return ({"/d/Kalad/common/guilds/red_fang/rooms/train"});
}

void
fang_init(object ob)
{
    setuid();
    seteuid(getuid());
    
    ob->add_cmdsoul(FANG_SOUL);
    ob->update_hooks();
    setuid();
    seteuid(getuid());
    if(ob->test_bit("Kalad",1,14))
        clone_object(FANG_DIR(obj/fh_badge))->move(ob);
    else
        clone_object(FANG_DIR(obj/f_badge))->move(ob);
    if(sizeof(get_tribe_info()))
        ob->add_subloc(TRIBE_SUBLOC,TO);
}
    
void
fang_dispell(object ob)
{
    tell_object(ob,"You have betrayed the Red Fang by changing your "+
        "race!\n");
    ob->set_m_in(F_ALIVE_MSGIN);
    ob->set_m_in(F_ALIVE_MSGOUT);
    remove_guild_race();
}

int
query_guild_keep_player(object ob)
{
    if (!Initialized)
    {
        Initialized = 1;
        if(ob->query_race_name() != "goblin")
            set_alarm(2.0,0.0,&fang_dispell(ob));
        else
            set_alarm(2.0,0.0,&fang_init(ob));
    }
    return 1;
}

/* Function name: query_fang_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */

int
query_fang_level()
{
    return roundo( (itof(shadow_who->query_base_stat(SS_RACE)) / 5.2) );
}

/* Function name: query_guild_title_race
 * Description:   We change the title of our members depending on their level
 * Returns:       The title
 */
int
query_guild_family_name()
{
    return 1;
}

string 
query_guild_title_race()
{
    string name, clan, tribe, str = "";
    int stat;

    name = shadow_who->query_real_name();
    
    if (clan = MEMBERS->query_clan(name))
    {
        tribe = MEMBERS->query_tribe(name);
        
        switch (MEMBERS->query_toggle(name))
        {
        case 1:
            str = clan+ ", ";
            break;
        case 2:
            str = "of the " + tribe+ ", ";
            break;
        case 3:
            str = clan + " of the " + tribe+", ";
            break;
        default:
            str = "bugged";
        }
    }

    stat = query_fang_level();
    if (stat < 0)
        stat = 0;   
    
    if (shadow_who->test_bit("Kalad",1,14))
        stat = stat + 1;

    if (stat < sizeof(titles))
    {
        return str + titles[stat];
    }
    
    /* The member with the highest stat average and max title gets the special
     * title */
    foreach (object user: users())
    {
        int level;
        level = user->query_fang_level();
        if (user->test_bit("Kalad", 1, 14))
            level += 1;

        if ((level < sizeof(titles)) || user->query_average_stat() < shadow_who->query_average_stat())
            continue;
        /* Other bigger gobbo in */
        return str + titles[sizeof(titles) - 1];
        
    }
    
    return str + SPECIAL_TITLE;
}


/*
 * Function name: query_guild_style_race
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */

string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_race
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
string
query_guild_name_race()
{
    return GUILD_NAME;
}

int
list()
{
    string str;
   
    str = TP->list_major_guilds();
    if (str)
        write("You are member of following guilds.\n" + str);
    else
        write("You are not member of any guilds.\n");
   
    return 1;
}

public mixed
query_guild_skill_name(int type)
{
    if(type == SS_WOLF_RIDING)
        return "wolf riding";
}

