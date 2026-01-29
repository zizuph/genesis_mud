/*
 * AA joining room created by Milan
 *
 *
 *  Modification log:
 *
 *     2008.06.17, Novo: Don't require a recruiter if nobody can recruit
 *     2008.08.18 Novo: Clear lay guild stat when upgrading
 *     2008.08.04 ?: Last modified (???)
 *     2011.07.18 Lavellan: Added downgrade occ to lay option
 *     2016.10.17 Mirandus: Removed requirement to be "recruited" and to
 *                get hobbit noses when downgrading to layman. Done now
 *                through <wimp out> command.
 *     2019.02.10 Finwe: Fixed guild and alignment check
 *
 *     2021.03.15 Nerull: Ensure that when the AA member leaves the guild,
 *                he/she is also removed from the Lieutenant positions.
 *
 */
#pragma save_binary
#pragma no_inherit
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include "../guild.h"

inherit "/lib/guild_support";
inherit SHIRE_ROOM;

#define BOARD_NAME  (AA_DIR+"boards/aa_board_chapel")
#define ALLOWED "_aa_allowed"
#define TRANSREQ "_aa_requested_transfer"

// Prototypes of command functions
int recruit(string str);
int join(string str);
int leave(string str);
int do_demote(string str);

void
create_shire_room()
{
    object board;

    set_short("Sacred room");
    set_long("This is the sacred room of the Angmar Army. You "+
           "can see many trophies from the old wars gathered by these "+
           "warriors. Though most of the things here look cruel the room "+
           "still emits an aura that might help you with your meditations. "+
           "If you are not a member of the Army, then this is the place "+
           "where you can join it. There is a sign placed on the wall "+
           "with more info, and a plaque next to it. You "
           +"might as well list guilds you "+
           "are member of. If you ever decide to leave the Army, you "+
           "can do it here too. Leaving is not a wise act because many "+
           "warriors will disapprove and become very angry at you "+
           "and they might even beat some experience and skills out of "+
           "your stupid head.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(ALLOWED, ({ }));

    add_cmd_item("plaque", "read", "@@read_sign@@");

    add_exit(AA_DIR+"rooms/c3", "east");

    add_item("sign", "There are instructions about joining on it.\n");
    add_cmd_item("sign", "read", "If you want to join Angmar Army you "+
        "need a Recruitment Officer or Final Judge or Lieutenant or "+
        "Captain of the Army who will:\n"+
        "            'recruit <name>'\n"+
        "Immediately after that you can:\n"+
        "            'enlist army layman'\n"+
        "         or 'enlist army occupational'\n"+
        "If you satisfy all requirements you will become a soldier. "+
        "Layman soldiers can later upgrade to occupational without "+
        "further requirements. To downgrade from occupational to layman, "+
        "well, you'd have to be crazy. But if you really wanted to, you "+
        "could simply <wimp out>. You might make some very "+
        "important people angry, though!\n\n" +
        "If you ever decide the Army is too hard, you can:\n" +
        "            'leave army'\n" +
        "You will pay dearly for leaving though.\n\n *Note: If there "
        +"is no Captain in the Army, anyone can join for FREE.\n\n");

    setuid();
    seteuid(getuid());
    create_guild_support();

    object book = clone_object(AA_DIR+"books/book");
    book->move(TO);
    book->set_book_is_private(1);

    board = clone_object(AA_DIR+"obj/aa_board");
    board->move(TO, 1);
}

void
init()
{
    add_action(recruit,"recruit");
    add_action(gs_meditate, "meditate");
    add_action(join,"enlist");
	add_action(do_demote,"wimp");
    add_action(leave, "leave");
    add_action(gs_list, "list");
    ::init();
}

void
remove_allowed(string str)
{
    string *arr = query_prop(ALLOWED);
    arr -= ({ str });
    add_prop(ALLOWED, arr);
}

int
recruit_access(object ob)
{
    if ((!living(ob)) || (ob->query_ghost()) || (ob == TP) ||
        (!ob->check_seen(TP)) || (ENV(ob) != ENV(TP)))
        return 0;
    return 1;
}

int
recruit(string str)
{
    string *arr, name = TP->query_name();
    object *who;

    if(TP->query_wiz_level() ||
        (IS_MEMBER(TP) && (AA_RANKS_OBJ->lieut_cap(name))))
    {
        who = CMDPARSE_ONE_ITEM(str, "recruit_access", "recruit_access");
        if (sizeof(who) > 1)
        {
            NF("Be specific, you can't recruit "+COMPOSITE_LIVE(who)+
               " at the same time.\n");
            return 0;
        }

        if (!sizeof(who))
        {
            NF("You find no such living creature here.\n");
            return 0;
        }

        name = LOW(who[0]->query_name());

        arr = query_prop(ALLOWED) + ({ name });

        add_prop(ALLOWED, arr);

        TP->catch_msg("You recruited "+QTNAME(who[0])+" into the Army.\n");

        who->catch_msg(QCTNAME(TP)+" recruited you into the Army. You can join now.\n");

		who->add_prop(ALLOWED, 1);

        tell_room(TO, QCTNAME(TP)+" recruited "+QTNAME(who[0])+" into the Army.\n",
                  ({TP, who[0]}) );
// no need to log wizards recruiting players
        if(TP->query_wiz_level())
            return 1;
        else
        {
		    write_file(AA_DIR + "log/recruit_log", ctime(time()) + " " +
			    capitalize(TP->query_real_name()) + " recruited "+
                capitalize(who[0]->query_real_name())+" into the Army.\n");
        }

        set_alarm(150.0, 0.0, &remove_allowed(name) );
        return 1;
    }

    NF("You are not allowed to recruit.\n");
    return 0;
}

void
leave_inv(object who, object to)
{
    gs_leave_inv(who,to);
    ::leave_inv(who,to);
}

int needs_recruiter()
{
    if ((AA_COUNCIL_OBJ->lieut_cap(this_player()->query_name())) == 1 || (this_player()->query_wiz_level()))
    {
        return 1;
    }

	/*if (AA_COUNCIL_OBJ->is_ro(this_player()->query_name()) == 1)
	{
		return 1;
	}*/

    /*if (sizeof(AA_RANKS_OBJ->query_players_with_rank_no(5)))
    {
        return 1;
    }

    if (sizeof(AA_RANKS_OBJ->query_players_with_rank_no(6)))
    {
        return 1;
    }*/

    return 0;
}

int
do_I_allow_join_my_guild(object player)
{
    string race = player->query_race_name();

    if (player->query_wiz_level()) return 1;

    if (IS_MEMBER(player)) return 1;

    /*if (sizeof(AA_RANKS_OBJ->query_aa_members()) > 23
        && needs_recruiter() &&
        member_array(LOW(player->query_name()), query_prop(ALLOWED))==-1)
    {
        player->catch_msg("You have not been recently recruited into the army.\n");
        return 0;
    }*/

    if (member_array(LOW(player->query_name()), query_prop(ALLOWED)) == -1)
    {
        player->catch_msg("You have not been recently recruited into the army.\n");
        return 0;
    }

    if (player->query_guild_style_occ()=="ranger")
    {
        player->catch_msg("Someone shouts: Help!!! There is a ranger here! Kill him!!!\n");
        return 0;
    }

    if (member_array(race, ALLOWED_RACES) == -1)
    {
        if (race == "elf") 
            player->catch_msg("We hate elves! Get lost!!!\n");
        else 
            player->catch_msg("Your puny "+race+" can't swing club properly!\n");
        return 0;
    }

//    if (player->query_guild_style("fighter") && (player->query_alignment() > -100))
    if ((player->query_alignment() > -100))
    {
        player->catch_msg("We don't want any holy warrior here!!!\n");
        return 0;
    }
    return 1;
}

int
join(string str)
{
    object shadow, soul;
    int result;
    string *soul_arr;
    string text;


    FIXEUID;

    NF("Enlist what? Army???\n");

    if (str != "army occupational"  && 
            (str != "army layman") && (str != "army"))
        return 0;
        
    if (str == "army")
    {
        TP->catch_msg("You have two choices here:\n"+
                      "       enlist army occupational\n"+
                      "       enlist army layman\n");
        return 1;
    }


    if (IS_MEMBER(TP))
    {
        /*if (str=="army layman")
        {
            TP->catch_msg("You are already member of our guild. Please do 'list guilds' "+
                          "to check your memberships.\n");
            return 1;
        }
        else if (TP->query_guild_name_occ() == GUILD_NAME)
        {
            TP->catch_msg("You are already occupational member of our guild.\n");
            return 1;
        }*/
        if(TP->query_guild_name_occ() == GUILD_NAME && 
            (str=="army occupational"))
        {
            TP->catch_msg("You are already an occupational member of the Army.\n");
            return 1;
        }

        else if (TP->query_guild_name_lay() == GUILD_NAME && 
            (str=="army layman"))
        {
            TP->catch_msg("You are already a layman member of the Army.\n");
            return 1;
        }
    }

    //if (!do_I_allow_join_my_guild(TP)) return 1;


	if (AA_COUNCIL_OBJ->no_captain() == 0)
	{
		if (!TP->query_prop(ALLOWED))
		{
			TP->catch_msg("You have not been recently recruited into the Army.\n");
			return 1;
		}
	}


    if (str=="army layman")
    {
        if (TP->query_guild_name_occ() == GUILD_NAME)
        {
            if (TP->query_guild_name_lay())
            {
                TP->catch_msg("But you are already a member of a layman" +
                    " guild!\n");
                return 1;
            }

        }
        else
        {
            say(QCTNAME(TP)+" joined the Angmar Army.\n");
            TP->catch_msg("You joined the Angmar Army as a layman member.\n");
        }

        shadow = clone_object(AA_LAY_SHADOW);
        if ((shadow->shadow_me(TP, "layman", GUILD_STYLE, GUILD_NAME, "")) != 1)
        {
            /* This is one of the few times you destruct is OK to use... */
            "secure/master"->do_debug("destroy",shadow);
            TP->catch_msg("Bug... For some reason you can't join.\n");
            return 1;
        }
    }
    else
    {
        text = TP->query_rank();
        shadow = clone_object(AA_OCC_SHADOW);
        if ((shadow->shadow_me(TP, "occupational", GUILD_STYLE, GUILD_NAME, "")) != 1)
        {
            /* This is one of the few times you destruct is OK to use... */
            "secure/master"->do_debug("destroy",shadow);
            TP->catch_msg("Bug... For some reason you can't join.\n");
            return 1;
        }
        if (TP->query_guild_name_lay() == GUILD_NAME)
        {
            int old_stat=TP->query_acc_exp(SS_LAYMAN);
            TP->remove_guild_lay();
            TP->clear_guild_stat(SS_LAYMAN);
            TP->catch_msg("You change from layman to occupational "+
            "member.\n");
            say(QCTNAME(TP)+" upgraded to occupational membership.\n");
            TP->set_rank(text);
            TP->set_guild_stat(SS_OCCUP,old_stat);
            return 1;
        }
        else
        {
            say(QCTNAME(TP)+" joined the Angmar Army.\n");
            TP->catch_msg("You joined the Angmar Army as an occupational member.\n");
        }
    }
    if (TP->query_wiz_level())
        TP->catch_msg("Remember to add cmdsoul '"+AA_SOUL+"', '"+AA_SOUL_E+"'.\n");
    //TP->catch_msg("You joined the Angmar Army.\n");
    //say(QCTNAME(TP)+" joined the Angmar Army.\n");
    FIXEUID;

    write_file(AA_DIR+"log/join_log",ctime(time())+ " "+
        capitalize(TP->query_real_name())+" has joined the "+str+".\n");
    return 1;
}

int
do_demote(string str)
{
	object shadow, soul;
	string text;
	FIXEUID;

    NF("Wimp what? Out???\n");
	if ((str != "out"))
        return 0;

    if (!IS_MEMBER(TP))
	{
		TP->catch_msg("You'd have to actually be a member of the Army to "
		+"demote yourself to the Layman branch.\n");
	}

	if (TP->query_guild_name_lay() == GUILD_NAME)
	{
		TP->catch_msg("You're already a Layman member of the Army\n");
		return 1;
	}

	if (TP->query_guild_name_occ() == GUILD_NAME)
    {
        if (TP->query_guild_name_lay())
        {
            TP->catch_msg("But you are already a member of a layman" +
                " guild!\n");
            return 1;
        }

        if (!TP->query_prop(TRANSREQ))
        {
            TP->add_prop(TRANSREQ,1);
            tell_room(TO,QCTNAME(TP) + " asks to become a layman.\n\n",({TP}));
            tell_room(TO,"A shout goes up: Hey! This pathetic excuse for a "+
                "soldier thinks " + TP->query_pronoun() + " can find a "+
                "better army somewhere else! Says "+ TP->query_pronoun() + " "+
                "wants to be a LAYMAN soldier!!\n\n");
            tell_room(TO,"A group of huge and menacing soldiers crowd around.\n");
            tell_room(TO,"One says: Huh, we don't need 'em!\n\n");
            tell_room(TO,"Another shouts: Let's just eat him?\n\n");
            tell_room(TO,"A huge laugh goes up around the room.\n\n");
            tell_room(TO,"The first one says: Nah, whatever! If the weak "+
            "little baby wants to be a LAYMAN soldier, we'll let him. But "
            +"Not unless "+TP->query_pronoun()+" asks again\n\n");
            tell_room(TO,"They all stomp out.\n");
            return 1;
        }
        else
        {
            text = TP->query_rank();
            int old_stat=TP->query_acc_exp(SS_OCCUP);
            TP->remove_guild_occ();
            TP->clear_guild_stat(SS_OCCUP);
            tell_room(TO,QCTNAME(TP) + " asks to become a layman, waving "+
                TP->query_possessive() + ".\n\n",({TP}));
            tell_room(TO,"A group of huge and menacing soldiers crowd around.\n\n");
            tell_room(TO,"One says: Looks like " + TP->query_pronoun() +
                " did it, then, eh?\n\n");
            tell_room(TO,"Another shouts: I still say we kill 'em!\n\n");
            tell_room(TO,"The first shouts: Shut up! Fine, you go be "+
            "layman. You can start by sweeping out my toilet!\n\n");
            tell_room(TO,"A huge laugh goes up, and the crowd disperses.\n\n");
            TP->catch_msg("You change from occupational to layman "+
            "member.\n");
            say(QCTNAME(TP)+" downgraded to layman membership.\n");
            TP->set_rank(text);
            TP->set_guild_stat(SS_LAYMAN,old_stat / 4);
            
            AA_COUNCIL_OBJ->demote_lieutenant(TP->query_name());
            AA_COUNCIL_OBJ->demote_captain(TP->query_name());
        }
        
        shadow = clone_object(AA_LAY_SHADOW);
        if ((shadow->shadow_me(TP, "layman", GUILD_STYLE, GUILD_NAME, "")) != 1)
        {
            /* This is one of the few times you destruct is OK to use... */
            "secure/master"->do_debug("destroy",shadow);
            TP->catch_msg("Bug... For some reason you can't join.\n");
            return 1;
        }

    }
    
    FIXEUID;

    write_file(AA_DIR+"log/join_log",ctime(time())+ " "+
    capitalize(TP->query_real_name())+" has wimped out to layman.\n");
    return 1;
}

int
do_leave(object tp)
{
    int *skills, i, j;

	object token;

    string text = QTRACE(tp);

    FIXEUID;

    if (!IS_MEMBER(tp))
    {
        tp->catch_msg("But you are not a member of the army!\n");
        return 1;
    }

    tp->catch_msg("Suddenly, many angry warriors jump you "+
        "and beat you with their nasty clubs...\n"+
        "Fortunatelly you lose consciousness so you don't feel every hit.\n\n"+
        "When you wake up you notice that you have terrible headache "+
        "and that you feel less skillful.\nYou are no longer a member "+
		"of the Army of Angmar!\n");
    tell_room(ENV(tp), QTNAME(tp)+
        " screams loudly when many angry warriors suddenly jump at "+
        HIM(tp)+" and beat "+HIM(tp)+" with their nasty clubs...\n"+
        QCTNAME(tp)+" is soon knocked down but the cruel warriors continue "+
        "beating "+HIM(tp)+", aiming mainly for "+HIS(tp)+" head.\n"+
        "After they are satisfied they leave the room leaving "+
        QTNAME(tp)+" laying on the floor...\n\n"+
        "After a long time "+QTNAME(tp)+" regains his senses and touches "+
        HIS(tp)+" sore head. "+CAP(HE(tp))+
        " is no longer a member of the Army of Angmar!\n", tp);
    tp->set_max_headache(MAX(1000, tp->query_max_headache()));
    tp->set_headache(tp->query_max_headache());

    // Ensures that anyone who leaves AA also loses the 
    // LT/CAP position. Nerull 2021.
    AA_COUNCIL_OBJ->demote_lieutenant(TP->query_name());
    AA_COUNCIL_OBJ->demote_captain(TP->query_name());
    
    tp->remove_aa_member(tp);
    
    return 1;
}

int
leave(string str)
{
    NF("Leave what? Army???\n");
    if(str != "army") return 0;
    return do_leave(TP);
}

/*
int
gs_hook_already_meditate()
{
    write("You are already meditating. You can stop it by typing 'rise'.\n");
    return 1;
}

void
gs_hook_start_meditate()
{
    write("You sit down and start to meditate upon yourself.\n"+
        "You find yourself able to <estimate> your attributes "+
        "and <set> your learning preferences.\n"+
        "Just <rise> when you have finished meditating.\n");
    say(QCTNAME(TP) + " sits on the floor and starts to meditate.\n");
}

void
gs_hook_rise()
{
    write("Relaxed you rise from the floor.\n");
    say(QCTNAME(TP) + " rises from the floor.\n");
}

int
gs_hook_catch_error(string str)
{
    write("You can't do that while meditating.\n");
    return 1;
}
*/



string read_sign()
{
    return "\n\nOn the plaque you read:\n\n" + 
"Officers of the Army of Angmar\n"+
"******************************\n"+
"Captain\n"+
"-------\n\n     "+AA_COUNCIL_OBJ->query_captain()+
"\n\n"+
"Lieutenants\n" +
"-----------\n\n     " + AA_COUNCIL_OBJ->query_lieutenant() +
"\n\n";
}
