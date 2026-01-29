inherit "/std/weapon";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <formulas.h>

public string
blade_desc()
{
    if (this_player()->query_prop(LIVE_I_UNDEAD))
    {
        return "The flawless silver blade shows a perfect " +
            "reflection of your face.\n";
    }

    return
        "You gaze into the flawless silver blade of the " + short() +
        "and see your own reflection in the metal.  As you look at it " +
        "longer, you notice your skin turn sallow, a sickly grey, your " +
        "eyes sink deep into the sockets.  Slowly you see yourself " +
        "deteriorate into a foul, rotting, diseased creature.  You " +
        "turn your eyes away, unable to watch any more.\n";
}

void
create_reaver_weapon()
{
}

nomask void
create_weapon()
{
    set_adj("silver");
    set_hit(40);
    set_pen(60);
    set_hands(W_BOTH);

    set_likely_break(0);
    set_likely_dull(0);

    set_wf(this_object());

    add_item(({ "blade", "silver blade", }), blade_desc);
        
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "The shiny surface of the blade is enchanted and is " +
        "especially reflective.\n", 10,
        "The silver is extremely resilient, holding a sharp edge " +
        "and being extremely resistant to breakage.\n", 20,
        "The weapon was created for a being of truly demonic " +
        "intent, and it resists being used by those of good " +
        "alignment.\n", 25,
        "Those of good alignment who try to wield this weapon can " +
        "be seriously injured by its magic.\n", 35,
        "The strange light reflected off of the blade can daze " +
        "opponents in a combat situation.\n", 45}));
    add_prop(OBJ_S_WIZINFO, "The weapon will not dull or break (under " +
        "normal circumstances).  1 in 20 turns it will stun the " +
        "wielder's opponent, adding 5 to 24 seconds of " +
        "LIVE_I_ATTACK_DELAY.  The weapon is evil:  those of good " +
        "alignment will take damage equal to twice their alignment when " +
        "wielding the weapon.\n");

    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME,  7000);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(40, 60) * 3 / 2);

    add_prop(OBJ_M_NO_BUY, 1);

    create_reaver_weapon();
}

public int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
    int dam)
{
    string name;

    if (random(20) ||
        !CAN_SEE(enemy, this_object()) || 
        (environment(enemy)->query_prop(OBJ_I_LIGHT) < 1) ||
        !query_prop(OBJ_I_IS_MAGIC_WEAPON) ||
        !wielder)
    {
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    name = enemy->query_the_name(wielder);
    wielder->catch_tell("As you bring the " + short() + " up to " +
        "swing at " + name + ", its silver blade catches the light.  " +
        "You see the bright flash of light reflected in " + 
        LANG_POSS(name) + " eyes, and " + enemy->query_pronoun() +
        "appears dazed.\n");

    enemy->catch_tell("As " + wielder->query_the_name(enemy) + " brings the " +
        short(enemy) + " up to swing at you, its silver blade catches the " +
        "light, flashing brightly.  The radiant glare dazes you slightly.\n");

    enemy->add_attack_delay(5 + random(20));

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

public int
disenchant_object()
{
    set_likely_break(4);
    set_hit(30);
    set_pen(40);

    if (wielded)
    {
        wielder->update_weapon(this_object());
    }

    remove_prop(OBJ_M_NO_BUY);
    remove_prop(OBJ_I_IS_MAGIC_WEAPON);
    remove_prop(MAGIC_AM_MAGIC);
    add_prop(MAGIC_AM_ID_INFO, ({ "The weapon once had some " +
        "magical properties, but is now powerless.\n", 50 }));

    set_long(query_long() + "The silvery blade appears to be " +
       "slightly tinged.\n");

    return 1;
}


public mixed
wield(object wep)
{
    int align;

    if (!query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
        return;
    }

    align = this_player()->query_alignment();

    if ((align > 99) && !this_player()->query_prop(LIVE_I_UNDEAD))
    {
        write("As you wield the " + short() + " an intense pain shoots through " +
            "your arms, into your chest.  Panic overwhelms you as you feel your " +
            "heart stop!\n");

        this_player()->heal_hp(-align * 2);
        
        if (this_player()->query_hp() <= 0)
	{
            this_player()->do_die(this_object());
            return 1;
	}

        set_alarm(1.0, 0.0, &(this_player())->catch_tell("A moment later, you are " +
            "relieved to feel your heart resume its pumping.\n"));
    }
        
    return 0;
}
