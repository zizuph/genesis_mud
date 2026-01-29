inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/dark_alliance/default.h"
#include <tasks.h>

static int worn;

void
create_object()
{
   ::create_object();
   set_name("_rider_");
   add_name("collar");
   set_short("@@query_rank@@");
   set_long("This is your collar, it shows you are a "+
   "Rider of the Dark Alliance. Wear it Proudly!\n");
   add_prop(OBJ_I_WEIGHT,400);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_M_NO_DROP,"You cannot be rid of this unless you leave "+
   "the Dark Alliance, do <dahelp> for guild info.\n");
   add_prop(OBJ_M_NO_SELL,"You dare not sell your Rider collar!.\n");
   set_alarm(3.0,0.0,"message");
}


int
wear(string arg)
{
  object collar;
  NF("Wear what?\n");
  parse_command("wear "+arg,TP,"'wear' %o",collar);
  if(!collar)
      return 0;
  if(collar != TO)
      return 0;
  NF("But you already wear it!\n");
  if(worn) 
      return 0;
  write("You wear "+short()+" around your neck.\n");
  say(QCTNAME(TP)+" wears "+short()+" around "+HIS(TP)+" neck.\n");
  worn = 1;
  TP->add_subloc(file_name(TO), TO);
  set_no_show_composite(1);
  return 1;
}

int
remove(string arg)
{
  NF("Remove what?\n");
  if(!parse_command(arg, TP, " %o ")) return 0;
  NF("First you must have it!\n");
  if(E(TO) != TP) return 0;
  NF("But you don't wear it!\n");
  if(!worn) return 0;
  write("You remove the "+short()+" from your neck.\n");
  say(QCTNAME(TP)+" removes a "+short()+" from "+HIS(TP)+" neck.\n");
  worn = 0;
  TP->remove_subloc(file_name(TO));
  set_no_show_composite(1);
  return 1;
}

string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != file_name(TO))
      return "";

    if (for_obj != on)
      return capitalize(HE(on))+" is wearing "+short()+" around "+HIS(on)+
    " neck.\n";
    else
      return "You are wearing "+short()+" around your neck.\n";
}

string 
query_auto_load() 
{
  return MASTER+":"; 
}

void
message()
{
    write("Hail Rider of the Dark Alliance! Destroy the Thanar!\n");
   return;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    to->catch_msg("Guild is down until further notice.\n");
    remove_object();
    if (to->query_wiz_level())
        return;
    if(to->query_race_name() == "human")
    {
        to->catch_msg("Your collar is blown up as you have betrayed the "+
                      "Dark Alliance by changing your race to human!\n");
        to->remove_guild_race();
        to->clear_bit(4,8);
        to->clear_guild_stat(SS_LAYMAN);
        to->update_hooks();
        remove_object();
    }
}

void
init()
{
   ::init();
   AA(dahelp,dahelp);
   AA(rtitles,rtitles);
   AA(daemotes,daemotes);
   AA(dahistory,dahistory);
   AA(wear,wear);
   AA(rsummon,rsummon);
   AA(remove,remove);
}

void
get_me_soul(object ob)
{
   int i;
   string *souls;
   
   seteuid(getuid());
   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
   ob->remove_cmdsoul(souls[i]);
   
   ob->add_cmdsoul(RIDER_SOUL);
   
   for(i = 0; i < sizeof(souls); i++)
   if(souls[i] != RIDER_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}

int
rsummon()
{
    write("You whistle for a weasel.\n");
    say(QCTNAME(TP)+" whistles for a weasel.\n");
    if(TP->resolve_task(TASK_ROUTINE,({SKILL_WEIGHT,200,105})) > 0)
    {
        set_alarm(5.0,0.0,"weasel");
        return 1;
    }
    set_alarm(5.0,0.0,"fail");
    return 1;
}

void
weasel()
{
    object obj;
    seteuid(getuid(TO));
    tell_room(E(TP),"A weasel skitters up to "+QCTNAME(TP)+".\n",TP);
    obj = clone_object(CPASS(goblin/guild/weasel));
    write("A weasel skitters up to you.\n");
    obj->move(TP);
}

void
fail()
{
    write("You feel that you failed to summon your weasel.\n");
}

int
dahelp()
{
   write("+------------------------------------------------------+\n");
   write("| To get a list of emotes------------------- daemotes  |\n");
   write("| To get a history of the Dark Alliance----- dahistory |\n");
   write("| To speak in the Alliance language--------- dasay     |\n");
   write("| To get a list of titles------------------- rtitles   |\n");
   write("+------------------------------------------------------+\n");
   return 1;
}
int
dahistory()
{
    TP->more("/d/Kalad/open/DA_INFO",1);
    return 1;
}

int
rtitles()
{
    write("+----------------------------------------------+\n");
    write("| Novice Rider of the Dark Alliance            |\n");
    write("| Trainee Rider of the Dark Alliance           |\n");
    write("| Trained Rider of the Dark Alliance           |\n");
    write("| Experienced Rider of the Dark Allaince       |\n");
    write("| Expert Rider of the Dark Allaince            |\n");
    write("| Specialist Rider of the Dark Alliance        |\n");
    write("| Master Rider of the Dark Alliance            |\n");
    write("| Elite Rider of the Dark Allaince             |\n");
    write("| Legendary Rider of the Dark Alliance         |\n");
    write("+----------------------------------------------+\n");
    return 1;
}

int
daemotes()
{
    TP->more("/d/Kalad/open/DAR_EMOTES",1);
    return 1;
}

string query_rank()
{
    switch(environment()->query_rider_level())
    {
        case 0:
        return "a black studded-leather collar";
        break;
        case 1:
        return "a rusted iron collar";
        break;
        case 2:
        return "a dingy copper collar";
        break;
        case 3:
        return "a polished steel collar";
        break;
        case 4:
        return "a smooth brass collar";
        break;
        case 5:
        return "a shiny silver collar";
        break;
        case 6:
        return "a bright, emerald-studded gold collar";
        break;
        case 7:
        return "an exsquisite, saphire-studded platinum collar";
        break;
        case 8:
        return "an impresive, ruby-spiked obsidian collar";
        break;

     }
}                          
