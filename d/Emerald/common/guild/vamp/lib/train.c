inherit "/d/Emerald/lib/train";

#include "/d/Emerald/common/guild/vamp/guild.h"
#include "/d/Emerald/sys/skills.h"
#include <ss_types.h>

mapping chosen_weapon = ([]);
mapping cost_factor = ([]);

#define SK_ADD(sknum, desc, name, level) \
    sk_add_train(sknum, desc, name, 0, level)

void set_up_skills()
{
    create_skill_raise();

    setuid();
    seteuid(getuid());

    /* It's a good idea to put this before set_up_skills() so
     * that the skills aren't added if some strange runtime
     * error prevents the mapping from being restored.
     */
    chosen_weapon = restore_map(WEAPON_SAVE);

    SK_ADD(SS_DEFENSE, "dodge attacks", "defense", 90);
    SK_ADD(SS_PARRY, "parry attacks", "parry", 45);
    SK_ADD(SS_BLIND_COMBAT, "fight while blind", "blindfighting", 40);
    SK_ADD(SS_SNEAK, "sneak", "sneak", 75);
    SK_ADD(SS_AWARENESS, "perceive", "awareness", 90);
    SK_ADD(SS_HIDE, "hide", "hide", 75);
    SK_ADD(SS_APPR_MON, "appraise enemies", "appraise enemy", 75);
    SK_ADD(SS_HUNTING, "hunt", "hunting", 75);
    SK_ADD(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat", 90);
    SK_ADD(SS_WEP_SWORD, "fight with swords", "sword", 75);
    SK_ADD(SS_WEP_KNIFE, "fight with knives", "knife", 75);
    SK_ADD(SS_WEP_POLEARM, "fight with polearms", "polearm", 75);
    SK_ADD(SS_WEP_CLUB, "fight with clubs", "club", 75);
    SK_ADD(SS_WEP_AXE, "fight with axes", "axe", 75);

    SK_ADD(SS_LANGUAGE, "speak foreign and archaic languages", "language", 60);
    SK_ADD(SS_TRADING, "make shrewd deals", "trading", 60);
    SK_ADD(SS_SPELLCRAFT, "understand magical theory", "spellcraft", 50);
    SK_ADD(SS_ELEMENT_DEATH, "manipulate the element of death",
	   "death magic", 40);
    SK_ADD(SS_ELEMENT_AIR, "manipulate the element of air", "air magic", 40);
    SK_ADD(SS_FORM_ILLUSION, "produce illusions", "illusion", 40);
    SK_ADD(SS_FORM_ENCHANTMENT, "produce enchantments", "enchantment", 40);
    SK_ADD(SS_FORM_ABJURATION, "resist and dispel magic", "abjuration", 60);

#undef SS_VAMP_FOCUS
#ifdef SS_VAMP_FOCUS
    sk_add_train(SS_VAMP_FOCUS, "focus power", "focus",
        200, 50);
#endif

#ifdef SS_VAMP_SLASH
    sk_add_train(SS_VAMP_SLASH, "slash a victim", "slash", 80, 100);
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

>>()
{
   set_up_skills();
}
