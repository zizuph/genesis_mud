#pragma save_binary

inherit "/std/guild/guild_lay_sh";

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "../defs.h"
#include "../titles.h"

#define SW shadow_who
#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

int incognito;
int autosneak_on;

void kick_out_trickster();
string query_trickster_title();

public mixed query_guild_trainer_lay()
{
 return (TRICKSTERS + "train");
}

int query_guild_tax_lay() 
{
 return TRICKSTERS_TAX;
}

query_guild_style_lay()
{
 return GUILD_STYLE;
}

query_guild_name_lay()
{
 return GUILD_NAME;
}

mixed query_guild_skill_name(int type)
{
 if (type == SS_STRANGLE) return "strangle";

 return 0;
}

int query_guild_leader_lay()
{
 return ((SERVER)->query_jamadar(SW->query_name()) || 
   (SERVER)->query_leader(SW->query_name()));
}

void delay_init_trickster()
{
 object stick,kit,rumel;

 setuid();
 seteuid(getuid());

 write("Welcome , "+query_trickster_title()+"!\n");
 write("Serve Kina , The Year of Skulls is close!\n");

 if((SERVER)->query_baned(SW->query_name()))
  {
   SW->catch_msg("You have been banned from Tricksters!\n");
   kick_out_trickster();
   (SERVER)->check_inside(SW);
   return;
  }

 (SERVER)->check_promote_on_logon(SW);
 (SERVER)->notify_news(SW);

 incognito=1;
 autosneak_on=0;
 SW->add_subloc("trickster_subloc",TO);

 SW->add_cmdsoul(TRICKSTERS_SOUL);
 SW->update_hooks();

 if(!(SERVER)->query_punished(SW->query_name()))
  {
   if(!present(STICK_DESC,SW))
    {
     stick=clone_object(STICK);
     stick->move(SW);
     stick->load_stick();
    }

   if(!present(KIT_DESC,SW))
    {
     kit=clone_object(KIT);
     kit->move(SW);
     kit->load_kit();
    }

   if(!present(RUMEL_DESC,SW))
    {
     rumel=clone_object(RUMEL);
     rumel->move(SW);
     rumel->update_level();
    }
  }
 else write("You are still punished! No abilities for you this time!\n");
}

void init_lay_shadow(string arg)
{
 set_alarm(1.0, 0.0, delay_init_trickster);
}

int add_trick_shadow(object who)
{
 int ret = shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);

 if (ret == 1)
  {
   set_alarm(1.0, 0.0, &init_lay_shadow(0));
  }

 return ret;
}

int query_trickster_level()
{
 int level,i;

 if(SW->query_wiz_level()) return 100;

 if((SERVER)->query_jamadar(SW->query_name())) return 35;
 if((SERVER)->query_leader(SW->query_name())) return 50;

 for(i=sizeof(titles)-1;i>=0;i--)
   if(SW->query_skill(SS_KILL_POINTS)>=(titles[i])[1]*AVG_PTS) 
     return i+1;
}

void update_trick_soul()
{
 SW->remove_cmdsoul(TRICKSTERS_SOUL);
 SW->update_hooks();
 SW->add_cmdsoul(TRICKSTERS_SOUL);
 SW->update_hooks();
}

void kick_out_trickster()
{
 SW->remove_cmdsoul(TRICKSTERS_SOUL);
 SW->update_hooks();
 setuid();
 seteuid(getuid());

 present(STICK_DESC,SW)->remove_object();
 present(KIT_DESC,SW)->remove_object();
 present(RUMEL_DESC,SW)->remove_object();

 SW->set_default_start_location(SW->query_def_start());
 (SERVER)->remove_member(SW->query_name());
 SW->remove_skill(SS_STRANGLE);
 SW->remove_skill(SS_KILL_POINTS);
 SW->clear_guild_stat(SS_LAYMAN);
 remove_guild_lay(); 
}

int *query_max_stick()
{
 int *res=({0,0,0,0,0});
 int i,slot=0;

 for(i=0;i<query_trickster_level();i++)
  {
   if (res[slot]<4) res[slot]++;
   slot++;
   if(slot==5) slot=0;
  }

 return res;
}

int query_max_kit()
{
 int res;

 res=(query_trickster_level()-1)/6+1;
 if(res>4) res=4;

 return res;
}

string query_trickster_title()
{
 if((SERVER)->query_leader(SW->query_name())) return leader_title;
 if((SERVER)->query_jamadar(SW->query_name())) return jamadar_title;

 return (titles[query_trickster_level()-1])[0];
}

public string query_guild_title_lay()
{
 if(incognito) return "";

 return query_trickster_title();
}

void set_incognito(int inc) {incognito=inc;}
int query_incognito() {return incognito;}

public string show_subloc(string subloc, object on, object for_obj)
{
 if(subloc=="trickster_subloc")
  {
   if(incognito) return 0;
   if(on==for_obj) return "You have the rascally look of a Trickster.\n";
   return C(PRO(SW))+" has the rascally look of a Trickster.\n";
  }

 return SW->show_subloc(subloc,on,for_obj);
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
 int hiding, retval, val, bval, did_sneak;

 if (!SW->query_prop(LIVE_I_SNEAK) &&
     autosneak_on &&
     query_verb() &&
     !(SW->query_prop(OBJ_I_LIGHT) && (SW->query_prop(OBJ_I_LIGHT) >
       environment(SW)->query_prop(OBJ_I_LIGHT))) &&
       !(objectp(SW->query_attack()))
      )
  {
   hiding = environment(SW)->query_prop(ROOM_I_HIDE);
   bval = SW->query_skill(SS_SNEAK)*2+SW->query_skill(SS_HIDE)/3;
   bval = (bval - hiding) / 2;

   if (hiding >= 0 && bval > 0)
    {
     val = bval + random(bval);
     SW->add_prop(OBJ_I_HIDE, val);
     SW->add_prop(LIVE_I_SNEAK, 1);
     did_sneak = 1;
    }
   if (!did_sneak)
     tell_object(SW, "You failed to sneak.\n");
  }

 retval = SW->move_living(how, to_dest, dont_follow, no_glance);

 if (!did_sneak) return retval;

 hiding = environment(SW)->query_prop(ROOM_I_HIDE);
 bval = SW->query_skill(SS_HIDE);
 bval = (bval - hiding) / 2;

 set_this_player(SW);
 if (hiding < 0 || bval <= 0)
  {
   write("It's too difficult to hide in here, you're visible again.\n");
   SW->reveal_me(0);
  }
 else if (SW->query_prop(OBJ_I_LIGHT) &&
         (SW->query_prop(OBJ_I_LIGHT) >
          environment(SW)->query_prop(OBJ_I_LIGHT)))
  {
   write("You can't hide here, shining like that!\n");
   SW->reveal_me(1);
  }

  val = bval + random(bval);
  SW->add_prop(OBJ_I_HIDE, val);
  return retval;
}

void set_autosneak(int val) {autosneak_on=val;}
int query_autosneak() {return autosneak_on;}

void notify_you_killed_me(object ob)
{
 int kills,pts;

 SW->notify_you_killed_me(ob);

 kills=SW->query_skill(SS_KILL_POINTS);
 pts=ob->query_average_stat();
 if(SW->query_prop_setting("_trick_i_killed_with_rumel"))
   pts*=2;
 if(!ob->query_npc()) pts*=2;
 kills+=pts;
 SW->set_skill(SS_KILL_POINTS,kills);
 SW->remove_prop("_trick_i_killed_with_rumel");
}

string query_rumel_color()
{
 int level,i;
 string col="gray";

 level=query_trickster_level();

 if(level==100) return GM_RUMEL_COLOR;
 if(level==50) return LEADER_RUMEL_COLOR;
 if(level==35) return JAMADAR_RUMEL_COLOR;

 for(i=0;i<sizeof(RUMEL_LEVELS);i++)
   if(level>=(RUMEL_LEVELS[i])[1]) col=(RUMEL_LEVELS[i])[0];

 return col;
}

