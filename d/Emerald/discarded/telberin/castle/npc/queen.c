inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc.c";
inherit "/d/Emerald/common/guild/kot/lib/npc_convey";

#include "/d/Emerald/defs.h"
#if 0
#include "/d/Emerald/lib/bit.h"
#endif

#include "/d/Emerald/common/guild/kot/guild.h"

#include <macros.h>

int alarmid, convey_time;

void get_help(object enemy);
#if 0
int give_jewels(string str);
#endif

void
create_emerald_monster()
{
   set_name("meltessa");
   add_name( ({"queen", }) );
   set_title("the Queen of Telberin");
   add_adj( ({"majestic", "beautiful"}) );
   set_race_name("elf");
   set_gender(1);
   set_long("This majestic, beautiful elf is Meltessa, the Queen "+
	"of Emerald. She stands tall, resplendant in her gown, "+
	"bearing a face of wisdom and beauty unmarred by age. "+
	"She is looking kindly upon the crowd of people in the "+
	"courtroom, waiting for the court Seneschal to announce "+
	"each of them."+
	"\n");
   
   set_stats( ({ 80, 100, 80, 100, 100, 80 }) );
   set_skill(SS_DEFENCE, 80);
   set_skill(SS_PARRY, 22);
   set_skill(SS_WEP_POLEARM, 50 + random(25));
   set_skill(SS_AWARENESS, 45 + random(10));
   set_alignment(700 + random(100));
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(LIVE_S_EXTRA_SHORT, " the Queen of Emerald");
   
   set_cchat_time(6);  
   /* add_cchat("@@help_call"); */
   add_cchat("Thou fool! Guards!!");
   
   set_act_time(10);    
   add_act("smile");
   add_act("grin merr");

   add_equipment( ({ TELBERIN_DIR + "castle/arm/queencrown",
		       TELBERIN_DIR + "castle/arm/queengown" }) );
   
   set_default_answer("I'm not really interested. Ask the King.\n");
   trig_new("%w 'bows' %s", "react_bow");

#if 0
   add_ask("jewels", VBFC_ME("react_jewel_ask"));
#endif
}

#if 0
string
react_jewel_ask()
{
    if (environment(TO)->query_stolen())
    {
	command("sob");
	return "The queen sobs to you: All of my beautiful "+
	    "jewels, given to me as wedding gifts "+
	    "by my husband! They're all gone! Some vile creature has "+
	    "taken them from me! Oh please help me get my jewels back!\n";
    }
    else {
	command("smile proud");
	return "The queen smiles at you: I once again have my beautiful "+
	    "jewels, wedding gifts from my wonderful husband! They're "+
	    "too valuable to me to leave out in the open, though.\n";
    }
}

void
init_living()
{
    ::init_living();
    add_action(give_jewels, "give");
}


int
give_jewels(string str)
{
    object ob1, ob2, ob3, ob4, ob5;

    if ((str!="jewels to queen") &&
	(str!="jewels to meltessa"))
	return 0;

    if (!environment(TO)->query_stolen())
    {
	notify_fail("You don't have any jewels that the queen "+
		    "would currently be interested in. Hers are "+
		    "secure within her safe.\n");
	return 0;
    }

    if(! ( (ob1=present("qj_bracelet", TP)) &&
	(ob2=present("qj_crown", TP)) &&
	(ob3=present("qj_earrings", TP)) &&
	(ob4=present("qj_necklace", TP)) &&
	(ob5=present("qj_ring", TP))) )
    {
	notify_fail("You do not have the jewels that the queen "+
		    "is currently looking for. Perhaps you should "+
		    "try to recover the queen's Emerald jewels?\n");
	return 0;
    }

    // at this point the player has all the jewels and we can reward
    // him/her/it.

    write("You step up to the queen and return her lost jewels.\n");
    command("thank "+TP->query_real_name());
    command("hug "+TP->query_real_name());

    if (TP->test_bit("Emerald", JEWELS_GROUP, JEWELS_BIT))
    {
	command("say to "+TP->query_real_name()+" You have yet again "+
		"returned to me my jewels! I am forever in your debt!");
    }
    else {
	command("say to "+TP->query_real_name()+" You have returned to "+
		"me my most precious possessions! I am forever in your "+
		"debt!");
	write("You feel more experienced.\n");
       QUEST_LOG("jewel", TP, " Completed the Jewel Quest");
	TP->add_exp(JEWELS_XP, 0);
       ob1->remove_object(); ob2->remove_object();
        ob3->remove_object(); ob4->remove_object();
        ob5->remove_object();
        TP->set_bit(JEWELS_GROUP, JEWELS_BIT);
    }

    return 1;
}
#endif

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

    if (!present(find_player(str), ENV(TO)) || present("king", ENV(TO)))
        return;
    if(sen)
      {
    set_alarm(2.0, 0.0, &sen->announce_guests(TO, str) );
      }
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
  	alarmid = set_alarm(0.5, 0.0, &get_help(enemy));

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
  n = (random(4) + 2);

  setuid();
  seteuid(getuid());

  for(i = 0; i < n; i++)
    {
	bodyguard = clone_object(TELBERIN_DIR + "castle/npc/bodyguard");
	bodyguard->move(ENV(TO));
        bodyguard->do_rescue(this_object(), enemy);
	tell_room(ENV(TO), CAP(LANG_ADDART(bodyguard->query_race_name()))+
		" rushes to "+HIS_HER(bodyguard)+" ruler's aid!\n");
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

    command("say Sorry, but the Order is accepting no " +
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
        command("say You are unworthy to join the Order, " +
            who->query_name() + ".");
        sh->remove_shadow();
        return;
    }

    if (sh->add_kot_member(who, CLERIC_CASTE) != 1)
    {
        who->catch_tell("Some conflict prevents you from joinint the " +
            "Order of the Keepers of Telberin.\n");
        sh->remove_shadow();
        return;
    }

    tell_room(environment(),
        QCTNAME(this_object()) + " steps down off of the dais and "+
        "lays her hand upon "+QTNAME(who)+"'s shoulder, " +
        "beginning to speak.\n", who);
    who->catch_tell(query_The_name(who) + " steps down off of the dais and "+
	"lays her hand upon your shoulder, beginning to speak.\n");
    command("say " +
        " As my mother's ancestors were of the Order in their "+
	"roles as Keepers of Telberin, so shall you be, " + 
        who->query_name() + ".");
    tell_room(environment(),
        "A brief flash of brilliant, emerald light fills the "+
	"room and then is gone instantly.\n");
#endif
}
