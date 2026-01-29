inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>      
#include "/d/Roke/common/defs.h"
#include "/d/Roke/varl/atuan/cape/guild/default.h"

#define   LASTING_TIME    2500
#define   MAX_FROM_ONE    2
#define   MAX_TOTAL       10

static string *message = ({ });
static string *who_sent = ({ });
static string *sent_for = ({ });
static int    *tt = ({ });

void give_message(mixed args);

void
create_object()
{
   set_name("_traveler_messager_");
   set_short(0);
   set_long(0);
   
   add_prop(OBJ_I_INVIS, 100);
   add_prop(OBJ_I_NO_GET, 1);
   
   seteuid(getuid());
   
   set_no_show();
}

void
remove_one_message(mixed arg)
{
   string str;
   string *tmp1, *tmp2, *tmp3;
   int i, j, *list = ({ });
   
   if(stringp(arg))
      {
      str = arg;
      for(i=0; i<sizeof(who_sent); i++)
	  if(who_sent[i] == str)  
	      list += ({ i });
      i = list[random(sizeof(list))];
   }
   else
      i = arg;
   
   tmp1 = ({ }); tmp2 = ({ }); tmp3 = ({ }); list = ({ });
   for(j=0; j<sizeof(sent_for); j++)
   if(i != j)
      {
      tmp1 += ({ who_sent[j] });
      tmp2 += ({ message[j] });
      tmp3 += ({ sent_for[j] });
      list += ({ tt[j] });
   }
   who_sent = tmp1;
   message = tmp2;
   sent_for = tmp3;
   tt = list;
}

void
set_messager(string name, string who, string str)
{
   if((sizeof(who_sent)-sizeof(who_sent-({name}))) > MAX_FROM_ONE) 
   remove_one_message(name);
   if(sizeof(who_sent) > MAX_TOTAL)
      remove_one_message(random(sizeof(who_sent)));
   
   who_sent += ({ name });
   sent_for += ({ who });
   message += ({ str });
   tt += ({ time() });
}

mixed
query_messager()
{
   return ({ who_sent, sent_for, message, tt });
}

void
init()
{
   set_alarm(2.0, 0.0, "give_message", TP );
   
   ::init();
}

void
remove_message(string name)
{
   string *tmp1, *tmp2;
   int i;
   
   tmp1 = ({ });
   tmp2 = ({ });
   if(sizeof(sent_for))
   for(i=0; i<sizeof(sent_for); i++)
   if(name != sent_for[i])
      {
      tmp1 += ({ who_sent[i] });
      tmp2 += ({ message[i] });
   }
   who_sent = tmp1;
   message = tmp2;
   sent_for -= ({ name });
}

/* Function:    give_message(object who)
* Description: This will send the stored message to the player and
*              then destruct itself if empty.
   */
void
give_message(object who)
{
   int i;
   string name = who->query_real_name();
   string race = who->query_race_name();
   int is_member = IS_MEMBER(who);
   
   who->catch_msg("You concentrate on the conversations around the room "+
      "and feel that there are some rumours floating here...\n");
   if(sizeof(sent_for))
   for(i=0; i<sizeof(sent_for); i++)
     if(("all" == sent_for[i])  || (name == sent_for[i]) ||
	(is_member && ("travellers" == sent_for[i])) ||
	(sent_for[i] == who->query_race_name()))
       who->catch_msg("You pick up '"+capitalize(message[i])+"' from "+
		      capitalize(who_sent[i])+".\n");

   remove_message(name);
   
   while((tt[0] + LASTING_TIME) < time()) remove_one_message(0);
   
   if(!sizeof(sent_for))
      remove_object();
}

