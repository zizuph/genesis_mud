/*
 * The Keepers of Telberin
 */

inherit "/std/guild/guild_race_sh";

void delay_init_keepers();
void remove_kot_member();

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <const.h>
#include <stdproperties.h>

#define MIN_ALIGN -159
#define SW shadow_who

#define MEMBER_LOG(msg) \
    setuid(); \
    seteuid(getuid()); \
    write_file(KOT_LOG_DIR + "member.log", ctime(time()) + " " + msg + "\n");

    
mixed *warrior_titles = ({
    "Royal Squire",
    "Sentry",
    "Guard",
    "Warrior",
    "Corporal",
    "Loyal Lieutenant",
    "Dedicated Captain",
    "Sergeant",
    ({ "Lord Sergeant", "Lady Sergeant"}),
    "General",
    ({ "Lord General", "Lady General" }),
    "Commander",
    ({ "Lord Commander", "Lady Commander" }),
    });

mixed *cleric_titles = ({
    "Servant",
    "Page",
    "Scout",
    "Missionary",
    "Paladin",
    "Protector",
    "Warden",
    "Bishop",
    ({ "Lord Bishop", "Lady Bishop"}),
    "Archbishop",
    ({ "Lord Archbishop", "Lady Archbishop"}),
    "Cardinal", 
    ({ "Lord Cardinal", "Lady Cardinal"}),
    });

static int caste = WARRIOR_CASTE;

int query_kot_council_member();
int query_kot_caste();

int
query_guild_tax_race()
{
    return GUILD_TAX;
}

string
query_guild_style_race()
{
    return ((caste == WARRIOR_CASTE) ? "fighter" : "cleric");
}

string
query_guild_name_race()
{
    return GUILD_NAME;
}

#ifdef GUILD_POST
string
query_def_post()
{
    if (this_player()->query_default_start_location() == GUILD_STARTLOC)
    {
        return GUILD_POST;
    }

    return SW->query_def_post();
}
#endif

mixed
acceptable_kot_member(object player)
{
    if (player->query_race() != "elf")
    {
        return "Only elves are worthy to serve in the Keepers of " +
            "Telberin!\n";
    }

    if (player->query_alignment() < MIN_ALIGN)
    {
        return "Your evil deeds are a disgrace to the Keepers of " +
            "Telberin!\n";
    }

    if (player->query_prop(LIVE_I_UNDEAD))
    {
        return "The foul influence of undead cannot be permitted " +
            "within the Keepers of Telberin!\n";
    }

    return 0;
}
    
int 
query_guild_keep_player(object player)
{
    mixed why;

    if (stringp(why = acceptable_kot_member(player)))
    {
        set_alarm(0.5, 0.0, &tell_object(SW, why));
        set_alarm(1.0, 0.0, remove_kot_member);
    }

    return 1;
}

int
query_kot_member()
{
    return 1;
}

int
query_kot_caste()
{
    return caste;
}

public mixed
query_guild_trainer_race()
{
    return ((caste == WARRIOR_CASTE) ? KOT_ROOM_DIR + "kot_hq3.c" :
                                       KOT_ROOM_DIR + "kot_hq2.c");
}

void
set_kot_caste(int i)
{
    caste = i;

    setuid();
    seteuid(getuid());
    MANAGER->set_caste(SW, i);
}

int
query_telberin_level()
{
    if (caste == WARRIOR_CASTE) 
    {
        return min(90, max(SW->query_skill(SS_WEP_SWORD),
                 SW->query_skill(SS_WEP_AXE),
                 SW->query_skill(SS_WEP_KNIFE)));
    }

    if (caste == CLERIC_CASTE)
    {
	return min(90, SW->query_skill(SS_SPELLCRAFT));
    }

    return 0;
}

varargs int
query_kot_level(int refuse)
{
    int level = (query_telberin_level() + 
        SW->query_base_stat(SS_RACE)) / 14;

    int frozen_level;

    level = min(sizeof(((caste == WARRIOR_CASTE) ? 
        warrior_titles : cleric_titles)) - 1, level);

    if (!refuse)
    {
        return level;
    }

    setuid();
    seteuid(getuid());

    frozen_level = MANAGER->query_level_frozen(SW);
    
    if (frozen_level == -1)
    {
        return level;
    }
    
    return min(frozen_level, level);
}

string
query_guild_title_race()
{
    int stat, gender;
    mixed rank;

    if (query_kot_council_member())
    {
        if (query_kot_caste() == WARRIOR_CASTE)
	{
            return "Regent of the Keepers of Telberin, " +
                "High Keeper of the Protectorate of Telberin";
	}
        
        return "Regent of the Keepers of Telberin, " +
            "High Chamberlain of the Order of Telan-Ri";
    }

    gender = SW->query_gender();
    if (gender == G_NEUTER)
    {
	gender = G_MALE;
    }
    
    stat = query_kot_level(1);

    setuid();
    seteuid(getuid());

    if (caste == WARRIOR_CASTE)
    {
        stat = max(0, min(sizeof(warrior_titles), stat));
	rank = (pointerp(warrior_titles[stat]) ? 
            warrior_titles[stat][gender] : warrior_titles[stat]);
	return rank + " of the Protectorate of Telberin";
    } 

    if (caste == CLERIC_CASTE)
    {
        stat = max(0, min(sizeof(cleric_titles), stat));
	rank = (pointerp(cleric_titles[stat]) ? 
            cleric_titles[stat][gender] : cleric_titles[stat]);
	return rank + " of the Order of Telan-Ri";
    }

    return "";
}

void
delay_init_keepers()
{
    object ob;

    setuid();
    seteuid(getuid());

#ifdef GUILD_OBJECT
    ob = clone_object(GUILD_OBJECT);
    ob->move(SW, 1);
#endif

#ifdef GUILD_SOUL
    SW->add_cmdsoul(GUILD_SOUL);
    SW->update_hooks();
#endif

    if (caste == CLERIC_CASTE)
    {
#ifdef GUILD_SOUL_CLERIC
        SW->add_cmdsoul(GUILD_SOUL_CLERIC);
        SW->update_hooks();
#endif

#ifdef GUILD_OBJECT_CLERIC
        ob = clone_object(GUILD_OBJECT_CLERIC);
        ob->move(SW, 1);
#endif

#ifdef SPELL_OBJECT_CLERIC
        ob = clone_object(SPELL_OBJECT_CLERIC);
        ob->move(SW, 1);
#endif
    }
    else
    {
#ifdef GUILD_OBJECT_WARRIOR
        ob = clone_object(GUILD_OBJECT_WARRIOR);
        ob->move(SW, 1);
#endif
    
#ifdef GUILD_SOUL_WARRIOR
	if (caste == WARRIOR_CASTE)
	{
	    SW->add_cmdsoul(GUILD_SOUL_WARRIOR);
	    SW->update_hooks();
	}
#endif
    }
}

void
init_race_shadow(string str)
{
#ifdef GUILD_CLOSED
    SW->clear_guild_stat(SS_RACE);
    remove_guild_race();
    return; 
#endif

    set_alarm(1.0, 0.0, delay_init_keepers);

    setuid();
    seteuid(getuid());

    caste = MANAGER->query_caste(SW);
}

varargs int
add_kot_shadow(object who, int caste = WARRIOR_CASTE)
{
    return shadow_me(who, "race",
        ((caste == WARRIOR_CASTE) ? "fighter" : "cleric"), GUILD_NAME);
}

int
add_kot_member(object who, int caste)
{
    int ret = add_kot_shadow(who);

    if (ret == 1)
    {
        setuid();
        seteuid(getuid());

        MEMBER_LOG(capitalize(who->query_real_name()) + " joined.");
        MANAGER->add_member(who);

        set_kot_caste(caste);
    }

    return ret;
}

public void
set_alignment(int a)
{
    SW->set_alignment(a);

    if ( (a < -79) && (a >= MIN_ALIGN) )
    {
	// the player is disagreeable now
	SW->catch_msg("You get the sickening feeling that your "+
			      "soul is polluted in some way.\n");
    }

    if ( a < MIN_ALIGN )
    {
	// the player is untrustworthy , or worse!
	SW->catch_tell("Suddenly standing before you, towering "+
			      "over your small form, is a shimmering, "+
			      "transluscent image of Vilgurn!\n");
	SW->catch_tell("The shimmering form of Vilgurn shouts "+
			      "directly into your mind: You have disgraced "+
			      "Telan-Ri and all that which He stands for! "+
			      "You are no longer worthy of companionship "+
			      "with us, nor of His blessings!!\n");
	SW->catch_tell("You howl in agony as you feel an unseen "+
			      "force pull at your very soul!!\n\n");
	tell_room(environment(SW),
                 QCTNAME(SW) + " howls in agony!\n", SW);

        remove_kot_member();
    }
}

void
remove_kot_member()
{
    setuid();
    seteuid(getuid());

    MEMBER_LOG(capitalize(SW->query_real_name()) + " left.");

    deep_inventory(SW)->remove_kot_object();

#ifdef GUILD_SOUL
    SW->remove_cmdsoul(GUILD_SOUL);
    SW->update_hooks();
#endif

#ifdef GUILD_SOUL_CLERIC
    SW->remove_cmdsoul(GUILD_SOUL_CLERIC);
    SW->update_hooks();
#endif

#ifdef GUILD_SOUL_WARRIOR
    SW->remove_cmdsoul(GUILD_SOUL_WARRIOR);
    SW->update_hooks();
#endif

#ifdef GUILD_STARTLOC
    if (SW->query_default_start_location() == GUILD_STARTLOC)
    {
        SW->set_default_start_location(SW->query_def_start());
    }
#endif

    MANAGER->remove_member(SW);

    SW->clear_guild_stat(SS_RACE); 
    remove_guild_race();
}

int
query_kot_council_member()
{
    setuid();
    seteuid(getuid());

    return MANAGER->query_council_member(SW);
}

int
query_guild_leader_race()
{
    return query_kot_council_member();
}
