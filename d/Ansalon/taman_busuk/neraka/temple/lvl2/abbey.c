/* Navarre July 3rd 2006, Fixed typo, infront to in front. */



/* A door should lead off to the east out of the abbey.
 * This abbey only serves as a quiet room for meditation and contemplation.
 * Therefore it should be possible to use the meditate command here.
 */

#pragma strict_types

#include "/d/Ansalon/taman_busuk/neraka/temple/defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
// #include GUILDDIR + "admin/admin.h"
#include <macros.h>

inherit TEMPLE + "std_temple.c";
inherit "/lib/guild_support";
inherit GUILDDIR + "lib/join";
inherit GUILDDIR + "lib/train_mind";
inherit GUILDDIR + "lib/rank";

#define TMP_POT_LAST_TIME_PRAYED    "_tmp_pot_last_time_prayed"
#define OLD_CMDSOUL                 "/d/Ansalon/guild/pot/soul/cmdsoul"
#define OLD_SHADOW                  "/d/Ansalon/guild/pot/shadow/occ_shadow"

object gPriest;

void
reset_temple_room()
{
    setuid();
    seteuid(getuid());

    if (!gPriest)
    {
        gPriest = clone_object(GUILDNPC + "terwed");
        gPriest->arm_me();
        if (gPriest->move(TO))
            gPriest->move(TO, 1);

        set_trainer(gPriest);
        set_master(gPriest);
    }
}

void
create_temple_room()
{
    object door;
    
    ::create_temple_room();

     set_short("dimly lit room");
    set_long("This room is fairly small and dimly lit. Evenly spaced " +
        "between the torches on the walls hang dark tapestries. " +
        "In the centre of the room stands a low altar. Forming a circle " +
        "around it are several low benches especially designed for " +
        "prayer and meditation.\n");

    add_item(({"low benches", "benches"}), "Low wooden benches barely " +
        "extending from the floor have been placed in a circle around " +
        "the altar, which would suggest they have been made for " +
        "kneeling in front of the altar in prayer and allow for " +
        "meditation.\n");
    add_cmd_parse("[before] [on] [the] [low] 'benches'", "kneel",
        "You kneel before the benches, facing the altar.\n");
    add_cmd_parse("[the] [queen] [of] [darkness] 'queen' / 'takhisis'",
        "worship", "You fall to your knees, your head nearly " +
        "touching the ground in reverence to the Dark Queen.\n");
    add_item(({"tapestries", "dark tapestries"}), "Dark tapestries " +
        "span all of the walls depicting dragons in all their might. " +
        "The images are very much alive, their eyes almost appearing " +
        "to be following your every movement.\n");
    add_item(({"altar", "low altar"}), "The altar is made of a slab " +
        "of stone upon metal stands, upon which carved out of the " +
        "otherwise smooth slab sits a five-headed dragon, its heads " +
        "overlooking the entire abbey.\n");
    add_item(({"dragon", "five-headed dragon"}), "Carved out of the " +
        "slab of stone making up the altar, sits a five-headed dragon " +
        "in its very middle overlooking the entire abbey.\n");
    add_item(({"slab", "slab of stone"}), "The slab of stone makes " +
        "up the altar upon which sits a five-headed dragon carved " +
        "out of the very same slab, overlooking the entire abbey.\n");
    add_item("dragons", "Chromatic dragons are depicted upon " +
        "dark tapestries spanning the entire walls whose eyes " +
        "seemingly follows your every movement.\n");

#ifdef 0
    door = clone_object( DOOR + "abbey2.c" );
    door->move(this_object());
#endif

    create_skill_raise();
    set_up_skills();

    add_exit( LVLTWO + "corr3", "east");

    reset_temple_room();
}

int
upgrade_priest(object who)
{
    object *emblem, guild, mana;
    int     g_error, m_error, s_soul, g_soul;

    setuid();
    seteuid(getuid());
   
    if (who->has_mana_shadow())
        return 0;
    
    emblem = filter(all_inventory(who), &operator(>)(,-1) @
                &member_array("takhisis_medallion", ) @ &->query_names());
    
    if (sizeof(emblem))
    {
        foreach(object item: emblem)
        {
            item->remove_object();
        }
    }
    
    OLD_CMDSOUL->remove_spells(who);
    who->remove_cmdsoul(OLD_CMDSOUL);
    who->update_hooks();
//    who->remove_autoshadow(OLD_SHADOW);
    who->remove_guild_occ();
    
    guild   = clone_object(POTSHADOW);
    mana    = clone_object(MANA_SHADOW);
    
    if ((g_error = guild->shadow_me(who, "occupational", GUILD_STYLE,
        GUILD_NAME)) > 0 && (m_error = mana->shadow_me(who)) > 0 &&
        (g_soul = who->add_cmdsoul(GUILD_CMDSOUL)) &&
        (s_soul = who->add_cmdsoul(SPELL_MANAGER_SOUL)))
    {
        who->update_hooks();
        write_file(GUILDDIR + "priest_transfer", ctime(time()) + " " +
        who->query_real_name() + " has successfully transferred to the new " +
        "guild.\n");
        
        return 1;
    }
    else
    {
        write_file(GUILDDIR + "priest_transfer", ctime(time()) + " " +
        who->query_real_name() + " has failed to transfer, guild shadow " +
        "returned: " + g_error + " and mana shadow returned: " + m_error +
        " guild soul returned: " + g_soul + " and spell manager soul " +
        "returned: " + s_soul + "\n");
        who->catch_msg("Something went wrong, contact " +
        implode(GUILDMASTERS, ", ") + " to report the issue.\n");
    }
    
    return -1;
}

int
do_pray(string arg)
{
    int spell_set, gs, alpha, beta, gamma, eta, phi, new_gs = -1, promo, new;
    object scroll;
    
    if (stringp(arg) && arg != "")
    {
        notify_fail("Pray what?\n");
        return 0;
    }
    
    write("You kneel in front of the altar and pray to the Queen of " +
        "Darkness.\n");
    say(QCTNAME(TP) + " kneels in front of the altar in a short " +
        "prayer.\n");
    
    if (TP->query_guild_name_occ() != GUILD_NAME)
    {
        write("You rise again, feeling mentally refreshed.\n");
        return 1;
    }
    
    if ((new = upgrade_priest(this_player())) != 0)
    {
        if (new < 0)
            return 1;
        
        write("As you pray to Takhisis you feel her presence more strongly " +
              "than before... as if she was closer to entering the material " +
              "plane.\nYou feel your granted prayers have changed and been " +
              "renewed! You feel the need to refamiliarise yourself with " +
              "your abilities through 'phelp' or 'help priest'.\n");
        return 1;
    }
    
    spell_set = SPELLS->set_spells(TP);

    if (spell_set & SPELLS_REVOKED)
    {
        if (TP->query_skill(PS_SPELLS))
            write("You feel a stabbing in your heart as Takhisis " +
                "grants you no spells.\n");
        TP->set_skill(PS_SPELLS, 0);
        P(MEDALLION_ID, TP)->update_spells();
    }

    if (spell_set & NEW_SPELLS)
    {
        write("In a holy vision you realise that you have been granted " +
            "new spells!\n");
    }
    
    if (spell_set & GOT_SPELL)
    {
        write("In reward for your excellent performance, the Queen " +
            "grants you a new spell; " +
            TP->query_prop(POT_GOT_NEW_SPELL)[0] + "!\n");
        TP->remove_prop(POT_GOT_NEW_SPELL);
    }

    do_rank(TP);
    
    if ((TP->query_prop(TMP_POT_LAST_TIME_PRAYED) + 3000 + random(500)) <
        time())
        TP->adjust_standing(RND_RANGE(90, 10));
    else
        TP->adjust_standing(RND_RANGE(-30, 20));
    
    TP->add_prop(TMP_POT_LAST_TIME_PRAYED, time());
#ifdef 0
    alpha = TP->query_stat(SS_OCCUP) - 15;
    beta = TP->query_stat(SS_WIS) - 45;
    gamma = TP->query_skill(PS_SKILL_POINTS);
    eta = TP->query_skill(SS_SPELLCRAFT);
    phi = TP->query_skill(SS_ELEMENT_LIFE);
        
    gs = (2 * alpha + 3 * beta) / 5 + (eta + phi) / 8 +
        ftoi(sqrt(itof(gamma)) / 5.0) - 5;
        
    if (gs < TP->query_skill(PS_GUILD_LEVEL))
        gs = TP->query_skill(PS_GUILD_LEVEL);

    switch (TP->query_skill(PS_GUILD_LEVEL))
    {
        case 0..9:
            if (gs > 9)
                gs = 9;
            break;
        case 10..19:
            if (gs > 19)
                gs = 19;
            break;
        case 20..29:
            if (gs > 29)
                gs = 29;
            break;
        case 30..39:
            if (gs > 39)
                gs = 39;
            break;
        case 40..49:
            if (gs > 49)
                gs = 49;
            break;
        case 50..99:
            if (gs > 99)
                gs = 99;
            break;
/*
        case 100..139:
            if (gs > 139)
                gs = 139;
            break;
*/
    }
  
    /* Before one can gain certain ranks, a promotion is required
     */
    switch (gs)
    {
        case 140..149:
            /* About to be leader, only one can have the highest title */
            if (GUILD_ADMIN->query_leader() &&
                GUILD_ADMIN->query_leader() != TP->query_real_name())
                gs = 139;
            break;
        case 100..139:
            /* About to be highpriest */
            if (TP->query_skill(PS_GUILD_LEVEL) < 100)
                gs = 99;
            break;
        case 50..99:
            /* About to be priest */
            if (TP->query_skill(PS_GUILD_LEVEL) < 50)
                gs = 49;
            break;
        case 40..49:
            /* About to be cleric lev 5 */
            if (TP->query_skill(PS_GUILD_LEVEL) < 40)
                gs = 39;
            break;
        case 30..39:
            /* About to be cleric lev 4 */
            if (TP->query_skill(PS_GUILD_LEVEL) < 30)
                gs = 29;
            break;
        case 20..29:
            /* About to be cleric lev 3 */
            if (TP->query_skill(PS_GUILD_LEVEL) < 20)
                gs = 19;
            break;
        case 10..19:
            /* About to be cleric lev 2 */
            if (TP->query_skill(PS_GUILD_LEVEL) < 10)
                gs = 9;
            break;
    }

    new_gs = GUILD_ADMIN->query_promoted(TP->query_real_name());
    if (new_gs > 0)
    {
        if (new_gs < TP->query_skill(PS_GUILD_LEVEL))
        {
            write("\nYou feel a stabbing at your heart as the " +
                "Queen of Darkness revokes your standing within " +
                "the guild.\n");
            TP->adjust_standing(RND_RANGE(-(TP->query_skill(PS_GUILD_LEVEL) +
                TP->query_skill(PS_GUILD_LEVEL) / 10), 5));
            TP->set_skill(PS_GUILD_LEVEL, new_gs);
            GUILD_ADMIN->clear_promotions(TP->query_real_name());
        }
        else if (new_gs > TP->query_skill(PS_GUILD_LEVEL))
        {
            if (TP->query_priest_level() < TP->query_priest_level(new_gs))
            {
                promo = TP->query_priest_level(new_gs);
                /* Clears the promotion from the admin when the
                 * quest is completed. This will create the 'feature'
                 * that the player will always feel this sensation
                 * when praying for as long as he has not completed it
                 */
                write("\nYou realise you are ready to become a " +
                    (promo == GUILD_LEVEL_PRIEST ? "Priest" : "High Priest") +
                    ".\n");
            }
            else
            {
                /* Cleric Promotion */
                TP->set_skill(PS_GUILD_LEVEL, new_gs);
                GUILD_ADMIN->clear_promotions(TP->query_real_name());

                write("\nYou feel an inner warmth as the Queen of " +
                    "Darkness recognises your exploits and grants you a " +
                    "higher standing within the guild.\n");

                TP->adjust_standing(RND_RANGE(TP->query_skill(PS_GUILD_LEVEL),
                    20));
            }
        }
    }
    else if (TP->query_priest_sublevel() != TP->query_priest_sublevel(gs))
    {
        if (gs >= 140 && GUILD_ADMIN->query_leader() != TP->query_real_name())
        {
            GUILD_ADMIN->set_leader(TP->query_real_name());
            write("\nA soothing voice in your mind speaks 'You my child " +
                "shall be known as the leader of my priesthood'\n");
        }

        TP->set_skill(PS_GUILD_LEVEL, gs);
        write("\nYou feel an inner warmth as the Queen of Darkness " +
            "recognises your exploits and grants you a higher standing " +
            "within the guild.\n");

        TP->adjust_standing(RND_RANGE(TP->query_skill(PS_GUILD_LEVEL), 20));
    }
    else
    {
        if ((TP->query_prop(TMP_POT_LAST_TIME_PRAYED) + 3000 +
            random(500)) < time())
            TP->adjust_standing(RND_RANGE(90, 10));
        else
            TP->adjust_standing(RND_RANGE(-30, 20));
    }
    
    TP->add_prop(TMP_POT_LAST_TIME_PRAYED, time());
    
    /* Only here can the guildlevel change. So we update the admin to
     * keep the new value as it needs to queried sometimes when the
     * player is not logged on and /secure/finger_player does not allow
     * for querying skills....
     */
    GUILD_ADMIN->set_guild_level(TP->query_real_name(),
        TP->query_skill(PS_GUILD_LEVEL));
#endif
        
    write("\nYou rise again, feeling mentally refreshed.\n");
        
    if (TP->query_prop(TMP_POT_DEDICATION_SCROLL) &&
        !present("scroll_of_dedication", this_player()) &&
        !present("scroll_of_high_dedication", this_player()))
    {
        setuid();
        seteuid(getuid());
        
        if (TP->query_prop(TMP_POT_DEDICATION_SCROLL) == GUILD_LEVEL_PRIEST)
            scroll = clone_object(GUILDDIR + "obj/priest_scroll");
        else
            scroll = clone_object(GUILDDIR + "obj/high_priest_scroll");
        
        if (scroll)
        {
            if (gPriest && environment(gPriest) == TO)
            {
                scroll->remove_prop(OBJ_M_NO_DROP);
                scroll->remove_prop(OBJ_M_NO_GIVE);
                
                if (scroll->move(gPriest))
                    scroll->move(gPriest, 1);
                
                gPriest->command("give scroll to " + OB_NAME(TP));
                if (environment(scroll) == gPriest)
                    gPriest->command("drop scroll");

                scroll->add_prop(OBJ_M_NO_DROP, 1);
                scroll->add_prop(OBJ_M_NO_GIVE, 1);
            }
            else
            {
                write("A scroll suddenly materialises in your inventory.\n");
                if (scroll->move(TP))
                {
                    write("But the scroll is too heavy and you drop it.\n");
                    tell_room(TO, QCTNAME(TP) + " drops a scroll.\n", TP);
                    
                    if (scroll->move(TO))
                        scroll->move(TO, 1);
                }
            }
        }
    }

    return 1;
}

void
gs_hook_start_meditate()
{
    write("You kneel upon one of the low wooden benches encircling " +
        "the altar and close your eyes in a silent prayer. A feeling " +
        "of great ease and self control falls upon you. You block " +
        "off your senses and concentrate solely upon your own mind. " +
        "You find yourself able to <set> your different preferences " +
        "at your own desire. Just <rise> when you are done praying. " +
        "You estimate your stats and the progress you make at them.\n");
    say(QCTNAME(this_player()) + " kneels upon one of the low wooden " +
        "benches encircling the altar and closes " + HIS(this_player()) +
        " eyes in a silent prayer.\n");
}

void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the " +
        "surface of your consciousness. You exhale and feel very " +
        "relaxed as you get up from the wooden bench.\n");
    say(QCTNAME(this_player()) + " rises from the wooden bench.\n");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}

int
choose_aspect(string arg)
{
    if (TP->query_priest_level() < GUILD_LEVEL_PRIEST)
    {
        write("You beseech the Queen of Darkness for her aid. For a moment " +
          "you thought you felt the dark amusement of a fell power, but " +
          "that feeling quickly departed.\n");
        return 1;
    }

    if (!arg)
    {
        notify_fail("Beseech which aspect of Takhisis? The Dark Warrior? " +
           "Or the Dark Lady?\n");
        return 0;
    }

    if (arg != "the dark warrior" && arg != "the dark lady" && 
        arg != "to be unaspected")
    {
        notify_fail("You may beseech Takhisis, and seek her dark blessing " +
           "for you to take on one of her fell aspects:\n\n   The Dark Warrior" +
           " - the martial bringer of darkness, death and destruction.\n" +
           "   The Dark Lady - the cruel manipulator and beautiful temptress.\n\n" +
           "Either <beseech the dark warrior> or <beseech the dark lady>. You " +
           "may also <beseech to be unaspected>.\n");
        return 0;
    }

    if(TP->query_skill(PS_STANDING) < -100)
    {
        notify_fail("You are out of favour with Takhisis. Your attempt at " +
           "seeking her dark blessings failed.\n");
        return 0;
    }

    if(arg == "the dark warrior")
    {
       if(TP->query_prop(DARK_WARRIOR_ASPECT))
      {
          notify_fail("You are already aspected to the Dark Warrior!\n");
          return 0;
      }

        write("You beseech the aspect of Takhisis known as the Dark Warrior, " +
          "seeking martial blessings " +
          "and prayers that will allow you to bring death and destruction " +
          "to the realms!\n\nYour petition to the Queen of Darkness is " +
          "successful, and you are now aspected to the Dark Warrior! Your " +
          "medallion pulses briefly with a malevolent light.\n");
        say(QCTNAME(this_player()) + " beseeches Takhisis the Dark Warrior, " +
          "seeking martial blessings and prayers to bring death and " +
          "destruction to the realms!\n");

        TP->add_prop(DARK_WARRIOR_ASPECT, 1);

        if(TP->query_prop(DARK_LADY_ASPECT))
          TP->remove_prop(DARK_LADY_ASPECT);

        return 1;
    }

    if(arg == "the dark lady")
    {
       if(TP->query_prop(DARK_LADY_ASPECT))
      {
          notify_fail("You are already aspected to the Dark Lady!\n");
          return 0;
      }
       if(TP->query_prop(ACTIVE_ENCHANTMENT))
      {
          notify_fail("You cannot beseech the aspect of the Dark Lady while " +
            "you have a martial blessing active on your weapon!\n");
          return 0;
      }

        write("You beseech the aspect of Takhisis known as the Dark Lady, " +
          "seeking curses and prayers to dominate the will of others, " +
          "blessings of protection and unholy miracles of healing!\n\n" +
          "Your petition to the Queen of Darkness is successful, and " +
          "you are now aspected to the Dark Lady! Your medallion pulses " +
          "briefly with a malevolent light.\n");
        say(QCTNAME(this_player()) + " beseeches Takhisis the Dark Lady, " +
        "seeking curses and prayers to dominate the will of others, " +
        "blessings of protection and unholy miracles of healing!\n");

        TP->add_prop(DARK_LADY_ASPECT, 1);

        if(TP->query_prop(DARK_WARRIOR_ASPECT))
          TP->remove_prop(DARK_WARRIOR_ASPECT);
        return 1;
    }

    if(arg == "to be unaspected")
    {
       if(!TP->query_prop(DARK_LADY_ASPECT) && 
          !TP->query_prop(DARK_WARRIOR_ASPECT))
      {
          notify_fail("You are already unaspected!\n");
          return 0;
      }

        write("You are now an unaspected Priest of Takhisis. Your medallion pulses " +
          "briefly with a malevolent light.\n");
        TP->remove_prop(DARK_WARRIOR_ASPECT);
        TP->remove_prop(DARK_LADY_ASPECT);

        return 1;
    }

    notify_fail("Beseech what?\n");
    return 0;
}

void
init()
{
    ::init();
    
    init_skill_raise();
    add_action(do_pray, "pray");
    add_action(choose_aspect,"beseech");
    init_lib_join();
    init_skill_raise();
    init_guild_support();
}
