/* created by Aridor 12/01/93
 * 
 * The scabbard or holster of the Prestigious Knights' Club.
 * It's the guild object.
 *
 */


inherit "/std/object";

#include "clubdefs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>

string location = "side";
string my_type = "scabbard";

/*prototypes*/
void soul(object ob);
int is_a_real_scabbard();
void log_a_login();
void log_a_logout();


string 
query_auto_load() 
{
  return MASTER_OB(TO) + ":" + location + " " + my_type;
}

void
init_arg(string arg)
{
    int num1, num2;
    string str1, str2;

    /*write(arg);*/
    if (sscanf(arg, "%s %s", str1, str2) == 2)
      {
	location = str1;
	my_type = str2;
      }
/*    write(str1 + " " + str2 + "\n");*/
}

void
check_if_owner_still_member()
{
  if ((CLUBMASTER)->is_no_longer_a_member(TP))
    (CLUBMASTER)->expel_from_club(TP, "You have not been faithful enough to the Prestigious Knights' Club.\n" +
				  "You have deserted the club for too long and have been removed from the club.\n" +
				  "Of course you will have the chance again to become a member.\n");
  else
    set_no_show_composite(1);
}

void
create_object()
{
    set_name("scabbard");
    add_name(IN_CLUB);
    set_adj("traditional");
    add_adj("ornamented");
    set_long("@@my_long");
    add_prop(OBJ_M_NO_DROP, "You cannot drop your personal scabbard.\n");

    call_out("check_if_owner_still_member", 5);
}


int
remove_object()
{
  object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
  if (sheathed)
    {
      sheathed->add_prop(OBJ_M_NO_DROP, sheathed->query_prop(CLUB_M_TMP_NO_DROP));
      sheathed->unset_no_show();
      sheathed->unset_no_show_composite();
      TP->catch_msg("You retrieve your " + sheathed->short() + " from the " + my_type + ".\n");
      TP->remove_prop(CLUB_O_SHEATHED_WEAPON);
      
    }
  log_a_logout();
  return ::remove_object();
}


string
my_long()
{
  object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
  if (!location)
    {
      location = "side";
      TP->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    }
  return BS("This is your personal traditional " + my_type + ". It is beautifully " +
	    "crafted and has fine and detailed carvings and ornaments on in. " +
	    "This is the your personal status symbol of your membership in " +
	    "the Prestigious Knights' Club. " +
	    "Inscribed in the " + my_type + ", you can make out the word: " + 
	    capitalize(TP->query_real_name()) + ". If you want to know more about the " +
	    "Knights' Club type 'help knights club'.",SL) +
	    "The " + my_type + " is strapped to your " + location +
	    (sheathed ?
	     (" and " +  LANG_ADDART(sheathed->short()) + " is " +
	      (is_a_real_scabbard() ? "sheathed" : "secured") + " in it.\n") :
	     (" and it is empty.\n"));
}


void
switch_the_scabbard()
{
  object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
  if (sheathed)
    {
      sheathed->unset_no_show();
      sheathed->unset_no_show_composite();
      TP->remove_prop(CLUB_O_SHEATHED_WEAPON);
      write("You retrieve your " + sheathed->short() + " from your " + my_type + ".\n");
    }
  if (my_type == "holster")
    {
      my_type = "scabbard";
      remove_name("holster");
      set_name("scabbard");
      add_prop(OBJ_M_NO_DROP, "You cannot drop your personal scabbard.\n");
      set_short(0);
      location = "side";
      TP->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    }
  else
    {
      my_type = "holster";
      remove_name("scabbard");
      set_name("holster");
      add_prop(OBJ_M_NO_DROP, "You cannot drop your personal holster.\n");
      set_short(0);
      location = "back";
      TP->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    }
}


int
is_a_real_scabbard()
{
  return (my_type == "scabbard");
}


string 
query_my_type()
{
  return my_type;
}

void
change_location(string where)
{
    location = where;
}

void
remove_from_club(object player)
{
  if (player->query_alignment() < 0)
    (CLUBMASTER)->expel_from_club(player);
}

/*
perform_the_add_subloc(object who)
{
  who->remove_subloc("the_knights_club");
  who->add_subloc("the_knights_club", TO);
}
*/


void
init()
{
    call_out("soul", 5, TP);
    log_a_login();

/*add the club sublocation*/
    TP->add_subloc("the_knights_club", TO);

    if (TP->query_alignment() < 0)
      call_out("remove_from_club", 400, TP);

    if (my_type == "holster")
      {
	switch_the_scabbard();
	switch_the_scabbard();
      }
}


/*
 * Function name: soul
 * Description:   Add the cmdsoul to the member
 */
void
soul(object ob)
{
   int i;
   string *souls;
   
/*write("here");*/
/*strange!, seems to work with mortals but not with wizzes, hmmm*/
   seteuid(getuid(TO));
   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
     {
       ob->remove_cmdsoul(souls[i]);
/*       write(souls[i] + "  " + ob->query_real_name());*/
     }
   ob->add_cmdsoul(CLUB_SOUL);
/*   write("\n\n" + ob->query_cmdsoul_list()[0]);*/
   for (i = 0; i < sizeof(souls); i++)
     if (souls[i] != CLUB_SOUL)
       ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
/*   write("done");*/
}


string
show_subloc(string subloc, object me, object for_obj)
{
    string str, how;
    int value, myself;
    object sheathed = me->query_prop(CLUB_O_SHEATHED_WEAPON);
    if (!IS_CLUB_MEMBER(me))
      return "";
    if (!me->query_prop(CLUB_S_SCABBARD_LOCATION))
      me->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "You have your " + my_type + " strapped to your " + location +
	(sheathed ? (" and " + LANG_ADDART(sheathed->short()) + 
		     " is " + (is_a_real_scabbard() ? "sheathed" : "secured") +
		     " in it.\n") : (" and it is empty.\n"));  
    myself = (for_obj == me);
    str = capitalize(me->query_pronoun());

    how = " " + lower_case((CLUBMASTER)->get_supporter_title(me));
    if (how[1..1] == "u" || how[1..1] == "e" ||
	how[1..1] == "i" || how[1..2] == "ho")
      how = "n" + how;

    return (myself ? "You have your" : str + " has " + POSSESSIVE(me)) +
	   " traditional ornamented " + my_type + " strapped to " +
	   (myself ? "your" : POSSESSIVE(me)) + " " + location + ".\n" + 
	   (myself ? "You are a" : str + " is a") +
           how + "of the Prestigious Knights' Club.\n";

}

void
update_me()
{
  seteuid(getuid(TO));
  MASTER_OB(TO)->load_me();
  if (IS_CLONE)
    clone_object(MASTER_OB(TO))->move(E(TO));
  tell_object(E(TO),"Your traditional ornamented " + my_type + " was updated.\n");
  remove_object();
}

void
log_a_login()
{
  seteuid(getuid(TO));
  if (TP->query_wiz_level())
    return;
  if (!IS_CLUB_MEMBER(TP))
    return;
  write_file(LOG + TP->query_real_name(),"LIN," + time() + "," + TP->query_age() + "\n");
}

void
log_a_logout()
{
  seteuid(getuid(TO));
  if (TP->query_wiz_level())
    {
      (CLUBMASTER)->remove_wizard_from_member_list(TP);
      return;
    }
  if (!IS_CLUB_MEMBER(TP))
    return;
  write_file(LOG + TP->query_real_name(),"OUT," + time() + "," + TP->query_age() + "\n");
}
