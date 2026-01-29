/* This is a wise old elf mage. He is needed for various Emerald quests.  */
/* He doesn't look as tough as the black dragon, but he does have a few   */
/* little tricks up his sleeve. I don't expect many people to kill him.   */
/* In fact, if a mortal manages to kill this guy, I'll eat my hat (and I  */
/* do have an edible hat ready, just in case!).                           */
/* Pink Floyd fans (like me) should check out the 'brain damage' spell... */
/* If you want to meet him, goto /d/Emerald/cave/levelc/cave27c.          */
/* Original coded by Tulix 13/6/1993. 
/* Recoded 27/05/96 by Tulix III, with new 'triggers' (emote hooks) based */
/* on the example coded by Tricky/Nick/Mercade.                           */

inherit "/std/monster";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/mountains/mtblack/cave/pearl_defs.h"
#include "/d/Emerald/mountains/mtblack/cave/nemesis_defs.h"

/* Always best to keep Mercade happy... */
#pragma strict_types

/* Lets have a few definitions to make life easier. */
#define HOOKED_EMOTIONS ({ "chuckle", "cry", "flip", "hug", "kick", \
    "kiss", "poke", "slap", "smile", "spit", "swear", "yawn" })
#define CHECK_ACTOR if (!present(actor, environment())) { return; }

/* Global variables used to track objects he has been given. */            
public string *players_given_me_powder, *players_given_me_coin;

/* Prototype functions - quite a few of them. */ 
public int do_heal_me_spell(object me);
public int fireball_spell(object me, object enemy);
public int lighting_spell(object me, object enemy);
public int shield_spell(object me);
public int dim_door_spell(object me);
public int haste_spell(object me);
public int intox_spell(object me);
public int steal_mana_spell(object me, object enemy);
public int stun_spell(object me, object enemy);
public int slow_spell(object me, object enemy);
public int gas_spell(object me, object enemy);
public int blast_spell(object me, object enemy);
public int teleport_spell(object me, object enemy);
public int brain_damage_spell(object me, object enemy);
public int plexus_block(string str);
public void check_wimp(object enemy);
public void enemy_flee(object enemy);
public void arm_me();
public void make_ointment(object from);
public void return_item(object ob, object from);
public void receive_nemesis_sword(object ob, object from);
public void swing_nemesis_sword(object ob, object from);
public void slash_nemesis_sword(object ob, object from);
public void flip_nemesis_sword(object ob, object from);
public void thrust_nemesis_sword(object ob, object from);
public void finish_with_nemesis_sword(object ob, object from);
public void reward_player_for_sword(object ob, object from);
public void introduce_npc(string name);
public void greet_player(object player);
public string quest_list();
public string knight_quest_info();
public string sword_quest_info();

/* 
 * Function name: create_monster
 * Description:   Define the basic npc features: race, skills, chat, etc.
 */
public void
create_monster()
{
    if (!IS_CLONE)
        return;

    /* Give him an original name. */
    set_name("enzalcaspin");
    
    /* Set an appropriate title, as we will be introduced to players. */
    set_title("the Great Enchanter and Master Spell-weaver");
    
    /* The name 'Enzalcaspin' was banished so that mortals can't use it. */
    set_living_name("enzalcaspin");
    set_race_name("elf");
    set_adj(({"wise", "old"}));
    add_name("mage");
    
    set_short("wise old elf mage");
    set_long("This is the legendary mage who is known throughout the world "
        +"as Enzalcaspin. The stories told about this man could quite "
        +"easily fill a large book: tales stretching back over dozens of "
        +"generations. Mages of the past were often hunted down and killed "
        +"by those who feared their power - but not this one. His eyes "
        +"show a kind of wisdom and experience that defies the ever "
        +"onward march of time. He may not be very tall for an elf, "
        +"but this is a man to be reckoned with.\n");
 
    add_prop(OBJ_S_WIZINFO, "Alas, most npcs are pretty dumb. " +
        "This one is not though - like (most) mortals, this one will " +
        "run away when things look bad. His spells make him tough enough " +
        "to deal with most mortals, too. If you want to find him, goto " +
        "/d/Emerald/cave/levelc/cave27c. He is needed for quests.\n");

    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(CONT_I_HEIGHT, 160);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(MAGIC_I_BREATH_WATER, 100);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_gender(0);                                        /* Male */
 
    /* This guy is needed for quests, so we don't want him dying. */
    /* Stats -   STR  DEX  CON  INT  WIS  DIS                     */
    set_stats(({ 190, 230, 180, 240, 200, 100 }));      /* Tough. */
    set_alignment(1200);    /* Hes killed lots of evil dragons... */
    set_hp(10000);                                  /* Full heal. */
    set_mana(10000);                                /* Full mana. */
 
    /* Set unarmed armour class, and he's an elf - no tough hide. */
    set_all_hitloc_unarmed(10);
 
    /* Set the all important combat skills. */
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 150);
 
    /* This is a man of magic */
    set_skill(SS_SPELLCRAFT, 150);
    set_skill(SS_HERBALISM, 100);
    set_skill(SS_ALCHEMY, 100);
 
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_DIVINATION, 100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_ABJURATION, 100);
 
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
 
    set_skill(SS_LANGUAGE, 100);
    set_skill(SS_CLIMB, 50);
    set_skill(SS_SWIM, 50);
    set_skill(SS_AWARENESS, 100);
 
    set_chat_time(10);                         /* Set speaking interval. */
    add_chat("Have you seen the Nemesis sword anywhere?");
    add_chat("I wish I knew what happened to my sword.");
    add_chat("I don't get too many visitors you know.");
    add_chat("People should place more trust in magic.");
    add_chat("I ought to get out and about more often.");
    add_chat("It seems strange how the old ways of magic are often ignored.");
    add_chat("I wonder if Artolmeus has learned his lesson yet?");
    add_chat("Perhaps turning that Knight into an octopus was a bit harsh.");

    /* Lets give this chap a few original one-liners for when in combat. */
    
    set_cchat_time(2);                  /* Set combat speaking interval. */
    add_cchat("Let's hope you remembered to write a will.");
    add_cchat("By the way, would you prefer to be buried or cremated...?");
    add_cchat("I hope you're on good terms with the grim reaper....");
    add_cchat("If you want another scar, so be it!");
    add_cchat("I suppose you lot will learn eventually.....");
    add_cchat("I hope your blood won't stain the carpet too much.");
    add_cchat("Die, unbeliever of the power of magic!");
    add_cchat("Perish like the others who have attacked me.");

    set_act_time(12);                            /* Set action interval. */
    add_act("smile");
    add_act("emote scratches his head.");
    add_act("emote smiles warmly, thinking of days long since passed.");
    add_act("emote ponders deeply the old ways of magic.");
    add_act("emote looks at you with a twinkle in his eyes.");
    add_act("emote tries to look thoughtful, and succeeds.");
    add_act("brighten");
    add_act("ponder");
    
    /* Give out quest information when asked. */
    add_ask(({"quest", "quests", "task", "tasks"}), VBFC_ME("quest_list"));
    add_ask(({"sword", "nemesis sword", "Nemesis sword", "the nemesis sword",
        "the Nemesis sword"}), VBFC_ME("sword_quest_info"));
    add_ask(({"artolmeus", "knight", "octopus", "quest", "quests", "pearl"}), 
        VBFC_ME("knight_quest_info"));
    
    /* Set uid & euid so that he can clone things. */
    setuid();
    seteuid(getuid());

    players_given_me_powder = ({ });
    players_given_me_coin =({ });
}
 
/*
 * Below are all the combat related functions - spells, etc.
 */

/* 
 * Function name: special_attack
 * Description:   Decide whether we cast a spell, or use a normal attack.
 * Arguments:     enemy: The target of the attack.
 * Returns:       0 = spell was not cast, so continue with normal attack.
 *                1 = spell was cast, so do not carry out normal attack.
 */
public int
special_attack(object enemy)
{
    object me, shield;
    int num;

    me = TO;
    
    /* Most npcs are stupid. This one is a little bit smarter! */
    
    /* Lets check to see if he has taken much damage. */
    if (me->query_hp() <= 1200)
    {    
        /* If we have enough mana to heal, do so... */
        if (me->do_heal_me_spell(me))
            return 1;
        else
        {
            /* If not, steal some, then teleport away. */
            me->steal_mana_spell(me, enemy);
            return (me->dim_door_spell(me));
        }
    }
    
    /* Check to see if the magical shield has worn off yet. */
    shield = present("enz_magic_shield", me);
    if (!shield)
    {
        if (!me->shield_spell(me));
            return 0;
        if (!me->haste_spell(me));
            return 0;
        if (!me->intox_spell(me));
            return 0;
    }
    
    num = random(1000);
    
    /* This routine determines which spell we cast (if any). */
    if (num >= 750)
    {
        /* No spell cast this time - carry out normal attack */
        return 0;
    }
    
    if (num >= 600)
        return (me->fireball_spell(me, enemy));
 
    if (num >= 500)
        return (me->lightning_spell(me, enemy));
    
    if (num >= 400)
        return (me->steal_mana_spell(me, enemy));
    
    if (num >= 300)
        return (me->stun_spell(me, enemy));

    if (num >= 200)
        return (me->slow_spell(me, enemy));
    
    if (num >= 100)
        return (me->blast_spell(me, enemy));
    
    if (num >= 15)
        return (me->gas_spell(me, enemy));
    
    if (num >= 4)
        return (me->teleport_spell(me, enemy));
    
    /* There is a 1 in 333 chance of this next spell being cast. */
    if ((num) == 3 || (num) == 2 || (num == 1))
        return (me->brain_damage_spell(me, enemy));

    /* Carry out normal attack if no spells were cast */
    return 0;
}
 
/* 
 * Function name: do_heal_me_spell
 * Description:   Healing spell for when we have taken lots of damage.
 * Arguments:     me: The spellcaster.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
do_heal_me_spell(object me)
{
    if (me->query_mana() <= 150)
        return 0;
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    me->heal_hp(3000);
    me->add_mana(-100);
    return 1;
}

/* 
 * Function name: fireball_spell
 * Description:   Fireballs - *yawn*. No marks for originality here.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
fireball_spell(object me, object enemy)
{
    if (me->query_mana() <= 230)
        return 0;
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    enemy->catch_msg("You are hit by a fireball!\n");
    tell_room(environment(me), QCTNAME(enemy) +
        " is burned by a fireball.\n", enemy);
    me->add_mana(-30);
    enemy->heal_hp(-300);
    if (!enemy->query_hp())
        enemy->do_die(me);
    check_wimp(enemy);
    
    return 1;
}
 
/* 
 * Function name: lighting_spell
 * Description:   No marks for originality here, either.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
lighting_spell(object me, object enemy)
{
    if (me->query_mana() <= 240)
        return 0;
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    enemy->catch_msg("You are stuck by a bolt of lightning!\n");
    tell_room(environment(me), QCTNAME(enemy) +
        " is struck by a bolt of lightning.\n", enemy);
    me->add_mana(-40);
    enemy->heal_hp(-400);
    if (!enemy->query_hp())
        enemy->do_die(me);
    check_wimp(enemy);
    
    return 1;
}
 
/* 
 * Function name: shield_spell
 * Description:   Conjour a magic shield for protection.
 * Arguments:     me: The spellcaster.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
shield_spell(object me)
{
    object sh;
    
    if (me->query_mana() <= 160)
        return 0;
    
    me->add_armour(CAVE_DIR + "arm/magic_shield");
    me->add_mana(-60);
    return 1;
}
 
/* 
 * Function name: dim_door_spell
 * Description:   Teleport to a safe place if things look bad.
 * Arguments:     me: The spellcaster.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
dim_door_spell(object me)
{
    if (me->query_mana() <= 10)
        return 0;
    
    me->command("say Sorry to ruin the party, but I dislike dying....");
    me->command("finger all");
    tell_room(environment(me), QCTNAME(me) + " disappears in a " +
        "blinding flash of light!\n", me);
    me->move("/d/Emerald/cave/levelc/cave28c");
    me->add_mana(-10);
    return 1;
}
 
/* 
 * Function name: haste_spell
 * Description:   Boost our speed in combat.
 * Arguments:     me: The spellcaster.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
haste_spell(object me)
{
    if (me->query_mana() <= 150)
        return 0;
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell, " +
        "and seems to have speeded up somewhat!\n", me);
    me->add_prop(LIVE_I_QUICKNESS, 250);
    me->add_mana(-50);
    return 1;
}
 
/* 
 * Function name: intox_spell
 * Description:   Boost our healing rate up to maximum.
 * Arguments:     me: The spellcaster.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
intox_spell(object me)
{
    int max;
    
    if (me->query_mana() <= 160)
        return 0;
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell, " +
        "and grins drunkenly.\n", me);
    
    max = me->intoxicated_max();

    me->set_intoxicated(max-1);
    me->add_mana(-60);
    return 1;
}

/* 
 * Function name: steal_mana_spell
 * Description:   Steal half of the remaining mana our enemy has.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
steal_mana_spell(object me, object enemy)
{
    int mana;
    
    if (me->query_mana() <= 10)
        return 0;
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    me->add_mana(-10);
    
    mana = enemy->query_mana()/2;
    me->add_mana(mana);
    enemy->add_mana(-mana);

    enemy->catch_msg("You feel mentally drained.\n");
    tell_room(environment(me), QCTNAME(enemy) +
        " looks mentally drained.\n", enemy);
    return 1;
}

/* 
 * Function name: stun_spell
 * Description:   Stun our enemy for a short while.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
stun_spell(object me, object enemy)
{
    int random_delay;
    object stun_object;
    
    if (me->query_mana() <= 240)
        return 0;
    
    random_delay = random(20);

    stun_object = present("enz_stun_object", enemy);
    if (stun_object)
        stun_object->replace_stun();
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    me -> add_mana(-40);

    stun_object = clone_object(CAVE_DIR + "obj/stun_obj");
    stun_object -> set_unstun_delay(10 + random_delay);
    stun_object -> move(enemy);

    return 1;
}

/* 
 * Function name: slow_spell
 * Description:   Slow our enemy down a bit.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
slow_spell(object me, object enemy)
{    
    object slow_object;

    if (me->query_mana() <= 240)
        return 0;
    
    slow_object = present("enz_slow_object", enemy);
    if (slow_object)
        slow_object->replace_slow();
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    me -> add_mana(-40);

    slow_object = clone_object(CAVE_DIR + "obj/slow_obj");
    slow_object -> move(enemy);

    return 1;
}

/* 
 * Function name: gas_spell
 * Description:   Poison our enemy with a bit of gas.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
gas_spell(object me, object enemy)
{
    object gas_obj;
    
    if (me->query_mana() <= 230)
        return 0;
    
    gas_obj = clone_object(CAVE_DIR + "obj/gas_obj");
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    me->add_mana(-30);
    tell_room(environment(enemy), QCTNAME(enemy) + " is suddenly " +
        "engulfed in a cloud of poisonous gas.\n", enemy);
    enemy->catch_msg("You are suddenly engulfed in a cloud of " +
        "poisonous gas!\nIt starts to burn your lungs as you " +
        "breathe it in, reluctantly....\n");
    
    gas_obj->move(enemy);
    gas_obj->start_poison();
    
    return 1;
}

/* 
 * Function name: blast_spell
 * Description:   Blast our enemy with a some magic.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
blast_spell(object me, object enemy)
{
    if (me->query_mana() <= 270)
        return 0;
    
    tell_room(environment(me), QCTNAME(me) + " casts a spell.\n", me);
    enemy->catch_msg("You are blasted in an inferno of magical power!\n");
    tell_room(environment(me), QCTNAME(enemy) +
        " is blasted in an inferno of magical power.\n", enemy);
    me->add_mana(-70);
    enemy->heal_hp(-600);
    if (!enemy->query_hp())
        enemy->do_die(me);
    check_wimp(enemy);
    
    return 1;
}

/* 
 * Function name: teleport_spell
 * Description:   This spell teleports our enemy down into the well in Terel.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
teleport_spell(object me, object enemy)
{
    if (me->query_mana() <= 250)
        return 0;
    
    me->add_mana(-50);
    me->command("say Bye, bye, dimwit!");
    me->command("cackle");
    tell_room(environment(me), QCTNAME(me) + " points a finger at " +
        QTNAME(enemy) + ".....\n", enemy);
    enemy->move_living("with a loud BANG!",
        "/d/Terel/common/town/mansion/crt/level4", 1, 0);
    
    return 1;
}

/* 
 * Function name: brain_damage_spell
 * Description:   This spell is dedicated to Pink Floyd, my favourite band.
 * Arguments:     me: The spellcaster,   enemy: The target of the spell.
 * Returns:       0 = spell is not cast, 1 = spell is cast.
 */
public int
brain_damage_spell(object me, object enemy)
{
    /* Takes a lot of mana, but does _lots_ of damage. */
    if (me->query_mana() <= 500)
        return 0;
    
    me->add_mana(-300);
    me->command("shout That does it! No more mister nice-guy!!");
    me->command("scream");

    /* This spell deserves a little more description than most. */
    tell_room(environment(me), "The whole room suddenly starts to shake!\n" +
        "With dark forbodings, too.....\n\n", me);
    
    /* Heh, can you spot the subtle Pink Floyd influences? */
    tell_room(environment(me), QCTNAME(enemy) + "'s head explodes. Bits " +
        "of brain are strewn all around.\n", enemy);
    
    enemy->catch_msg("Your head explodes, spreading what little brains " +
        "you have all around.\nDark forbodings, indeed.....\n");

    enemy->heal_hp(-2000); /* I'll see you on the dark side of the moon! */
                           /* Even Bebop would feel a hit like that..... */
    if (!enemy->query_hp())
        enemy->do_die(me);
    
    return 1;
}

/* 
 * Function name: check_wimp
 * Description:   Check if players hitpoints are less than their wimpy level.
 * Arguments:     enemy: The player who is our current enemy.
 */
public void
check_wimp(object enemy)
{    
    int wimpy_level;
    
    if (!(wimpy_level = enemy->query_whimpy()))
        return;

    if (((100 * enemy->query_hp()) / enemy->query_max_hp()) < wimpy_level)
    {
        /* Make player run away after this combat round. */
        set_alarm( 1.0, 0.0, &enemy_flee(enemy));
        command("say Hmmmm. Isn't it time to leave...?");
    }
}

/* 
 * Function name: enemy_flee
 * Description:   Cause player to run away.
 * Arguments:     enemy: The player who is running away.
 */
public void
enemy_flee(object enemy)
{
    enemy->run_away();

    if (random(2))
        command("say Now, lets see who is next.");
    else
        command("say Yes, go on, run back to your mother...");
    command("grin");
}

/* 
 * Function name: plexus_block
 * Description:   Prevent monks using the 'plexus' special attack.
 * Arguments:     from: The player who gave us the correct objects.
 * Returns:       0 = attack is allowed, 1 = attack is blocked.
 */
public int
plexus_block(string str)
{
    object target;
    mixed target_arr;

    /* Is the player fighting this npc? */
    if (TP->query_attack() == TO)
    {
        write("Alas, your enemy steps back to avoid the attack.\n");
        tell_room(ENV(TO), QCTNAME(TO) + " steps back to avoid " + 
            QTNAME(TP) + ".\n", TP);
        return 1;
    }

    if (!strlen(str))
        return 0;
    
    /*  use parse_command to check who we want to plexus. */
    parse_command(str, ENV(TP), "[the] %l", target_arr);
    
    if (sizeof(target_arr) < 2)
    {
        write("Plexus whom?\n");
        return 1;
    }
    
    if (!living(target_arr[1]))
    {
        write("Plexus whom?\n");
        return 1;
    }
    
    if (sizeof(target_arr) != 2)
    {
        write("You can only plexus one target at a time.\n");
        return 1;
    }
    
    target = target_arr[1];

    if (target == TO)
    {
        write("Alas, your enemy steps back to avoid the attack.\n");
        tell_room(ENV(TO), QCTNAME(TO) + " steps back to avoid " + 
            QTNAME(TP) + ".\n", TP);
        return 1;
    }

    return 0;
}

/* 
 * Function name: arm_me
 * Description:   Not used currently, but still called by cloning room.
 */
public void
arm_me()
{
    /* Who needs weapons when you have magic like this?? */
}


/*
 * Non-combat related functions
 */

/* 
 * Function name: quest_list
 * Description:   Give a list of quests that players can attempt.
 * Returns:       An empty string.
 */
public string
quest_list()
{
    command("smile");
    command("say So you want a quest, eh? Well there are a couple of " +
        "things I need help with. You can ask me about either Artolmeus, " +
        "or the Nemesis sword."); 

    return "";
}

/* 
 * Function name: knight_quest_info
 * Description:   Give player information needed to free the octopus.
 * Returns:       An empty string.
 */
public string
knight_quest_info()
{
    command("ponder");
    command("say Well listen up, my little friend.....");
    
    command("say Some time ago, a young Knight named Artolmeus attacked a " +
        "good friend of mine, as he wrongly assumed all goblins were evil. " +
        "To teach him a lesson, I turned him into an octopus, thus " +
        "imprisoning him here in the well."); 
    
    command("say As I think he has now had long enough to reflect on what " +
        "he did, perhaps it is time to release him. You know, I think " +
        "it's possible that you could help me - to make the ointment " +
        "required to release him, I need some crushed emerald powder. " +
        "I had some in convenient sachets, but they were all stolen " +
        "while I was off killing dragons.\n");
    
    command("say Bring me some crushed emerald powder, and perhaps we " +
        "can free Artolmeus again. Oh yes, I'll need a platinum coin, too." +
        "\nYou will be rewarded....");
    
    command("wink all");

    return "";
}

/* 
 * Function name: sword_quest_info
 * Description:   Tell player what is needed for the Nemesis sword quest.
 * Returns:       An empty string.
 */
public string
sword_quest_info()
{
    command("say A few hundered years ago, I made a sword. I enchanted " +
        "it, and it turned out to be quite a weapon. I gave it to a " +
        "Ranger who I frequently used to team with to kill dragons."); 
    
    command("say Alas, the Ranger was killed by unknown assailants, " +
        "and as for the sword, I know not what happened to it. As it is " +
        "such a powerful sword, I don't want it to be in the wrong hands."); 
    
    command("sigh");
    
    command("say If you could bring me the sword, I would be safe " +
        "in the knowledge that does not serve the forces of darkness."); 
    
    command("say Finally, the name of the sword: I called it the Nemesis " +
        "sword."); 
    
    command("say Best of luck..."); 
    command("smile hopefully");

    return "";
}

/*
 * Function name: add_introduced
 * Description  : Called when a player is introduced
 * Arguments    : string name - the introduced persons [lower case] name
 */
public void
add_introduced(string name)
{
    set_alarm( 2.0, 0.0, &introduce_npc(name) );
}

/*
 * Function name: introduce_npc
 * Description  : Introduce this npc, to be polite
 * Arguments    : string name - the person we want to be introduced to 
 */
public void
introduce_npc(string name)
{
    command("introduce me");
    command("nod " + lower_case(name));
}

/* 
 * Function name: enter_inv
 * Description:   Called when an object is given to this npc
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{    
    string name;
    int wanted;

    ::enter_inv(ob, from);
    
    /* Objects are not wanted by default. */
    wanted = 0;

    /* Only bother checking things that we are given by mortals. */
    if (living(from))
    {
        name = lower_case(from->query_real_name());

        /* Make sure we remember who gives us platinum coins & powder. */
        if (ob->query_coin_type() == "platinum")
        {
            /* Add player to list of those who have given a platinum coin. */
            if (sizeof(players_given_me_coin))
                players_given_me_coin += ({ name });
            else
                players_given_me_coin = ({ name });
            
            if (member_array(name, players_given_me_powder) != -1)
            {
                command("say Ah, you have given me all I need...");
                set_alarm( 2.0, 0.0, &make_ointment(from) );    
            }
            else
                command("say Great! Now I only need the emerald powder.");
            wanted = 1;
        }
        
        if (ob->query_short() == "sachet of emerald powder")
        {
            /* Add player to list of those who have given a sachet. */
            if (sizeof(players_given_me_powder))
                players_given_me_powder += ({ name });
            else
                players_given_me_powder = ({ name });
            
            if (member_array(name, players_given_me_coin) != -1)
            {
                command("say Ah, you have given me all I need...");
                set_alarm( 4.0, 0.0, &make_ointment(from) );    
            }
            else
                command("say Great! Now I only need a platinum coin.");
            wanted = 1;
        }
        
        /* Give quest xp for returning the sword. */
        if (ob->query_short() == "nemesis sword")
        {
            /* The Nemesis sword was made by Enzalcaspin. */
            command("gasp");
            command("Surely it cannot be...!");
            set_alarm( 4.0, 0.0, &receive_nemesis_sword(ob, from) );

            wanted = 1;
        }

        if (!wanted)
        {
            command("say Well now, do I need this?");
            command("ponder");
            set_alarm( 4.0, 0.0, &return_item(ob, from) );
        }
    }
}

/* 
 * Function name: make_ointment
 * Description:   Create the magic ointment for the questing player.
 * Arguments:     from: The player who gave us the correct objects.
 */
public void
make_ointment(object from)
{
    object ointment;
    string name;

    name = lower_case(from->query_real_name());
    
    tell_room(ENV(TO), QCTNAME(TO) + " places a platinum coin in one " +
        "hand, and places a sachet of emerald powder in the other.\n");
    tell_room(ENV(TO), QCTNAME(TO) + " suddenly claps his hands together, " +
        "producing a loud bang, and a small puff of smoke.\n");
    
    ointment = clone_object(EMERALD_OINTMENT);
    ointment->move(TO);

    if (objectp(ointment))
    {
        command("say Well, so far so good.");
    
        players_given_me_coin -= ({ name });
        players_given_me_powder -= ({ name });
    }

    if (present(from, ENV(TO)))
    {
        command("say All you have left to do is rub this ointment over " +
            "the octopus. You'll find him down in the water somewhere. " +
            "Best of luck!");
        command("give ointment to " + name );
    }
    else
    {
        command("shrug");
        command("drop ointment");
    }
}

/* 
 * Function name: return_item
 * Description:   Either give back an item given to him, or drop it.
 * Arguments:     ob:   The item he has been given.
 *                from: The player who gave him the item.
 */
public void
return_item(object ob, object from)
{
    string ob_name, player_name;

    ob_name = ob->query_name();
    player_name = lower_case(from->query_real_name());
    
    if (present(from, ENV(TO)))
        command("give " + ob_name + " to " + player_name );
    else
    {
        command("shrug");
        command("drop " + ob_name);
    }
}

/* 
 * Function name: receive_nemesis_sword
 * Description:   Show everyone how pleased he is to see his sword again.
 * Arguments:     ob:   The Nemesis sword.
 *                from: The player who gave us the Nemesis sword.
 */
public void
receive_nemesis_sword(object ob, object from)
{
    command("emote holds the Nemesis sword up to the light.");
    command("My old sword! Ah, this brings back some memories.");
    command("wield nemesis sword");
    if(!ob->query_prop(NEMESIS_QUEST_DONE)) ob->add_prop(NEMESIS_QUEST_DONE,
	 from->query_real_name());
    set_alarm( 8.0, 0.0, &swing_nemesis_sword(ob, from) );
}

/* 
 * Function name: swing_nemesis_sword
 * Description:   Give everyone a sword-play demonstration.
 * Arguments:     ob:   The Nemesis sword.
 *                from: The player who gave us the Nemesis sword.
 */
public void
swing_nemesis_sword(object ob, object from)
{
    command("say Oh, it has been such a long, long time...");
    command("say ...so lets have some fun!");
    command("emote spins around fast, swinging the Nemesis sword " +
        "around him.");
    set_alarm( 8.0, 0.0, &slash_nemesis_sword(ob, from) );
}

/* 
 * Function name: slash_nemesis_sword
 * Description:   Give everyone a sword-play demonstration.
 * Arguments:     ob:   The Nemesis sword.
 *                from: The player who gave us the Nemesis sword.
 */
public void
slash_nemesis_sword(object ob, object from)
{
    command("emote brilliantly demonstrates a complex sequence of " +
        "slashing, thrusting and parrying maneuvers.");
    set_alarm( 8.0, 0.0, &flip_nemesis_sword(ob, from) );
}

/* 
 * Function name: flip_nemesis_sword
 * Description:   Give everyone a sword-play demonstration.
 * Arguments:     ob:   The Nemesis sword.
 *                from: The player who gave us the Nemesis sword.
 */
public void
flip_nemesis_sword(object ob, object from)
{
    command("emote flips head over heels, landing on both feet while " +
        "pulling the Nemesis sword over his head, executing a gigantic " +
        "overhead smash.");
    set_alarm( 8.0, 0.0, &thrust_nemesis_sword(ob, from) );
}

/* 
 * Function name: thrust_nemesis_sword
 * Description:   Give everyone a sword-play demonstration.
 * Arguments:     ob:   The Nemesis sword.
 *                from: The player who gave us the Nemesis sword.
 */
public void
thrust_nemesis_sword(object ob, object from)
{
    command("say And now for the coup de grace...");
    command("emote leaps in the air, and thrusts the Nemesis sword " +
        "deep into the heart of an imaginary foe (probably a dragon).");
    set_alarm( 8.0, 0.0, &finish_with_nemesis_sword(ob, from) );
}

/* 
 * Function name: finish_with_nemesis_sword
 * Description:   End the sword-play demonstration.
 * Arguments:     ob:   The Nemesis sword.
 *                from: The player who gave us the Nemesis sword.
 */
public void
finish_with_nemesis_sword(object ob, object from)
{
    command("unwield all");
    command("emote throws the Nemesis sword up over his head, it spins " +
        "once, then he catches the sword in both hands.");
    set_alarm( 8.0, 0.0, &reward_player_for_sword(ob, from) );
}

/* 
 * Function name: reward_player_for_sword
 * Description:   Give the player some xp for returning the sword.
 * Arguments:     ob:   The Nemesis sword.
 *                from: The player who gave us the Nemesis sword.
 */
public void
reward_player_for_sword(object ob, object from)
{
    setuid();
    seteuid(getuid(TO));
    
    command("say That's the most fun I've had in ages!");
    command("unwield nemesis sword");

    /* Has the player completing the quest foolishly left the room? */
    if (member_array( from, all_inventory( ENV(TO) ) ) == -1)
    {
        command("say Hey! Where did that " + from->query_race() + " go?");        
        set_alarm( 2.0, 0.0, &return_item(ob, from) );
        return;
    }
    
    if (from->test_bit( "emerald", NEMESIS_BIT[0], NEMESIS_BIT[1] ) ||
	ob->query_prop(NEMESIS_QUEST_DONE) != from->query_real_name())
    {
        command("say It's nice to know the sword is still in safe hands.");
        set_alarm( 2.0, 0.0, &return_item(ob, from) );
        return;
    }
    else
    {
        command("say At last I know the sword is in safe hands!");
        
        if (!NEMESIS_QUEST_OPEN)
        {
            command("say Alas, I am currently unable to give a reward.");
            set_alarm( 2.0, 0.0, &return_item(ob, from) );
            return;
        }

        if (from->query_exp() > NEMESIS_QUEST_XP )
        {
            from->set_bit(NEMESIS_BIT[0], NEMESIS_BIT[1]);
            from->add_exp(NEMESIS_QUEST_XP);
    
            from->catch_msg("You get the pleasant feeling of being " + 
                "more experienced.\n");
	    log_file("quests/nemesis_sword",
		capitalize(from->query_real_name()) + " returned the "+
		  "Nemesis sword for " + NEMESIS_QUEST_XP + " xp.\t"+
		  ctime(time())+"\n");
        }
        else
        {
            from->catch_msg("If you were bigger, you would have felt " + 
                "a bit more experienced.\n");
        }
    }

    set_alarm( 2.0, 0.0, &return_item(ob, from) );
}

/*
 * Function name:   init_living
 * Description:     called when a player enters our environment
 */
public void
init_living()
{
    ::init_living();
    
    /* Plexus is probably the biggest threat to this npcs survival. */
    add_action(plexus_block, "plexus");

    /* Greet players, if we are not too busy fighting. */
    if (!TO->query_attack())
        set_alarm( 4.00, 0.0, &greet_player(TP) );
}
    
/*
 * Function name:   greet_player
 * Description:     Greet players as they enter the room.
 * Arguments:       player: the player we wish to greet
 */
public void
greet_player(object player)
{
    int num;
    string *action;

    action = ({ "greet", "smile", "shake", "nod" });

    num = random(sizeof(action));

    command(action[num] + " " + lower_case(player->query_real_name()));
}

/*
 * Let's give the npc a few nice emote hooks, for realism.
 * (Not too many though, we're getting near the 50K gamedriver limit!)
 */
public void
chuckle(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("say You can chuckle all you like, " + 
            actor->query_race() + ".");
        return;

    case 1:
        command("say A chuckling " + actor->query_race() + "? " +
            "Fancy that!");
        return;

    default:
        command("chortle");
    }
}

public void
cry(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("say Aw, don't cry now, " + actor->query_race() + "."); 
        command("comfort " + actor->query_real_name());
        return;

    case 1:
        command("say What's the matter, my little friend?"); 
        return;

    default:
        command("say Cheer up, it will all look better tomorrow!");
    }
}

public void
flip(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("say Anything you can do..."); 
        command("emote flips head over heels, backwards.");
        return;

    case 1:
        command("say " + capitalize(LANG_PWORD(actor->query_race())) + 
            " get so excited, don't they...");
        return;

    default:
        command("say Heh, you'll get dizzy if you do that.");
    }
}

public void
hug(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("say Why thank you, " + actor->query_race() + "."); 
        return;

    case 1:
        command("say It's so nice to see a friendly " +
            actor->query_race() + "."); 
        return;

    default:
        command("smile at " + actor->query_real_name());
    }
}

public void
kick(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("say ...and you can cut that out, too!"); 
        return;

    case 1:
        command("say Is a kick all the thanks I get, " +
            actor->query_race() + "?");
        command("sulk"); 
        return;

    default:
        command("poke " + actor->query_real_name() + " eye");
    }
}

public void
kiss(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("blush"); 
        return;

    case 1:
        command("say So what would you do for a few platinum coins...?");
        command("wink " + actor->query_real_name()); 
        return;

    default:
        command("hug " + actor->query_real_name());
    }
}

public void
poke(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(4))
    {
    case 0:
        command("say Hey, who do you think you're poking, " +
            actor->query_race() + "?");
        return;

    case 1:
        command("say Why must " + LANG_PWORD(actor->query_race()) + 
            " always have to poke people?");
        return;
    
    case 2:
        command("say Two can play at that game!");
        command("poke " + actor->query_real_name());
        return;

    default:
        command("say You don't know Tricky by any chance, do you??");
    }
}

public void
slap(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("say Well! That's a charming way to act."); 
        return;

    case 1:
        command("say Aw, did I upset you, " + actor->query_race() + "?");
        return;

    default:
        command("say " + capitalize(LANG_PWORD(actor->query_race())) +
            " really don't have a sense of humour...");
    }
}

public void
smile(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(3))
    {
    case 0:
        command("say Smile, and the world smiles with you.");
        command("smile");
        return;

    case 1:
        command("say I love to see " + LANG_ADDART(actor->query_race()) + 
            " smile.");
        return;

    default:
        command("smile");
    }
}

public void
spit(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(4))
    {
    case 0:
        command("say Really, that is quite unnecessary, " + 
            actor->query_race() + "!");
        return;

    case 1:
        command("say Why, oh why, do I let " + 
            LANG_PWORD(actor->query_race()) + " in here?");
        return;

    case 2:
        command("say Must you really spit in here, " +
            actor->query_race() + "?");
        return;

    default:
        command("say Don't spit near my carpet, you young ruffian!");
    }
}

public void
swear(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(4))
    {
    case 0:
        command("say That is rather impolite, " + 
            actor->query_race() + "!");
        return;

    case 1:
        command("say Oh dear me, why do " + 
            LANG_PWORD(actor->query_race()) + " behave this way?");
        return;

    case 2:
        command("cringe");
        return;

    default:
        command("emote winces at the profanity.");
    }
}

public void
yawn(object actor, string adverb)
{
    CHECK_ACTOR;

    switch(random(5))
    {
    case 0:
        command("say Well, I do hope I'm not boring you, " + 
            actor->query_race() + "!");
        return;

    case 1:
        command("say I suppose " + 
            LANG_PWORD(actor->query_race()) + " must get tired too easily.");
        return;

    case 2:
        command("say Past your bed-time, is it?");
        command("pat " + actor->query_real_name());
        return;
    
    case 3:
        command("yawn");
        command("say Yawning is contagious, you know...");
        return;

    default:
        command("poke " + actor->query_real_name());
        command("say Don't you go falling asleep now, " +
            actor->query_race() + ".");
    }
}

/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 */
public void
emote_hook(string emote, object actor, string adverb)
{
    /* Several emote hooks, so use the code from the example. */
    if (member_array(emote, HOOKED_EMOTIONS) == -1)
        return;
    
    set_alarmv(3.0, 0.0, emote, ({ actor, adverb }) );
}
