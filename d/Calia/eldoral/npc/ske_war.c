/*
 * ske_war.c
 *
 * The main npc's of the caverns beneath Castle Chimera.
 * The skeletal warriors have a 'fear' special, and nothing
 * but magic weapons, magic attacks, or normal attacks with
 * high wcpens will hit them.
 * 
 * Khail - Feb 12/97
 */
#pragma strict_type

#include "defs.h"

inherit UNDEAD;

/*
 * Function name: arm_me
 * Description  : Clones in the skeletal warrior's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
arm_me()
{
    seteuid(getuid());

    clone_object(WEP + "ske_sword")->move(TO);
    tell_room(environment(), "The skeletal warrior draws forth " +
        "a longsword from the very shadows themselves.\n");
    command("wield all");
    clone_object(ARM + "ske_chain")->move(TO);
    tell_room(environment(), "The skeletal warrior seems to pull " +
        "the shadows about itself, where they coalesce into a dark " +
        "chainmail.\n");
    command("wear all");
}

public string
random_adj()
{
    string *adjs = ({"putrid", "filthy", "slimy", "dusty",
        "sooty", "decayed", "worm-eaten", "moth-eaten", 
        "mouldy", "moss-covered", "mildewed", "yellowed",
        "cobweb-covered", "nine-fingered", "nine-toed",
        "knock-kneed", "bowlegged", "pigeon-toed", "hunchbacked",
        "toothless", "buck-toothed", "slack-jawed", "stiff-necked"});

    return adjs[random(sizeof(adjs))];
}

/*
 * Function name: create_monster
 * Description  : Turns this object into a skeletal warrior.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_monster()
{
    set_name("warrior");
    add_name("undead");
    add_name("skeleton");
    add_name(SKELETAL_WARRIOR);
    set_adj(random_adj());
    add_adj("skeletal");
    set_race_name("human");
    set_short(query_adj() + " skeletal warrior");
    set_long("This horrific creature before you appears to have " +
        "once been a human warrior, possibly a knight of some " +
        "kind, but through some twisted act of fate or man, has " +
        "been doomed to spend eternity in life-in-death, a decayed " +
        "skeleton still behaving as if it were alive, with one " +
        "difference; an intense hatred for all things living.\n");
    create_undead_monster(UNDEAD_WARRIOR);
    remove_prop(LIVE_I_NO_CORPSE);
}

/*
 * Function name: special_attack
 * Description  : Controls the skeletal warrior's special attacks in
 *                combat. Decides which to use, if any.
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 1 - Made attack, no further attacks this round.
 *                0 - No special attack, continue normal combat round.
 */
public int
special_attack(object enemy)
{
  /* 90% of the time, no special attack. */
    if((random(100) + 1) <= 90)
    return 0;

  /* Fear. No mana, it's an 'innate' ability. */
    tell_object(enemy, "Suddenly, waves of fear seem to emanate " +
        "from the skeletal warrior, clutching your heart in " +
        "terror!\n");
    enemy->add_panic(random(50));
    return 1;        
}

/*
 * Function name: make_corpse
 * Description  : Simply makes a 'corpse' for when the skeletal warrior
 *                dies, a pile of bones, in this case.
 * Arguments    : n/a
 * Returns      : object pointer to the new corpse.
 */
public mixed
make_corpse()
{
    mixed ob;

    reset_euid();
    ob = clone_object(OBJ + "skeleton_corpse");
    ob->add_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
    ob->add_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
    ob->add_prop(CONT_I_TRANSP, 1);
    ob->add_prop(CONT_I_MAX_WEIGHT, query_prop(CONT_I_MAX_WEIGHT));
    ob->add_prop(CONT_I_MAX_VOLUME, query_prop(CONT_I_MAX_VOLUME));
    return ob;
}    