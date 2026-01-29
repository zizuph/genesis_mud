#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit "/d/Ansalon/common/cheater";

#define SHIP_DIR "/d/Ansalon/goodlund/bloodsea/obj/"

#define BOAT_DESC ({  "imposing", "massive", "menacing", "broad-decked", \
                        "sleek", "swift", "black", \
                        "trim", "black-sailed", "grim" })
 
#define BOAT_DESIGN ({ "skull over crossbones",  \
                        "flaming jolly roger", \
                        "parrot with an eye-patch", \
                        "crossed sabres dripping blood", \
                        "screaming skull", \
                        "dwarven pirate", \
                        "drunken corsair", \
                        "naked maiden", \
                        "deep sea dragon", \
                        "coy mermaid" })

#define BOAT_FIGUREHEAD ({ "a blindfolded and weeping maiden",  \
                        "a snarling sea serpent", \
                        "a cackling sea witch", \
                        "a raging sea goddess", \
                        "a mad dwarven king wielding twin axes", \
                        "a solemn minotaur holding a greatsword in both hands", \
                        "a rearing black nightmare", \
                        "a galloping celestial steed", \
                        "a grim warrior pointing his spear forward", \
                        "a sabre-wielding pirate" })

#define BOAT_DESC_PROP    "_pirate_boat_prop_desc"
#define BOAT_DESIGN_PROP  "_pirate_boat_prop_design"
#define BOAT_FIGURE_PROP  "_pirate_boat_prop_figurehead"

object pegleg, patch, monkey, parrot, hook;

public string
query_guild_name_lay()
{
    return "Pirate of the Bloodsea";
}

void
create_krynn_monster()
{
    set_name("stumpy");
    set_living_name("stumpy");
    set_title("the Landlocked, One-Legged Corsair and Ship Acquirer");
    add_name("pirate");
    set_race_name("human");
    set_adj("one-legged");
    set_adj("grizzled");
    set_short("one-legged grizzled pirate");
    set_long("This grizzled one-legged human is a life-long bucaneer " +
        "and plunderer of the Bloodsea. For fellow pirates he will " +
        "commandeer a ship on request.. and for a fee!\n");
    set_stats(({70,170,75,155,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("say Argh! Want a ship? I can get ye one!");
    add_act("emote hobbles around on his pegleg.");
    add_act("say The minotaurs are distracted by the Black Dragonarmy, so " +
        "it has never been a better time to plunder the isles!");
    add_act("emote grins toothily.");

    set_default_answer("The pirate looks at you as if you were and simpleton, " +
        "then grins and says very slowly: Ye want a ship? Ye can <commandeer> " +
        "one through me for a fee. Senior pirate discounts apply!\n");

    add_ask(({"ship","ships","ships for sale","boat","warship","frigate",
              "pirate frigate", "pirate ship",
              "corsair ship","fishing boat","sailing ship","corsair ship"}),
        VBFC_ME("ship_types"));

    trig_new("%w 'introduces' %s","react_to_intro");

    add_prop(OBJ_M_NO_ATTACK,"Attacking this pirate will only result in " +
        "you never being able to requisition a ship again on the Bloodsea! " +
        "You reconsider.\n");
}

void
react_to_intro(string who, string garbage)
{
    set_alarm(2.0,0.0,"return_intro", who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who, E(TO)))
    {
        command("say Argh " +C(who)+ "!");
	command("introduce myself");
        command("say Ye in thee market for ay fine ship?");
    }
}

string
ship_types()
{
    command("say I can commandeer a single pirate ship for ye...");
    command("say Cost will range depending on yer pirate seniority...");
    command("grin evil");
    command("say Jus <commandeer a pirate ship> and I will get ye " +
        "one if ye have tha gold!"); 
    command("say Or for Legendary Pirate Lords with a bit more loot " +
        "to spare, <commandeer a pirate frigate> and I'll get you " +
        "a flagship to terrorise the high seas!");
    command("say You can also let me know your <preference> for the " +
        "look or design on the ship if you want to pay a bit extra!");
    command("cackle");
    return "";
}

void
arm_me()
{
    seteuid(getuid(TO));
    pegleg = clone_object(GUILD_OBJ + "pegleg");
    pegleg->move(TO, 1);

    patch = clone_object(GUILD_OBJ + "patch");
    patch->move(TO, 1);

    monkey = clone_object(GUILD_OBJ + "monkey");
    monkey->move(TO, 1);

    parrot = clone_object(GUILD_OBJ + "parrot");
    parrot->move(TO, 1);

    hook = clone_object(GUILD_OBJ + "hook");
    hook->move(TO, 1);

    TO->command("wield hook");
    TO->command("wear pegleg");
    TO->command("wear eyepatch");
    TO->command("wear pegleg");
}


void
init_living()
{
    ::init_living();
    ADA("commandeer");
    ADA("preference");
}

int
preference(string str)
{
    string arg, * all_ship_options;

    if (!str)
    {
        command("say Your preference for what? Look, design, or figurehead?");
        return 1;
    }

    if (str == "look")
    {
        string ext = "";
        string arg;
        string * look_array = BOAT_DESC;
        int array_size = sizeof(look_array);

        foreach(string desc: look_array)
        {
            ext += desc;

            if(array_size == 2)
            {
                ext += ", and ";
                array_size -= 1;
            }
            else if(array_size > 2)
            {
                ext += ", ";
                array_size -= 1;
            }
            else
            {
                ext += ".";
            }
        }

        command("say Hmm... I could find a ship with the following " +
            "look: " + ext);
        command("say If you want, you can <preference look> " +
            "description and i'll see if I can commandeer such a ship?");
        return 1;
    }

    if (str == "design")
    {
        string ext = "\n";
        string arg;
        string * look_array = BOAT_DESIGN;
        int array_size = sizeof(look_array);

        foreach(string desc: look_array)
        {
            ext += "     " +desc;

            if(array_size == 2)
            {
                ext += ", and\n";
                array_size -= 1;
            }
            else if(array_size > 2)
            {
                ext += ",\n";
                array_size -= 1;
            }
            else
            {
                ext += ".\n";
            }
        }

        command("say Hmm... I could find a ship with the following " +
            "design on it: " + ext);
        command("say If you want, you can <preference design> " +
            "design and i'll see if I can commandeer such a ship?");
        return 1;
    }

    if (str == "figurehead")
    {
        string ext = "\n";
        string arg;
        string * look_array = BOAT_FIGUREHEAD;
        int array_size = sizeof(look_array);

        foreach(string desc: look_array)
        {
            ext += "     " +desc;

            if(array_size == 2)
            {
                ext += ", and\n";
                array_size -= 1;
            }
            else if(array_size > 2)
            {
                ext += ",\n";
                array_size -= 1;
            }
            else
            {
                ext += ".\n";
            }
        }

        command("say Hmm... I could find a frigate, if you can sail " +
            "one, and add the following " +
            "figurehead on it: " + ext);
        command("say If you want, you can <preference figurehead> " +
            "figurehead and i'll see if I can commandeer such a ship with one?");
        return 1;
    }

    if (parse_command(str, environment(TP), "'look' %s", arg))
    {
        if(member_array(lower_case(arg), BOAT_DESC) > -1)
        {
            command("say Very well! I will look for " +LANG_ADDART(arg)+ 
                " ship for ye when yer ready for me to commandeer one!");
            TP->add_prop(BOAT_DESC_PROP, lower_case(arg));
            return 1;
        }
        command("say Never seen " +LANG_ADDART(arg)+ 
                " ship before! Choose a look I know of!");
    }

    if (parse_command(str, environment(TP), "'design' %s", arg))
    {
        if(member_array(lower_case(arg), BOAT_DESIGN) > -1)
        {
            command("say Very well! I will look for a ship with " +
                LANG_ADDART(arg)+ " design on it!");
            TP->add_prop(BOAT_DESIGN_PROP, lower_case(arg));
            return 1;
        }
        command("say Never seen a ship with " +LANG_ADDART(arg)+ 
                " design before! Choose a design I know of!");
    }

    if (parse_command(str, environment(TP), "'figurehead' %s", arg))
    {
        if(member_array(lower_case(arg), BOAT_FIGUREHEAD) > -1)
        {
            command("say Very well! I will look for a frigate with " +
                arg+ " figurehead on it!");
            TP->add_prop(BOAT_FIGURE_PROP, lower_case(arg));
            return 1;
        }
        command("say Never seen a ship with " +arg+ 
                " figurehead before! Choose a figurehead I know of!");
    }

    command("say Yer need to preference a look, design or figurehead! Like... " +
        "'preference look grim' or 'preference design coy mermaid'!");
    command("say Or if yer want a list of options, 'preference look', " +
        "'preference design', or 'preference figurehead'.");

    return 1;
}

int
commandeer(string str)
{
    object ship, boat_in, who;
    int price;
    string pirate_name = "_comandeered_pirate_ship_" + TP->query_real_name();
    int extra_cost = TO->query_prop(pirate_name);

    if (check_cheater(TP, TO))
        return 1;

    if (str == "pirate ship" || str == "a pirate ship" || str == "ship")
    {
        if(PADMIN->query_pirate_king(TP) && !extra_cost)
            price = 0;
        else
            price = max(400, (14400 - (PIRATE_RANK(TP) * 10)));

        if(extra_cost)
            price = price * extra_cost;

        NF("The pirate says: You cannot afford a pirate ship.\n");
        if(!MONEY_ADD(TP, -price) && !PADMIN->query_pirate_king(TP))
	    return 0;

        if((TP->query_guild_name_lay() != GUILD_NAME) && (!TP->query_wiz_level()))
        {
            NF("The pirate looks at you suspiciously. He wants nothing to do " +
                 "with non-pirates!\n");
            return 0;
        }

        // Pirate wont commandeer a ship for low-ranked pirates
        if((TP->query_guild_level_lay() < 4) && (!TP->query_wiz_level()))
        {
            NF("The pirate looks at you incredulously. He has no intention of " +
                 "commandeering ships for Deck Swabbies or Cabinboys!\n");
            return 0;
        }

        if(TP->query_prop(BOAT_DESC_PROP) == "imposing" ||
            TP->query_prop(BOAT_DESC_PROP) == "massive" ||
            TP->query_prop(BOAT_DESC_PROP) == "broad-decked")
        {
            NF("The pirate looks at you incredulously. Only ships " +
                "the size of frigates can look " +
                TP->query_prop(BOAT_DESC_PROP)+ "! Either change your " +
                "look preference or commandeer a frigate!\n");
            return 0;
        }

        pirate_name = "_comandeered_pirate_ship_" + TP->query_real_name();
        if(TO->query_prop(pirate_name))
        {
            command("say Ye have already commandeered ships from me! Ye next " +
                "one will be more expensive!");
        }
        else if(PADMIN->query_pirate_king(TP))
        {
            command("say Ye commandeered ship for free, " +TP->query_guild_title_lay()+
                "!");
        }

        write("You pay the pirate, who tucks the money into a big pouch. He then whistles " +
              "loudly towards the cove entry...\n");
        say(QCTNAME(TP) + " pays the pirate some money. The pirate whistles loadly towards " +
              "the cove entry...\n");

        who = TP;
        ship = clone_object(SHIP_DIR + "pirate_ship2");

        if(TP->query_prop(BOAT_DESC_PROP))
            ship->set_ship_desc(TP->query_prop(BOAT_DESC_PROP));
        if(TP->query_prop(BOAT_DESIGN_PROP))
            ship->set_ship_design(TP->query_prop(BOAT_DESIGN_PROP));

        ship->move(environment(who));
        ship->config_boat_inside();
        boat_in = ship->query_boat_in();
        boat_in->set_owner(who);

        extra_cost++;

        TO->add_prop(pirate_name, extra_cost); 
        return 1;
    }

    if (str == "pirate frigate" || str == "a pirate frigate" || str == "frigate")
    {
        if(PADMIN->query_pirate_king(TP) && !extra_cost)
            price = 0;
        else
            price = 14400; // 100 gold

        if(extra_cost)
            price = price * extra_cost;

        NF("The pirate says: You cannot afford a pirate frigate. Costs 100 gold!\n");
        if(!MONEY_ADD(TP, -price) && !PADMIN->query_pirate_king(TP))
	    return 0;

        if((TP->query_guild_name_lay() != GUILD_NAME) && (!TP->query_wiz_level()))
        {
            NF("The pirate looks at you suspiciously. He wants nothing to do " +
                 "with non-pirates!\n");
            return 0;
        }

        // Pirate wont commandeer a ship for non pirate lords
        if((PIRATE_RANK(TP) > IS_PIRATE_LORD) && (!TP->query_wiz_level()))
        {
            NF("The pirate looks at you incredulously. He has no intention of " +
                 "commandeering a flagship for anything less than a Legendary " +
                 "Pirate Lord!\n");
            return 0;
        }

        pirate_name = "_comandeered_pirate_ship_" + TP->query_real_name();
        if(TO->query_prop(pirate_name))
        {
            command("say Ye have already commandeered ships from me! Ye next " +
                "one will be more expensive!");
        }
        else if(PADMIN->query_pirate_king(TP))
        {
            command("say Ye commandeered ship for free, " +TP->query_guild_title_lay()+
                "!");
        }

        write("You pay the pirate, who tucks the money into a big pouch. He then whistles " +
              "loudly towards the cove entry...\n");
        say(QCTNAME(TP) + " pays the pirate some money. The pirate whistles loadly towards " +
              "the cove entry...\n");

        who = TP;
        ship = clone_object(SHIP_DIR + "pirate_ship3");

        if(TP->query_prop(BOAT_DESC_PROP))
            ship->set_ship_desc(TP->query_prop(BOAT_DESC_PROP));
        if(TP->query_prop(BOAT_DESIGN_PROP))
            ship->set_ship_design(TP->query_prop(BOAT_DESIGN_PROP));
        if(TP->query_prop(BOAT_FIGURE_PROP))
            ship->set_ship_figurehead(TP->query_prop(BOAT_FIGURE_PROP));

        ship->move(environment(who));
        ship->config_boat_inside();
        boat_in = ship->query_boat_in();
        boat_in->set_owner(who);

        extra_cost++;

        TO->add_prop(pirate_name, extra_cost); 
        return 1;
    }

    NF("What did you say you wanted to commandeer? A pirate ship? Or a pirate frigate?\n");
	return 0; 
}
