#pragma save_binary
#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit "/d/Emerald/lib/train";

#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>

#include "/d/Emerald/sys/skills.h"

#define WEAPON_SAVE (VAMP_LOG_DIR + "weapon")

int arch_block();

mapping chosen_weapon = ([]);
mapping cost_factor = ([]);

#define SK_ADD(sknum, desc, name, level) \
    sk_add_train(sknum, desc, name, 0, level)

void set_up_skills()
{
    create_skill_raise();


    SK_ADD(SS_DEFENSE, "dodge attacks", "defense", 90);
    SK_ADD(SS_PARRY, "parry attacks", "parry", 45);
    SK_ADD(SS_BLIND_COMBAT, "fight while blind", "blindfighting", 50);
    SK_ADD(SS_SNEAK, "sneak", "sneak", 80);
    SK_ADD(SS_AWARENESS, "perceive", "awareness", 90);
    SK_ADD(SS_HIDE, "hide", "hide", 85);
    SK_ADD(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat", 90);
    SK_ADD(SS_WEP_SWORD, "fight with swords", "sword", 75);
    SK_ADD(SS_WEP_KNIFE, "fight with knives", "knife", 75);
    SK_ADD(SS_WEP_POLEARM, "fight with polearms", "polearm", 75);
    SK_ADD(SS_WEP_CLUB, "fight with clubs", "club", 75);
    SK_ADD(SS_WEP_AXE, "fight with axes", "axe", 75);

  
    SK_ADD(SS_HUNTING, "hunt", "hunting", 70);
    SK_ADD(SS_LANGUAGE, "speak foreign and archaic languages", "language", 60);
    SK_ADD(SS_APPR_MON, "appraise enemies", "appraise enemy", 70);
    SK_ADD(SS_TRADING, "make deals", "trading", 60);
    SK_ADD(SS_SPELLCRAFT, "understand magical theory", "spellcraft", 40);

#ifdef SS_VAMP_FOCUS
    sk_add_train(SS_VAMP_FOCUS, "focus power", "focus",
        200, 50);
#endif

#ifdef SS_VAMP_SLASH
    sk_add_train(SS_VAMP_SLASH, "slash a victim", "slash", 80, 100);
#endif
}

int sk_no_train(object who)
{
  if (!IS_MEMBER(who) && !EMRLD_WIZ(who))
  {
    command("say Only true vampires may train here!");
    return 1;
  }

/*
  if (CHECK_PUNISHMENT(BAR, TP->query_real_name()))
  {
    command("say Sorry " + TP->query_name() + ", but you are " +
        "considered unworthy to train here.");
    return 1;
  }
*/

  return 0;
}

void create_vamp_room()
{
    set_short("Temple training room");

    set_long("   This area appears to be the temple's recreational " +
        "area and training facility.  Various books, guides, and " +
        "training implements can be found about the room.\n" +
        "To the north is a small, dark archway.\n");

    add_item(({ "books", "guides" }), "A great number of guides in the " +
        "form of journals, pamphlets, scrolls and books, their subjects vary " +
        "widely...from discussions on hunting to theories on focusing mental " +
        "powers to descriptions of combat techniques.\n");

    add_item(({ "implements", "training implements" }), "A wide array of physical " +
        "training equipment is available and in working condition.\n");

    add_item(({ "archway", "dark archway", "small archway", 
        "small dark archway" }), "The archway is obscured by a " +
        "dark aura emanating from it.  It is impossible to make " +
        "anything out in its perfect blackness.\n");

    add_exit("hall3", "west");
    add_exit("arch",  "north", arch_block);

    setuid();
    seteuid(getuid());

    /* It's a good idea to put this before set_up_skills() so
     * that the skills aren't added if some strange runtime
     * error prevents the mapping from being restored.
     */
    chosen_weapon = restore_map(WEAPON_SAVE);

    set_up_skills();
}

int arch_block()
{
#if 0
    write("Some force prevents you from entering.\n");
    return 1;
#else
    object archroom, *livings;

    archroom = find_object(VAMP_ROOM_DIR + "arch");

    if (archroom && sizeof(livings = FILTER_LIVE(all_inventory(archroom))))
    {
        write("You bump into someone who is already there.\n" +
            "There isn't enough room for you both!\n");
        livings->catch_msg("Someone trying to enter the archway bumps " +
            "into you.\n");
        return 1;
    }

    write("You pass into the blackness of the archway and immediately " +
        "sense powerful magic.\n");

    return 0;
#endif
}

int
sk_improve(string str)
{
    string pre, aft;

    /* "defence" can be spelled with an 's' */
    if (strlen(str) && sscanf(str, "%sdefense%s", pre, aft))
    {
        str = pre + "defence" + aft;
    }

    return ::sk_improve(str);
}

int
sk_query_max(int snum, int silent)
{
    int chosen, max = ::sk_query_max(snum, silent);
    string name;

    if (member_array(snum,
        ({ SS_WEP_SWORD, SS_WEP_AXE,
          SS_WEP_POLEARM, SS_WEP_CLUB,
          SS_WEP_KNIFE, SS_UNARM_COMBAT, SS_PARRY })) < 0)
    {
        return max;
    }

    name = this_player()->query_real_name();

    if (member_array(name, m_indices(chosen_weapon)) < 0)
    {
        chosen = SS_UNARM_COMBAT;
    }
    else
    {
        chosen = chosen_weapon[name];
    }

    if (snum == SS_PARRY)
    {
        return ((chosen != SS_UNARM_COMBAT) ? max : 0);
    }

    return ((snum == chosen) ? max : 0);
}

public int
sk_cost(int snum, int fr, int to)
{
    return ::sk_cost(snum, fr, to) * 
        (100 + cost_factor[this_player()->query_real_name()]) / 100;
}

int
select_weapon(string str)
{
    mapping m = ([ "sword"   : SS_WEP_SWORD,
  		   "axe"     : SS_WEP_AXE,
 		   "polearm" : SS_WEP_POLEARM,
          	   "knife"   : SS_WEP_KNIFE,
		   "club"    : SS_WEP_CLUB,
		   "unarmed combat" : SS_UNARM_COMBAT, ]);
    string name;

    if (!strlen(str) ||
        (member_array(str, m_indices(m)) < 0))
    {
        notify_fail("Possible selections are: " + 
            COMPOSITE_WORDS(m_indices(m)) + ".\n");
        return 0;
    }
   
    name = this_player()->query_real_name();

    if (member_array(name, m_indices(chosen_weapon)) >= 0)
    {
        cost_factor[name] += 10;
    }

    chosen_weapon[name] = m[str];

    setuid();
    seteuid(getuid());
    save_map(chosen_weapon, WEAPON_SAVE);

    write("Ok.\n");
    return 1;
}

void
init()
{
    ::init();
    init_skill_raise();

    add_action(select_weapon, "select");
}
