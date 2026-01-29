inherit "/std/object";

#include <tasks.h>

/* 
 *    This is currently the first version of the cloak, having been taken
 *    from Plugh's and Mylos's work on the mage_guild of the Emerald.
 *                      Mylos   8.4.93 
 *    Kat re-wrote the messages for the tele (do_message2()) on 9-39-93.
 */

#define DEBUG   1

#include "default.h"

#define IS_SPECIAL      ({ "tintin", "glindor", "mecien", "plugh", \
				"mrpr", "mercade", "olorin" })

/* Unique id to identify the guildobject */
#define CLOAK_ID    "vamp_cloak"


/* outcomment this if you don't want it */
#define OWN_SOUL        (SOUL_DIR + "vamp_soul")
#define PUN_SOUL        (SOUL_DIR + "vamp_pun")

static int      used,
                no_noise,       /* True if replace is to be silently */
                more_pos;

static string   filter_str,
                *more_array;
string          *banned;

void    add_vamp_actions();
void    init_msg(object who);
int     is_a_vamp(object owner);
int     ghost();
int     fail_ghost();
void    more_list();
void    wait_for_more(string str);
int     cloak_info();
int     is_founder(string str);
int     is_member(mixed who);
int     is_a_vamp(object ob);
int     set_silent();
int     has_a_cloak(object obj);

#ifdef DEBUG
#define AUTOPOS         OBJECT_DIR + "vamp/newcloak:"
#define CLOAKPOS         OBJECT_DIR + "vamp/newcloak"
#define LISTPOS         OBJECT_DIR + "vamp/newvampli"
#else
#define AUTOPOS         OBJECT_DIR + "vamp/cloak:"
#define CLOAKPOS         OBJECT_DIR + "vamp/cloak"
#define LISTPOS         OBJECT_DIR + "vamp/vampli"
#endif

/*
 * Function name:   is_founder
 * Description:     Test if the person is a member of the Emerald domain or
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

/*
 * Function name:   is_member
 * Description:     Test if the person is a member of the Vamp guild
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
    if (ob->test_bit(DOMAIN_NAME, VAMP_GROUP, VAMP_BIT))
        return 1;
    return 0;
}

/*
 * Function name:   is_a_vamp
 * Description:     Test whether this person is also bearing a Vamp title.

* Arguments:       owner: The person to check.
 * Returns:         1 if the person is a Vamp, 0 otherwise.
 */
int
is_a_vamp(object ob)
{
    string str;

    if (ob->query_wiz_level() > WIZLEV_NORMAL)
        return 1;
    str = ob->query_title();
    if (str && sscanf(str, "%s Elements%s", str, str) == 2 ||
	sscanf(str, "%s Planes%s", str, str) == 2)
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

/*
 * Function name:   join_to_guild
 * Description:     Join someone to the Vamp guild. The person's
 *                  guildbit will be set, and necessary Vamp-stuff will be
 *                  added. It will not add the cloak, tough.
 * Arguments:       ob: player to be joined
 * Returns:         1 if successful, 0 otherwise.
 */
static int
join_to_guild(object ob, int check)
{
    object shadow;
    int i;

    seteuid(getuid());

    if (!ob->set_bit(VAMP_GROUP, VAMP_BIT)) {
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

    ob->set_guild_pref(SS_OCCUP, GUILD_TAX);
    if (check)
        write("-> Set guild-tax.\n");

    if (ob->query_guild_member(GUILD_NAME)) {
        if (check)
            write("-> Player already has a guild shadow.\n");
    }
    else {
        shadow = clone_object(ROOM_DIR + "vamp/vamp_sh");
        i = shadow->shadow_me(ob, GUILD_TYPE, GUILD_STYLE, GUILD_NAME);
        if (i == 1) {
            if (check)
                write("-> Successfully added the guild shadow.\n");
                log_file("guild", "Added a guild shadow.\n");
        }
        else {
            if (check) {
                write("-> Failed to add the guild shadow.\n");
                write("-> Aborting...\n");
            }
            shadow->remove_object();
            return 0;
        }
    }
    if (ob->query_wiz_level() == WIZLEV_MORTAL) {
        if (add_soul_at_top(OWN_SOUL, ob)) {
            if (check)
                write("-> Successfully added the guild soul.\n");
        }
        else {
            if (check) {
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
    object ob, cloak;
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
        notify_fail("Lady Freyja is very fond of " + ob->query_name() + 
        " and won't let you do it.\n");
        return 0;
    }
    seteuid(getuid());

    if (!ob->clear_bit(VAMP_GROUP, VAMP_BIT)) {
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
    if (member_array(OWN_SOUL, list) >= 0) {
            write("-> Guild soul found ");
        if (ob->remove_cmdsoul(OWN_SOUL))
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
    ob->set_race_name("vampyr");
    ob->heal_hp(-100000);
    ob->do_die();
   
    write("You have expelled " + ob->query_name() + " from the Vampyr "
          + "guild.\n");
    ob->catch_msg(QCTNAME(this_player()) + " has excommunicated you from "+
        "the Vampyr guild.\n");
    if (cloak = present(CLOAK_ID, ob)) 
    {
        cloak->remove_object();
        ob->catch_msg("Your cloak fades into black smoke.\n");
    }
    return 1;
}

/*
 * Function name:   do_enlight
 * Description:     allows emerald-wizards to recruit others to the Emerald 
guild
 * Arguments:       name of player
 * Returns:         1 for successful, else 0
 */
static int
do_enlight(string str)
{
    object ob;

    if (!str)
        return 0;
   if(!is_founder(TP->query_real_name()) || TP->query_wiz_level()
         <= WIZLEV_APPRENTICE) {
        notify_fail("You must be a Emerald wizard to do that.\n");
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
    clone_object(CLOAKPOS)->move(ob);
    write("You magically duplicate your cloak and let " + 
        ob->query_name() + " share the joy of it!\n");
    ob->catch_msg(QCTNAME(this_player()) + " gives you a wonderful cloak!\n");
    ob->catch_msg("You are now a member of the Vampyr guild.\n");
    return 1;
}

static int
do_remove_list(string str)
{
    int index;

    if (!is_founder(this_player()->query_real_name()))
        return 0;

    if (!str || str == "?") {
        write("Usage: " + query_verb() + " <playername>\n"
        + "This will remove <playername> from the list of banned people.\n");
    }

    str = capitalize(lower_case(str));
    restore_object(LISTPOS);

    if ((index = member_array(str, banned)) != -1) {
        /* Delete the name from the members list */
        banned = exclude_array(banned, index, index);
        save_object(LISTPOS);
        write("Removed " + str + " from the banish-list.\n");
        return 1;
    }
    write("Could not find " + str + " in the banish-list.\n");
    return 1;
}

static int
do_add_list(string str)
{
    if (!is_founder(this_player()->query_real_name()))
        return 0;

    str = lower_case(str);

    if (!str || str == "?") {
        write("Usage: " + query_verb() + " <playername>\n"
            + "This will add <playername> to the list of banned people.\n");
    }

    restore_object(LISTPOS);
    str = capitalize(lower_case(str));

    if (!banned)
        banned = ({ });
    if (member_array(str, banned) != -1) {
        write(str + " already is in the banish-list.\n");
        return 1;
    }
    banned += ({ str });
    save_object(LISTPOS);
    write("Added " + str + " to the banish-list.\n");
    return 1;
}

static int
do_show_list(string str)
{
    string *tmp_array, filter_str;

    if (!is_founder(this_player()->query_real_name()))
        return 0;

    /* Analyse the input-string */
    if (!str)
        str = "";

    str = lower_case(str);

    if (str == "?") {
        write("\nCOMMAND:   Showlist\n\n"
              + "FORMAT:\n   showlist [name]\n\n"
              + "SYNOPSIS:\n");
        write("   Showlist shows all members of the Vampyr guild who are\n"
              + "   registered in the file " + LISTPOS + ".o .\n"
              + "   In that file all banished Vampyr are kept.\n"
              + "     name    Show, if present the members whose name "
              + "starts with\n");
        write("             with the string 'name'. If you do not specify "+
                "a name,\n"
              + "             all names will be shown.\n"
              + "EXAMPLES:\n");
        write("   showlist          Show all banished members.\n"
          + "   showlist t        Will show all banned members whose "+
                "name\n                     starts with 'T'\n");
        return 1;
    }

    restore_object(LISTPOS);
    if (str != "")
        filter_str = capitalize(str);
    else
        filter_str = "";

    tmp_array = filter_array(banned, "partial_name_filter", this_object());

    write("\nTotal number of banished members: " + sizeof(banned) + ".\n");
    write("Banished members of the Vampyr guild are:\n");

    more_array = sort_array(tmp_array, "less_eq_func", this_object());
    more_pos = 0;
    more_list();
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

static int
do_news(string str)
{
    if (!is_founder(this_player()->query_real_name()))
        return 0;
    cat(HELP_DIR + "NEWS");
    return 1;
}

static int
do_newsoul(string str)
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

    for (i = 0; i < sizeof(ul); i++) {
        if (ul[i] == this_player())
            continue;

        souls = ul[i]->query_cmdsoul_list();

        if (member_array(OWN_SOUL, souls) == -1)
            continue;

        if (!silence)
            tell_object(ul[i], "Your awareness of the undead world " +
                        "has changed.\n");
        ul[i]->update_hooks();
        write("Gave " + capitalize(ul[i]->query_real_name())
              + " a new soul.\n");
    }
    write("Ok.\n");
    return 1;
}

/*
 * Function name:   do_replace
 * Description:     Replace all cloaks in the game. This can be used to give
 *                  everyone in the game a new cloak after an update has been
 *                  made.
 * Arguments:       str: If the argument was "-s", change the cloaks without
 *                       any noise, so the change will pass unnoticed.
*/
static int
do_renew(string str)
{
    object cloak, player_ob;
    object *list;
    int    i, silence, test;

    if (!is_founder(this_player()->query_real_name()))
        return 0;
    if (!str)
        silence = 0;
    else if (str == "-s")
        silence = 1;

    list = filter_array(users(), "is_member", this_object());
    i = 0;
    for (i = 0; i < sizeof(list); i++) {
     /* Do not remove the cloak of the owner... He probably already did it. */
        if ((player_ob = list[i]) != this_player()) {
            cloak = present(CLOAK_ID, player_ob);
            cloak->remove_object();
            cloak = clone_object(CLOAKPOS);
            if (silence)
                cloak->set_silent();
            cloak->move(player_ob);
            if (!silence)
                player_ob->catch_msg(QCTNAME(TP) + " gives you a brand "+
			"new cloak.\n");
            write("Replaced the cloak of "
                  + capitalize(player_ob->query_real_name()));
            if (silence)
                write(" silently");

            write(".\n");
        }
    }
    return 1;
}

/* 
 * Function name:   do_punish
 * Decription:      To punish the player by removing some of his/her
 *                  commands
 * Arguments:       str, the player
 */
int
do_punish(string str)
{
    object ob;

    if (!is_founder(this_player()->query_real_name()))
        return 0;

    ob = find_living(str);

    ob->catch_msg("You feel empty and strange within.\n");

    ob->remove_cmdsoul(OWN_SOUL);
    if(add_soul_at_top(PUN_SOUL, ob))
    {
       ob->catch_msg("You are being punished by the Family.\nYou have "+
                "now lost the savage, suck and vbite abilities.\n");
       write("You gave " + capitalize(ob->query_real_name())
              + " a punishment soul.\n");
       ob->update_hooks();
       return 1;
    }
    notify_fail("Failed to give punishment soul.\n");
    return 0;
}

/*
 * Function name:   do_forgive
 * Decription:      Give the player back their normal soul.
 * Arguments:       str, the player
 */
int
do_forgive(string str)
{
   object ob;
 
   if(!is_founder(this_player()->query_real_name()))
        return 0;
   ob = find_living(str);

   ob->catch_msg("Your punishment is at an end.\n");
   ob->remove_cmdsoul(PUN_SOUL);

   if(add_soul_at_top(OWN_SOUL, ob))
   {
      tell_room(ENV(ob), QCTNAME(TP)+" forgives "+QTNAME(ob)+".\n", TP, ob);
      write("You forgave " +QCTNAME(ob) + ".\n");
      ob->update_hooks();
      return 1;
   }
   notify_fail("Unable to forgive "+QCTNAME(ob)+".\n");
   return 0;
}


/*
 * Function name:   has_a_cloak
 * Description:     Check if the object has a cloak
 * Arguments:       obj: Object to check
 */
int
has_a_cloak(object obj)
{
    return present(CLOAK_ID, obj) ? 1 : 0;
}

/*
 * Function name:   set_silent
 * Description:     Make sure the cloak makes no sounds when replaced
 */
int
set_silent()
{
    no_noise = 1;
}

void
create_object()
{
    if (!IS_CLONE)
        return;

    set_name("cloak");
    add_name(CLOAK_ID);
    set_long("@@cloak_desc");
    set_adj("long");
    add_adj("magical");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 100);

    seteuid(getuid());
}

string
cloak_desc()
{
    string light;

    if (query_prop(OBJ_I_LIGHT))
        light = " It is emanating a light source all around you.";

    else
        light = "";
    return break_string("It is a large black cloak, easily covering "+
                "your entire body. It is surprisingly light and woven from "+
                "a strange black metallic material." + light + "\n",76);
}

string
query_auto_load()
{
    return AUTOPOS + "0";
}

void
init_arg(string str)
{
}

void
init()
{
    /* Check if it is the owner who causes this init */
    if (this_player() == environment()) {
        add_vamp_actions();
        call_out("init_msg", 1, this_player());
    }
}

void
add_vamp_actions()
{
    add_action("light_cloak", "moroi");
    add_action("extinguish_cloak", "vocat");
    add_action("do_give_explanation","help", 0);
    add_action("do_destroy_cloak", "rip", 0);
    add_action("do_message2", "telepath", 0);
    add_action("do_message2", "tele", 0);
    add_action("do_vmessage2", "empath", 0);
    add_action("do_vmessage2", "emph", 0);
    add_action("do_show_members", "vlist", 0);
    add_action("do_show_members", "vamplist", 0);
    add_action("do_excom", "excom", 0);
    if (is_founder(environment()->query_real_name())) {
        add_action("do_enlight", "undead", 0);
        add_action("do_cloak", "cl", 0);
        add_action("do_show_list", "vwho",0);
        add_action("do_remove_list", "rmvamp",0);
        add_action("do_add_list", "addvamp",0);
        add_action("do_renew", "renew",0);
        add_action("do_news", "vnews",0);
        add_action("do_newsoul", "nsoul", 0);
        add_action("do_punish", "punish", 0);
        add_action("do_forgive", "forgive", 0);
    }
}

static int
do_cloak(string str)
{
    object cloak, name;
    object list;
    int    i, silence, test;

    if (!is_founder(this_player()->query_real_name()))
        return 0;

    notify_fail("That person isn't here!\n");
    if(!str || !strlen(str))
        return 0;

    name = find_living(str);

    notify_fail("That person is not in the game at present.\n");
    if(!name)
        return 0;

    setuid();
    seteuid(getuid());
    cloak = clone_object(CLOAKPOS);

    if(!present(cloak, name))
    {
       cloak->move(name, 1);
       name->catch_msg(QCTNAME(TP)+" gives you a brand new cloak.\n");
       TP->catch_msg("Replaced the cloak of "+QTNAME(name)+".\n");
       return 1;
    }
    notify_fail("That person already has a cloak.\n");
    return 0;
}

int
light_cloak()
{
    if(this_player()->resolve_task(TASK_SIMPLE, ({ TS_WIS, SS_AWARENESS }) ) > 0 )
    {
        if(query_prop(OBJ_I_LIGHT))
        {
           notify_fail("The cloak is already emanating light.\n");
           return 0;
        }
        add_prop(OBJ_I_LIGHT, 1);
        write("You focus power on the cloak, and it begins to emanate light.\n");
        say(QCTNAME(this_player()) + " focuses " +
        this_player()->query_possessive() + " power, and the cloak begins to "+
        "emanate light.\n");
        TP->add_mana(-5);
        call_out("light_fail", 120);
        return 1;
    }
    notify_fail("You can't seem to focus your power correctly.\n");
    return 0;
}

int
extinguish_cloak()
{
    if(!query_prop(OBJ_I_LIGHT))
    {
        notify_fail("The cloak isn't emanating light.\n");
        return 0;
    }
    else
    write("The light from the cloak dies away and you are plunged into "+
        " darkness.\n");
    say(QCTNAME(this_player()) + " closes "+this_player()->query_possessive()+
                " eyes, and "+this_player()->query_possessive() + " cloak "+
                "stops emanating light.\n");
    add_prop(OBJ_I_LIGHT, 0);
    return 1;
}

void
light_fail()
{
   if(TO->query_prop(OBJ_I_LIGHT))
   {
      write("The light from the cloak slowly dies away.\n");
      tell_room(ENV(TP), "The light from "+QTNAME(this_player())+"'s "+
        "cloak dies away.\n", TP);
      add_prop(OBJ_I_LIGHT, 0);
   }
}

void
init_msg(object who)
{
  int i, lsize, j;
  object *some_arr, *list;
  object player_ob;
  string sh_name, dummy1, dummy2, title;

  list = filter_array(users(), "is_member", this_object());
  lsize = sizeof(list);

  title = TP->query_title();

  for (j = 0; j < lsize; j++)
  {
    if((player_ob = list[j]) != this_player())
    {
      sh_name = capitalize(TP->query_real_name());
      if(!(extract(sh_name, -2) == "jr"))
      {
	if(present("_vamp_master_object_", TP)) {
	list[j]->catch_msg(sh_name+" arises from slumber in the Nether "+
		"Planes.\n");
	}
  	if(present("_vamp_lord_object_", TP)) {
	list[j]->catch_msg(sh_name+" enters the Prime Planes from rest in "+
		"the Ethereal Planes.\n");
	}
	if(present("_vamp_regal_object_", TP)) {
	list[j]->catch_msg("Your blood warms slightly as "+sh_name+" arises "+
		"from the Vampyr's slumber.\n");
	}
	if(present("_vamp_ruler_object_", TP)) {
	list[j]->catch_msg("Your undead blood skips a beat as Mylos the "+
		"Father rises.\n");
   	}
  	if(sscanf(title, "%s Deaths Elements%s", dummy1, dummy2) == 2) {
	list[j]->catch_msg(sh_name+" awakens from the Elements of Death.\n");
	}
	if(sscanf(title, "%s Dark Elements%s", dummy1, dummy2) == 2) {
	list[j]->catch_msg("The Dark Elements grow deeper as "+sh_name+
	   " rises from rest.\n");
  	}
	else if(sscanf(title, "%s Shadow Elements%s", dummy1, dummy2) == 2) {
        list[j]->catch_msg("The Shadow Elements flicker as "+sh_name+
	   " enters unlife again.\n");
   	}
      }
    }
  }

  /* Selfdestruct if not held */
  if (!living(who))
        remove_object();

  if (who && !used) {
        if (is_founder(who->query_real_name())
            || is_member(who->query_real_name())) {
#ifndef DEBUG
            add_prop(OBJ_I_NO_GIVE,1);  /* Normally non giveable        */
#endif
            add_prop(OBJ_I_WEIGHT,1344); /* A very light cloak, 1344 grams */
            add_prop(OBJ_I_NO_DROP,1);   /* Normally non droppable       */
            add_prop(OBJ_I_VOLUME, 2760);/* A small cloak, 0.02 litres    */
            add_prop(OBJ_I_NO_INS,1);    /* It is not a container        */

            if (is_a_vamp(environment()) && !no_noise)
                who->catch_msg("Welcome, Undead creature.\n");
            else if (!no_noise)
                who->catch_msg("Welcome, creature of the night.\n");

            /* Test for the soul */
            some_arr = who->query_cmdsoul_list();
            if (member_array(OWN_SOUL,some_arr) == -1) {
                /* Filter out all known command souls */
                some_arr = filter_array(some_arr,"known_souls",this_object());

                if (!some_arr)
                    some_arr = ({ });


                /* Remove all command souls */
                for (i=0; i< sizeof(some_arr); i++)
                    who->add_cmdsoul(some_arr[i]);
 
                /* Put the Emerald-soul in front of the other souls */
                who->add_cmdsoul(OWN_SOUL);
 
                /* Add all the other command souls */
                for (i=0; i< sizeof(some_arr); i++)
                    who->add_cmdsoul(some_arr[i]);

                who->update_hooks(); /* And make the souls active */
            }
        }
        else {
            who->catch_msg("You are not allowed to use the cloak. " +
                           "You're not a Vampyr!\n" +
                           "The cloak fades into black smoke.\n");
            remove_object();
            remove_object();
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
  object player_ob, active, cloak, *list;

  list = filter_array(users(),"is_member",this_object());
  lsize = sizeof(list);
  cnt = 0;

  tell_room(ENV(TP), QCTNAME(TP)+" narrows "+POS(TP)+" eyes, pondering "+
	"something important.\n", TP);
  write("Active Vampyrs are:\n");

  for (i=0; i < lsize; i++) 
  {
    str = "";
    player_ob = list[i];

    /* Leave invisible people invisible to players */
    if (!(player_ob->query_invis()) ||
         this_player()->query_wiz_level() >= WIZLEV_APPRENTICE)
    {
      /* Everyone knows one another in the Family */
      if (!(sh_name = player_ob->query_name()))
            sh_name = "";

      if (!(sh_title = player_ob->query_title()))
            sh_title = "";

      str = sh_name + " " + sh_title;

      if(!(cloak = present(CLOAK_ID, player_ob)))
      {
	str += " (* no cloak *)";
      }

      if (player_ob->query_ghost())
        str += " <deceased>";

      /* Mark invisible players for wizards */
      if (player_ob->query_invis() &&
        this_player()->query_wiz_level() >= WIZLEV_APPRENTICE)
      str = "(" + str + ")";
      cnt++;      /* And another VAMPYR! */

      this_player()->catch_msg(": " + str + "\n");
    }
  }
  write("Total number of active Vampyrs are: "+cnt+".\n");
  return 1;
}

int
do_message2(string str)
{
    string who, c_who, msg, tell_str, known;
    int is_wiz;
    object target, cloak;

    if (!str || !is_member(capitalize(environment()->query_real_name())))
        return 0;

    if ((sscanf(str, "%s %s", who, msg) != 2) || !who)
        return 0;

    is_wiz = this_player()->query_wiz_level();
    if (!is_wiz && this_player()->query_mana() < 5) {
        write("You do not have enough mental power for that!\n");
        return 1;
    }

    who = lower_case(who);
    target = find_player(who);
    if (!target) {
        write("No such player!\n");
        return 1;
    }
    c_who = capitalize(who);
    if (!is_member(who)) {
        write(c_who + " is not a Vampyr!\n");
        return 1;
    }
    if(target->query_invis())
    {
        write(c_who + " is not presently on.\n");
        return 1;
    }
    if (!(cloak = present(CLOAK_ID, target))) {
        write(c_who + " does not have a cloak!\n");
        return 1;
    }
    if (environment()->query_wiz_level() <= target->query_wiz_level() 
        && !target->short()) {
        write("No such player!\n");
        return 1;
    }

    /* Break the text and put stuff in between for yourself */
    write("You feel your thoughts gripping " + c_who + "'s mind, saying:\n"+
          implode(explode(break_string(msg, 63-strlen(c_who)),"\n"),
                  sprintf("\n%*s  ",9+strlen(c_who),"")) + "\n");

    /* Break the text and put stuff in between for the recipient */
    tell_str = ("You hear the voice of " + 
    capitalize(environment() -> query_real_name())  + ", ripping " + 
    "through your thoughts, telling you:  \n");
   tell_str += break_string((msg + "\n"), 70);
   target->catch_msg(tell_str);

    /* Reduce the mana */
    if (!is_wiz)
        this_player()->add_mana(-5);
    return 1;
}

int
do_vmessage2(string str)
{
    string who, c_who, msg, tell_str, known;
    int is_wiz;
    object target, cloak;

    if (!str || !is_member(capitalize(environment()->query_real_name())))
        return 0;

    if ((sscanf(str, "%s %s", who, msg)) != 2 || !who)
        return 0;

    is_wiz = this_player()->query_wiz_level();

    if (!is_wiz && this_player()->query_mana() < 5) {
        write("You do not have enough mental power for that!\n");
        return 1;
    }

    who = lower_case(who);
    target = find_player(who);
    if (!target) {
        write("No such player!\n");
        return 1;
    }
    c_who = capitalize(who);
    if (!is_member(who)) {
        write(c_who + " is not a vampyr!\n");
        return 1;
    }
    if(target->query_invis())
    {
        write(c_who + " is not on at present.\n");
        return 1;
    }
    if (!(cloak = present(CLOAK_ID, target))) {
        write(c_who + " does not have a cloak!\n");
        return 1;
    }
    if (environment()->query_wiz_level()<=target->query_wiz_level() 
        && !target->short()) {
        write("No such player!\n");
        return 1;
    }
    /* Break the text and put stuff in between for yourself */
    write(break_string("You tell " + c_who + " that you " + msg + "\n", 76));

    /* Break the text and put stuff in between for the recipient */
        tell_str = ("Your cloak suddenly starts to feel warm.\n"+
                            "An image forms in front of you of "+
                            capitalize(environment()->query_real_name()) +
                                ".\n");
    tell_str += break_string("The image tells you that it " + msg + "\n",76);
    target->catch_msg(tell_str);
    /* Reduce the mana */
    if (!is_wiz)
        this_player()->add_mana(-5);
    return 1;
}

int
fail_ghost()
{
    write("You fail.\n");
    return 1;
}

static int
do_destroy_cloak(string str)
{
    if (id(str)) {
        write("As you rip the cloak, it fades into black smoke.\n");
        say(QCTNAME(this_player()) + " rips " + 
        environment()->query_possessive() + " cloak...\n");
        remove_object();
        return 1;
    }
    return 0;
}

int
do_give_explanation(string str)
{
    if (ghost())
        return fail_ghost();
    if (!str)
        return 0;

    str = lower_case(str);

    if (id(str) && !is_a_vamp(environment()))
    {
        write("You do not bear a proper Vampyr title!\n" +
              "Your title must contain \" Vampyr\" to get help.\n" +
              "Among the things you can do are "+
                "\"telepath\", \"empath\" and such.\n");
        return 1;
    }

    if (id(str)) {
        cloak_info();
        return 1;
    }

    if (str == "guild vlevels") {
        seteuid(getuid());
        cat(HELP_DIR + "vlvl_info.txt");
        return 1;
    }
    if(str == "guild align") {
        seteuid(getuid());
        cat(HELP_DIR + "align");
        return 1;
    }
    if(str == "guild vamp") {
        seteuid(getuid());
        cat(HELP_DIR + "vamp");
        return 1;
    }
    return 0;
}

int
cloak_info()
{
    seteuid(getuid());

    if (is_a_vamp(environment())) {
        cat(HELP_DIR + "cloakhelp1.txt");
        cat(HELP_DIR + "cloakhelp2.txt");
        cat(HELP_DIR + "cloakhelp3.txt");
    }
    else
        cat(HELP_DIR + "cloakhelp4.txt");

    if (is_founder(environment()->query_real_name()))
        cat(HELP_DIR + "cloakhelp5.txt");

    cat(HELP_DIR + "cloakhelp6.txt");
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
