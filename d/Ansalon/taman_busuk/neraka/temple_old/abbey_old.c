/* Ashlar, 30 Sep 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../guild/guild.h"

inherit TEMPLE_BASE;
inherit "/lib/skill_raise";

#define A_JOIN_LOG(f, j, w) (log_file(f, sprintf("%s %15s %s the guild " + \
         "(%3d)\n", \
         extract(ctime(time()), 4), \
         C(w->query_real_name()),j, \
         w->query_average_stat()), \
      200000))


#define TEMP_I_PREPARED  "_temp_i_prepared"

void set_up_skills();

int levlim;
object priest;

void
reset_neraka_room()
{
    if (!objectp(priest))
        priest = clone_npc(NNPC + "terwed");    	
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
    	    spell_set += 128;
	case GUILD_LEVEL_PRIEST:
	    spell_set += 16652;
	case GUILD_LEVEL_INITIATE:
	    spell_set += 7202;
    }

    if ((~TP->query_skill(PS_SPELLS)) & spell_set)
    {
    	TP->set_skill(PS_SPELLS, TP->query_skill(PS_SPELLS) | spell_set);
    	write("\nIn a holy vision you realise that you have been granted " +
    	"more spells!\n");
    }

    /* Here is an example of a formula that might be used to determine
       guild level */

    gs = (5 * TP->query_stat(SS_OCCUP) + 2 * TP->query_stat(SS_WIS) +
        TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_ELEMENT_LIFE)) / 9;

    if (gs > 2 * TP->query_stat(SS_OCCUP))
        gs = 2 * TP->query_stat(SS_OCCUP);
        
    if (gs < TP->query_skill(PS_GUILD_LEVEL))
        gs = TP->query_skill(PS_GUILD_LEVEL);

    if (TP->query_priest_level() != TP->query_priest_level(gs))
    {
    	write("\nYou realise you are ready to become a " +
    	(TP->query_priest_level(gs) == GUILD_LEVEL_PRIEST ? "Priest" : "High Priest") +
    	".\n");
    	write("You should nag the resident wizard to code the neccessary functions " +
    	"for your promotion.\n");
    }
    else if (TP->query_priest_sublevel() != TP->query_priest_sublevel(gs))
    {
    	TP->set_skill(PS_GUILD_LEVEL, gs);
    	write("\nYou feel an inner warmth as the Queen of Darkness " +
    	"recognizes your exploits and grant you a higher standing " +
    	"within the guild.\n");
    }

    write("\nYou rise again, feeling mentally refreshed.\n");
    return 1;
}

int
do_pray(string arg)
{
    if (MEMBER(TP))
        return member_pray(arg);
        
    if (!stringp(arg) || arg == "")
    {
    	NF("Pray for what?\n");
    	return 0;
    }
    arg = lower_case(arg);

    if (arg == "for lord devrail's swift return" ||
        arg == "for lord devrail's swift return.")
    {
    	write("You kneel before the statue of Takhisis and pray for " +
    	"the swift return of Lord Devrail.\n");
    	tell_room(TO, QCTNAME(TP) + " kneels before the statue of " +
    	"Takhisis and mutters a short prayer.\n", TP);

    	if (interactive(TP))
    	{
    	    setuid();
    	    seteuid(getuid());

    	    write_file(NERAKA + "log/prayers",
    	        sprintf("%s %-45s (%3d)\n",
                extract(ctime(time()), 4), 
                C(TP->query_real_name()) + " prayed for the swift return",
                TP->query_average_stat()));
    	}
    	return 1;
    }
    NF("Pray for what? Lord Devrail's swift return?\n");
    return 0;
}

void
finish_initiate(object pl, object tp)
{
    object sh;
    int i;

    if (!pl || !P(pl,TO))
    {
    	tell_room(TO, "The prospective initiate has left the room, " +
    	"and the initiation is aborted.\n");
    	return;
    }

    if (!tp || !P(tp,TO))
    {
    	tell_room(TO,"The priest performing the initiation has left " +
    	"the room, and the initiation is aborted.\n");
    	return;
    }
    
    setuid();
    seteuid(getuid());

    sh = clone_object(GUILDDIR + "obj/occ_shadow");

    switch (sh->add_occ_shadow(pl))
    {
    	case 1:
    	pl->catch_msg("You are now a member of the Priests of Takhisis!\n");
    	tp->catch_msg("You successfully initiated " + pl->query_the_name(tp) +
    	" into the guild.\n");
    	tell_room(TO, QCTNAME(pl) + " is now a member of the Priests of " +
    	"Takhisis!\n", ({ pl, tp }));
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
        A_JOIN_LOG("pot/join","joined",pl);
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

int
do_initiate(string str)
{
    object pl;
    string reason;
    
    if (!MEMBER(TP) || !(TP->query_priest_level() >= GUILD_LEVEL_PRIEST))
        return 0;

    NF("Initiate whom?\n");
    if (!stringp(str) || str == "")
        return 0;

    if (!(pl = P(str,TO)))
        return 0;

    str = pl->query_the_name(TP);

    NF("Terwed is not here.\n");
    if (!P(priest,TO))
        return 0;

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

    set_alarm(2.0,0.0,&finish_initiate(pl,TP));
    return 1;
}

int
do_leave(string str)
{
    NF("If you want to leave, use the command <leave! priests>.\n");
    if (!stringp(str) || (str != "priests"))
        return 0;

    write("You renounce your vows to Takhisis, Queen of Darkness!\n");
    tell_room(TO, QCTNAME(TP) + " renounces " + HIS(TP) + " vows " +
    "to the Queen of Darkness!\n", TP);

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

void
set_up_skills()
{
    sk_add_train(SS_SPELLCRAFT,         "cast spells",         0, 0, 75 );
    sk_add_train(SS_ELEMENT_LIFE,       "cast life spells",    0, 0, 75 );
    sk_add_train(SS_FORM_ENCHANTMENT,   "cast enchantments",   0, 0, 75 );
    sk_add_train(SS_FORM_DIVINATION,    "divine information",  0, 0, 45 );
    sk_add_train(SS_FORM_ABJURATION,    "dispel magic",        0, 0, 45 );
}

int
sk_improve(string sk)
{
    if (sk)
    {
        if (!MEMBER(TP))
        {
        
            NF("You are no member of this guild, you cannot train "+
              "here.\n");

            write("Only Priests of Takhisis can improve their skills "+
              "here.\n");
            return 1;
        }
    }

    if (!P(priest, TO))
    {
        write("There is noone here to train you.\n");
        return 1;
    }

    return ::sk_improve(sk);
}

int
sk_query_max(int snum)
{
    int lev, mxtrain, *skills_available_here;
    mixed skval;
    object pl;
    int sum,tm;

    skills_available_here = sk_query_train();

    if(member_array(snum, skills_available_here) == -1)
        return 0;

    if (!this_player() || ((this_player() != previous_object()) &&
        previous_object() != this_object()))
        pl = previous_object();
    else
        pl = this_player();

    if (MEMBER(pl))
    {
        lev = pl->query_priest_level();
        mxtrain = MAX_SKILL_LEVEL[lev][snum];
    }
    else
        mxtrain = 0;

    if (!mappingp(sk_default))
        return 0;

    /* Do some fancy calculation according to the rules on training
       magic skills:
                Prime element (LIFE):           100% of INT
                Secondary element (AIR):        80% of INT
                Total of all elements:          200% of INT

                Any form:                       100% of WIS
                Total of all forms:             200% of WIS
       
     */
    switch(snum)
    {
    	case SS_ELEMENT_LIFE:
    	case SS_ELEMENT_AIR:
    	    sum = pl->query_skill(SS_ELEMENT_LIFE) + pl->query_skill(SS_ELEMENT_DEATH) +
            pl->query_skill(SS_ELEMENT_AIR) + pl->query_skill(SS_ELEMENT_EARTH) +
            pl->query_skill(SS_ELEMENT_WATER) + pl->query_skill(SS_ELEMENT_FIRE);

            tm = mxtrain - pl->query_skill(snum);
            
            if (sum + tm > 2 * pl->query_stat(SS_INT))
    	        mxtrain -= sum + tm - 2 * pl->query_stat(SS_INT);
    	    if ((snum == SS_ELEMENT_LIFE) && (mxtrain > pl->query_stat(SS_INT)))
    	        mxtrain = pl->query_stat(SS_INT);
    	    if ((snum == SS_ELEMENT_AIR) && (mxtrain > (8 * pl->query_stat(SS_INT)) / 10))
    	        mxtrain = (8 * pl->query_stat(SS_INT)) / 10;
            break;

        case SS_FORM_ENCHANTMENT:
        case SS_FORM_DIVINATION:
        case SS_FORM_ABJURATION:
        case SS_FORM_TRANSMUTATION:
        case SS_FORM_ILLUSION:
            sum = pl->query_skill(SS_FORM_ENCHANTMENT) +
            pl->query_skill(SS_FORM_DIVINATION) +
            pl->query_skill(SS_FORM_ABJURATION) +
            pl->query_skill(SS_FORM_TRANSMUTATION) +
            pl->query_skill(SS_FORM_ILLUSION) +
            pl->query_skill(SS_FORM_CONJURATION);

            tm = mxtrain - pl->query_skill(snum);

            if (sum + tm > 2 * pl->query_stat(SS_WIS))
                mxtrain -= sum + tm - 2 * pl->query_stat(SS_WIS);

            if (mxtrain > pl->query_stat(SS_WIS))
                mxtrain = pl->query_stat(SS_WIS);
            break;
    }

    skval = sk_trains[snum];

    if (skval[2] < mxtrain)
    {
        mxtrain = skval[2];
        levlim = 0;
    }
    else
        levlim = 1;

    if (sizeof(skval) > 2)
        return mxtrain;
    else
        return 0;
}

int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
      "seek knowledge elsewhere.\n");
    if (levlim)
        notify_fail("Your position in the guild does not allow further " +
        "training of this skill.\n");
    return 0;
}

