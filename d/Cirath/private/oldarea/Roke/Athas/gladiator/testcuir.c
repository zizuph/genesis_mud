inherit "/std/armour";

/* 
*      This is currently the first version of the cuirasse, having been taken
*      from Mylos's work on the wildrunner_guild of the domain Emerald.
*                      Mylos   18-8-93 
*/

#include "guild.h"
#include <macros.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include "guruquest.h"

#define IS_SPECIAL      ({ "tintin", "plugh", "quis", "tricky", "glindor", "mylos", "nick", "mecien", "marvin" })

static int      used,
            no_noise,       /* True if replace is to be silently */
              killed,
            more_pos;

static string   filter_str,
               *more_array;
string             *banned;

void    add_glad_actions();
void    init_msg(object who);
int     is_a_glad(object owner);
int     ghost();
int     fail_ghost();
void    more_list();
void    wait_for_more(string str);
int     is_founder(string str);
int     is_member(mixed who);
int     is_a_glad(object ob);
int     set_silent();
int     has_a_cuirasse(object obj);

/*
* Function name:   is_founder
* Description:     Test if the person is a member of the Roke domain or
   *                  a special person
* Arguments:       who: Either the name or the object of the person to check
* Returns:         1 if a founder, 0 otherwise
   */
int
is_founder(string str)
{
   if (!str)
      return 0;
   str = lower_case(str);
   if (SECURITY->query_wiz_dom(str) == DOMAIN_NAME)
      return 1;
   return (member_array(str,IS_SPECIAL)!= -1);
}

query_recover()
{ 
    return 0;
}

/*
* Function name:   is_member
* Description:     Test if the person is a member of the Gladiator guild 
* Arguments:       who: Either the name or the object of the person to check
* Returns:         1 if a member, 0 otherwise
*/
int
is_member(mixed who)
{
   object ob;
   if (!who)
      return 0;
   if (stringp(who))
      ob = find_player(lower_case(who));
   else if (objectp(who))
      ob = who;
   else
      return 0;
   if (!ob || !interactive(ob))
      return 0;
   if (ob->test_bit(DOMAIN_NAME, GLAD_GROUP, GLAD_MEMBER))
      return 1;
   return 0;
}

/*
* Function name:   is_a_glad
* Description:     Test whether this person is also bearing a Gladiators title.
* Arguments:       owner: The person to check.
* Returns:         1 if the person is a Gladiator, 0 otherwise.
*/
int
is_a_glad(object ob)
{
   string str;
   
   if (ob->query_wiz_level() > WIZLEV_NORMAL)
      return 1;
   str = ob->query_title();
   if (str && sscanf(str, "%s Gladiator%s", str, str) == 2)
      return 1;
   return 0;
}

/*
* Function name:   add_soul_at_top
* Description:     add given soul at the top of the cmdsoul list
* Arguments:       soul: filename of soul to be added
*                  who:  player the soul must be added to
* Returns:         1 if successful, 0 otherwise.
   */
static int
add_soul_at_top(string soul, object who)
{
   string *soul_arr;
   int i;
   
   seteuid(getuid());
   if (member_array(soul, who->query_cmdsoul_list()) >= 0)
      who->remove_cmdsoul(soul);
   if (!who->add_cmdsoul(soul))
      return 0;
   else
      who->remove_cmdsoul(soul);
   soul_arr = who->query_cmdsoul_list();
   for (i = 0; i < sizeof(soul_arr); i++)
   who->remove_cmdsoul(soul_arr[i]);
   who->add_cmdsoul(soul);
   for (i = 0; i < sizeof(soul_arr); i++)
   who->add_cmdsoul(soul_arr[i]);
   who->update_hooks();
   return 1;
}

int
less_eq_func(string str1, string str2)
{
   return str1 <= str2;
}

int
partial_name_filter(string str)
{
   string var3, var2, var1;
   
   var3 = "#" + str + "#";
   var2 = "#" + filter_str + "%s";
   if (sscanf(var3, var2, var1))
      return 1;
   return 0;
}

/*
 * Function name:   join_to_guild
 * Description:     Join someone to the Gladiator guild. The person's
 *                  guildbit will be set, and necessary Gladiator-stuff will be
 *                  added. It will not add the cuirasse, tough.
 * Arguments:       ob: player to be joined
 * Returns:         1 if successful, 0 otherwise.
 */
static int
join_to_guild(object ob, int check)
{
    object shadow;
    int i;

    seteuid(getuid());

    if (!ob->set_bit(GLAD_GROUP, GLAD_MEMBER)) {
        log_file("errors", ctime(time()) + " Could not set guild bit in "
                 + capitalize(ob->query_real_name()) + ".\n");
        if (check) {
            write("-> Could not set guild bit.\n");
            write("-> Aborting...\n");
        }
        return 0;
    }
    else if (check)
        write("-> Successfully set the guild bit.\n");

    ob->set_guild_pref(SS_OCCUP, TAX);
    if (check)
        write("-> Set guild-tax.\n");

    if (ob->query_guild_member(GUILD_NAME)) {
        if (check)
            write("-> Player already has a guild shadow.\n");
    }
    else 
    {
        shadow = clone_object(GUILD_SHADOW);
        i = shadow->shadow_me(ob, GUILD_TYPE, GUILD_STYLE, GUILD_NAME);
        if (i == 1) 
        {
            if (check)
                write("-> Successfully added the guild shadow.\n");
                log_file("guild", "Added a guild shadow.\n");
        }
        else 
        {
            if (check) 
            {
                write("-> Failed to add the guild shadow.\n");
                write("-> Aborting...\n");
            }
            shadow->remove_object();
            return 0;
        }
    }
    if (ob->query_wiz_level() == WIZLEV_MORTAL) 
    {
        if (add_soul_at_top(GLAD_SOUL, ob)) 
        {
            if (check)
                write("-> Successfully added the guild soul.\n");
        }
        else 
        {
            if (check) 
            {
                write("-> Failed to add the guild soul.\n");
                write("-> Aborting...\n");
            }
            return 0;
        }
    }
    else if (check)
        write("-> Skipped addition of the guild soul.\n");
    return 1;
}

/*
 * Function name:   do_excom
 * Description:     Expell someone from the Vamp guild. The person's
 *                  guildbit is erased, and all Vamp-stuff is removed.
 * Arguments:       str: Name of the person to be expelled.
 * Returns:         1 if successful, 0 otherwise.
 */
static int
do_excom(string str)
{
    object ob, cuir;
    string *list;

    if (!str || !is_founder(this_player()->query_real_name()))
        return 0;
    ob = find_player(str);
    if (!ob) {
        notify_fail("No player with that name.\n");
        return 0;
    }
    if (ob == this_player()) {
        notify_fail("You can't excommunicate yourself.\n");
        return 0;
    }
    if (is_founder(ob->query_real_name())) {
        notify_fail("Lord Ged is very fond of " + ob->query_name() + 
        " and won't let you do it.\n");
        return 0;
    }
    seteuid(getuid());

    if (!ob->clear_bit(GLAD_GROUP,GLAD_MEMBER)) {
        log_file("errors", ctime(time()) + " Could not clear guild bit in "
                 + capitalize(ob->query_real_name()) + ".\n");
            write("-> Could not clear guild bit.\n");
    }
    else 
        write("-> Successfully cleared the guild bit.\n");

    ob->set_guild_pref(SS_OCCUP, 0);
        write("-> Relieved of the guild-tax.\n");

    if (ob->query_guild_member(GUILD_NAME)) {
            write("-> Guild shadow found ");
        if (ob->remove_guild_occ())
            write("and removed.\n");
        else
            write("but failed to remove.\n");
    }
    else 
        write("-> Guild shadow not found.\n");

    list = ob->query_cmdsoul_list();
    if (member_array(GLAD_SOUL, list) >= 0) {
            write("-> Guild soul found ");
        if (ob->remove_cmdsoul(GLAD_SOUL))
            write("and removed.\n");
        else 
            write("but failed to remove.\n");
    }
    else 
        write("-> Guild soul not found.\n");
    ob->remove_skill(70001);
    ob->set_skill(21, 0);
    if(TP->query_skill(23) > 50)
    {
        ob->set_skill(23, 50);
    }
    ob->set_race_name("gladiator");
    ob->heal_hp(-100000);
    ob->do_die();
   
    write("You have expelled " + ob->query_name() + " from the Guild of "
          + "Gladiators.\n");
    ob->catch_msg(QCTNAME(this_player()) + " has excommunicated you from "+
        "the Guild of Gladiators.\n");
    if (cuir = present(CUIR_ID, ob)) 
    {
        cuir->remove_object();
        ob->catch_msg("Your cuirasse decays into dust.\n");
    }
    return 1;
}

/*
 * Function name:   do_join
 * Description:     allows Roke-wizards to recruit others to the Roke guild
 * Arguments:       name of player
 * Returns:         1 for successful, else 0
 */
static int
do_join(string str)
{
    object ob;

    if (!str)
        return 0;
    if (!is_a_glad(this_player()) || this_player()->query_wiz_level()
         <= WIZLEV_APPRENTICE) {
        notify_fail("You must be a Roke wizard to do that.\n");
        return 0;
    }
    if (is_founder(this_player()->query_real_name()))
        ob = find_player(str);
    else
        ob = present(str, environment(this_player()));
    if (!ob || !interactive(ob)) {
        notify_fail("No player with that name.\n");
        return 0;
    }
    if (ob == this_player()) {
        notify_fail("Sharing wizdom with oneself is too deep.\n");
        return 0;
    }
    if (!this_object()->join_to_guild(ob, 1)) {
        write("Failed to enlight " + ob->query_name() + ".\n");
        return 1;
    }
    clone_object(GLAD_DIR+"cuirasse")->move(ob);
    write("You magically duplicate your cuirasse and let " + 
        ob->query_name() + " share the joy of it!\n");
    ob->catch_msg(QCTNAME(this_player()) + " gives you a nice new cuirasse!\n");
    ob->catch_msg("You are now a member of the famed Guild of Gladiators.\n");
    return 1;
}

static int
do_gladsoul(string str)
{
   object *ul;
   string *souls;
   int i, silence;
   
   if (!is_founder(this_player()->query_real_name()))
      return 0;
   
   if (str == "-s")
      silence = 1;
   else
      silence = 0;
   
   seteuid(getuid());
   ul = users();
   
   for (i = 0; i < sizeof(ul); i++) 
   {
      if (ul[i] == this_player())
         continue;
      
      souls = ul[i]->query_cmdsoul_list();
      
      if (member_array(GLAD_SOUL, souls) == -1)
         continue;
      
      if (!silence)
         tell_object(ul[i], "You become aware of new things as a Gladiator.\n");
      ul[i]->update_hooks();
      write("Gave " + capitalize(ul[i]->query_real_name())
         + " a new soul.\n");
   }
   write("Ok.\n");
   return 1;
}

/*
* Function name:   do_renew
* Description:     Replace all cuirasses in the game. This can be used to give
*                  everyone in the game a new cuirasse after an update has been
*                  made.
* Arguments:       str: If the argument was "-s", change the cuirasses without
*                       any noise, so the change will pass unnoticed.
*/
static int
do_renew(string str)
{
   object cuir, player_ob;
   object *list;
   int    i, silence, test;
   
   if (!is_founder(this_player()->query_real_name()))
      return 0;
   if (!str)
      silence = 0;
   else if (str == "-s")
      silence = 1;
   
   list = filter(users(), "has_a_cuirasse", this_object());
   i = 0;
   for (i = 0; i < sizeof(list); i++) {
      /* Do not remove the cuirasse of the owner... He probably already did it.
      */
      if ((player_ob = list[i]) != this_player()) {
         cuir = present(CUIR_ID, player_ob);
         cuir->remove_object();
         cuir = clone_object(GLAD_DIR+"cuirasse");
         if (silence)
            cuir->set_silent();
         cuir->move(player_ob);
         if (!silence)
            tell_object(player_ob, this_player()->query_name()
            + " gives you a brand new cuirasse.\n");
         write("Replaced the cuirasse of "
            + capitalize(player_ob->query_real_name()));
         if (silence)
            write(" silently");
         write(".\n");
        }
   }
   return 1;
}

/*
* Function name:   has_a_cuirasse
* Description:     Check if the object has a cuirasse
   * Arguments:       obj: Object to check
*/
int
has_a_cuirasse(object obj)
{
   return present(CUIR_ID, obj) ? 1 : 0;
}

/*
* Function name:   set_silent
* Description:     Make sure the cuirasse makes no sounds when replaced
*/
int
set_silent()
{
   no_noise = 1;
}

void
create_armour()
{
   if (!IS_CLONE)
      return;
   
   set_name("cuirasse");
   add_name("g_cuirasse");
   add_name(CUIR_ID);
   set_long(break_string("This expertly crafted cuirasse is the first item "+
	"you obtained when you joined the famed Guild of Gladiators. For "+
	"more help do <help gladiator>.\n",78));
   set_short("cuirasse");
   
   set_ac(0); /* My, its a tough cuirasse! */
   set_at(A_NECK);
   
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_NO_DROP, "Ouch! It's too painful to drop.\n");
   add_prop(OBJ_I_WEIGHT, 670);
   
   seteuid(getuid());
}

string
query_auto_load()
{
    return MASTER + ":" + killed;
}

void
init_arg(string arg)
{
    killed = atoi(arg);
}

void
init()
{
   /* Check if it is the owner who causes this init */
      if (this_player() == environment()) {
      add_glad_actions();
      call_out("init_msg", 1, this_player());
   }
}

void
add_glad_actions()
{
   add_action("do_give_explanation","help",0);
   add_action("do_show_members", "brothers", 0);
   add_action("do_show_members", "br", 0);
   if(is_founder(environment()->query_real_name())) {
      add_action("do_renew","grenew",0);
      add_action("do_gladsoul","gsoul",0);
      add_action("do_join", "enlight", 0);
      add_action("do_excom", "expel", 0);
   }
}

void
init_msg(object who)
{
   int i;
   object *some_arr;
   
   /* Selfdestruct if not held */
      if (!living(who))
      remove_object();
   
   if (who && !used) {
      if (is_founder(who->query_real_name())
            || is_member(who->query_real_name())) {
#ifndef DEBUG
            add_prop(OBJ_I_NO_GIVE,1);  /* Normally non giveable        */
#endif
            add_prop(OBJ_I_WEIGHT,670); /* A light cuirasse, 100 grams */
         add_prop(OBJ_I_NO_DROP,1);  /* Normally non droppable       */
         add_prop(OBJ_I_VOLUME,20);  /* A small ring, 0.02 litres    */
         add_prop(OBJ_I_NO_INS,1);   /* It is not a container        */
         
         if (is_a_glad(environment()) && !no_noise)
        who->catch_msg("\nYou sense something alien in your "+
           "mind; Something familiar yet never quite this "+
           "strong. It seems to be saying something:\n"+
           "'I am King Kalak: Tyrant of Tyr, Master of Athas, "+
           "Lord of the Gladiators. For to long I have turned "+
           "a blind eye to those who serve me, but no longer. "+
           "So that you may know and respect my power, I will "+
           "strip you of yours.\n Yes, until you reswear your "+
           "fealty to me by updating your membership in the "+
           "room of joining, you may not perform any function "+
           "of your profession. Beyond that: Wait and see.'\n");
         else if (!no_noise)
            who->catch_msg("Hail, Gladiator!\n");
#ifdef DEBUG
            who->catch_msg("Your name: " +
            capitalize(environment()->query_real_name())+", ");
         
         if (is_founder(environment()->query_real_name()))
            who->catch_msg("a guildmaster");
         else
            who->catch_msg("not a guildmaster");
         
         if (is_a_glad(who))
            who->catch_msg(" and a true Gladiator.\n");
         else
            who->catch_msg(", but not a true Gladiator.\n");
#endif
            
         /* Test for the soul */
         some_arr = who->query_cmdsoul_list();
         if (member_array(GLAD_SOUL,some_arr) == -1) {
            /* Filter out all known command souls */
            some_arr = filter(some_arr,"known_souls",this_object());
            
            if (!some_arr)
               some_arr = ({ });
            
            
            /* Remove all command souls */
            for (i=0; i< sizeof(some_arr); i++)
            who->add_cmdsoul(some_arr[i]);
            
            /* Put the Gladiator-soul in front of the other souls */
            who->add_cmdsoul(GLAD_SOUL);
            
            /* Add all the other command souls */
            for (i=0; i< sizeof(some_arr); i++)
            who->add_cmdsoul(some_arr[i]);
            
            who->update_hooks(); /* And make the souls active */
          }
       }
      else {
         who->catch_msg("You are not allowed to use the cuirasse. " +
            "You're not a Gladiator!\n" +
            "The cuirasse decays into dust.\n");
         remove_object();
         remove_object();          /* Just in case */
         return;
       }
   }
   used = 1;
}

int
ghost()
{
   return environment()->query_ghost();
}

int
do_show_members()
{
   string sh_name, sh_title, str;
   int i, cnt, lsize;
   object player_ob, active, cuir, *list;
   
   list = filter(users(),"is_member",this_object());
   lsize = sizeof(list);
   cnt = 0;
   write("Rumours have it that the following Gladiators are abroad:\n");
   
   for (i=0; i < lsize; i++) {
      str = 0;
      player_ob = list[i];
      sh_name = capitalize(player_ob->query_real_name());
      
      if (player_ob->short()) {
         if (!(sh_title = player_ob->query_title()))
            sh_title = "";
         
         /* QCNAME does not work with write() */
         str = ": " + player_ob->query_name() + " " + sh_title;
         cnt++;
        }
      cuir = present(CUIR_ID, player_ob);
      
      if (!(player_ob->short()) && 
            environment()->query_wiz_level()> WIZLEV_APPRENTICE) {
         str = ": (" + player_ob->query_name() + ")";
         cnt++;
        }
      if (cuir && player_ob->short()) {
         /* The person has a cuirasse, but is he online? */
         if (player_ob->query_ghost())
            str += " <deceased>";
        }
      else if (player_ob->short())
         str += " (* no cuirasse *)";
      if (str)
         environment()->catch_msg(str + "\n");
   }
   write("Total number of active Gladiators are: "+cnt+".\n");
   return 1;
}

int
fail_ghost()
{
   write("You fail.\n");
   return 1;
}

int
do_give_explanation(string str)
{
   if (ghost())
      return fail_ghost();
   if (!str)
      return 0;
   
   str = lower_case(str);
   
   if (id(str) && !is_a_glad(environment()))
      {
      write("You do not bear a proper Gladiator title!\n" +
         "Your title must contain \" Gladiator\" to get help.\n" +
         "Among the things you can do are "+
         "\"hail\", \"holograph\" and such.\n");
      return 1;
   }
   
   if (str == "gladiator") {
      seteuid(getuid());
      cat(GLAD_DIR+"g_help");
      return 1;
   }
   return 0;
}

void
more_list()
{
   string emptystr, fillstr;
   int    array_size, count, lastlen;
   
   emptystr = "                     ";
   array_size = sizeof(more_array);
   count = lastlen = 0;
   while ((more_pos < array_size) && (count < 88)) {
      if ((count % 4) == 0)
         write(more_array[more_pos]);
      else
         write(extract(emptystr,0,19-lastlen) + more_array[more_pos]);
      lastlen = strlen(more_array[more_pos++]);
      if ((count++ % 4) == 3)
         write("\n");
   }
   if (more_pos == array_size) {
      write("\n");
      return;
   }
   write("<More>   ");
   input_to("wait_for_more");
}

void
wait_for_more(string str)
{
   if (str == "q" || str == "Q")
      return;
   more_list();
}

public void
report_kill(int which)
{
    int new = which | killed;
    if (!(which & GURU_DONE) || new == killed || !(new & GOT_QUEST))
        return;
    ROKE_LOG("glad_guru", 
	     capitalize(environment(this_object())->query_real_name()) +
	     " got bit " + which + " giving total " + new + "\n");
    killed = new;
}

public int
guru_done()
{
    return killed == GURU_DONE;
}

public int
got_quest()
{
    return killed & GOT_QUEST;
}

/* Function used in filter, but not defined.  --LA */
known_souls() {return 0; }
