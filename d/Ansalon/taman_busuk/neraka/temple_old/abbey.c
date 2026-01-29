/* Ashlar, 30 Sep 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/guild/pot/guild.h"
#include "/d/Ansalon/guild/pot/spells.h"

inherit TEMPLE_BASE;
inherit "/d/Ansalon/guild/pot/lib/train_mind";

#define A_JOIN_LOG(f, j, w) (log_file(f, sprintf("%s %15s %s the guild " + \
         "(%3d)\n", \
         extract(ctime(time()), 4), \
         C(w->query_real_name()),j, \
         w->query_average_stat()), \
      200000))

#define TEMP_I_PREPARED  "_temp_i_prepared"
#define TEMPLE_WANT_TO_LEAVE    "_temple_want_to_leave"

object priest;

int is_initiating;

void
reset_neraka_room()
{
    if (!objectp(priest))
    {
        priest = clone_npc(NNPC + "terwed");    	
        set_trainer(priest);
    }
}

string
long_descr()
{
    return "You are standing inside a huge circular chamber, the dark " +
    "abbey, in the temple. Four doors in each cardinal direction lead " +
    "out of the chamber. In the center of the room is a lifesize " +
    "statue of Takhisis, the Queen of Darkness, raised on a podium, " +
    "below which is an altar.\n";
}

void
create_neraka_room()
{
    set_short("in the dark abbey");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"door","large door"}),
    "The large door is made of oak inlaid with metal.\n");

    add_item(({"statue","queen","takhisis"}),
    "The statue of the Queen of Darkness is impressive, sculptured of " +
    "obsidian with details of platinum.\n");

    add_item("podium",
    "The podium on which the statue stands is made of dark stone, and a " +
    "metal plaque is set in it at the base of the statue.\n");

    add_item(({"plaque","metal plaque","steel plaque"}),
    "The plaque is made of polished steel, it is square and set in " +
    "the podium, at the base of the statue.\n");

    add_cmd_item(({"plaque","metal plaque","steel plaque"}),
    ({"read"}),({VBFC_ME("read_plaque")}));

    add_item("altar",
    "The altar is devoid of ornaments, it is not much more than a " +
    "slab of stone upon metal stands.\n");

    add_item(({"slab","stone slab","slab of stone"}),
    "The slab of stone that makes up the altar rests upon sturdy " +
    "metal stands.\n");

    add_item(({"stands","metal stands"}),
    "The metal stands raise the altar to waist-height.\n");

    reset_room();

    add_prop(ROOM_M_NO_ATTACK, "The sanctity of this room prevents you " +
    "from fighting.\n");

    create_skill_raise();
    set_up_skills();

    add_exit(NTEMPLE + "d6", "south");
    add_exit(NTEMPLE + "d3", "west");
    add_exit(NTEMPLE + "d5", "north");
    add_exit(NTEMPLE + "d4", "east");
}

string
read_plaque()
{
    tell_room(TO,QCTNAME(TP) + " reads the metal plaque.\n", TP);

    return "Gaze upon thy queen, and worship her with all your soul. " +
    "Follow her command and do her bidding, and thou shall reap " +
    "rewards that are undreamed of. In her name shall you conquer, " +
    "in her blessing will you be victorious.\n";
}

int
member_pray(string arg)
{
    int spell_set;
    int gs;
    int alpha, beta, gamma, eta, phi;
    int to_priest = 0;
    
    if (stringp(arg) && arg != "")
    {
    	NF("Pray what?\n");
    	return 0;
    }

    write("You kneel in front of the altar and pray to the Queen of Darkness.\n");
    tell_room(TO, QCTNAME(TP) + " kneels in front of the altar in a short prayer.\n", TP);

    spell_set = 0;

    switch(TP->query_priest_level())
    {
    	case GUILD_LEVEL_HIGH_PRIEST:
    	    spell_set += PGEM_ID + PIDENTIFY_ID + PSLOW_ID + PSCRY_ID +
			PRESTORE_ID + PEYES_ID + PPAIN_ID;
	case GUILD_LEVEL_PRIEST:
        spell_set += PHAMMER_ID;
	    spell_set += PMIRAGE_ID;
	    if (TP->query_priest_sublevel() >= 2)
		spell_set += PBLESS_ID;
	    if (TP->query_priest_sublevel() >= 1)
		spell_set += PBLIND_ID;
	case GUILD_LEVEL_INITIATE:
	    spell_set += PALIGN_ID + PCURSE_ID + PHEAL_ID + PTELL_ID + PDRAIN_ID +
	        PHEARING_ID;
    }

    if ((~TP->query_skill(PS_SPELLS)) & spell_set)
    {
    	TP->set_skill(PS_SPELLS, TP->query_skill(PS_SPELLS) | spell_set);
    	write("\nIn a holy vision you realise that you have been granted " +
    	"new spells!\n");
    	
    }

//    TP->set_skill(PS_SPELLS, TP->query_skill(PS_SPELLS) & ~(PSCRY_ID));
    
    if (TP->query_prop(POT_GOT_NEW_SPELL))
    {
    	write("\nIn reward for your excellent performance, the Queen grants " +
    	"you a new spell; " + TP->query_prop(POT_GOT_NEW_SPELL) + "!\n");
    	TP->remove_prop(POT_GOT_NEW_SPELL);
    }

    P(MEDALLION_ID, TP)->update_spells();

    /* Do some arcane computations involving greek letters to compute
       the guild level
    */
    alpha = TP->query_stat(SS_OCCUP) - 15;
    beta  = TP->query_stat(SS_WIS) - 45;
    gamma = TP->query_skill(PS_SKILL_POINTS);
    eta   = TP->query_skill(SS_SPELLCRAFT);
    phi   = TP->query_skill(SS_ELEMENT_LIFE);

    gs = (2 * alpha + 3 * beta) / 5 + (eta + phi) / 8 +
        ftoi(sqrt(itof(gamma)) / 5.0) - 5;

    // write("\ngs = " + gs + "\n");

    // We do not get demoted
    if (gs < TP->query_skill(PS_GUILD_LEVEL))
        gs = TP->query_skill(PS_GUILD_LEVEL);

    if (TP->query_priest_level() < TP->query_priest_level(gs))
    {
    	write("\nYou realise you are ready to become a " +
    	(TP->query_priest_level(gs) == GUILD_LEVEL_PRIEST ? "Priest" : "High Priest") +
    	".\n");

    	if (TP->query_priest_level(gs) == GUILD_LEVEL_PRIEST)
    	    to_priest = 1;
	    else
            to_priest = 2;
    }
    else if (TP->query_priest_sublevel() != TP->query_priest_sublevel(gs))
    {
    	TP->set_skill(PS_GUILD_LEVEL, gs);
    	write("\nYou feel an inner warmth as the Queen of Darkness " +
    	"recognizes your exploits and grants you a higher standing " +
    	"within the guild.\n");
    }

    write("\nYou rise again, feeling mentally refreshed.\n");

    if (to_priest)
    {
        object scroll;

        setuid();
        seteuid(getuid());
 
        if (to_priest == 1)
            scroll = clone_object(GUILDDIR + "obj/priest_scroll");
        else
            scroll = clone_object(GUILDDIR + "obj/high_priest_scroll");
            
        if (scroll)
        {
            if (priest && E(priest) == TO)
            {
                TP->catch_msg(QCTNAME(priest) + " gives you a scroll.\n");
                priest->say(" gives " + QTNAME(TP) + " something.\n");
            }
            else
            {
                write("A scroll suddenly materializes in your inventory!\n");
            }
            if (scroll->move(TP))
            {
                write("But the scroll is too heavy, and you drop it.\n");
                TP->say(" drops a scroll.\n");
                scroll->move(TO);
            }
        }
    }
            
    return 1;
}

int
do_pray(string arg)
{
    if (MEMBER(TP))
        return member_pray(arg);
        
	write("You kneel before the statue of Takhisis and offer up " +
	"a prayer to the Queen of Darkness.\n");
	tell_room(TO, QCTNAME(TP) + " kneels before the statue of " +
	"Takhisis and mutters a short prayer.\n", TP);

    return 1;
}

int
sanity_check(object pl, object tp)
{
    if (!pl || !P(pl,TO))
    {
    	tell_room(TO, "The prospective initiate has left the room, " +
    	"and the initiation is aborted.\n");
    	is_initiating = 0;
    	return 0;
    }

    if (!tp || !P(tp,TO))
    {
    	tell_room(TO,"The priest performing the initiation has left " +
    	"the room, and the initiation is aborted.\n");
    	is_initiating = 0;
    	return 0;
    }

    if (!priest || !P(priest,TO))
    {
    	tell_room(TO,"The Master of Rituals has left the room, and the " +
    	"initiation is aborted.\n");
    	is_initiating = 0;
    	return 0;
    }
    
    return 1;
}

void
finish_initiate(object pl, object tp)
{
    object sh;
    int i;

    if (!sanity_check(pl, tp))
        return;

    is_initiating = 0;
    
    setuid();
    seteuid(getuid());

    sh = clone_object(POTSHADOW);

    switch (sh->add_occ_shadow(pl))
    {
    	case 1:
    	pl->catch_msg("You are now a member of the Priests of Takhisis!\n");
    	tp->catch_msg("You successfully initiated " + pl->query_the_name(tp) +
    	" into the guild.\n");
    	tell_room(TO, QCTNAME(pl) + " is now a member of the Priests of " +
    	"Takhisis!\n", ({ pl }));
    	for (i=0; i<sizeof(PS_NUM); i++)
        {
    	    pl->remove_skill(PS_NUM[i]);
    	    pl->clear_guild_stat(SS_OCCUP);
        }
        if (ATTACKERS_ADMIN->remove_attacker(pl->query_real_name(),"joined the PoT") == "Ok.\n")
        {
            pl->catch_msg("As you join the guild, you are forgiven your past " +
            "transgressions against the guards of Neraka.\n");
        }
        (GUILD_ADMIN)->add_priest(pl, tp);
        (GUILD_ADMIN)->log(pl, "join", "Joined, initiated by " +
            C(tp->query_real_name()) + ".");
/*
        A_JOIN_LOG("pot/join","initiated by " + C(tp->query_real_name()),pl);
*/
        (NERAKA_ADMIN)->tell_neraka("temple/","You hear the muted sound of the " +
        "bells of the temple tolling.\n", 2);
        (NERAKA_ADMIN)->tell_neraka(({"temple/","inner/","outer/"}),
        "You hear the bells of the temple tolling, a low, omnious sound.\n",1);
	return;
    
        case -4:
        /* The player has an occ guild already, or one of his existing
         * guilds has blocked this one.
         */
        pl->catch_msg("Your other guilds don't want you in this one!\n");
        tell_room(TO, QCTNAME(pl) + " is split in loyalties, and cannot " +
        "finish the initiation.\n", pl);
	break;
    
        default:
        /* Some error in shadowing */
        tell_room(TO, "An error occured that prevented a successful " +
        "initiation. Report this to the responsible wizards!\n");
	break;
    }

    sh->remove_object();
}

void
perform_initiate(object pl, object tp, int round)
{
    string str;
    
    if (!sanity_check(pl,tp))
        return;
        
    switch(round)
    {
    	case 0:
    	    priest->command("say Here have we gathered; to bring into the priesthood");
    	    break;
    	case 1:
    	    priest->command("say One who is bold and daring, and serves the Queen.");
    	    break;
    	case 2:
    	    priest->command("say Now, young " + pl->query_name() + ", your pledge.");
    	    break;
    	case 4:
    	    str = "To the Queen of Darkness\nWith my soul, precious, priceless, do I pledge my life.\n";
    	    pl->catch_msg("You pledge: " + str);
    	    tell_room(TO,QCTNAME(pl) + " pledges: " + str, pl);
    	    break;
    	case 8:
    	    priest->command("say Who speaks for this " +
    	    (pl->query_gender() == 1 ? "woman" : "man") + "?");
    	    break;
    	case 9:
    	    str = "I do - \nAnd I serve the Queen; that I bring this new member\n" +
    	    "To serve, and to prosper - to bring glory and victory - \n" +
    	    "which is forseen by the Queen herself - to our guild.\n";
    	    tp->catch_msg("You declare: " + str);
    	    tell_room(TO,QCTNAME(tp) + " declares: " + str, tp);
    	    break;
    	case 12:
    	    str = "Victory and glory for the Dark Queen of Krynn!\n";
    	    tp->catch_msg("Together with " + QTNAME(priest) + ", you chant: " + str);
    	    tell_room(TO,QCTNAME(tp) + " and " + QTNAME(priest) + " chants: " + str, tp);
    	    break;
    	case 15:
    	    tp->catch_msg("You close your eyes and whisper a prayer to the Queen of Darkness.\n");
    	    tell_room(TO,QCTNAME(tp) + " closes " + HIS(tp) + " eyes.\n", tp);
    	    break;
        case 16:
            priest->command("say Mark this well; upon your arm will be marked");
            break;
        case 17:
            priest->command("say the likeness of a dragon, for like dragons we are.");
            break;
        case 18:
            priest->command("say And here - ");
            break;
        case 19:
            str = "In the name of the Queen!\n";
            tp->catch_msg("You cast your spell and shout: " + str);
            tell_room(TO,QCTNAME(tp) + " shouts: " + str, tp);

            tell_room(TO,"A light flashes and a medallion appears on the altar.\n");
            break;
        case 20:
            priest->command("say The symbol of the Queen's power.");
            break;
        case 21:
            priest->command("emote picks up the medallion from the altar.");
            break;
        case 22:
            pl->catch_msg(QCTNAME(priest) + " gives you a black medallion.\n");
            tell_room(TO,QCTNAME(priest) + " gives a black medallion to " +
            QTNAME(pl) + ".\n", pl);
            break;
        case 24:
            priest->command("say Wear it with pride, Initiate of Takhisis!");
            break;
        case 25:
            (NERAKA_ADMIN)->tell_neraka("temple/","The walls of the temple shake " +
            "as a loud thunderclap is heard!\n",3);
            (NERAKA_ADMIN)->tell_neraka(({"inner/","outer/"}),"A loud thunderclap " +
            "is heard from the direction of the temple.\n");
            break;
    }

    if (round < 25)
        set_alarm(2.0,0.0,&perform_initiate(pl,tp,round+1));
    else
        set_alarm(2.0,0.0,&finish_initiate(pl,tp));
}

int
do_initiate(string str)
{
    object pl, *i;
    string reason;
    
    if ((!MEMBER(TP) || (TP->query_priest_level() < 1)) && !TP->query_wiz_level())
        return 0;

    if (is_initiating)
    {
    	write("There is already an initiation in progress. Calm down.\n");
        return 1;
    }

    NF("Initiate whom?\n");
    if (!stringp(str) || str == "")
        return 0;

    if (!(pl = P(str,TO)))
        return 0;

    str = pl->query_the_name(TP);

    NF("Terwed is not here, most troubling!\n");
    if (!objectp(priest))
        return 0;

    if (!P(priest,TO))
    {
        priest->move_living("X",TO);
        priest->command("emote smiles apologetically.");
    }

    if (stringp(reason = (GUILD_ADMIN)->query_may_join(pl)))
    {
    	NF("You cannot initiate " + str + " because " + HE(pl) +
    	" is " + reason + ".\n");
    	return 0;
    }

    if (!pl->query_prop(TEMP_I_PREPARED))
    {
    	NF(C(str) + " has not prepared " + HIM(pl) + "self.\n");
    	return 0;
    }
    pl->remove_prop(TEMP_I_PREPARED);

    /* Perform some initiation ritual right here */

    write("You prepare to initiate " + str + ".\n");
    is_initiating = 1;

    set_alarm(2.0,0.0,&perform_initiate(pl,TP,0));
    return 1;
}

int
do_leave(string str)
{
    NF("If you want to leave, use the command <leave! priests>.\n");
    if (!stringp(str) || (str != "priests"))
        return 0;

    if ((time() - TP->query_prop(TEMPLE_WANT_TO_LEAVE)) > 60)
    {
        // Double-check. If the player wants to leave, he must repeat
        // the command within one minute.
        
        write("Are you sure you want to leave the Priests of Takhisis? " +
            "If you are, enter the same command once more!\n");
        TP->add_prop(TEMPLE_WANT_TO_LEAVE, time());
        return 1;
    }
    TP->remove_prop(TEMPLE_WANT_TO_LEAVE);        

    write("You renounce your vows to Takhisis, Queen of Darkness!\n");
    tell_room(TO, QCTNAME(TP) + " renounces " + HIS(TP) + " vows " +
    "to the Queen of Darkness!\n", TP);

    setuid();
    seteuid(getuid());

    (GUILD_ADMIN)->remove_priest(TP);
    (GUILD_ADMIN)->log(TP, "join", "Left on " +
        (({"his", "her", "its"})[TP->query_gender()]) + " own accord.");
/*
    A_JOIN_LOG("pot/join","left",TP);
*/

    write("You sink down to your knees as you feel the wrath of the " +
    "Dark Queen center upon you. An agony like worms feeding on your " +
    "soul course through your body, leaving you with an empty feeling, " +
    "as if something is lost.\n");
    tell_room(TO, QCTNAME(TP) + " sinks down to " + HIS(TP) + " knees " +
    "and scream in agony.\n", TP);

    /* punish_for_leaving defined in the soul, it is NOT called from
       the remove_occ_member function */
    TP->punish_for_leaving();
    TP->remove_occ_member();
    
    return 1;
}

/* Prepare.. it's just a small procedure so that players cannot shanghai
   other people that just happen to be in the same room and force
   them to join. :)
*/
int
do_prepare(string str)
{
    NF("Prepare what? Yourself?\n");
    if (!stringp(str) || (str != "myself"))
        return 0;

    if (MEMBER(TP))
    {
    	NF("Prepare yourself for what? You are already a member..\n");
    	return 0;
    }
    write("You prepare yourself to be initiated into the priesthood.\n");
    tell_room(TO, QCTNAME(TP) + " stands ready to be initiated.\n", TP);
    TP->add_prop(TEMP_I_PREPARED, 1);
    return 1;
}

public void
init()
{
    init_skill_raise();
    add_action(do_pray,"pray");
    add_action(do_initiate,"initiate");
    add_action(do_prepare,"prepare");
    add_action(do_leave,"leave!");
    ::init();
}
