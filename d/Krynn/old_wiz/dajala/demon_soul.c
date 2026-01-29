/*
 *  D_Soul.c
 *
 *  This is the command soul of the DemonSpawn Guild
 *
 */

inherit "/cmd/std/command_driver";

#include "/d/Immortal/std/domain.h"
#include "/d/Immortal/shanar/Caverns/Guild/demons.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

/*****************************************************************************
 * Soul identifying and autoloading
 *****************************************************************************/

string get_soul_id() { return "DemonSpawn"; }

int query_cmd_soul() { return 1; }

/*****************************************************************************
 * The list of verbs and functions. Please add new in alfabetic order.
 *****************************************************************************/

mapping
query_cmdlist()
{
    return ([
    "dfeast":"dfeast",
    "dgrowl":"dgrowl",
    "dhiss":"dhiss",
    "dlist":"dlist",
    "dltell":"dltell",
    "dmhelp":"dmhelp",
    "dmtell":"dmtell",
    "enshroud":"enshroud",
    ]);
}

/*****************************************************************************
 * Here follows the functions. New functions should be added in alfabetic
 * order.
 ****************************************************************************/

/*
 * Global variables
 */

int shroud_again;     // Can the player enshroud again??

// #################################
//       D F E A S T
// #################################

int
dfeast(string str)
{

    object the_corpse;

    if (!str)
      {
        notify_fail("You must specify what you're trying to feast on.\n");
        return 0;
      }
    if ( !(the_corpse=present(str,environment(TP))) )
     {
       notify_fail("Feast on what?\n");
       return 0;
     }
    if (!the_corpse->id("corpse"))
     {
       notify_fail("You cannot feast on that which is not a corpse.\n");
       return 0;
     }

    TP->catch_msg("You sink your teeth into the raw flesh of your victim, "+
                  "sucking its blood and revelling in the taste of its "+
                  "vital organs.\n");
    tell_room(environment(TP),QCTNAME(TP)+" sinks "+TP->query_possessive()+
                  " teeth into the raw flesh of the corpse, sucking its "+
                  "ood and revelling in the taste of its "+
                  "vital organs.\n",TP);
    the_corpse->remove_object();
    TP->heal_hp(100+random(250));
    TP->add_fatigue(30+random(50));
    return 1;
}
// #################################
//          D G R O W L
// #################################

int
dgrowl(string str)
{

    object *ob;

    if (!str)
    {
    write("You growl evilly, parting acid-dripping teeth in a "+
          "rictus grin.\n");
    say(QCTNAME(TP) + " growls evilly, parting acid-dripping teeth "+
          "in a rictus grin.\n");
    return 1;
    }

    ob = parse_this(str, "[at] %l");
    NF("Growl at whom?\n");
    if (!sizeof(ob))
	return 0;
    TP->catch_msg("You growl evilly at "+QCTNAME(ob[0])+", parting "+
                  "your acid-dripping teeth in a rictus grin.\n");
    ob[0]->catch_msg(QCTNAME(TP) + " growls evilly at you, "+
                  "parting "+ob[0]->query_possessive()+" acid-dripping "+
                  "teeth in a rictus grin.\n");
    say(QCTNAME(TP) + " growls evilly at " + QTNAME(ob[0]) +
        ", parting "+TP->query_possessive()+ " acid-dripping teeth "+
        "in a rictus grin.\n",({ ob[0],TP }) );
    return 1;
}


// #################################
//           D H I S S
// #################################

int
dhiss(string str)
{
    object *ob;

    if (!str)
    {
    write("You hiss angrily.\n");
    say(QCTNAME(TP) + " hisses angrily, spitting steaming acid "+
        "onto the ground.\n");
	return 1;
    }

    ob = parse_this(str, "[at] %l");
    NF("Hiss at whom?\n");
    if (!sizeof(ob))
	return 0;
   TP->catch_msg("You his angrily at "+QCTNAME(ob[0])+".\n");
    ob[0]->catch_msg(QCTNAME(TP) + " hisses angrily at you, "+
          "spitting steaming acid at your feet.\n");
    say(QCTNAME(TP) + " hisses angrily at " + QTNAME(ob[0]) +
        ", spitting steaming acid at "+TP->query_possessive()+
        " feet.\n", ({ ob[0],TP }) );
    return 1;
}


// ############################
//       D L I S T
// ############################

int
dlist()
{
    object *players;
    int i,dcount;

    players=users();

    write("\n"+sizeof(players)+" players connected.\n");

    write("\nList of connected Demon Servants and Brothers.\n");
    write("----------------------------------------------\n");
    for (i=0;i<sizeof(players);i++)
      {
       if (present("demon_rank_object",players[i]))
        {
         dcount++;
         if (players[i]->query_skill(SS_DEMON_LORE)>DEM_ASCENSION_LEVEL)
           write("[Extra-Planar Demon]\n");
         else
           write("[Demonic Servant]\n");
         write(" "+players[i]->query_name()+" "+
               players[i]->query_title()+" ["+players[i]->query_race_name()+
               "]\n");
        }
      }
write("----------------------------------------------\n");
write(dcount+" DemonSpawn Connected.\n");
return 1;
}
// ########################
// D L T E L L
// ########################

int dltell(string str)
{
    object *players;
    string message;
    int i;

	if (!str || str=="")
	 {
	   NF("Dltell What?\n");
	   return 0;
	 }

	players=users();

        for (i=0;i<sizeof(players);i++)
	   {
	     if (present("demon_rank_object",players[i]))
		{
		  players[i]->catch_msg("<DemonSpawn>["+QCTNAME(TP)+"]"+
                        ": "+str+"\n");
	 	}
	   }
	TP->add_mana(-80);
    return 1;
}
// #######################
// D M H E L P
// #######################

string
determine_help(string str)
{
    return "DemonHelp.Doc";
}

int
dmhelp(string str)
{
    TP->catch_msg("DemonSpawn Help (Search For : "+str+")\n----------------\n");
    seteuid(getuid(TO));
    if (!str || str=="")
	{ 
          cat(DEFAULT_HELP,1);
        }
    else
      {
	cat(determine_help(str));
       }
return 1;
}


// ########################
// D M T E L L
// #########################

int
dmtell(string str)
{

	string name, message;
	object target;

	if (!str || str=="")
           {
	    NF("Dtell Who?\n");
	    return 0;
	   }
	if (sscanf(str,"%s %s",name,message) !=2)
	   {
            NF("Usage:\n       dtell <player> <message>\n");
            return 0;
           }
	target=find_player(name);
	if (!target)
	   {
	     NF(capitalize(name)+"'s mind is unreachable.\n");
  	     return 0;
           }
        if (!present("demon_rank_object",target))
	   {
	     NF("You cannot enter the mind of one who does not serve"+
                " the demons.\n");
	     return 0;
            }
        target->catch_msg("You feel the presence of "+QCTNAME(TP)+"'s mind "+
                   "within yours. It softly "+
                   "hisses to you :\n "+message+"\n\n");
	TP->catch_msg("You contact "+capitalize(name)+"'s mind and send "+
		      "your message.\n");
	TP->add_mana(-50);
	return 1;
}

int
enshroud(string str)
{
    if (!TP->query_prop(DEMON_IS_ENSHROUDED))
    {
    TP->add_prop(DEMON_IS_ENSHROUDED, 1);
    TP->catch_msg("You prepare to enshroud yourself.\n");
    say(QCTNAME(TP)+" thrusts "+TP->query_possessive()+" hands "+
        "forward and bellows an un-recognizable phrase with "+
        "incredible volume and rage.\n");
    write("You thrust your hands forward and shout the words "+
          "of the demonic incantation.\n");
    } else if (TP->query_prop(DEMON_IS_ENSHROUDED) == 1)
       write("You are already preparing another enshroudment.\n");
    else
       write("You must recover from the previous enshroudment.\n");
    call_out("complete_enshroud",15,TP);
    return 1;
}

int
complete_enshroud(object ob)
{
    string shroud_type;
    int    mc;

    if (ob->query_mana() < 250)
      {
        write("You cannot utilize the mental strength required "+
              "to enshroud yourself.\n");
        say(QCTNAME(ob)+" contorts "+ob->query_possessive()+" face "+
              "in anger as concentration is not enough to bring "+
              "forth a demonic incantation.\n");
        return 1;
      }

    if (ob->query_mana() > 250)
      {
        shroud_type="fire";
        mc=250;
      }
    if (ob->query_mana() > 350)
      {
        shroud_type="lightning";
        mc=350;
      }
    if (ob->query_mana() > 500)
      {
        shroud_type="plasma";
        mc=500;
      }

    ob->add_mana(-mc);
    ob->add_prop(DEMON_IS_ENSHROUDED,2);
    write("You are suddenly engulfed in "+shroud_type+".\n");
    say(QCTNAME(ob)+" is suddenly surrounded in "+shroud_type+", "+
       "no part of "+ob->query_possessive()+" body remaining "+
       "untouched.\n");
    ob->add_prop(DEMON_SHROUD_TYPE,shroud_type);
    call_out("remove_shroud",15,TP);
    return 1;
}

int remove_shroud(object ob)
{
    write("You are no longer enshrouded in "+
          ob->query_prop(DEMON_SHROUD_TYPE)+".\n");
    call_out("ready_again",15,TP);
    return 1;
}

int ready_again(object ob)
{
    write("You feel as if you can enshroud again.\n");
    ob->remove_prop(DEMON_IS_ENSHROUDED);
    return 1;
}

/*

void
bash_ob(object *ob)
{
    string how;

    set_this_player(ob[1]);
    how = c_can_attack(ob[0], "bash");
    if (stringp(how))
    {
	write("You are unable to bash the intended victim.\n");
	TP->remove_prop(KNIGHT_I_BASH);
	return;
    }

    call_out("allow_bash", 15, TP);

    if (ob[0] && environment(TP) != environment(ob[0]))
        return;

    TP->add_prop(LIVE_O_SPELL_ATTACK, this_object());
    TP->attack_object(ob[0]);
    TP->add_prop(KNIGHT_I_BASH, 2);
}

void
allow_bash(object ob) { ob->remove_prop(KNIGHT_I_BASH); }


void
spell_attack(object attacker, object target)
{
    string how;
    mixed *hitresult;

    if (attacker->query_prop(KNIGHT_I_BASH) == 2)
    {
	attacker->add_prop(KNIGHT_I_BASH, 1);
	if (random(F_BASH_HIT(attacker, target)) > random(BASH_HIT))
        {
            hitresult = target->hit_me(F_BASH_PEN(attacker, target),
		W_BLUDGEON, attacker, -1;
	    how = "unharmed though";
	    if (hitresult[0] > 0)
	    	how = "a little hurt";
	    if (hitresult[0] > 5)
	    	how = "rather hurt";
	    if (hitresult[0] > 10)
		how = "shaken by the experience";
	    if (hitresult[0] > 25)
		how = "extremely hurt";
	    if (hitresult[0] > 50)
		how = "like hit buy a hurricane";

            attacker->catch_msg("You send " + QTNAME(target) +
		" sprawling with a wonderful bash.\n");
	    attacker->catch_msg(QCTNAME(target) + " looks " + how + ".\n");

            target->catch_msg(QCTNAME(attacker) +
		" sends you sprawling with a bash.\n");
	    target->catch_msg("You feel " + how + ".\n");

	    tell_watcher(QCTNAME(attacker) + " sends " + QTNAME(target) +
		" sprawling with a wonderful bash.\n", attacker, target);

	    if (target->query_hp() <= 0)
	        target->do_die(attacker);
            return;
        }

    	attacker->add_prop(LIVE_I_ATTACK_DELAY, 2);
    	target->hit_me(0, W_BLUDGEON, attacker, -1);
    	attacker->catch_msg("You try to bash " + QTNAME(target) +
	    " but you miss.\n" + "You stumble and fall to the ground.\n");
    	target->catch_msg(QCTNAME(attacker) +
	    " tries to bash you but misses.\n" + C(attacker->query_pronoun()) +
	    " stumbles and falls.\n");
	tell_watcher(QCTNAME(attacker) + " tries to bash " + QTNAME(target) +
	    " but stumbles and falls.\n", attacker, target);
    	return;
    }
    else if (attacker->query_prop(KNIGHT_I_KICK) == 2)
    {
        attacker->add_prop(KNIGHT_I_KICK, 1);
        if (random(F_BASH_HIT(attacker, target)) > random(CKICK_HIT))
        {
            hitresult = target->hit_me(F_CKICK_PEN(attacker, target),
		W_BLUDGEON, attacker, -1);
            how = "without effect";
            if (hitresult[0] > 0)
                how = "hard";
            if (hitresult[0] > 5)
                how = "rather hard";
            if (hitresult[0] > 10)
                how = "very hard";
            if (hitresult[0] > 25)
                how = "extremely hard";
            if (hitresult[0] > 50)
                how = "with a bonecrashing sound";

            attacker->catch_msg("You kick " + QTNAME(target) +  " in " +
                target->query_possessive() + " " +
                hitresult[1] + " " + how + ".\n");
            target->catch_msg(QCTNAME(attacker) + " kicks you " + how +
		" in your " + hitresult[1] + ".\n");
	    tell_watcher(QCTNAME(attacker) + " kicks " + QTNAME(target) +
		" " + how + ".\n", attacker, target);

            if (target->query_hp() <= 0)
                target->do_die(attacker);
            return;

        }

	attacker->add_prop(LIVE_I_ATTACK_DELAY, 2);
        target->hit_me(0, W_BLUDGEON, attacker, -1);
        attacker->catch_msg("You try to kick " + QTNAME(target) +
            " but you miss.\n" + "You stumble and fall to the ground.\n");
        target->catch_msg(QCTNAME(attacker) +
            " tries to kick you but misses.\n" + C(attacker->query_pronoun()) +
            " stumbles and falls.\n");
	tell_watcher(QCTNAME(attacker) + " tries to kick " + QTNAME(target) +
	    " but stumbles and falls.\n", attacker, target);
        return;
    }
}

int
ckick(string str)
{
    object ob, *obj;
    mixed *hitresult;
    string how;

    if (!str)
        ob = TP->query_attack();
    else {
        obj = parse_this(str, "%l");
        if (sizeof(obj) > 0)
            ob = obj[0];
        if (sizeof(obj) > 1)
        {
            NF("Choose one enemy to kick.\n");
            return 0;
        }
    }

    how = c_can_attack(ob, query_verb());
    if (stringp(how))
    {
        NF(how);
        return 0;
    }

    if (!TP->query_prop(KNIGHT_I_KICK))
    {
        TP->add_prop(KNIGHT_I_KICK, 3);
        call_out("ckick_ob", 3, ({ ob, TP }));
        TP->catch_msg("You prepare a combat kick on " + QTNAME(ob) + ".\n");
	if (ob != TP->query_attack())
	{
	    say(QCTNAME(TP) + " looks at " + QTNAME(ob) + " with murder " +
		"in " + TP->query_possessive() + " eyes.\n", ({ ob, TP }));
	    ob->catch_msg(QCTNAME(TP) + " looks at you with murder in " +
		TP->query_possessive() + " eyes.\n");
	}
    } else if (TP->query_prop(KNIGHT_I_KICK) > 1)
        write("You are already preparing another combat kick.\n");
    else
        write("You have to get yourself together from the earlier " +
                "kick before.\n");
    return 1;
}

void
ckick_ob(object *ob)
{
    string how;

    set_this_player(ob[1]);
    how = c_can_attack(ob[0], "kick");
    if (stringp(how))
    {
        write("You are unable to kick the intended victim.\n");
        TP->remove_prop(KNIGHT_I_KICK);
        return;
    }

    call_out("allow_ckick", 15, TP);

    if (ob[0] && environment(TP) != environment(ob[0]))
        return;

    TP->add_prop(LIVE_O_SPELL_ATTACK, this_object());
    TP->attack_object(ob[0]);
    TP->add_prop(KNIGHT_I_KICK, 2);
}

void
allow_ckick(object ob) { ob->remove_prop(KNIGHT_I_KICK); }

int
guildlist(string str)
{
    string name;
    object ob;

    if (str)
    {
        if (TP->query_wiz_level())
        {
            name = C(str) + " is ";
            NF("No such player found.\n");
            if (!(ob = find_player(str)))
                return 0;
        } else {
            write("Curious aren't we?\n");
            return 1;
        }
    } else {
        ob = TP;
        name = "You are ";
    }

    str = ob->list_mayor_guilds();
    if (str)
        write(name + "member of following guilds.\n" + str);
    else
        write(name + "not member of any guilds.\n");

    return 1;
}

int
help(string str)
{
    string subject, filename;

    if (!str)
        return 0;

    if (sscanf(str, "guild %s", subject) != 1)
        return 0;

    seteuid(getuid(TO));
    filename = HELP_DIR + subject;
    if (file_size(filename) > 0)
    {
        cat(filename);
        return 1;
    }

    NF("No help on that subject I'm afraid.\n");
    return 0;
}
*/
