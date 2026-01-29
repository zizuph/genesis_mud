/* 
 *  The room where mariner captain's can register their ensign.
 */

#pragma strict_types
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/palanthas/local.h";
#include CLOCKH
#include "guild.h"

inherit SHIP_BASE;

string * colour_options = ({ "yellow", "blue", "red", "green", "cyan", "violet",
             "black", "royal purple","maroon", "brown", "white", "aqua",
             "imperial red","imperial blue","tribal green","tribal yellow",
             "tribal red" });

string * insignia_options = ({ "roaring lion","golden sceptre","crossed axes",
             "crossed sabres","fierce manticore", "sea serpent", "storm cloud",
             "silver star", "bronze coronet", "red cross", "cresting wave" });

string * knight_options = ({ "golden crown","red rose","ornate broadsword",
             "kingfisher in flight", "mounted lancer" });

string * darmy_options = ({ "red dragon","blue dragon","black dragon",
             "white dragon", "green dragon", "bloody spear", 
             "bloody sword", "red-eyed wyvern" });

string * pot_options = ({ "red dragon","blue dragon","black dragon",
             "white dragon", "green dragon", "five-headed dragon",
             "shadowy temptress", "dark warrior" });

string * wohs_options = ({ "open spellbook","fireball", "lightning bolt", 
             "convergence of three moons", "robed wizard", "astrolab", 
             "glowing staff" });

string * dwarf_options = ({ "axe and shield","dwarven longbeard", "lone hill", 
             "bloody waraxe", "mining pick", "dwarven warhammer",
             "dwarven ironclad" });

string * elf_options = ({"aspen tree", "winged griffin", "crossed arrows",
             "golden sun", "silver moon", "crimson phoenix" });

string * kender_options = ({"decorated hoopak", "green apple tree", "full pouch",
             "laughing sun", "grinning kender" });

string * gnome_options = ({"bells and whistles", "long wrench", "open tome",
             "great mountain", "studious gnome" });

string * hobgob_options = ({ "red-eyed worg", "black worg", "white worg",
             "bloody axe" });

string * mino_options = ({ "twin horns", "angry bison", "double-headed waraxe",
             "victorious minotaur", "lightning bolt" });

mixed * ensign_details = ({  });

string ensign_short, ensign_long1, ensign_long2;
string * ensign_names, expiration, allowed_guild;

#define COLOUR_PROP        "_mariner_ensign_colour"
#define INSIG_PROP         "_mariner_ensign_insignia"
#define CONFIRM_REGISTER   "_mariner_confirm_register"
#define STD_ENSIGN         "/d/Krynn/std/boats/sailing_ensign"

void
reset_palan_room()
{
    return;
}

void
create_palan_room()
{
    SHORT("registrar of the Mariners");
    LONG("@@long_descr");

    EXIT("/d/Ansalon/guild/mariner/mariner_joinroom", "up", 0, 0);

    add_item(({"staircase","stairs","circular staircase"}),
        "A narrow circular staircase leads up to the guild hall " +
        "above.\n");
    add_item(({"registrar","registrar of the mariners"}),
        "In this room of the Guild of Mariners the registrar creates " +
        "on demand the personalised ensigns for mariner captains.\n");
    add_item(({"flags","maritime flags","walls","wall"}), 
        "Maritime flags of all ages, colours, and shapes cover the " +
        "walls here.\n");

    reset_palan_room();

}

string
long_descr()
{
    return "You are in the registrar of the mariners, where ship " +
        "captains may register their personal ensign. Maritime flags " +
        "of all makes and types cover the walls here.\n\n" +
        "Ship captains may:\n" +
        "    'select' to see the ensign options available to them.\n" +
        "    'select ensign colour <colour>'\n" +
        "    'select ensign insignia <insignia>'\n" +
        "    'check ensign' to see what their selected ensign looks like.\n" +
        "    'register ensign' and purchase the personalised ensign\n" +
        "     for 100 platinum coins.\n\n";
}

int
do_select(string str)
{
    string arg, * all_colour_options, * all_insignia_options;
    string cstring = "";
    string istring = "";
    int csize = 0;
    int isize = 0;

    all_colour_options = colour_options;
    all_insignia_options = insignia_options;

    if (TP->query_guild_member("Dragonarmy"))
        all_insignia_options += darmy_options;
    if (TP->query_guild_member("Solamnian Knights"))
        all_insignia_options += knight_options;
    if (TP->query_guild_member("Priests of Takhisis"))
        all_insignia_options += pot_options;
    if (TP->query_guild_member("Wizards of High Sorcery") ||
        TP->query_guild_member("School of High Magic"))
        all_insignia_options += wohs_options;
    if (TP->query_guild_member("Raiders of Throtyl"))
        all_insignia_options += hobgob_options;

    if(TP->query_race_name() == "dwarf")
        all_insignia_options += dwarf_options;
    if(TP->query_race_name() == "elf" || TP->query_race_name() == "half-elf")
        all_insignia_options += elf_options;
    if(TP->query_race_name() == "kender")
        all_insignia_options += kender_options;
    if(TP->query_race_name() == "minotaur")
        all_insignia_options += mino_options;
    if(TP->query_race_name() == "gnome")
        all_insignia_options += gnome_options;

    if (!str || str == "ensign options" || str == "options")
    {
        foreach(string col: all_colour_options)
        {
            csize++;
            cstring += col;
            if (sizeof(all_colour_options) - csize == 1)
                cstring += ", and ";
            else if (sizeof(all_colour_options) - csize > 1)
                cstring += ", ";
        }

        foreach(string insig: all_insignia_options)
        {
            isize++;
            istring += insig;
            if (sizeof(all_insignia_options) - isize == 1)
                istring += ", and ";
            else if (sizeof(all_insignia_options) - isize > 1)
                istring += ", ";
        }

          write("The following ensign colour and insignia options are " +
              "available to you:\n\nEnsign colour options: " +cstring+ ".\n\n" +
                "Ensign insignia options: " +istring+ ".\n\nYou can " +
                "'select ensign colour <colour>' and 'select ensign " +
                "insignia <insignia>', and <check ensign> to see what " +
                "the maritime flag will look like. When you are happy " +
                "with the design you can <register ensign> to purchase " +
                "it.\n");
          return 1;
    }

    if (parse_command(str, environment(TP), "'ensign' 'colour' [to] %s", arg))
    {
        if(member_array(lower_case(arg), all_colour_options) > -1)
        {
            write("You select '" +arg+ "' as the colour of your ensign.\n");
            TP->add_prop(COLOUR_PROP, arg);
            return 1;
        }

        write("The colour '" +arg+ "' is not an option for your " +
            "ensign. Check 'select' for a list of available colours.\n");
        return 1;
    }

    if (parse_command(str, environment(TP), "'ensign' 'insignia' [to] %s", arg))
    {
        if(member_array(lower_case(arg), all_insignia_options) > -1)
        {
            write("You select '" +arg+ "' as the insignia of your ensign.\n");
            TP->add_prop(INSIG_PROP, arg);
            return 1;
        }

        write("The insignia '" +arg+ "' is not an option for your " +
            "ensign. Check 'select' for a list of available insignias.\n");
        return 1;
    }

    write("Either 'select ensign colour <colour>' or 'select ensign " +
        "insignia <insignia>'.\n");
    return 1;
}

int
do_check(string str)
{
    if(!str || str != "ensign")
    {
        notify_fail("Check what? Ensign?\n");
        return 0;
    }

    string ensign_colour = TP->query_prop(COLOUR_PROP);
    string ensign_insig = TP->query_prop(INSIG_PROP);

    if(!strlen(ensign_colour))
    {
        notify_fail("You haven't selected an ensign colour yet.\n");
        return 0;
    }

    if(!strlen(ensign_insig))
    {
        notify_fail("You haven't selected an ensign insignia yet.\n");
        return 0;
    }

    ensign_short = LANG_ADDART(ensign_colour)+ " ensign " +
       "adorned with " +LANG_ADDART(ensign_insig);
    ensign_long1 = "Flying from the main mast is " +
        LANG_ADDART(ensign_colour)+ " ensign adorned with " +
        LANG_ADDART(ensign_insig)+ ", the insignia of Captain "; 
    ensign_long2 = "Neatly folded is " +LANG_ADDART(ensign_colour)+ 
        " ensign adorned with the insignia of " +LANG_ADDART(ensign_insig)+ ". ";

    write("Your ensign would look like:\n\n" +
        "Ensign short description: " +ensign_short+ "."+
        "\n\nHoisted ensign description: " +ensign_long1+ 
        capitalize(TP->query_real_name())+ "." +
        "\n\nLowered ensign detailed description: " +ensign_long2+ "\n\n" +
        "If you are happy with the ensign design you can have one " +
        "made for you for 100 platinum coins by <register>ing the " +
        "ensign with the registrar here.\n");

    return 1;
}

int
do_register(string str)
{
    if(!str || str != "ensign")
    {
        notify_fail("Register what? Ensign?\n");
        return 0;
    }

    string ensign_colour = TP->query_prop(COLOUR_PROP);
    string ensign_insig = TP->query_prop(INSIG_PROP);

    if(!strlen(ensign_colour))
    {
        notify_fail("You haven't selected an ensign colour yet.\n");
        return 0;
    }

    if(!strlen(ensign_insig))
    {
        notify_fail("You haven't selected an ensign insignia yet.\n");
        return 0;
    }

    if((TP->query_guild_name_craft() != GUILD_NAME) &&
        !TP->query_wiz_level())
    {
        notify_fail("Only mariners of Captain rank or higher are " +
            "allowed to register personal ensigns.\n");
        return 0;
    }

    int sailor_lvl = TP->query_stat(SS_CRAFT) / 12; 

    // Mariner captain levels are 11 and 12.
    if((sailor_lvl < 11) && !TP->query_wiz_level())
    {
        notify_fail("Only mariners of Captain rank or higher are " +
            "allowed to register personal ensigns. You will need " +
            "to gain some experience as a mariner before you will " +
            "be able to get your own ensign!\n");
        return 0;
    }

    ensign_short = ensign_colour+ " ensign " +
       "adorned with " +LANG_ADDART(ensign_insig);
    ensign_long1 = "Flying from the main mast is " +
        LANG_ADDART(ensign_colour)+ " ensign adorned with " +
        LANG_ADDART(ensign_insig)+ ", the insignia of Captain "; 
    ensign_long2 = "Neatly folded is " +LANG_ADDART(ensign_colour)+ 
        " ensign adorned with the insignia of " +LANG_ADDART(ensign_insig)+ ". ";

    if(!TP->query_prop(CONFIRM_REGISTER))
    {
        write("The registrar says: So to confirm, " +
            "your ensign would look like:\n\n" +
            "Ensign short description: " +LANG_ADDART(ensign_short)+ "."+
            "\n\nHoisted ensign description: " +ensign_long1+ 
            capitalize(TP->query_real_name())+ "." +
            "\n\nLowered ensign detailed description: " +ensign_long2+ "\n\n" +
            "If you are happy with the ensign design and have the " +
            "100 platinum coins for the purchase, <register ensign> " +
            "once again to confirm.\n");
        say("The registrar whispers something to " +QTNAME(TP)+ ".\n");
        TP->add_prop(CONFIRM_REGISTER, 1);
        return 1;
    }

    // costs 100 platinum, or 172800 copper coins
    if(!MONEY_ADD(TP, -172800))
    {
        notify_fail("You don't have 100 platinum coins to register " +
            "an ensign.\n");
        return 0; 
    }

    setuid();
    seteuid(getuid());

    write("You pay the registrar, who swiftly crafts you up your customised " +
        "ensign and gives it to you.\n");
    say(QCTNAME(TP) + " pays the registrar, who swiftly crafts up a " +
        "customised ensign and gives it to " +HIM(TP)+ ".\n");

    object ensign = clone_object(STD_ENSIGN);
    mixed * ensign_array = ({ ensign_short, ensign_long1, ensign_long2,
        ({ "ensign", "main mast", ensign_colour + " ensign", "flag" }),
        GUILD_NAME });

    ensign->set_ensign_details(ensign_array);
    ensign->create_the_ensign();

    if (ensign->move(TP) != 0)
    {
        write("Noticing that you are too burdened to carry the ensign, the " +
    	    "registrar places it on the ground before you.\n");
        say("The registrar places the ensign on the ground before " 
            + QCTNAME(TP) + ".\n");
        ensign->move(environment(TP));
    }

    TP->remove_prop(CONFIRM_REGISTER);
    TP->remove_prop(COLOUR_PROP);
    TP->remove_prop(INSIG_PROP);

    return 1;
}

void
init()
{
    ::init();
    add_action(do_select, "design");
    add_action(do_select, "select");
    add_action(do_check, "check");
    add_action(do_register, "register");

}
