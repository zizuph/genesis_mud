/*
 * Setup Functions for different Guilds
 *
 * When a Test NPC is created, it will call a setup function if it
 * has been defined. This module is included in the main test_npc
 * file.
 *
 * Created by Petros, December 2009
 */

#pragma strict_types

public void
setup_knight_effects_helper()
{
    object medal;
    object oldtp = this_player();
    set_this_player(this_object());
    if (objectp(medal = present("pal_med", this_player())))
    {
        medal->set_knight_level(3);
        medal->set_knight_sublevel(11);
    }
    clone_object("/d/Krynn/guilds/knights/guildhall/npcs/steed")->move(environment(this_object()));
    command("mount warhorse");
    set_this_player(oldtp);
}

public void
setup_knight_effects()
{
    set_alarm(1.0, 0.0, &setup_knight_effects_helper());
}

public void
setup_gladiator_effects()
{
}

public void
setup_neidar_effects()
{
}

public void
setup_newmerc_effects()
{
}


public void
setup_ogre_effects()
{
    set_alarm(1.0, 0.0, this_object()->refresh_living);
}

public void
setup_academic_effects()
{    
    object oldtp = this_player();
    set_this_player(this_object());
    "/d/Calia/guilds/academics/spells/lithodermu"->do_ability("");
    set_this_player(oldtp);
}

public void
setup_vampire_effects()
{
    // Set up Celerity
    object oldtp = this_player();
    set_this_player(this_object());
    "/d/Terel/guilds/vamp/spells/celerity"->do_ability("");
    set_this_player(oldtp);
}

public void
setup_cadet_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    
    command("cchange right");
    set_skill(SS_WEP_SWORD, 50); // cadets max out at 50
    
    set_this_player(oldtp);
}

private void
delayed_setup_mage_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    
    this_player()->command("cast narusse");
    
    set_this_player(oldtp);
}

public void
setup_mage_effects()
{
    set_alarm(5.0, 0.0, &delayed_setup_mage_effects());
}

private void
delayed_setup_mage_defence_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());

    this_player()->command("cast ringurth");

    set_this_player(oldtp);
}

public void
setup_mage_defence_effects()
{
    set_alarm(5.0, 0.0, &delayed_setup_mage_defence_effects());
}

public void
setup_base_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    
    foreach (int skill_num, mixed skill_item : SS_SKILL_DESC)
    {
        if (skill_item[4] > 0)
        {
            int current_train = this_player()->query_skill(skill_num);
            if (current_train < skill_item[4])
            {
                set_skill(skill_num, skill_item[4]); // set to adventurer guild max
            }
        }
    }
    
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 80);
    
    set_this_player(oldtp);
}

public void
setup_base_undead_effects()
{
    setup_base_effects();

    object oldtp = this_player();
    set_this_player(this_object());

    this_player()->add_prop(LIVE_I_UNDEAD, 100);
    
    set_this_player(oldtp);    
}

public void
setup_bda_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    
    command("dfear");

    set_this_player(oldtp);
}

public void
setup_rda_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    
    command("dfear");

    set_this_player(oldtp);
}

public void
setup_ew_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    
    foreach (int skill_num, mixed skill_item : SS_SKILL_DESC)
    {
        if (skill_item[4] > 0)
        {
            int current_train = this_player()->query_skill(skill_num);
            if (current_train < skill_item[4])
            {
                set_skill(skill_num, skill_item[4]); // set to adventurer guild max
            }
        }
    }
    
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 80);
    
    set_this_player(oldtp);
}

public void
setup_union_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());

    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_SWORD, 84);
    set_skill(SS_PARRY, 84);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_BLIND_COMBAT, 40);
    
    /* Unique skills to the Union */
    set_skill(139050, 100); // Sway
    set_skill(139051, 100); // Slash
    set_skill(139052, 100); // Fling
    set_skill(139053, 9);   // OCC Level
    set_skill(139055, 1180); // Union Dignity
    set_skill(139056, 1200); // Union Pride
    set_skill(139057, 1181); // Union Grace
    set_skill(139058, 1146); // Union Purity

    set_this_player(oldtp);
}

public void
setup_union_acro_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());

    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_SWORD, 84);
    set_skill(SS_PARRY, 50); // -34 for + 80 acro
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_ACROBAT, 80);
    
    /* Unique skills to the Union */
    set_skill(139050, 100); // Sway
    set_skill(139051, 100); // Slash
    set_skill(139052, 100); // Fling
    set_skill(139053, 9);   // OCC Level
    set_skill(139055, 1180); // Union Dignity
    set_skill(139056, 1200); // Union Pride
    set_skill(139057, 1181); // Union Grace
    set_skill(139058, 1146); // Union Purity

    set_this_player(oldtp);
}

private void
delayed_setup_sohm_defense_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    "/d/Krynn/guilds/sohm/spells/stoneskin"->do_ability("");
    // No need to do anything else because the complete triggers should activate
    // the rest of the spells necessary.
    set_this_player(oldtp);
}

public void
setup_sohm_defense_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    set_skill(SS_FORM_TRANSMUTATION, 60); // trainers max out at 50. Need 60 to cast spells
    set_alarm(5.0, 0.0, &delayed_setup_sohm_defense_effects());
    set_this_player(oldtp);
}

public void
setup_pot_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());

    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_ELEMENT_LIFE, 100);

    set_skill(143004, 149);
    set_skill(143007, 1200);

    add_prop("_pot_dark_warrior_aspect", 1);

    set_this_player(oldtp);
}