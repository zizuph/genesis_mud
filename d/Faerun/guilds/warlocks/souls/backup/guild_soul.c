/*
 * Warlock Guild soul
 *
 * Nerull, 2017
 *
 */

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include "/d/Faerun/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

string chip_component;
string shop_component;
string herb_component;

object wield_par;

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Warlocks"; }

public mapping
query_cmdlist()
{
    return ([
        // Commands

        "wapatron"      : "wapatron",
        "walist"        : "walist",
        "waemotes"      : "s_waemotes",
        "wadefensive"   : "do_wadefensive",
        "wascatter"     : "chip_components",
        "wacreate"      : "create_charm",
        "wahelp"        : "s_wahelp",
        
        // Emotes
        "wagrin"        : "do_wagrin",
        "wasmile"       : "do_wasmile",
        "wanod"         : "do_wanod",
        "wagreet"       : "do_wagreet",
        "waanger"       : "do_waanger",
        "wadepart"      : "do_wadepart",
        "wainjury"      : "do_wainjury",
        "wadefy"        : "do_wadefy",
        "waslap"        : "do_waslap",
        "wadisgust"     : "do_wadisgust",
        "wapinch"       : "do_wapinch",
        "waunaf"        : "do_waunaf",
        "wasmell"       : "do_wasmell",
        "waperf"        : "do_waperf",
        "walaugh"       : "do_walaugh",
        "waboggle"      : "do_waboggle",
        
        // Asmodeus emotes
        "wadevilapp"    : "do_wadevilapp",
        
        // Hastur emotes
        "wayellowsign"  : "do_wayellowsign",
        
        // Baba Zirana emotes
        "wacannibalism" : "do_wacannibalism",
        ]);
}


int
s_wahelp(string str)
{
    if (str == "charms")
    {   
        write(""
        +"==================================================================\n"
        +"|           C H A R M S    A N D   C O M P O N E N T S           |\n"
        +"|----------------------------------------------------------------|\n"
        +"| Charms   | Component 1        Component 2          Component 3 |\n"
        +"|----------|-----------------------------------------------------|\n"
        +"| uraene   | flat bone chip     bat spleen            laurel     |\n"
        +"| uralane  | flat bone chip     tear of the innocent  blackberry |\n"
        +"| urbienc  | flat bone chip     virgin's blood        basil      |\n"
        +"| urchem   | curved bone chip   bloody fairy wing     thyme      |\n"
        +"| urfiviel | dried heart piece  vampire dust          coccinea   |\n"
        +"| urgashe  | curved bone chip   bat guano             garlic     |\n"
        +"| urhadoele| dried heart piece  virgin's blood        handasse   |\n"
        +"| urhaese  | dried heart piece  tear of the innocent  garlic     |\n"
        +"| urhagash | dried heart piece  bat spleen            suranie    |\n"
        +"| urhavol  | dried heart piece  bone-powder           coccinea   |\n"
        +"| urhuew   | flat bone chip     vampire dust          tarragon   |\n"
        +"| urkenu   | dried heart piece  tear of the innocent  fennel     |\n"
        +"| urlob    | dried heart piece  bat spleen            savory     |\n"
        +"| urluir   | curved bone chip   bone-powder           hemlock    |\n"
        +"| urnerulla| curved bone chip   sulphur               pepper     |\n"
        +"| urvaesa  | curved bone chip   vampire dust          chives     |\n"
        +"| urwem    | curved bone chip   sulphur               bilberry   |\n"
        +"| urfenn   | flat bone chip     virgin's blood        chervil    |\n"
        +"|----------------------------------------------------------------|\n"
        +"|        To create a charm, use 'wacreate <charm name>'          |\n"
        +"|                                                                |\n"
        +"|        To use a charm, do 'flare <charm name>'                 |\n"
        +"|________________________________________________________________|\n");
        
        return 1;
    }
    
    if (str == "emotes")
    {
        write(""   
        +"================================================================\n"
        +"|                  W A R L O C K   E M O T E S                 |\n"
        +"|--------------------------------------------------------------|\n"
        +"|            The general emotes for warlocks.                  |\n"
        +"|                                                              |\n"
        +"| waanger <target>        : Display anger at someone           |\n"
        +"| waboggle <target>       : Show shock at someone              |\n"
        +"| wadefy                  : Show your defiance of something    |\n"
        +"| wadepart                : Advise everyone you're departing   |\n"
        +"| wadisgust <target>      : Display disguist at someone        |\n"
        +"| wagreet <target>        : Acknowledge someone's presense     |\n"
        +"| wagrin                  : Contort face into a slight grin    |\n"
        +"| wainjury                : Stroke one of your scars           |\n"
        +"| walaugh <target>        : Laugh at someone                   |\n"
        +"| wanod <target>          : Barely nod at someone              |\n"
        +"| waperf <target>         : Look at someone disdainfully       |\n"
        +"| wapinch <target>        : Pinch someone's earlobe painfully  |\n"
        +"| waslap <target>         : Slap someone angrily               |\n"
        +"| wasmell <target>        : Smell someone                      |\n"
        +"| wasmile <target>        : Smile slightly at someone          |\n"
        +"| waunaf <target>         : show a blank face                  |\n"
        +"|______________________________________________________________|\n");
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SHIELD_UNLOCK)
        {
        write(""   
        +"|                                                              |\n"
        +"|                         PACT MAGIC                           |\n"
        +"|                                                              |\n"
        +"| nullify pact magic      : Reset your pact magic selection    |\n"
        +"|                                                              |\n"
        +"| *This command only work in the special location of your      |\n"
        +"|  patron.                                                     |\n"
        +"|______________________________________________________________|\n");
        }
        
        if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
        {
        write(""   
        +"|                                                              |\n"
        +"|    Additional emotes for Warlocks with Asmodeus as Patron    |\n"
        +"|                                                              |\n"
        +"| wadevilapp              : Turn into an arch devil            |\n"
        +"|______________________________________________________________|\n");
        }
        
        if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
        {
        write(""   
        +"|                                                              |\n"
        +"|    Additional emotes for Warlocks with Hastur as Patron      |\n"
        +"|                                                              |\n"
        +"| wayellowsign <target>   : Show the Yellow Sign at someone    |\n"
        +"|______________________________________________________________|\n"); 
        }
        
        if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
        {
        write(""   
        +"|                                                              |\n"
        +"|   Additional emotes for Warlocks with Baba Zirana as Patron  |\n"
        +"|                                                              |\n"
        +"| wacannibalism <target>  : Dream about eating someone         |\n"
        +"|______________________________________________________________|\n");
        }

        return 1;
    }
    
    write(""
    +"=====================================================================\n"
    +"|                      W A R L O C K   H E L P                      |\n"
    +"|-------------------------------------------------------------------|\n"
    +"|  You can get help for the Warlock guild by using the commands     |\n"
    +"|  below.                                                           |\n"
    +"|                                                                   |\n"
    +"|    > wahelp                           : This list                 |\n"
    +"|    > wapatron                         : About your patron         |\n"
    +"|    > wahelp charms                    : List of charms            |\n"
    +"|    > wahelp emotes                    : List of emotes            |\n"
    +"|    > walist                           : List awake members        |\n"
    +"|    > wadefensive (on/off)             : Turn defensive mode on or |\n"
    +"|                                         off for your spells.      |\n"
    +"|    > wascatter <skull/kneecap/heart>  : Break item into pieces    |\n"
    +"|-------------------------------------------------------------------|\n"
    +"|                                                                   |\n"
    +"|___________________________________________________________________|\n");
    
    return 1;   
}


int
wapatron()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
    {
        write(""
        +" ===============================================================\n"
        +"|  Y O U R   P A T R O N :            A S M O D E U S           |\n"
        +"|---------------------------------------------------------------|\n"
        +"|                                                               |\n"
        +"| Asmodeus is the most powerful of all archfiends and is the    |\n"
        +"| undisputed Lord of the Nine Hells. He often resides in        |\n"
        +"| Nessus, the Ninth and lowermost layer of Hell where he        |\n"
        +"| commands his legions of devils and other arch devils and      |\n"
        +"| Dukes of the other layers of Hell. Asmodeus is about          |\n"
        +"| thirteen feet tall, and looks handsome, strong, very          |\n"
        +"| cunning, and has lustrous skin and black hair. His eyes are   |\n"
        +"| crimson and shine with with internal power. His forehead is   |\n"
        +"| crowned with small sharp horns.                               |\n"
        +"|                                                               |\n"
        +"| Asmodeus is usually wearing red and black robes which are     |\n"
        +"| studded with black diamonds and fiery red rubies and wields   |\n"
        +"| a Ruby Rod. It is said that Asmodeus is an ancient schemer and|\n"
        +"| deadly manipulator, orchestrator of the most Machiavellian    |\n"
        +"| of schemes. Unlike several of the other arch devils, he is    |\n"
        +"| supposedly calm and chillingly reasonable to deal with.       |\n"
        +"|                                                               |\n"
        +"| Everything can be Undone...in Time!                           |\n"
        +"|                                                               |\n"
        +"|---------------------------------------------------------------|\n"
        +"|_______________________________________________________________|\n");
        
        return 1;
    }
    
    if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
    {
        write(""
        +" ===============================================================\n"
        +"|  Y O U R   P A T R O N :               H A S T U R            |\n"
        +"|---------------------------------------------------------------|\n"
        +"|                                                               |\n"
        +"| Hastur, aka the King in Yellow, or the Yellow King, is the    |\n"
        +"| brother of the migthy Cthulhu and is a Great Old One. This    |\n"
        +"| powerful entity controls both time and space, and brings      |\n"
        +"| madness and despair to gods and mortals alike. Unlike other   |\n"
        +"| Great Old Ones, Hastur often uses the destructive power that  |\n"
        +"| is embedded in the egoes of any sentient living to spread     |\n"
        +"| chaos, madness, despair, dominance and influence.             |\n"
        +"|                                                               |\n"
        +"| Servants of Hastur are all mad with their minds touched and   |\n"
        +"| minds lost, fanatical to the cause of spreading Hastur's      |\n"
        +"| will by spreading the Yellow Sign, which the mere sight of    |\n"
        +"| itself corrupts and taints the mortal minds. Hastur often     |\n"
        +"| reside in Carcosa, an distant alien city on some other        |\n"
        +"| world that reside under the visage of several black stars.    |\n"
        +"|                                                               |\n"
        +"| His appearance, or avatar, is often depicted as an alien      |\n"
        +"| figure dressed in tattered yellow hooded robe with a smooth   |\n"
        +"| and featureless mask, but he do take other forms that is      |\n"
        +"| often to alien to describe for mere mortals, or beyond        |\n"
        +"| their comprehension.                                          |\n"
        +"|                                                               |\n"
        +"| Spread the Song! Spread the Sign! Spread the Madness!         |\n"
        +"|---------------------------------------------------------------|\n"
        +"|_______________________________________________________________|\n");
        
        return 1;
    }
    
    if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
         write(""
        +" ===============================================================\n"
        +"|  Y O U R   P A T R O N :        B A B A   Z I R A N A         |\n"
        +"|---------------------------------------------------------------|\n"
        +"|                                                               |\n"
        +"| The Archfey Baba Zirana is a force of raw nature and resides  |\n"
        +"| in the Feywild, the plane Faerie, which exist in parallel to  |\n"
        +"| the Prime material plane. Her origin is unknown, but she      |\n"
        +"| hunts and consumes everything in her path in the Feywild      |\n"
        +"| forests that she considers unworthy of her presence.          |\n"
        +"| Consuming in this context means literary that, both blood     |\n"
        +"| and flesh.                                                    |\n"
        +"|                                                               |\n"
        +"| While regulary taking the shape of her true form, a gruesome  |\n"
        +"| hag, she sometimes depict herself as a young maid, a form she |\n"
        +"| sometime takes after consuming the necessary amount of fresh  |\n"
        +"| infant blood and flesh. Supposedly, her younger form is what  |\n"
        +"| she once was before time and arcane corruption took its       |\n"
        +"| toll along with altering her sanity. Raw power is never       |\n"
        +"| free.                                                         |\n"
        +"|                                                               |\n"
        +"| Her followers share the lust and craving of mortal flesh,     |\n"
        +"| especially from infants, and it's not uncommon to use the     |\n"
        +"| bones and the leftovers in pastry and breads.                 |\n"
        +"|                                                               |\n"
        +"| As it's said: Dead mortals and infants no longer require      |\n"
        +"| their flesh and blood, and besides, it's...sweet,             |\n"
        +"| empowering and restores...Youth!                              |\n"
        +"|---------------------------------------------------------------|\n"
        +"|_______________________________________________________________|\n");
        
        return 1;
    }
    
    write("You currently don't have a patron.\n");
    
    return 1;   
}
    

public int
walist(string str)
{
    setuid();
    seteuid(getuid());

    MEMBER_LIST_UTILITY->list_members();

    return 1;
}


int
do_wadefensive(string arg)
{
    if ((arg != "on") && (arg != "off"))
    {
        if (this_player()->query_war_defensive() == 1)
        {
            notify_fail(capitalize(query_verb()) + " on/off?\nIt's currently "
            +"ON at the moment.\n");
            return 0;
        }

        notify_fail(capitalize(query_verb()) + " on/off?\nIt's currently "
        +"OFF at the moment.\n");
        return 0;
    }

    if (arg == "on")
    {
        if (this_player()->query_war_defensive() == 1)
        {
            write("You are focusing on being defensive already!\n");
            return 1;
        }

        if (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player()) ||
        present("_warpreality_object_", this_player()) || 
        present("_sculptor_object_", this_player()))
        {
            write("You must dispel all your offensive and defensive "
            +"persistent spells before switching stance!\n");
            return 1;
        }

        this_player()->set_war_defensive(1);
        
        write("You will channel your spells to be stronger "
        +" in defense and weaker in offence.\n");
        
        return 1;
    }

    if (!this_player()->query_war_defensive())
    {
        write("But you are not trying to be defensive!\n");
        return 1;
    }

    if (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player()) ||
        present("_warpreality_object_", this_player()) || 
        present("_sculptor_object_", this_player()))
    {
        write("You must dispel all your offensive and defensive "
        +"persistent spells before switching stance!\n");
        
        return 1;
    }

    this_player()->set_war_defensive(0);

    write("You will channel your spells to be stronger "
    +" in offence and weaker in defense.\n");

    return 1;
}


int
set_component1(string str)
{
    chip_component = str;

    return 1;
}


string
query_component1()
{
    return chip_component;
}


int
set_component2(string str)
{
    shop_component = str;

    return 1;
}


string
query_component2()
{
    return shop_component;
}


int
set_component3(string str)
{
    herb_component = str;

    return 1;
}


string
query_component3()
{
    return herb_component;
}


int
create_charm(string str)
 {
    object *obj1;
    object *obj2;
    object *obj3;

    string charm_ob_name;

    object charm;

    if (!str)
    {
        write("Create which charm?\n");
        
        return 1;
    }

    // String for charms we want to make.
    switch(str)
    {
        // Warp Reality
        case "uralane":
        set_component1("_war_knee_chip");
        set_component2("_war_tear");
        set_component3("blackberry");
        charm_ob_name = "war_flat_charm_1";
        break;

        case "urfenn":
        set_component1("_war_knee_chip");
        set_component2("_war_blood");
        set_component3("chervil");
        charm_ob_name = "war_flat_charm_2";
        break;

        /*case "urchass":
        set_component1("_war_knee_chip");
        set_component2("_war_heart_piece");
        set_component3("suranie");
        charm_ob_name = "war_flat_charm_3";
        break;*/

        // Falselife
        case "urbienc":
        set_component1("_war_knee_chip");
        set_component2("_war_blood");
        set_component3("basil");
        charm_ob_name = "war_flat_charm_4";
        break;

        // Ascendant Step
        case "uraene":
        set_component1("_war_knee_chip");
        set_component2("_war_spleen");
        set_component3("laurel");
        charm_ob_name = "war_flat_charm_5";
        break;

        // Witchstep
        case "urhuew":
        set_component1("_war_knee_chip");
        set_component2("_war_dust");
        set_component3("tarragon");
        charm_ob_name = "war_flat_charm_6";
        break;

        // Shroud
        case "urwem":
        set_component1("_war_skull_chip");
        set_component2("_war_sulphur");
        set_component3("bilberry");
        charm_ob_name = "war_curved_charm_1";
        break;

        // Shadows
        case "urvaesa":
        set_component1("_war_skull_chip");
        set_component2("_war_dust");
        set_component3("chives");
        charm_ob_name = "war_curved_charm_2";
        break;

        // Mists
        case "urluir":
        set_component1("_war_skull_chip");
        set_component2("_war_powder");
        set_component3("hemlock");
        charm_ob_name = "war_curved_charm_3";
        break;

        // Dread
        case "urgashe":
        set_component1("_war_skull_chip");
        set_component2("_war_guano");
        set_component3("garlic");
        charm_ob_name = "war_curved_charm_4";
        break;

        // Spook
        case "urnerulla":
        set_component1("_war_skull_chip");
        set_component2("_war_sulphur");
        set_component3("pepper");
        charm_ob_name = "war_curved_charm_5";
        break;

        // Mask
        case "urchem":
        set_component1("_war_skull_chip");
        set_component2("_war_wing");
        set_component3("thyme");
        charm_ob_name = "war_curved_charm_6";
        break;

        // Sculptor
        case "urhagash":
        set_component1("_war_heart_piece");
        set_component2("_war_spleen");
        set_component3("suranie");
        charm_ob_name = "war_heart_charm_1";
        break;

        // Aversion
        case "urhaese":
        set_component1("_war_heart_piece");
        set_component2("_war_tear");
        set_component3("garlic");
        charm_ob_name = "war_heart_charm_2";
        break;

        // Eldritch Sight
        case "urhavol":
        set_component1("_war_heart_piece");
        set_component2("_war_powder");
        set_component3("coccinea");
        charm_ob_name = "war_heart_charm_3";
        break;

        /*case "urhamine":
        set_component1("_war_heart_piece");
        set_component2("_war_wing");
        set_component3("foxglove");
        charm_ob_name = "war_heart_charm_4";
        break;*/

        // Rejuvenation
        case "urhadoele":
        set_component1("_war_heart_piece");
        set_component2("_war_blood");
        set_component3("handasse");
        charm_ob_name = "war_heart_charm_5";
        break;

        // Coldlight
        case "urfiviel":
        set_component1("_war_heart_piece");
        set_component2("_war_dust");
        set_component3("coccinea");
        charm_ob_name = "war_heart_charm_6";
        break;

        // Infusion
        case "urkenu":
        set_component1("_war_heart_piece");
        set_component2("_war_tear");
        set_component3("fennel");
        charm_ob_name = "war_heart_charm_7";
        break;

        // Scry
        case "urlob":
        set_component1("_war_heart_piece");
        set_component2("_war_spleen");
        set_component3("savory");
        charm_ob_name = "war_heart_charm_8";
        break;
        default:
        write("Create what? No valid charm type.\n");
        return 1;
    }

    // Chip component
    obj1 = filter(deep_inventory(this_player()),
    &operator(==)(query_component1()) @&->query_name());

    if (!sizeof(obj1))
    {
        write("You don't have the necessary fragmented component to "
        +"create the charm!\n");
        return 1;
    }

    // Shop component
    obj2 = filter(deep_inventory(this_player()),
    &operator(==)(query_component2()) @&->query_name());

    if (!sizeof(obj2))
    {
        write("You don't have the necessary exotic merchandise to "
        +"create the charm!\n");
        return 1;
    }

    // Herb component
    obj3 = filter(deep_inventory(this_player()),
    &operator(==)(query_component3()) @&->query_herb_name());

    if (!sizeof(obj3))
    {
        write("You don't have the necessary herbal component to "
        +"create the charm!\n");
        return 1;
    }

    obj1[0]->set_heap_size(obj1[0]->num_heap() - 1);
    obj2[0]->set_heap_size(obj2[0]->num_heap() - 1);
    obj3[0]->set_heap_size(obj3[0]->num_heap() - 1);

    setuid();
    seteuid(getuid());

    charm = clone_object(WARLOCK_GUILDDIR + "obj/" + charm_ob_name);
    charm->move(this_player(), 1);

    write("With magical energies, you create a "
    +charm->query_short()+" from the components!\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" applies magical energies at something!\n", this_player());

    return 1;
}

///////////////////////// scatter comps /////////////////////////
int
chip_components(string str)
{
    object product, comp;

    setuid();
    seteuid(getuid());

    if (!str)
    {
        write("scatter what?\n");
        return 1;
    }

    if (str == "skull" || str == "skulls")
    {
        object *skulls = filter(deep_inventory(this_player()),
        &operator(==)("skull") @&->query_name());

        if (!sizeof(skulls))
        {
            write("You don't have any skulls.\n");
            return 1;
        }

        comp = skulls[0];

        string comp_short = comp->query_short();

        comp->set_heap_size(comp->num_heap() - 1);

        write("You hold a "+comp_short+" in your hand and whisper "
        +"the sacred words.\nThe "+comp_short+" shatters into several "
        +"pieces of bone.\n");

        tell_room(environment(this_player()), QCTNAME(this_player())
        +" holds a "
        +comp_short+" in his hand, looks at it and whisper a few "
        +"incantations.\nThe "+comp_short+" shatters into several pieces "
        +"of bone.\n", this_player());

        product = clone_object(WARLOCK_GUILDDIR +"obj/war_skull_chip");
        product->set_heap_size(6);
        product->move(this_player(), 1);

        return 1;
    }


    if (str == "kneecap" || str == "kneecaps")
    {
        object *kneecaps = filter(deep_inventory(this_player()),
        &operator(==)("kneecap") @&->query_name());

        if (!sizeof(kneecaps))
        {
            write("You don't have any kneecaps.\n");
            return 1;
        }

        comp = kneecaps[0];

        string comp_short = comp->query_short();

        comp->set_heap_size(comp->num_heap() - 1);

        write("You hold a "+comp_short+" in your hand and whisper "
        +"the sacred words.\nThe "+comp_short+" shatters into several "
        +"pieces of bone.\n");

        tell_room(environment(this_player()), QCTNAME(this_player())
        +" holds a "
        +comp_short+" in his hand, looks at it and whisper a few "
        +"incantations.\nThe "+comp_short+" shatters into several pieces "
        +"of bone.\n", this_player());

        product = clone_object(WARLOCK_GUILDDIR +"obj/war_knee_chip");
        product->set_heap_size(6);
        product->move(this_player(), 1);

        return 1;
    }


    if (str == "heart" || str == "hearts")
    {
        object *hearts = filter(deep_inventory(this_player()),
        &operator(==)("heart") @&->query_name());

        if (!sizeof(hearts))
        {
            write("You don't have any hearts.\n");
            return 1;
        }

        comp = hearts[0];

        string comp_short = comp->query_short();

        comp->set_heap_size(comp->num_heap() - 1);

        write("You hold a "+comp_short+" in your hand and whisper "
        +"the sacred words.\nThe "+comp_short+" shatters into several "
        +"pieces of muscle tissue.\n");

        tell_room(environment(this_player()), QCTNAME(this_player())
        +" holds a "
        +comp_short+" in his hand, looks at it and whisper a few "
        +"incantations.\nThe "+comp_short+" shatters into several pieces "
        +"of muscle tissue.\n", this_player());

        product = clone_object(WARLOCK_GUILDDIR +"obj/war_heart_piece");
        product->set_heap_size(6);
        product->move(this_player(), 1);

        return 1;
    }
}


//////////////////////////// EMOTES /////////////////////////////


//------Asmodeus patron emotes
int do_wadevilapp()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
    {
        write("With a thought, your physically transform into "
        +"a large red-winged devil from the Ninth layer of Hell! You "
        +"laugh devilishly before you transform back into regular form!\n");

        all(" suddenly transforms into a large red-winged terrifying "
        +"devil from the Ninth layer of Hell while laughing devilishly, "
        +"before transforming back again!");
        
        return 1;
    }
    
    return 0;
}


//------Hastur patron emotes
int do_wayellowsign(string str)
{
    object *targ;
    
    if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
    {
        if(!strlen(str)) /* no string supplied */
        {
            write("You pull up a medallion with the Yellow sign. You "
            +"glare at it, feeling your madness increasing slowly.\n");

            all(" pulls up some weird medallion and glares at it while "
            +"grinning madly.");
       
            return 1;
        }

        targ = parse_this(str,"[the] %l");

        if(!sizeof(targ))
        return 0;

        actor("You pull up a medallion with the Yellow sign, and faces it "
        +"directly at",targ, ".");
    
        targetbb(" pulls up some weird medallion and shows it to you. Its "
        +"black surface decorated with an alien weird Yellow Sign suddenly makes "
        +"your heart racing! Pictures of tormented souls, mutilated bodies "
        +"and scattered brains and terrible entities beyond time and space "
        +"flashes through your mind like torture! The gruesome experience "
        +"messes with your mind and sanity!",targ);
        targ->command("scream");
        targ->command("stumble");
    
        all2actbb(" pulls up some weird medallion and faces it directly "
        +"at",targ,".");

        return 1;
    }
    
    return 0;
}


//------Baba Yaga patron emotes
int do_wacannibalism(string str)
{
    object *targ;
    
    if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {    
        if(!strlen(str)) /* no string supplied */
        {
            write("Your hunger makes you dream about consuming some "
            +"fresh infant meat.\n");

            all(" mutters something about consuming some fresh infant meat.");

            return 1;
        }

        targ = parse_this(str,"[the] %l");

        if(!sizeof(targ))
        return 0;
    
        actor("Your hunger makes you dream about sinking your teeth into the "
        +"flesh of",targ, ".");
    
        targetbb(" mutters about sinking " + HIS_HER(TP) 
        +" stinking teeth into your flesh, eating you!",targ);
        targ->command("cringe");
    
        all2actbb(" mutters about sinking " + HIS_HER(TP) 
        +" stinking teeth into",targ,"'s flesh."); 

        return 1;
    }
    
    return 0;
}


int
do_wagrin()
{
    write("Your face contorts into a slight, barely noticable grin.\n");
    all("'s face contorts into a slight, barely noticable grin.");

    return 1;
}


int do_wasmile(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("You struggle to keep your lips from curling as "
        +"you smile ever so slightly.\n");

        all(" fails to mask " + HIS_HER(TP) +" lips from forming "
        +"a slight smile.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You struggle to keep your lips from curling as "
    +"you smile slightly at",targ, ".");

    targetbb(" fails to mask " + HIS_HER(TP) +" lips from forming "
    +"a slight smile in your direction.",targ);

    all2actbb(" fails to mask " + HIS_HER(TP) +" lips from forming "
    +"a slight smile at",targ,".");

    return 1;
}


int do_wanod(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("You tilt your head forward in a barely noticable nod.\n");

        all(" tilts " + HIS_HER(TP) +" head forward in a barely noticable "
        +"nod.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You tilt your head forward at",targ, " in a barely "
    +"noticable nod.");

    targetbb(" tilts " + HIS_HER(TP) +" forward head at you in a "
    +"barely noticable nod.",targ);

    all2actbb(" tilts " + HIS_HER(TP) +" forward head "
    +"at",targ," in a barely noticable nod.");

    return 1;
}


int do_wagreet(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Greet who?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You acknowledge",targ, "'s presence.");

    targetbb(" acknowledges your presence.",targ);

    all2actbb(" acknowledges",targ,"'s presence.");

    return 1;
}


int do_waanger(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Your eyes flicker and flare up in raging anger.\n");

        all(" eyes flicker and flare up in raging anger.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You tilt your head forward at",targ, " in a barely "
    +"noticable nod.");

    targetbb(" eyes turns to you and flare up in raging anger.",targ);

    all2actbb(" eyes turns to",targ," and flare up in raging anger.");

    return 1;
}


int
do_wadepart()
{
    write("You abruptly notify everyone of your intention to depart.\n");

    all(" abruptly you of " + HIS_HER(TP) + " intention to depart.");
    return 1;
}


int
do_wainjury()
{
    write("You get a distant look in your eyes as you gently "
    +"stroke one of your many scars.\n");

    all(" gets a distant look in" + HIS_HER(TP)
    + " eyes as "+HE_SHE(TP)+" gently strokes one of "
    +HIS_HER(TP)+" many scars.");
    return 1;
}


int
do_wadefy()
{
    write("You cross your arms in subtle defiance.\n");

    all(" crosses " + HIS_HER(TP)+" arms in subtle defiance.");
    return 1;
}


int do_waslap(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Your eyes darken as you slap yourself silly across "
        +"the face with the back of your hands! Weird!\n");

        all(" eyes darken and slaps "+HIM_HER(TP)
        +"self silly with the back of "+HIS_HER(TP)+" hands! Weird!");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("Your eyes darken as you slap",targ, " across the face "
    +"with the back of your hand!");

    targetbb(" eyes darken as "+HE_SHE(TP)+" slaps you across your "
    +"face with the back of "+HIS_HER(TP)+" hand!",targ);

    all2actbb(" eyes darken as "+HE_SHE(TP)+" slaps",targ," across "
    +HIS_HER(targ[0])+" face with the back of "+HIS_HER(TP)+" hand!");

    return 1;
}


int do_wadisgust(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Your whole face contorts as your mind rages with disgust.\n");

        all(" face contorts as "+HIS_HER(TP)+" mind seem occupied "
        +"with thoughts of pure disgust.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("Your whole face contorts as you look at",targ, " with "
    +"utter disgust.");

    targetbb(" face contorts as "+HE_SHE(TP)+" looks at you "
    +"with utter disgust",targ);

    all2actbb(" face contorts as "+HE_SHE(TP)
    +" looks at",targ," with utter disgust.");

    return 1;
}


int do_wapinch(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Pinch whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You grab",targ,"'s earlobe and push your nails "
    +"deep into their skin as you tug on it forcefully.");

    targetbb(" grabs your earlobe and pushes "+HIS_HER(TP)
    +" nails deep into their skin as he tugs on it forcefully.",targ);

    all2actbb(" grabs",targ,"'s earlobe and pushes "+HIS_HER(TP)+" nails "
    +"deep into the skin as "+HE_SHE(TP)+" tugs on it forcefully.");

    targ->command("wince");

    return 1;
}


int do_waunaf(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Your face remain motionless.\n");

        all(" face remains motionless.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You look at",targ," with a blank, indifferent stare.");

    targetbb(" looks at you with a blank, indifferent stare.",targ);

    all2actbb(" looks at",targ," with a blank, indifferent stare.");

    return 1;
}


int do_wasmell(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("You smell in your own armpits, but detects nothing "
        +"unusual and shrugs it off.\n");

        all(" smells in "+HIS_HER(TP)+" own armpits, but "
        +"shrugs it off.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You sniff in the vicinity of",targ," and your face pales "
    +"as you are overcome with a distinctly horrifying odour.");

    targetbb(" sniffs in your vicinity and "+HIS_HER(TP)+" face pales "
    +"as "+HE_SHE(TP)+" is seemingly overcome with a horrifying and "
    +"overpowering scent.",targ);

    all2actbb(" sniffs in the vicinity of",targ," and "+HIS_HER(TP)
    +" face pales as "+HE_SHE(TP)+" is seemingly overcome with a horrifying "
    +"and overpowering scent.");

    return 1;
}


int do_waperf(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You look at",targ," disdainfully, clearly not impressed "
    +"with "+HIS_HER(targ[0])+" performance.");

    targetbb(" looks at you disdainfully, clearly not impressed with "
    +"your performance.",targ);

    all2actbb(" looks at",targ," disdainfully, clearly not "
    +"impressed with "+HIS_HER(targ[0])+" performance.");

    return 1;
}


int do_walaugh(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("You completely fail to keep your posture and begin "
        +"producing sounds only heard in the vicinity of pigs. You "
        +"hope that others recognize this cacophony as laughter.\n");

        all(" completely fails to keep "+HIS_HER(TP)+" posture and begin "
        +"producing sounds you've only heard in the vicinity of "
        +"pigs. You struggle, but fall on the conclusion "
        +"that "+HE_SHE(TP)+" is laughing.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You point a finger at",targ," while producing a cacophony of "
    +"vile squealing, unsure if "+HE_SHE(targ[0])+" caught on to your "
    +"intentions.");

    targetbb(" points a finger at you while producing a cacophony of "
    +"squeals, "
    +"you struggle to decipher "+HIS_HER(TP)+" intentions but fall on the "
    +"conclusion that "+HE_SHE(TP)+" is laughing at you.",targ);

    all2actbb(" points a finger at",targ," while producing a cacophony "
    +"of vile squealing, you struggle to decipher "+HIS_HER(TP)+" intentions "
    +"but fall on the conclusion that "+HE_SHE(TP)+" is laughing at "
    +HIM_HER(targ[0])+".");

    return 1;
}


int do_waboggle(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("You shake your head and struggle to keep your jaw locked as "
        +"your mind boggles over the shortcomings of others.\n");

        all(" shakes "+HIS_HER(TP)+" head while clenching "
        +HIS_HER(TP)+" teeth as "+HE_SHE(TP)+" boggles over the shortcomings "
        +"of others.");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You shake your head at",targ," while struggling to keep your jaw "
    +"locked as your mind boggles over "+HIS_HER(targ[0])+" shortcomings.");

    targetbb(" shakes his head at you while while clenching "+HIS_HER(TP)
    +" teeth as "+HE_SHE(TP)+" boggles over your shortcomings.",targ);

    all2actbb(" shakes his head at",targ," while clenching  "+HIS_HER(TP)
    +" teeth as "+HE_SHE(TP)+" boggles over "+HIS_HER(targ[0])
    +" shortcomings.");

    return 1;
}

/****************************************************************
  Robe Emotes
 ***************************************************************/
/*int
do_clean()
{
    if (present("robe",TP)->query_worn()
        || present("cloak",TP)->query_worn())
    {
        write("You pick off dust and debris from your robe untill "
        +"it is clean.\n");
        all(" picks off dust and debris from " + HIS_HER(TP) +
            " robe until it is clean.");
        return 1;
    }
    else
    {
        write("You need to be wearing a robe or cloak.\n");
        return 1;
    }
}

int
do_draw()
{
    if (present("robe",TP)->query_worn() || present("cloak",TP)->query_worn())
    {
        write("You draw folds of your robe tight around yourself.\n");
        all(" draws the folds of " + HIS_HER(TP) + " robe tight around " +
            HIM_HER(TP) + "self.");
        return 1;
    }
    else
    {
        write("You need to be wearing a robe or cloak.\n");
        return 1;
    }
}

int
do_hide()
{
    if (present("robe",TP)->query_worn() || present("cloak",TP)->query_worn())
    {
        write("You hide in the folds of your robe and watch your " +
            "surroundings.\n");
        all(" hides in the folds of " + HIS_HER(TP) + " robe and watches " +
            HIS_HER(TP) + " suroundings.");
        return 1;
    }
    else
    {
        write("You need to be wearing a robe or cloak.\n");
        return 1;
    }
}

int
do_stir()
{
    if (present("robe",TP)->query_worn() || present("cloak",TP)->query_worn())
    {
        write("You stir slightly within the folds of your robe and watch " +
            "your surroundings intently.\n");
        all(" stirs slightly from within the folds of " + HIS_HER(TP) +
            " robe, watching " + HIS_HER(TP) + " suroundings intently.");
        return 1;
    }
    else
    {
        write("You need to be wearing a robe or cloak.\n");
        return 1;
    }
}*/

