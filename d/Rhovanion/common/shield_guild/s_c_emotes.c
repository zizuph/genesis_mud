#pragma save_binary

/*
'threaten' ...Elessar threatens you with his <weapon>
*/
#define SHADOW  "/d/Rhovanion/common/shield_guild/rumour_sh"

#define ME_DOMAINS  ({ "Rhovanion","Shire","Gondor" })
#define DONT_LOOK_SMOKE   "_dont_look_smoke"
#define IS_MEMBER(x)  ((x)->query_guild_member(GUILD_NAME))
#define LANGUAGE_TO_UNDERSTAND   100

/***********************  SIGNAL  ***************************/
void signal_now(object tp, string str);

int
signal(string str)
{
  string *signals = ({"HELP","HELLO","S.O.S.","O.K.","BYE"});
  int time;
  object obj;
  mixed tmp;

  if(str == "off")
  {
    TP->add_prop(DONT_LOOK_SMOKE, 1);
    write("You will not look for smoke signals.\n");
    return 1;
  }
  if(str == "on")
  {
    TP->remove_prop(DONT_LOOK_SMOKE);
    write("You look for smoke signals again.\n");
    return 1;
  }

  /***  first couple of restrictions  ***/
  if((strlen(str) != 1) && (member_array(str, signals) == -1))
  {
    NF("Signal what?\n");
    return 0;
  }
  if(TP->query_attack())
  {
    write("You can't give smoke signals while fighting!\n");
    return 1;
  }
  if(ENV(TP)->query_prop(ROOM_I_INSIDE))
  {
    write("You must be outside to make smoke signals!\n");
    return 1;
  }
  tmp = ENV(TP)->query_prop(ROOM_I_TYPE);
  if((tmp == ROOM_IN_WATER) || (tmp == ROOM_UNDER_WATER))
  {
    write("You can't make smoke signals in the water!\n");
    return 1;
  }
  if(tmp == ROOM_IN_AIR)
  {
    write("There is no wood for smoke signals in the air!\n");
    return 1;
  }

  // *** It is tiring to make smoke signals (gather wood etc...)
  if(TP->query_fatigue() < 15)
  {
    write("You are too exhausted to gather enough wood for smoke signal.\n");
    return 1;
  }
  TP->add_fatigue(-10);
  write("You gather some wood and start to make smoke signals.\n");
  tell_room(ENV(TP), QCTNAME(TP)+" gathers some wood and starts to make "+
                     "smoke signals.\n", TP);

  time = random(10)+10;
  set_alarm(itof(time), 0.0, &signal_now(TP, str));
  setuid();
  seteuid(getuid());
  obj = clone_object("/std/paralyze");
  obj->set_no_show(1);
  obj->set_stop_message("");
  obj->set_fail_message("You must stop signaling to do something else.\n");
  obj->set_stop_verb("stop");
  obj->set_stop_fun("stop_signaling");
  obj->set_stop_object(TO);
  obj->set_remove_time(time);
  obj->move(TP);

  return 1;
}

void
make_message(object who, string from, int mess,   int sign,
                                      string str, string name, int dif)
{
  int *hard = ({ 30, 60, 200 });
  int read_mess, read_sign;
  string text;

  if(random(who->query_skill(SS_LOC_SENSE)) > random((30*dif)+10))
    text = "coming up somewhere from the land of "+from+".\n";
  else
    text = "but you are not sure where it originated.\n";
  who->catch_msg("You notice some smoke signal "+text);

  if(!IS_MEMBER(who)) return;

  if(random(hard[dif]) < (mess + random(who->query_stat(SS_INT))))
    read_mess = 1;

  if(random(hard[dif]) < (sign + random(who->query_stat(SS_INT))))
    read_sign = 1;

  if(!read_mess && !read_sign)
  {
    who->catch_msg("You are not able to recognize the meaning of it.\n");
    return;
  }
  if(!read_mess)
  {
    who->catch_msg("You are only able to recognize the signature '"+
                    name+"'.\n");
    return;
  }
  if(!read_sign)
  {
    who->catch_msg("You are only able to recognize the symbol '"+
                   str+"'.\n");
    return;
  }
  who->catch_msg("You are able to recognize the symbol '"+
                 str+"' and the signature '"+name+"'.\n");
}

void
signal_now(object tp, string str)
{
  object *present, *list;
  string where1, where2, name;
  int i, j, how_visible, message, signature;

  if (!objectp(tp)) return;
  name = tp->query_name();
  list = users() - ({ tp });
  present = list & all_inventory(ENV(tp));
  list -= present;

  /* how much wood did we gather and how well can we use it */
  how_visible = random(tp->query_stat(SS_STR))+
                random(tp->query_stat(SS_WIS))+
                random(tp->query_stat(SS_INT));
  /* we need to be agile to jump around properly */
  message =     random(tp->query_stat(SS_DEX))+
                random(tp->query_stat(SS_WIS))+
                random(tp->query_stat(SS_INT));
  signature =   random(tp->query_stat(SS_DEX))+
                random(tp->query_stat(SS_WIS))+
                random(tp->query_stat(SS_INT));

  tp->catch_msg("You finish making smoke signals.\n");
  tell_room(ENV(tp), QCTNAME(tp)+" finishes making smoke signals.\n", tp);
  if(sizeof(present))
  for(i=0; i<sizeof(present); i++)
    if(IS_MEMBER(present[i]))
        present[i]->catch_msg("You recognize symbol '"+str+"'.\n");

  where1 = explode(MASTER_OB(ENV(tp)),"/")[2];

  for(i=0; i<sizeof(list); i++)
    if(objectp(list[i]) && objectp(ENV(list[i])) &&
       !(ENV(list[i])->query_prop(ROOM_I_INSIDE)) &&
       (ENV(list[i])->query_prop(ROOM_I_LIGHT) > 0) &&
       !(list[i]->query_prop(DONT_LOOK_SMOKE)) &&
       CAN_SEE_IN_ROOM(list[i]) &&
       (!list[i]->query_wiz_level() || IS_MEMBER(list[i])))
    {
      j = (how_visible+list[i]->query_skill(SS_AWARENESS)) / 2;
      if ((where2 = explode(MASTER_OB(ENV(list[i])),"/")[2]) == where1)
      {
        if (random(20) < j)
          make_message(list[i], where1, message, signature, str, name, 0);
      }
      else if ((member_array(where1, ME_DOMAINS) != -1) &&
               (member_array(where2, ME_DOMAINS) != -1))
      {
        if (random(60) < j)
          make_message(list[i], where1, message, signature, str, name, 1);
      }
      else if (random(150) < j)
          make_message(list[i], where1, message, signature, str, name, 2);
    }
  return;
}

int
stop_signaling(mixed arg)
{
    int i;
    mixed *calls;

    if((arg == "signaling") || (arg == "signal"))
    {
        write("You decide to stop signaling.\n");
        tell_room(ENV(TP), QCTNAME(TP)+" decides to stop signaling.\n", TP);
        calls = get_all_alarms();
        for (i = 0; i < sizeof(calls); ++i)
        {
            if((calls[i][1] == "signal_now") && (calls[i][4][0] == TP))
            {
                remove_alarm(calls[i][0]);
                return 0;
            }
        }
        write("It seems that you were not signaling...\n");
    }
    return 1;
}
/************************************************************************/

/***********************  INCOGNITO  ***************************/
int
incognito(string arg)
{
    if ((arg != "on") && (arg != "off"))
    {
        NF("Incognito what?\n");
        return 0;
    }
    if (arg == "on")
    {
        if (TP->query_incognito())
        {
            write("You are already trying to be incognito!\n");
            return 1;
        }
        TP->set_incognito(1);
        write("You will try to be incognito.\n");
        return 1;
    }
    if (!TP->query_incognito())
    {
        write("But you are not trying to be incognito!\n");
        return 1;
    }
    TP->set_incognito(0);
    write("You stop trying to be incognito.\n");
    return 1;
}
/************************************************************************/

/***************************   AASAY       ******************************/

int
aasay(string str)
{
    int i, j, dots, lan_skill;
    object *oblist, *tmp = ({ });
    string *words, what_get;

    if (!ENV(TP))
	return 0;

    if (!strlen(str))
    {
	NF("What do you want to say in Angmar language?\n");
	return 0;
    }

    oblist = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));

    for (i = 0; i < sizeof(oblist); i++)
    {
	if (IS_MEMBER(oblist[i]) || (oblist[i]->query_wiz_level()) ||
            (oblist[i]->query_skill(SS_LANGUAGE) >= LANGUAGE_TO_UNDERSTAND))
	{
	    oblist[i]->catch_msg(QCTNAME(TP)+" says in Angmar: "+str+"\n");
            tmp += ({ oblist[i] });
	}
    }
    words = explode(str, " ");
    oblist -= tmp;
    for (i = 0; i < sizeof(oblist); i++)
    {
      dots = 0;
      what_get = "";
      lan_skill = oblist[i]->query_skill(SS_LANGUAGE);
      lan_skill = lan_skill*lan_skill/ LANGUAGE_TO_UNDERSTAND;
      for (j = 0; j < sizeof(words); j++)
        if(lan_skill > random(LANGUAGE_TO_UNDERSTAND))
	{
	  what_get += words[j]+" ";
          dots = 0;
	}
        else if(!dots)
	{
          dots = 1;
	  what_get += "... ";
	}
      if(what_get == "... ")
        oblist[i]->catch_msg(QCTNAME(TP)+" says something that you don't "+
				"understand at all.\n");
      else
        oblist[i]->catch_msg(QCTNAME(TP)+" says something like: "+
				what_get+"\n");
    }
    if (TP->query_get_echo())
	write("You say in Angmar: " + str + "\n");
    else
	write("Ok.\n");
    return 1;
}

/************************************************************************/
