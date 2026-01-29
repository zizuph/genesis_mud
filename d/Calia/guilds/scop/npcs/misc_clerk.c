
inherit "/lib/trade";
inherit "/std/monster";
inherit "/d/Calia/std/remember";
inherit "/d/Calia/std/intro";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "defs.h"
#include SPIRIT_HEADER

#define NUM sizeof(MONEY_TYPES)

#pragma save_binary

public string
armoury_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Though "+
        "we are spiritual beings, we still must be trustworthy of the "+
        "Temple that is our body. Armour and weapons will help to protect "+
        "us in the battles that lie ahead.\n");
    return "";
}

public string
battles_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: We are a "+
        "tranquil breeze upon the face of the world, but even the calmest "+
        "wind must sometimes rise up and blow with great fury. We must "+
        "do likewise against the pox of the Soulless.\n");
    return "";
}

public string
aeria_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: In the "+
        "days of my youth I would dance and sing with the blessing of "+
        "my Lady Aeria.  Though I serve Psuchae now, I carry her joy and "+
        "wisdom still.\n");
    TO->command("sweyes");
    return "";
}

public string
psuchae_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Praised be "+
        "Psuchae, the Ruler of Spirit and Shadow.\n");
    return "";
}

public string
ingot_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: The ingot "+
        "is a tool granted for use to hasten the decay of the mortal shells "+
        "of our foes. A cleric need only clean the corpse of the fallen to "+
        "leave behind useful leftovers, some of which retain spiritual "+
        "energies for use by the Clergy.\n");
    return "";
}

public string
soulless_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: The Soulless "+
        "are the dead who remain linked to this world by powerful magic. It "+
        "is our sworn duty to destroy these desecrated bodies so that their "+
        "rightful spirits can at last rest in peace.\n");
    return "";
}

void
create_monster()
{
    set_name("Tahla");
    add_name("tahla");
    set_adj(({"captivating","brown-robed"}));
    set_title("the Storehouse Guardian"); 
    set_race_name("elf");
    set_gender(G_FEMALE);
    set_stats(({100,100,100,100,100,100}));
    
    set_base_stat(SS_OCCUP, 115);
    set_skill(SS_DEFENCE,100);
    add_prop(LIVE_I_ALWAYSKNOWN,1);
    default_config_trade();

    clone_object("/d/Calia/guilds/scop/specials/spiritshadow")->shadow_me(TO,
        "occupational", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/specials/spiritlayshadow")->shadow_me(TO,
        "layman", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/objects/holy_symbol")->move(TO);

    set_skill(SS_PATRON_ELEMENTAL,AIR_FLAG);
    set_alignment(1100);
    set_intro_delay(1);
    set_act_time(60);
    add_act("emote eyes the armoury with a discriminating glance.");
    add_act("emote chews thoughtfully on her quill, while double-checking "+
        "the donation scroll on the wall.");
    add_act("emote sorts quickly through the Temple supplies, to ensure "+
        "they are well-stocked.");
    add_act("emote gives you a stern look, and you are reminded to take "+
        "care of the equipment you borrow.");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"armoury","armour","weapons","weapon","armours"}),&armoury_answer());
    add_ask(({"battle","battles"}),&battles_answer());
    add_ask(({"aeria","lady aeria","winds","air"}),&aeria_answer());
    add_ask(({"psuchae"}),&psuchae_answer());
    add_ask(({"ingot","ingots"}),&ingot_answer());
    add_ask(({"soulless","undead"}),&soulless_answer());
}

public string
default_answer()
{
    command("emote telepathically says to you: I do not know of what "+
        "you speak.");
    return "";
}

void
init_living()
{
    ::init_living();
    add_action("do_buy","buy");
}

int
do_buy(string str)
{
    object item;
    string str2,str3;
    int *arr, price, num,iprice;
    switch(str)
    {
        case "gloves":
            item = clone_object("/d/Calia/sea/objects/herb_gloves");
            iprice = 24;
            break;
        case "herb gloves":
            item = clone_object("/d/Calia/sea/objects/herb_gloves");
            iprice = 24;
            break;
        case "ingot":
            item = clone_object("/d/Calia/sea/objects/corpse_cleaner");
            iprice = 4000;
            break;
        case "silver ingot":
            item = clone_object("/d/Calia/sea/objects/corpse_cleaner");
            iprice = 4000;
            break;
        case "wrap":
            item = clone_object("/d/Shire/common/herbs/obj/wrap");
            iprice = 33;
            break;
        case "herbwrap":
            item = clone_object("/d/Shire/common/herbs/obj/wrap");
            iprice = 33;
            break;
        case "herb wrap":
            item = clone_object("/d/Shire/common/herbs/obj/wrap");
            iprice = 33;
            break;
        case "componentpouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "component pouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "herbpouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "herb pouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "pouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "herbjar":
            item = clone_object("/d/Gondor/common/guild/obj/herbjar");
            iprice = 24;
            break;
        case "herb jar":
            item = clone_object("/d/Gondor/common/guild/obj/herbjar");
            iprice = 24;
            break;
        case "jar":
            item = clone_object("/d/Gondor/common/guild/obj/herbjar");
            iprice = 24;
            break;
        case "sheath":
            item = clone_object(SPIRIT_OBJECTS+"arm_sheath");
            iprice = 450;
            break;
        case "sheathe":
            item = clone_object(SPIRIT_OBJECTS+"arm_sheath");
            iprice = 450;
            break;
        case "lantern":
		case "lamp":
            item = clone_object(SPIRIT_OBJECTS+"sturdy_lantern");
            iprice = 201;
            break;
	    case "oil":
		case "flask of oil":
		case "lantern-oil":
		case "lantern oil":
		case "lamp-oil":
		case "lamp oil":
            item = clone_object(SPIRIT_OBJECTS+"large_oil_flask");
            iprice = 173;
            break;

        default: 
            NF("I don't have any items named "+str+".\n");
            return 0;
    }
    price = iprice;
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
       return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
       write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("You get a "+item->short()+".\n");
    say(QCTNAME(TP)+" gets a "+item->short()+".\n");
    if(item->move(TP))
    {
        write("Its too heavy, and you drop it.\n");
        item->move(environment(TP));
    }
    return 1;
}
