/*	Modified by Toby 971009 (I fixed a typo)   
 */


inherit "/std/guild/guild_race_sh";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#pragma strict_types
#pragma save_binary

/*
* Guild titles
*/

// Is the shadow initialized?
static int Initialized;

#define TITLES ({ "Grim Soldier of the Red Fang", \
      "Vicious Soldier of the Red Fang", \
      "Ferocious Soldier of the Red Fang", \
      "Fierce Soldier of the Red Fang", \
      "Grim Sergeant of the Red Fang", \
      "Vicious Sergeant of the Red Fang", \
      "Ferocious Sergeant of the Red Fang", \
      "Fierce Sergeant of the Red Fang", \
      "Grim Lieutenant of the Red Fang", \
      "Vicious Lieutenant of the Red Fang", \
      "Ferocious Lieutenant of the Red Fang", \
      "Fierce Lieutenant of the Red Fang", \
      "Grim Captain of the Red Fang", \
      "Vicious Captain of the Red Fang", \
      "Ferocious Captain of the Red Fang", \
      "Fierce Captain of the Red Fang", \
      "Ruthless Major of the Red Fang", \
      "Dreaded Lieutenant-Colonel of the Red Fang",\
      "Treacherous Colonel of the Red Fang", \
      "Merciless General of the Red Fang" })


#define SPECIAL_TITLE  "The Most Notorious Goblin in all of Kalad";
#define TRIBE_SUBLOC   "_kalad_tribe_subloc"

int ftoggle;

void
set_toggle(int i)
{
    mapping temp;
    string str,sc,st;
    if(i > 3)
        i = 3;
    if(i < 1)
        i = 1;
    ftoggle = i;
    seteuid(getuid());
    temp = restore_map("/d/Kalad/common/guilds/red_fang/doc/player_tribes");
    if(!m_sizeof(temp))
        temp = ([]);
    str = temp[shadow_who->query_real_name()];
    if(!stringp(str))
        return;
    sscanf(str,"%s|%s|%d",sc,st,i);
    temp += ([shadow_who->query_real_name():sc+"|"+st+"|"+ftoggle]);
    save_map(temp,"/d/Kalad/common/guilds/red_fang/doc/player_tribes");    
}

int
set_family(string clan, string tribe, int ft)
{
    mapping temp;
    seteuid(getuid());
    temp = restore_map("/d/Kalad/common/guilds/red_fang/doc/player_tribes");
    if(!m_sizeof(temp))
        temp = ([]);
    temp += ([shadow_who->query_real_name():clan+"|"+tribe+"|"+ft]);
    save_map(temp,"/d/Kalad/common/guilds/red_fang/doc/player_tribes");
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
    mapping temp;
    string str,st,sc,color;
    int i;
    seteuid(getuid());
    temp = restore_map(FANG_DIR(doc/player_tribes));
    str = temp[shadow_who->query_real_name()];
    if(!str)
        return ({});
    sscanf(str,"%s|%s|%d",sc,st,i);
    switch(st)
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
    return ({st,color});
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

void
do_die(object killer)
{
/* This was causing runtime errors
    tell_room(E(killer),QCTNAME(shadow_who)+" gets a fevered look "+
    "in "+HIS(shadow_who)+" eye.\n",shadow_who);
    tell_object(shadow_who,"You get a fevered look in your eye.\n");
    shadow_who->command("shout Red Fang forever!!!");
*/
    shadow_who->do_die(killer);
}

object
compare_stats(object ob1, object ob2)
{
    /* Returns the bigger stats of the two players */
    if (ob1->query_average_stat() >= ob2->query_average_stat())
        return ob1;
    return ob2;
}

object *
others_with_same_title()
{
   int stat,i;
   object *obs;
   object *obs2 = ({});
   obs = users();
   for(i=0;i<sizeof(obs);i++)
   {
      stat = obs[i]->query_fang_level();
   
      if (stat < 0)
         stat = 0;
   
      if(obs[i]->test_bit("Kalad",1,14))
         stat = stat +1;

      if (stat > sizeof(TITLES) -1)
         obs2 += ({obs[i]});
   }
   return obs2;
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
   mapping temp;
   int stat;
   object *obs,me;
   string str,bul,clan,tribe;
   int i;
   stat = query_fang_level();
   seteuid(getuid());
   temp = restore_map("/d/Kalad/common/guilds/red_fang/doc/player_tribes");
   
   bul = temp[shadow_who->query_real_name()];
   str = "";
   if(stringp(bul))
   {
      sscanf(bul,"%s|%s|%d",clan,tribe,ftoggle);
      switch(ftoggle)
      {
          case 1:
             str = clan+", ";
          break;
          case 2:
             str = "of the "+tribe+", ";
          break;
          case 3:
             str = clan+" of the "+tribe+", ";
          break;
          default:
             str = "bugged";
      }
   }
   if (stat < 0)
      stat = 0;
   
   
   if(shadow_who->test_bit("Kalad",1,14))
        stat = stat +1;

   if (stat > sizeof(TITLES) -1)
   {
      stat = sizeof(TITLES) -1;
      if(sizeof(obs = others_with_same_title()) )
      {
          for(i=0;i<sizeof(obs);i++)
          {
             if(compare_stats(shadow_who,obs[i]) != shadow_who)
                 return str+TITLES[stat];
          }
      }
      return str+SPECIAL_TITLE;
   }
      return str+TITLES[stat];
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

