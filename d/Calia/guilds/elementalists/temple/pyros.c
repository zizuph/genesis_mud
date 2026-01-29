/*
 * Pyros Statue Room in the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 * Moved room to fit actual place on pentagram - Jaacar, June 2016
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines
#define CONFIRM_CHANGE_PATRON "_player_i_confirm_change_patron"

// Prototypes

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public void
create_temple_room()
{
    set_short("Statue room inside the Elemental Temple");
    set_long("@@desc_long_description"); 

    try_item( ({ "pedestal", "white pedestal", "marble pedestal",
        "white marble pedestal" }),
        "The white marble pedestal is featured prominently in the "
      + "center of the room. A life-sized statue is sitting on top "
      + "of it.\n");

    try_item( ({ "statue", "life-sized statue" }),
        "This statue is very large. It is carved out of some sort of glowing "
      + "rock that seems to pulse with power. There is incredible heat "
      + "emanating from it. It depicts a man rising out of the flaming "
      + "ground, hands rising above his head. It measures about eight feet "
      + "across at he base of the flaming area, and stands about six feet "
      + "high at its highest point. The eyes of the statue glow bright "
      + "yellow.\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "pyros_start", "southeast", "@@cannot_enter_start_locations", 1, "@@cannot_see_start_locations");
    add_exit(ELEMENTALIST_TEMPLE + "outer14a", "west"); 
    add_exit(ELEMENTALIST_TEMPLE + "outer12", "northeast");
 
}

public string
desc_long_description()
{
	string long_desc = 
          "You stand inside the Elemental Temple of Calia, an ornately "
        + "constructed building that houses those devoted to the service "
        + "of the Elementals of Calia. The outer circle of the Temple "
        + "has hallways that lead into this room from the northeast and the "
        + "west. Featured in the center of the room is a white marble "
        + "pedestal with a statue upon it. "; 
    
    return long_desc += "\n\n";
}

public void
init()
{
    ::init();
    add_action("do_worship", "worship");
}

public string
get_patron_name(string element)
{
    string patron = "Unknown";
    switch (element)
    {
    case "fire":
        patron = "Lord Pyros";
        break;
    case "water":
        patron = "Lord Diabrecho";
        break;
    case "air":
        patron = "Lady Aeria";
        break;
    case "earth":
        patron = "Lady Gu";
        break;
    case "life":
    	patron = "Psuchae";
    	break;
    default:
    }
    return patron;
}

public void
remove_confirmation_prop(object player)
{
    player->remove_prop(CONFIRM_CHANGE_PATRON);
}

public int
do_worship(string arg)
{
    setuid();
    seteuid(getuid());
    object player = this_player();
    if (!GUILD_MANAGER->query_is_worshipper(player))
    {
        if (!GUILD_MANAGER->query_is_master_cleric(player))
        {
            if (!GUILD_MANAGER->query_is_full_master_cleric(player))
            {
                if (!GUILD_MANAGER->query_is_elder_cleric(player))
                {
                    notify_fail("What?\n");
                    return 0;
                }
            }
        }
    }

    notify_fail("Worship whom?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    if (arg != "pyros" && arg != "lord pyros")
    {
        return 0;
    }

    string statue_element = "fire";
    string element = GUILD_MANAGER->query_primary_element(player);
    string patron = get_patron_name(element);
    string newpatron = get_patron_name(statue_element);
    if (element == 0)
    {
        // Player has not selected a primary element. We set it here.
        GUILD_MANAGER->set_primary_element(player, statue_element);
        write("The booming voice of Lord Pyros echoes through your mind: "
              + "Welcome, "+capitalize(player->query_real_name())+"! "
              + "May you unleash the elemental flames upon all those who "
              + "stand in your way!\n");
        COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(player->query_real_name()) +
        	" has set their primary Element as Fire.\n");
        if (GUILD_MANAGER->query_is_worshipper(player))
        {
            player->init_worshipper_titles();
        }
        else
        {
            player->query_elemental_cleric_title();
        }
    }
    else if (element == statue_element)
    {
        // Player already has this as the primary element
        write("You renew your worship in " + patron + "!\n");
    }
    else if (player->query_prop(CONFIRM_CHANGE_PATRON) == statue_element)
    {
        // Player has confirmed that they want to change elements
        int old_primary = GUILD_MANAGER->query_primary_element_skillnum(player);
        GUILD_MANAGER->set_primary_element(player, statue_element);
        write("The booming voice of Lord Pyros echoes through your mind: "
              + "Welcome, "+capitalize(player->query_real_name())+"! "
              + "May you unleash the elemental flames upon all those who "
              + "stand in your way!\n");
        COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(player->query_real_name()) +
        	" has reset their primary Element to Fire.\n");
        if (GUILD_MANAGER->query_is_worshipper(player))
        {
            GUILD_MANAGER->set_created_own_title(player, 0);
            GUILD_MANAGER->set_title_created(player,"");
            player->init_worshipper_titles();
            if (player->query_skill(old_primary) > 40)
            {
                player->set_skill(old_primary, 40);
                write("Because of your change in devotion, you lose some training "
                      + "you previous had in " + element + " spells.\n");
            }
        }
        else
        {
            GUILD_MANAGER->set_created_own_title(player, 0);
            GUILD_MANAGER->set_title_created(player,"");
            player->query_elemental_cleric_title();
            GUILD_MANAGER->set_player_property(player, "teleport_locations", 0);
            write("The voice of Nysa echoes in your mind saying, 'Allow me to change "+
                "the pattern on your Mandala.'\nThe pattern on your Mandala suddenly "+
                "changes!\n'You will need to relearn your teleport locations.'\n");
            object old_mandala = present("_elemental_guild_mandala",TP);
            if (old_mandala)
            	old_mandala->remove_object();
            setuid();
            seteuid(getuid());
            clone_object(ELEMENTALIST_OBJS +"fire_mandala")->move(TP,1);
            GUILD_MANAGER->set_fire_carving(this_player());
            object skia_ob = present("_skiamorfi_object_", TP);
            if (skia_ob)
            	skia_ob->remove_object();
            write("Your teleport locations have been reset.\n");
        }
        GUILD_MANAGER->set_has_changed_element(player,1);
        
        remove_confirmation_prop(player);
    }
    else 
    {
        if (!GUILD_MANAGER->query_has_changed_element(player))
    	{
	        // Player is already another element. Need to ask them to confirm
	        // the change.
	        write("You are currently devoted to serving " + patron + ". Are "
	              + "you certain that you want to devote your worship to "
	              + newpatron + " instead? If so, <worship> again within the "
	              + "next thirty seconds.\n");
	        player->add_prop(CONFIRM_CHANGE_PATRON, statue_element);
	        set_alarm(30.0, 0.0, &remove_confirmation_prop(player));
	        return 1;
	    }
	    
	    write("You have already changed your devotion once. You will need "+
	        "to ask the Council if you wish to do so again.\n");
    }    
    return 1;
}
