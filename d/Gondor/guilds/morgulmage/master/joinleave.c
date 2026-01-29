/*
 *  /d/Gondor/guilds/morgulmage/master/joinleave.c
 *
 *  This file is part of the Morgul Mage master object. It should
 *  not be loaded or called directly.
 *
 *  Created by Eowul, May 11th, 2009
 */

int is_acceptable_as_member(object player) {
    return (MORGUL_ROOM_DIR + "death_room")->accept_player(player);
}

/*
 * Function   : expulsion_pending
 * Description: Is there an expulsion pending for the given mage
 * Arguments  : mage - the name of the mage to be checked
 * Returns    : string - the name of the person responsible for the
 *                 expulsion, then a colon, then the official log reason.
 */
string expulsion_pending(mixed mage) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    
    if (member_array("expelled", m_indices(member_information[magename])) == -1)
    {
        return 0;
    }
    
    return member_information[magename]["expelled"][0] + ": " + 
        member_information[magename]["expelled"][1];
}

/*
 * Function   : add_player_to_guild
 * Description: Adds the shadow to the player and sets the necessary information
 *            : within the master object.
 * Arguments  : player - the player joining the guild
 *            : sponsor - the player that sponsored the new mage
 */
public int add_player_to_guild(object player, string sponsor)
{
    int     result;

    object shadow = clone_object(MORGUL_SHADOW);
    if ((result = shadow->shadow_me(player, GUILD_TYPE,
          GUILD_STYLE, GUILD_NAME)) != 1)
    {
        player->catch_msg("For unknown reasons you are not able to join "
          + "the guild.\n");
        SECURITY->do_debug("destroy", shadow);
        return 0;
    }

    player->clear_guild_stat(SS_OCCUP);
    set_mage_penalty(player, 0);
    player->set_bit(MORGUL_GROUP, MORGUL_MAGE_BIT);
    player->init_occ_shadow("");

    write_file(MORGUL_REGULAR_RECORDS, "MORGUL MAGES: " + player->query_name()
      + " joined the Morgul Mages sponsored by " + CAP(sponsor)
      + ". " + ctime(time()) + ".\n");
    player->catch_msg("You are now a member of the Society of Morgul "
      + "Mages!\n");
      
    string magename = get_mage_real_name(player);
    initialize_member(magename);
    member_information[magename]["sponsor"] = sponsor;
    member_information[magename]["jointime"] = time();
    member_information[magename]["tuvale"] = 1;
    save_data();
    return 1;
}

/*
 * Function   : remove_shadow
 * Description: Remove all the objects from the player related to the guild
 * Arguments  : object mage - the mage to remove
 *            : int punish - kill the player for leaving
 */
private int remove_shadow(object mage, int punish)
{
    int     result;
    object  robe;

    if (!(result = mage->remove_guild_occ()))
        return 0;

    if (mage->query_guild_name_lay() == GUILD_NAME) {
        mage->remove_guild_lay();
        mage->clear_guild_stat(SS_LAYMAN);        
    }

    mage->set_nazgul(0);
    mage->clear_bit(MORGUL_GROUP, MORGUL_MAGE_BIT);
    mage->clear_guild_stat(SS_OCCUP);
    mage->remove_undead_shadow();
    mage->remove_mana_shadow();
    mage->remove_skill(SS_MORGUL_PENALTY);
    mage->remove_cmdsoul(MORGUL_COMMAND_SOUL);
    mage->remove_cmdsoul(MORGUL_GUILD_DIR + "morgul_spells");
    mage->update_hooks();
    if (mage->query_default_start_location() == MORGUL_ROOM_DIR + "startroom")
    {
        mage->set_default_start_location(mage->query_def_start());
    }
    
    if (objectp(robe = present(MORGUL_S_SPELL_OBJECT, mage)))
    {
        mage->catch_msg("Your " + robe->query_short() + " bursts out in "
          + "flames and disappears.\n");
        tell_room(ENV(mage), "The "+robe->query_short()+" of "+
          QTNAME(mage)+" bursts out in flames and disappears.\n", mage);
        robe->remove_object();
    }
    
    if (punish)
    {
        MORGUL_DEATH_ROOM->teleledningsanka();
        object deathroom = find_object(MORGUL_DEATH_ROOM);
        
        if (!objectp(present(mage, deathroom)))
        {
            mage->catch_msg("You are summoned by a powerful spirit.\n");
            mage->move_living("X", deathroom);
        }
        
        mage->heal_hp(- mage->query_max_hp() - 100);
        mage->do_die(deathroom);
    }
    return 1;
}

/*
 * Function   : remove_player_from_guild
 * Description: Remove the player from the guild
 * Arguments  : mage - the mage to remove
 *            : reason - the reason the player was removed
 *            : punish - kill the player for leaving
 */
public int remove_player_from_guild(object mage, string reason = 0, 
    int punish = 1)
{    
    string magename = get_mage_real_name(mage);
    int     result;
 
    if (!IS_MEMBER(mage)) return 0;
    
    if (result = remove_shadow(mage, punish))
    {
        m_delkey(member_information, magename);
        remove_player_from_positions(magename);
        save_data();
        
        write_file(MORGUL_REGULAR_RECORDS, "MORGUL MAGES: " + mage->query_name()
          + " left the Morgul Mages. Reason: " + reason
          + " (" + punish + "). " + ctime(time()) + ".\n");
        write_file(MORGUL_NAZGUL_RECORDS, mage->query_name()+ " left the Morgul "+
            "Mages. Reason: " + reason + ctime( time() )+ ".\n" );
        mage->catch_msg("The Lord of Morgul removes you from the "
          + "Society of Morgul Mages!\n");
    }
    else
    {
        write_file(MORGUL_LOG, "MORGUL MAGES: " + mage->query_name()
          + " failed to leave the Morgul Mages. Reason: " + reason
          + " (" + punish + "). Result: " + result + ". "
          + ctime(time()) + ".\n");
    }

    return result;
}

/*
 * Function   : expel_player_from_guild
 * Description: Called by the command soul to remove a player from the guild
 * Arguments  : caster - the name of the person expelling the mage
 *            : name - the name of the mage being expelled
 *            : reason - the motivation for removing the mage
 */
public void
expel_player_from_guild(string caster, string name, string reason)
{
    object player;

    player = find_player(name);
    if (objectp(player))
    {
        remove_player_from_guild(player, reason, 1);
        return;
    }

    string magename = get_mage_real_name(name);
    initialize_member(magename);
    member_information[magename]["expelled"] = ({ caster, reason });
    save_data();
}

/*
 * Function   : remove_player_from_layman
 * Description: Removes a play from his layman guild
 * Arguments  : Player object to remove
 */
private int
remove_player_from_layman(object player) 
{
    setuid();
    seteuid(getuid());
    
    switch(player->query_guild_name_lay()) {
        case "Angmar Army":
            player->catch_msg("You are removed from the Angmar Army.\n");

            log_file("morgulmage_switch", ctime(time()) + " "
                + capitalize(player->query_real_name()) + " removed "
                + "from the Angmar Army.\n");

            player->remove_skill(112201 /*SS_SHIELD*/);
            player->remove_skill(112200 /*SS_SMASH*/);
            player->remove_skill(112202 /*SS_BASH*/);
            player->remove_cmdsoul("/d/Shire/guild/AA/soul/aa_soul");
            player->update_hooks();
            "/d/Shire/guild/AA/obj/aa_ranks"->remove_entry(player->query_real_name());
            return player->remove_guild_lay();

        case "Necromancers Of Vile Darkness":
            player->catch_msg("You are removed from the Necromancers Of Vile Darkness.\n");   

            log_file("morgulmage_switch", ctime(time()) + " "
                + capitalize(player->query_real_name()) + " removed "
                + "from the Necromancers.\n");


            "/d/Faerun/guilds/nov/obj/nmanager"->remove_nov_member(player->query_real_name());
            player->remove_cmdsoul("/d/Faerun/guilds/nov/souls/nov_soul");
            player->update_hooks();
            return player->remove_guild_lay();    

        case "Cabal of Hiddukel":
            player->catch_msg("You are removed from the Cabal of Hiddukel.\n");

            log_file("morgulmage_switch", ctime(time()) + " "
                + capitalize(player->query_real_name()) + " removed "
                + "from the Thief guild.\n");


            player->remove_skill(108300 /* SS_SACRIFICE */);
            player->remove_skill(108301 /* SS_STOLEN */);
            if (objectp(present("Thief_OBJ", player))) 
            {
                present("Thief_OBJ", player)->remove_object();
            }

            "/d/Krynn/solamn/thief/guild/master"->remove_thief(player->query_real_name());

            player->remove_cmdsoul("/d/Krynn/solamn/thief/guild/obj/thief_soul_cabal");
            player->update_hooks();
            return player->remove_guild_lay();    
    }

    log_file("morgulmage_switch", ctime(time()) + " "
        + capitalize(player->query_real_name()) + " was in unknown "
        + "layman guild " + player->query_guild_name_lay() + ".\n");
    return 0;
}

/*
 * Function   : setup_layman_guild
 * Description: Makes sure that the player has the layman guild shadow
 * Arguments  : Player object to remove
 */
public void
setup_layman_guild(object player)
{

    // Apprentices are no longer layman Morgul Mages. Only full
    // mages take up the layman slot.
    if (IS_APPRENTICE(player))
    {
        if (player->query_guild_name_lay() == GUILD_NAME)
        {
            player->catch_msg("\nBeing the pathetic wretch you are, the " +
                "Dark Lord recognises you need assistance in serving " +
                "His will. As an apprentice Morgul Mage you have been " +
                "unshackled from complete commitment, and may once again " +
                "seek support from a layman guild approved by the Nine.\n\n");
            player->remove_guild_lay();
            player->clear_guild_stat(SS_LAYMAN);

            return;
        }

        return;
    }

    if (player->query_guild_name_lay() == GUILD_NAME) return;

    if (stringp(player->query_guild_name_lay())) {
        player->catch_msg("\nFull Morgul Mages require occupational and "
            + "layman guild commitment. As such you cannot remain member of the " 
            + player->query_guild_name_lay() + ".\n\n");

        if (!remove_player_from_layman(player)) {
            player->catch_msg("You could not be removed from your guild, "
                + "please contact the AoP.\n");
            return;
        }
    }

    object shadow = clone_object(MORGUL_LAY_SHADOW);
    int result;
    if ((result = shadow->shadow_me(player, "layman",
          GUILD_STYLE, GUILD_NAME)) != 1)
    {
        log_file("morgulmage_switch", ctime(time()) + " Could not add "
            + "layman guild shadow to " + capitalize(player->query_real_name()) 
            + ". Reason: " + result + ".\n");

        player->catch_msg("You could not be added to the layman part "
            + "of the Morgul Mages. Please contact the AoP.\n");
        SECURITY->do_debug("destroy", shadow);
        return;
    } else {
        log_file("morgulmage_switch", ctime(time()) + " Added layman shadow to " 
            + capitalize(player->query_real_name()) + ".\n");
    }

    player->clear_guild_stat(SS_LAYMAN);        
}