inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc.c";
inherit "/d/Emerald/common/guild/kot/lib/npc_convey";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/kot/guild.h"
#include <macros.h>

void get_help(object enemy);

int alarmid, p, convey_time;

void
create_emerald_monster()
{
   set_name("mondarin");
   add_name( ({"king", }) );
   set_title("the King of Telberin");
   add_adj( ({"regal", "dignified"}) );
   set_race_name("elf");
   set_long("This regal, dignified elderly elf is Mondarin, "+
	"the King of Telberin. He stands here in his throne room "+
	"patiently as the court seneschal presents supplicants, "+
	"and those who wish to pay him tribute. He looks very "+
	"wise and learned, yet not in the least frail or weak.\n");
   
   set_stats( ({ 100, 130, 100, 100, 100, 100 }) );
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_PARRY, 80);
   set_skill(SS_WEP_CLUB, 70 + random(25));
   set_skill(SS_AWARENESS, 45 + random(10));
   set_alignment(700 + random(100));
   add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_S_EXTRA_SHORT, " the King of Telberin");
   
   set_cchat_time(6);  
   add_cchat("Thou fool! Guards!!");
   
   set_act_time(10);    
   add_act("yawn");      
   add_act("hmm");

   add_equipment( ({ "/d/Emerald/telberin/castle/wep/kingscepter",
			"/d/Emerald/telberin/castle/arm/kingcrown",
		       "/d/Emerald/telberin/castle/arm/kingrobe"}) );
   
   set_default_answer("I'm not really interested. Ask the Queen.\n");
   trig_new("%w 'bows' %s", "react_bow");
}

int
react_bow(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_bow", 3, who);
      return 1;
   }
}

void
return_bow(string who) {
   command("nod formally " + who);
}


public void
add_introduced(string str)
{
    object sen;

    sen = present("seneschal", environment(TO));

    if (!present(find_player(str)), ENV(TO))
        return;
    if(sen)
    	set_alarm(2.0, 0.0, &sen->announce_guests(TO, str) );
}

/*
 * Function name:   short
 * Description:     Returns the short-description of this living, for the
 *                  object given. Handles invisibility and met/nonmet.
 * Returns:         The short string.
 */
public varargs string
short(object for_obj)
{
    string desc;
    string extra;

    if (!objectp(for_obj))
        for_obj = this_player();

    if (notmet_me(for_obj))
    {
        desc = this_object()->query_nonmet_name();
    }
    else
    {
      /* we only want the extra if we're checking met name */
      /* thanks goes out to Olorin for this piece          */
        desc = this_object()->query_met_name();
        if (strlen(extra = query_prop(LIVE_S_EXTRA_SHORT)))
        {
            return (desc + extra);
        }

    }

    return desc;
}

attacked_by(object enemy)
{
  get_assistance(enemy);
  command("shout Help! Guards!!");
  /*if(!sizeof(get_alarm(alarmid)) || sizeof(get_alarm(alarmid)) == 0)*/
  get_help(enemy);

  if ((time() - convey_time) > 90)
  {
      convey_time = time();
      ktconvey("red");
  }

  ::attacked_by(enemy);
}

get_help(object enemy)
{
  object bodyguard;
  int i, n;
  if(p > 9) return;

  /* n = (random(4) + 2); */
  n = 5;
  p = n + p;

  setuid();
  seteuid(getuid());

  for(i = 0; i < n; i++)
    {
	bodyguard = clone_object(TELBERIN_DIR + "castle/npc/bodyguard");
	bodyguard->move(ENV(TO), 1);
	bodyguard->do_rescue(TO, enemy);
	find_player("karath")->catch_msg("i is "+i+" p is "+p+"\n");
        continue;
    } 
}

void
show_hook(object ob)
{
    object sh, who = this_player();
    mixed why;

    if (!ob->id(GUILD_EMBLEM_ID))
    {
        command("eyebrow " + OB_NAME(who));
        return;
    }

    if (who->query_kot_member())
    {
        command("smile proudly " + OB_NAME(who));
        return;
    }

    command("say Sorry, but the Protectorate is accepting no " +
        "new members at this time.");

#if 0
    if (!who->query_prop("_newbie_wannabe_keeper"))
    {
	who->catch_tell("You have not been given the proper blessing. " +
            "Without that, the rest of the ritual seems pointless "+
	    "to pursue.\n");
	return;
    }

    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);
    if (stringp(why = sh->acceptable_kot_member(who)))
    {
        who->catch_tell(why);
        command("say You are unworthy to join the Protectorate, " +
            who->query_name() + ".");
        sh->remove_shadow();
        return;
    }

    if (sh->add_kot_member(who, WARRIOR_CASTE) != 1)
    {
        who->catch_tell("Some conflict prevents you from joining the " +
            "Protectorate of the Keepers of Telberin.\n");
        sh->remove_shadow();
        return;
    }

    tell_room(environment(),
        QCTNAME(this_object())+" steps down off of the dais and "+
        "lays his hand upon "+QTNAME(who)+"'s shoulder, " +
        "beginning to speak.\n", who);
    who->catch_tell(query_The_name(who) + " steps down off of the dais and "+
	"lays his hand upon your shoulder, beginning to speak.\n");

    command("say to "+ OB_NAME(who) +
        " As my father's ancestors were of the Protectorate "+
        "in their roles as Keepers of Telberin, so shall "+
        "you be.");

    tell_room(environment(),
        "A brief flash of brilliant, emerald light fills the "+
	"room and then is gone instantly.\n");
#endif
}
