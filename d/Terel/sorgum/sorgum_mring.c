/* -*- C++ -*- */

inherit "/d/Terel/mecien/valley/guild/mring";

void
update_spells(object ob)
{
    add_spell("carrus", "cast_spell", "ancient chariot");    
    ::update_spells(ob);

}

void
notify_icon_holders()
{
    this_player()->catch_msg("No icons grow warm.\n");
    return;
}

    
