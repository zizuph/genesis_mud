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
           "with more info. You might as well list guilds you "+
           "are member of. If you ever decide to leave the Army, you "+
           "can do it here too. Leaving is not a wise act because many "+
           "warriors will disapprove and become very angry at you "+
           "and they might even beat some experience and skills out of "+
           "your stupid head.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(ALLOWED, ({ }));

    add_exit(AA_DIR+"rooms/c3", "east");

    add_item("sign", "There are instructions about joining on it.\n");
    add_cmd_item("sign", "read", "If you want to join Angmar Army you "+
        "need a Recruitment Officer or Final Judge or Lieutenant or "+
        "Captain of the Army who will:\n"+
        "            'recruit <name>'\n"+
        "Immediately after that you can:\n"+
        "            'join army layman'\n"+
        "         or 'join army occupational'\n"+
        "If you satisfy all requirements you will become a soldier. "+
        "Layman soldiers can later upgrade to occupational without "+
        "further requirements. To downgrade from occupational to layman, "+
        "well, you'd have to be crazy. But if you really wanted to, you "+
        "could simply try to join as a layman. You might make some very "+
        "important people angry, though!\n");

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
    add_action(join,"join");
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

    if ((IS_MEMBER(TP) &&
        (AA_RANKS_OBJ->lieut_cap(name) || TP->query_wiz_level)))
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

		write_file(AA_DIR + "log/recruit_log", ctime(time()) + " " +
			capitalize(TP->query_real_name()) + " recruited "+who[0]->query_real_name()+" into the Army.\n");

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
        if (race == "elf") player->catch_msg("We hate elves! Get lost!!!\n");
        else player->catch_msg("You puny "+race+" can't swing club properly!\n");
        return 0;
    }

    if (player->query_guild_style("fighter") && (player->query_alignment() > -100))
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
    object *noses;
    int nosenum;

    FIXEUID;

    NF("Join what? Army???\n");

    if ((str != "army occupational") && (str != "army layman") && (str != "army"))
        return 0;
    if (str == "army")
    {
        TP->catch_msg("You have two choices here:\n"+
                      "       join army occupational\n"+
                      "       join army layman\n");
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
        if (TP->query_guild_name_occ() == GUILD_NAME && str=="army occupational")
        {
            TP->catch_msg("You are already an occupational member of our guild.\n");
            return 1;
        }

        else if (TP->query_guild_name_lay() == GUILD_NAME && str=="army layman")
        {
            TP->catch_msg("You are already a layman member of our guild.\n");
            return 1;
        }
    }

    //if (!do_I_allow_join_my_guild(TP)) return 1;


	if (AA_COUNCIL_OBJ->no_captain() == 0 || AA_COUNCIL_OBJ->no_lieutenants() == 0)
	{
		if (!TP->query_prop(ALLOWED))
		{
			TP->catch_msg("You have not been recently recruited into the army.\n");
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

            if (!TP->query_prop(TRANSREQ))
            {
                TP->add_prop(TRANSREQ,1);
                //TP->catch_msg("You may transfer from occupational to layman" +
                    //" if you bring us... Twenty hobbit noses!\n");
                tell_room(TO,QCTNAME(TP) + " asks to become a layman.\n\n",({TP}));
                tell_room(TO,"A shout goes up: Hey! This pathetic excuse for a "+
                    "soldier thinks " + TP->query_pronoun() + " can find a "+
                    "better army somewhere else! Says "+ TP->query_pronoun() + " "+
                    "wants to be a LAYMAN soldier!!\n\n");
                tell_room(TO,"A group of huge and menacing soldiers crowd around.\n");
                tell_room(TO,"One says: Huh, we don't need 'em!\n\n");
                tell_room(TO,"Another shouts: Tell 'em to bring back twenty hobbit "+
                    "noses, then maybe we'll think about it!\n\n");
                tell_room(TO,"A huge laugh goes up around the room.\n\n");
                tell_room(TO,"The first one says: Good. That's it then. Twenty "+
                    "hobbit noses, then we will THINK about it, you pathetic sot!\n\n");
                tell_room(TO,"They all stomp out.\n");
                return 1;
            }
            else
            {
                nosenum = 0;
                noses = FILTER_LEFTOVER_OBJECTS(deep_inventory(TP));
                noses = filter(noses,&operator(==)("hobbit") @ &->query_race());
                noses = filter(noses,&operator(==)("nose") @ &->query_organ());
                foreach (object nose:noses)
                {
                    nosenum += nose->num_heap();
                }
                if (nosenum < 20)
                {
                    TP->catch_msg("Are you stupid? You were told to fetch" +
                        " twenty hobbit noses, and you have not!\n");
                    return 1;
                }
                TP->catch_msg("All your hobbit noses are taken from you!\n");
                noses->remove_object();
                text = TP->query_rank();
                int old_stat=TP->query_acc_exp(SS_OCCUP);
                TP->remove_guild_occ();
                TP->clear_guild_stat(SS_OCCUP);
                tell_room(TO,QCTNAME(TP) + " asks to become a layman, waving "+
                    TP->query_possessive() + " catch of hobbit noses in the"+
                    " air.\n\n",({TP}));
                tell_room(TO,"A group of huge and menacing soldiers crowd around.\n\n");
                tell_room(TO,"One says: Looks like " + TP->query_pronoun() +
                    " did it, then, eh?\n\n");
                tell_room(TO,"Another shouts: I still say we kill 'em!\n\n");
                tell_room(TO,"The first shouts: Shut up! We're makin' stew" +
                    " from these. Fine, you go be layman. You can start by" +
                    " sweeping out my toilet!\n\n");
                tell_room(TO,"A huge laugh goes up, and the crowd disperses.\n\n");
                TP->catch_msg("You change from occupational to layman "+
                "member.\n");
                say(QCTNAME(TP)+" downgraded to layman membership.\n");
                TP->set_rank(text);
                TP->set_guild_stat(SS_LAYMAN,old_stat / 4);
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
    tp->query_aa_evade_obj()->remove_object();
    
    if (tp->query_guild_name_occ() == GUILD_NAME)
    {
        if (!tp->remove_guild_occ())
        {
            write("There was a strange error, I'm afraid you are stuck with us.\n");
            return 1;
        }
        /* drain occ-leave */
        tp->add_exp(-tp->query_exp_combat()/6,1);
        tp->clear_guild_stat(SS_OCCUP);
    }
    else
    {
        if (!tp->remove_guild_lay())
        {
            write("There was a strange error, I'm afraid you are stuck with us.\n");
            return 1;
        }
        /* drain lay_leave */
        tp->add_exp(-tp->query_exp_combat()/9,1);
        tp->clear_guild_stat(SS_LAYMAN);
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

    if (member_array(AA_SOUL, tp->query_cmdsoul_list()) != -1)
        tp->remove_cmdsoul(AA_SOUL);
    if (member_array(AA_SOUL_E, tp->query_cmdsoul_list()) != -1)
        tp->remove_cmdsoul(AA_SOUL_E);
    tp->update_hooks();

    tp->remove_skill(SS_SHIELD);
    tp->remove_skill(SS_SMASH);
    tp->remove_skill(SS_BASH);

    skills = tp->query_all_skill_types();
    for (i=0; i<sizeof(skills); i++)
    {
        if ((skills[i]<1000))
        {
            j = tp->query_base_skill(skills[i]);
            tp->set_skill( skills[i], j - random(MIN(j,20)) );
        }
    }
    tp->set_default_start_location(tp->query_def_start());
    AA_RANKS_OBJ->remove_entry(tp->query_real_name());
    write_file(AA_DIR+"log/join_log",ctime(time())+ " "+
        capitalize(TP->query_real_name())+" has left the army.\n");


	if (objectp(token = present("_aa_tabard_ob", this_player())))
	{
	    write("Your "+token->query_short()+" fades away.\n");

	    tell_room(environment(this_player()), "The "+
	    token->query_short()+" of "+
	    QTNAME(this_player())+" fades away.\n", this_player());

	    token->remove_object();
	}

	
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
